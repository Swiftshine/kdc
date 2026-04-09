#ifndef DONUT_PRELOAD_PRELOADMANAGER_HPP
#define DONUT_PRELOAD_PRELOADMANAGER_HPP

#include <donut/mem/MemBlock.hpp>

namespace preload {

class PreLoadManager {
public:
    class FindResult {
    public:
        FindResult();

        //NOTE: Merged into effect::detail::GenContext::dataType() const
        bool isValid() const;
        //NOTE: Merged into mem::DataBlock::block() const
        mem::MemBlock block() const;
        /* 0x0 */ bool m_0;
        /* 0x4 */ mem::MemBlock mBlock;
    };

    PreLoadManager();
    ~PreLoadManager();

    void waitToFinishLoading();
    FindResult find(const char* pFilePath);

private:
    STRUCT_FILL(0xBB64);
};

}

#endif
