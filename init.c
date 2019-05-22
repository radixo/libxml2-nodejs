#include "parser.h"
#include "c14n.h"
#include "xpath.h"

napi_value
Init(napi_env env, napi_value exports)
{
	napi_status status;

	status = parser_init(env, exports);
	if (status != napi_ok)
		return NULL;

	status = c14n_init(env, exports);
	if (status != napi_ok)
		return NULL;

	status = xpath_init(env, exports);
	if (status != napi_ok)
		return NULL;

	return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
