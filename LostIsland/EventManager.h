#pragma once
#include "Event.h"
namespace events {
    #define MAX_TIME INFINITE
    typedef std::shared_ptr<Event> EventPtr;
    typedef fastdelegate::FastDelegate1<EventPtr> EventListenerDelegate;
    typedef std::hash_map<EventType, std::list<EventListenerDelegate>*>::const_iterator ListenerMapIter;
    typedef std::list<EventListenerDelegate>::iterator DelegateIter;
    typedef std::list<EventListenerDelegate>::const_iterator ListenerListIter;
    typedef std::list<EventPtr>::const_iterator QueueIter;
    class EventManager
    {
    private:
        static std::shared_ptr<EventManager> g_global;

        std::list< std::list<EventListenerDelegate>* > m_listenerList;
        std::list<EventPtr> m_queue[2];
        std::hash_map<EventType, std::list<EventListenerDelegate>*> m_listenerMap;
        INT m_currentQueue;

    public:
        static std::shared_ptr<EventManager> GetGlobal() { return g_global; }
        static VOID SetGlobal(CONST std::shared_ptr<EventManager> global) { EventManager::g_global = global; }

        EventManager(VOID);
        ~EventManager(VOID);

        VOID AddListener(CONST EventListenerDelegate& listener, EventType type);
        VOID RemoveListener(CONST EventListenerDelegate& listener, EventType type);
        VOID TriggerEvent(CONST EventPtr& e);
        VOID QueueEvent(CONST EventPtr& e);
        INT Update(LONG maxMillis);
        VOID MemberTest(EventPtr e);
    };
};


