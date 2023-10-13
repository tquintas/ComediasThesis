#include "xreset.hpp"

namespace bkr
{
    XReset::XReset(XAttribute* id, XAttribute* name) : XPreparation(id, name, XName::bitKlavierTagNames.Item, 13, 0, 0)
    {
        just_item = true;
    };
    void XReset::Mod() {};
}