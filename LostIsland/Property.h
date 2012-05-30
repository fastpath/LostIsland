#pragma once
typedef shared_ptr<VOID> PropertyPtr;
template<class T>
class Property
{
private:
    shared_ptr<T> m_value;
    BOOL temp;
    string m_name;

protected:
    VOID SetValue(shared_ptr<T> value) { this->m_value = value; }
    shared_ptr<T> GetValue() CONST { return m_value; }

public:

    Property(VOID);
    Property(string name);
    Property(string name, shared_ptr<T> value);
    ~Property(VOID);

    VOID SetName(string name) { this->m_name = name; }
    string GetName() { return this->m_name; };
};

