#pragma peephole off
#include <donut/file/FileClearDisableScope.hpp>
#include <donut/app/Application.hpp>

namespace file {
    FileClearDisableScope::FileClearDisableScope() {
        app::Application::Instance->fileManager().disableClearInc();
    }

    FileClearDisableScope::~FileClearDisableScope() {
        app::Application::Instance->fileManager().disableClearDec();
    }
}
