#ifndef DONUT_FILE_FILETREE_HPP
#define DONUT_FILE_FILETREE_HPP

#include <types.h>

namespace file {
    class IFileInitializer;
    class FileLoader;

    class FileTree {
    public:
        FileTree();
        ~FileTree();

        FileLoader* findFile(const char* pFilePath) const;
        FileLoader* addFile(const char* pFilePath, const IFileInitializer* pInitializer);
    private:
        STRUCT_FILL(0x40);
    };

}

#endif
