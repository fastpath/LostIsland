#pragma once
#include "stdafx.h"
#include "Event.h"
typedef shared_ptr<Event> EventPtr;
typedef fastdelegate::FastDelegate1<EventPtr> EventListenerDelegate;
typedef hash_map<enum EventType, list<EventListenerDelegate>*>::const_iterator ListenerMapIter;
typedef list<EventListenerDelegate>::iterator DelegateIter;
typedef list<EventPtr>::iterator QueueIter;
class EventManager
{
private:
    static shared_ptr<EventManager> g_global;

    //list<EventListenerDelegate*> m_listener;
    list<EventPtr> m_queue;
    hash_map<enum EventType, list<EventListenerDelegate>*> m_listenerMap;

public:
    static shared_ptr<EventManager> GetGlobal() { return g_global; }
    static VOID SetGlobal(CONST shared_ptr<EventManager> global) { EventManager::g_global = global; }

    EventManager(VOID);
    ~EventManager(VOID);

    VOID AddListener(CONST EventListenerDelegate& listener, enum EventType type);
    VOID RemoveListener(CONST EventListenerDelegate& listener);
    VOID TriggerEvent(CONST EventPtr& e);
    VOID QueueEvent(CONST EventPtr& e);
    VOID Update(LONG maxMillis);
    VOID MemberTest(EventPtr e);
};

