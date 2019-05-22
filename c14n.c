#include <stdio.h>

#include "c14n.h"

napi_status
c14n_init(napi_env env, napi_value exports)
{
	napi_status status;
	napi_value fn;

	status = napi_create_function(env, NULL, 0, _xmlC14NDocDumpMemory, NULL,
	    &fn);
	if (status != napi_ok)
		return status;

	status = napi_set_named_property(env, exports, "xmlC14NDocDumpMemory",
	    fn);
	if (status != napi_ok)
		return status;

	return napi_ok;
}

napi_value
_xmlC14NDocDumpMemory(napi_env env, napi_callback_info info)
{
	printf("ta aqui\n");
	return NULL;
}
