#ifndef _IO_H_
#define _IO_H_

#include <node_api.h>

napi_status	IO_init(napi_env, napi_value);
napi_value	_xmlAllocOutputBuffer(napi_env, napi_callback_info);
void		_xmlAllocOutputBufferFree(napi_env, void *, void *);
napi_value	_xmlOutputBufferFlush(napi_env, napi_callback_info);
napi_value	_xmlOutputBufferGetContent(napi_env, napi_callback_info);
napi_value	_xmlOutputBufferGetSize(napi_env, napi_callback_info);

#endif
