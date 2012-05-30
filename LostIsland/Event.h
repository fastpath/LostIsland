#pragma once
#include "EventType.h"
class Event
{
private:
    enum EventType m_type;

public:
    Event(enum EventType type);
    ~Event(VOID);

    enum EventType GetType() { return m_type; }
};

