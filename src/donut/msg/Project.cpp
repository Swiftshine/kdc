#pragma peephole off
#include <donut/msg/Project.hpp>
#include <hel/common/FixedStringIN.hpp>

using msg::Project;

Project::Project(mem::IAllocator& rAllocator, const char* pFilename)
    : mFileLoader()
    , mProjectInfo(nullptr)
{
    mFileLoader.load(hel::common::FixedStringIN<char, 80>::FromFormat("msg/%s.msbp", pFilename).str(),
    rAllocator, false, nullptr);

    mProjectInfo = LMS_InitProject(mFileLoader.data().mStartAddress);
}

Project::~Project() {
    LMS_CloseProject(mProjectInfo);
    mProjectInfo = nullptr;
    mFileLoader.unload();
}

const wchar_t* Project::tagGroupName(u16 arg1) const {
    return LMS_GetTagGroupName(mProjectInfo, arg1);
}

const wchar_t* Project::tagName(u16 arg1, u16 arg2) const {
    return LMS_GetTagName(mProjectInfo, arg1, arg2);
}

const wchar_t* Project::listItemName(u16 arg1, u16 arg2, u16 arg3, u16 arg4) const {
    return LMS_GetTagListItemName(mProjectInfo, arg1, arg2, arg3, arg4);
}
