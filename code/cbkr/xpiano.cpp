#include "xpiano.hpp"

namespace bkr
{
    XPiano::XPiano(XAttribute* id, XAttribute* name) : XPreparation(id, name, XName::bitKlavierTagNames.Piano, 12, 0, 0) {};
    void XPiano::AddPreparation(XPreparation* prep)
    {
        appendChild(prep->getItem());
        if (!prep->IsJustItem()) preparations.push_back(prep);
    };
    void XPiano::TriggeredBy(XPreparation* keynote)
    {
        keynote->ChangePiano(ID->getValue());
        Connect(keynote);
    }
    std::vector<XPreparation*>::iterator XPiano::BeginPreparations()
    {
        return preparations.begin();
    }
    std::vector<XPreparation*>::iterator XPiano::EndPreparations()
    {
        return preparations.end();
    }
    void XPiano::Mod() {};
}