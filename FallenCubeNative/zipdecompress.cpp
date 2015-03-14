#include "zipdecompress.h"
#include "miniz.cpp"
#include <QDir>

ZipDecompress::ZipDecompress(char *filename, char *folder)
{
    archiveName = filename;
    extractTo = folder;
    mz_zip_archive zip_archive;
    memset(&zip_archive, 0, sizeof(zip_archive));
    mz_zip_reader_init_file(&zip_archive, archiveName, 0);
    if (!QDir(extractTo).exists()) QDir().mkdir(extractTo);
    for (int i = 0; i < (int)mz_zip_reader_get_num_files(&zip_archive); i++)
     {
       mz_zip_archive_file_stat file_stat;
       if (!mz_zip_reader_file_stat(&zip_archive, i, &file_stat))
       {
          mz_zip_reader_end(&zip_archive);
       }
       char folderName[128];
       strcpy(folderName, extractTo);
       strcat(folderName, file_stat.m_filename);
       if (mz_zip_reader_is_file_a_directory(&zip_archive, i)) {
           if (!QDir(folderName).exists()) QDir().mkdir(folderName);
       }
       else {
           mz_zip_reader_extract_file_to_file(&zip_archive, file_stat.m_filename, folderName, 0);
       }

       if (!strcmp(file_stat.m_filename, "directory/"))
       {
         if (!mz_zip_reader_is_file_a_directory(&zip_archive, i))
         {
           mz_zip_reader_end(&zip_archive);
         }
       }
     }
     mz_zip_reader_end(&zip_archive);
}

ZipDecompress::~ZipDecompress()
{

}

