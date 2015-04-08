#pragma once
#include <vector>
#include "todcore/basetype.h"
#include "todcore/macro.h"
#include "todcore/string.h"
namespace tod
{ 

class Tokenizer
{
public:
    typedef std::vector<String> Tokens;
    typedef Tokens::iterator iterator;

public:
    Tokenizer(const str_t* s, const str_t sep);

    uint32 tokenize(const str_t* s, const str_t sep);

    void clear();
    bool empty() const;
    size_t size() const;

    iterator begin();
    iterator end();

    const String& operator [] (size_t index) const;


private:
    Tokens tokens;
};

}
