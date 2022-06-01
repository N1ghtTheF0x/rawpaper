#include "renderer.hpp"

namespace Paper
{
    PRenderer::PRenderer(PWindow &w): window(w)
    {

    }
    void PRenderer::init()
    {
#ifdef IS_LINUX
        XSetWindowAttributes swa;
        GLint att[] = {
            GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None
        };
        vi = glXChooseVisual(window.getLinuxDisplay(),window.getLinuxScreen(),att);
        cmap = XCreateColormap(window.getLinuxDisplay(),*window.getLinuxWindow(),vi->visual,AllocNone);
        swa.colormap = cmap;
        swa.event_mask = ExposureMask | KeyPressMask;
        // XCreateWindow
        
#endif
    }
}