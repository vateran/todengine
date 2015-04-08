#pragma once
#include "todcore/basetype.h"
#include "todcore/derive.h"
#include "todcore/macro.h"
namespace tod
{ 

class TODEXPORT Object : public Derive<Object, void>
{
public:
    Object();
    virtual~Object();

    void autorelease();
    uint32 retain();
    uint32 release();
    uint32 getRefCount();
    uint32 getId();

    static void bindMethod();
    static void bindProperty();

private:
    uint32 id;
    uint32 refCount;

private:
    static uint32 s_id;
};

}

