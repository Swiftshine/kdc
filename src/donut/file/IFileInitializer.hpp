#ifndef DONUT_FILE_IFILEINITIALIZER_HPP
#define DONUT_FILE_IFILEINITIALIZER_HPP

#include <donut/mem/MemBlock.hpp>

namespace file {

class IFileInitializer {
    public:
    //Guessed
    /* 0x08 */ virtual ~IFileInitializer();
    /* 0x0C */ virtual void virtual_0C(mem::MemBlock& rMemBlock) const;

};

}

#endif
