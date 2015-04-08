#include "todcore/variables.h"

namespace tod
{

//-----------------------------------------------------------------------------
Variables::Variables()
{

}


//-----------------------------------------------------------------------------
Variables::~Variables()
{
    this->clear();
}


//-----------------------------------------------------------------------------
Variable* Variables::getVariable(uint32 i)
{
    return this->datas[i];
}


//-----------------------------------------------------------------------------
void Variables::clear()
{
    for (auto i : this->datas) delete i;
    this->datas.clear();
}


//-----------------------------------------------------------------------------
void Variables::reserve(size_t n)
{
    this->datas.reserve(n);
}


//-----------------------------------------------------------------------------
size_t Variables::size() const
{
    return this->datas.size();
}

}
