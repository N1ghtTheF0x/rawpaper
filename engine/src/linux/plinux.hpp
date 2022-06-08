#if !defined(PAPER_LINUX)
#define PAPER_LINUX

#include <GL/glx.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <X11/keysym.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

namespace Paper
{
    struct PLinux
    {
        Display *dpy;
        Window win;
        GLXContext ctx;
        XVisualInfo *vi;
        XEvent event;
    } instance;
}

#endif