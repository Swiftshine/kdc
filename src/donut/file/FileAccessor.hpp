#ifndef DONUT_FILE_FILE_ACCESSOR_HPP
#define DONUT_FILE_FILE_ACCESSOR_HPP

#include <types.h>

namespace file {

class FileAccessor {
public:
    FileAccessor();
    ~FileAccessor();
private:
    STRUCT_FILL(0x4);
};

}

#endif
