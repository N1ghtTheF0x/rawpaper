#include "renderer.hpp"

namespace Paper
{
    PRenderer &PRenderer::getInstance()
    {
        static PRenderer instance;
        return instance;
    }
    PRenderer::PRenderer()
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
#ifdef IS_WINDOWS
    void PRenderer::setWindowsHRC(HGLRC hrc)
    {
        this->hrc = hrc;
    }
    HGLRC PRenderer::getWindowsHRC()
    {
        return hrc;
    }
#endif
}