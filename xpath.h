#ifndef _XPATH_H_
#define _XPATH_H_

#include <node_api.h>

napi_status	xpath_init(napi_env, napi_value);
napi_value 	_xmlXPathNewContext(napi_env, napi_callback_info);
void		_xmlXPathNewContextFree(napi_env, void *, void *);

#endif
