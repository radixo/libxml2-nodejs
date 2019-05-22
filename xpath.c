#include <stdio.h>
#include <string.h>
#include <libxml/xpath.h>

#include "xpath.h"

napi_status
xpath_init(napi_env env, napi_value exports)
{
	napi_status status;
	napi_value fn;

	status = napi_create_function(env, NULL, 0, _xmlXPathNewContext, NULL,
	    &fn);
	if (status != napi_ok)
		return status;

	status = napi_set_named_property(env, exports, "xmlXPathNewContext",
	    fn);
	if (status != napi_ok)
		return status;

	return napi_ok;
}

napi_value
_xmlXPathNewContext(napi_env env, napi_callback_info info)
{
	napi_status	status;
	napi_valuetype	vt;
	size_t 		argc = 1;
	napi_value 	argv[1], tmp, _o, _n, export;
	char		buf[10];
	xmlDocPtr	doc;

	// Get arguments
	status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
	if (status != napi_ok)
		return NULL;

	if (argc != 1) {
		napi_throw_error(env, NULL, "You must provide all arguments: "
		    "'doc'");
		return NULL;
	}

	// Check types
	status = napi_typeof(env, argv[0], &vt);
	if (vt != napi_object) {
		napi_throw_error(env, NULL, "'doc' must to be an xmlDoc "
		    "object");
		return NULL;
	}
	status = napi_get_named_property(env, argv[0], "_n", &tmp);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read property '_n' of doc "
		    "object");
		return NULL;
	}
	status = napi_get_value_string_latin1(env, tmp, buf, 10, &argc);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read object name");
		return NULL;
	}
	if (strcmp(buf, "xmlDoc") != 0) {
		napi_throw_error(env, NULL, "'doc' must to be an xmlDoc "
		    "object");
		return NULL;
	}

	// Creates the context
	status = napi_get_named_property(env, argv[0], "_o", &tmp);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read xmlDoc reference");
		return NULL;
	}
	status = napi_get_value_external(env, tmp, (void **)&doc);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't retrieve xmlDocPtr");
		return NULL;
	}

	// context var
	xmlXPathContextPtr ctxp = xmlXPathNewContext(doc);
	if (ctxp == NULL) {
		napi_throw_error(env, NULL, "Error creating context");
		return NULL;
	}

	// creating result object
	status = napi_create_object(env, &export);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't create result object");
		xmlXPathFreeContext(ctxp);
		return NULL;
	}

	// creating ctxp external
	status = napi_create_external(env, ctxp, _xmlXPathNewContextFree, NULL,
	    &_o);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't create external reference");
		xmlXPathFreeContext(ctxp);
		return NULL;
	}

	// creating ctxp object name
	status = napi_create_string_latin1(env, "xmlXPathContext",
	    NAPI_AUTO_LENGTH, &_n);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't create obj name");
		xmlXPathFreeContext(ctxp);
		return NULL;
	}

	// Object properties
	napi_property_descriptor props[] = {
		{ "_n", NULL, NULL, NULL, NULL, _n, napi_default, NULL },
		{ "_o", NULL, NULL, NULL, NULL, _o, napi_default, NULL }
	};

	// create object
	status = napi_define_properties(env, export, 2, props); 
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't define result obj "
		    "properties");
		xmlXPathFreeContext(ctxp);
		return NULL;
	}

	return export;
}

void
_xmlXPathNewContextFree(napi_env env, void *finalize_data, void *finalize_hint)
{
	//
	xmlXPathFreeContext(finalize_data);
}
