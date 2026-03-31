#pragma peephole off
#include <donut/gfx/GXFifoProtectCanceler.hpp>
#include <donut/gfx/GXFifoMemoryManager.hpp>

using gfx::GXFifoProtectCanceler;
using gfx::GXFifoMemoryManager;

GXFifoProtectCanceler::GXFifoProtectCanceler(GXFifoMemoryManager& rManager)
    : mManager(&rManager)
{
    mManager->mutex()->lock();
    mManager->setWriteEnable();
}

GXFifoProtectCanceler::~GXFifoProtectCanceler() {
    mManager->setWriteEnable();
    mManager->mutex()->unlock();
}
