#if !defined(PAPER_WINDOW)
#define PAPER_WINDOW

#ifdef IS_LINUX
    #include <X11/Xlib.h>
    #include <X11/Xatom.h>
    #include <X11/extensions/Xrender.h>
    #include <X11/Xutil.h>
    #include <X11/Xos.h>
#endif
#ifdef IS_WINDOWS
    #include "pwin.hpp"
#endif

namespace Paper
{
    class PWindow
    {
    private:
        PWindow();

        int argc;
        char** argv;

        void windowLoop();
        void draw();
        void handleKeyboardInput(unsigned int keyCode);
        void handleMouseInput(int x,int y,unsigned int buttons);
    public:
        static PWindow &getInstance();
        void init(int argc,char** argv);
        void create(int x,int y,unsigned int width,unsigned int height);
        void setName(const char* title);
        void close();
        void show();
        void hide();
        void emitKeyboardInput(unsigned int keyCode);
#ifdef IS_LINUX
    private:
        Display *dis = XOpenDisplay(NULL);
        int screen = 0;
        Window win;
        GC gc;
    public:
        Display* getLinuxDisplay();
        int getLinuxScreen();
        Window* getLinuxWindow();
        GC* getLinuxGC();
#endif
#ifdef IS_WINDOWS
    private:
        HINSTANCE hInstance;
        LPTSTR lpCmdLine;
        int nCmdShow;

        HWND hwnd;
        HDC hdc;
    public:
        void setWindowsHDC(HDC hdc);
        HDC getWindowsHDC();

        HWND getWindowsHWND();
#endif
    };
}

#endif // PAPER_WINDOW
