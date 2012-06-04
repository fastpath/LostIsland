#include "StdAfx.h"
#include "EventManager.h"

using namespace events;
EventManager::EventManager() : m_currentQueue(0)
{
}

VOID EventManager::TriggerEvent(CONST EventPtr& e) {
    EventType type = e->GetType();
    ListenerMapIter start = this->m_listenerMap.find(type);
    if(start != this->m_listenerMap.end()) 
    {
        list<EventListenerDelegate>* deles = start->second;
        DelegateIter it = deles->begin();
        for(DelegateIter startD = deles->begin(); startD != deles->end(); ++startD) 
        {
            (*startD)(e);
        }
    }
}

INT EventManager::Update(LONG maxMillis) {
    int oldQueue = this->m_currentQueue;
    this->m_currentQueue = (this->m_currentQueue + 1) % 2;
    int max = GetTickCount() + maxMillis;
    this->m_queue[this->m_currentQueue].clear();
    while(!this->m_queue[oldQueue].empty())
    {
        this->TriggerEvent(this->m_queue[oldQueue].front());
        this->m_queue[oldQueue].pop_front();
        if((maxMillis != MAX_TIME) && (GetTickCount() > max))
        {
            while(!this->m_queue[oldQueue].empty())
            {
                EventPtr e = this->m_queue[oldQueue].front();
                this->m_queue[oldQueue].pop_front();
                this->m_queue[m_currentQueue].push_front(e);
            }
            break;
        }
    }
    return this->m_queue[m_currentQueue].size();
}

VOID EventManager::QueueEvent(CONST EventPtr& e) {
    this->m_queue[m_currentQueue].push_back(e);
}

VOID EventManager::AddListener(CONST EventListenerDelegate& listener, EventType type) {
    ListenerMapIter it;
    it = this->m_listenerMap.find(type);
    if(it == m_listenerMap.end()) 
    {
        std::list<EventListenerDelegate>* l = new std::list<EventListenerDelegate>;
        this->m_listenerList.push_back(l);
        l->push_back(listener);
        this->m_listenerMap.insert(std::pair<EventType, std::list<EventListenerDelegate>*> (type, l));
    } else 
    {
        it->second->push_back(listener);
    }
}

VOID EventManager::RemoveListener(CONST EventListenerDelegate& listener, EventType type) {
    ListenerMapIter it = this->m_listenerMap.find(type);
    if(it != this->m_listenerMap.end())
    {
        for(ListenerListIter it2 = it->second->begin(); it2 != it->second->end(); ++it2) 
        {
            if((*it2) == listener) 
            {
                it->second->erase(it2);
            }
        }
    }
}

VOID EventManager::MemberTest(EventPtr e) {
    std::cout << "MemberTest";
    std::cout << e->GetType();
    std::cout << "\n";
}

EventManager::~EventManager(void)
{
    while(!this->m_listenerList.empty()) 
    {
        std::list<EventListenerDelegate>* l = this->m_listenerList.front();
        this->m_listenerList.pop_front();
        SAFE_DELETE(l);
    }
}
