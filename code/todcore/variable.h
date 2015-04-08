#pragma once
#include <map>
#include <list>
#include "todcore/macro.h"
#include "todcore/string.h"
#include "todcore/typeid.h"
#include "todcore/singleton.h"
namespace tod
{ 

class TODEXPORT Variable
{
public:
    virtual~Variable() {}

    virtual type_id getType() const
    {
        return TypeId<void>::id();
    }

private:

};


template <typename TYPE>
class TODEXPORT VariableBinder : public Variable
{
public:
    VariableBinder() {}
    virtual~VariableBinder() {}

    void set(const TYPE& value)
    {
        this->data = value;
    }
    TYPE& get()
    {
        return this->data;
    }
    OVERRIDE type_id getType() const
    {
        return TypeId<TYPE>::id();
    }

public:
    class NullHolder : public Singleton<NullHolder>
    {
    public:
        ~NullHolder()
        {
            for (auto i : this->nulls) delete i;
        }
        void add(Variable* value)
        {
            this->nulls.push_back(value);
        }
    private:
        std::list<Variable*> nulls;
    };
    static VariableBinder<TYPE>* null_instance()
    {
        if (nullptr == VariableBinder<TYPE>::s_null)
        {
            VariableBinder<TYPE>::s_null = new VariableBinder<TYPE>();
            NullHolder::instance()->add(VariableBinder<TYPE>::s_null);
        }
        return VariableBinder<TYPE>::s_null;
    }

private:
    TYPE data;
    static VariableBinder<TYPE>* s_null;
};

template <typename TYPE>
VariableBinder<TYPE>* VariableBinder<TYPE>::s_null = nullptr;

}
