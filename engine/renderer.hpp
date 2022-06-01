#if !defined(PAPER_RENDERER)
#define PAPER_RENDERER

#include "window.hpp"

#ifdef IS_LINUX
    #include <GL/gl.h>
    #include <GL/glx.h>
    #include <GL/glxext.h>
#endif

namespace Paper
{
    class PRenderer
    {
    private:
        PWindow &window;
        void init();
    public:
        PRenderer(PWindow &window);
#ifdef IS_LINUX
    private:
        GLXFBConfig *fbconfig;
        GLXContext context;
        XVisualInfo *vi;
        Colormap cmap;
#endif
    };
}

#endif