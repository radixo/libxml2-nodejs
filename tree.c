#include <stdio.h>
#include <libxml/tree.h>

#include "tree.h"

napi_status
tree_init(napi_env env, napi_value exports)
{
	napi_status status;
	napi_value fn;

	status = napi_create_function(env, NULL, 0, _xmlDocGetRootElement, NULL,
	    &fn);
	if (status != napi_ok)
		return status;

	status = napi_set_named_property(env, exports, "xmlDocGetRootElement",
	    fn);
	if (status != napi_ok)
		return status;

	status = napi_create_function(env, NULL, 0, _xmlNode_type, NULL,
	    &fn);
	if (status != napi_ok)
		return status;

	status = napi_set_named_property(env, exports, "xmlNode_type",
	    fn);
	if (status != napi_ok)
		return status;

	status = napi_create_function(env, NULL, 0, _xmlNode_name, NULL,
	    &fn);
	if (status != napi_ok)
		return status;

	status = napi_set_named_property(env, exports, "xmlNode_name",
	    fn);
	if (status != napi_ok)
		return status;

	status = napi_create_function(env, NULL, 0, _xmlNode_next, NULL,
	    &fn);
	if (status != napi_ok)
		return status;

	status = napi_set_named_property(env, exports, "xmlNode_next",
	    fn);
	if (status != napi_ok)
		return status;

	status = napi_create_function(env, NULL, 0, _xmlNode_prev, NULL,
	    &fn);
	if (status != napi_ok)
		return status;

	status = napi_set_named_property(env, exports, "xmlNode_prev",
	    fn);
	if (status != napi_ok)
		return status;

	status = napi_create_function(env, NULL, 0, _xmlNode_parent, NULL,
	    &fn);
	if (status != napi_ok)
		return status;

	status = napi_set_named_property(env, exports, "xmlNode_parent",
	    fn);
	if (status != napi_ok)
		return status;

	status = napi_create_function(env, NULL, 0, _xmlNode_children, NULL,
	    &fn);
	if (status != napi_ok)
		return status;

	status = napi_set_named_property(env, exports, "xmlNode_children",
	    fn);
	if (status != napi_ok)
		return status;

	status = napi_create_function(env, NULL, 0, _xmlNode_eq, NULL,
	    &fn);
	if (status != napi_ok)
		return status;

	status = napi_set_named_property(env, exports, "xmlNode_eq",
	    fn);
	if (status != napi_ok)
		return status;

	return napi_ok;
}

napi_value
_xmlDocGetRootElement(napi_env env, napi_callback_info info)
{
	napi_status	status;
	size_t		argc = 1;
	napi_value 	argv[1], export;
	xmlDocPtr	doc;
	xmlNodePtr	node;

	// Get arguments
	status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read arguments");
		return NULL;
	}

	// Get xmlDoc
	status = napi_get_value_external(env, argv[0], (void **)&doc);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read xmlDoc at arg 0");
		return NULL;
	}

	// Get the root element
	node = xmlDocGetRootElement(doc);
	if (node == NULL) {
		napi_throw_error(env, NULL, "Error trying to get root element");
		return NULL;
	}

	// create the external
	status = napi_create_external(env, (void *)node, NULL, NULL, &export);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't create external");
		return NULL;
	}

	return export;
}

napi_value
_xmlNode_type(napi_env env, napi_callback_info info)
{
	napi_status	status;
	size_t		argc = 1;
	napi_value	argv[1], export;
	xmlNodePtr	node;

	// Get arguments
	status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read arguments");
		return NULL;
	}

	// Get xmlNode
	status = napi_get_value_external(env, argv[0], (void **)&node);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read xmlNode at arg 0");
		return NULL;
	}

	// create the export
	status = napi_create_int32(env, (int32_t)node->type, &export);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't create export");
		return NULL;
	}

	return export;
}

napi_value
_xmlNode_name(napi_env env, napi_callback_info info)
{
	napi_status	status;
	size_t		argc = 1;
	napi_value	argv[1], export;
	xmlNodePtr	node;

	// Get arguments
	status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read arguments");
		return NULL;
	}

	// Get xmlNode
	status = napi_get_value_external(env, argv[0], (void **)&node);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read xmlNode at arg 0");
		return NULL;
	}

	// create the export
	status = napi_create_string_utf8(env, (char *)node->name,
	    NAPI_AUTO_LENGTH, &export);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't create export");
		return NULL;
	}

	return export;
}

napi_value
_xmlNode_next(napi_env env, napi_callback_info info)
{
	napi_status	status;
	size_t		argc = 1;
	napi_value	argv[1], export;
	xmlNodePtr	node;

	// Get arguments
	status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read arguments");
		return NULL;
	}

	// Get xmlNode
	status = napi_get_value_external(env, argv[0], (void **)&node);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read xmlNode at arg 0");
		return NULL;
	}

	// return null when null
	if (node->next == NULL)
		return NULL;

	// create the export
	status = napi_create_external(env, node->next, NULL, NULL, &export);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't create export");
		return NULL;
	}

	return export;
}

napi_value
_xmlNode_prev(napi_env env, napi_callback_info info)
{
	napi_status	status;
	size_t		argc = 1;
	napi_value	argv[1], export;
	xmlNodePtr	node;

	// Get arguments
	status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read arguments");
		return NULL;
	}

	// Get xmlNode
	status = napi_get_value_external(env, argv[0], (void **)&node);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read xmlNode at arg 0");
		return NULL;
	}

	// return null when null
	if (node->prev == NULL)
		return NULL;

	// create the export
	status = napi_create_external(env, node->prev, NULL, NULL, &export);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't create export");
		return NULL;
	}

	return export;
}

napi_value
_xmlNode_parent(napi_env env, napi_callback_info info)
{
	napi_status	status;
	size_t		argc = 1;
	napi_value	argv[1], export;
	xmlNodePtr	node;

	// Get arguments
	status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read arguments");
		return NULL;
	}

	// Get xmlNode
	status = napi_get_value_external(env, argv[0], (void **)&node);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read xmlNode at arg 0");
		return NULL;
	}

	// return null when null
	if (node->parent == NULL)
		return NULL;

	// create the export
	status = napi_create_external(env, node->parent, NULL, NULL, &export);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't create export");
		return NULL;
	}

	return export;
}

napi_value
_xmlNode_children(napi_env env, napi_callback_info info)
{
	napi_status	status;
	size_t		argc = 1;
	napi_value	argv[1], export;
	xmlNodePtr	node;

	// Get arguments
	status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read arguments");
		return NULL;
	}

	// Get xmlNode
	status = napi_get_value_external(env, argv[0], (void **)&node);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read xmlNode at arg 0");
		return NULL;
	}

	// return null when null
	if (node->children == NULL)
		return NULL;

	// create the export
	status = napi_create_external(env, node->children, NULL, NULL, &export);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't create export");
		return NULL;
	}

	return export;
}

napi_value
_xmlNode_eq(napi_env env, napi_callback_info info)
{
	napi_status	status;
	size_t		argc = 2;
	napi_value	argv[2], tmp, export;
	xmlNodePtr	node0, node1;

	// Get arguments
	status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read arguments");
		return NULL;
	}

	// Get xmlNode 0
	status = napi_get_value_external(env, argv[0], (void **)&node0);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read xmlNode at arg 0");
		return NULL;
	}

	// Get xmlNode 1
	status = napi_get_value_external(env, argv[1], (void **)&node1);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read xmlNode at arg 1");
		return NULL;
	}

	// check if are equal
	status = napi_create_int32(env, (int32_t)(node0 == node1), &tmp);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't create cmp var");
		return NULL;
	}

	// create the export
	status = napi_coerce_to_bool(env, tmp, &export);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't create export");
		return NULL;
	}

	return export;
}
