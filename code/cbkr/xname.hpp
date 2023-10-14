#ifndef XNAME_H
#define XNAME_H

#include "xtext.hpp"

namespace bkr
{
    //Class for xml tag names and attribute names
    class XName : public XNode
    {
        private:
            XText* content;
        public:
            //Set of tag names for bitKlavier
            struct BitKlavierTagStruct
            {
                XName* Gallery;
                XName* General;
                XName* Equalizer;
                XName* Compressor;
                XName* Resonance;
                XName* Keymap;
                XName* Tuning;
                XName* Tempo;
                XName* Synchronic;
                XName* Direct;
                XName* Blendronic;
                XName* Nostalgic;
                XName* Mod;
                XName* Dirty;
                XName* Params;
                XName* MidiInputs;
                XName* MidiInputIdentifiers;
                XName* Harmonizer;
                XName* Transposition;
                XName* Transposition_inc;
                XName* ADSR;
                XName* ADSRs;
                XName* ReverseADSR;
                XName* UndertowADSR;
                XName* ExportedPiano;
                XName* Piano;
                XName* Item;
                XName* Connections;
                XName* BeatMultipliers;
                XName* BeatMultipliers_inc;
                XName* BeatMultipliersStates;
                XName* BeatMultipliersStates_inc;
                XName* LengthMultipliers;
                XName* LengthMultipliers_inc;
                XName* LengthMultipliersStates;
                XName* LengthMultipliersStates_inc;
                XName* AccentMultipliers;
                XName* AccentMultipliers_inc;
                XName* AccentMultipliersStates;
                XName* AccentMultipliersStates_inc;
                XName* TranspOffsets;
                XName* TranspOffsets_inc;
                XName* TranspOffsetsStates;
                XName* TranspOffsetsStates_inc;
                XName* Beats;
                XName* DelayLengths;
                XName* SmoothLengths;
                XName* FeedbackCoefficients;
                XName* Beats_inc;
                XName* DelayLengths_inc;
                XName* SmoothLengths_inc;
                XName* FeedbackCoefficients_inc;
                XName* BeatsStates;
                XName* DelayLengthsStates;
                XName* SmoothLengthsStates;
                XName* FeedbackCoefficientsStates;
                XName* BeatsStates_inc;
                XName* DelayLengthsStates_inc;
                XName* SmoothLengthsStates_inc;
                XName* FeedbackCoefficientsStates_inc;
                XName* CustomScale;
                XName* CustomScale_inc;
                XName* AbsoluteOffsets;
                XName* AbsoluteOffsets_inc;
                XName* Springtuning;
                XName* Tethers;
                XName* Springs;
                XName* IntervalScale;
                XName* SpringMode;
                XName* ClosestKeys;
                XName* ClosestKeys_inc;
                XName* Offsets;
                XName* Offsets_inc;
                XName* Gains;
                XName* Gains_inc;
                XName* Add;
                XName* Add_inc;
                XName* T(int n)
                { 
                    XName* xt = new XName("t" + to_string(n));
                    return xt;
                };
                XName* E(int n)
                { 
                    XName* xt = new XName("e" + to_string(n));
                    return xt;
                };
            };
            static BitKlavierTagStruct bitKlavierTagNames;
            //Constructors
            XName(std::string str);
            XName(XText* text);
            XName(const XName& other);
            XName(XName&& other);
            //Destructor
            ~XName();
            //Assignments
            XName& operator=(XName&& other);
            //Get the content
            XText* getContent();
            //Set the text
            void setContent(XText* text);
            //Parse the xml
            std::string xml() override;
            //Convert to string
            friend std::string to_string(XName& other);
    };
}

#endif