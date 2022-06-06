#if !defined(PAPER_WINDOWS)
#define PAPER_WINDOWS

#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

namespace Paper
{
    #define PWINDOWS_APPNAME "RawPaper Engine"
    struct PWindows
    {
        HINSTANCE hInstance;
        LPTSTR lpCmdLine;
        int nCmdShow;
        HWND hwnd;
        HDC hdc;
        HGLRC hrc;
    } windows;
}

#endif