#if !defined(WOODFS_HEADER)
#define WOODFS_HEADER

namespace WoodFS
{
    struct Header
    {
        char id[6]; // "WOODFS"
        unsigned long int fileCount;
    };
    struct DataFile
    {
        unsigned long typeLength;
        char *type;
        unsigned long int fileSize;
        char *data;
    };
    struct File
    {
        Header header;
        DataFile *files;
    };
    
};

WoodFS::File* readFile(const char* path);

#endif