#ifndef _XPATH_H_
#define _XPATH_H_

#include <node_api.h>

napi_status	xpath_init(napi_env, napi_value);
napi_value	_xmlXPathNewContext(napi_env, napi_callback_info);
void		_xmlXPathNewContextFree(napi_env, void *, void *);
napi_value	_xmlXPathContext_set_node(napi_env, napi_callback_info);
napi_value	_xmlXPathEvalExpression(napi_env, napi_callback_info);
void		_xmlXPathObjectFree(napi_env, void *, void *);
napi_value	_xmlXPathObject_nodesetval(napi_env, napi_callback_info);

#endif
