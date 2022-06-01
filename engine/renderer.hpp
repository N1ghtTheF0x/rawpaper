#if !defined(PAPER_RENDERER)
#define PAPER_RENDERER

#ifdef IS_LINUX
    #include <GL/gl.h>
    #include <GL/glx.h>
    #include <GL/glxext.h>
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

        void init();
#ifdef IS_LINUX
    private:
        GLXFBConfig *fbconfig;
        GLXContext context;
        XVisualInfo *vi;
        Colormap cmap;
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