#include <stdio.h>
#include <libxml/xpath.h>
#include <libxml/c14n.h>

#include "napi.h"
#include "c14n.h"

napi_status
c14n_init(napi_env env, napi_value exports)
{
	napi_status status;
	napi_value fn;

	NAPI_EXPORT_FN(status, env, xmlC14NDocDumpMemory, fn, exports);

	return napi_ok;
}

napi_value
_xmlC14NDocDumpMemory(napi_env env, napi_callback_info info)
{
	napi_status		status;
	napi_valuetype		vt;
	size_t			argc = 5;
	napi_value		argv[5], export;
	xmlDocPtr		doc;
	xmlNodeSetPtr		nset;
	int32_t			mode, with_comments;
	xmlChar			*inc_ns_prefixes, *doc_txt = NULL;
	int			ret;

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

	// Get xmlNodeSet
	status = napi_typeof(env, argv[1], &vt);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't get typeof arg 1");
		return NULL;
	}
	if (vt == napi_undefined || vt == napi_null) {
		nset = NULL;
	} else {
		status = napi_get_value_external(env, argv[1], (void **)&nset);
		if (status != napi_ok) {
			napi_throw_error(env, NULL, "Can't read xmlNodeSet at "
			    "arg 1");
			return NULL;
		}
	}

	// Get mode
	status = napi_get_value_int32(env, argv[2], &mode);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read mode at arg 2");
		return NULL;
	}

	// Get inclusive_ns_prefixes
	status = napi_typeof(env, argv[3], &vt);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't get typeof arg 3");
		return NULL;
	}
	if (vt != napi_null || vt != napi_undefined) {
		inc_ns_prefixes = NULL;
	} else {
		status = napi_get_value_string_latin1(env, argv[3], NULL, 0,
		    &argc);
		if (status != napi_ok) {
			napi_throw_error(env, NULL, "Can't read arg 3 len");
			return NULL;
		}
		argc++;
		inc_ns_prefixes = malloc(argc);
		if (inc_ns_prefixes == NULL) {
			napi_throw_error(env, NULL, "Can't read arg 3 value");
			return NULL;
		}
		status = napi_get_value_string_latin1(env, argv[3],
		    (char *)inc_ns_prefixes, argc, NULL);
		if (status != napi_ok) {
			napi_throw_error(env, NULL, "Can't read arg 3 value");
			free(inc_ns_prefixes);
			return NULL;
		}
	}

	// Get with_comments
	status = napi_get_value_int32(env, argv[4], &with_comments);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't read mode at arg 4");
		free(inc_ns_prefixes);
		return NULL;
	}

	// Exec xmlC14NDocDumpMemory
	ret = xmlC14NDocDumpMemory(doc, nset, mode, &inc_ns_prefixes,
	    with_comments, &doc_txt);
	if (ret < 0) {
		napi_throw_error(env, NULL, "Failed to canonicalize XML");
		if (doc_txt != NULL)
			xmlFree(doc_txt);
		free(inc_ns_prefixes);
		return NULL;
	}

	// create export
	status = napi_create_string_utf8(env, (char *)doc_txt, NAPI_AUTO_LENGTH,
	    &export);
	xmlFree(doc_txt);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't create external reference");
		return NULL;
	}

	return export;
}
