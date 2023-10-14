#ifndef BITKLAVIER_H
#define BITKLAVIER_H

#include "xpiano.hpp"
#include "xkeymap.hpp"
#include "xdirect.hpp"
#include "xsynchronic.hpp"
#include "xnostalgic.hpp"
#include "xtempo.hpp"
#include "xtuning.hpp"
#include "xblendronic.hpp"
#include "xresonance.hpp"
#include "xreset.hpp"
#include "xcomment.hpp"
#include "xgeneral.hpp"

namespace bkr
{
    //Class for a bitKlavier Gallery
    class BitKlavier : public XElement
    {
        protected:
            XAttribute* name;
            XAttribute* sType;
            XAttribute* sfURL;
            XAttribute* sfInst;
            XAttribute* dfPiano;
            XGeneral* general;
            XEqualizer* eq;
            XCompressor* comp;
            std::vector<XPiano*> pianoList;
            int current_piano;
        public:
            //Module type
            enum Module
            {
                PIANO,
                KEYMAP,
                DIRECT,
                SYNCHRONIC,
                NOSTALGIC,
                TEMPO,
                TUNING,
                BLENDRONIC,
                RESONANCE,
                RESET,
                COMMENT
            };
            //Constructor
            BitKlavier(XAttribute* g_name);
            //Set default parameters
            void DefaultParamAttributes();
            //Set the General element
            void SetGeneral(XGeneral* gen);
            //Set the Equalizer element
            void SetEqualizer(XEqualizer* equalizer);
            //Set the Compressor element
            void SetCompressor(XCompressor* compressor);
            //Add a piano to the gallery
            void AddPiano(XPiano* piano);
            //Get current piano
            XPiano* GetCurrentPiano();
            //Create a preparation in the current piano, or a new piano if no current piano exists
            XPreparation* Create(Module module);
            //Create a piano
            XPiano* NextPiano();
            //Create a piano
            XPiano* NextPiano(XAttribute* name);
            //Create a Keymap module in the current piano
            XKeymap* CreateKeymap();
            //Create a Direct preparation in the current piano
            XDirect* CreateDirect();
            //Create a Synchronic preparation in the current piano
            XSynchronic* CreateSynchronic();
            //Create a Nostalgic preparation in the current piano
            XNostalgic* CreateNostalgic();
            //Create a Tempo preparation in the current piano
            XTempo* CreateTempo();
            //Create a Tuning preparation in the current piano
            XTuning* CreateTuning();
            //Create a Blendronic preparation in the current piano
            XBlendronic* CreateBlendronic();
            //Create a Resonance preparation in the current piano
            XResonance* CreateResonance();
            //Create a Reset module in the current piano
            XReset* CreateReset();
            //Create a Comment module in the current piano
            XComment* CreateComment();
            //Create a Comment module in the current piano
            XComment* CreateComment(std::string com);
            //Save the Gallery into bitKlaiver
            void Save();

    };

}

#endif