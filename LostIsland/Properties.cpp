#include "StdAfx.h"
#include "Properties.h"

Property<INT> Properties::ACTOR_ID;

Properties::Properties(VOID)
{
}

template<class T>
T Properties::GetValue(Property<T> prop) {

}

template<class T>
VOID Properties::SetProperty(Property<T> prop, shared_ptr<T> value) {
    this->m_properties.insert((VOID*)&prop, (VOID*)&value);
}


Properties::~Properties(VOID)
{
}
