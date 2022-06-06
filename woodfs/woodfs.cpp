#include "woodfs.hpp"

#include <putils.hpp>
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

WoodFS::File* readFile(const char* path)
{
    std::ifstream file(path,std::ios::binary);
    if(!file.is_open()) THROW_PE("woodfs","Couldn't open file!");
    WoodFS::File *woodfs = new WoodFS::File();
    file.read(reinterpret_cast<char*>(&woodfs->header),sizeof(WoodFS::Header));
    if(!checkHeader(woodfs->header.id)) THROW_PE("woodfs","Header ID is invalid!");
    return woodfs;
}