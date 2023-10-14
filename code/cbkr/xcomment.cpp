#include "xcomment.hpp"

namespace bkr
{
    XComment::XComment(std::string comment) : XPreparation(XAttribute::bitKlavierAttributes.ID(0), XAttribute::bitKlavierAttributes.Name("comment"), XName::bitKlavierTagNames.Item, 15, 0, 0)
    {
        just_item = true;
        ChangeText(comment);
    }
    void XComment::ChangeText(std::string comment)
    {
        text->setValue(comment);
    }
    void XComment::Mod() {};
}