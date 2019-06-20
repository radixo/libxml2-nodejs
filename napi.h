#ifndef _NAPI_H_
#define _NAPI_H_

#include <node_api.h>

#define NAPI_EXPORT_FN(STATUS, ENV, FN, VFN, EXPORTS)			  \
	STATUS = napi_create_function(ENV, NULL, 0, _ ## FN, NULL, &VFN); \
	if (STATUS != napi_ok)						  \
		return STATUS;						  \
	STATUS = napi_set_named_property(ENV, EXPORTS, #FN, VFN);	  \
	if (STATUS != napi_ok)						  \
		return STATUS;

#endif
