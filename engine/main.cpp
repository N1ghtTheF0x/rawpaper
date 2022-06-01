#include "window.hpp"

int main(int argc, char** argv)
{
    Paper::PWindow window(argc,argv);
    window.setName("Title");
    window.create(0,0,320,200);
}
