#include "todcore/basetype.h"
#include "json/json.h"

namespace tod
{

//-----------------------------------------------------------------------------
void Color::fromString(const str_t* value)
{
    Json::Value jval;
    Json::Reader reader;
    if (!reader.parse(value, jval, false)) return;
    if (!jval.isArray()) return;
    if (jval.size() != 4) return;
    for (int i=0;i<4;++i)
    {
        this->array[i] = jval[i].asInt();
    }
}


//-----------------------------------------------------------------------------
void Color::toString(OUT String& s) const
{
    char buf[64];
    TOD_SNPRINTF(buf, sizeof(buf), S("[%d,%d,%d,%d]"), this->r, this->g, this->b, this->a);
    s = buf;
}

}
