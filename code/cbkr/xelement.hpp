#ifndef XELEMENT_H
#define XELEMENT_H

#include "xattribute.hpp"

namespace bkr
{
    //Class for a xml element
    class XElement : public XNode
    {
        private:
            XName* tag_name;
            std::vector<XNode*>* child_nodes;
            std::vector<XAttribute*>* attributes;
        public:
            //Constructors
            XElement(XName* name, int n_of_childs, ...);
            XElement(std::string str, int n_of_childs, ...);
            XElement(const XElement& other);
            //Destructor
            ~XElement();
            //Get string to compare elements
            std::string getComparisonString() override;
            //Get the tag name
            XName* getTagName();
            //Set the tag name
            void setTagName(XName* tagname);
            //Parse the xml
            std::string xml() override;
            //Add a child
            void appendChild(XNode* childNode);
            //Remove all children with the tag name
            void removeChild(XNode* tagname);
            //Add an attrubute
            XAttribute* setAttribute(XAttribute* xattr);
            XAttribute* setAttribute(XName* attr_name, XText* attr_value);
            //Checks if element has attribute and returns it if true
            std::pair<bool, XAttribute*> has_attribute(XAttribute* xattr);
            //Checks if element has child and returns it if true
            std::pair<bool, XNode*> has_element(XNode* xele);
            //Checks if element has descendant and returns it if true
            std::pair<bool, XNode*> has_descendant(XNode* xele) override;
            //Remove attribute
            XAttribute* removeAttribute(XAttribute* xattr);
            XAttribute* removeAttribute(XName* attr_name);
            //Add attribute
            XElement& operator<<(XAttribute* xattr);
            //Add child
            XElement& operator<<(XNode* xnode);
            //Return first descendant with tag name
            XNode* Element(XNode* tagname);
            //Return the attribute with name
            XAttribute* Attribute(XAttribute* xattr);
            //Iterator for first child
            std::vector<XNode*>::iterator FirstChild() const;
            //Iterator for last child
            std::vector<XNode*>::iterator LastChild() const;
            //Iterator for first attribute
            std::vector<XAttribute*>::iterator FirstAttribute() const;
            //Iterator for last attribute
            std::vector<XAttribute*>::iterator LastAttribute() const;
            //Return vector with all descendants
            std::vector<XNode*> Descendants() override;
            //Delete all attributes
            void ClearAttributes() override;
            //Delete all children
            void ClearChildren();
            //Copy element
            XElement* copy();
    };

}

#endif