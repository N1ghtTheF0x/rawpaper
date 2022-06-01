#include "window.hpp"

#include "renderer.hpp"

#ifdef IS_WINDOWS


const CHAR appName[] = "Raw Paper Engine";

BOOL wPaper_SetupPixelFormat(HDC hdc)
{
    PIXELFORMATDESCRIPTOR pfd, *ppfd;
    int pixelformat;

    ppfd = &pfd;

    ppfd->nSize = sizeof(PIXELFORMATDESCRIPTOR);
    ppfd->nVersion = 1;
    ppfd->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    ppfd->dwLayerMask = PFD_MAIN_PLANE;
    ppfd->iPixelType = PFD_TYPE_COLORINDEX;
    ppfd->cColorBits = 8;
    ppfd->cDepthBits = 16;
    ppfd->cAccumBits = 0;
    ppfd->cStencilBits = 0;

    pixelformat = ChoosePixelFormat(hdc,ppfd);
    if((pixelformat = ChoosePixelFormat(hdc,ppfd)) == 0)
    {
        MessageBox(NULL,"Failed to choose pixelformat","[windows] SetupPixelFormat Error",MB_OK);
        return FALSE;
    }
    if(SetPixelFormat(hdc,pixelformat,ppfd) == FALSE)
    {
        MessageBox(NULL,"Failed to set pixelformat","[windows] SetPixelFormat Error",MB_OK);
        return FALSE;
    }
    return TRUE;
}

LONG WINAPI wPaper_Process(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
    LONG lRet = 1;
    PAINTSTRUCT ps;
    RECT rect;

    switch(uMsg)
    {
        case WM_CREATE:
        {
            HDC hdc = GetDC(hwnd);
            Paper::PWindow::getInstance().setWindowsHDC(hdc);
            if(!wPaper_SetupPixelFormat(hdc)) PostQuitMessage(0);
            HGLRC hrc = wglCreateContext(hdc);
            Paper::PRenderer::getInstance().setWindowsHRC(hrc);
            wglMakeCurrent(hdc,hrc);
            GetClientRect(hwnd,&rect);
            break;
        }
        case WM_PAINT:
        {
            BeginPaint(hwnd,&ps);
            EndPaint(hwnd,&ps);
            break;
        }
        case WM_SIZE:
        {
            GetClientRect(hwnd,&rect);
            glViewport(0,0,rect.right,rect.bottom);
            break;
        }
        case WM_CLOSE:
        {
            HGLRC hrc = Paper::PRenderer::getInstance().getWindowsHRC();
            if(hrc) wglDeleteContext(hrc);
            HDC hdc = Paper::PWindow::getInstance().getWindowsHDC();
            if(hdc) ReleaseDC(hwnd,hdc);
            Paper::PRenderer::getInstance().setWindowsHRC(0);
            Paper::PWindow::getInstance().setWindowsHDC(0);
            DestroyWindow(hwnd);
            break;
        }
        case WM_DESTROY:
        {
            HGLRC hrc = Paper::PRenderer::getInstance().getWindowsHRC();
            if(hrc) wglDeleteContext(hrc);
            HDC hdc = Paper::PWindow::getInstance().getWindowsHDC();
            if(hdc) ReleaseDC(hwnd,hdc);
            PostQuitMessage(0);
            break;
        }
        case WM_KEYDOWN:
        {
            unsigned int keycode = static_cast<unsigned int>(wParam);
            Paper::PWindow::getInstance().emitKeyboardInput(keycode);
            break;
        }
        default:
        {
            lRet = static_cast<LONG>(DefWindowProc(hwnd,uMsg,wParam,lParam));
            break;
        }
    }
    return lRet;
}

void wPaper_registerClass()
{
    WNDCLASS wnd;
    HINSTANCE hinst = GetModuleHandle(0);
    wnd.style = 0;
    wnd.lpfnWndProc = (WNDPROC)wPaper_Process;
    wnd.cbClsExtra = 0;
    wnd.cbWndExtra = 0;
    wnd.hInstance = hinst;
    wnd.hCursor = LoadIcon(hinst,appName);
    wnd.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wnd.lpszMenuName = appName;
    wnd.lpszClassName = appName;
    if(!RegisterClass(&wnd)) throw "[windows] Couldn't register class!";
}

#endif

namespace Paper
{
    PWindow::PWindow()
    {

    }
    PWindow &PWindow::getInstance()
    {
        static PWindow instance;
        return instance;
    }

    void PWindow::init(int argc,char** argv)
    {
        this->argc = argc;
        this->argv = argv;
#ifdef IS_LINUX
        screen = DefaultScreen(dis);
#endif
#ifdef IS_WINDOWS
        hInstance = GetModuleHandle(0);
        lpCmdLine = GetCommandLine();
        STARTUPINFO info;
        GetStartupInfo(&info);
        nCmdShow = info.wShowWindow;
        
#endif
    }

    void PWindow::create(int x,int y,unsigned int width,unsigned int height)
    {
#ifdef IS_LINUX
        unsigned long black = BlackPixel(dis,screen), white = WhitePixel(dis,screen);
        win = XCreateSimpleWindow(dis,DefaultRootWindow(dis),x,y,width,height,5,white,black);
        XSelectInput(dis,win,ExposureMask|ButtonPressMask|KeyPressMask);
        gc = XCreateGC(dis,win,0,0);
        XSetBackground(dis,gc,white);
        XSetForeground(dis,gc,black);
        XClearWindow(dis,win);
        XMapRaised(dis,win);
#endif
#ifdef IS_WINDOWS
        hwnd = CreateWindow(appName,"",WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,x,y,width,height,NULL,NULL,hInstance,NULL);
        if(!hwnd) throw "[windows] Couldn't create window!";
        show();
        UpdateWindow(hwnd);
#endif
        windowLoop();
    }

    void PWindow::setName(const char* title)
    {
#ifdef IS_LINUX
        XStoreName(dis,DefaultRootWindow(dis),title);
#endif
    }

    void PWindow::close()
    {
#ifdef IS_LINUX
        XFreeGC(dis,gc);
        XDestroyWindow(dis,win);
        XCloseDisplay(dis);
#endif
    }

    void PWindow::show()
    {
#ifdef IS_WINDOWS
        ShowWindow(hwnd,SW_SHOW);
#endif
    }

    void PWindow::hide()
    {
#ifdef IS_WINDOWS
        ShowWindow(hwnd,SW_HIDE);
#endif
    }

    void PWindow::windowLoop()
    {
#ifdef IS_LINUX
        XEvent event;
        while(1)
        {
            XNextEvent(dis,&event);
            if(event.type == Expose && event.xexpose.count == 0)
                draw();
            if(event.type == KeyPress)
                handleKeyboardInput(event.xkey.keycode);
            if(event.type == ButtonPress)
                handleMouseInput(event.xbutton.x,event.xbutton.y,event.xbutton.button);
        }
        close();
        
#endif
#ifdef IS_WINDOWS
        MSG msg;
        while(1)
        {
            while(PeekMessage(&msg,NULL,0,0,PM_NOREMOVE) == TRUE)
            {
                if(GetMessage(&msg,NULL,0,0))
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
                else break;
            }
            draw();
        }
#endif
    }

    void PWindow::draw()
    {

    }

    void PWindow::emitKeyboardInput(unsigned int keycode)
    {
        handleKeyboardInput(keycode);
    }

    void PWindow::handleKeyboardInput(unsigned int keycode)
    {

    }

    void PWindow::handleMouseInput(int x,int y,unsigned int buttons)
    {

    }
#ifdef IS_WINDOWS
    void PWindow::setWindowsHDC(HDC hdc)
    {
        this->hdc = hdc;
    }
    HDC PWindow::getWindowsHDC()
    {
        return hdc;
    }
    HWND PWindow::getWindowsHWND()
    {
        return hwnd;
    }
#endif
#ifdef IS_LINUX
    Display* PWindow::getLinuxDisplay()
    {
        return dis;
    }
    int PWindow::getLinuxScreen()
    {
        return screen;
    }
    Window* PWindow::getLinuxWindow()
    {
        return &win;
    }
    GC* PWindow::getLinuxGC()
    {
        return &gc;
    }
#endif
}