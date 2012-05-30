#include "StdAfx.h"
#include "EventManager.h"

using namespace events;
EventManager::EventManager()
{
}

VOID EventManager::TriggerEvent(CONST EventPtr& e) {
    EventType type = e->VGetType();
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

VOID EventManager::Update(LONG maxMIllis) {
    while(!this->m_queue.empty())
    {
        this->TriggerEvent(this->m_queue.front());
        this->m_queue.pop_front();
    }
}

VOID EventManager::QueueEvent(CONST EventPtr& e) {
    this->m_queue.push_back(e);
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
    std::cout << e->VGetType();
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
