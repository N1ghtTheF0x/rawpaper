#include "window.hpp"

namespace Paper
{
    PWindow::PWindow(int argc,char** argv)
    {
        this->argc = argc;
        this->argv = argv;
#ifdef IS_LINUX
        screen = DefaultScreen(dis);
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

    void PWindow::windowLoop()
    {
#ifdef IS_LINUX
        XEvent event;
        while(1)
        {
            XNextEvent(dis,&event);
            if(event.type == Expose && event.xexpose.count == 0)
                redraw();
            if(event.type == KeyPress)
                handleKeyboardInput(event.xkey.keycode);
            if(event.type == ButtonPress)
                handleMouseInput(event.xbutton.x,event.xbutton.y,event.xbutton.button);
        }
        close();
        
#endif
    }

    void PWindow::redraw()
    {

    }

    void PWindow::handleKeyboardInput(unsigned int keycode)
    {

    }

    void PWindow::handleMouseInput(int x,int y,unsigned int buttons)
    {

    }
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