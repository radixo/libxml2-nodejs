## Functions

<dl>
<dt><a href="#xmlReadDoc">xmlReadDoc(cur, URL, encoding, options)</a> ⇒ <code>xmlDocPtr</code></dt>
<dd><p>Parse a XML string and build a tree.</p>
</dd>
<dt><a href="#xmlDocGetRootElement">xmlDocGetRootElement(doc)</a> ⇒ <code>xmlNodePtr</code></dt>
<dd><p>Get the root element of the document.</p>
</dd>
</dl>

<a name="xmlReadDoc"></a>

## xmlReadDoc(cur, URL, encoding, options) ⇒ <code>xmlDocPtr</code>
Parse a XML string and build a tree.

**Kind**: global function  
**Returns**: <code>xmlDocPtr</code> - The resulting document tree  

| Param | Type | Description |
| --- | --- | --- |
| cur | <code>string</code> | XML Document string representation |
| URL | <code>string</code> | The base URL to use for the document |
| encoding | <code>string</code> | The document encoding, or null |
| options | <code>number</code> | A combination of xmlParserOptions |

<a name="xmlDocGetRootElement"></a>

## xmlDocGetRootElement(doc) ⇒ <code>xmlNodePtr</code>
Get the root element of the document.

**Kind**: global function  
**Returns**: <code>xmlNodePtr</code> - the #xmlNodePtr for the root or undefined  

| Param | Type | Description |
| --- | --- | --- |
| doc | <code>xmlDocPtr</code> | The document |

