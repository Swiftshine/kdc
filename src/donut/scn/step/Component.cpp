#include "scn/step/Component.hpp"
#include "mem/ExplicitScopedPtr.hpp"
#include "scn/step/debug/GeneralDrawer.hpp"

using namespace scn::step;
using mem::ExplicitScopedPtrUtil::CheckPointerIsValid;

debug::GeneralDrawer* Component::debugGeneralDrawer() {
    CheckPointerIsValid(mDebugGeneralDrawer);
    return mDebugGeneralDrawer;
}

debug::ObjInfoRepos* Component::debugObjInfoRepos() {
    CheckPointerIsValid(mDebugObjInfoRepos);
    return mDebugObjInfoRepos;
}
