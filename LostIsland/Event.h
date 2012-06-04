#pragma once
#include "Property.h"
namespace events {
    enum EventType {
        TEST_EVENT
    };
    class Event
    {
    private:
        
        std::hash_map<PropertyType, std::shared_ptr<IProperty>> m_properties;

        EventType m_type;

    public:
        /*
        std::string m_string;
        INT m_int;

        FLOAT m_float;
        DOUBLE m_double;
        LONG m_long;
        std::shared_ptr<VOID> m_pData; */

        Event(CONST EventType type);

        ~Event(VOID);

        EventType GetType(VOID) CONST { return m_type; }

        template<class T> std::shared_ptr<T> GetProperty(CONST PropertyType type) { 
            std::hash_map<PropertyType, std::shared_ptr<IProperty>>::iterator it = this->m_properties.find(type);
            if(it == this->m_properties.end())
            {
                return NULL;
            }
//            std::shared_ptr<Property<T>> p = std::static_pointer_cast<std::shared_ptr<Property<T>>>(it->second);
            IProperty* p = it->second.get();
            Property<T>* t = std::static_pointer_cast<Property<T>>(p);
            return NULL;//p->GetValue();
        }

        template<class T> VOID SetProperty(CONST PropertyType type,  CONST std::shared_ptr<T> value) {
            Property<T>* p = new Property<T>;
            p->SetValue(value);
            std::shared_ptr<Property<T>> ptr(p);
            this->m_properties.insert(std::pair<PropertyType, std::shared_ptr<IProperty>>(type, ptr));
        }
    };
};

