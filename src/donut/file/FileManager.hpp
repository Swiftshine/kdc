#ifndef DONUT_FILE_FILEMANAGER_HPP
#define DONUT_FILE_FILEMANAGER_HPP

#include <donut/file/FileTree.hpp>

namespace file {

class FileManager {
public:
    FileManager();
    ~FileManager();

    void clearFilesIfEnable();

    //NOTE: Merged into DefaultSwitchThreadCallback
    FileTree* treeRoot() const;
    void disableClearInc();
    void disableClearDec();

private:
    /* 0x00 */ FileTree mTreeRoot;
    /* 0x40 */ s32 m_40;
};

}

#endif
