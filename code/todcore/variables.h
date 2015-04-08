#pragma once
#include <vector>
#include "todcore/variable.h"
namespace tod
{ 

class Variables sealed
{
public:
    Variables();
    ~Variables();

    template <typename T>
    void add()
    {
        this->datas.push_back(new VariableBinder<T>());
    }
    template <typename T>
    void set(uint32 i, T value)
    {
        if (i>=this->datas.size()) { TOD_TRACE(); return; }
        typedef VariableBinder<T> VType;
        VType* v = dynamic_cast<VType*>(this->datas[i]);
        v->set(value);
    }
    template <typename T>
    T& get(uint32 i)
    {
        typedef VariableBinder<T> VType;
        if (i>=this->datas.size()) { TOD_TRACE(); return VType::null_instance()->get(); }
        VType* v = dynamic_cast<VType*>(this->datas[i]);
        return v->get();
    }

    Variable* getVariable(uint32 i);
    void clear();
    void reserve(size_t n);
    size_t size() const;

private:
    typedef std::vector<Variable*> Datas;

private:
    Datas datas;
};

}
