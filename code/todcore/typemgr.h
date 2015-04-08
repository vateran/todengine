#pragma once
#include <list>
#include "todcore/macro.h"
#include "todcore/singleton.h"
namespace tod
{

class Type;
class TODEXPORT TypeMgr : public Singleton<TypeMgr>
{
public:
	virtual~TypeMgr();

	void add(Type* type);

private:
	typedef std::list<Type*> Types;

private:
	Types types;
};

}
