#ifndef DONUT_STORAGE_STORAGEMANAGER_HPP
#define DONUT_STORAGE_STORAGEMANAGER_HPP

#include <types.h>

namespace storage {

class StorageManager {
public:
    StorageManager();
    ~StorageManager();
private:
    STRUCT_FILL(0x28);
};

}

#endif
