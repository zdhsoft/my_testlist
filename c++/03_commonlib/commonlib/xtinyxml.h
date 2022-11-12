/*
www.sourceforge.net/projects/tinyxml
Original code (2.0 and earlier )copyright (c) 2000-2006 Lee Thomason (www.grinninglizard.com)

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any
damages arising from the use of this software.

Permission is granted to anyone to use this software for any
purpose, including commercial applications, and to alter it and
redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must
not claim that you wrote the original software. If you use this
software in a product, an acknowledgment in the product documentation
would be appreciated but is not required.

2. Altered source versions must be plainly marked as such, and
must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.


*/


#ifndef XTinyXMLH
#define XTinyXMLH
#include <iostream>
#include <sstream>
#include <xtype.h>
#include <xos_include.h>
#if IS_BCB
    #include <ctype.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <assert.h>
    #include <string.h>
#else
    #include <cctype>
    #include <cstdio>
    #include <cstdlib>
    #include <cstring>
    #include <cassert>
#endif
#include <xstring.h>
#include <xdatetime.h>

namespace zdh
{
    const XInt TIXML_MAJOR_VERSION = 2;
    const XInt TIXML_MINOR_VERSION = 6;
    const XInt TIXML_PATCH_VERSION = 1;

    class TiXmlDocument;
    class TiXmlElement;
    class TiXmlComment;
    class TiXmlUnknown;
    class TiXmlAttribute;
    class TiXmlText;
    class TiXmlDeclaration;
    class TiXmlParsingData;

    /*  Internal structure for tracking location of items 
        in the XML file.
    */
    struct TiXmlCursor
    {
        TiXmlCursor():row(-1),col(-1){}
        void Clear()
        { 
            row = -1;
            col = -1; 
        }
        XInt row;   // 0 based.
        XInt col;   // 0 based.
    };

    
    /**
        If you call the Accept() method, it requires being passed a TiXmlVisitor
        class to handle callbacks. For nodes that contain other nodes (Document, Element)
        you will get called with a VisitEnter/VisitExit pair. Nodes that are always leaves
        are simple called with Visit().
    
        If you return 'true' from a Visit method, recursive parsing will continue. If you return
        false, <b>no children of this node or its sibilings</b> will be Visited.
    
        All flavors of Visit methods have a default implementation that returns 'true' (continue 
        visiting). You need to only override methods that are interesting to you.
    
        Generally Accept() is called on the TiXmlDocument, although all nodes suppert Visiting.
    
        You should never change the document from a callback.
    
        @sa TiXmlNode::Accept()
    */
    class TiXmlVisitor
    {
    public:
        virtual ~TiXmlVisitor() {}
    
        /// Visit a document.
        virtual bool VisitEnter( const TiXmlDocument& doc );
        /// Visit a document.
        virtual bool VisitExit( const TiXmlDocument& doc );
    
        /// Visit an element.
        virtual bool VisitEnter( const TiXmlElement& element, const TiXmlAttribute* firstAttribute );
        /// Visit an element.
        virtual bool VisitExit( const TiXmlElement& element );
    
        /// Visit a declaration
        virtual bool Visit( const TiXmlDeclaration& declaration );
        /// Visit a text node
        virtual bool Visit( const TiXmlText& text );
        /// Visit a comment node
        virtual bool Visit( const TiXmlComment& comment );
        /// Visit an unknow node
        virtual bool Visit( const TiXmlUnknown& unknown );
    };
    
    // Only used by Attribute::Query functions
    enum 
    { 
        TIXML_SUCCESS,
        TIXML_NO_ATTRIBUTE,
        TIXML_WRONG_TYPE
    };
    
    
    // Used by the parsing routines.
    enum TiXmlEncoding
    {
        TIXML_ENCODING_UNKNOWN,
        TIXML_ENCODING_UTF8,
        TIXML_ENCODING_LEGACY
    };
    
    const TiXmlEncoding TIXML_DEFAULT_ENCODING = TIXML_ENCODING_UNKNOWN;
    
    /** TiXmlBase is a base class for every class in TinyXml.
        It does little except to establish that TinyXml classes
        can be printed and provide some utility functions.
    
        In XML, the document and elements can contain
        other elements and other types of nodes.
    
        @verbatim
        A Document can contain: Element (container or leaf)
                                Comment (leaf)
                                Unknown (leaf)
                                Declaration( leaf )
    
        An Element can contain: Element (container or leaf)
                                Text    (leaf)
                                Attributes (not on tree)
                                Comment (leaf)
                                Unknown (leaf)
    
        A Decleration contains: Attributes (not on tree)
        @endverbatim
    */
    class TiXmlBase
    {
        friend class TiXmlNode;
        friend class TiXmlElement;
        friend class TiXmlDocument;
    
    public:
        TiXmlBase() :   userData(0)     {}
        virtual ~TiXmlBase()            {}
    
        /** All TinyXml classes can print themselves to a filestream
            or the string class (TiXmlString in non-STL mode, XAnsiString
            in STL mode.) Either or both cfile and str can be null.
            
            This is a formatted print, and will insert 
            tabs and newlines.
            
            (For an unformatted stream, use the << operator.)
        */
        virtual void Print( FILE* cfile, XInt depth ) const = 0;
        virtual void Print(XAnsiString & strOut,XInt depth ) const = 0;
       
    
        /** The world does not agree on whether white space should be kept or
            not. In order to make everyone happy, these global, static functions
            are provided to set whether or not TinyXml will condense all white space
            into a single space or not. The default is to condense. Note changing this
            value is not thread safe.
        */
        static void SetCondenseWhiteSpace( bool condense )      { condenseWhiteSpace = condense; }
    
        /// Return the current white space setting.
        static bool IsWhiteSpaceCondensed()                     { return condenseWhiteSpace; }
    
        /** Return the position, in the original source file, of this node or attribute.
            The row and column are 1-based. (That is the first row and first column is
            1,1). If the returns values are 0 or less, then the parser does not have
            a row and column value.
    
            Generally, the row and column value will be set when the TiXmlDocument::Load(),
            TiXmlDocument::LoadFile(), or any TiXmlNode::Parse() is called. It will NOT be set
            when the DOM was created from operator>>.
    
            The values reflect the initial load. Once the DOM is modified programmatically
            (by adding or changing nodes and attributes) the new values will NOT update to
            reflect changes in the document.
    
            There is a minor performance cost to computing the row and column. Computation
            can be disabled if TiXmlDocument::SetTabSize() is called with 0 as the value.
    
            @sa TiXmlDocument::SetTabSize()
        */
        XInt Row() const            { return location.row + 1; }
        XInt Column() const     { return location.col + 1; }    ///< See Row()
    
        void  SetUserData( void* user )         { userData = user; }    ///< Set a pointer to arbitrary user data.
        void* GetUserData()                     { return userData; }    ///< Get a pointer to arbitrary user data.
        const void* GetUserData() const         { return userData; }    ///< Get a pointer to arbitrary user data.
    
        // Table that returs, for a given lead byte, the total number of bytes
        // in the UTF-8 sequence.
        static const XInt utf8ByteTable[256];
    
        virtual const XChar* Parse( const XChar* p, 
                                    TiXmlParsingData* data, 
                                    TiXmlEncoding encoding /*= TIXML_ENCODING_UNKNOWN */ ) = 0;
    
        enum
        {
            TIXML_NO_ERROR = 0,
            TIXML_ERROR,
            TIXML_ERROR_OPENING_FILE,
            TIXML_ERROR_OUT_OF_MEMORY,
            TIXML_ERROR_PARSING_ELEMENT,
            TIXML_ERROR_FAILED_TO_READ_ELEMENT_NAME,
            TIXML_ERROR_READING_ELEMENT_VALUE,
            TIXML_ERROR_READING_ATTRIBUTES,
            TIXML_ERROR_PARSING_EMPTY,
            TIXML_ERROR_READING_END_TAG,
            TIXML_ERROR_PARSING_UNKNOWN,
            TIXML_ERROR_PARSING_COMMENT,
            TIXML_ERROR_PARSING_DECLARATION,
            TIXML_ERROR_DOCUMENT_EMPTY,
            TIXML_ERROR_EMBEDDED_NULL,
            TIXML_ERROR_PARSING_CDATA,
            TIXML_ERROR_DOCUMENT_TOP_ONLY,
    
            TIXML_ERROR_STRING_COUNT
        };
    
    protected:
    
        static const XChar* SkipWhiteSpace( const XChar*, TiXmlEncoding encoding );
        inline static bool IsWhiteSpace( XChar c )      
        { 
            return ( isspace( (XByte) c ) || c == '\n' || c == '\r' ); 
        }
        inline static bool IsWhiteSpace( XInt c )
        {
            if ( c < 256 )
                return IsWhiteSpace( (XChar) c );
            return false;   // Again, only truly correct for English/Latin...but usually works.
        }
    
        static bool StreamWhiteSpace( std::istream * in, XAnsiString * tag );
        static bool StreamTo( std::istream * in, XInt character, XAnsiString * tag );
    
        /*  Reads an XML name into the string provided. Returns
            a pointer just past the last character of the name,
            or 0 if the function has an error.
        */
        static const XChar* ReadName( const XChar* p, XAnsiString* name, TiXmlEncoding encoding );
    
        /*  Reads text. Returns a pointer past the given end tag.
            Wickedly complex options, but it keeps the (sensitive) code in one place.
        */
        static const XChar* ReadText(   const XChar* in,                // where to start
                                        XAnsiString* text,          // the string read
                                        bool ignoreWhiteSpace,      // whether to keep the white space
                                        const XChar* endTag,            // what ends this text
                                        bool ignoreCase,            // whether to ignore case in the end tag
                                        TiXmlEncoding encoding );   // the current encoding
    
        // If an entity has been found, transform it into a character.
        static const XChar* GetEntity( const XChar* in, XChar* value, XInt* length, TiXmlEncoding encoding );
    
        // Get a character, while interpreting entities.
        // The length can be from 0 to 4 bytes.
        static const XChar* GetChar( const XChar* p, XChar* _value, XInt* length, TiXmlEncoding encoding );
    /*  {
            ZDH_ASSERT( p );
            if ( encoding == TIXML_ENCODING_UTF8 )
            {
                *length = utf8ByteTable[ *((const XByte*)p) ];
                ZDH_ASSERT( *length >= 0 && *length < 5 );
            }
            else
            {
                *length = 1;
            }
    
            if ( *length == 1 )
            {
                if ( *p == '&' )
                    return GetEntity( p, _value, length, encoding );
                *_value = *p;
                return p+1;
            }
            else if ( *length )
            {
                for( XInt i=0; p[i] && i<*length; ++i ) {
                    _value[i] = p[i];
                }
                return p + (*length);
            }
            else
            {
                // Not valid text.
                return 0;
            }
        }
     */
        // Puts a string to a stream, expanding entities as it goes.
        // Note this should not contian the '<', '>', etc, or they will be transformed into entities!
        static void PutString( const XAnsiString& str, XAnsiString* out );
    
        // Return true if the next characters in the stream are any of the endTag sequences.
        // Ignore case only works for english, and should only be relied on when comparing
        // to English words: StringEqual( p, "version", true ) is fine.
        static bool StringEqual(    const XChar* p,
                                    const XChar* endTag,
                                    bool ignoreCase,
                                    TiXmlEncoding encoding );
    
        static const XChar* errorString[ TIXML_ERROR_STRING_COUNT ];
    
        TiXmlCursor location;
    
        /// Field containing a generic user pointer
        void*           userData;
        
        // None of these methods are reliable for any language except English.
        // Good for approximation, not great for accuracy.
        static XInt IsAlpha( XByte anyByte, TiXmlEncoding encoding );
        static XInt IsAlphaNum( XByte anyByte, TiXmlEncoding encoding );
        inline static XInt ToLower( XInt v, TiXmlEncoding encoding )
        {
            if ( encoding == TIXML_ENCODING_UTF8 )
            {
                if ( v < 128 ) return tolower( v );
                return v;
            }
            else
            {
                return tolower( v );
            }
        }
        static void ConvertUTF32ToUTF8( unsigned long input, XChar* output, XInt* length );
    
    private:
        TiXmlBase( const TiXmlBase& );              // not implemented.
        void operator=( const TiXmlBase& base );    // not allowed.
    
        struct Entity
        {
            const XChar * str;
            XDWord  strLength;
            XChar chr;
        };
        enum
        {
            NUM_ENTITY = 5,
            MAX_ENTITY_LENGTH = 6
    
        };
        static Entity entity[ NUM_ENTITY ];
        static bool condenseWhiteSpace;
    };
    
    /** The parent class for everything in the Document Object Model.
        (Except for attributes).
        Nodes have siblings, a parent, and children. A node can be
        in a document, or stand on its own. The type of a TiXmlNode
        can be queried, and it can be cast to its more defined type.
    */
    class TiXmlNode : public TiXmlBase
    {
        friend class TiXmlDocument;
        friend class TiXmlElement;
    
    public:
        
    
        /** An input stream operator, for every class. Tolerant of newlines and
            formatting, but doesn't expect them.
        */
        friend std::istream& operator >> (std::istream& in, TiXmlNode& base);

        /** An output stream operator, for every class. Note that this outputs
            without any newlines or formatting, as opposed to Print(), which
            includes tabs and new lines.

            The operator<< and operator>> are not completely symmetric. Writing
            a node to a stream is very well defined. You'll get a nice stream
            of output, without any extra whitespace or newlines.
            
            But reading is not as well defined. (As it always is.) If you create
            a TiXmlElement (for example) and read that from an input stream,
            the text needs to define an element or junk will result. This is
            true of all input streams, but it's worth keeping in mind.

            A TiXmlDocument will read nodes until it reads a root element, and
            all the children of that root element.
        */  
        friend std::ostream& operator<< (std::ostream& out, const TiXmlNode& base);

        /// Appends the XML node or attribute to a XAnsiString.
        friend XAnsiString& operator<< (XAnsiString& out, const TiXmlNode& base );
    
        
    
        /** The types of XML nodes supported by TinyXml. (All the
                unsupported types are picked up by UNKNOWN.)
        */
        enum NodeType
        {
            DOCUMENT,
            ELEMENT,
            COMMENT,
            UNKNOWN,
            TEXT,
            DECLARATION,
            TYPECOUNT
        };
    
        virtual ~TiXmlNode();
    
        /** The meaning of 'value' changes for the specific type of
            TiXmlNode.
            @verbatim
            Document:   filename of the xml file
            Element:    name of the element
            Comment:    the comment text
            Unknown:    the tag contents
            Text:       the text string
            @endverbatim
    
            The subclasses will wrap this function.
        */
        const XChar *Value() const { return value.c_str (); }
    
        
        /** Return Value() as a XAnsiString. If you only use STL,
            this is more efficient than calling Value().
            Only available in STL mode.
        */
        const XAnsiString& ValueStr() const { return value; }
        
    
        /** Changes the value of the node. Defined as:
            @verbatim
            Document:   filename of the xml file
            Element:    name of the element
            Comment:    the comment text
            Unknown:    the tag contents
            Text:       the text string
            @endverbatim
        */
        void SetValue(const XChar * _value) { value = _value;}
    
        
        /// STL XAnsiString form.
        void SetValue( const XAnsiString& _value )  { value = _value; }
        
    
        /// Delete all the children of this node. Does not affect 'this'.
        void Clear();
    
        /// One step up the DOM.
        TiXmlNode* Parent()                         { return parent; }
        const TiXmlNode* Parent() const             { return parent; }
    
        const TiXmlNode* FirstChild()   const   { return firstChild; }      ///< The first child of this node. Will be null if there are no children.
        TiXmlNode* FirstChild()                 { return firstChild; }
        const TiXmlNode* FirstChild( const XChar * value ) const;           ///< The first child of this node with the matching 'value'. Will be null if none found.
        /// The first child of this node with the matching 'value'. Will be null if none found.
        TiXmlNode* FirstChild( const XChar * _value ) {
            // Call through to the const version - safe since nothing is changed. Exiting syntax: cast this to a const (always safe)
            // call the method, cast the return back to non-const.
            return const_cast< TiXmlNode* > ((const_cast< const TiXmlNode* >(this))->FirstChild( _value ));
        }
        const TiXmlNode* LastChild() const  { return lastChild; }       /// The last child of this node. Will be null if there are no children.
        TiXmlNode* LastChild()  { return lastChild; }
        
        const TiXmlNode* LastChild( const XChar * value ) const;            /// The last child of this node matching 'value'. Will be null if there are no children.
        TiXmlNode* LastChild( const XChar * _value ) {
            return const_cast< TiXmlNode* > ((const_cast< const TiXmlNode* >(this))->LastChild( _value ));
        }
    
        
        const TiXmlNode* FirstChild( const XAnsiString& _value ) const  {   return FirstChild (_value.c_str ());    }   ///< STL XAnsiString form.
        TiXmlNode* FirstChild( const XAnsiString& _value )              {   return FirstChild (_value.c_str ());    }   ///< STL XAnsiString form.
        const TiXmlNode* LastChild( const XAnsiString& _value ) const   {   return LastChild (_value.c_str ()); }   ///< STL XAnsiString form.
        TiXmlNode* LastChild( const XAnsiString& _value )               {   return LastChild (_value.c_str ()); }   ///< STL XAnsiString form.
        
    
        /** An alternate way to walk the children of a node.
            One way to iterate over nodes is:
            @verbatim
                for( child = parent->FirstChild(); child; child = child->NextSibling() )
            @endverbatim
    
            IterateChildren does the same thing with the syntax:
            @verbatim
                child = 0;
                while( child = parent->IterateChildren( child ) )
            @endverbatim
    
            IterateChildren takes the previous child as input and finds
            the next one. If the previous child is null, it returns the
            first. IterateChildren will return null when done.
        */
        const TiXmlNode* IterateChildren( const TiXmlNode* previous ) const;
        TiXmlNode* IterateChildren( TiXmlNode* previous ) {
            return const_cast< TiXmlNode* >( (const_cast< const TiXmlNode* >(this))->IterateChildren( previous ) );
        }
    
        /// This flavor of IterateChildren searches for children with a particular 'value'
        const TiXmlNode* IterateChildren( const XChar * value, const TiXmlNode* previous ) const;
        TiXmlNode* IterateChildren( const XChar * _value, TiXmlNode* previous ) {
            return const_cast< TiXmlNode* >( const_cast< const TiXmlNode* >(this)->IterateChildren( _value, previous ) );
        }
    
        
        const TiXmlNode* IterateChildren( const XAnsiString& _value, const TiXmlNode* previous ) const  {   return IterateChildren (_value.c_str (), previous); }   ///< STL XAnsiString form.
        TiXmlNode* IterateChildren( const XAnsiString& _value, TiXmlNode* previous ) {  return IterateChildren (_value.c_str (), previous); }   ///< STL XAnsiString form.
        
    
        /** Add a new node related to this. Adds a child past the LastChild.
            Returns a pointer to the new object or NULL if an error occured.
        */
        TiXmlNode* InsertEndChild( const TiXmlNode& addThis );
    
    
        /** Add a new node related to this. Adds a child past the LastChild.
    
            NOTE: the node to be added is passed by pointer, and will be
            henceforth owned (and deleted) by tinyXml. This method is efficient
            and avoids an extra copy, but should be used with care as it
            uses a different memory model than the other insert functions.
    
            @sa InsertEndChild
        */
        TiXmlNode* LinkEndChild( TiXmlNode* addThis );
    
        /** Add a new node related to this. Adds a child before the specified child.
            Returns a pointer to the new object or NULL if an error occured.
        */
        TiXmlNode* InsertBeforeChild( TiXmlNode* beforeThis, const TiXmlNode& addThis );
    
        /** Add a new node related to this. Adds a child after the specified child.
            Returns a pointer to the new object or NULL if an error occured.
        */
        TiXmlNode* InsertAfterChild(  TiXmlNode* afterThis, const TiXmlNode& addThis );
    
        /** Replace a child of this node.
            Returns a pointer to the new object or NULL if an error occured.
        */
        TiXmlNode* ReplaceChild( TiXmlNode* replaceThis, const TiXmlNode& withThis );
    
        /// Delete a child of this node.
        bool RemoveChild( TiXmlNode* removeThis );
    
        /// Navigate to a sibling node.
        const TiXmlNode* PreviousSibling() const            { return prev; }
        TiXmlNode* PreviousSibling()                        { return prev; }
    
        /// Navigate to a sibling node.
        const TiXmlNode* PreviousSibling( const XChar * ) const;
        TiXmlNode* PreviousSibling( const XChar *_prev ) {
            return const_cast< TiXmlNode* >( const_cast< const TiXmlNode* >(this)->PreviousSibling( _prev ) );
        }
    
        const TiXmlNode* PreviousSibling( const XAnsiString& _value ) const {   return PreviousSibling (_value.c_str ());   }   ///< STL XAnsiString form.
        TiXmlNode* PreviousSibling( const XAnsiString& _value )             {   return PreviousSibling (_value.c_str ());   }   ///< STL XAnsiString form.
        const TiXmlNode* NextSibling( const XAnsiString& _value) const      {   return NextSibling (_value.c_str ());   }   ///< STL XAnsiString form.
        TiXmlNode* NextSibling( const XAnsiString& _value)                  {   return NextSibling (_value.c_str ());   }   ///< STL XAnsiString form.
    
        /// Navigate to a sibling node.
        const TiXmlNode* NextSibling() const                { return next; }
        TiXmlNode* NextSibling()                            { return next; }
    
        /// Navigate to a sibling node with the given 'value'.
        const TiXmlNode* NextSibling( const XChar * ) const;
        TiXmlNode* NextSibling( const XChar* _next ) {
            return const_cast< TiXmlNode* >( const_cast< const TiXmlNode* >(this)->NextSibling( _next ) );
        }
    
        /** Convenience function to get through elements.
            Calls NextSibling and ToElement. Will skip all non-Element
            nodes. Returns 0 if there is not another element.
        */
        const TiXmlElement* NextSiblingElement() const;
        TiXmlElement* NextSiblingElement() {
            return const_cast< TiXmlElement* >( const_cast< const TiXmlNode* >(this)->NextSiblingElement() );
        }
    
        /** Convenience function to get through elements.
            Calls NextSibling and ToElement. Will skip all non-Element
            nodes. Returns 0 if there is not another element.
        */
        const TiXmlElement* NextSiblingElement( const XChar * ) const;
        TiXmlElement* NextSiblingElement( const XChar *_next ) {
            return const_cast< TiXmlElement* >( const_cast< const TiXmlNode* >(this)->NextSiblingElement( _next ) );
        }
    
        const TiXmlElement* NextSiblingElement( const XAnsiString& _value) const    {   return NextSiblingElement (_value.c_str ());    }   ///< STL XAnsiString form.
        TiXmlElement* NextSiblingElement( const XAnsiString& _value)                {   return NextSiblingElement (_value.c_str ());    }   ///< STL XAnsiString form.
    
        /// Convenience function to get through elements.
        const TiXmlElement* FirstChildElement() const;
        TiXmlElement* FirstChildElement() {
            return const_cast< TiXmlElement* >( const_cast< const TiXmlNode* >(this)->FirstChildElement() );
        }
    
        /// Convenience function to get through elements.
        const TiXmlElement* FirstChildElement( const XChar * _value ) const;
        TiXmlElement* FirstChildElement( const XChar * _value ) {
            return const_cast< TiXmlElement* >( const_cast< const TiXmlNode* >(this)->FirstChildElement( _value ) );
        }
    
        const TiXmlElement* FirstChildElement( const XAnsiString& _value ) const    {   return FirstChildElement (_value.c_str ()); }   ///< STL XAnsiString form.
        TiXmlElement* FirstChildElement( const XAnsiString& _value )                {   return FirstChildElement (_value.c_str ()); }   ///< STL XAnsiString form.
    
        /** Query the type (as an enumerated value, above) of this node.
            The possible types are: DOCUMENT, ELEMENT, COMMENT,
                                    UNKNOWN, TEXT, and DECLARATION.
        */
        XInt Type() const   { return type; }
    
        /** Return a pointer to the Document this node lives in.
            Returns null if not in a document.
        */
        const TiXmlDocument* GetDocument() const;
        TiXmlDocument* GetDocument() {
            return const_cast< TiXmlDocument* >( const_cast< const TiXmlNode* >(this)->GetDocument() );
        }
    
        /// Returns true if this node has no children.
        bool NoChildren() const                     { return !firstChild; }
    
        virtual const TiXmlDocument*    ToDocument()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
        virtual const TiXmlElement*     ToElement()     const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
        virtual const TiXmlComment*     ToComment()     const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
        virtual const TiXmlUnknown*     ToUnknown()     const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
        virtual const TiXmlText*        ToText()        const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
        virtual const TiXmlDeclaration* ToDeclaration() const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
    
        virtual TiXmlDocument*          ToDocument()    { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
        virtual TiXmlElement*           ToElement()     { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
        virtual TiXmlComment*           ToComment()     { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
        virtual TiXmlUnknown*           ToUnknown()     { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
        virtual TiXmlText*              ToText()        { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
        virtual TiXmlDeclaration*       ToDeclaration() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
    
        /** Create an exact duplicate of this node and return it. The memory must be deleted
            by the caller. 
        */
        virtual TiXmlNode* Clone() const = 0;
    
        /** Accept a hierchical visit the nodes in the TinyXML DOM. Every node in the 
            XML tree will be conditionally visited and the host will be called back
            via the TiXmlVisitor interface.
    
            This is essentially a SAX interface for TinyXML. (Note however it doesn't re-parse
            the XML for the callbacks, so the performance of TinyXML is unchanged by using this
            interface versus any other.)
    
            The interface has been based on ideas from:
    
            - http://www.saxproject.org/
            - http://c2.com/cgi/wiki?HierarchicalVisitorPattern 
    
            Which are both good references for "visiting".
    
            An example of using Accept():
            @verbatim
            TiXmlPrinter printer;
            tinyxmlDoc.Accept( &printer );
            const XChar* xmlcstr = printer.CStr();
            @endverbatim
        */
        virtual bool Accept( TiXmlVisitor* visitor ) const = 0;
    
    protected:
        TiXmlNode( NodeType _type );
    
        // Copy to the allocated object. Shared functionality between Clone, Copy constructor,
        // and the assignment operator.
        void CopyTo( TiXmlNode* target ) const;
    
            // The real work of the input operator.
        virtual void StreamIn( std::istream* in, XAnsiString* tag ) = 0;
    
        // Figure out what is at *p, and parse it. Returns null if it is not an xml node.
        TiXmlNode* Identify( const XChar* start, TiXmlEncoding encoding );
    
        TiXmlNode*      parent;
        NodeType        type;
    
        TiXmlNode*      firstChild;
        TiXmlNode*      lastChild;
    
        XAnsiString value;
    
        TiXmlNode*      prev;
        TiXmlNode*      next;
    
    private:
        TiXmlNode( const TiXmlNode& );              // not implemented.
        void operator=( const TiXmlNode& base );    // not allowed.
    };
    
    /** An attribute is a name-value pair. Elements have an arbitrary
        number of attributes, each with a unique name.
    
        @note The attributes are not TiXmlNodes, since they are not
              part of the tinyXML document object model. There are other
              suggested ways to look at this problem.
    */
    class TiXmlAttribute : public TiXmlBase
    {
        friend class TiXmlAttributeSet;
    
    public:
        /// Construct an empty attribute.
        TiXmlAttribute() : TiXmlBase()
        {
            document = 0;
            prev = next = 0;
        }
    
        /// XAnsiString constructor.
        TiXmlAttribute( const XAnsiString& _name, const XAnsiString& _value )
        {
            name = _name;
            value = _value;
            document = 0;
            prev = next = 0;
        }

    
        /// Construct an attribute with a name and value.
        TiXmlAttribute( const XChar * _name, const XChar * _value )
        {
            name = _name;
            value = _value;
            document = 0;
            prev = next = 0;
        }
    
        const XChar*        Name()  const       { return name.c_str(); }        ///< Return the name of this attribute.
        const XChar*        Value() const       { return value.c_str(); }       ///< Return the value of this attribute.
        const XAnsiString& ValueStr() const { return value; }               ///< Return the value of this attribute.
        XInt                IntValue() const;                                   ///< Return the value of this attribute, converted to an integer.
        double          DoubleValue() const;                                ///< Return the value of this attribute, converted to a double.
    
        // Get the tinyxml string representation
        const XAnsiString& NameStr() const { return name; }
    
        /** QueryIntValue examines the value string. It is an alternative to the
            IntValue() method with richer error checking.
            If the value is an integer, it is stored in 'value' and 
            the call returns TIXML_SUCCESS. If it is not
            an integer, it returns TIXML_WRONG_TYPE.
    
            A specialized but useful call. Note that for success it returns 0,
            which is the opposite of almost all other TinyXml calls.
        */
        XInt QueryIntValue( XInt* _value ) const;
        /// QueryDoubleValue examines the value string. See QueryIntValue().
        XInt QueryDoubleValue( double* _value ) const;
    
        void SetName( const XChar* _name )  { name = _name; }               ///< Set the name of this attribute.
        void SetValue( const XChar* _value )    { value = _value; }             ///< Set the value.
    
        void SetIntValue( XInt _value );                                        ///< Set the value from an integer.
        void SetDoubleValue( double _value );                               ///< Set the value from a double.
    
        /// STL XAnsiString form.
        void SetName( const XAnsiString& _name )    { name = _name; }   
        /// STL XAnsiString form.   
        void SetValue( const XAnsiString& _value )  { value = _value; }
    
        /// Get the next sibling attribute in the DOM. Returns null at end.
        const TiXmlAttribute* Next() const;
        TiXmlAttribute* Next() {
            return const_cast< TiXmlAttribute* >( const_cast< const TiXmlAttribute* >(this)->Next() ); 
        }
    
        /// Get the previous sibling attribute in the DOM. Returns null at beginning.
        const TiXmlAttribute* Previous() const;
        TiXmlAttribute* Previous() {
            return const_cast< TiXmlAttribute* >( const_cast< const TiXmlAttribute* >(this)->Previous() ); 
        }
    
        bool operator==( const TiXmlAttribute& rhs ) const { return rhs.name == name; }
        bool operator<( const TiXmlAttribute& rhs )  const { return name < rhs.name; }
        bool operator>( const TiXmlAttribute& rhs )  const { return name > rhs.name; }
    
        /*  Attribute parsing starts: first letter of the name
                             returns: the next XChar after the value end quote
        */
        virtual const XChar* Parse( const XChar* p, TiXmlParsingData* data, TiXmlEncoding encoding );
    
        // Prints this Attribute to a FILE stream.
        virtual void Print( FILE* cfile, XInt depth ) const {
            Print( cfile, depth, 0 );
        }
    
        virtual void Print(XAnsiString & strOut,XInt depth ) const
        {
            Print(strOut,depth,NULL);
        }
        void Print( XAnsiString & strOut,XInt depth, XAnsiString * str ) const;
    
        void Print( FILE* cfile, XInt depth, XAnsiString* str ) const;
    
        // [internal use]
        // Set the document pointer so the attribute can report errors.
        void SetDocument( TiXmlDocument* doc )  { document = doc; }
    
    private:
        TiXmlAttribute( const TiXmlAttribute& );                // not implemented.
        void operator=( const TiXmlAttribute& base );   // not allowed.
    
        TiXmlDocument*  document;   // A pointer back to a document, for error reporting.
        XAnsiString name;
        XAnsiString value;
        TiXmlAttribute* prev;
        TiXmlAttribute* next;
    };
    
    
    /*  A class used to manage a group of attributes.
        It is only used internally, both by the ELEMENT and the DECLARATION.
        
        The set can be changed transparent to the Element and Declaration
        classes that use it, but NOT transparent to the Attribute
        which has to implement a next() and previous() method. Which makes
        it a bit problematic and prevents the use of STL.
    
        This version is implemented with circular lists because:
            - I like circular lists
            - it demonstrates some independence from the (typical) doubly linked list.
    */
    class TiXmlAttributeSet
    {
    public:
        TiXmlAttributeSet();
        ~TiXmlAttributeSet();
    
        void Add( TiXmlAttribute* attribute );
        void Remove( TiXmlAttribute* attribute );
    
        const TiXmlAttribute* First()   const   { return ( sentinel.next == &sentinel ) ? 0 : sentinel.next; }
        TiXmlAttribute* First()                 { return ( sentinel.next == &sentinel ) ? 0 : sentinel.next; }
        const TiXmlAttribute* Last() const      { return ( sentinel.prev == &sentinel ) ? 0 : sentinel.prev; }
        TiXmlAttribute* Last()                  { return ( sentinel.prev == &sentinel ) ? 0 : sentinel.prev; }
    
        const TiXmlAttribute*   Find( const XChar* _name ) const;
        TiXmlAttribute* Find( const XChar* _name ) {
            return const_cast< TiXmlAttribute* >( const_cast< const TiXmlAttributeSet* >(this)->Find( _name ) );
        }
        const TiXmlAttribute*   Find( const XAnsiString& _name ) const;
        TiXmlAttribute* Find( const XAnsiString& _name ) {
            return const_cast< TiXmlAttribute* >( const_cast< const TiXmlAttributeSet* >(this)->Find( _name ) );
        }
    
    private:
        //*ME:  Because of hidden/disabled copy-construktor in TiXmlAttribute (sentinel-element),
        //*ME:  this class must be also use a hidden/disabled copy-constructor !!!
        TiXmlAttributeSet( const TiXmlAttributeSet& );  // not allowed
        void operator=( const TiXmlAttributeSet& ); // not allowed (as TiXmlAttribute)
    
        TiXmlAttribute sentinel;
    };
    
    
    /** The element is a container class. It has a value, the element name,
        and can contain other elements, text, comments, and unknowns.
        Elements also contain an arbitrary number of attributes.
    */
    class TiXmlElement : public TiXmlNode
    {
    public:
        /// Construct an element.
        TiXmlElement (const XChar * in_value);
    
        /// XAnsiString constructor.
        TiXmlElement( const XAnsiString& _value );
    
        TiXmlElement( const TiXmlElement& );
    
        void operator=( const TiXmlElement& base );
    
        virtual ~TiXmlElement();
        

        TiXmlElement * getFirstChildElement(const XChar * aName)
        {
            return FirstChildElement(aName);
        }
        TiXmlElement * getChildElement(const XChar * aName,XInt paramIndex = 0);

        XInt getInt(const XChar * aName,XInt aDefault = 0,XInt paramIndex = 0)
        {
            TiXmlElement * elem = getChildElement(aName,paramIndex);
            XInt iRet = aDefault;
            if( elem != NULL ) iRet = string_utils::StringToIntDef(elem->GetText(),aDefault);
            return iRet;
        }
        const XChar * getString(const XChar * aName,const XChar * aDefault = NULL,XInt paramIndex = 0)
        {
            TiXmlElement * elem = getChildElement(aName,paramIndex);
            const XChar * strRet = aDefault;
            if( elem != NULL ) strRet = elem->GetText();
            return strRet;    
        }
        TiXmlElement * AppendChildElement(const XChar * aName)
        {
            TiXmlElement * elem = new TiXmlElement(aName);
            LinkEndChild(elem);
            return elem;
        }
        TiXmlElement * AppendStringElement(const XChar * aName,const XChar * aValue);

        TiXmlElement * AppendIntElement(const XChar * aName,XInt aValue)
        {
            XChar buffer[32];
            return AppendStringElement(aName,string_utils::IntToStr(aValue,buffer));
        }
        TiXmlElement * AppendDWordElement(const XChar * aName,XDWord aValue)
        {
            XChar buffer[32];
            return AppendStringElement(aName,string_utils::DWordToStr(aValue,buffer));
        }
        TiXmlElement * AppendLongElement(const XChar * aName,XLong aValue)
        {
            XChar buffer[64];
            return AppendStringElement(aName,string_utils::LongToStr(aValue,buffer));
        }
        TiXmlElement * AppendDDWordElement(const XChar * aName,XDDWord aValue)
        {
            XChar buffer[64];
            return AppendStringElement(aName,string_utils::DDWordToStr(aValue,buffer));
        }
        TiXmlElement * AppendDateTimeElement(const XChar * aName,const XDateTime<> & aDateTime)
        {
            XChar buffer[32];
            return AppendStringElement(aName,aDateTime.ToString(buffer));
        }
        TiXmlElement * AppendDateElement(const XChar * aName,const XDate<> & aDate)
        {
            XChar buffer[16];
            return AppendStringElement(aName,aDate.ToString(buffer));
        }
        TiXmlElement * AppendTimeElement(const XChar * aName,const XTime<> & aTime)
        {
            XChar buffer[16];
            return AppendStringElement(aName,aTime.ToString(buffer));
        }
        TiXmlElement * AppendDurationElement(const XChar * aName,const XDurationTime<> & aDuration)
        {
            XChar buffer[40];
            return AppendStringElement(aName,aDuration.ToString(buffer));
        }

        //下面增加了一组，关于属性值操作方法
        void setBoolAttrib(const XAnsiString & aName,bool aValue)
        {
            SetAttribute(aName,aValue?1:0);
        }
        
        bool getBoolAttrib(const XAnsiString & aName,bool aDefault = false)
        {
            const XAnsiString * pValue = Attribute(aName);
            bool bRet = aDefault;
            if( pValue != NULL ) bRet =   pValue->ToIntDef(aDefault?1:0) != 0;
            return bRet;
        }

        void setIntAttrib(const XAnsiString & aName,XInt aValue)
        {
            XChar buffer[12];
            SetAttribute(aName,string_utils::IntToStr(aValue,buffer));
        }

        XInt getIntAttrib(const XAnsiString & aName,XInt aDefault = 0)
        {
            const XAnsiString * pValue = Attribute(aName);
            XInt iRet = aDefault;
            if( pValue != NULL ) iRet =  pValue->ToIntDef(aDefault);
            return iRet;
        }

        void setDWordAttrib(const XAnsiString & aName,XDWord aValue)
        {
            XChar Buffer[12];
            SetAttribute(aName, string_utils::DWordToStr(aValue,Buffer));
        }
        XDWord getDWordAttrib(const XAnsiString & aName,XDWord aDefault = 0)
        {
            const XAnsiString * pValue = Attribute(aName);
            XDWord dwRet = aDefault;
            if( pValue != NULL ) dwRet =  pValue->ToDWordDef(aDefault);
            return dwRet;
        }
        void setDDWordAttrib(const XAnsiString & aName,XDDWord aValue)
        {
            XChar Buffer[22];
            SetAttribute(aName,string_utils::DDWordToStr(aValue,Buffer));
        }
        XDDWord getDDWordAttrib(const XAnsiString & aName,XDDWord aDefault = 0)
        {
            const XAnsiString * pValue = Attribute(aName);
            XDDWord ddwRet = aDefault;
            if( pValue != NULL ) ddwRet =  pValue->ToDDWordDef(aDefault);
            return ddwRet;
        }
        void setLongAttrib(const XAnsiString & aName,XLong aValue)
        {
            XChar Buffer[22];
            SetAttribute(aName,string_utils::LongToStr(aValue,Buffer));
        }
        XLong getLongAttrib(const XAnsiString & aName,XLong aDefault = 0)
        {
            const XAnsiString * pValue = Attribute(aName);
            XLong lngRet = aDefault;
            if( pValue != NULL ) lngRet =  pValue->ToLongDef(aDefault);
            return lngRet;
        }
        void setStringAttrib(const XAnsiString & aName,const XAnsiString & aValue)
        {
            SetAttribute(aName,aValue);
        }
        const XChar * getStringAttrib(const XAnsiString & aName,const XChar * aDefault = NULL )
        {
            const XAnsiString * pValue = Attribute(aName);
            if( pValue != NULL ) return pValue->c_str();
            else return aDefault;
        }
        XDateTime<> getDateTimeAttrib(const XAnsiString & aName)
        {
            const XAnsiString * pValue = Attribute(aName);
            XDateTime<> dt;
            if( pValue != NULL ) dt.Parse(*pValue);
            return dt;
        }
        void setDateTimeAttrib(const XAnsiString &aName,XDateTime<> &aDateTime)
        {
            XChar buffer[24];
            aDateTime.ToString(buffer);
            SetAttribute(aName,buffer);
        }
        XDurationTime<> getDurationTimeAttrib(const XAnsiString & aName)
        {
            const XAnsiString * pValue = Attribute(aName);
            XDurationTime<> dt;
            if( pValue != NULL ) dt.Parse(*pValue);
            return dt;
        }
        void setDurationTimeAttrib(const XAnsiString &aName,XDurationTime<> &aDurationTime)
        {
            XChar buffer[40];
            SetAttribute(aName,aDurationTime.ToString(buffer));
        }


        /** Given an attribute name, Attribute() returns the value
            for the attribute of that name, or null if none exists.
        */
        const XChar* Attribute( const XChar* name ) const;
    
        /** Given an attribute name, Attribute() returns the value
            for the attribute of that name, or null if none exists.
            If the attribute exists and can be converted to an integer,
            the integer value will be put in the return 'i', if 'i'
            is non-null.
        */
        const XChar* Attribute( const XChar* name, XInt* i ) const;
    
        /** Given an attribute name, Attribute() returns the value
            for the attribute of that name, or null if none exists.
            If the attribute exists and can be converted to an double,
            the double value will be put in the return 'd', if 'd'
            is non-null.
        */
        const XChar* Attribute( const XChar* name, double* d ) const;
    
        /** QueryIntAttribute examines the attribute - it is an alternative to the
            Attribute() method with richer error checking.
            If the attribute is an integer, it is stored in 'value' and 
            the call returns TIXML_SUCCESS. If it is not
            an integer, it returns TIXML_WRONG_TYPE. If the attribute
            does not exist, then TIXML_NO_ATTRIBUTE is returned.
        */  
        XInt QueryIntAttribute( const XChar* name, XInt* _value ) const;
        /// QueryDoubleAttribute examines the attribute - see QueryIntAttribute().
        XInt QueryDoubleAttribute( const XChar* name, double* _value ) const;
        /// QueryFloatAttribute examines the attribute - see QueryIntAttribute().
        XInt QueryFloatAttribute( const XChar* name, float* _value ) const {
            double d;
            XInt result = QueryDoubleAttribute( name, &d );
            if ( result == TIXML_SUCCESS ) {
                *_value = (float)d;
            }
            return result;
        }
        /** Template form of the attribute query which will try to read the
            attribute into the specified type. Very easy, very powerful, but
            be careful to make sure to call this with the correct type.
    
            @return TIXML_SUCCESS, TIXML_WRONG_TYPE, or TIXML_NO_ATTRIBUTE
        */
        //template< typename T > 
        //XInt QueryValueAttribute( const XAnsiString& name, T* outValue ) const
        //{
        //  const TiXmlAttribute* node = attributeSet.Find( name );
        //  if ( !node )
        //      return TIXML_NO_ATTRIBUTE;
    //
    //      std::stringstream ss( node->ValueStr().c_str() );
    //      ss >> *outValue;
    //      if ( !ss.fail() )
    //      {
    //          return TIXML_SUCCESS;
    //      }
    //      else
    //      {
    //          return TIXML_WRONG_TYPE;
    //      }
    //  }
        void ClearAttribute();
        /** Sets an attribute of name to a given value. The attribute
            will be created if it does not exist, or changed if it does.
        */
        void SetAttribute( const XChar* name, const XChar * _value );
        void SetAttribute( const XChar * name, XInt value )
        {
            XChar Buffer[32];
            string_utils::IntToStr(value,Buffer);
            SetAttribute( name, Buffer);
        }
        void SetAttribute( const XAnsiString& name, const XAnsiString& _value );
        void SetAttribute( const XAnsiString& name, XInt _value )
        {
            XChar Buffer[32];
            string_utils::IntToStr(_value, Buffer);
            SetAttribute( name, Buffer);
        }
    
        const XAnsiString* Attribute( const XAnsiString& name ) const;
        const XAnsiString* Attribute( const XAnsiString& name, XInt* i ) const;
        const XAnsiString* Attribute( const XAnsiString& name, double* d ) const;
        XInt QueryIntAttribute( const XAnsiString& name, XInt* _value ) const;
        XInt QueryDoubleAttribute( const XAnsiString& name, double* _value ) const;
    
    
        /** Sets an attribute of name to a given value. The attribute
            will be created if it does not exist, or changed if it does.
        */
        void SetDoubleAttribute( const XChar * name, double value );
    
        /** Deletes an attribute with the given name.
        */
        void RemoveAttribute( const XChar * name );
        void RemoveAttribute( const XAnsiString& name ) {   RemoveAttribute (name.c_str ());    }   ///< STL XAnsiString form.
    
        const TiXmlAttribute* FirstAttribute() const    { return attributeSet.First(); }        ///< Access the first attribute in this element.
        TiXmlAttribute* FirstAttribute()                { return attributeSet.First(); }
        const TiXmlAttribute* LastAttribute()   const   { return attributeSet.Last(); }     ///< Access the last attribute in this element.
        TiXmlAttribute* LastAttribute()                 { return attributeSet.Last(); }
    
        /** Convenience function for easy access to the text inside an element. Although easy
            and concise, GetText() is limited compared to getting the TiXmlText child
            and accessing it directly.
        
            If the first child of 'this' is a TiXmlText, the GetText()
            returns the character string of the Text node, else null is returned.
    
            This is a convenient method for getting the text of simple contained text:
            @verbatim
            <foo>This is text</foo>
            const XChar* str = fooElement->GetText();
            @endverbatim
    
            'str' will be a pointer to "This is text". 
            
            Note that this function can be misleading. If the element foo was created from
            this XML:
            @verbatim
            <foo><b>This is text</b></foo> 
            @endverbatim
    
            then the value of str would be null. The first child node isn't a text node, it is
            another element. From this XML:
            @verbatim
            <foo>This is <b>text</b></foo> 
            @endverbatim
            GetText() will return "This is ".
    
            WARNING: GetText() accesses a child node - don't become confused with the 
                     similarly named TiXmlHandle::Text() and TiXmlNode::ToText() which are 
                     safe type casts on the referenced node.
        */
        const XChar* GetText() const;
    
        /// Creates a new Element and returns it - the returned element is a copy.
        virtual TiXmlNode* Clone() const;
        // Print the Element to a FILE stream.
        virtual void Print( FILE* cfile, XInt depth ) const;
        virtual void Print(XAnsiString & strOut,XInt depth) const;
    
        /*  Attribtue parsing starts: next XChar past '<'
                             returns: next XChar past '>'
        */
        virtual const XChar* Parse( const XChar* p, TiXmlParsingData* data, TiXmlEncoding encoding );
    
        virtual const TiXmlElement*     ToElement()     const { return this; } ///< Cast to a more defined type. Will return null not of the requested type.
        virtual TiXmlElement*           ToElement()           { return this; } ///< Cast to a more defined type. Will return null not of the requested type.
    
        /** Walk the XML tree visiting this node and all of its children. 
        */
        virtual bool Accept( TiXmlVisitor* visitor ) const;
    
    protected:
    
        void CopyTo( TiXmlElement* target ) const;
        void ClearThis();   // like clear, but initializes 'this' object as well
    
        // Used to be public [internal use]
        virtual void StreamIn( std::istream * in, XAnsiString * tag );
        /*  [internal use]
            Reads the "value" of the element -- another element, or text.
            This should terminate with the current end tag.
        */
        const XChar* ReadValue( const XChar* in, TiXmlParsingData* prevData, TiXmlEncoding encoding );
    
    private:
    
        TiXmlAttributeSet attributeSet;
    };
    
    
    /** An XML comment.
    */
    class TiXmlComment : public TiXmlNode
    {
    public:
        /// Constructs an empty comment.
        TiXmlComment() : TiXmlNode( TiXmlNode::COMMENT ) {}
        /// Construct a comment from text.
        TiXmlComment( const XChar* _value ) : TiXmlNode( TiXmlNode::COMMENT ) {
            SetValue( _value );
        }
        TiXmlComment( const TiXmlComment& );
        void operator=( const TiXmlComment& base );
    
        virtual ~TiXmlComment() {}
    
        /// Returns a copy of this Comment.
        virtual TiXmlNode* Clone() const;
        // Write this Comment to a FILE stream.
        virtual void Print( FILE* cfile, XInt depth ) const;
    
        virtual void Print(XAnsiString & strOut,XInt depth ) const;
    
    
        /*  Attribtue parsing starts: at the ! of the !--
                             returns: next XChar past '>'
        */
        virtual const XChar* Parse( const XChar* p, TiXmlParsingData* data, TiXmlEncoding encoding );
    
        virtual const TiXmlComment*  ToComment() const { return this; } ///< Cast to a more defined type. Will return null not of the requested type.
        virtual TiXmlComment*  ToComment() { return this; } ///< Cast to a more defined type. Will return null not of the requested type.
    
        /** Walk the XML tree visiting this node and all of its children. 
        */
        virtual bool Accept( TiXmlVisitor* visitor ) const;
    
    protected:
        void CopyTo( TiXmlComment* target ) const;
    
        // used to be public
        virtual void StreamIn( std::istream * in, XAnsiString * tag );
    //  virtual void StreamOut( TIXML_OSTREAM * out ) const;
    
    private:
    
    };
    
    
    /** XML text. A text node can have 2 ways to output the next. "normal" output 
        and CDATA. It will default to the mode it was parsed from the XML file and
        you generally want to leave it alone, but you can change the output mode with 
        SetCDATA() and query it with CDATA().
    */
    class TiXmlText : public TiXmlNode
    {
        friend class TiXmlElement;
    public:
        /** Constructor for text element. By default, it is treated as 
            normal, encoded text. If you want it be output as a CDATA text
            element, set the parameter _cdata to 'true'
        */
        TiXmlText (const XChar * initValue ) : TiXmlNode (TiXmlNode::TEXT)
        {
            SetValue( initValue );
            cdata = false;
        }
        virtual ~TiXmlText() {}
    
        /// Constructor.
        TiXmlText( const XAnsiString& initValue ) : TiXmlNode (TiXmlNode::TEXT)
        {
            SetValue( initValue );
            cdata = false;
        }
    
        TiXmlText( const TiXmlText& copy ) : TiXmlNode( TiXmlNode::TEXT )   { copy.CopyTo( this ); }
        void operator=( const TiXmlText& base )                             { base.CopyTo( this ); }
    
        // Write this text object to a FILE stream.
        virtual void Print( FILE* cfile, XInt depth ) const;
        virtual void Print( XAnsiString & strOut,XInt depth) const;
    
        /// Queries whether this represents text using a CDATA section.
        bool CDATA() const              { return cdata; }
        /// Turns on or off a CDATA representation of text.
        void SetCDATA( bool _cdata )    { cdata = _cdata; }
    
        virtual const XChar* Parse( const XChar* p, TiXmlParsingData* data, TiXmlEncoding encoding );
    
        virtual const TiXmlText* ToText() const { return this; } ///< Cast to a more defined type. Will return null not of the requested type.
        virtual TiXmlText*       ToText()       { return this; } ///< Cast to a more defined type. Will return null not of the requested type.
    
        /** Walk the XML tree visiting this node and all of its children. 
        */
        virtual bool Accept( TiXmlVisitor* content ) const;
    
    protected :
        ///  [internal use] Creates a new Element and returns it.
        virtual TiXmlNode* Clone() const;
        void CopyTo( TiXmlText* target ) const;
    
        bool Blank() const; // returns true if all white space and new lines
        // [internal use]
        virtual void StreamIn( std::istream * in, XAnsiString * tag );
    
    private:
        bool cdata;         // true if this should be input and output as a CDATA style text element
    };
    
    
    /** In correct XML the declaration is the first entry in the file.
        @verbatim
            <?xml version="1.0" standalone="yes"?>
        @endverbatim
    
        TinyXml will happily read or write files without a declaration,
        however. There are 3 possible attributes to the declaration:
        version, encoding, and standalone.
    
        Note: In this version of the code, the attributes are
        handled as special cases, not generic attributes, simply
        because there can only be at most 3 and they are always the same.
    */
    class TiXmlDeclaration : public TiXmlNode
    {
    public:
        /// Construct an empty declaration.
        TiXmlDeclaration()   : TiXmlNode( TiXmlNode::DECLARATION ) {}
    
        /// Constructor.
        TiXmlDeclaration(   const XAnsiString& _version,
                            const XAnsiString& _encoding,
                            const XAnsiString& _standalone );
    
        /// Construct.
        TiXmlDeclaration(   const XChar* _version,
                            const XChar* _encoding,
                            const XChar* _standalone );
    
        TiXmlDeclaration( const TiXmlDeclaration& copy );
        void operator=( const TiXmlDeclaration& copy );
    
        virtual ~TiXmlDeclaration() {}
    
        /// Version. Will return an empty string if none was found.
        const XChar *Version() const            { return version.c_str (); }
        /// Encoding. Will return an empty string if none was found.
        const XChar *Encoding() const       { return encoding.c_str (); }
        /// Is this a standalone document?
        const XChar *Standalone() const     { return standalone.c_str (); }
    
        /// Creates a copy of this Declaration and returns it.
        virtual TiXmlNode* Clone() const;
        // Print this declaration to a FILE stream.
        virtual void Print( FILE* cfile, XInt depth, XAnsiString* str ) const;
        virtual void Print( FILE* cfile, XInt depth ) const {
            Print( cfile, depth, 0 );
        }
    
        virtual void Print( XAnsiString & strOut, XInt depth, XAnsiString* str ) const;
        virtual void Print( XAnsiString & strOut, XInt depth ) const
        {
            Print( strOut, depth, 0 );
        }
    
        virtual const XChar* Parse( const XChar* p, TiXmlParsingData* data, TiXmlEncoding encoding );
    
        virtual const TiXmlDeclaration* ToDeclaration() const { return this; } ///< Cast to a more defined type. Will return null not of the requested type.
        virtual TiXmlDeclaration*       ToDeclaration()       { return this; } ///< Cast to a more defined type. Will return null not of the requested type.
    
        /** Walk the XML tree visiting this node and all of its children. 
        */
        virtual bool Accept( TiXmlVisitor* visitor ) const;
    
    protected:
        void CopyTo( TiXmlDeclaration* target ) const;
        // used to be public
        virtual void StreamIn( std::istream * in, XAnsiString * tag );
    
    private:
    
        XAnsiString version;
        XAnsiString encoding;
        XAnsiString standalone;
    };
    
    
    /** Any tag that tinyXml doesn't recognize is saved as an
        unknown. It is a tag of text, but should not be modified.
        It will be written back to the XML, unchanged, when the file
        is saved.
    
        DTD tags get thrown into TiXmlUnknowns.
    */
    class TiXmlUnknown : public TiXmlNode
    {
    public:
        TiXmlUnknown() : TiXmlNode( TiXmlNode::UNKNOWN )    {}
        virtual ~TiXmlUnknown() {}
    
        TiXmlUnknown( const TiXmlUnknown& copy ) : TiXmlNode( TiXmlNode::UNKNOWN )      { copy.CopyTo( this ); }
        void operator=( const TiXmlUnknown& copy )                                      { copy.CopyTo( this ); }
    
        /// Creates a copy of this Unknown and returns it.
        virtual TiXmlNode* Clone() const;
        // Print this Unknown to a FILE stream.
        virtual void Print( FILE* cfile, XInt depth ) const;
        virtual void Print( XAnsiString & strOut,XInt depth) const;
    
        virtual const XChar* Parse( const XChar* p, TiXmlParsingData* data, TiXmlEncoding encoding );
    
        virtual const TiXmlUnknown*     ToUnknown()     const { return this; } ///< Cast to a more defined type. Will return null not of the requested type.
        virtual TiXmlUnknown*           ToUnknown()     { return this; } ///< Cast to a more defined type. Will return null not of the requested type.
    
        /** Walk the XML tree visiting this node and all of its children. 
        */
        virtual bool Accept( TiXmlVisitor* content ) const;
    
    protected:
        void CopyTo( TiXmlUnknown* target ) const;
    
        virtual void StreamIn( std::istream * in, XAnsiString * tag );
    
    private:
    
    };
    
    
    /** Always the top level node. A document binds together all the
        XML pieces. It can be saved, loaded, and printed to the screen.
        The 'value' of a document node is the xml file name.
    */
    class TiXmlDocument : public TiXmlNode
    {
    public:
        /// Create an empty document, that has no name.
        TiXmlDocument();
        /// Create a document with a name. The name of the document is also the filename of the xml.
        TiXmlDocument( const XChar * documentName );
    
        /// Constructor.
        TiXmlDocument( const XAnsiString& documentName );
    
        TiXmlDocument( const TiXmlDocument& copy );
        void operator=( const TiXmlDocument& copy );
    
        virtual ~TiXmlDocument() {}
    
        /** Load a file using the current document value.
            Returns true if successful. Will delete any existing
            document data before loading.
        */
        bool LoadFile( TiXmlEncoding encoding = TIXML_DEFAULT_ENCODING );
        /// Save a file using the current document value. Returns true if successful.
        bool SaveFile() const;
        /// Load a file using the given filename. Returns true if successful.
        bool LoadFile( const XChar * filename, TiXmlEncoding encoding = TIXML_DEFAULT_ENCODING );
        /// Save a file using the given filename. Returns true if successful.
        bool SaveFile( const XChar * filename ) const;
        /** Load a file using the given FILE*. Returns true if successful. Note that this method
            doesn't stream - the entire object pointed at by the FILE*
            will be interpreted as an XML file. TinyXML doesn't stream in XML from the current
            file location. Streaming may be added in the future.
        */
        bool LoadFile( FILE*, TiXmlEncoding encoding = TIXML_DEFAULT_ENCODING );
        bool LoadFromString(const XAnsiString & paramData ,TiXmlEncoding encoding = TIXML_DEFAULT_ENCODING)
        {
            return LoadFromString(paramData.c_str(), encoding); 
        }
        bool LoadFromString(const XChar * strData,TiXmlEncoding encoding = TIXML_DEFAULT_ENCODING);
        /// Save a file using the given FILE*. Returns true if successful.
        bool SaveFile( FILE* ) const;
        bool LoadFile( const XAnsiString& filename, TiXmlEncoding encoding = TIXML_DEFAULT_ENCODING )       //< STL XAnsiString version.
        {
    //      StringToBuffer f( filename );
    //      return ( f.buffer && LoadFile( f.buffer, encoding ));
            return LoadFile( filename.c_str(), encoding );
        }
        bool SaveFile( const XAnsiString& filename ) const      //< STL XAnsiString version.
        {
    //      StringToBuffer f( filename );
    //      return ( f.buffer && SaveFile( f.buffer ));
            return SaveFile( filename.c_str() );
        }
    
        /** Parse the given null terminated block of xml data. Passing in an encoding to this
            method (either TIXML_ENCODING_LEGACY or TIXML_ENCODING_UTF8 will force TinyXml
            to use that encoding, regardless of what TinyXml might otherwise try to detect.
        */
        virtual const XChar* Parse( const XChar* p, TiXmlParsingData* data = 0, TiXmlEncoding encoding = TIXML_DEFAULT_ENCODING );
    
        /** Get the root element -- the only top level element -- of the document.
            In well formed XML, there should only be one. TinyXml is tolerant of
            multiple elements at the document level.
        */
        const TiXmlElement* RootElement() const     { return FirstChildElement(); }
        TiXmlElement* RootElement()                 { return FirstChildElement(); }
    
        /** If an error occurs, Error will be set to true. Also,
            - The ErrorId() will contain the integer identifier of the error (not generally useful)
            - The ErrorDesc() method will return the name of the error. (very useful)
            - The ErrorRow() and ErrorCol() will return the location of the error (if known)
        */  
        bool Error() const                      { return error; }
    
        /// Contains a textual (english) description of the error if one occurs.
        const XChar * ErrorDesc() const { return errorDesc.c_str (); }
    
        /** Generally, you probably want the error string ( ErrorDesc() ). But if you
            prefer the ErrorId, this function will fetch it.
        */
        XInt ErrorId()  const               { return errorId; }
    
        /** Returns the location (if known) of the error. The first column is column 1, 
            and the first row is row 1. A value of 0 means the row and column wasn't applicable
            (memory errors, for example, have no row/column) or the parser lost the error. (An
            error in the error reporting, in that case.)
    
            @sa SetTabSize, Row, Column
        */
        XInt ErrorRow() { return errorLocation.row+1; }
        XInt ErrorCol() { return errorLocation.col+1; } ///< The column where the error occured. See ErrorRow()
    
        /** SetTabSize() allows the error reporting functions (ErrorRow() and ErrorCol())
            to report the correct values for row and column. It does not change the output
            or input in any way.
            
            By calling this method, with a tab size
            greater than 0, the row and column of each node and attribute is stored
            when the file is loaded. Very useful for tracking the DOM back in to
            the source file.
    
            The tab size is required for calculating the location of nodes. If not
            set, the default of 4 is used. The tabsize is set per document. Setting
            the tabsize to 0 disables row/column tracking.
    
            Note that row and column tracking is not supported when using operator>>.
    
            The tab size needs to be enabled before the parse or load. Correct usage:
            @verbatim
            TiXmlDocument doc;
            doc.SetTabSize( 8 );
            doc.Load( "myfile.xml" );
            @endverbatim
    
            @sa Row, Column
        */
        void SetTabSize( XInt _tabsize )        { tabsize = _tabsize; }
    
        XInt TabSize() const    { return tabsize; }
    
        /** If you have handled the error, it can be reset with this call. The error
            state is automatically cleared if you Parse a new XML block.
        */
        void ClearError()                       {   error = false; 
                                                    errorId = 0; 
                                                    errorDesc = ""; 
                                                    errorLocation.row = errorLocation.col = 0; 
                                                    //errorLocation.last = 0; 
                                                }
    
        /** Write the document to standard out using formatted printing ("pretty print"). */
        void Print() const                      { Print( stdout, 0 ); }
    
        /* Write the document to a string using formatted printing ("pretty print"). This
            will allocate a character array (new XChar[]) and return it as a pointer. The
            calling code pust call delete[] on the return XChar* to avoid a memory leak.
        */
        //XChar* PrintToMemory() const; 
    
        /// Print this Document to a FILE stream.
        virtual void Print( FILE* cfile, XInt depth = 0 ) const;
        virtual void Print(XAnsiString & strOut,XInt depth=0) const;
        // [internal use]
        void SetError( XInt err, const XChar* errorLocation, TiXmlParsingData* prevData, TiXmlEncoding encoding );
    
        virtual const TiXmlDocument*    ToDocument()    const { return this; } ///< Cast to a more defined type. Will return null not of the requested type.
        virtual TiXmlDocument*          ToDocument()          { return this; } ///< Cast to a more defined type. Will return null not of the requested type.
    
        /** Walk the XML tree visiting this node and all of its children. 
        */
        virtual bool Accept( TiXmlVisitor* content ) const;
    
    protected :
        // [internal use]
        virtual TiXmlNode* Clone() const;
        virtual void StreamIn( std::istream * in, XAnsiString * tag );
    
    private:
        void CopyTo( TiXmlDocument* target ) const;
    
        bool error;
        XInt  errorId;
        XAnsiString errorDesc;
        XInt tabsize;
        TiXmlCursor errorLocation;
        bool useMicrosoftBOM;       // the UTF-8 BOM were found when read. Note this, and try to write.
    };
    
    
    /**
        A TiXmlHandle is a class that wraps a node pointer with null checks; this is
        an incredibly useful thing. Note that TiXmlHandle is not part of the TinyXml
        DOM structure. It is a separate utility class.
    
        Take an example:
        @verbatim
        <Document>
            <Element attributeA = "valueA">
                <Child attributeB = "value1" />
                <Child attributeB = "value2" />
            </Element>
        <Document>
        @endverbatim
    
        Assuming you want the value of "attributeB" in the 2nd "Child" element, it's very 
        easy to write a *lot* of code that looks like:
    
        @verbatim
        TiXmlElement* root = document.FirstChildElement( "Document" );
        if ( root )
        {
            TiXmlElement* element = root->FirstChildElement( "Element" );
            if ( element )
            {
                TiXmlElement* child = element->FirstChildElement( "Child" );
                if ( child )
                {
                    TiXmlElement* child2 = child->NextSiblingElement( "Child" );
                    if ( child2 )
                    {
                        // Finally do something useful.
        @endverbatim
    
        And that doesn't even cover "else" cases. TiXmlHandle addresses the verbosity
        of such code. A TiXmlHandle checks for null pointers so it is perfectly safe 
        and correct to use:
    
        @verbatim
        TiXmlHandle docHandle( &document );
        TiXmlElement* child2 = docHandle.FirstChild( "Document" ).FirstChild( "Element" ).Child( "Child", 1 ).ToElement();
        if ( child2 )
        {
            // do something useful
        @endverbatim
    
        Which is MUCH more concise and useful.
    
        It is also safe to copy handles - internally they are nothing more than node pointers.
        @verbatim
        TiXmlHandle handleCopy = handle;
        @endverbatim
    
        What they should not be used for is iteration:
    
        @verbatim
        XInt i=0; 
        while ( true )
        {
            TiXmlElement* child = docHandle.FirstChild( "Document" ).FirstChild( "Element" ).Child( "Child", i ).ToElement();
            if ( !child )
                break;
            // do something
            ++i;
        }
        @endverbatim
    
        It seems reasonable, but it is in fact two embedded while loops. The Child method is 
        a linear walk to find the element, so this code would iterate much more than it needs 
        to. Instead, prefer:
    
        @verbatim
        TiXmlElement* child = docHandle.FirstChild( "Document" ).FirstChild( "Element" ).FirstChild( "Child" ).ToElement();
    
        for( child; child; child=child->NextSiblingElement() )
        {
            // do something
        }
        @endverbatim
    */
    class TiXmlHandle
    {
    public:
        /// Create a handle from any node (at any depth of the tree.) This can be a null pointer.
        TiXmlHandle( TiXmlNode* _node )                 { this->node = _node; }
        /// Copy constructor
        TiXmlHandle( const TiXmlHandle& ref )           { this->node = ref.node; }
        TiXmlHandle operator=( const TiXmlHandle& ref ) { this->node = ref.node; return *this; }
    
        /// Return a handle to the first child node.
        TiXmlHandle FirstChild() const;
        /// Return a handle to the first child node with the given name.
        TiXmlHandle FirstChild( const XChar * value ) const;
        /// Return a handle to the first child element.
        TiXmlHandle FirstChildElement() const;
        /// Return a handle to the first child element with the given name.
        TiXmlHandle FirstChildElement( const XChar * value ) const;
    
        /** Return a handle to the "index" child with the given name. 
            The first child is 0, the second 1, etc.
        */
        TiXmlHandle Child( const XChar* value, XInt index ) const;
        /** Return a handle to the "index" child. 
            The first child is 0, the second 1, etc.
        */
        TiXmlHandle Child( XInt index ) const;
        /** Return a handle to the "index" child element with the given name. 
            The first child element is 0, the second 1, etc. Note that only TiXmlElements
            are indexed: other types are not counted.
        */
        TiXmlHandle ChildElement( const XChar* value, XInt index ) const;
        /** Return a handle to the "index" child element. 
            The first child element is 0, the second 1, etc. Note that only TiXmlElements
            are indexed: other types are not counted.
        */
        TiXmlHandle ChildElement( XInt index ) const;
    
        TiXmlHandle FirstChild( const XAnsiString& _value ) const               { return FirstChild( _value.c_str() ); }
        TiXmlHandle FirstChildElement( const XAnsiString& _value ) const        { return FirstChildElement( _value.c_str() ); }
    
        TiXmlHandle Child( const XAnsiString& _value, XInt index ) const            { return Child( _value.c_str(), index ); }
        TiXmlHandle ChildElement( const XAnsiString& _value, XInt index ) const { return ChildElement( _value.c_str(), index ); }
    
        /** Return the handle as a TiXmlNode. This may return null.
        */
        TiXmlNode* ToNode() const           { return node; } 
        /** Return the handle as a TiXmlElement. This may return null.
        */
        TiXmlElement* ToElement() const     { return ( ( node && node->ToElement() ) ? node->ToElement() : 0 ); }
        /** Return the handle as a TiXmlText. This may return null.
        */
        TiXmlText* ToText() const           { return ( ( node && node->ToText() ) ? node->ToText() : 0 ); }
        /** Return the handle as a TiXmlUnknown. This may return null.
        */
        TiXmlUnknown* ToUnknown() const     { return ( ( node && node->ToUnknown() ) ? node->ToUnknown() : 0 ); }
    
        /** @deprecated use ToNode. 
            Return the handle as a TiXmlNode. This may return null.
        */
        TiXmlNode* Node() const         { return ToNode(); } 
        /** @deprecated use ToElement. 
            Return the handle as a TiXmlElement. This may return null.
        */
        TiXmlElement* Element() const   { return ToElement(); }
        /** @deprecated use ToText()
            Return the handle as a TiXmlText. This may return null.
        */
        TiXmlText* Text() const         { return ToText(); }
        /** @deprecated use ToUnknown()
            Return the handle as a TiXmlUnknown. This may return null.
        */
        TiXmlUnknown* Unknown() const   { return ToUnknown(); }
    
    private:
        TiXmlNode* node;
    };
    
    
    /** Print to memory functionality. The TiXmlPrinter is useful when you need to:
    
        -# Print to memory (especially in non-STL mode)
        -# Control formatting (line endings, etc.)
    
        When constructed, the TiXmlPrinter is in its default "pretty printing" mode.
        Before calling Accept() you can call methods to control the printing
        of the XML document. After TiXmlNode::Accept() is called, the printed document can
        be accessed via the CStr(), Str(), and Size() methods.
    
        TiXmlPrinter uses the Visitor API.
        @verbatim
        TiXmlPrinter printer;
        printer.SetIndent( "\t" );
    
        doc.Accept( &printer );
        fprintf( stdout, "%s", printer.CStr() );
        @endverbatim
    */
    class TiXmlPrinter : public TiXmlVisitor
    {
    public:
        TiXmlPrinter() : depth( 0 ), simpleTextPrint( false ),
                         buffer(), indent( "    " ), lineBreak( "\n" ) {}
    
        virtual bool VisitEnter( const TiXmlDocument& doc );
        virtual bool VisitExit( const TiXmlDocument& doc );
    
        virtual bool VisitEnter( const TiXmlElement& element, const TiXmlAttribute* firstAttribute );
        virtual bool VisitExit( const TiXmlElement& element );
    
        virtual bool Visit( const TiXmlDeclaration& declaration );
        virtual bool Visit( const TiXmlText& text );
        virtual bool Visit( const TiXmlComment& comment );
        virtual bool Visit( const TiXmlUnknown& unknown );
    
        /** Set the indent characters for printing. By default 4 spaces
            but tab (\\t) is also useful, or null/empty string for no indentation.
        */
        void SetIndent( const XChar* _indent )          { indent = _indent ? _indent : "" ; }
        /// Query the indention string.
        const XChar* Indent()                           { return indent.c_str(); }
        /** Set the line breaking string. By default set to newline (\n). 
            Some operating systems prefer other characters, or can be
            set to the null/empty string for no indenation.
        */
        void SetLineBreak( const XChar* _lineBreak )        { lineBreak = _lineBreak ? _lineBreak : ""; }
        /// Query the current line breaking string.
        const XChar* LineBreak()                            { return lineBreak.c_str(); }
    
        /** Switch over to "stream printing" which is the most dense formatting without 
            linebreaks. Common when the XML is needed for network transmission.
        */
        void SetStreamPrinting()                        { indent = "";
                                                          lineBreak = "";
                                                        }   
        /// Return the result.
        const XChar* CStr()                             { return buffer.c_str(); }
        /// Return the length of the result string.
        size_t Size()                                   { return buffer.getLength(); }
    
        /// Return the result.
        const XAnsiString& Str()                        { return buffer; }
    
    private:
        void DoIndent();
    /*    {
            for( XInt i=0; i<depth; ++i )
                buffer += indent;
        }
    */
        void DoLineBreak() {
            buffer += lineBreak;
        }
    
        XInt depth;
        bool simpleTextPrint;
        XAnsiString buffer;
        XAnsiString indent;
        XAnsiString lineBreak;
    };
        
    class TiXmlParsingData
    {
        friend class TiXmlDocument;
      public:
        void Stamp( const XChar* now, TiXmlEncoding encoding );
    
        const TiXmlCursor& Cursor() { return cursor; }
    
      private:
        // Only used by the document!
        TiXmlParsingData( const XChar* start, XInt _tabsize, XInt row, XInt col )
        {
            ZDH_ASSERT( start );
            stamp = start;
            tabsize = _tabsize;
            cursor.row = row;
            cursor.col = col;
        }
    
        TiXmlCursor     cursor;
        const XChar*        stamp;
        XInt                tabsize;
    };
}        
#endif
