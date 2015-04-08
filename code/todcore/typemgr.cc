#include "todcore/typemgr.h"
#include "todcore/object.h"
namespace tod
{

//-----------------------------------------------------------------------------
TypeMgr::~TypeMgr()
{
    for (auto i : this->types) delete i;
}


//-----------------------------------------------------------------------------
void TypeMgr::add(Type* type)
{
    this->types.emplace_back(type);
}

}
