#include "todirrlicht/main.h"
#include "todcore/kernel.h"
#include "todcore/node.h"
#include "todirrlichtdevice.h"
namespace tod
{



void init_todirrlichtlib()
{
    BEGIN_MODULE(TodIrrlicht);
        ADD_TYPE(TodIrrlicht, TodIrrlichtDevice);
    END_MODULE(TodIrrlicht);
}




}
