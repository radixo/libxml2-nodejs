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

	status = napi_create_function(env, NULL, 0, _xmlXPathEvalExpression,
	    NULL, &fn);
	if (status != napi_ok)
		return status;

	status = napi_set_named_property(env, exports, "xmlXPathEvalExpression",
	    fn);
	if (status != napi_ok)
		return status;

	status = napi_create_function(env, NULL, 0, _xmlXPathContext_set_node,
	    NULL, &fn);
	if (status != napi_ok)
		return status;

	status = napi_set_named_property(env, exports,
	    "xmlXPathContext_set_node", fn);
	if (status != napi_ok)
		return status;

	status = napi_create_function(env, NULL, 0, _xmlXPathObject_nodesetval,
	    NULL, &fn);
	if (status != napi_ok)
		return status;

	status = napi_set_named_property(env, exports,
	    "xmlXPathObject_nodesetval", fn);
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
	napi_value 	argv[1], export;
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
	if (vt != napi_external) {
		napi_throw_error(env, NULL, "'doc' must to be an external");
		return NULL;
	}

	// Get xmlDoc
	status = napi_get_value_external(env, argv[0], (void **)&doc);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read xmlDoc reference");
		return NULL;
	}

	// Creates the context
	xmlXPathContextPtr ctxp = xmlXPathNewContext(doc);
	if (ctxp == NULL) {
		napi_throw_error(env, NULL, "Error creating context");
		return NULL;
	}

	// creating ctxp external
	status = napi_create_external(env, ctxp, _xmlXPathNewContextFree, NULL,
	    &export);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't create external reference");
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

napi_value
_xmlXPathContext_set_node(napi_env env, napi_callback_info info)
{
	napi_status		status;
	size_t			argc = 2;
	napi_value		argv[2];
	napi_valuetype		vt;
	xmlXPathContextPtr	ctxt;
	xmlNodePtr		node;

	// Get arguments
	status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read arguments");
		return NULL;
	}

	// Get xmlXPathContext
	status = napi_get_value_external(env, argv[0], (void **)&ctxt);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read xmlXPathContext at arg "
		    "0");
		return NULL;
	}

	// Get xmlNode
	status = napi_typeof(env, argv[1], &vt);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read value type at arg 1");
		return NULL;
	}
	if (vt == napi_undefined || vt == napi_null) {
		node = NULL;
	} else {
		status = napi_get_value_external(env, argv[1], (void **)&node);
		if (status != napi_ok) {
			napi_throw_error(env, NULL, "Can't read xmlNode at arg "
			    "1");
			return NULL;
		}
	}
	
	// Sets the node to context
	ctxt->node = node;

	return NULL;
}

napi_value
_xmlXPathEvalExpression(napi_env env, napi_callback_info info)
{
	napi_status		status;
	napi_valuetype		vt;
	size_t 			argc = 2, str_l;
	napi_value 		argv[2], export;
	xmlChar			*str;
	xmlXPathContextPtr	ctxt;

	// Get arguments
	status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
	if (status != napi_ok)
		return NULL;

	if (argc != 2) {
		napi_throw_error(env, NULL, "You must provide all arguments: "
		    "'str', 'ctxt'");
		return NULL;
	}

	// Check each argument
	// str
	status = napi_typeof(env, argv[0], &vt);
	if (vt != napi_string) {
		napi_throw_error(env, NULL, "'str' must to be a string");
		return NULL;
	}
	status = napi_get_value_string_latin1(env, argv[0], NULL, 0, &str_l);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't get 'str' length");
		return NULL;
	}
	str_l++;
	str = malloc(str_l);
	if (str == NULL) {
		napi_throw_error(env, NULL, "Can't allocate 'str' mem");
		return NULL;
	}
	status = napi_get_value_string_latin1(env, argv[0], (char *)str, str_l,
	    NULL);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read 'str' argument");
		free(str);
		return NULL;
	}

	// ctxt
	status = napi_typeof(env, argv[1], &vt);
	if (vt != napi_external) {
		napi_throw_error(env, NULL, "'ctxt' must to be an external");
		free(str);
		return NULL;
	}
	status = napi_get_value_external(env, argv[1], (void **)&ctxt);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't retrieve xmlXPathContext");
		free(str);
		return NULL;
	}

	// Creates the xmlXPathObject from expression
	xmlXPathObjectPtr xpathobjp = xmlXPathEvalExpression(str, ctxt);
	free(str);
	if (!xpathobjp || xpathobjp->type != XPATH_NODESET) {
		napi_throw_error(env, NULL, "XPath query did not return a "
		    "nodeset");
		if (xpathobjp)
			xmlXPathFreeObject(xpathobjp);
		return NULL;
	}

	// creating xpathObj external
	status = napi_create_external(env, xpathobjp, _xmlXPathObjectFree,
	    NULL, &export);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't create external reference");
		xmlXPathFreeObject(xpathobjp);
		return NULL;
	}

	return export;
}

void
_xmlXPathObjectFree(napi_env env, void *finalize_data, void *finalize_hint)
{
	//
	xmlXPathFreeObject(finalize_data);
}

napi_value
_xmlXPathObject_nodesetval(napi_env env, napi_callback_info info)
{
	napi_status		status;
	size_t			argc = 1;
	napi_value		argv[1], export;
	xmlXPathObjectPtr	xpathobjp;

	// Get arguments
	status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read arguments");
		return NULL;
	}

	// Get XPathObject
	status = napi_get_value_external(env, argv[0], (void **)&xpathobjp);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read xmlXPathObject "
		    "reference");
		return NULL;
	}

	// create the export
	status = napi_create_external(env, xpathobjp->nodesetval, NULL, NULL,
	    &export);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't create export");
		return NULL;
	}

	return export;
}
