#pragma once
#include "todcore/derive.h"
#include "todcore/node.h"
#include "todcore/params.h"
namespace tod
{ 

class TODEXPORT ScriptServer : public AbstractDerive<ScriptServer, Node>
{
public:
    virtual bool run(const str_t* command, OUT String* result)=0;
    virtual bool call(const str_t* func_name, Params& params)=0;
    virtual bool runFile(const str_t* fname, OUT String* result)=0;

    static void bindMethod();
};

}
