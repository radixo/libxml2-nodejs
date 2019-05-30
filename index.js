"use strict";

exports = module.exports = require("./build/Release/xml2");

// Enum xmlParserOption
exports.XML_PARSE_RECOVER = 1; // recover on errors
exports.XML_PARSE_NOENT = 2; // substitute entities
exports.XML_PARSE_DTDLOAD = 4; // load the external subset
exports.XML_PARSE_DTDATTR = 8; // default DTD attributes
exports.XML_PARSE_DTDVALID = 16; // validate with the DTD
exports.XML_PARSE_NOERROR = 32; // suppress error reports
exports.XML_PARSE_NOWARNING = 64; // suppress warning reports
exports.XML_PARSE_PEDANTIC = 128; // pedantic error reporting
exports.XML_PARSE_NOBLANKS = 256; // remove blank nodes
exports.XML_PARSE_SAX1 = 512; // use the SAX1 interface internally
exports.XML_PARSE_XINCLUDE = 1024; // Implement XInclude substitition
exports.XML_PARSE_NONET = 2048; // Forbid network access
exports.XML_PARSE_NODICT = 4096; // Do not reuse the context dictionary
exports.XML_PARSE_NSCLEAN = 8192; // remove redundant namespaces declarations
exports.XML_PARSE_NOCDATA = 16384; // merge CDATA as text nodes
exports.XML_PARSE_NOXINCNODE = 32768; // do not generate XINCLUDE START/END
                                      // nodes
exports.XML_PARSE_COMPACT = 65536; // compact small text nodes; no modification
                                   // of the tree allowed afterwards (will
                                   // possibly crash if you try to modify the
                                   // tree)
exports.XML_PARSE_OLD10 = 131072; // parse using XML-1.0 before update 5
exports.XML_PARSE_NOBASEFIX = 262144; // do not fixup XINCLUDE xml:base uris
exports.XML_PARSE_HUGE = 524288; // relax any hardcoded limit from the parser
exports.XML_PARSE_OLDSAX = 1048576; // parse using SAX2 interface before 2.7.0
exports.XML_PARSE_IGNORE_ENC = 2097152; // ignore internal document encoding
                                        // hint
exports.XML_PARSE_BIG_LINES = 4194304; // Store big lines numbers in text PSVI
                                       // field
//

// Enum xmlC14NMode
exports.XML_C14N_1_0 = 0; // Origianal C14N 1.0 spec
exports.XML_C14N_EXCLUSIVE_1_0 = 1; // Exclusive C14N 1.0 spec
exports.XML_C14N_1_1 = 2; // C14N 1.1 spec
//

// Enum xmlElementType
exports.XML_ELEMENT_NODE = 1
exports.XML_ATTRIBUTE_NODE = 2
exports.XML_TEXT_NODE = 3
exports.XML_CDATA_SECTION_NODE = 4
exports.XML_ENTITY_REF_NODE = 5
exports.XML_ENTITY_NODE = 6
exports.XML_PI_NODE = 7
exports.XML_COMMENT_NODE = 8
exports.XML_DOCUMENT_NODE = 9
exports.XML_DOCUMENT_TYPE_NODE = 10
exports.XML_DOCUMENT_FRAG_NODE = 11
exports.XML_NOTATION_NODE = 12
exports.XML_HTML_DOCUMENT_NODE = 13
exports.XML_DTD_NODE = 14
exports.XML_ELEMENT_DECL = 15
exports.XML_ATTRIBUTE_DECL = 16
exports.XML_ENTITY_DECL = 17
exports.XML_NAMESPACE_DECL = 18
exports.XML_XINCLUDE_START = 19
exports.XML_XINCLUDE_END = 20
exports.XML_DOCB_DOCUMENT_NODE = 21
//
