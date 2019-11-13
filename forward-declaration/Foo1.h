#pragma once

class Foo2;
class Foo1
{
public:
	Foo1();
	virtual ~Foo1();

private:
	Foo2* pfoo2;
};

