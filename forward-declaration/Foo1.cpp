#include "Foo1.h"
#include "Foo2.h"

Foo1::Foo1()
	: pfoo2( new Foo2() )
{

}

Foo1::~Foo1()
{
	delete pfoo2;
}
