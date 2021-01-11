#pragma once
#include "IAppContext.h"

class CAppContext : public IAppContext
{
public:
	CAppContext(int id);

	virtual int id() const { return _id; }

private:
	int _id;
};

