#include "app/Application.hpp"
#include "msg/Manager.hpp"
#include "app/Message.hpp"

using namespace app;

#define MESSAGE_GET_TEXT_IMPL(name, category) \
    const char* Message::Text##name(const char* pText) { \
        return Application::Instance->messageManager().text(category, pText); \
    }

#define MESSAGE_GET_UNSAFED_TEXT_IMPL(name, category) \
    const char* Message::UnsafedText##name(const char* pText) { \
        return Application::Instance->messageManager().text(category, pText); \
    }

MESSAGE_GET_TEXT_IMPL(Name, msg::Manager::CAT_NAME)
MESSAGE_GET_TEXT_IMPL(LvMap, msg::Manager::CAT_LVMAP)
MESSAGE_GET_TEXT_IMPL(Ship, msg::Manager::CAT_SHIP)
MESSAGE_GET_TEXT_IMPL(Step, msg::Manager::CAT_STEP)
MESSAGE_GET_TEXT_IMPL(Challenge, msg::Manager::CAT_CHALLENGE)
MESSAGE_GET_TEXT_IMPL(ChallengeTitle, msg::Manager::CAT_CHALLENGETITLE)
MESSAGE_GET_TEXT_IMPL(ChallengeFileSelect, msg::Manager::CAT_CHALLENGEFILESELECT)
MESSAGE_GET_TEXT_IMPL(Pause, msg::Manager::CAT_PAUSE)
MESSAGE_GET_TEXT_IMPL(Common, msg::Manager::CAT_COMMON)
MESSAGE_GET_TEXT_IMPL(Option, msg::Manager::CAT_OPTION)
MESSAGE_GET_TEXT_IMPL(History, msg::Manager::CAT_HISTORY)
MESSAGE_GET_TEXT_IMPL(Product, msg::Manager::CAT_PRODUCT)
MESSAGE_GET_TEXT_IMPL(News, msg::Manager::CAT_NEWS)
MESSAGE_GET_TEXT_IMPL(PlayMovie, msg::Manager::CAT_PLAYMOVIE)
MESSAGE_GET_TEXT_IMPL(Resident, msg::Manager::CAT_RESIDENT)
MESSAGE_GET_TEXT_IMPL(GrandMenu, msg::Manager::CAT_GRANDMENU)
MESSAGE_GET_TEXT_IMPL(GrandTitle, msg::Manager::CAT_GRANDTITLE)
MESSAGE_GET_TEXT_IMPL(StaffCredit, msg::Manager::CAT_STAFFCREDIT)
MESSAGE_GET_UNSAFED_TEXT_IMPL(Pause, msg::Manager::CAT_PAUSE)
MESSAGE_GET_UNSAFED_TEXT_IMPL(Challenge, msg::Manager::CAT_CHALLENGE)
MESSAGE_GET_UNSAFED_TEXT_IMPL(StaffCredit, msg::Manager::CAT_STAFFCREDIT)
