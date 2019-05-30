#ifndef _XPATH_H_
#define _XPATH_H_

napi_status	xpath_init(napi_env, napi_value);
napi_value	_xmlXPathNewContext(napi_env, napi_callback_info);
void		_xmlXPathNewContextFree(napi_env, void *, void *);
napi_value	_xmlXPathContext_set_node(napi_env, napi_callback_info);
napi_value	_xmlXPathEvalExpression(napi_env, napi_callback_info);
void		_xmlXPathObjectFree(napi_env, void *, void *);
napi_value	_xmlXPathObject_nodesetval(napi_env, napi_callback_info);
napi_value	_xmlXPathRegisterNs(napi_env, napi_callback_info);
napi_value	_xmlNodeSet_nodeNr(napi_env, napi_callback_info);
napi_value	_xmlNodeSet_nodeMax(napi_env, napi_callback_info);
napi_value	_xmlNodeSet_pos_nodeTab(napi_env, napi_callback_info);

#endif
