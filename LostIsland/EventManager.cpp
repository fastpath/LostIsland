#include "StdAfx.h"
#include "EventManager.h"


EventManager::EventManager()
{
}

VOID EventManager::TriggerEvent(CONST Event& e) {
	EventType type = e->GetType();
	for(ListenerMapIter start = this->m_listenerMap.find(type); start != this->m_listenerMap.end(); ++start) {
		list<EventListenerDelegate>* deles = start->second;
		DelegateIter it = deles->begin();
		for(DelegateIter startD = deles->begin(); startD != deles->end(); ++startD) {
			(*startD)(e);
		}
	}
}

VOID EventManager::Update(LONG maxMIllis) {
	for(QueueIter it = this->m_queue.begin(); it != this->m_queue.end(); ++it) {
		this->TriggerEvent(*it);
	}
	this->m_queue.clear();
}

VOID EventManager::QueueEvent(CONST Event& e) {
	this->m_queue.push_back(e);
}

VOID EventManager::AddListener(CONST EventListenerDelegate& listener, EventType type) {
	ListenerMapIter it;
	it = this->m_listenerMap.find(type);
	if(it != m_listenerMap.end()) {
		list<EventListenerDelegate>* l = new list<EventListenerDelegate>;
		l->push_back(listener);
		this->m_listenerMap.insert(std::pair<EventType, list<EventListenerDelegate>*> (type, l));
	} else {
		it->second->push_back(listener);
	}
}

EventManager::~EventManager(void)
{
}
