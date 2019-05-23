#ifndef _PARSER_H_
#define _PARSER_H_

#include <node_api.h>

napi_status	parser_init(napi_env, napi_value);
napi_value	_xmlReadDoc(napi_env, napi_callback_info);
void		_xmlReadDocFree(napi_env, void *, void *);

#endif
