#pragma once

class IAppContext;

class CUserContext
{
public:
	CUserContext(const IAppContext& appContext);

private:
	const IAppContext& _appCtx;
};
