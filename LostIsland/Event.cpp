#include "StdAfx.h"
#include "Event.h"

using namespace events;
Event::Event(CONST EventType type ) : m_type(type)
{
}
/*
template<class T>
T& Event::GetProperty(PropertyType type) {
    std::hash_map<PropertyType, std::shared_ptr<IProperty>>::iterator it = this->m_properties.find(type);
    std::shared_ptr<Property<T>> p = std::static_pointer_cast<std::shared_ptr<Property<T>>>(it->second);
    return p->GetValue();
}

template<class T>
VOID Event::SetProperty(PropertyType type, std::shared_ptr<T> value) {
    Property<T>* p = new Property<T>;
    p->SetValue(value);
    std::shared_ptr<Property<T>> ptr(p);
    this->m_properties.insert(std::pair<PropertyType, std::shared_ptr<IProperty>>(type, ptr));
} */

Event::~Event(VOID)
{
}
