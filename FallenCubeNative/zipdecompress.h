#ifndef ZIPDECOMPRESS_H
#define ZIPDECOMPRESS_H

class ZipDecompress
{
public:
    ZipDecompress(char const *filename, char const *destname);
    ~ZipDecompress();
private:
    char const * archiveName;
    char const * extractTo;
    char data[2048];
    char uSize;
};

#endif // ZIPDECOMPRESS_H
