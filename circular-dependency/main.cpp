#include <iostream>
#include "AppContext.h"
#include "UserContext.h"

int main()
{
    CAppContext app(1);

    CUserContext userCtx(app);
}
