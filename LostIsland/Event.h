#pragma once
#include "Property.h"
#include "Properties.h"
namespace events {
    enum EventType {
        TEST_EVENT
    };
    class Event
    {
    private:
        
        props::Properties props;
        EventType m_type;

    public:

        Event(CONST EventType type);
        ~Event(VOID);

        EventType GetType(VOID) CONST { return m_type; }

        template<class T> std::shared_ptr<T> GetProperty(CONST props::PropertyType type) { 
            return this->props.template GetProperty<T>(type);
        }

        template<class T> VOID SetProperty(CONST props::PropertyType type,  CONST std::shared_ptr<T> value) {
            this->props.SetProperty(type, value);
        }
    };
};

