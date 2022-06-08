#include "src/helper.hpp"
#include <pscanner.hpp>

int main(int argc,char** argv)
{
    const char* filename = "test.txt";
    std::fstream file(filename);
    std::stringstream ss;
    ss << file.rdbuf();
    PScript::PScanner scanner(ss.str());

    scanner.scanTokens();

    return 0;
}