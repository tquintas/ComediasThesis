#include "xpreparation.hpp"

namespace bkr
{
    XPreparation::XPreparation(XAttribute* id, XAttribute* prep_name, XName* tag_name, int type, int dn, int modtype) : XElement(tag_name, 0), itype(type), mod_itype(modtype), moded(false)
    {
        ID = setAttribute(id);
        name = setAttribute(prep_name);
        alt = XAttribute::bitKlavierAttributes.Alt<bool>(false);
        dirty_element = new XElement(XName::bitKlavierTagNames.Dirty, 0);
        dirty = new XAttributeMap<bool>(dirty_element, "d", [](int i, bool j) { return XAttribute::bitKlavierAttributes.D<bool>(i, j); });
        for (int i = 0; i < dn; ++i)
        {
            dirty->NewPair(i, false);
        }
        createItem();
    };
    void XPreparation::createItem()
    {
        Item = new XElement(XName::bitKlavierTagNames.Item, 0);
        item = new XElement(XName::bitKlavierTagNames.Item, 0);
        connections = new XElement(XName::bitKlavierTagNames.Connections, 0);
        Item->appendChild(item);
        Item->appendChild(connections);
        piano = XAttribute::bitKlavierAttributes.ItemParams.Piano<int>(0);
        active = XAttribute::bitKlavierAttributes.ItemParams.Active<bool>(true);
        text = XAttribute::bitKlavierAttributes.ItemParams.Text("");
        type = XAttribute::bitKlavierAttributes.ItemParams.Type(itype);
        position = {
            XAttribute::bitKlavierAttributes.ItemParams.X(100.0),
            XAttribute::bitKlavierAttributes.ItemParams.Y(50.0),
            XAttribute::bitKlavierAttributes.ItemParams.W(50.0),
            XAttribute::bitKlavierAttributes.ItemParams.H(50.0)
        };
        *item << ID << name << type;
        *item << text;
        *item << piano << active << position.x << position.y << position.w << position.h;
    };
    void XPreparation::ChangePiano(XText* val)
    {
        piano->setValue(val);
    }
    XElement* XPreparation::getItem()
    {
        return Item;
    }
    void XPreparation::Connect(XPreparation* node)
    {
        connections->appendChild(node->item);
    };
    bool XPreparation::IsJustItem()
    {
        return just_item;
    }
    void XPreparation::Mod()
    {
        appendChild(dirty_element);
        setAttribute(alt);
        type = XAttribute::bitKlavierAttributes.ItemParams.Type(mod_itype);
        std::string n = getComparisonString();
        n[0] = std::toupper(n[0]);
        XName* modName = new XName("mod" + n);
        setTagName(modName);
        moded = true;
    }
    void XPreparation::GetDirty(int i)
    {
        dirty->UpdatePair(i, true);
    }
    void XPreparation::Save(std::string file_name = "xmlPreparation.xml")
    {
        XDocument xdoc(this);
        xdoc.Save(file_name);
    };
}