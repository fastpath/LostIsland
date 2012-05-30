#pragma once
#include "IEvent.h"
namespace events {
    class CreateActorEvent : public IEvent
    {
    public:
        static CONST EventType TYPE;
        std::string _mActorSource;
        CreateActorEvent(VOID){}
        ~CreateActorEvent(VOID){}
        EventType VGetType(VOID) CONST { return CreateActorEvent::TYPE; }
    };
};

