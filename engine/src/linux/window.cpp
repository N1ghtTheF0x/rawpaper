#include "../../include/window.hpp"

#include "../../include/renderer.hpp"

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

    void PWindow::init(int c,char** v)
    {
        argc = c;
        argv = v;
    }

    void PWindow::setName(const char* title)
    {
        XStoreName(dis,win,title);
    }

    void PWindow::create(int x,int y,unsigned int width,unsigned int height)
    {
        PRenderer::getInstance().init(x,y,width,height);
    }

    void PWindow::create(int x,int y,unsigned int width,unsigned int height,XVisualInfo *vs,XSetWindowAttributes &swa)
    {
        win = XCreateWindow(dis,RootWindow(dis,vs->screen),x,y,width,height,0,vs->depth,InputOutput,vs->visual,CWBorderPixel | CWColormap | CWEventMask,&swa);
    }

    void PWindow::close()
    {
        XDestroyWindow(dis,win);
        XCloseDisplay(dis);
    }

    void PWindow::show()
    {

    }

    void PWindow::hide()
    {
        
    }

    void PWindow::draw()
    {

    }

    void PWindow::windowLoop()
    {
        XEvent *event = PRenderer::getInstance().getLinuxEvent();
        while(1)
        {
            XNextEvent(dis,event);
            if(event->type == Expose && event->xexpose.count == 0)
                draw();
            if(event->type == KeyPress)
                handleKeyboardInput(event->xkey.keycode);
            if(event->type == ButtonPress)
                handleMouseInput(event->xbutton.x,event->xbutton.y,event->xbutton.button);
        }
        close();
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
}