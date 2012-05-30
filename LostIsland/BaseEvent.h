#pragma once
#include "IEvent.h"
namespace events {
    class BaseEvent : public IEvent
    {
    public:
        static CONST EventType TYPE;

        std::string m_string;
        INT m_int;
        EventType m_type;
        FLOAT m_float;
        DOUBLE m_double;
        LONG m_long;
        std::shared_ptr<VOID> m_data;

        BaseEvent(EventType type);
        BaseEvent(VOID);
        ~BaseEvent(VOID);

        EventType VGetType(VOID) CONST { return m_type; }
    };
};

