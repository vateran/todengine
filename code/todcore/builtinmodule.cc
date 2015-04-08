#include "todcore/builtinmodule.h"
#include "todcore/object.h"
#include "todcore/node.h"

namespace tod
{

//-----------------------------------------------------------------------------
BuiltinModule::BuiltinModule():
    Module("builtin")
{
    this->addType<Object>();
    this->addType<Node>();
}

}
