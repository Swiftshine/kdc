#pragma peephole off
#include <donut/gfx/TexBuffer.hpp>

using gfx::TexBuffer;

//TODO: Do they actually do 0xFFFF or is it some type casting?
TexBuffer::TexBuffer(mem::IAllocator& rAllocator, u16 width, u16 height, GXTexFmt format)
    : mDataBlock(GXGetTexBufferSize(width, height, format, GX_FALSE, 0), 0x20, rAllocator)
    , mWidth(width & 0xFFFF)
    , mHeight(height & 0xFFFF)
    , mFormat(format)
{
    DCInvalidateRange(mDataBlock.block().mData, mDataBlock.block().mSize);
}

TexBuffer::~TexBuffer() {}

u16 TexBuffer::height() const {
    return mHeight;
}

//NOTE: All functions below are code merged into others. Refer to the header for more details

mem::MemBlock TexBuffer::block() const {
    return mDataBlock.block();
}

u16 TexBuffer::width() const {
    return mWidth;
}

GXTexFmt TexBuffer::format() const {
    return mFormat;
}
