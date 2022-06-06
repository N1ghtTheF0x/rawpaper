#include <woodfs.hpp>
#include <iostream>

int main(int argc,char** argv)
{
    if(argc != 2)
    {
        std::cout << "Usage:" << std::endl << "cwoodfs <file>" << std::endl;
        return 64;
    }
    if(argc == 2)
    {
        const char* filename = argv[1];
    }
    return 0;
}