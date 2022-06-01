#if !defined(WOODFS_HEADER)
#define WOODFS_HEADER

struct WoodFS
{
    struct Header
    {
        char id[6]; // "WOODFS"
        unsigned long int fileCount;
    };
    struct File
    {
        unsigned long typeLength;
        char *type;
        unsigned long int fileSize;
        char *data;
    };
    Header header;
    File *files;
};

WoodFS* readFile(const char* path);

#endif