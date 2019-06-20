#ifndef _TREE_H_
#define _TREE_H_

#include <node_api.h>

napi_status	tree_init(napi_env, napi_value);
napi_value	_xmlDocGetRootElement(napi_env, napi_callback_info);
napi_value	_xmlNode_type(napi_env, napi_callback_info);
napi_value	_xmlNode_name(napi_env, napi_callback_info);
napi_value	_xmlNode_next(napi_env, napi_callback_info);
napi_value	_xmlNode_prev(napi_env, napi_callback_info);
napi_value	_xmlNode_parent(napi_env, napi_callback_info);
napi_value	_xmlNode_children(napi_env, napi_callback_info);
napi_value	_xmlNode_content(napi_env, napi_callback_info);
napi_value	_xmlNode_eq(napi_env, napi_callback_info);
napi_value	_xmlGetProp(napi_env, napi_callback_info);
napi_value	_xmlDocDumpMemory(napi_env, napi_callback_info);
napi_value	_xmlDoc_encoding(napi_env, napi_callback_info);
napi_value	_xmlNewNode(napi_env, napi_callback_info);
napi_value	_xmlNewNs(napi_env, napi_callback_info);
napi_value	_xmlSetNs(napi_env, napi_callback_info);
napi_value	_xmlAddNextSibling(napi_env, napi_callback_info);
napi_value	_xmlAddPrevSibling(napi_env, napi_callback_info);
napi_value	_xmlAddChild(napi_env, napi_callback_info);
napi_value	_xmlNewProp(napi_env, napi_callback_info);
napi_value	_xmlNodeAddContent(napi_env, napi_callback_info);
napi_value	_xmlNodeGetContent(napi_env, napi_callback_info);
napi_value	_xmlNodeDumpOutput(napi_env, napi_callback_info);

#endif
