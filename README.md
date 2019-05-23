# libxml2-nodejs
A wrapper for libxml2 (or an attempt to)

## Installation
```bash
$ npm i libxml2-nodejs
```

## Documentation
- Not ready yet (help us)

## Usage example
```javascript
"use strict";

const xml = require("libxml2-nodejs");

// reading XML document
let doc = xml.xmlReadDoc(`<?xml version="1.0" encoding="UTF-8"?>
<ns1:ReqEnvioLoteRPS xmlns:ns1="http://localhost:8080/WsNFe2/lote"
 xmlns:tipos="http://localhost:8080/WsNFe2/tp"
 xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
 xsi:schemaLocation="http://localhost:8080/WsNFe2/lote
 http://localhost:8080/WsNFe2/xsd/ReqEnvioLoteRPS.xsd">
  <Cabecalho>
    <CodCidade>6291</CodCidade>
    <RazaoSocialRemetente>Superlogica Eventos LTDA</RazaoSocialRemetente>
    <transacao/>
    <ValorTotalDeducoes>0.00</ValorTotalDeducoes>
    <Versao>1</Versao>
  </Cabecalho>
  <Lote Id="lote:1ABCDZ">
    <RPS>
      <NumeroRPS>1531</NumeroRPS>
      <SituacaoRPS>N</SituacaoRPS>
      <SeriePrestacao>99</SeriePrestacao>
    </RPS>
  </Lote>
</ns1:ReqEnvioLoteRPS>`,
  null, null, xml.XML_PARSE_DTDATTR | xml.XML_PARSE_NOENT);


// Creating a XPath Context
let ctxt = xml.xmlXPathNewContext(doc);

// Get a node to Canonicalize
// Starting from doc root
let node = xml.xmlDocGetRootElement(doc);

// Position at children
node = xml.xmlNode_children(node);
// Get the secound (next) one
node = xml.xmlNode_next(node);

// Just print the node name
console.log(xml.xmlNode_name(node));

// Set node to the XPath Context
xml.xmlXPathContext_set_node(ctxt, node);

// Get XPath Object from Evaluating XPath Expression
let xpath = xml.xmlXPathEvalExpression("(.//. | .//@* | .//namespace::*)",
  ctxt);

// Get NodeSet from evaluated XPath Object
let nset = xml.xmlXPathObject_nodesetval(xpath);

// Finally Canonicalize
xml.xmlC14NDocDumpMemory(doc, nset, xml.XML_C14N_1_0, null, 0);
```

## Conclusion
It is only at the start of the wrapper and I'm trying to be close to C
interface.
