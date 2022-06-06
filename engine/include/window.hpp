#if !defined(PAPER_WINDOW)
#define PAPER_WINDOW

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
