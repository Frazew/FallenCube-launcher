#ifndef ZIPDECOMPRESS_H
#define ZIPDECOMPRESS_H

class ZipDecompress
{
public:
    ZipDecompress(char *filename, char *destname);
    ~ZipDecompress();
private:
    char* archiveName;
    char* extractTo;
    char data[2048];
    char uSize;
};

#endif // ZIPDECOMPRESS_H
