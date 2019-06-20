#include <stdio.h>
#include <libxml/encoding.h>

#include "napi.h"
#include "encoding.h"

napi_status
encoding_init(napi_env env, napi_value exports)
{
	napi_status status;
	napi_value fn;

	NAPI_EXPORT_FN(status, env, xmlFindCharEncodingHandler, fn, exports);

	return napi_ok;
}

napi_value
_xmlFindCharEncodingHandler(napi_env env, napi_callback_info info)
{
	napi_status	status;
	size_t		argc = 1;
	napi_value 	argv[1], export;
	char		str[20];

	// Get arguments
	status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read arguments");
		return NULL;
	}

	// Get xmlDoc
	status = napi_get_value_string_latin1(env, argv[0], str, 20, NULL);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read string at arg 0");
		return NULL;
	}

	xmlCharEncodingHandlerPtr encp = xmlFindCharEncodingHandler(str);
	if (encp == NULL) {
		napi_throw_error(env, NULL, "Encoding not found");
		return NULL;
	}

	// create the external
	status = napi_create_external(env, (void *)encp, NULL, NULL, &export);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't create external");
		return NULL;
	}

	return export;
}
