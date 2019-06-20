#include "parser.h"
#include "c14n.h"
#include "xpath.h"
#include "tree.h"
#include "encoding.h"
#include "IO.h"

napi_value
Init(napi_env env, napi_value exports)
{
	napi_status status;

#define NAPI_MODULE_INIT(FN)						\
	status = FN ## _init(env, exports);				\
	if (status != napi_ok)						\
		return NULL;

	NAPI_MODULE_INIT(parser);
	NAPI_MODULE_INIT(c14n);
	NAPI_MODULE_INIT(xpath);
	NAPI_MODULE_INIT(tree);
	NAPI_MODULE_INIT(encoding);
	NAPI_MODULE_INIT(IO);

#undef NAPI_MODULE_INIT

	return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
