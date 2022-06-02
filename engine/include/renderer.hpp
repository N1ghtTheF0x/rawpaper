#if !defined(PAPER_RENDERER)
#define PAPER_RENDERER

#ifdef IS_LINUX
    #include <GL/glx.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <X11/keysym.h>
    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
#endif

#ifdef IS_WINDOWS
    #include "pwin.hpp"
    #include <gl/GL.h>
    #include <gl/GLU.h>
#endif

namespace Paper
{
    class PRenderer
    {
    private:
        PRenderer();
    public:
        static PRenderer &getInstance();

        void init(int x,int y,unsigned int width,unsigned int height);
        void close();
        void showWindow();
        void hideWindow();
#ifdef IS_LINUX
    private:
        Display *dis;
        int screen;
        Window win;

        GLXFBConfig *fbconfig;
        GLXContext context;
        XVisualInfo *vi;
        Colormap cmap;

        XEvent event;
    public:
        XEvent *getLinuxEvent();
        Display &getLinuxDisplay();
        int getLinuxScreen();
        Window &getLinuxWindow();
#endif
#ifdef IS_WINDOWS
    private:
        HGLRC hrc;
    public:
        void setWindowsHRC(HGLRC hrc);
        HGLRC getWindowsHRC();
#endif
    };
}

#endif