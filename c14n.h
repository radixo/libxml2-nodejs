#ifndef _C14N_H
#define _C14N_H

#include <node_api.h>

napi_status	c14n_init(napi_env, napi_value);
napi_value 	_xmlC14NDocDumpMemory(napi_env, napi_callback_info);

#endif
