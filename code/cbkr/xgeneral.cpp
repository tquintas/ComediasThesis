#include "xgeneral.hpp"

namespace bkr
{
    XCompressor::XCompressor(XAttribute* c_name) : XElement(XName::bitKlavierTagNames.Equalizer, 0)
    {
        name = setAttribute(c_name);
        attrs = new XAttributeMap<Params>(this);
        DefaultParamAttributes();
    }
    void XCompressor::DefaultParamAttributes()
    {
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.CompressorParams.LookAhead(false));
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.CompressorParams.AutoAttack(false));
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.CompressorParams.AutoRelease(false));
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.CompressorParams.Power(false));
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.CompressorParams.AutoMakeup(false));
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.CompressorParams.Knee(2.0));
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.CompressorParams.InputGain(0.0));
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.CompressorParams.MakeupGain(0.0));
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.CompressorParams.Attack(0.002));
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.CompressorParams.Release(0.4));
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.CompressorParams.Thresh(-20.0));
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.CompressorParams.Ratio(3.0));
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.CompressorParams.Mix(1.0));
    }
    void XCompressor::SetParamAttribute(XAttribute* xattr)
    {
        std::string key = xattr->getComparisonString();
        if ((*attrs)[key])
        {
            attrs->UpdateCustomPair(xattr);
        }
    }
    template <typename T>
    void XCompressor::SetParamAttribute(std::string key, T value)
    {
        if ((*attrs)[key])
        {
            XAttribute* xattr = new XAttribute(key, to_string(value));
            attrs->UpdateCustomPair(xattr);
        }
    }

    XEqualizer::XEqualizer() : XElement(XName::bitKlavierTagNames.Equalizer, 0)
    {
        attrs = new XAttributeMap<Params>(this);
        DefaultParamAttributes();
    }
    void XEqualizer::DefaultParamAttributes()
    {
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.EqualizerParams.Bypassed(true));
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.EqualizerParams.LowCutBypassed(false));
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.EqualizerParams.PeakBypassed(false, 1));
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.EqualizerParams.PeakBypassed(false, 2));
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.EqualizerParams.PeakBypassed(false, 3));
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.EqualizerParams.LowCutFreq(20.0));
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.EqualizerParams.LowCutSlope(12));
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.EqualizerParams.PeakFreq(500.0, 1));
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.EqualizerParams.PeakGain(0.0, 1));
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.EqualizerParams.PeakQuality(1.0, 1));
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.EqualizerParams.PeakFreq(1000.0, 2));
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.EqualizerParams.PeakGain(0.0, 2));
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.EqualizerParams.PeakQuality(1.0, 2));
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.EqualizerParams.PeakFreq(5000.0, 3));
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.EqualizerParams.PeakGain(0.0, 3));
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.EqualizerParams.PeakQuality(1.0, 3));
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.EqualizerParams.HighCutFreq(20000.0));
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.EqualizerParams.HighCutSlope(12));
    }
    void XEqualizer::SetParamAttribute(XAttribute* xattr)
    {
        std::string key = xattr->getComparisonString();
        if ((*attrs)[key])
        {
            attrs->UpdateCustomPair(xattr);
        }
    }
    template <typename T>
    void XEqualizer::SetParamAttribute(std::string key, T value)
    {
        if ((*attrs)[key])
        {
            XAttribute* xattr = new XAttribute(key, to_string(value));
            attrs->UpdateCustomPair(xattr);
        }
    }

    XGeneral::XGeneral() : XElement(XName::bitKlavierTagNames.General, 0)
    {
        attrs = new XAttributeMap<Params>(this);
        DefaultParamAttributes();
    }
    void XGeneral::DefaultParamAttributes()
    {
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.GeneralParams.GlobalGain(1.0));
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.GeneralParams.TempoMultiplier(1.0));
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.GeneralParams.TuningFund(440.0));
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.GeneralParams.InvertSustain(false));
        attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.GeneralParams.NoteOnSetsNoteOffVelocity(false));
    }
    void XGeneral::SetParamAttribute(XAttribute* xattr)
    {
        std::string key = xattr->getComparisonString();
        if ((*attrs)[key])
        {
            attrs->UpdateCustomPair(xattr);
        }
    }
    template <typename T>
    void XGeneral::SetParamAttribute(std::string key, T value)
    {
        if ((*attrs)[key])
        {
            XAttribute* xattr = new XAttribute(key, to_string(value));
            attrs->UpdateCustomPair(xattr);
        }
    }
}