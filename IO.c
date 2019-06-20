#include <stdio.h>
#include <libxml/xmlIO.h>

#include "napi.h"
#include "IO.h"

napi_status
IO_init(napi_env env, napi_value exports)
{
	napi_status status;
	napi_value fn;

	NAPI_EXPORT_FN(status, env, xmlAllocOutputBuffer, fn, exports);
	NAPI_EXPORT_FN(status, env, xmlOutputBufferFlush, fn, exports);
	NAPI_EXPORT_FN(status, env, xmlOutputBufferGetContent, fn, exports);
	NAPI_EXPORT_FN(status, env, xmlOutputBufferGetSize, fn, exports);

	return napi_ok;
}

napi_value
_xmlAllocOutputBuffer(napi_env env, napi_callback_info info)
{
	napi_status			status;
	size_t				argc = 1;
	napi_value 			argv[1], export;
	napi_valuetype			vt;
	xmlCharEncodingHandlerPtr	encp;
	xmlOutputBufferPtr		bufp;

	// Get arguments
	status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read arguments");
		return NULL;
	}

	// Get xmlCharEncodingHandlerPtr
	status = napi_typeof(env, argv[0], &vt);
	if (vt == napi_null || vt == napi_undefined) {
		encp = NULL;
	} else {
		status = napi_get_value_external(env, argv[0], (void **)&encp);
		if (status != napi_ok) {
			napi_throw_error(env, NULL, "Can't read "
			    "xmlCharEncodingHandlerPtr at arg 0");
			return NULL;
		}
	}

	bufp = xmlAllocOutputBuffer(encp);
	if (bufp == NULL) {
		napi_throw_error(env, NULL, "Can't allocate xmlOutputBuffer");
		return NULL;
	}

	// create the external
	status = napi_create_external(env, (void *)bufp,
	    _xmlAllocOutputBufferFree, NULL, &export);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't create external");
		return NULL;
	}

	return export;
}

void
_xmlAllocOutputBufferFree(napi_env env, void *finalize_data,
    void *finalize_hint)
{
	//
	if (xmlOutputBufferClose(finalize_data) == -1) {
		napi_throw_error(env, NULL, "Can't close xmlOutputBuffer");
	}
}

napi_value
_xmlOutputBufferFlush(napi_env env, napi_callback_info info)
{
	napi_status		status;
	size_t			argc = 1;
	napi_value 		argv[1], export;
	xmlOutputBufferPtr	out;
	int			ret;

	// Get arguments
	status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read arguments");
		return NULL;
	}

	// Get xmlOutputBufferPtr
	status = napi_get_value_external(env, argv[0], (void **)&out);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read xmlOutputBufferPtr "
		    "at arg 0");
		return NULL;
	}

	// Exec
	ret = xmlOutputBufferFlush(out);

	// create the external
	status = napi_create_int64(env, (int64_t)ret, &export);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't create external");
		return NULL;
	}

	return export;
}

napi_value
_xmlOutputBufferGetContent(napi_env env, napi_callback_info info)
{
	napi_status		status;
	size_t			argc = 1;
	napi_value 		argv[1], export;
	xmlOutputBufferPtr	out;
	const xmlChar		*ret;

	// Get arguments
	status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read arguments");
		return NULL;
	}

	// Get xmlOutputBufferPtr
	status = napi_get_value_external(env, argv[0], (void **)&out);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read xmlOutputBufferPtr "
		    "at arg 0");
		return NULL;
	}

	// Exec
	ret = xmlOutputBufferGetContent(out);
	if (ret == NULL) {
		napi_throw_error(env, NULL, "Exucution error "
		    "xmlOutputBufferGetContent");
		return NULL;
	}

	// create the external
	status = napi_create_string_utf8(env, (char *)ret, NAPI_AUTO_LENGTH,
	    &export);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't create external");
		return NULL;
	}

	return export;
}

napi_value
_xmlOutputBufferGetSize(napi_env env, napi_callback_info info)
{
	napi_status		status;
	size_t			argc = 1;
	napi_value 		argv[1], export;
	xmlOutputBufferPtr	out;
	size_t			ret;

	// Get arguments
	status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read arguments");
		return NULL;
	}

	// Get xmlOutputBufferPtr
	status = napi_get_value_external(env, argv[0], (void **)&out);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read xmlOutputBufferPtr "
		    "at arg 0");
		return NULL;
	}

	// Exec
	ret = xmlOutputBufferGetSize(out);

	// create the external
	status = napi_create_int64(env, (int64_t)ret, &export);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't create external");
		return NULL;
	}

	return export;
}
