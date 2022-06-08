#if !defined(PAPER_WINDOW)
#define PAPER_WINDOW

#define PAPER_APPNAME "RawPaper Engine"
#define PAPER_WINDOW_WIDTH 640
#define PAPER_WINDOW_HEIGHT 480

namespace Paper
{
    class PWindow
    {
    private:
        PWindow();

        int argc;
        char** argv;
        void windowLoop();
    public:
        static PWindow &getInstance() {static PWindow instance;return instance;};
        void init(int argc,char** argv);
        void onKeyInput(unsigned int keycode);
    };
}

#endif // PAPER_WINDOW
