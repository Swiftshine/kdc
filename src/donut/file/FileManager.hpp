#ifndef DONUT_FILE_FILEMANAGER_HPP
#define DONUT_FILE_FILEMANAGER_HPP

#include <types.h>

namespace file {

class FileManager {
public:
    FileManager();
    ~FileManager();
private:
    STRUCT_FILL(0x44);
};

}

#endif
