#include "types.h"
#pragma peephole off
#include <donut/file/FileAccessor.hpp>
#include <donut/file/FileLoader.hpp>
#include <donut/file/IFileInitializer.hpp>
#include <donut/app/Application.hpp>

namespace file {
    FileAccessor::FileAccessor(const char* pFilePath, bool arg2)
        : mLoader(nullptr)
    {
        load(pFilePath, nullptr, arg2);
    }

    bool FileAccessor::isLoaded() const {
        bool loaded = false;
        if (mLoader != nullptr && mLoader->isLoaded()) {
            loaded = true;
        }
        return loaded;
    }

    mem::MemBlock FileAccessor::block() const {
        return mLoader->data();
    }

    void FileAccessor::load(const char* pFilePath, const IFileInitializer* pInitializer, bool arg3) {
        FileTree* tree = app::Application::Instance->fileManager().treeRoot();

        FileLoader* file = tree->findFile(pFilePath);
        if (file != nullptr) {
            mLoader = file;
            return;
        }
        file = tree->addFile(pFilePath, pInitializer);
        if (file != nullptr) {
            mLoader = file;
        }
    }
};
