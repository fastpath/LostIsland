#pragma once
namespace events {
    class IEvent
    {
    public:
        IEvent(VOID) {};
        ~IEvent(VOID) {};
        virtual EventType VGetType(VOID) CONST = 0;
    };
};


