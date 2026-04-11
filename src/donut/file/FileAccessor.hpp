#ifndef DONUT_FILE_FILE_ACCESSOR_HPP
#define DONUT_FILE_FILE_ACCESSOR_HPP

#include <donut/mem/MemBlock.hpp>

namespace file {
class FileLoader;
class IFileInitializer;

class FileAccessor {
public:
    FileAccessor() {}
    FileAccessor(const char*, bool);

    //NOTE: Merged into hel::common::ExplicitSingleton<app::Reset>::~ExplicitSingleton()
    ~FileAccessor();

    mem::MemBlock block() const;
    bool isLoaded() const;
    void load(const char* pFilePath, const IFileInitializer* pInitializer, bool arg3);

private:
    /* 0x0 */ FileLoader* mLoader;
};

}

#endif
