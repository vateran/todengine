#include "todcore/tokenizer.h"

namespace tod
{

//-----------------------------------------------------------------------------
Tokenizer::Tokenizer(const str_t* s, const str_t sep)
{
    this->tokenize(s, sep);
};


//-----------------------------------------------------------------------------
uint32 Tokenizer::tokenize(const str_t* s, const str_t sep)
{
    this->clear();

    String tmp(s);
    str_t* b = &tmp[0];
    str_t* e = b;
    str_t* ee = &tmp[tmp.size()];
    bool f = true;

    do
    {
        if (f) { b = e; f = false; }
        if (*e==sep)
        {
            *e = 0;
            if (e-b>0) this->tokens.emplace_back(b);
            f = true;
        }

    } while (++e<ee);
    if (!f && e-b>0) this->tokens.emplace_back(b);

    return this->size();
}


//-----------------------------------------------------------------------------
void Tokenizer::clear()
{
    this->tokens.clear();
}


//-----------------------------------------------------------------------------
bool Tokenizer::empty() const
{
    return this->tokens.empty();
}


//-----------------------------------------------------------------------------
size_t Tokenizer::size() const
{
    return this->tokens.size();
}


//-----------------------------------------------------------------------------
Tokenizer::iterator Tokenizer::begin()
{
    return this->tokens.begin();
}


//-----------------------------------------------------------------------------
Tokenizer::iterator Tokenizer::end()
{
    return this->tokens.end();;
}


//-----------------------------------------------------------------------------
const String& Tokenizer::operator [] (size_t index) const
{
    return this->tokens[index];
}

}
