#include "xtext.hpp"

namespace bkr
{
    XText::XText(std::string str) : content(new std::string(str)) {};
    XText::XText(const XText& other) : content(nullptr), XNode(other)
    {
        if (other.content != nullptr)
        {
            content = new std::string(*other.content);
        };
    };
    XText::~XText() {};
    void XText::setContent(std::string* cont)
    {
        content = cont;
    };
    std::string* XText::getContent()
    {
        return content;
    }
    std::string XText::xml() 
    {
        return getOffset() + *content + "\n";
    };
    std::string XText::to_string(const XText& other)
    {
        return *other.content;
    };
    template <typename T> XText XText::operator+(const T& other) const
    {
        std::string txt = *content + *XText(to_string(other)).content;
        return XText(txt);
    };
    std::pair<bool, XNode*> XText::has_descendant(XNode* xnode) 
    {
        bool exists = getComparisonString() == xnode->getComparisonString();
        return std::make_pair(exists, (exists ? this : nullptr));
    };
    XNode* XText::copy() 
    {
        return new XText(*this);
    }
}