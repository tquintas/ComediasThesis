#ifndef XATTRIBUTE_H
#define XATTRIBUTE_H

#include "xname.hpp"

namespace bkr
{
    //Class for xml attributes
    class XAttribute : public XNode
    {
        private:
            XName* name;
            XText* value;
        public:
            //Set of attributes for bitKlavier
            struct bitKlavierAttributesStruct
            {
                template <typename T = const char*> XAttribute* ID(T val = T(""))
                {
                    XName* id = new XName("Id");
                    XText* txt = new XText(to_string(val));
                    XAttribute* xattr = new XAttribute(id, txt);
                    return xattr;
                };
                template <typename T = const char*> XAttribute* Name(T val = T(""))
                {
                    XName* id = new XName(fl2lc(__func__));
                    XText* txt = new XText(to_string(val));
                    XAttribute* xattr = new XAttribute(id, txt);
                    return xattr;
                };
                template <typename T = const char*> XAttribute* Alt(T val = T(""))
                {
                    XName* id = new XName(fl2lc(__func__));
                    XText* txt = new XText(to_string(val));
                    XAttribute* xattr = new XAttribute(id, txt);
                    return xattr;
                };
                template <typename T = const char*> XAttribute* D(int n, T val = T(""))
                {
                    XName* id = new XName(fl2lc(__func__)+to_string(n));
                    std::string str = to_string(val);
                    XText* txt = new XText(str);
                    XAttribute* xattr = new XAttribute(id, txt);
                    return xattr;
                };
                template <typename T = const char*> XAttribute* I(int n, T val = T(""))
                {
                    XName* id = new XName(fl2lc(__func__)+to_string(n));
                    std::string str = to_string(val);
                    XText* txt = new XText(str);
                    XAttribute* xattr = new XAttribute(id, txt);
                    return xattr;
                };
                template <typename S = const char*> XAttribute* T(int n, S val = S(""))
                {
                    XName* id = new XName(fl2lc(__func__)+to_string(n));
                    std::string str = to_string(val);
                    XText* txt = new XText(str);
                    XAttribute* xattr = new XAttribute(id, txt);
                    return xattr;
                };
                template <typename T = const char*> XAttribute* F(int n, T val = T(""))
                {
                    XName* id = new XName(fl2lc(__func__) + to_string(n));
                    std::string str = to_string(val);
                    XText* txt = new XText(str);
                    XAttribute* xattr = new XAttribute(id, txt);
                    return xattr;
                };
                template <typename T = const char*> XAttribute* B(int n, T val = T(""))
                {
                    XName* id = new XName(fl2lc(__func__) + to_string(n));
                    std::string str = to_string(val);
                    XText* txt = new XText(str);
                    XAttribute* xattr = new XAttribute(id, txt);
                    return xattr;
                };
                template <typename T = const char*> XAttribute* S(int n, T val = T(""))
                {
                    XName* id = new XName(fl2lc(__func__) + to_string(n));
                    std::string str = to_string(val);
                    XText* txt = new XText(str);
                    XAttribute* xattr = new XAttribute(id, txt);
                    return xattr;
                };
                struct GalleryParams
                {
                    template <typename T = const char*> XAttribute* SampleType(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* SoundfontURL(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* SoundfontInst(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* DefaultPiano(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                } GalleryParams;
                struct GeneralParams
                {
                    template <typename T = const char*> XAttribute* GlobalGain(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* TempoMultiplier(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* TuningFund(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* InvertSustain(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* NoteOnSetsNoteOffVelocity(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                } GeneralParams;
                struct EqualizerParams
                {
                    template <typename T = const char*> XAttribute* Bypassed(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* LowCutBypassed(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* PeakBypassed(T val = T(""), int peak = 1)
                    {
                        XName* id = new XName("peak"+to_string(peak)+"Bypassed");
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* HighCutBypassed(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* LowCutFreq(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* LowCutSlope(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* PeakFreq(T val = T(""), int peak = 1)
                    {
                        XName* id = new XName("peak"+to_string(peak)+"Freq");
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* PeakGain(T val = T(""), int peak = 1)
                    {
                        XName* id = new XName("peak"+to_string(peak)+"Gain");
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* PeakQuality(T val = T(""), int peak = 1)
                    {
                        XName* id = new XName("peak"+to_string(peak)+"Quality");
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* HighCutFreq(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* HighCutSlope(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                } EqualizerParams;
                struct CompressorParams
                {
                    template <typename T = const char*> XAttribute* Name(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* LookAhead(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* AutoAttack(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* AutoRelease(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* Power(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* AutoMakeup(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* Knee(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* InputGain(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* MakeupGain(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* Attack(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* Release(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* Thresh(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* Ratio(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* Mix(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                } CompressorParams;
                struct ItemParams
                {
                    template <typename T = const char*> XAttribute* Type(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* Text(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* Piano(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* Active(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* X(T val = T(""))
                    {
                        XName* id = new XName(__func__);
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* Y(T val = T(""))
                    {
                        XName* id = new XName(__func__);
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* W(T val = T(""))
                    {
                        XName* id = new XName(__func__);
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* H(T val = T(""))
                    {
                        XName* id = new XName(__func__);
                        XText* txt = new XText(to_string(val));
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                } ItemParams;
                struct Keymap
                {
                    template <typename T = const char*> XAttribute* K(int n, T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__)+to_string(n));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* I(int n, T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__)+to_string(n));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* TargetStates(int n, T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__)+to_string(n));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* Inverted(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* HarmonizerPreTranspose(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* HarmonizerPostTranspose(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* EndKeystrokes(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* IgnoreSustain(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* SustainPedalKeys(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* ToggleKey(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* SostenutoMode(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* AsymmetricalWarp(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* SymmetricalWarp(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* Scale(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* Offset(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* VelocityInvert(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* DefSelected(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* OsSelected(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                } Keymap;
                struct DirectParams
                {
                    template <typename T = const char*, typename S = const char*> XAttribute* Gain(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* ResGain(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* HammerGain(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* BlendronicGain(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* TranspUsesTuning(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* DirectUseGlobalSoundSet(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* DirectSoundSet(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* VelocityMin(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* VelocityMax(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* Transposition(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                } DirectParams;
                struct SynchronicParams
                {
                    template <typename T = const char*, typename S = const char*> XAttribute* Gain(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* BlendronicGain(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* NumBeats(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* ClusterMin(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* ClusterMax(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* ClusterCap(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* ClusterThresh(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* Mode(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* BeatsToSkip(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* TranspUsesTuning(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* SynchronicUseGlobalSoundSet(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* SynchronicSoundSet(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* NumClusters(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* OnOffMode(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* HoldMin(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* HoldMax(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* VelocityMin(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* VelocityMax(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* TargetTypeSynchronicPatternSync(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* TargetTypeSynchronicBeatSync(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* TargetTypeSynchronicAddNotes(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* TargetTypeSynchronicClear(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* TargetTypeSynchronicPausePlay(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* TargetTypeSynchronicDeleteOldest(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* TargetTypeSynchronicDeleteNewest(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* TargetTypeSynchronicRotate(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* MidiOutput(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* BeatMultipliers(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* BeatMultipliersStates(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* LengthMultipliers(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* LengthMultipliersStates(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* AccentMultipliers(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* AccentMultipliersStates(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* TranspOffsets(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* TranspOffsetsStates(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* ADSRs(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(to_string(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                } SynchronicParams;
                struct NostalgicParams
                {
                    template <typename T = const char*, typename S = const char*> XAttribute* Gain(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* BlendronicGain(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* WaveDistance(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* Undertow(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* Transposition(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* TranspUsesTuning(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* LengthMultiplier(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* BeatsToSkip(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* Mode(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* HoldMin(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* HoldMax(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* ClusterMin(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* ClusterThresh(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* VelocityMin(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* VelocityMax(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* KeyOnReset(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* TargetTypeNostalgicClearAll(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* NostalgicUseGlobalSoundSet(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* NostalgicSoundSet(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                } NostalgicParams;
                struct BlendronicParams
                {
                    template <typename T = const char*, typename S = const char*> XAttribute* OutGain(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* DelayBufferSize(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* Beats(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* BeatsStates(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* DelayLengths(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* DelayLengthsStates(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* SmoothLengths(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* SmoothLengthsStates(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* FeedbackCoefficients(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* FeedbackCoefficientsStates(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* TargetTypeBlendronicPatternSync(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* TargetTypeBlendronicBeatSync(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* TargetTypeBlendronicClear(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* TargetTypeBlendronicPausePlay(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* TargetTypeBlendronicOpenCloseInput(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* TargetTypeBlendronicOpenCloseOutput(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                } BlendronicParams;
                struct TempoParams
                {
                    template <typename T = const char*, typename S = const char*> XAttribute* Tempo(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* System(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* At1Mode(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* At1History(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* At1Subdivisions(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* At1Min(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* At1Max(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* Subdivisions(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                } TempoParams;
                struct ADSR
                {
                    template <typename T = const char*, typename S = const char*> XAttribute* F(int n, T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(n) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                } ADSR;
                struct TuningParams
                {
                    template <typename T = const char*, typename S = const char*> XAttribute* Scale(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*> XAttribute* ScaleName(T val = T(""))
                    {
                        XName* id = new XName(fl2lc(__func__));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* Fundamental(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* Offset(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* AdaptiveIntervalScale(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* AdaptiveInversional(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* AdaptiveAnchorScale(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* AdaptiveAnchorFund(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* AdaptiveClusterThresh(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* AdaptiveHistory(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* NToneRoot(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* NToneSemitoneWidth(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* AdaptiveSystem(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* CustomScale(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* AbsoluteOffsets(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                } TuningParams;
                struct SpringParams
                {
                    template <typename T = const char*, typename S = const char*> XAttribute* Rate(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* Drag(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* TetherStiffness(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* IntervalStiffness(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* Stiffness(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* Active(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* IntervalTuningId(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* IntervalFundamental(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* FundamentalSetsTether(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* TetherWeightGlobal(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* TetherWeightSecondaryGlobal(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                } SpringParams;
                struct ResonanceParams
                {
                    template <typename T = const char*, typename S = const char*> XAttribute* Gain(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* BlendronicGain(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* ResonanceUseGlobalSoundSet(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* ResonanceSoundSet(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* StarttimeMin(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* StarttimeMax(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* MaxSympStrings(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* FundamentalKey(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* ClosestKeys(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* Offsets(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* Gains(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                    template <typename T = const char*, typename S = const char*> XAttribute* Add(T val = T(""), S opt = S(""))
                    {
                        XName* id = new XName(fl2lc(__func__) + to_string(opt));
                        std::string str = to_string(val);
                        XText* txt = new XText(str);
                        XAttribute* xattr = new XAttribute(id, txt);
                        return xattr;
                    };
                } ResonanceParams;
            };
            //Set of attributes for bitKlavier
            static bitKlavierAttributesStruct bitKlavierAttributes;
            //Constructors
            XAttribute(XName* n, XText* val);
            XAttribute(std::string n, std::string val);
            XAttribute(XName* n);
            XAttribute(std::string n);
            XAttribute(const XAttribute& other);
            //Destructor
            ~XAttribute();
            //Parse the xml
            std::string xml() override;
            //Getters
            XName* getName();
            XText* getValue();
            //Setters
            void setName(XName* n);
            void setName(std::string n);
            void setValue(XText* val);
            void setValue(std::string val);
            //Convert attribute to string
            friend std::string to_string(const XAttribute& other);
            //Get string to compare
            std::string getComparisonString() override;
            //Copy attribute
            XAttribute* copy();
    };
}

#endif