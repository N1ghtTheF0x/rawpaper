#include <window.hpp>

int main(int argc, char** argv)
{
    Paper::PWindow &window = Paper::PWindow::getInstance();
    window.init(argc,argv);
}
