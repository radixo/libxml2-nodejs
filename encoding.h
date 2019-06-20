#ifndef _ENCODING_H_
#define _ENCODING_H_

#include <node_api.h>

napi_status	encoding_init(napi_env, napi_value);
napi_value	_xmlFindCharEncodingHandler(napi_env, napi_callback_info);

#endif
