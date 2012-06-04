#pragma once
#include "IProperty.h"
namespace events {
    enum PropertyType {
        NAME
    };
    template<class T>
    class Property : public 
        IProperty
    {
    private:
        std::shared_ptr<T> m_value;
    public:
        Property(VOID) {};
        ~Property(VOID) {};
        VOID SetValue(std::shared_ptr<T> value) { this->m_value = value; }
        std::shared_ptr<T> GetValue() { return this->m_value; }
    };
};


