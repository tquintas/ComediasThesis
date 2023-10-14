#include "xattribute.hpp"

namespace bkr
{
    XAttribute::XAttribute(XName* n, XText* val) : name(n), value(val) {};
    XAttribute::XAttribute(std::string n, std::string val) : name(new XName(n)), value(new XText(val)) {};
    XAttribute::XAttribute(XName* n) : name(n), value(new XText("")) {};
    XAttribute::XAttribute(std::string n) : name(new XName(n)), value(new XText("")) {};
    XAttribute::XAttribute(const XAttribute& other) : name(new XName(*other.name)), value(new XText(*other.value)) {};
    XAttribute::~XAttribute() {};
    std::string XAttribute::xml()
    {
        if (value == nullptr || value->getContent() == nullptr)
        {
            return to_string(*name);
        }
        else
        {
            return to_string(*name)+"="+"\""+to_string(*value)+"\"";
        }
    };
    XName* XAttribute::getName()
    {
        return name;
    };
    XText* XAttribute::getValue()
    {
        return value;
    };
    void XAttribute::setName(XName* n)
    {
        name = n;
    };
    void XAttribute::setName(std::string n)
    {
        name = new XName(n);
    };
    void XAttribute::setValue(XText* val)
    {
        value = val;
    };
    void XAttribute::setValue(std::string val)
    {
        value = new XText(val);
    };
    std::string to_string(const XAttribute &other)
    {
        return to_string(*other.name)+"="+"\""+to_string(*other.value)+"\"";
    };
    std::string XAttribute::getComparisonString()
    {
        return to_string(*name);
    };
    XAttribute* XAttribute::copy()
    {
        return new XAttribute(*this);
    }
    XAttribute::bitKlavierAttributesStruct XAttribute::bitKlavierAttributes = {};
}