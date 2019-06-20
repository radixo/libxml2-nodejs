#include <stdio.h>
#include <libxml/parser.h>

#include "napi.h"
#include "parser.h"

napi_status
parser_init(napi_env env, napi_value exports)
{
	napi_status status;
	napi_value fn;

	NAPI_EXPORT_FN(status, env, xmlReadDoc, fn, exports);

	return napi_ok;
}

/**
 * Parse a XML string and build a tree.
 * @name xmlReadDoc
 * @function
 * @param {string} cur XML Document string representation
 * @param {string} URL The base URL to use for the document
 * @param {string} encoding The document encoding, or null
 * @param {number} options A combination of xmlParserOptions
 * @return {xmlDocPtr} The resulting document tree
 */
napi_value
_xmlReadDoc(napi_env env, napi_callback_info info)
{
	napi_status 			status;
	napi_valuetype			vt;
	size_t 				argc = 4, strl;
	napi_value 			argv[4], export;
	xmlChar 			*cur;
	char 				*url = NULL, encoding[30];
	int64_t				opts;
	xmlDocPtr			doc;
	int				urlN, encodingN;

	// Get arguments
	status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
	if (status != napi_ok)
		return NULL;

	if (argc != 4) {
		napi_throw_error(env, NULL, "You must provide all arguments: "
		    "'cur', 'URL', 'encoding', 'opts'");
		return NULL;
	}

	// Check types
	status = napi_typeof(env, argv[0], &vt);
	if (vt != napi_string) {
		napi_throw_error(env, NULL, "'cur' must to be of type string");
		return NULL;
	}
	status = napi_typeof(env, argv[1], &vt);
	urlN = (vt == napi_null);
	if (vt != napi_string && !urlN) {
		napi_throw_error(env, NULL, "'URL' must to be of type null or "
		    "string");
		return NULL;
	}
	status = napi_typeof(env, argv[2], &vt);
	encodingN = (vt == napi_null);
	if (vt != napi_string && !encodingN) {
		napi_throw_error(env, NULL, "'encoding' must to be of type "
		    "null or string");
		return NULL;
	}
	status = napi_typeof(env, argv[3], &vt);
	if (vt != napi_number) {
		napi_throw_error(env, NULL, "'opts' must to be of type int");
		return NULL;
	}

	// Get xml buffer
	status = napi_get_value_string_latin1(env, argv[0], NULL, 0, &strl);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't get cur buffer size");
		return NULL;
	}
	strl++;
	cur = BAD_CAST malloc(strl);
	status = napi_get_value_string_latin1(env, argv[0], (char *)cur, strl,
	    NULL);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't get cur buffer");
		free(cur);
		return NULL;
	}

	// Get url
	if (!urlN) {
		status = napi_get_value_string_latin1(env, argv[1], NULL, 0,
		    &strl);
		if (status != napi_ok) {
			napi_throw_error(env, NULL, "Can't get URL buffer "
			    "size");
			free(cur);
			return NULL;
		}
		strl++;
		url = (char *)malloc(strl);
		status = napi_get_value_string_latin1(env, argv[1], url, strl,
		    NULL);
		if (status != napi_ok) {
			napi_throw_error(env, NULL, "Can't get URL buffer");
			free(cur);
			free(url);
			return NULL;
		}
	}

	// Get encoding
	if (!encodingN) {
		status = napi_get_value_string_latin1(env, argv[2], encoding,
		    30, NULL);
		if (status != napi_ok) {
			napi_throw_error(env, NULL, "Can't get encoding "
			    "buffer");
			free(cur);
			free(url);
			return NULL;
		}
	}

	// Get options
	status = napi_get_value_int64(env, argv[3], &opts);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't get opts");
		free(cur);
		free(url);
		return NULL;
	}

	// Create xmlDocPtr
	doc = xmlReadDoc(cur, urlN ? NULL : url, encodingN ? NULL : encoding,
	    opts);
	if (doc == NULL) {
		napi_throw_error(env, NULL, "Error on parse");
		free(cur);
		free(url);

		return NULL;
	} 

	// parse gone ok, lets create the object
	free(cur);
	free(url);

	// creating doc external
	status = napi_create_external(env, doc, _xmlReadDocFree, NULL, &export);
	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Can't create external reference");
		xmlFreeDoc(doc);
		return NULL;
	}

	return export;
}

void
_xmlReadDocFree(napi_env env, void *finalize_data, void *finalize_hint)
{
	//
	xmlFreeDoc(finalize_data);
}
