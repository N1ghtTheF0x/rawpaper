#include "../../include/renderer.hpp"

#include "../../include/window.hpp"

//#include <putils.hpp>

Bool lPaper_WaitForMapNotify(Display *dis,XEvent *event,char *arg)
{
    if((event->type == MapNotify) && (event->xmap.window == (Window)arg))
        return GL_TRUE;
    return GL_FALSE;
}

namespace Paper
{
    PRenderer &PRenderer::getInstance()
    {
        static PRenderer instance;
        return instance;
    }
    PRenderer::PRenderer()
    {
        dis = XOpenDisplay(NULL);
        screen = DefaultScreen(dis);
    }
    void PRenderer::close()
    {
        XDestroyWindow(dis,win);
        XCloseDisplay(dis);
    }
    void PRenderer::showWindow()
    {

    }
    void PRenderer::hideWindow()
    {
        
    }
    void PRenderer::init(int x,int y,unsigned int width,unsigned int height)
    {
        int attr[] = {GLX_DEPTH_SIZE, 16,GLX_DOUBLEBUFFER, None};
        XSetWindowAttributes swa;
        int dummy;
        if(!glXQueryExtension(dis,&dummy,&dummy))
            THROW_PE("[renderer]","Could not query OpenGL Extension");
        vi = glXChooseVisual(dis,DefaultScreen(dis),attr);
        if(vi == NULL)
            throw "[renderer] Could not get Visual Info!";
        context = glXCreateContext(dis,vi,None,GL_TRUE);
        if(context == NULL)
            throw "[renderer] Could not create OpenGL Context!";
        cmap = XCreateColormap(dis,vi->screen,vi->visual,AllocNone);
        swa.colormap = cmap;
        swa.border_pixel = 0;
        swa.event_mask = ExposureMask | KeyPressMask | StructureNotifyMask;
        PWindow::getInstance().create(x,y,width,height,vi,swa);
        glXMakeCurrent(dis,win,context);
        XMapWindow(dis,win);
        XIfEvent(dis,&event,lPaper_WaitForMapNotify,(char*)win);
    }
    XEvent *PRenderer::getLinuxEvent()
    {
        return &event;
    }
    Display &PRenderer::getLinuxDisplay()
    {
        return *dis;
    }
    int PRenderer::getLinuxScreen()
    {
        return screen;
    }
    Window &PRenderer::getLinuxWindow()
    {
        return win;
    }
}