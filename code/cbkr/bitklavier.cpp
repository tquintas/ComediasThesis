#include "bitklavier.hpp"

namespace bkr
{
    BitKlavier::BitKlavier(XAttribute* g_name) : XElement(XName::bitKlavierTagNames.Gallery, 0), current_piano(-1)
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
        pianoList.push_back(piano);
    }
    XPiano* BitKlavier::GetCurrentPiano()
    {
        if (current_piano == -1)
        {
            return NextPiano();
        }
        else
        {
            return pianoList[current_piano];
        }

    }
    XPiano* BitKlavier::NextPiano()
    {
        current_piano = pianoList.size();
        XPiano* piano = new XPiano(XAttribute::bitKlavierAttributes.ID(++counter), XAttribute::bitKlavierAttributes.Name("Piano"+current_piano));
        pianoList.push_back(piano);
        return piano;
    }
    XPiano* BitKlavier::NextPiano(XAttribute* name)
    {
        current_piano = pianoList.size();
        XPiano* piano = new XPiano(XAttribute::bitKlavierAttributes.ID(++counter), name);
        pianoList.push_back(piano);
        return piano;
    }
    XKeymap* BitKlavier::CreateKeymap()
    {
        XPiano* piano = GetCurrentPiano();
        XKeymap* keymap = new XKeymap(XAttribute::bitKlavierAttributes.ID(++counter), XAttribute::bitKlavierAttributes.Name("Keymap"+counter));
        piano->AddPreparation(keymap);
        return keymap;
    }
    XDirect* BitKlavier::CreateDirect()
    {
        XPiano* piano = GetCurrentPiano();
        XDirect* direct = new XDirect(XAttribute::bitKlavierAttributes.ID(++counter), XAttribute::bitKlavierAttributes.Name("Direct"+counter));
        piano->AddPreparation(direct);
        return direct;
    }
    XSynchronic* BitKlavier::CreateSynchronic()
    {
        XPiano* piano = GetCurrentPiano();
        XSynchronic* synchronic = new XSynchronic(XAttribute::bitKlavierAttributes.ID(++counter), XAttribute::bitKlavierAttributes.Name("Synchronic"+counter));
        piano->AddPreparation(synchronic);
        return synchronic;
    }
    XNostalgic* BitKlavier::CreateNostalgic()
    {
        XPiano* piano = GetCurrentPiano();
        XNostalgic* nostalgic = new XNostalgic(XAttribute::bitKlavierAttributes.ID(++counter), XAttribute::bitKlavierAttributes.Name("Nostalgic"+counter));
        piano->AddPreparation(nostalgic);
        return nostalgic;
    }
    XTempo* BitKlavier::CreateTempo()
    {
        XPiano* piano = GetCurrentPiano();
        XTempo* tempo = new XTempo(XAttribute::bitKlavierAttributes.ID(++counter), XAttribute::bitKlavierAttributes.Name("Tempo"+counter));
        piano->AddPreparation(tempo);
        return tempo;
    }
    XTuning* BitKlavier::CreateTuning()
    {
        XPiano* piano = GetCurrentPiano();
        XTuning* tuning = new XTuning(XAttribute::bitKlavierAttributes.ID(++counter), XAttribute::bitKlavierAttributes.Name("Tuning"+counter));
        piano->AddPreparation(tuning);
        return tuning;
    }
    XBlendronic* BitKlavier::CreateBlendronic()
    {
        XPiano* piano = GetCurrentPiano();
        XBlendronic* blendronic = new XBlendronic(XAttribute::bitKlavierAttributes.ID(++counter), XAttribute::bitKlavierAttributes.Name("Blendronic"+counter));
        piano->AddPreparation(blendronic);
        return blendronic;
    }
    XResonance* BitKlavier::CreateResonance()
    {
        XPiano* piano = GetCurrentPiano();
        XResonance* resonance = new XResonance(XAttribute::bitKlavierAttributes.ID(++counter), XAttribute::bitKlavierAttributes.Name("Resonance"+counter));
        piano->AddPreparation(resonance);
        return resonance;
    }
    XReset* BitKlavier::CreateReset()
    {
        XPiano* piano = GetCurrentPiano();
        XReset* reset = new XReset(XAttribute::bitKlavierAttributes.ID(++counter), XAttribute::bitKlavierAttributes.Name("Reset"+counter));
        piano->AddPreparation(reset);
        return reset;
    }
    XComment* BitKlavier::CreateComment()
    {
        XPiano* piano = GetCurrentPiano();
        XComment* comment = new XComment("");
        piano->AddPreparation(comment);
        return comment;
    }
    XComment* BitKlavier::CreateComment(std::string com)
    {
        XPiano* piano = GetCurrentPiano();
        XComment* comment = new XComment(com);
        piano->AddPreparation(comment);
        return comment;
    }
    XPreparation* BitKlavier::Create(Module module)
    {
        switch (module)
        {
            case PIANO:
                return NextPiano();
                break;
            case KEYMAP:
                return CreateKeymap();
                break;
            case DIRECT:
                return CreateDirect();
                break;
            case SYNCHRONIC:
                return CreateSynchronic();
                break;
            case NOSTALGIC:
                return CreateNostalgic();
                break;
            case TEMPO:
                return CreateTempo();
                break;
            case TUNING:
                return CreateTuning();
                break;
            case BLENDRONIC:
                return CreateBlendronic();
                break;
            case RESONANCE:
                return CreateResonance();
                break;
            case RESET:
                return CreateReset();
                break;
            case COMMENT:
                return CreateComment();
                break;
        }
    }
    void BitKlavier::Save()
    {
        for (XPiano* piano : pianoList)
        {
            for (auto it = piano->BeginPreparations(); it != piano->EndPreparations(); ++it)
            {
                appendChild(*it);
            }
            appendChild(piano);
        }
        std::string file_name = "/Applications/bitKlavier/galleries/" + to_string(*name->getValue()) + ".xml";
        XDocument xdoc(this);
        xdoc.Save(file_name);
    };
}