#ifndef DONUT_APP_MESSAGE_HPP
#define DONUT_APP_MESSAGE_HPP

namespace app {

#define MESSAGE_GET_TEXT_DECL(name) \
    static const char* Text##name(const char* pText)

#define MESSAGE_GET_UNSAFED_TEXT_DECL(name) \
    static const char* UnsafedText##name(const char* pText)

class Message {
public:
    MESSAGE_GET_TEXT_DECL(Name);
    MESSAGE_GET_TEXT_DECL(LvMap);
    MESSAGE_GET_TEXT_DECL(Ship);
    MESSAGE_GET_TEXT_DECL(Step);
    MESSAGE_GET_TEXT_DECL(Challenge);
    MESSAGE_GET_TEXT_DECL(ChallengeTitle);
    MESSAGE_GET_TEXT_DECL(ChallengeFileSelect);
    MESSAGE_GET_TEXT_DECL(Pause);
    MESSAGE_GET_TEXT_DECL(Common);
    MESSAGE_GET_TEXT_DECL(Option);
    MESSAGE_GET_TEXT_DECL(History);
    MESSAGE_GET_TEXT_DECL(Product);
    MESSAGE_GET_TEXT_DECL(News);
    MESSAGE_GET_TEXT_DECL(PlayMovie);
    MESSAGE_GET_TEXT_DECL(Resident);
    MESSAGE_GET_TEXT_DECL(GrandMenu);
    MESSAGE_GET_TEXT_DECL(GrandTitle);
    MESSAGE_GET_TEXT_DECL(StaffCredit);
    MESSAGE_GET_UNSAFED_TEXT_DECL(Pause);
    MESSAGE_GET_UNSAFED_TEXT_DECL(Challenge);
    MESSAGE_GET_UNSAFED_TEXT_DECL(StaffCredit);
};

}

#endif
