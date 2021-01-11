#include "UserContext.h"
#include "IAppContext.h"

CUserContext::CUserContext( const IAppContext& appContext )
	: _appCtx(appContext)
{
}
