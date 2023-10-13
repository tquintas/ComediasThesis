#include "xelement.hpp"

namespace bkr
{
    XElement::XElement(XName* name, int n_of_childs, ...) : tag_name(name), child_nodes(nullptr), attributes(nullptr)
    {
        if (n_of_childs > 0)
        {
            va_list args;
            XNode* xnode;
            va_start(args, n_of_childs);
            for (int i = 0; i < n_of_childs; ++i)
            {
                xnode = va_arg(args, XNode*);
                appendChild(xnode);
            }
            va_end(args);
        };
    };
    XElement::XElement(std::string str, int n_of_childs, ...) : tag_name(new XName(str)), child_nodes(nullptr), attributes(nullptr)
    {
        if (n_of_childs > 0)
        {
            va_list args;
            XNode* xnode;
            va_start(args, n_of_childs);
            for (int i = 0; i < n_of_childs; ++i)
            {
                xnode = va_arg(args, XNode*);
                appendChild(xnode);
            }
            va_end(args);
        };
    };
    XElement::XElement(const XElement& other) : tag_name(new XName(*other.tag_name)), child_nodes(nullptr), attributes(nullptr), XNode(other)
    {
        if (other.child_nodes != nullptr)
        {
            child_nodes = new std::vector<XNode*>{};
            for (auto it = other.FirstChild(); it != other.LastChild(); ++it)
            {
                appendChild((*it)->copy());
            };
        }
        if (other.attributes != nullptr)
        {
            attributes = new std::vector<XAttribute*>{};
            for (auto it = other.FirstAttribute(); it != other.LastAttribute(); ++it)
            {
                setAttribute((*it)->copy());
            };
        }
    };
    XElement::~XElement() {};
    std::string XElement::getComparisonString()
    {
        return tag_name->xml();
    } 
    XName* XElement::getTagName()
    {
        return tag_name;
    }
    void XElement::setTagName(XName* tagname)
    {
        tag_name = tagname;
    }
    std::string XElement::xml()
    {
        std::string joined_attrs;
        if (attributes != nullptr && !attributes->empty())
        {
            std::vector<XAttribute*> attr_copy(attributes->size());
            auto it = std::copy_if(attributes->begin(), attributes->end(), attr_copy.begin(), [](XAttribute* xattr) {return !(xattr->getValue()->getContent()->empty());});
            attr_copy.erase(it, attr_copy.end());
            std::vector<std::string> attr_copy2(attr_copy.size());
            std::transform(attr_copy.begin(), attr_copy.end(), attr_copy2.begin(), [](XAttribute* xattr) {return xattr->xml();});
            joined_attrs = std::accumulate(attr_copy2.begin(), attr_copy2.end(), std::string{}, [](const std::string& a, const std::string& b) {return a.empty() ? b : a + " " + b;});
        }
        else
        {
            joined_attrs = "";
        }
        std::string offset = getOffset();
        std::string xmlstr = offset;
        if (child_nodes == nullptr || child_nodes->empty())
        {
            xmlstr += "<" + tag_name->xml() + " " + joined_attrs + "/>\n";
        }
        else
        {
            xmlstr += "<" + tag_name->xml() + (joined_attrs.empty() ? "" : " " + joined_attrs) + ">\n";
            for (auto it = FirstChild(); it != LastChild(); ++it)
            {
                xmlstr += (*it)->xml();
            };
            xmlstr += offset + "</" + tag_name->xml() + ">\n";
        };
        return xmlstr;
    };
    void XElement::appendChild(XNode* childNode)
    {
        if (child_nodes == nullptr)
        {
            child_nodes = new std::vector<XNode*>();
        }
        child_nodes->push_back(childNode);
        childNode->setParent(this);
    };
    void XElement::removeChild(XNode* tagname)
    {
        if (child_nodes == nullptr) return;
        std::string comp = tagname->getComparisonString();
        auto it = std::remove_if(child_nodes->begin(), child_nodes->end(), [comp](XNode* node) { return comp == node->getComparisonString(); });
        child_nodes->erase(it, child_nodes->end());
    };
    XAttribute* XElement::setAttribute(XAttribute* xattr)
    {
        if (attributes == nullptr)
        {
            attributes = new std::vector<XAttribute*>();
        }
        std::pair<bool, XAttribute*> xa_pair = has_attribute(xattr);
        if (xa_pair.first)
        {
            xa_pair.second->setValue(xattr->getValue());
            return xa_pair.second;
        }
        else
        {
            attributes->push_back(xattr);
            return xattr;
        }
    };
    XAttribute* XElement::setAttribute(XName* attr_name, XText* attr_value)
    {
        XAttribute* xattr = new XAttribute(attr_name, attr_value);
        return setAttribute(xattr);
    };
    std::pair<bool, XAttribute*> XElement::has_attribute(XAttribute* xattr)
    {
        if (attributes == nullptr || attributes->size() == 0) return std::make_pair(false, nullptr);
        XAttribute* xa1;
        bool exists = std::any_of(attributes->begin(), attributes->end(), [xattr, &xa1](XAttribute* xa) {
            if (xa->getComparisonString() == xattr->getComparisonString())
            {
                xa1 = xa;
                return true;
            }
            else
            {
                return false;
            }
        });
        return std::make_pair(exists, xa1);
    };
    std::pair<bool, XNode*> XElement::has_element(XNode* xele)
    {
        if (child_nodes == nullptr || child_nodes->size() == 0) return std::make_pair(false, nullptr);
        XNode* xe;
        bool exists = std::any_of(child_nodes->begin(), child_nodes->end(), [xele, &xe](XNode* xnode) {
            if (xnode->getComparisonString() == xele->getComparisonString())
            {
                xe = xnode;
                return true;
            }
            else
            {
                return false;
            }
        });
        return std::make_pair(exists, xe);
    };
    std::pair<bool, XNode*> XElement::has_descendant(XNode* xele)
    {
        if (child_nodes == nullptr || child_nodes->size() == 0)
        {
            bool exists = getComparisonString() == xele->getComparisonString();
            return std::make_pair(exists, (exists ? this : nullptr));
        };
        XNode* xe;
        bool exists = std::any_of(child_nodes->begin(), child_nodes->end(), [xele, &xe](XNode* xnode) {
            std::pair<bool, XNode*> xe_pair = xnode->has_descendant(xele);
            if (xe_pair.first)
            {
                xe = xe_pair.second;
                return true;
            }
            else
            {
                return false;
            }
        });
        return std::make_pair(exists, xe);
    }
    XAttribute* XElement::removeAttribute(XAttribute* xattr)
    {
        if (attributes == nullptr) return nullptr;
        std::pair<bool, XAttribute*> xa_pair = has_attribute(xattr);
        if (xa_pair.first)
        {
            attributes->erase(std::remove(attributes->begin(), attributes->end(), xa_pair.second), attributes->end());
            return xa_pair.second;
        }
        else
        {
            return nullptr;
        };
    };
    XAttribute* XElement::removeAttribute(XName* attr_name)
    {
        XAttribute* xattr = new XAttribute(attr_name);
        return removeAttribute(xattr);
    };
    XElement& XElement::operator<<(XAttribute* xattr)
    {
        setAttribute(xattr);
        return *this;
    };
    XElement& XElement::operator<<(XNode* xnode)
    {
        appendChild(xnode);
        return *this;
    };
    XNode* XElement::Element(XNode* tagname)
    {
        std::pair<bool, XNode*> xe_pair = has_descendant(tagname);
        return xe_pair.second;
    };
    XAttribute* XElement::Attribute(XAttribute* xattr)
    {
        std::pair<bool, XAttribute*> xa_pair = has_attribute(xattr);
        return xa_pair.second;
    };
    std::vector<XNode*>::iterator XElement::FirstChild() const
    {
        return child_nodes->begin();
    };
    std::vector<XNode*>::iterator XElement::LastChild() const
    {
        return child_nodes->end();
    };
    std::vector<XAttribute*>::iterator XElement::FirstAttribute() const
    {
        return attributes->begin();
    };
    std::vector<XAttribute*>::iterator XElement::LastAttribute() const
    {
        return attributes->end();
    };
    std::vector<XNode*> XElement::Descendants()
    {
        std::vector<XNode*> vect(0);
        std::vector<XNode*> vect2;
        for (auto it = FirstChild(); it != LastChild(); ++it)
        {
            XNode* xnode = *it;
            vect.push_back(xnode);
            vect2 = xnode->Descendants();
            if (vect2.size() == 0) continue;
            for (auto it2 = vect2.begin(); it2 != vect2.end(); ++it2)
            {
                vect.push_back(*it2);
            };
        };
        return vect;
    };
    void XElement::ClearAttributes()
    {
        if (attributes != nullptr) attributes->clear();
    };
    void XElement::ClearChildren()
    {
        if (child_nodes != nullptr) child_nodes->clear();
    };
    XElement* XElement::copy()
    {
        return new XElement(*this);
    };
}