#pragma peephole off
#include <donut/file/FileLoader.hpp>
#include <donut/file/Utility.hpp>
#include <donut/app/Application.hpp>
#include <donut/mem/Memory.hpp>
#include <string.h>
#include <revolution/OS.h>
#include <donut/file/IFileInitializer.hpp>

namespace file {
    FileLoader::FileLoader()
        : mem::AllocatorHandle()
        , m_4(0)
        , m_8()
        , mPathRef()
        , m_5C(mem::MemBlock::EmptyBlock())
        , m_64(0)
    { }

    FileLoader::~FileLoader() {
        if (isValid()) {
            unload();
        }
    }

    void FileLoader::load(const char* pFilename, mem::IAllocator& rAllocator, bool arg3, const IFileInitializer* pFileInitializer) {
        loadIN(pFilename, rAllocator, nullptr, arg3, pFileInitializer, nullptr);
    }

    void FileLoader::load(const char* pFilename, mem::HeapCompaction& rCompaction, bool arg3, const IFileInitializer* pFileInitializer) {
        loadIN(pFilename, rCompaction.m_4,& rCompaction, arg3, pFileInitializer, nullptr);
    }

    void FileLoader::load(const mem::MemBlock& rMemBlock, const char* pFilename, mem::IAllocator& rAllocator, const IFileInitializer* pFileInitializer) {
        loadIN(pFilename, rAllocator,nullptr, false, pFileInitializer, &rMemBlock);
    }

    //https://decomp.me/scratch/rRMjE
    void FileLoader::unload() {
        if (isValid()) {
            if (data().startAddress() != nullptr) {
                obj()->allocatorFree(data().startAddress());
            }
            m_5C = mem::MemBlock::EmptyBlock();
            mPathRef = hel::common::FixedString<80>();
            m_8 = mem::HeapCompactionNodeHandle();
            m_4 = 0;
        }

    }

    bool FileLoader::isLoaded() const {
        return isValid();
    }

    mem::MemBlock FileLoader::data() const {
        if (m_8.isValid()) {
            u32 size = m_5C.mSize;
            return mem::MemBlock(m_8.block().startAddress(), size);
        }
        return m_5C;
    }

    u32 FileLoader::latestUpdateDate() const {
        return m_64;
    }

    //https://decomp.me/scratch/Ad1gb
    void FileLoader::loadIN(const char* pFilename, mem::IAllocator& rAllocator, mem::HeapCompaction* pCompaction, bool arg3,
        const IFileInitializer* pFileInitializer, const mem::MemBlock* pMemBlock) {
            bool isMemBlockhere =  pMemBlock != nullptr;
            if (isMemBlockhere  || Utility::IsExistFileOnUsbOrDvd(pFilename)) {
                mAllocator = mem::AllocatorHandle(rAllocator).mAllocator;
                //*this = handle;
                if (pCompaction) {
                    m_4 = pCompaction;
                }
                mPathRef = hel::common::FixedString<80>(pFilename);
                m_64 = Utility::LatestUpdateDateOnUSB(pFilename, true);
                preload::PreLoadManager::FindResult findResult;

                if (!isMemBlockhere) {
                    if (app::Application::Instance != nullptr) {
                        findResult = app::Application::Instance->preLoadManager().find(pFilename);
                        if (!findResult.isValid()) {
                            Utility::IsFileLoadWarningEnable();
                        }
                    }
                }
                if (isMemBlockhere) {
                    m_5C = Utility::UncompressedFile(*pMemBlock, rAllocator);
                } else {
                    u32 fileNameLength =  strlen(pFilename);

                    bool val;
                    if (fileNameLength < 4 && !strcmp(&pFilename[fileNameLength - 4], ".cmp")) {
                        val = true;
                    } else {
                        val = false;
                    }
                    if (val) {
                        if (findResult.isValid()) {
                            m_5C = Utility::UncompressedFile(findResult.block(), rAllocator);
                        } else {
                            mem::IAllocator& tailAllocator = mem::Memory::Instance->sceneHeap().allocFromTailAllocator();
                            mem::MemBlock local_58 = Utility::LoadFromUsbOrDvd(pFilename, tailAllocator);
                            m_5C = Utility::UncompressedFile(local_58, rAllocator);
                            mAllocator->allocatorFree(&local_58);
                        }
                    }
                    if (findResult.isValid()) {
                        mem::MemBlock local_6C(findResult.block());
                        m_5C = mem::MemBlock(rAllocator.allocatorAlloc(local_6C.mSize, 0x20), local_6C.mSize);
                        memcpy(m_5C.mStartAddress, local_6C.mStartAddress, local_6C.mSize);
                        DCStoreRangeNoSync(m_5C.mStartAddress, m_5C.mSize);
                    } else {
                        m_5C = Utility::LoadFromUsbOrDvd(pFilename, rAllocator);
                    }
                }
                if (pFileInitializer != nullptr) {
                    pFileInitializer->virtual_0C(m_5C);
                }
                if (m_4 != nullptr) {
                    m_8 = m_4->search(m_5C.mStartAddress);
                }
            }
    }
};
