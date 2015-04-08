#include "todcore/method.h"
#include "todcore/basetype.h"
#include "todcore/node.h"

namespace tod
{

//-----------------------------------------------------------------------------
Method::Method(const str_t* prototype)
{
    this->initialize(prototype);
}


//-----------------------------------------------------------------------------
Method::~Method()
{
}


//-----------------------------------------------------------------------------
const String& Method::getName()
{
    return this->name;
}


//-----------------------------------------------------------------------------
 Params& Method::getParams()
 {
     return this->params;
 }
 

 //-----------------------------------------------------------------------------
 void Method::initialize(const str_t* prototype)
 {
     String p(prototype);
     size_t n1 = p.find(S("_"));
     if (n1 == -1) { TOD_TRACE(); return; }
     size_t n2 = p.rfind(S("_"));
     if (n2 == -1) { TOD_TRACE(); return; }
     this->name.assign(p, n1 + 1, n2 - n1 - 1);
     p[n1] = 0;
     p[n2] = 0;

     this->build_params(&p[0], this->params.out());
     this->build_params(&p[n2+1], this->params.in());
 }
 
 
 //-----------------------------------------------------------------------------
void Method::build_params(const str_t* p, INOUT Variables& v)
{
    size_t n = TOD_STRLEN(p);
    v.reserve(n);

    for (size_t i=0; i<n;++i)
    {
        switch (p[i])
        {
        case 'v':
            continue;
        case 'b':
            v.add<bool>();
            break;
        case 'i':
            v.add<int>();
            break;
        case 'L':
            v.add<int64>();
            break;
        case 'f':
            v.add<float>();
            break;
        case 'd':
            v.add<double>();
            break;
        case 's':
            v.add<String>();
            break;
        case 'u':
            //v->add<Uri>(Uri());
            break;
        case 't':
            //v->add<Vector3>(Vector3());
            break;
        case 'c':
            //v->add<Color>(Color());
            break;
        case 'o':
            v.add<Object*>();
            break;
        case 'n':
            v.add<Node*>();
            break;
        case 'l':
            //v->setForceList(true);
            break;
        }
    } 
}

}
