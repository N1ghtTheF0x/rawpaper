#include "woodfs.hpp"

#include <fstream>

bool checkHeader(char id[6])
{
    return id[0] == 'W' &&
           id[1] == 'O' &&
           id[2] == 'O' &&
           id[3] == 'D' &&
           id[4] == 'F' &&
           id[5] == 'S';
}

WoodFS* readFile(const char* path)
{
    std::ifstream file(path,std::ios::binary);
    if(!file.is_open()) throw "[woodfs] Couldn't open file!";
    WoodFS *woodfs;
    file.read(reinterpret_cast<char*>(&woodfs->header),sizeof WoodFS::Header);
    if(!checkHeader(woodfs->header.id)) throw "[woodfs] Header ID is invalid!";
    
}