#ifndef DONUT_FILE_FILE_ACCESSOR_HPP
#define DONUT_FILE_FILE_ACCESSOR_HPP

#include <donut/mem/MemBlock.hpp>
#include <types.h>

namespace mem {
    class IAllocator;
}

namespace file {

class IFileInitializer;

class FileLoader {
public:
    FileLoader();
    ~FileLoader();

    void load(const char* pFilename, mem::IAllocator& rAllocator, bool arg3, const IFileInitializer* fileInitializer);
    void unload();

    mem::MemBlock data() const;

private:
    STRUCT_FILL(0x68);
};

}

#endif
