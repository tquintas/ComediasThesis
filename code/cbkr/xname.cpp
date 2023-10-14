#include "xname.hpp"

namespace bkr
{

    XName::BitKlavierTagStruct XName::bitKlavierTagNames =
    {
        new XName("gallery"),
        new XName("general"),
        new XName("equalizer"),
        new XName("compressor"),
        new XName("resonance"),
        new XName("keymap"),
        new XName("tuning"),
        new XName("tempo"),
        new XName("synchronic"),
        new XName("direct"),
        new XName("blendronic"),
        new XName("nostalgic"),
        new XName("mod"),
        new XName("dirty"),
        new XName("params"),
        new XName("midiInputs"),
        new XName("midiInputIdentifiers"),
        new XName("harmonizer"),
        new XName("transposition"),
        new XName("transposition_inc"),
        new XName("ADSR"),
        new XName("ADSRs"),
        new XName("reverseADSRs"),
        new XName("undertowADSRs"),
        new XName("exportedPiano"),
        new XName("piano"),
        new XName("item"),
        new XName("connections"),
        new XName("beatMultipliers"),
        new XName("beatMultipliers_inc"),
        new XName("beatMultipliersStates"),
        new XName("beatMultipliersStates_inc"),
        new XName("lengthMultipliers"),
        new XName("lengthMultipliers_inc"),
        new XName("lengthMultipliersStates"),
        new XName("lengthMultipliersStates_inc"),
        new XName("accentMultipliers"),
        new XName("accentMultipliers_inc"),
        new XName("accentMultipliersStates"),
        new XName("accentMultipliersStates_inc"),
        new XName("transpOffsets"),
        new XName("transpOffsets_inc"),
        new XName("transpOffsetsStates"),
        new XName("transpOffsetsStates_inc"),
        new XName("beats"),
        new XName("delayLengths"),
        new XName("smoothLengths"),
        new XName("feedbackCoefficients"),
        new XName("beats_inc"),
        new XName("delayLengths_inc"),
        new XName("smoothLengths_inc"),
        new XName("feedbackCoefficients_inc"),
        new XName("beatsStates"),
        new XName("delayLengthsStates"),
        new XName("smoothLengthsStates"),
        new XName("feedbackCoefficientsStates"),
        new XName("beatsStates_inc"),
        new XName("delayLengthsStates_inc"),
        new XName("smoothLengthsStates_inc"),
        new XName("feedbackCoefficientsStates_inc"),
        new XName("customScale"),
        new XName("customScale_inc"),
        new XName("absoluteOffsets"),
        new XName("absoluteOffsets_inc"),
        new XName("springtuning"),
        new XName("tethers"),
        new XName("springs"),
        new XName("intervalScale"),
        new XName("springMode"),
        new XName("closestKeys"),
        new XName("closestKeys_inc"),
        new XName("offsets"),
        new XName("offsets_inc"),
        new XName("gains"),
        new XName("gains_inc"),
        new XName("add"),
        new XName("add_inc")
    };      
    XName::XName(std::string str) : content(new XText(str)) {};
    XName::XName(XText* text) : content(text) {};
    XName::XName(const XName& other) : content(new XText(*other.content)) {};
    XName::XName(XName&& other) : content(other.content) {};
    XName::~XName() {};
    XName& XName::operator=(XName&& other)
    {
        if (this != &other)
        {
            content = other.content;
            other.content = nullptr;
        }
        return *this;
    };
    XText* XName::getContent()
    {
        return content;
    };
    void XName::setContent(XText* text)
    {
        content = text;
    };
    std::string XName::xml()
    {
        return to_string(*content);
    };
    std::string to_string(XName &other)
    {
        return to_string(*other.content);
    }
}