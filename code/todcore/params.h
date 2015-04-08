#pragma once
#include "todcore/variables.h"
namespace tod
{ 

class TODEXPORT Params
{
public:
    Variables& in() { return this->input; }
    Variables& out() { return this->output; } 

private:
    Variables input;
    Variables output;
};

}
