#include <stdio.h>
#include <libxml/tree.h>

#include "napi.h"
#include "tree.h"

napi_status
tree_init(napi_env env, napi_value exports)
{
	napi_status status;
	napi_value fn;

	NAPI_EXPORT_FN(status, env, xmlDocGetRootElement, fn, exports);
	NAPI_EXPORT_FN(status, env, xmlNode_type, fn, exports);
	NAPI_EXPORT_FN(status, env, xmlNode_name, fn, exports);
	NAPI_EXPORT_FN(status, env, xmlNode_next, fn, exports);
	NAPI_EXPORT_FN(status, env, xmlNode_prev, fn, exports);
	NAPI_EXPORT_FN(status, env, xmlNode_parent, fn, exports);
	NAPI_EXPORT_FN(status, env, xmlNode_content, fn, exports);
	NAPI_EXPORT_FN(status, env, xmlNode_children, fn, exports);
	NAPI_EXPORT_FN(status, env, xmlNode_eq, fn, exports);
	NAPI_EXPORT_FN(status, env, xmlGetProp, fn, exports);
	NAPI_EXPORT_FN(status, env, xmlDocDumpMemory, fn, exports);
	NAPI_EXPORT_FN(status, env, xmlDoc_encoding, fn, exports);
	NAPI_EXPORT_FN(status, env, xmlNewNode, fn, exports);
	NAPI_EXPORT_FN(status, env, xmlNewNs, fn, exports);
	NAPI_EXPORT_FN(status, env, xmlSetNs, fn, exports);
	NAPI_EXPORT_FN(status, env, xmlAddNextSibling, fn, exports);
	NAPI_EXPORT_FN(status, env, xmlAddPrevSibling, fn, exports);
	NAPI_EXPORT_FN(status, env, xmlAddChild, fn, exports);
	NAPI_EXPORT_FN(status, env, xmlNewProp, fn, exports);
	NAPI_EXPORT_FN(status, env, xmlNodeAddContent, fn, exports);
	NAPI_EXPORT_FN(status, env, xmlNodeDumpOutput, fn, exports);

	return napi_ok;
}


/**
 * Get the root element of the document.
 * @name xmlDocGetRootElement
 * @function
 * @param {xmlDocPtr} doc The document
 * @return {xmlNodePtr} the #xmlNodePtr for the root or undefined
 */
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
_xmlNode_content(napi_env env, napi_callback_info info)
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
	if (node->content == NULL)
		return NULL;

	// create the export
	status = napi_create_string_utf8(env, (char *)node->content,
	    NAPI_AUTO_LENGTH, &export);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't create return");
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

napi_value
_xmlGetProp(napi_env env, napi_callback_info info)
{
	napi_status	status;
	size_t		argc = 2, len;
	napi_value	argv[2], export;
	xmlNodePtr	node;
	char		*pname;
	xmlChar		*pval;

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

	// Get property name
	status = napi_get_value_string_latin1(env, argv[1], NULL, 0, &len);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read name at arg 1");
		return NULL;
	}
	pname = (char *)malloc(++len);
	status = napi_get_value_string_latin1(env, argv[1], pname, len, NULL);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read name at arg 1");
		free(pname);
		return NULL;
	}

	// Get prop
	pval = xmlGetProp(node, BAD_CAST pname);
	if (pval == NULL) {
		free(pname);
		return NULL;
	}

	// Creating return
	status = napi_create_string_utf8(env, (char *)pval, NAPI_AUTO_LENGTH,
	    &export);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't create return");
		free(pname);
	}

	free(pname);
	return export;
}

napi_value
_xmlDocDumpMemory(napi_env env, napi_callback_info info)
{
	napi_status	status;
	size_t		argc = 1;
	napi_value	argv[1], export;
	xmlDocPtr	doc;
	xmlChar		*mem;

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

	// Get Document
	xmlDocDumpMemory(doc, (xmlChar **)&mem, NULL);

	// Create export
	status = napi_create_string_utf8(env, (char *)mem, NAPI_AUTO_LENGTH,
	    &export);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't create return");
		xmlFree(mem);
		return NULL;
	}

	xmlFree(mem);
	return export;
}

napi_value
_xmlDoc_encoding(napi_env env, napi_callback_info info)
{
	napi_status	status;
	size_t		argc = 1;
	napi_value	argv[1], export;
	xmlDocPtr	doc;


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

	if (doc->encoding == NULL)
		return NULL;

	// Create export
	status = napi_create_string_utf8(env, (char *)doc->encoding,
	    NAPI_AUTO_LENGTH, &export);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't create return");
		return NULL;
	}

	return export;
}

napi_value
_xmlNewNode(napi_env env, napi_callback_info info)
{
	napi_status	status;
	size_t		argc = 2, len;
	napi_value	argv[2], export;
	napi_valuetype	vt;
	xmlNsPtr	ns;
	xmlChar		*name;
	xmlNodePtr	node;

	// Get arguments
	status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read arguments");
		return NULL;
	}

	// Get xmlNs
	status = napi_typeof(env, argv[0], &vt);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read value type at arg 0");
		return NULL;
	}
	if (vt == napi_undefined || vt == napi_null) {
		ns = NULL;
	} else {
		status = napi_get_value_external(env, argv[0], (void **)&ns);
		if (status != napi_ok) {
			napi_throw_error(env, NULL, "Can't read xmlNode at arg "
			    "0");
			return NULL;
		}
	}

	// Get name
	status = napi_get_value_string_latin1(env, argv[1], NULL, 0, &len);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't get name length at arg 1");
		return NULL;
	}
	name = BAD_CAST malloc(++len);
	status = napi_get_value_string_latin1(env, argv[1], (char *)name, len,
	    NULL);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read name at arg 1");
		free(name);
		return NULL;
	}

	// Create the node
	node = xmlNewNode(ns, name);
	if (node == NULL) {
		napi_throw_error(env, NULL, "Error: could not create new node");
		free(name);
		return NULL;
	}

	// Create the export
	status = napi_create_external(env, (void *)node, NULL, NULL, &export);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't create external");
		free(name);
		return NULL;
	}

	free(name);
	return export;
}

napi_value
_xmlNewNs(napi_env env, napi_callback_info info)
{
	napi_status	status;
	size_t		argc = 3, len;
	napi_value	argv[3], export;
	napi_valuetype	vt;
	xmlChar		*prefix, *href;
	xmlNodePtr	node;
	xmlNsPtr	ns;

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

	// Get href
	status = napi_get_value_string_latin1(env, argv[1], NULL, 0, &len);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't get href length at arg 1");
		return NULL;
	}
	href = BAD_CAST malloc(++len);
	status = napi_get_value_string_latin1(env, argv[1], (char *)href, len,
	    NULL);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read href at arg 1");
		free(href);
		return NULL;
	}

	// Get prefix
	status = napi_typeof(env, argv[2], &vt);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read value type at arg 2");
		free(href);
		return NULL;
	}
	if (vt == napi_undefined || vt == napi_null) {
		prefix = NULL;
	} else {
		status = napi_get_value_string_latin1(env, argv[2], NULL, 0,
		    &len);
		if (status != napi_ok) {
			napi_throw_error(env, NULL, "Can't get prefix length "
			    "at arg 2");
			free(href);
			return NULL;
		}
		prefix = BAD_CAST malloc(++len);
		status = napi_get_value_string_latin1(env, argv[2],
		    (char *)prefix, len, NULL);
		if (status != napi_ok) {
			napi_throw_error(env, NULL, "Can't read prefix at arg "
			    "1");
			free(href);
			free(prefix);
			return NULL;
		}
	}

	// Create the NS
	ns = xmlNewNs(node, href, prefix);
	if (ns == NULL) {
		napi_throw_error(env, NULL, "Error: could not create new "
		    "namespate");
		free(href);
		free(prefix);
		return NULL;
	}

	// Create the export
	status = napi_create_external(env, (void *)ns, NULL, NULL, &export);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't create external");
		free(href);
		free(prefix);
		return NULL;
	}

	free(href);
	free(prefix);
	return export;
}

napi_value
_xmlSetNs(napi_env env, napi_callback_info info)
{
	napi_status	status;
	size_t		argc = 2;
	napi_value	argv[2];
	xmlNodePtr	node;
	xmlNsPtr	ns;

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

	// Get xmlNs
	status = napi_get_value_external(env, argv[1], (void **)&ns);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read xmlNs at arg 1");
		return NULL;
	}

	// exec xmlSetNs
	xmlSetNs(node, ns);

	return NULL;
}

napi_value
_xmlAddNextSibling(napi_env env, napi_callback_info info)
{
	napi_status	status;
	size_t		argc = 2;
	napi_value	argv[2], export;
	xmlNodePtr	cur, elem;

	// Get arguments
	status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read arguments");
		return NULL;
	}

	// Get xmlNode
	status = napi_get_value_external(env, argv[0], (void **)&cur);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read xmlNode at arg 0");
		return NULL;
	}

	// Get xmlNode
	status = napi_get_value_external(env, argv[1], (void **)&elem);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read xmlNode at arg 1");
		return NULL;
	}

	// Exec func
	elem = xmlAddNextSibling(cur, elem);
	if (elem == NULL) {
		napi_throw_error(env, NULL, "Error: could not add node");
		return NULL;
	}

	// Create the export
	status = napi_create_external(env, (void *)elem, NULL, NULL, &export);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't create external");
		return NULL;
	}

	return export;
}

napi_value
_xmlAddPrevSibling(napi_env env, napi_callback_info info)
{
	napi_status	status;
	size_t		argc = 2;
	napi_value	argv[2], export;
	xmlNodePtr	cur, elem;

	// Get arguments
	status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read arguments");
		return NULL;
	}

	// Get xmlNode
	status = napi_get_value_external(env, argv[0], (void **)&cur);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read xmlNode at arg 0");
		return NULL;
	}

	// Get xmlNode
	status = napi_get_value_external(env, argv[1], (void **)&elem);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read xmlNode at arg 1");
		return NULL;
	}

	// Exec func
	elem = xmlAddPrevSibling(cur, elem);
	if (elem == NULL) {
		napi_throw_error(env, NULL, "Error: could not add node");
		return NULL;
	}

	// Create the export
	status = napi_create_external(env, (void *)elem, NULL, NULL, &export);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't create external");
		return NULL;
	}

	return export;
}

napi_value
_xmlAddChild(napi_env env, napi_callback_info info)
{
	napi_status	status;
	size_t		argc = 2;
	napi_value	argv[2], export;
	xmlNodePtr	parent, cur;

	// Get arguments
	status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read arguments");
		return NULL;
	}

	// Get xmlNode
	status = napi_get_value_external(env, argv[0], (void **)&parent);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read xmlNode at arg 0");
		return NULL;
	}

	// Get xmlNode
	status = napi_get_value_external(env, argv[1], (void **)&cur);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read xmlNode at arg 1");
		return NULL;
	}

	// Exec func
	cur = xmlAddChild(parent, cur);
	if (cur == NULL) {
		napi_throw_error(env, NULL, "Error: could not add node");
		return NULL;
	}

	// Create the export
	status = napi_create_external(env, (void *)cur, NULL, NULL, &export);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't create external");
		return NULL;
	}

	return export;
}

napi_value
_xmlNewProp(napi_env env, napi_callback_info info)
{
	napi_status	status;
	size_t		argc = 3, len;
	napi_value	argv[3], export;
	xmlChar		*name, *value;
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

	// Get name
	status = napi_get_value_string_latin1(env, argv[1], NULL, 0, &len);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't get name length at arg 1");
		return NULL;
	}
	name = BAD_CAST malloc(++len);
	status = napi_get_value_string_latin1(env, argv[1], (char *)name, len,
	    NULL);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read name at arg 1");
		free(name);
		return NULL;
	}

	// Get value
	status = napi_get_value_string_latin1(env, argv[2], NULL, 0, &len);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't get value length at arg 2");
		free(name);
		return NULL;
	}
	value = BAD_CAST malloc(++len);
	status = napi_get_value_string_latin1(env, argv[2], (char *)value, len,
	    NULL);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read value at arg 2");
		free(name);
		free(value);
		return NULL;
	}

	// Exec func
	xmlAttrPtr attr = xmlNewProp(node, name, value);
	if (attr == NULL) {
		napi_throw_error(env, NULL, "Error: could not create prop");
		free(name);
		free(value);
	}

	// Create the export
	status = napi_create_external(env, (void *)attr, NULL, NULL, &export);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't create external");
		free(name);
		free(value);
		return NULL;
	}

	free(name);
	free(value);
	return export;
}

napi_value
_xmlNodeAddContent(napi_env env, napi_callback_info info)
{
	napi_status	status;
	size_t		argc = 2, len;
	napi_value	argv[2];
	xmlChar		*content;
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

	// Get content
	status = napi_get_value_string_latin1(env, argv[1], NULL, 0, &len);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't get content length at arg "
		    "1");
		return NULL;
	}
	content = BAD_CAST malloc(++len);
	status = napi_get_value_string_latin1(env, argv[1], (char *)content,
	    len, NULL);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read content at arg 1");
		free(content);
		return NULL;
	}

	// Exec func
	xmlNodeAddContent(node, content);

	free(content);
	return NULL;
}

napi_value
_xmlNodeGetContent(napi_env env, napi_callback_info info)
{
	napi_status	status;
	size_t		argc = 1;
	napi_value	argv[1], export;
	xmlNodePtr	node;
	xmlChar		*mem;

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

	// Get Document
	mem = xmlNodeGetContent(node);

	// Create export
	status = napi_create_string_utf8(env, (char *)mem, NAPI_AUTO_LENGTH,
	    &export);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't create return");
		xmlFree(mem);
		return NULL;
	}

	xmlFree(mem);
	return export;
}

napi_value
_xmlNodeDumpOutput(napi_env env, napi_callback_info info)
{
	napi_status		status;
	size_t			argc = 6;
	napi_value		argv[6];
	napi_valuetype		vt;
	xmlOutputBufferPtr	buf;
	xmlDocPtr		doc;
	xmlNodePtr		cur;
	int32_t			level, format;
	char			encp[20], *encoding;

	// Get arguments
	status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read arguments");
		return NULL;
	}

	// Get xmlOutputBufferPtr
	status = napi_get_value_external(env, argv[0], (void **)&buf);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read "
		    "xmlNodeOutputBufferPtr at arg 0");
		return NULL;
	}

	// Get xmlDocPtr
	status = napi_get_value_external(env, argv[1], (void **)&doc);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read xmlDocPtr at arg 1");
		return NULL;
	}

	// Get xmlNodePtr
	status = napi_get_value_external(env, argv[2], (void **)&cur);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read xmlNodePtr at arg 2");
		return NULL;
	}

	// Get level
	status = napi_get_value_int32(env, argv[3], &level);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read level at arg 3");
		return NULL;
	}

	// Get format
	status = napi_get_value_int32(env, argv[4], &format);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read format at arg 4");
		return NULL;
	}

	// Get encoding
	status = napi_typeof(env, argv[5], &vt);
	if (vt == napi_undefined || vt == napi_null) {
		encoding = NULL;
	} else {
		status = napi_get_value_string_latin1(env, argv[5], encp,
		    20, NULL);
		if (status != napi_ok) {
			napi_throw_error(env, NULL, "Can't read encoding at "
			     "arg 5");
			return NULL;
		}
		encoding = encp;
	}

	// Exec
	xmlNodeDumpOutput(buf, doc, cur, level, format, encoding);

	return NULL;
}
