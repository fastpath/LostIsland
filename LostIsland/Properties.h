#pragma once
#include "IProperty.h"
namespace props {
    class Properties
    {
    private:
        std::hash_map<props::PropertyType, std::shared_ptr<props::IProperty>> m_properties;
    public:
        Properties(VOID) {};
        ~Properties(VOID) {};

        template<class T> std::shared_ptr<T> GetProperty(CONST PropertyType type) { 
            std::hash_map<PropertyType, std::shared_ptr<IProperty>>::iterator it = this->m_properties.find(type);
            if(it == this->m_properties.end())
            {
                return NULL;
            }
            std::shared_ptr<Property<T>> p = std::static_pointer_cast<Property<T>>(it->second);
            return p->GetValue();
        }

        template<class T> VOID SetProperty(CONST PropertyType type,  CONST std::shared_ptr<T> value) {
            Property<T>* p = new Property<T>;
            p->SetValue(value);
            std::shared_ptr<Property<T>> ptr(p);
            this->m_properties.insert(std::pair<PropertyType, std::shared_ptr<IProperty>>(type, ptr));
        }
    };
};


