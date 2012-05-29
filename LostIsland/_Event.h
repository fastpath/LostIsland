#pragma once
#include "EventType.h"
class _Event
{
private:
	EventType m_type;
public:
	_Event(EventType type);
	EventType GetType() { return m_type; }
	~_Event(VOID);
};

