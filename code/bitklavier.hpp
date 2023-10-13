#ifndef XPIANO_H
#define XPIANO_H

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
        public:
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
            //Save the Gallery into bitKlaiver
            void Save();
    };

}

#endif