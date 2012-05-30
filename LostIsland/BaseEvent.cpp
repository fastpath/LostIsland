#include "StdAfx.h"
#include "BaseEvent.h"

using namespace events;
CONST EventType BaseEvent::TYPE = EventType(0x1afe8911);
BaseEvent::BaseEvent(EventType type ) : m_type(type)
{
}

BaseEvent::BaseEvent(VOID) : m_type(TYPE)
{
}

BaseEvent::~BaseEvent(VOID)
{
}
