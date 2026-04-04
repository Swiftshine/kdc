#ifndef DONUT_MSG_PROJECT_HPP
#define DONUT_MSG_PROJECT_HPP

#include <donut/file/FileLoader.hpp>
#include <libms/projfile.h>

namespace msg {
    class Project {
    public:
        Project(mem::IAllocator& rAllocator, const char* pFilename);
        ~Project();

        const wchar_t* tagGroupName(u16 arg1) const;
        const wchar_t* tagName(u16 arg1, u16 arg2) const;
        const wchar_t* listItemName(u16 arg1, u16 arg2, u16 arg3, u16 arg4) const;

    private:
        /* 0x00 */ file::FileLoader mFileLoader;
        /* 0x68 */ struct ProjectInfo* mProjectInfo;
    };
}

#endif
