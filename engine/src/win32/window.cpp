#include <window.hpp>
#include <putils.hpp>
#include "pwindows.hpp"

void wPaper_resizeWindow(GLsizei width,GLsizei height,bool loadI = true)
{
    GLfloat aspect;
    glViewport(0,0,width,height);
    aspect = (GLfloat)width/height;
    glMatrixMode(GL_PROJECTION);
    if(loadI) glLoadIdentity();
    gluPerspective(45.0,aspect,3.0,7.0);
    glMatrixMode(GL_MODELVIEW);
}

void test_obj()
{
    GLUquadricObj *obj;

    glNewList(1,GL_COMPILE);
        obj = gluNewQuadric();
        gluQuadricDrawStyle(obj,GLU_LINE);
        gluSphere(obj,1.5,16,16);
    glEndList();

}

void wPaper_initGL(GLsizei width,GLsizei height)
{
    glClearIndex(0);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    wPaper_resizeWindow(width,height,false);
    test_obj();
}

void wPaper_SetupPixelFormat(HDC)
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

    pixelformat = ChoosePixelFormat(Paper::windows.hdc,ppfd);

    if((pixelformat = ChoosePixelFormat(Paper::windows.hdc,ppfd)) == 0)
    {
        THROW_PE("windows","ChoosePixelFormat failed!");
    }
    if(SetPixelFormat(Paper::windows.hdc,pixelformat,ppfd) == FALSE)
    {
        THROW_PE("windows","SetPixelFormat failed!");
    }
}

LONG WINAPI wPaper_WindowProcess(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
    LONG lRet = 1;
    PAINTSTRUCT ps;
    RECT rect;
    HDC hdc;
    HGLRC hrc;
    switch(uMsg)
    {
        case WM_CREATE:
            hdc = GetDC(hwnd);
            Paper::windows.hdc = hdc;
            wPaper_SetupPixelFormat(hdc);
            hrc = wglCreateContext(hdc);
            Paper::windows.hrc = hrc;
            wglMakeCurrent(hdc,hrc);
            GetClientRect(hwnd,&rect);
            wPaper_initGL(rect.right,rect.bottom);
            break;
        case WM_PAINT:
            BeginPaint(hwnd,&ps);
            EndPaint(hwnd,&ps);
            break;
        case WM_SIZE:
            GetClientRect(hwnd,&rect);
            wPaper_resizeWindow(rect.right,rect.bottom);
            break;
        case WM_CLOSE:
            try
            {
                if(hrc) wglDeleteContext(hrc);
                if(hdc) ReleaseDC(hwnd,hdc);
                hrc = 0,Paper::windows.hrc = 0;
                hdc = 0,Paper::windows.hdc = 0;
                DestroyWindow(hwnd);
            }
            catch(const std::exception& e)
            {
                (void)e;
                return lRet;
            }
            break;
        case WM_DESTROY:
            if(hrc) wglDeleteContext(hrc);
            if(hdc) ReleaseDC(hwnd,hdc);
            PostQuitMessage(0);
            break;
        case WM_KEYDOWN:
            Paper::PWindow::getInstance().onKeyInput((unsigned int)wParam);
            break;
        default:
            lRet = (LONG)DefWindowProc(hwnd,uMsg,wParam,lParam);
            break;
    }
    return lRet;
}

BOOL wPaper_RegisterClass()
{
    WNDCLASS wndclass;
    wndclass.style = 0;
    wndclass.lpfnWndProc = (WNDPROC)wPaper_WindowProcess;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = Paper::windows.hInstance;
    wndclass.hIcon = LoadIcon(Paper::windows.hInstance,PWINDOWS_APPNAME);
    wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wndclass.lpszMenuName = PWINDOWS_APPNAME;
    wndclass.lpszClassName = PWINDOWS_APPNAME;
    return RegisterClass(&wndclass);
}

void testDraw()
{    

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
        glIndexi(16);
        glCallList(1);
    glPopMatrix();

    SwapBuffers(Paper::windows.hdc);
}

namespace Paper
{
    PWindow::PWindow()
    {

    }

    void PWindow::init(int c,char** v)
    {
        this->argc = c,this->argv = v;
        windows.hInstance = GetModuleHandle(0);
        windows.lpCmdLine = GetCommandLineA();
        STARTUPINFOA info;
        GetStartupInfoA(&info);
        windows.nCmdShow = info.wShowWindow;
        if(!wPaper_RegisterClass())
            THROW_PE("windows","Couldn't register class!");
        HWND hwnd = CreateWindow(PWINDOWS_APPNAME,PWINDOWS_APPNAME,WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
        CW_USEDEFAULT,CW_USEDEFAULT,640,480,NULL,NULL,windows.hInstance,NULL);
        if(!hwnd) THROW_PE("window","Couldn't create Window!");
        windows.hwnd = hwnd;
        ShowWindow(windows.hwnd,windows.nCmdShow);
        UpdateWindow(windows.hwnd);
        windowLoop();
    }
    void PWindow::windowLoop()
    {
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
            testDraw();
        }
    }
    void PWindow::onKeyInput(unsigned int keycode)
    {

    }
}