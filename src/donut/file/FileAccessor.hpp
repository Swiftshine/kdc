#ifndef DONUT_FILE_FILE_ACCESSOR_HPP
#define DONUT_FILE_FILE_ACCESSOR_HPP

#include <types.h>
#include <donut/mem/MemBlock.hpp>

namespace file {

class FileAccessor {
public:
    FileAccessor();
    FileAccessor(const char*, bool);
    ~FileAccessor();
    //TODO: Double check this
    mem::MemBlock block() const;

private:
    STRUCT_FILL(0x4);
};

}

#endif
