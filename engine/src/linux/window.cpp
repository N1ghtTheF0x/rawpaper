#include <window.hpp>
#include <putils.hpp>

#include "plinux.hpp"

static Bool lPaper_WaitForMapNotify(Display *dpy,XEvent *event,char* arg)
{
    if((event->type == MapNotify) && (event->xmap.window == (Window)arg)) return GL_TRUE;
    return GL_FALSE;
}

void lPGL_resize(GLsizei width,GLsizei height)
{
    GLfloat aspect;
    glViewport(0,0,width,height);
    aspect = (GLfloat)width/height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,aspect,3.0,7.0);
    glMatrixMode(GL_MODELVIEW);
}

void lPGL_init()
{
    GLfloat aspect;
    glClearIndex((GLfloat)0);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    aspect = (GLfloat)PAPER_WINDOW_WIDTH/PAPER_WINDOW_HEIGHT;
    gluPerspective(45.0,aspect,3.0,7.0);
    glMatrixMode(GL_MODELVIEW);
}

void lPaper_SetupOpenGL()
{
    int attr[] = {GLX_DEPTH_SIZE,16,GLX_DOUBLEBUFFER,None};
    int dummy;
    if(!glXQueryExtension(Paper::instance.dpy,&dummy,&dummy)) THROW_PE("glx","Couldn't query extension!");
    Paper::instance.vi = glXChooseVisual(Paper::instance.dpy,DefaultScreen(Paper::instance.dpy),attr);
    if(Paper::instance.vi == NULL) THROW_PE("glx","Couldn't choose visual!");
    Paper::instance.ctx = glXCreateContext(Paper::instance.dpy,Paper::instance.vi,None,GL_TRUE);
    if(Paper::instance.ctx == NULL) THROW_PE("glx","Couldn't create context!");
}

void lPaper_CreateDisplay(int argc,char** argv)
{
    Colormap cmap;
    XSetWindowAttributes swa;

    cmap = XCreateColormap(Paper::instance.dpy,RootWindow(Paper::instance.dpy,Paper::instance.vi->screen),Paper::instance.vi->visual,AllocNone);
    swa.colormap = cmap;
    swa.border_pixel = 0;
    swa.event_mask = ExposureMask | KeyPressMask | StructureNotifyMask;
    Paper::instance.win = XCreateWindow(Paper::instance.dpy,RootWindow(Paper::instance.dpy,Paper::instance.vi->screen),0,0,PAPER_WINDOW_WIDTH,PAPER_WINDOW_HEIGHT,0,Paper::instance.vi->depth,InputOutput,Paper::instance.vi->visual,CWBorderPixel | CWColormap | CWEventMask,&swa);
    XSetStandardProperties(Paper::instance.dpy,Paper::instance.win,PAPER_APPNAME,PAPER_APPNAME,None,argv,argc,NULL);
    glXMakeCurrent(Paper::instance.dpy,Paper::instance.win,Paper::instance.ctx);
    XMapWindow(Paper::instance.dpy,Paper::instance.win);
    XIfEvent(Paper::instance.dpy,&Paper::instance.event,lPaper_WaitForMapNotify,(char*)Paper::instance.win);
}

namespace Paper
{
    PWindow::PWindow()
    {

    }

    void PWindow::init(int argc,char** argv)
    {
        this->argc = argc,this->argv = argv;
        instance.dpy = XOpenDisplay(NULL);
        if(instance.dpy == NULL) THROW_PE("x11","Couldn't open display!");
        lPaper_SetupOpenGL();
        lPaper_CreateDisplay(argc,argv);
        lPGL_init();
        lPGL_resize(PAPER_WINDOW_WIDTH,PAPER_WINDOW_HEIGHT);
        windowLoop();
    }

    void PWindow::windowLoop()
    {
        while(1)
        {
            while(XPending(instance.dpy))
            {
                XNextEvent(instance.dpy,&instance.event);
                switch(instance.event.type)
                {
                    case ConfigureNotify:
                        lPGL_resize(instance.event.xconfigure.width,instance.event.xconfigure.height);
                        break;
                    case KeyPress:
                        onKeyInput(instance.event.xbutton.button);
                        break;
                    default:
                        break;
                }
            }

        }
    }

    void PWindow::onKeyInput(unsigned int keycode)
    {

    }
}