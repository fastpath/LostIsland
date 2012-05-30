#include "StdAfx.h"
#include "Property.h"

template<class T>
Property<T>::Property(VOID)
{
}

template<class T>
Property<T>::Property(string name) : temp(TRUE), m_name(name)
{
}

template<class T>
Property<T>::Property(string name, shared_ptr<T> value) : temp(FALSE), m_value(value), m_name(name)
{
}

template<class T>
Property<T>::~Property(VOID)
{
}
