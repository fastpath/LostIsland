#pragma once
#include "EventType.h"
class Event
{
private:
	EventType m_type;
public:
	Event(EventType type);
	EventType GetType() { return m_type; }
	~Event(VOID);
};

