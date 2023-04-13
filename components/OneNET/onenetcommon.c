#include "onenetcommon.h"
#include "cJSON.h"

static bool g_IsInit=false;
static cJSON_Hooks g_cjsonhooks=
{
    .malloc_fn=OneNETMalloc,
    .free_fn=OneNETFree
};

void OneNETCommonInit()
{
    if(!g_IsInit)
    {
        //只初始化一次
        g_IsInit=true;
        cJSON_InitHooks(&g_cjsonhooks);
    }
}

