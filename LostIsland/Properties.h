#pragma once
#include "stdafx.h"
#include "Property.h"
namespace prop {
    //TODO
}
class Properties
{
private:
    hash_map<VOID*, VOID*> m_properties;

public:
    static Property<INT> ACTOR_ID;

    template<class T> 
    static Property<T> Init(string name) {
       return Property<T>(name);
    }

    static VOID Init() {
        Properties::ACTOR_ID = Properties::Init<INT>("test");
    }

    Properties(VOID);
    ~Properties(VOID);

    template<class T> 
    VOID SetProperty(Property<T> prop, shared_ptr<T> value);
    template<class T> 
    T GetValue(Property<T> prop);
};

