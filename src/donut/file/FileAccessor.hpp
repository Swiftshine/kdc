#ifndef DONUT_FILE_FILE_ACCESSOR_HPP
#define DONUT_FILE_FILE_ACCESSOR_HPP

#include <types.h>

namespace file {

class FileAccessor {
public:
    FileAccessor();
    FileAccessor(const char*, bool);
    ~FileAccessor();
    //TODO: Double check this
    void* block() const;

private:
    STRUCT_FILL(0x4);
};

}

#endif
