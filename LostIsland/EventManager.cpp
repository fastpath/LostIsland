#include "StdAfx.h"
#include "EventManager.h"


EventManager::EventManager()
{
}

VOID EventManager::TriggerEvent(CONST EventPtr& e) {
    enum EventType type = e->GetType();
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

VOID EventManager::AddListener(CONST EventListenerDelegate& listener, enum EventType type) {
    ListenerMapIter it;
    it = this->m_listenerMap.find(type);
    if(it == m_listenerMap.end()) 
    {
        list<EventListenerDelegate>* l = new list<EventListenerDelegate>;
        l->push_back(listener);
        this->m_listenerMap.insert(std::pair<enum EventType, list<EventListenerDelegate>*> (type, l));
    } else 
    {
        it->second->push_back(listener);
    }
}

VOID EventManager::RemoveListener(CONST EventListenerDelegate& listener) {
    //TODO
}

VOID EventManager::MemberTest(EventPtr e) {
    std::cout << "MemberTest";
    std::cout << e->GetType();
    std::cout << "\n";
}

EventManager::~EventManager(void)
{
}
