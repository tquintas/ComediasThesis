#include "bitklavier.hpp"

namespace bkr
{
    BitKlavier::BitKlavier(XAttribute* g_name) : XElement(XName::bitKlavierTagNames.Gallery, 0)
    {
        name = setAttribute(g_name);
        general = new XGeneral();
        eq = new XEqualizer();
        comp = new XCompressor(g_name);
        DefaultParamAttributes();
        appendChild(general);
        appendChild(eq);
        appendChild(comp);
    }
    void BitKlavier::DefaultParamAttributes()
    {
        sType = setAttribute(XAttribute::bitKlavierAttributes.GalleryParams.SampleType(5));
        sfURL = setAttribute(XAttribute::bitKlavierAttributes.GalleryParams.SoundfontURL("XSynth"));
        sfInst = setAttribute(XAttribute::bitKlavierAttributes.GalleryParams.SoundfontInst(0));
        dfPiano = setAttribute(XAttribute::bitKlavierAttributes.GalleryParams.DefaultPiano(1));
    }
    void BitKlavier::SetGeneral(XGeneral* gen)
    {
        general = gen;
    }
    void BitKlavier::SetEqualizer(XEqualizer* equalizer)
    {
        eq = equalizer;
    }
    void BitKlavier::SetCompressor(XCompressor* compressor)
    {
        comp = compressor;
    }
    void BitKlavier::AddPiano(XPiano* piano)
    {
        for (auto it = piano->BeginPreparations(); it != piano->EndPreparations(); ++it)
        {
            appendChild(*it);
        }
        appendChild(piano);
    }
    void BitKlavier::Save()
    {
        std::string file_name = "/Applications/bitKlavier/galleries/" + to_string(*name->getValue()) + ".xml";
        XDocument xdoc(this);
        xdoc.Save(file_name);
    };
}