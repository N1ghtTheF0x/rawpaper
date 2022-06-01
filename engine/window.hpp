#if !defined(PAPER_WINDOW)
#define PAPER_WINDOW

#ifdef IS_LINUX
    #include <X11/Xlib.h>
    #include <X11/Xatom.h>
    #include <X11/extensions/Xrender.h>
    #include <X11/Xutil.h>
    #include <X11/Xos.h>
#endif

namespace Paper
{
    class PWindow
    {
    private:
        int argc;
        char** argv;

        void windowLoop();
        void redraw();
        void handleKeyboardInput(unsigned int keyCode);
        void handleMouseInput(int x,int y,unsigned int buttons);
    public:
        PWindow(int argc,char** argv);
        void create(int x,int y,unsigned int width,unsigned int height);
        void setName(const char* title);
        void close();
    
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
    };
}

#endif // PAPER_WINDOW
