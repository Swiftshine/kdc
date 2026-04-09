#ifndef DONUT_FILE_FILE_ACCESSOR_HPP
#define DONUT_FILE_FILE_ACCESSOR_HPP

#include <donut/mem/HeapCompactionNodeHandle.hpp>
#include <donut/mem/MemBlock.hpp>
#include <donut/mem/AllocatorHandle.hpp>
#include <hel/common/FixedString.hpp>
#include <donut/mem/HeapCompaction.hpp>

namespace file {

class IFileInitializer;

class FileLoader : public mem::AllocatorHandle  {
public:
    FileLoader();
    ~FileLoader();

    void load(const char* pFilename, mem::IAllocator& rAllocator, bool arg3, const IFileInitializer* pFileInitializer);
    void load(const char* pFilename, mem::HeapCompaction& rCompaction, bool arg3, const IFileInitializer* pFileInitializer);
    void load(const mem::MemBlock& rMemBlock, const char* pFilename, mem::IAllocator& rAllocator, const IFileInitializer* pFileInitializer);
    void loadIN(const char* pFilename, mem::IAllocator& rAllocator, mem::HeapCompaction* pCompaction, bool arg3,
        const IFileInitializer* pFileInitializer, const mem::MemBlock* pMemBlock);
    void unload();

    mem::MemBlock data() const;
    bool isLoaded() const;
    u32 latestUpdateDate() const;
    //NOTE: is merged into app::RomFontWrapper::font()
    hel::common::FixedString<80> pathRef() const;

private:
    /* 0x04 */ mem::HeapCompaction* m_4;
    /* 0x08 */ mem::HeapCompactionNodeHandle m_8;
    /* 0x0C */ hel::common::FixedString<80> mPathRef;
    /* 0x5C */ mem::MemBlock m_5C;
    /* 0x64 */ u32 m_64;
};

}

#endif
