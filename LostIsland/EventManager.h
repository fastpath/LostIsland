#pragma once
#include "stdafx.h"
#include "_Event.h"
typedef shared_ptr<_Event> Event;
typedef fastdelegate::FastDelegate1<Event> EventListenerDelegate;
typedef hash_map<EventType, list<EventListenerDelegate>*>::const_iterator ListenerMapIter;
typedef list<EventListenerDelegate>::iterator DelegateIter;
typedef list<Event>::iterator QueueIter;
class EventManager
{
private:
	//list<EventListenerDelegate*> m_listener;
	list<Event> m_queue;
	hash_map<EventType, list<EventListenerDelegate>*> m_listenerMap;
	static shared_ptr<EventManager> g_global;
public:
	EventManager(VOID);
	~EventManager(VOID);

	VOID AddListener(CONST EventListenerDelegate& listener, EventType type);
	VOID TriggerEvent(CONST Event& e);
	VOID QueueEvent(CONST Event& e);
	VOID Update(LONG maxMillis);
	static shared_ptr<EventManager> GetGlobal() { return g_global; }
	static VOID SetGlobal(CONST shared_ptr<EventManager> global) { EventManager::g_global = global; }
};

