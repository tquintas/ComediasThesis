#include <utility>
#include <cstdarg>
#include <sstream>
#include <type_traits>
#include <algorithm>
#include "serialMatrix.cpp"

namespace bkr
{
    std::mt19937 rng(std::random_device{}());
    int decimal_places = 6;
    double max_complexity = QSynth::max_complexity;
    std::string opts[4] = {"", "_inc", "_time", "_maxN"};
    std::vector<int> getKeyRange(int from = 0, int to = 128)
    {
        std::vector<int> key_range;
        for (int i = from; i < to; ++i)
        {
            key_range.push_back(i);
        };
        return key_range;
    }
    std::vector<double> getKeyWeigths(int n = 128, double mean = 60, double stddev = 6)
    {
        (n > 0) || (n = 0);
        (n <= 128) || (n = 128);
        std::vector<double> weights;
        auto normal = [mean, stddev](double x)
        {
            double coeff = 1.0 / (sqrt(2*M_PI) * stddev);
            double expo = -0.5 * pow((x - mean) / stddev, 2);
            return coeff*exp(expo);
        };
        for (double i = 0; i < n; i++) {
            double weight = normal(i);
            weights.push_back(weight);
        }
        return weights;
    }
    std::vector<int> getRandomKeys(int n, int from = 0, int to = 128, double mean = 60, double stddev = 32)
    {
        (n > 0) || (n = 0);
        (n <= 128) || (n = 128);
        std::vector<int> random_reys;
        std::vector<int> key_range = getKeyRange(from, to);
        std::vector<double> weights = getKeyWeigths(to - from, mean, stddev);
        for (int i = 0; i < n; i++) {
            std::discrete_distribution<int> discreteDistribution(weights.begin(), weights.end());
            int idx = discreteDistribution(rng);
            random_reys.push_back(key_range[idx]);
            key_range.erase(key_range.begin() + idx);
            weights.erase(weights.begin() + idx);
        };
        std::sort(random_reys.begin(), random_reys.end());
        return random_reys;
    }

    union Params {
        double d_val;
        int i_val;
        bool b_val;
        const char* s_val;
    };
    
    std::string to_string(int value)
    {
        return std::to_string(value);
    }

    std::string to_string(const char* value)
    {
        return std::string(value);
    }

    std::string to_string(const std::string& value)
    {
        return value;
    }

    std::string to_string(const bool value)
    {
        return to_string((int)value);
    }

    template<typename T>
    std::string to_string(const T& value)
    {
        return std::to_string(value);
    }

    std::string to_string(const Params& p)
    {
        if (std::is_same<decltype(p.i_val), int>::value)
        {
            return to_string(p.i_val);
        }
        else if (std::is_same<decltype(p.d_val), double>::value)
        {
            return to_string(p.d_val);
        }
        else if (std::is_same<decltype(p.b_val), bool>::value)
        {
            return to_string(p.b_val);
        }
        else if (std::is_same<decltype(p.s_val), const char*>::value)
        {
            return to_string(p.s_val);
        }
    }

    std::string fl2lc(std::string str)
    {
        for (char& c : str)
        {
            c = std::tolower(c);
            break;
        }
        return str;
    }

    std::string repeat(const char* str, int n)
    {
        std::string result;
        for (int i = 0; i < n; i++) {
            result += str;
        }
        return result;
    };

    class XNode
    {
        private:
            std::string offset;
            XNode* parent;
        public:
            XNode() : offset(""), parent(nullptr) {};
            XNode(const XNode& other) : offset(other.offset), parent(nullptr)
            {
                if (other.parent != nullptr)
                {
                    parent = new XNode;
                    *parent = *(other.parent);
                }
            };
            ~XNode() {};
            void setOffset(std::string off)
            {
                offset = off;
            };
            std::string getOffset()
            {
                offset = repeat("    ", getDepth());
                return offset;
            };
            void setParent(XNode* par)
            {
                parent = par;
            };
            XNode* getParent()
            {
                return parent;
            };
            int getDepth(int i = 0)
            {
                if (parent == nullptr) return i;
                return parent->getDepth(i+1);
            };
            bool operator==(XNode* other)
            {
                return getComparisonString() == other->getComparisonString();
            };
            virtual std::string xml()
            {
                return "";
            };
            virtual std::string getComparisonString()
            {
                return getOffset()+xml();
            };
            virtual std::pair<bool, XNode*> has_descendant(XNode* xnode)
            {
                return std::make_pair(false, nullptr);
            };
            virtual std::vector<XNode*> Descendants()
            {
                std::vector<XNode*> vect(0);
                return vect;
            };
            virtual XNode* copy()
            {
                return new XNode(*this);
            };
            virtual void ClearAttributes() {};
    };

    class XText : public XNode
    {
        private:
            std::string* content = new std::string;
        public:
            XText(std::string str) : content(new std::string(str)) {};
            XText(const XText& other) : content(nullptr), XNode(other)
            {
                if (other.content != nullptr)
                {
                    content = new std::string(*other.content);
                };
            };
            ~XText() {};
            void setContent(std::string* cont)
            {
                content = cont;
            };
            std::string* getContent()
            {
                return content;
            }
            std::string xml() override
            {
                return getOffset() + *content + "\n";
            };
            friend std::string to_string(const XText& other)
            {
                return *other.content;
            };
            template <typename T> XText operator+(const T& other) const
            {
                std::string txt = *content + *XText(to_string(other)).content;
                return XText(txt);
            };
            std::pair<bool, XNode*> has_descendant(XNode* xnode) override
            {
                bool exists = getComparisonString() == xnode->getComparisonString();
                return std::make_pair(exists, (exists ? this : nullptr));
            };
            XNode* copy() override
            {
                return new XText(*this);
            }
    };

    class XName : public XNode
    {
        private:
            XText* content;
        public:
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
            XName(std::string str) : content(new XText(str)) {};
            XName(XText* text) : content(text) {};
            XName(const XName& other) : content(new XText(*other.content)) {};
            XName(XName&& other) : content(other.content) {};
            ~XName() {};
            XName& operator=(XName&& other)
            {
                if (this != &other)
                {
                    content = other.content;
                    other.content = nullptr;
                }
                return *this;
            };
            XText* getContent()
            {
                return content;
            };
            void setContent(XText* text)
            {
                content = text;
            };
            std::string xml() override
            {
                return to_string(*content);
            };
            friend std::string to_string(const XName& other)
            {
                return to_string(*other.content);
            }
    };

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

    class XAttribute : public XNode
    {
        private:
            XName* name;
            XText* value;
        public:
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
                struct 
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
                struct
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
                struct
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
                struct
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
                struct
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
                struct
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
                struct
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
                struct
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
                struct
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
                struct
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
                struct
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
                struct
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
                struct
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
                struct
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
                struct
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
            static bitKlavierAttributesStruct bitKlavierAttributes;
            XAttribute(XName* n, XText* val) : name(n), value(val) {};
            XAttribute(std::string n, std::string val) : name(new XName(n)), value(new XText(val)) {};
            XAttribute(XName* n) : name(n), value(new XText("")) {};
            XAttribute(std::string n) : name(new XName(n)), value(new XText("")) {};
            XAttribute(const XAttribute& other) : name(new XName(*other.name)), value(new XText(*other.value)) {};
            ~XAttribute() {};
            std::string xml() override
            {
                if (value == nullptr || value->getContent() == nullptr)
                {
                    return to_string(*name);
                }
                else
                {
                    return to_string(*name)+"="+"\""+to_string(*value)+"\"";
                }
            };
            XName* getName()
            {
                return name;
            };
            XText* getValue()
            {
                return value;
            };
            void setName(XName* n)
            {
                name = n;
            };
            void setName(std::string n)
            {
                name = new XName(n);
            };
            void setValue(XText* val)
            {
                value = val;
            };
            void setValue(std::string val)
            {
                value = new XText(val);
            };
            friend std::string to_string(const XAttribute& other)
            {
                return to_string(*other.name)+"="+"\""+to_string(*other.value)+"\"";
            };
            std::string getComparisonString() override
            {
                return to_string(*name);
            };
            XAttribute* copy()
            {
                return new XAttribute(*this);
            }
    };

    XAttribute::bitKlavierAttributesStruct XAttribute::bitKlavierAttributes = {};

    class XElement : public XNode
    {
        private:
            XName* tag_name;
            std::vector<XNode*>* child_nodes;
            std::vector<XAttribute*>* attributes;
        public:
            XElement(XName* name, int n_of_childs, ...) : tag_name(name), child_nodes(nullptr), attributes(nullptr)
            {
                if (n_of_childs > 0)
                {
                    va_list args;
                    XNode* xnode;
                    va_start(args, n_of_childs);
                    for (int i = 0; i < n_of_childs; ++i)
                    {
                        xnode = va_arg(args, XNode*);
                        appendChild(xnode);
                    }
                    va_end(args);
                };
            };
            XElement(std::string str, int n_of_childs, ...) : tag_name(new XName(str)), child_nodes(nullptr), attributes(nullptr)
            {
                if (n_of_childs > 0)
                {
                    va_list args;
                    XNode* xnode;
                    va_start(args, n_of_childs);
                    for (int i = 0; i < n_of_childs; ++i)
                    {
                        xnode = va_arg(args, XNode*);
                        appendChild(xnode);
                    }
                    va_end(args);
                };
            };
            XElement(const XElement& other) : tag_name(new XName(*other.tag_name)), child_nodes(nullptr), attributes(nullptr), XNode(other)
            {
                if (other.child_nodes != nullptr)
                {
                    child_nodes = new std::vector<XNode*>{};
                    for (auto it = other.FirstChild(); it != other.LastChild(); ++it)
                    {
                        appendChild((*it)->copy());
                    };
                }
                if (other.attributes != nullptr)
                {
                    attributes = new std::vector<XAttribute*>{};
                    for (auto it = other.FirstAttribute(); it != other.LastAttribute(); ++it)
                    {
                        setAttribute((*it)->copy());
                    };
                }
            };
            ~XElement() {};
            std::string getComparisonString() override
            {
                return tag_name->xml();
            } 
            XName* getTagName()
            {
                return tag_name;
            }
            void setTagName(XName* tagname)
            {
                tag_name = tagname;
            }
            std::string xml() override
            {
                std::string joined_attrs;
                if (attributes != nullptr && !attributes->empty())
                {
                    std::vector<XAttribute*> attr_copy(attributes->size());
                    auto it = std::copy_if(attributes->begin(), attributes->end(), attr_copy.begin(), [](XAttribute* xattr) {return !(xattr->getValue()->getContent()->empty());});
                    attr_copy.erase(it, attr_copy.end());
                    std::vector<std::string> attr_copy2(attr_copy.size());
                    std::transform(attr_copy.begin(), attr_copy.end(), attr_copy2.begin(), [](XAttribute* xattr) {return xattr->xml();});
                    joined_attrs = std::accumulate(attr_copy2.begin(), attr_copy2.end(), std::string{}, [](const std::string& a, const std::string& b) {return a.empty() ? b : a + " " + b;});
                }
                else
                {
                    joined_attrs = "";
                }
                std::string offset = getOffset();
                std::string xmlstr = offset;
                if (child_nodes == nullptr || child_nodes->empty())
                {
                    xmlstr += "<" + tag_name->xml() + " " + joined_attrs + "/>\n";
                }
                else
                {
                    xmlstr += "<" + tag_name->xml() + (joined_attrs.empty() ? "" : " " + joined_attrs) + ">\n";
                    for (auto it = FirstChild(); it != LastChild(); ++it)
                    {
                        xmlstr += (*it)->xml();
                    };
                    xmlstr += offset + "</" + tag_name->xml() + ">\n";
                };
                return xmlstr;
            };
            void appendChild(XNode* childNode)
            {
                if (child_nodes == nullptr)
                {
                    child_nodes = new std::vector<XNode*>();
                }
                child_nodes->push_back(childNode);
                childNode->setParent(this);
            };
            void removeChild(XNode* tagname)
            {
                if (child_nodes == nullptr) return;
                std::string comp = tagname->getComparisonString();
                auto it = std::remove_if(child_nodes->begin(), child_nodes->end(), [comp](XNode* node) { return comp == node->getComparisonString(); });
                child_nodes->erase(it, child_nodes->end());
            }
            XAttribute* setAttribute(XAttribute* xattr)
            {
                if (attributes == nullptr)
                {
                    attributes = new std::vector<XAttribute*>();
                }
                std::pair<bool, XAttribute*> xa_pair = has_attribute(xattr);
                if (xa_pair.first)
                {
                    xa_pair.second->setValue(xattr->getValue());
                    return xa_pair.second;
                }
                else
                {
                    attributes->push_back(xattr);
                    return xattr;
                }
            };
            XAttribute* setAttribute(XName* attr_name, XText* attr_value)
            {
                XAttribute* xattr = new XAttribute(attr_name, attr_value);
                return setAttribute(xattr);
            };
            std::pair<bool, XAttribute*> has_attribute(XAttribute* xattr)
            {
                if (attributes == nullptr || attributes->size() == 0) return std::make_pair(false, nullptr);
                XAttribute* xa1;
                bool exists = std::any_of(attributes->begin(), attributes->end(), [xattr, &xa1](XAttribute* xa) {
                    if (xa->getComparisonString() == xattr->getComparisonString())
                    {
                        xa1 = xa;
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                });
                return std::make_pair(exists, xa1);
            };
            std::pair<bool, XNode*> has_element(XNode* xele)
            {
                if (child_nodes == nullptr || child_nodes->size() == 0) return std::make_pair(false, nullptr);
                XNode* xe;
                bool exists = std::any_of(child_nodes->begin(), child_nodes->end(), [xele, &xe](XNode* xnode) {
                    if (xnode->getComparisonString() == xele->getComparisonString())
                    {
                        xe = xnode;
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                });
                return std::make_pair(exists, xe);
            };
            std::pair<bool, XNode*> has_descendant(XNode* xele) override
            {
                if (child_nodes == nullptr || child_nodes->size() == 0)
                {
                    bool exists = getComparisonString() == xele->getComparisonString();
                    return std::make_pair(exists, (exists ? this : nullptr));
                };
                XNode* xe;
                bool exists = std::any_of(child_nodes->begin(), child_nodes->end(), [xele, &xe](XNode* xnode) {
                    std::pair<bool, XNode*> xe_pair = xnode->has_descendant(xele);
                    if (xe_pair.first)
                    {
                        xe = xe_pair.second;
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                });
                return std::make_pair(exists, xe);
            }
            XAttribute* removeAttribute(XAttribute* xattr)
            {
                if (attributes == nullptr) return nullptr;
                std::pair<bool, XAttribute*> xa_pair = has_attribute(xattr);
                if (xa_pair.first)
                {
                    attributes->erase(std::remove(attributes->begin(), attributes->end(), xa_pair.second), attributes->end());
                    return xa_pair.second;
                }
                else
                {
                    return nullptr;
                };
            };
            XAttribute* removeAttribute(XName* attr_name)
            {
                XAttribute* xattr = new XAttribute(attr_name);
                return removeAttribute(xattr);
            };
            XElement& operator<<(XAttribute* xattr)
            {
                setAttribute(xattr);
                return *this;
            };
            XElement& operator<<(XNode* xnode)
            {
                appendChild(xnode);
                return *this;
            };
            XNode* Element(XNode* tagname)
            {
                std::pair<bool, XNode*> xe_pair = has_descendant(tagname);
                return xe_pair.second;
            };
            XAttribute* Attribute(XAttribute* xattr)
            {
                std::pair<bool, XAttribute*> xa_pair = has_attribute(xattr);
                return xa_pair.second;
            };
            std::vector<XNode*>::iterator FirstChild() const
            {
                return child_nodes->begin();
            };
            std::vector<XNode*>::iterator LastChild() const
            {
                return child_nodes->end();
            };
            std::vector<XAttribute*>::iterator FirstAttribute() const
            {
                return attributes->begin();
            };
            std::vector<XAttribute*>::iterator LastAttribute() const
            {
                return attributes->end();
            };
            std::vector<XNode*> Descendants() override
            {
                std::vector<XNode*> vect(0);
                std::vector<XNode*> vect2;
                for (auto it = FirstChild(); it != LastChild(); ++it)
                {
                    XNode* xnode = *it;
                    vect.push_back(xnode);
                    vect2 = xnode->Descendants();
                    if (vect2.size() == 0) continue;
                    for (auto it2 = vect2.begin(); it2 != vect2.end(); ++it2)
                    {
                        vect.push_back(*it2);
                    };
                };
                return vect;
            };
            void ClearAttributes() override
            {
                if (attributes != nullptr) attributes->clear();
            };
            void ClearChildren()
            {
                if (child_nodes != nullptr) child_nodes->clear();
            };
            XElement* copy()
            {
                return new XElement(*this);
            };
    };

    template <typename T>
    class XAttributeMap : public std::map<std::string, XAttribute*>
    {
        private:
            XElement* node;
            std::string prefix;
            std::function<XAttribute*(int, T)> attr_func;
            std::function<XAttribute*(int, std::string, T)> alt_attr_func1;
            std::function<XAttribute*(std::string, T)> alt_attr_func2;
            std::function<XAttribute*(int, T, std::string)> opt_attr_func;
        public:
            XAttributeMap(XElement* main_node) : node(main_node)
            {
                prefix = "";
                alt_attr_func1 = [](int i, std::string pref, T val) { return new XAttribute(pref+to_string(i), to_string(val)); };
                alt_attr_func2 = [](std::string pref, T val) { return new XAttribute(pref, to_string(val)); };
            };
            XAttributeMap(XElement* main_node, std::string fprefix, std::function<XAttribute*(int, T)> func) : node(main_node)
            {
                attr_func = func;
                prefix = fprefix;
                alt_attr_func1 = [](int i, std::string pref, T val) { return new XAttribute(pref+to_string(i), to_string(val)); };
                alt_attr_func2 = [](std::string pref, T val) { return new XAttribute(pref, to_string(val)); };
            };
            XAttributeMap(XElement* main_node, std::string fprefix, std::function<XAttribute*(int, T, std::string)> func) : node(main_node)
            {
                opt_attr_func = func;
                prefix = fprefix;
                alt_attr_func1 = [](int i, std::string pref, T val) { return new XAttribute(pref+to_string(i), to_string(val)); };
                alt_attr_func2 = [](std::string pref, T val) { return new XAttribute(pref, to_string(val)); };
            };
            void NewPair(int key, T val)
            {
                if (!attr_func) return; 
                (*this)[prefix+std::to_string(key)] = node->setAttribute(attr_func(key, val));
            };
            void UpdatePair(int key, T val)
            {
                if ((*this)[prefix+std::to_string(key)])
                {
                    (*this)[prefix+std::to_string(key)]->setValue(to_string(val));
                }
                else
                {
                    NewPair(key, val);
                }
            };
            void NewPair(int key, T val, std::string opt)
            {
                if (!opt_attr_func) return;
                (*this)[prefix+opt+std::to_string(key)] = node->setAttribute(opt_attr_func(key, val, opt));
            };
            void UpdatePair(int key, T val, std::string opt)
            {
                if ((*this)[prefix+opt+std::to_string(key)])
                {
                    (*this)[prefix+opt+std::to_string(key)]->setValue(to_string(val));
                }
                else
                {
                    NewPair(key, val, opt);
                }
            };
            void UpdateCustomPair(std::string key, T val)
            {
                if ((*this)[key])
                {
                    (*this)[key]->setValue(to_string(val));
                }
                else
                {
                    CustomPair(key, val);
                }
            };
            void UpdateCustomPair(XAttribute* xattr)
            {
                std::string key = xattr->getComparisonString();
                if ((*this)[key])
                {
                    (*this)[key]->setValue(xattr->getValue());
                }
                else
                {
                    CustomPair(xattr);
                }
            };
            void CustomPair(std::string key, T val)
            {
                (*this)[key] = node->setAttribute(alt_attr_func2(key, val));
            };
            void CustomPair(XAttribute* xattr)
            {
                std::string key = xattr->getComparisonString();
                (*this)[key] = node->setAttribute(xattr);
            };
            void CustomPair(int key, std::string pref, T val)
            {
                (*this)[pref+std::to_string(key)] = node->setAttribute(alt_attr_func1(key, pref, val));
            };
            XElement* getNode()
            {
                return node;
            };
            XAttribute* operator()(int i)
            {
                return (*this)[prefix+to_string(i)];
            };
            XAttribute* operator()(int i, std::string pref)
            {
                return (*this)[pref+to_string(i)];
            };
            std::string getPrefix()
            {
                return prefix;
            };
            std::vector<XAttribute*>::iterator FirstAttribute() const
            {
                std::vector<XAttribute*> attrs;
                attrs.reserve(this->size());
                for (const auto& kp : *this)
                {
                    attrs.push_back(kp.second);
                }
                return attrs.begin();
            };
            std::vector<XAttribute*>::iterator LastAttribute() const
            {
                std::vector<XAttribute*> attrs;
                attrs.reserve(this->size());
                for (const auto& kp : *this)
                {
                    attrs.push_back(kp.second);
                }
                return attrs.end();
            };
            void Clear()
            {
                for (const auto& kp : *this)
                {
                    node->removeAttribute(kp.second);
                }
                this->clear();
            }
            bool HasValue(T val)
            {
                for (const auto& kp : *this) if (to_string(val) == to_string(*kp.second->getValue())) return true;
                return false;
            }
            void RemoveWithValue(T val)
            {
                for (const auto& kp : *this)
                {
                    if (to_string(val) == to_string(*kp.second->getValue()))
                    {
                        node->removeAttribute(kp.second);
                        this->erase(kp.first);
                    }
                }
            }
    };

    template <typename T>
    class XElementMap : public std::map<std::string, XAttributeMap<T>*>
    {
        private:
            XElement* node;
            std::string prefix;
            std::function<XName*(int)> name_func;
            std::function<XName*(std::string)> alt_name_func1;
        public:
            XElementMap(XElement* main_node) : node(main_node)
            {
                prefix = "";
                alt_name_func1 = [](std::string pref) { return new XName(pref); };
            }
            XElementMap(XElement* main_node, std::string fpref, std::function<XName*(int)> func) : node(main_node)
            {
                prefix = fpref;
                name_func = func;
                alt_name_func1 = [](std::string pref) { return new XName(pref); };
            };
            void AddElement(int key, std::string attr_pref, std::function<XAttribute*(int, T)> func)
            {
                if (!name_func) return;
                std::string t = prefix+std::to_string(key);
                if (this->count(t)) return;
                XElement* new_node = new XElement(name_func(key), 0);
                node->appendChild(new_node);
                (*this)[t] = new XAttributeMap<T>(new_node, attr_pref, func);
            };
            void AddCustomElement(std::string key, std::string attr_pref, std::function<XAttribute*(int, T)> func)
            {
                std::string t = key;
                if (this->count(t)) return;
                XElement* new_node = new XElement(alt_name_func1(t), 0);
                node->appendChild(new_node);
                (*this)[t] = new XAttributeMap<T>(new_node, attr_pref, func);
            };
            void AddCustomElement(XName* key, std::string attr_pref, std::function<XAttribute*(int, T)> func)
            {
                std::string t = key->xml();
                if (this->count(t)) return;
                XElement* new_node = new XElement(alt_name_func1(t), 0);
                node->appendChild(new_node);
                (*this)[t] = new XAttributeMap<T>(new_node, attr_pref, func);
            };
            void AddCustomElement(int key, std::string ele_pref, std::string attr_pref, std::function<XAttribute*(int, T)> func)
            {
                std::string t = ele_pref+std::to_string(key);
                if (this->count(t)) return;
                XElement* new_node = new XElement(alt_name_func1(t), 0);
                node->appendChild(new_node);
                (*this)[t] = new XAttributeMap<T>(new_node, attr_pref, func);
            };
            XAttributeMap<T>* operator()(int i)
            {
                return (*this)[prefix+to_string(i)];
            };
            XAttributeMap<T>* operator()(int i, std::string ele_pref)
            {
                return (*this)[ele_pref+to_string(i)];
            };
            XAttributeMap<T>* get(std::string ele_pref)
            {
                return (*this)[ele_pref];
            };
            XAttributeMap<T>* get(XName* name)
            {
                return (*this)[name->xml()];
            };
            XAttribute* operator()(int i, int j)
            {
                std::string attr_pref = (*this)[prefix+to_string(i)]->getPrefix();
                return (*(*this)[prefix+to_string(i)])[attr_pref+to_string(j)];
            };
            XAttribute* operator()(int i, int j, std::string ele_pref, std::string attr_pref)
            {
                return (*(*this)[ele_pref+to_string(i)])[attr_pref+to_string(j)];
            };
            void Clear()
            {
                this->clear();
                node->ClearChildren();
            }
            void ClearAttributes()
            {
                for (auto it = this->begin(); it != this->end(); ++it)
                {
                    it->second->Clear();
                }
            };
            void ClearChildAttributes(XName* except = nullptr)
            {
                std::string comp = except == nullptr ? "" : except->getComparisonString();
                for (auto it = node->FirstChild(); it != node->LastChild(); ++it)
                {
                    if ((*it)->getComparisonString() == comp) continue;
                    (*it)->ClearAttributes();
                };
            }
    };

    class XDocument : public XNode
    {
        protected:
            XElement* root;
        public:
            XDocument(XElement* xele) : root(xele) {};
            XDocument(const XDocument& other) : root(other.root) {};
            XDocument(XDocument&& other) : root(other.root)
            {
                other.root = nullptr;
            };
            ~XDocument() {};
            XDocument& operator=(XDocument&& other)
            {
                if (this != &other)
                {
                    root = other.root;
                    other.root = nullptr;
                };
                return *this;
            };
            void Save(std::string file_name = "xmlDocument.xml")
            {
                std::ofstream fs(file_name);
                if (fs.is_open())
                {
                    std::string long_string = root->xml();
                    int wrap = 75;
                    std::stringstream ss;
                    int length = 0;
                    bool min_idx = false;
                    int params_idx = 0;
                    for (char c : long_string)
                    {
                        if (length >= wrap && c == ' ')
                        {
                            ss << "\n";
                            ss << repeat(" ", params_idx);
                            length = 0;
                        }
                        else
                        {
                            ss << c;
                            c == '\n' && (length = -1);
                        }
                        c == '<' && (min_idx = true);
                        if (min_idx && c == ' ')
                        {
                            params_idx = length + 1;
                            min_idx = false;
                        }
                        c == '>' && ((params_idx = 0) || (min_idx = false));
                        length++;
                    }
                    fs << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
                    fs << ss.str();
                    std::cout << "File saved as " << file_name << "." << std::endl;
                }
                else
                {
                    std::cerr << "Unable to open file " << file_name << "." << std::endl;
                };
            }
    };

    class XPreparation : public XElement
    {
        protected:
            XAttribute* ID;
            XAttribute* name;
            XAttribute* alt;
            XElement* Item;
            XElement* item;
            XAttribute* piano;
            XAttribute* active;
            XAttribute* text;
            XAttribute* type;
            struct {
                XAttribute* x;
                XAttribute* y;
                XAttribute* w;
                XAttribute* h;
            } position;
            XElement* connections;
            bool just_item = false;
            XAttributeMap<bool>* dirty;
            XElement* dirty_element;
            int itype;
            int mod_itype;
            bool moded;
        public:
            XPreparation(XAttribute* id, XAttribute* prep_name, XName* tag_name, int type, int dn, int modtype) : XElement(tag_name, 0), itype(type), mod_itype(modtype), moded(false)
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
            void createItem()
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
            void ChangePiano(XText* val)
            {
                piano->setValue(val);
            }
            XElement* getItem()
            {
                return Item;
            }
            void Connect(XPreparation* node)
            {
                connections->appendChild(node->item);
            };
            bool IsJustItem()
            {
                return just_item;
            }
            void Mod()
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
            void GetDirty(int i)
            {
                dirty->UpdatePair(i, true);
            }
            void Save(std::string file_name = "xmlPreparation.xml")
            {
                XDocument xdoc(this);
                xdoc.Save(file_name);
            };
    };

    class XPiano : public XPreparation
    {
        protected:
            std::vector<XPreparation*> preparations;
        public:
            XPiano(XAttribute* id, XAttribute* name) : XPreparation(id, name, XName::bitKlavierTagNames.Piano, 12, 0, 0) {};
            void AddPreparation(XPreparation* prep)
            {
                appendChild(prep->getItem());
                if (!prep->IsJustItem()) preparations.push_back(prep);
            };
            void TriggeredBy(XPreparation* keynote)
            {
                keynote->ChangePiano(ID->getValue());
                Connect(keynote);
            }
            std::vector<XPreparation*>::iterator BeginPreparations()
            {
                return preparations.begin();
            }
            std::vector<XPreparation*>::iterator EndPreparations()
            {
                return preparations.end();
            }
            void Mod() {};
    };

    class XKeymap : public XPreparation
    {
        protected:
            XElement* midiInputs;
            XElement* midiInputIdentifiers;
            XAttributeMap<int>* keys;
            XAttributeMap<bool>* options;
            XAttributeMap<bool>* t_states;
            XAttributeMap<double>* vel_curve;
            XElementMap<int>* harmonizer;
        public:
            XKeymap(XAttribute* id, XAttribute* name) : XPreparation(id, name, XName::bitKlavierTagNames.Keymap, 5, 0, 0)
            {
                midiInputs = new XElement(XName::bitKlavierTagNames.MidiInputs, 0);
                midiInputIdentifiers = new XElement(XName::bitKlavierTagNames.MidiInputIdentifiers, 0);
                XElement* harm = new XElement(XName::bitKlavierTagNames.Harmonizer, 0);
                appendChild(harm);
                harmonizer = new XElementMap<int>(harm, "t", [](int i) { return XName::bitKlavierTagNames.T(i); });
                keys = new XAttributeMap<int>(this, "k", [](int i, int j) { return XAttribute::bitKlavierAttributes.Keymap.K<int>(i, j); });
                options = new XAttributeMap<bool>(this);
                t_states = new XAttributeMap<bool>(this, "targetStates", [](int i, bool j) { return XAttribute::bitKlavierAttributes.Keymap.TargetStates<bool>(i, j); });
                vel_curve = new XAttributeMap<double>(this);
                for (int i = 0; i < 128; ++i)
                {
                    harmonizer->AddElement(i, "i", [](int i, int j) { return XAttribute::bitKlavierAttributes.Keymap.I<int>(i, j); });
                    (*harmonizer)(i)->NewPair(0, i);
                };
                AllDefault();
            };
            void AllDefault()
            {
                Full();
                DefaultStates();
                DefaultOptions();
                DefaultVelocityCurving();
                DefaultHarmonizer();
            };
            void DefaultStates()
            {
                for (int i = 0; i < 22; ++i)
                {
                    bool v = (i < 2 || i == 10 || i >= 17);
                    t_states->UpdatePair(i, v);
                };
            }
            void SetTargetState(int key, bool val)
            {
                t_states->UpdatePair(key, val);
            }
            void DefaultOptions()
            {
                options->UpdateCustomPair(XAttribute::bitKlavierAttributes.Keymap.HarmonizerPreTranspose<bool>(false));
                options->UpdateCustomPair(XAttribute::bitKlavierAttributes.Keymap.HarmonizerPostTranspose<bool>(false));
                options->UpdateCustomPair(XAttribute::bitKlavierAttributes.Keymap.EndKeystrokes<bool>(false));
                options->UpdateCustomPair(XAttribute::bitKlavierAttributes.Keymap.IgnoreSustain<bool>(false));
                options->UpdateCustomPair(XAttribute::bitKlavierAttributes.Keymap.SustainPedalKeys<bool>(false));
                options->UpdateCustomPair(XAttribute::bitKlavierAttributes.Keymap.ToggleKey<bool>(false));
                options->UpdateCustomPair(XAttribute::bitKlavierAttributes.Keymap.SostenutoMode<bool>(false));
            };
            void SetOptionAttribute(XAttribute* xattr)
            {
                std::string key = xattr->getComparisonString();
                if ((*options)[key])
                {
                    options->UpdateCustomPair(xattr);
                }
            }
            template <typename T>
            void SetOptionAttribute(std::string key, T value)
            {
                if ((*options)[key])
                {
                    XAttribute* xattr = new XAttribute(key, to_string(value));
                    options->UpdateCustomPair(xattr);
                }
            }
            void Full()
            {
                for (int i = 0; i < 128; ++i)
                {
                    keys->UpdatePair(i, i);
                };
            };
            void AddKey(int k)
            {
                int c = keys->size();
                keys->NewPair(c, k);
            }
            void AddKeys(std::vector<int> k)
            {
                int c = keys->size();
                for (int i = 0; i < k.size(); i++)
                {
                    keys->NewPair(c+i, k[i]);
                }
            }
            template <typename... A>
            void AddKeys(A... ks)
            {
                (AddKey(ks), ...);
            }
            void SetKeys(std::vector<int> k)
            {
                keys->Clear();
                AddKeys(k);
            }
            template <typename... A>
            void SetKeys(A... ks)
            {
                keys->Clear();
                (AddKey(ks), ...);
            }
            void ClearKeys()
            {
                keys->clear();
            };
            void DefaultVelocityCurving()
            {
                vel_curve->UpdateCustomPair(XAttribute::bitKlavierAttributes.Keymap.AsymmetricalWarp<double>(1.0));
                vel_curve->UpdateCustomPair(XAttribute::bitKlavierAttributes.Keymap.SymmetricalWarp<double>(1.0));
                vel_curve->UpdateCustomPair(XAttribute::bitKlavierAttributes.Keymap.Scale<double>(1.0));
                vel_curve->UpdateCustomPair(XAttribute::bitKlavierAttributes.Keymap.Offset<double>(0.0));
                options->UpdateCustomPair(XAttribute::bitKlavierAttributes.Keymap.VelocityInvert<bool>(false));
            };
            void SetAsymmetricalWarp(double val)
            {
                val >= 0.0 || (val = 0.0);
                vel_curve->UpdateCustomPair(XAttribute::bitKlavierAttributes.Keymap.AsymmetricalWarp<double>(val));
            };
            void SetSymmetricalWarp(double val)
            {
                val >= 0.0 || (val = 0.0);
                vel_curve->UpdateCustomPair(XAttribute::bitKlavierAttributes.Keymap.SymmetricalWarp<double>(val));
            };
            void SetScale(double val)
            {
                val >= 0.0 || (val = 0.0);
                vel_curve->UpdateCustomPair(XAttribute::bitKlavierAttributes.Keymap.Scale<double>(val));
            };
            void SetOffset(double val)
            {
                (val >= -1.0 || (val = -1.0)) && (val <= 1.0 || (val = 1.0));
                vel_curve->UpdateCustomPair(XAttribute::bitKlavierAttributes.Keymap.Offset<double>(val));
            };
            void InvertVelocity(bool val)
            {
                options->UpdateCustomPair(XAttribute::bitKlavierAttributes.Keymap.VelocityInvert<bool>(val));
            };
            void SetVelocityCurving(double asymm_wrap, double symm_wrap, double scale, double voffset, bool invert)
            {
                SetAsymmetricalWarp(asymm_wrap);
                SetSymmetricalWarp(symm_wrap);
                SetScale(scale);
                SetOffset(voffset);
                InvertVelocity(invert);
            };
            void RandomVelocityCurving(int df = 5, double exp_val = 3, double offset_variance = 0.1)
            {
                std::chi_squared_distribution<double> chi(df);
                std::normal_distribution<double> norm(0, offset_variance);
                std::bernoulli_distribution bern(0.3);
                auto re_scale = [](double val) {return exp((log(11) / 10)*val)-1.0; };
                const double n = exp_val / re_scale((double)df);
                double asymm_wrap = re_scale(chi(rng)) * n;
                double symm_wrap = re_scale(chi(rng)) * n;
                double scale = re_scale(chi(rng)) * n;
                double voffset = norm(rng);
                bool invert = bern(rng);
                SetVelocityCurving(asymm_wrap, symm_wrap, scale, voffset, invert);
            };
            void DefaultHarmonizer()
            {
                harmonizer->ClearAttributes();
                for (int i = 0; i < 128; ++i)
                {
                    (*harmonizer)(i)->NewPair(0, i);
                };
            };
            void RandomRangeHarmonizer(int n = 12, int lowestHarm = 0, int highestHarm = 127, int lowestKey = 0, int highestKey = 127, bool with_root = true)
            {
                std::uniform_int_distribution<int> dist(lowestHarm, highestHarm);
                for (int i = lowestKey; i <= highestKey; ++i)
                {
                    std::vector<int> is;
                    if (with_root) is.push_back(i);
                    while (is.size() != (n+with_root))
                    {
                        int r = dist(rng);
                        if (std::find(is.begin(), is.end(), r) != is.end()) continue;
                        is.push_back(r);
                    };
                    std::sort(is.begin(), is.end());
                    (*harmonizer)(i)->Clear();
                    for (int j = 0; j < is.size(); ++j)
                    {
                        (*harmonizer)(i)->NewPair(j, is[j]);
                    };
                };
            };
            void AddRandomRangeHarmonizer(int n = 3, int lowestHarm = 0, int highestHarm = 127, int lowestKey = 0, int highestKey = 127)
            {
                std::uniform_int_distribution<int> dist(lowestHarm, highestHarm);
                for (int i = lowestKey; i <= highestKey; ++i)
                {
                    std::vector<int> is;
                    XAttributeMap<int>* harm_i = (*harmonizer)(i);
                    for (auto it = harm_i->FirstAttribute(); it != harm_i->LastAttribute(); ++it)
                    {
                        is.push_back(std::stoi((*it)->getValue()->getComparisonString()));
                    }
                    int m = is.size();
                    while (is.size() != m+n)
                    {
                        int r = dist(rng);
                        if (std::find(is.begin(), is.end(), r) != is.end()) continue;
                        is.push_back(r);
                    };
                    std::sort(is.begin(), is.end());
                    for (int j = 0; j < is.size(); ++j)
                    {
                        harm_i->UpdatePair(j, is[j]);
                    };
                };
            };
            void RandomSparseHarmonizer(int n = 12, double sparseness = 0.5, int lowestHarm = 0, int highestHarm = 127, int lowestKey = 0, int highestKey = 127, bool with_root = true)
            {
                std::uniform_int_distribution<int> dist(lowestHarm, highestHarm);
                std::bernoulli_distribution bern(sparseness);
                for (int i = lowestKey; i <= highestKey; ++i)
                {
                    if (bern(rng)) continue;
                    std::vector<int> is;
                    if (with_root) is.push_back(i);
                    while (is.size() != (n+with_root))
                    {
                        int r = dist(rng);
                        if (std::find(is.begin(), is.end(), r) != is.end()) continue;
                        is.push_back(r);
                    };
                    std::sort(is.begin(), is.end());
                    (*harmonizer)(i)->Clear();
                    for (int j = 0; j < is.size(); ++j)
                    {
                        (*harmonizer)(i)->NewPair(j, is[j]);
                    };
                };
            };
            void RandomHarmonizer(int n = 12, double density = 0.5, int lowestHarm = 0, int highestHarm = 127, std::vector<int> ks = {60}, bool with_root = true)
            {
                std::uniform_int_distribution<int> dist(lowestHarm, highestHarm);
                std::bernoulli_distribution bern(density);
                for (int i : ks)
                {
                    std::vector<int> is;
                    if (with_root) is.push_back(i);
                    while (is.size() != (n+with_root))
                    {
                        int r = dist(rng);
                        if (std::find(is.begin(), is.end(), r) != is.end()) continue;
                        is.push_back(r);
                    };
                    //std::sort(is.begin(), is.end());
                    (*harmonizer)(i)->Clear();
                    for (int j = 0; j < is.size(); ++j)
                    {
                        (*harmonizer)(i)->NewPair(j, is[j]);
                        if (bern(rng)) break;
                    };
                };
            };
            void AddRandomSparseHarmonizer(int n = 3, double sparseness = 0.5, int lowestHarm = 0, int highestHarm = 127, int lowestKey = 0, int highestKey = 127)
            {
                std::uniform_int_distribution<int> dist(lowestHarm, highestHarm);
                std::bernoulli_distribution bern(sparseness);
                for (int i = lowestKey; i <= highestKey; ++i)
                {
                    if (bern(rng)) continue;
                    std::vector<int> is;
                    XAttributeMap<int>* harm_i = (*harmonizer)(i);
                    for (auto it = harm_i->FirstAttribute(); it != harm_i->LastAttribute(); ++it)
                    {
                        is.push_back(std::stoi((*it)->getValue()->getComparisonString()));
                    }
                    int m = is.size();
                    while (is.size() != m+n)
                    {
                        int r = dist(rng);
                        if (std::find(is.begin(), is.end(), r) != is.end()) continue;
                        is.push_back(r);
                    };
                    std::sort(is.begin(), is.end());
                    for (int j = 0; j < is.size(); ++j)
                    {
                        harm_i->UpdatePair(j, is[j]);
                    };
                };
            };
            void RandomKeymap(int complexity)
            {
                double val = complexity / max_complexity;
                int n_of_notes = floor(val * 128)+1;
                int n_of_harms = floor(val * 13);
                int inter = floor((1.0-val) * 64);
                double density = (1.0-val) * 0.5;
                std::vector<int> randK = getRandomKeys(n_of_notes);
                SetKeys(randK);
                RandomVelocityCurving();
                RandomHarmonizer(n_of_harms, density, inter, 128 - inter, randK);
            }
            void Mod() {};
            void Save(std::string file_name = "XKeymap.xml")
            {
                file_name = "/Applications/bitKlavier/preparations/Keymap" + file_name;
                XDocument xdoc(this);
                xdoc.Save(file_name);
            };
    };

    class XDirect : public XPreparation
    {
        protected:
            XAttributeMap<double>* transposition;
            XAttributeMap<double>* transposition_inc;
            XAttributeMap<double>* ADSR;
            XAttributeMap<Params>* param_attrs;
            std::map<std::string, int> ds = {
                {"?", 0},
                {"transposition", 1},
                {"gain", 2},
                {"resGain", 3},
                {"hammerGain", 4},
                {"blendronicGain", 5},
                {"??", 6},
                {"adsr", 7},
                {"transpUsesTuning", 8},
                {"directUseGlobalSoundSet", 9},
                {"directSoundSet", 10},
                {"velocityMin", 11},
                {"velocityMax", 12}
            };
        public:
            XDirect(XAttribute* id, XAttribute* name) : XPreparation(id, name, XName::bitKlavierTagNames.Direct, 0, 13, 6)
            {
                XElement* params = new XElement(XName::bitKlavierTagNames.Params, 0);
                appendChild(params);
                XElement* transp = new XElement(XName::bitKlavierTagNames.Transposition, 0);
                XElement* transp_inc = new XElement(XName::bitKlavierTagNames.Transposition_inc, 0);
                XElement* adsr = new XElement(XName::bitKlavierTagNames.ADSR, 0);
                params->appendChild(transp);
                params->appendChild(transp_inc);
                params->appendChild(adsr);
                transposition = new XAttributeMap<double>(transp, "f", [](int i, double j) { return XAttribute::bitKlavierAttributes.F<double>(i, j); });
                transposition_inc = new XAttributeMap<double>(transp_inc, "f", [](int i, double j) { return XAttribute::bitKlavierAttributes.F<double>(i, j); });
                ADSR = new XAttributeMap<double>(adsr, "f", [](int i, double j, std::string o) { return XAttribute::bitKlavierAttributes.ADSR.F<double, std::string>(i, j, o); });
                param_attrs = new XAttributeMap<Params>(params);
                AllDefault();
            };
            void AllDefault()
            {
                DefaultParamAttributes();
                DefaultADSR();
                DefaultTranspositions();
            };
            void DefaultParamAttributes()
            {
                bool first = true;
                for (std::string opt : opts)
                {
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.DirectParams.Gain((first ? 1.0 : 0.0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.DirectParams.ResGain((first ? 0.5 : 0.0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.DirectParams.HammerGain((first ? 0.5 : 0.0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.DirectParams.BlendronicGain((first ? 1.0 : 0.0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.DirectParams.VelocityMin(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.DirectParams.VelocityMax((first ? 127 : 0), opt));
                    if (opt == "_inc") continue;
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.DirectParams.TranspUsesTuning(false, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.DirectParams.DirectUseGlobalSoundSet(first, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.DirectParams.DirectSoundSet("", opt));
                    if (opt == "") continue;
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.DirectParams.Transposition(0, opt));
                    first = false;
                };
            };
            void SetParamAttribute(XAttribute* xattr)
            {
                std::string key = xattr->getComparisonString();
                if ((*param_attrs)[key])
                {
                    param_attrs->UpdateCustomPair(xattr);
                    if (ds[key]) GetDirty(ds[key]);
                }
            }
            template <typename T>
            void SetParamAttribute(std::string key, T value)
            {
                if ((*param_attrs)[key])
                {
                    XAttribute* xattr = new XAttribute(key, to_string(value));
                    param_attrs->UpdateCustomPair(xattr);
                    if (ds[key]) GetDirty(ds[key]);
                }
            }
            void DefaultADSR()
            {
                bool first = true;
                for (std::string opt : opts)
                {
                    ADSR->UpdatePair(0, (first ? 2.0 : 0.0), opt);
                    ADSR->UpdatePair(1, (first ? 5.0 : 0.0), opt);
                    ADSR->UpdatePair(2, (first ? 0.9 : 0.0), opt);
                    ADSR->UpdatePair(3, (first ? 250.0 : 0.0), opt);
                    first = false;
                };
            };
            void SetAttack(double a, std::string opt = "")
            {
                a >= 0.0 || (a = 0.0);
                if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
                ADSR->UpdatePair(0, a, opt);
            };
            void SetDecay(double d, std::string opt = "")
            {
                d >= 0.0 || (d = 0.0);
                if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
                ADSR->UpdatePair(1, d, opt);
            };
            void SetSustain(double s, std::string opt = "")
            {
                (s <= 1.0 || (s = 1.0)) && (s >= 0.0 || (s = 0.0));
                if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
                ADSR->UpdatePair(2, s, opt);
            };
            void SetRelease(double r, std::string opt = "")
            {
                r >= 0.0 || (r = 0.0);
                if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
                ADSR->UpdatePair(3, r, opt);
            };
            void SetADSR(double a, double d, double s, double r, std::string opt = "")
            {
                SetAttack(a, opt);
                SetDecay(d, opt);
                SetSustain(s, opt);
                SetRelease(r, opt);
            };
            void RandomADSR(int df = 5, double a_exp_val = 2.0, double d_exp_val = 5.0, double s_exp_val = 0.7, double r_exp_val = 250.0, double s_var = 0.1, std::string opt = "")
            {
                std::chi_squared_distribution<double> chi(df);
                std::normal_distribution<double> norm(s_exp_val, s_var);
                auto re_scale = [](double val) {return exp((log(1001) / 10)*val)-1.0; };
                double scaled = re_scale((double)df);
                double a = re_scale(chi(rng)) * (a_exp_val / scaled);
                double d = re_scale(chi(rng)) * (d_exp_val / scaled);
                double s = norm(rng);
                double r = re_scale(chi(rng)) * (r_exp_val / scaled);
                SetADSR(a, d, s, r, opt);
            };
            void DefaultTranspositions()
            {
                transposition->Clear();
                transposition_inc->Clear();
                transposition->UpdatePair(0, 0.0);
                transposition_inc->UpdatePair(0, 0.0);
            };
            void AddTransposition(double n)
            {
                int i = transposition->size();
                transposition->NewPair(i, n);
            };
            template <typename... A>
            void SetTranspositions(A... n)
            {
                transposition->Clear();
                ((AddTransposition(n)), ...);
            };
            template <typename... A>
            void AddTranspositions(A... n)
            {
                ((AddTransposition(n)), ...);
            };
            void RandomTranspositionsGauss(int n = 3, double exp_int = 0, double var_int = 7, char slope = 'e', bool root = true, bool integer = false)
            {
                transposition->Clear();
                std::normal_distribution<double> norm(exp_int, var_int);
                auto e_slope = [var_int](double val)
                {
                    if (val >= 0) return pow((var_int + 1.0), (val / var_int)) - 1.0;
                    else return -(pow((var_int + 1.0), (-val / var_int)) - 1.0);
                };
                auto l_slope = [var_int](double val)
                {
                    if (val >= 0) return var_int * (log(val + 1.0) / log(var_int + 1.0));
                    else return -(var_int * (log(-val + 1.0) / log(var_int + 1.0)));
                };
                auto round = [integer](double val) { return integer ? std::round(val) : val; };
                std::vector<double> vals;
                if (root) vals.push_back(0.0);
                while (vals.size() != n + root)
                {
                    double val = slope == 'e' ? e_slope(norm(rng)) : slope == 'l' ? l_slope(norm(rng)) : norm(rng);
                    if (std::find(vals.begin(), vals.end(), round(val)) != vals.end()) continue;
                    vals.push_back(round(val));
                };
                std::sort(vals.begin(), vals.end());
                for (int i = 0; i < vals.size(); ++i)
                {
                    transposition->NewPair(i, vals[i]);
                }
            };
            void RandomTranspositionsChiSquared(int n = 3, bool above = true, int df = 5, double exp_int = 7, double max_int = 12, char slope = 'e', bool root = true, bool integer = false)
            {
                transposition->Clear();
                std::chi_squared_distribution<double> chi(df);
                auto e_slope = [max_int](double val) { return pow((max_int + 1.0), (val / max_int)) - 1.0; };
                auto l_slope = [max_int](double val) { return max_int * (log(val + 1.0) / log(max_int + 1.0)); };
                double scaled = slope == 'e' ? exp_int / e_slope((double)df) : slope == 'l' ? exp_int / l_slope((double)df) : exp_int / df;
                auto round = [integer](double val) { return integer ? std::round(val) : val; };
                std::vector<double> vals;
                if (root) vals.push_back(0.0);
                int sig = above ? 1 : -1;
                while (vals.size() != n + root)
                {
                    double val = slope == 'e' ? e_slope(chi(rng)) : slope == 'l' ? l_slope(chi(rng)) : chi(rng);
                    val *= scaled*sig;
                    if (std::find(vals.begin(), vals.end(), round(val)) != vals.end()) continue;
                    vals.push_back(round(val));
                };
                std::sort(vals.begin(), vals.end());
                for (int i = 0; i < vals.size(); ++i)
                {
                    transposition->NewPair(i, vals[i]);
                }
            };
            void AddRandomTranspositionsGauss(int n = 3, double exp_int = 0, double var_int = 7, char slope = 'e', bool integer = false)
            {
                std::normal_distribution<double> norm(exp_int, var_int);
                auto e_slope = [var_int](double val)
                {
                    if (val >= 0) return pow((var_int + 1.0), (val / var_int)) - 1.0;
                    else return -(pow((var_int + 1.0), (-val / var_int)) - 1.0);
                };
                auto l_slope = [var_int](double val)
                {
                    if (val >= 0) return var_int * (log(val + 1.0) / log(var_int + 1.0));
                    else return -(var_int * (log(-val + 1.0) / log(var_int + 1.0)));
                };
                int size = transposition->size();
                auto round = [integer](double val) { return integer ? std::round(val) : val; };
                std::vector<double> vals;
                for (auto it = transposition->FirstAttribute(); it != transposition->LastAttribute(); ++it)
                {
                    vals.push_back(std::stod((*it)->getValue()->getComparisonString()));
                }
                while (vals.size() != n + size)
                {
                    double val = slope == 'e' ? e_slope(norm(rng)) : slope == 'l' ? l_slope(norm(rng)) : norm(rng);
                    if (std::find(vals.begin(), vals.end(), round(val)) != vals.end()) continue;
                    vals.push_back(round(val));
                };
                std::sort(vals.begin(), vals.end());
                for (int i = 0; i < vals.size(); ++i)
                {
                    transposition->UpdatePair(i, vals[i]);
                }
            };
            void AddRandomTranspositionsChiSquared(int n = 3, bool above = true, int df = 5, double exp_int = 7, double max_int = 12, char slope = 'e', bool integer = false)
            {
                std::chi_squared_distribution<double> chi(df);
                auto e_slope = [max_int](double val) { return pow((max_int + 1.0), (val / max_int)) - 1.0; };
                auto l_slope = [max_int](double val) { return max_int * (log(val + 1.0) / log(max_int + 1.0)); };
                double scaled = slope == 'e' ? exp_int / e_slope((double)df) : slope == 'l' ? exp_int / l_slope((double)df) : exp_int / df;
                int size = transposition->size();
                auto round = [integer](double val) { return integer ? std::round(val) : std::round(val * 1000) / 100; };
                std::vector<double> vals;
                int sig = above ? 1 : -1;
                for (auto it = transposition->FirstAttribute(); it != transposition->LastAttribute(); ++it)
                {
                    vals.push_back(std::stod((*it)->getValue()->getComparisonString()));
                }
                while (vals.size() != n + size)
                {
                    double val = slope == 'e' ? e_slope(chi(rng)) : slope == 'l' ? l_slope(chi(rng)) : chi(rng);
                    val *= scaled*sig;
                    if (std::find(vals.begin(), vals.end(), round(val)) != vals.end()) continue;
                    vals.push_back(round(val));
                };
                std::sort(vals.begin(), vals.end());
                for (int i = 0; i < vals.size(); ++i)
                {
                    transposition->UpdatePair(i, vals[i]);
                }
            };
            void RandomDirect(int complexity)
            {
                double val = complexity / max_complexity;
                int n_of_notes = floor(val * 13);
                RandomTranspositionsGauss(n_of_notes, 0.0, val*7.0, 'e', true, complexity < max_complexity/2);
                RandomADSR(n_of_notes+1, 2.0, 5.0, 0.7, 250.0, val*5.0);
            };
            void Save(std::string file_name = "XDirect.xml")
            {
                std::string extra = moded ? "Mod/" : "/";
                file_name = "/Applications/bitKlavier/preparations/Direct" + extra + file_name;
                XDocument xdoc(this);
                xdoc.Save(file_name);
            };
    };

    class XSynchronic : public XPreparation
    {
        protected:
            XAttributeMap<Params>* param_attrs;
            XElementMap<double>* beats;
            XElementMap<bool>* states;
            XElementMap<double>* ADSRs;
            XElementMap<double>* transp_offsets;
            std::map<std::string, int> ds = {
                {"?", 0},
                {"numBeats", 1},
                {"clusterMin", 2},
                {"clusterMax", 3},
                {"clusterCap", 4},
                {"clusterThresh", 5},
                {"mode", 6},
                {"beatsToSkip", 7},
                {"transpOffsets", 8},
                {"accentMultipliers", 9},
                {"lengthMultipliers", 10},
                {"beatMultipliers", 11},
                {"gain", 12},
                {"ADSRs", 13},
                {"onOffMode", 14},
                {"numClusters", 15},
                {"holdMin", 16},
                {"holdMax", 17},
                {"velocityMin", 18},
                {"velocityMax", 19},
                {"midiOutput", 20},
                {"transpUsesTuning", 21},
                {"??", 22},
                {"synchronicUseGlobalSoundSet", 23},
                {"synchronicSoundSet", 24}
            };
        public:
            XSynchronic(XAttribute* id, XAttribute* name) : XPreparation(id, name, XName::bitKlavierTagNames.Synchronic, 1, 25, 7)
            {
                XElement* params = new XElement(XName::bitKlavierTagNames.Params, 0);
                XElement* adsrs = new XElement(XName::bitKlavierTagNames.ADSRs, 0);
                XElement* toff = new XElement(XName::bitKlavierTagNames.TranspOffsets, 0);
                params->appendChild(toff);
                params->appendChild(adsrs);
                appendChild(params);
                param_attrs = new XAttributeMap<Params>(params);
                beats = new XElementMap<double>(params);
                states = new XElementMap<bool>(params);
                ADSRs = new XElementMap<double>(adsrs, "e", [](int i) { return XName::bitKlavierTagNames.E(i); });
                transp_offsets = new XElementMap<double>(toff, "t", [](int i) { return XName::bitKlavierTagNames.T(i); });
                beats->AddCustomElement(XName::bitKlavierTagNames.BeatMultipliers, "f", [](int i, double j){ return XAttribute::bitKlavierAttributes.F<double>(i, j); });
                beats->AddCustomElement(XName::bitKlavierTagNames.BeatMultipliers_inc, "f", [](int i, double j){ return XAttribute::bitKlavierAttributes.F<double>(i, j); });
                states->AddCustomElement(XName::bitKlavierTagNames.BeatMultipliersStates, "b", [](int i, bool j){ return XAttribute::bitKlavierAttributes.B<bool>(i, j); });
                states->AddCustomElement(XName::bitKlavierTagNames.BeatMultipliersStates_inc, "b", [](int i, bool j){ return XAttribute::bitKlavierAttributes.B<bool>(i, j); });
                beats->AddCustomElement(XName::bitKlavierTagNames.LengthMultipliers, "f", [](int i, double j){ return XAttribute::bitKlavierAttributes.F<double>(i, j); });
                beats->AddCustomElement(XName::bitKlavierTagNames.LengthMultipliers_inc, "f", [](int i, double j){ return XAttribute::bitKlavierAttributes.F<double>(i, j); });
                states->AddCustomElement(XName::bitKlavierTagNames.LengthMultipliersStates, "b", [](int i, bool j){ return XAttribute::bitKlavierAttributes.B<bool>(i, j); });
                states->AddCustomElement(XName::bitKlavierTagNames.LengthMultipliersStates_inc, "b", [](int i, bool j){ return XAttribute::bitKlavierAttributes.B<bool>(i, j); });
                beats->AddCustomElement(XName::bitKlavierTagNames.AccentMultipliers, "f", [](int i, double j){ return XAttribute::bitKlavierAttributes.F<double>(i, j); });
                beats->AddCustomElement(XName::bitKlavierTagNames.AccentMultipliers_inc, "f", [](int i, double j){ return XAttribute::bitKlavierAttributes.F<double>(i, j); });
                states->AddCustomElement(XName::bitKlavierTagNames.AccentMultipliersStates, "b", [](int i, bool j){ return XAttribute::bitKlavierAttributes.B<bool>(i, j); });
                states->AddCustomElement(XName::bitKlavierTagNames.AccentMultipliersStates_inc, "b", [](int i, bool j){ return XAttribute::bitKlavierAttributes.B<bool>(i, j); });
                states->AddCustomElement(XName::bitKlavierTagNames.TranspOffsetsStates, "b", [](int i, bool j){ return XAttribute::bitKlavierAttributes.B<bool>(i, j); });
                states->AddCustomElement(XName::bitKlavierTagNames.TranspOffsetsStates_inc, "b", [](int i, bool j){ return XAttribute::bitKlavierAttributes.B<bool>(i, j); });
                AllDefault();
            };
            void AllDefault()
            {
                DefaultBeats();
                DefaultParamAttributes();
                DefaultADSRs();
            }
            void DefaultBeats()
            {
                beats->ClearChildAttributes();
                states->ClearChildAttributes();
                beats->get(XName::bitKlavierTagNames.BeatMultipliers)->NewPair(0, 1.0);
                beats->get(XName::bitKlavierTagNames.BeatMultipliers_inc)->NewPair(0, 0.0);
                states->get(XName::bitKlavierTagNames.BeatMultipliersStates)->NewPair(0, true);
                states->get(XName::bitKlavierTagNames.BeatMultipliersStates_inc)->NewPair(0, false);
                beats->get(XName::bitKlavierTagNames.LengthMultipliers)->NewPair(0, 1.0);
                beats->get(XName::bitKlavierTagNames.LengthMultipliers_inc)->NewPair(0, 0.0);
                states->get(XName::bitKlavierTagNames.LengthMultipliersStates)->NewPair(0, true);
                states->get(XName::bitKlavierTagNames.LengthMultipliersStates_inc)->NewPair(0, false);
                beats->get(XName::bitKlavierTagNames.AccentMultipliers)->NewPair(0, 1.0);
                beats->get(XName::bitKlavierTagNames.AccentMultipliers_inc)->NewPair(0, 0.0);
                states->get(XName::bitKlavierTagNames.AccentMultipliersStates)->NewPair(0, true);
                states->get(XName::bitKlavierTagNames.AccentMultipliersStates_inc)->NewPair(0, false);
                SetTranspositions(0.0);
                states->get(XName::bitKlavierTagNames.TranspOffsetsStates_inc)->NewPair(0, true);
            }
            void DefaultParamAttributes()
            {
                bool first = true;
                for (std::string opt : opts)
                {
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.Gain((first ? 1.0 : 0.0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.BlendronicGain((first ? 1.0 : 0.0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.NumBeats((first ? 20 : 0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.ClusterMin((first ? 2 : 0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.ClusterMax((first ? 12 : 0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.ClusterCap((first ? 8 : 0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.ClusterThresh((first ? 500.0 : 0.0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.BeatsToSkip(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.NumClusters((first ? 1 : 0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.HoldMin(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.HoldMax((first ? 12000 : 0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.VelocityMin(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.VelocityMax((first ? 127 : 0), opt));
                    if (opt == "_inc") continue;
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.Mode(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.TranspUsesTuning(false, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.OnOffMode(false, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.SynchronicUseGlobalSoundSet((first ? true : false), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.SynchronicSoundSet("", opt));
                    first = false;
                    if (opt == "") continue;
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.BeatMultipliers(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.BeatMultipliersStates(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.LengthMultipliers(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.LengthMultipliersStates(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.AccentMultipliers(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.AccentMultipliersStates(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.TranspOffsets(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.TranspOffsetsStates(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.ADSRs(0, opt));
                };
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.TargetTypeSynchronicAddNotes(false));
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.TargetTypeSynchronicBeatSync(false));
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.TargetTypeSynchronicClear(false));
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.TargetTypeSynchronicDeleteNewest(false));
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.TargetTypeSynchronicDeleteOldest(false));
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.TargetTypeSynchronicPatternSync(false));
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.TargetTypeSynchronicPausePlay(false));
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.TargetTypeSynchronicRotate(false));
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.MidiOutput(0));
            };
            void SetParamAttribute(XAttribute* xattr)
            {
                std::string key = xattr->getComparisonString();
                if ((*param_attrs)[key])
                {
                    param_attrs->UpdateCustomPair(xattr);
                    if (ds[key]) GetDirty(ds[key]);
                }
            }
            template <typename T>
            void SetParamAttribute(std::string key, T value)
            {
                if ((*param_attrs)[key])
                {
                    XAttribute* xattr = new XAttribute(key, to_string(value));
                    param_attrs->UpdateCustomPair(xattr);
                    if (ds[key]) GetDirty(ds[key]);
                }
            }
            void DefaultADSRs()
            {
                SetADSR(3.0, 3.0, 1.0, 30.0);
            };
            void AddTransposition(double transp)
            {
                int c = transp_offsets->size();
                transp_offsets->AddElement(c, "f", [](int i, double j){ return XAttribute::bitKlavierAttributes.F<double>(i, j); });
                (*transp_offsets)(c)->NewPair(0, transp);
                states->get(XName::bitKlavierTagNames.TranspOffsetsStates)->UpdatePair(c, true);
            };
            void AddTransposition(std::vector<double> transps)
            {
                int c = transp_offsets->size();
                transp_offsets->AddElement(c, "f", [](int i, double j){ return XAttribute::bitKlavierAttributes.F<double>(i, j); });
                for (int i = 0; i < transps.size(); i++)
                {
                    (*transp_offsets)(c)->NewPair(i, transps[i]);
                };
                states->get(XName::bitKlavierTagNames.TranspOffsetsStates)->UpdatePair(c, true);
            };
            template <typename... A>
            void SetTranspositions(A... n)
            {
                transp_offsets->Clear();
                ((AddTransposition(n)), ...);
            };
            template <typename... A>
            void AddTranspositions(A... n)
            {
                ((AddTransposition(n)), ...);
            };
            void AddBeatMultiplier(double beat)
            {
                XAttributeMap<double>* beatMultipliers = beats->get(XName::bitKlavierTagNames.BeatMultipliers);
                int c = beatMultipliers->size();
                beatMultipliers->UpdatePair(c, beat);
                states->get(XName::bitKlavierTagNames.BeatMultipliersStates)->UpdatePair(c, true);
            }
            template <typename... A>
            void SetBeatMultipliers(A... n)
            {
                beats->get(XName::bitKlavierTagNames.BeatMultipliers)->Clear();
                (AddBeatMultiplier(n), ...);
            }
            template <typename... A>
            void AddBeatMultipliers(A... n)
            {
                (AddBeatMultiplier(n), ...);
            }
            void AddLengthMultiplier(double length)
            {
                XAttributeMap<double>* lengthMultipliers = beats->get(XName::bitKlavierTagNames.LengthMultipliers);
                int c = lengthMultipliers->size();
                lengthMultipliers->UpdatePair(c, length);
                states->get(XName::bitKlavierTagNames.LengthMultipliersStates)->UpdatePair(c, true);
            }
            template <typename... A>
            void SetLengthMultipliers(A... n)
            {
                beats->get(XName::bitKlavierTagNames.LengthMultipliers)->Clear();
                (AddLengthMultiplier(n), ...);
            }
            template <typename... A>
            void AddLengthMultipliers(A... n)
            {
                (AddLengthMultiplier(n), ...);
            }
            void AddAccentMultiplier(double accent)
            {
                XAttributeMap<double>* accentMultipliers = beats->get(XName::bitKlavierTagNames.AccentMultipliers);
                int c = accentMultipliers->size();
                accentMultipliers->UpdatePair(c, accent);
                states->get(XName::bitKlavierTagNames.AccentMultipliersStates)->UpdatePair(c, true);
            }
            template <typename... A>
            void SetAccentMultipliers(A... n)
            {
                beats->get(XName::bitKlavierTagNames.AccentMultipliers)->Clear();
                (AddAccentMultiplier(n), ...);
            }
            template <typename... A>
            void AddAccentMultipliers(A... n)
            {
                (AddAccentMultiplier(n), ...);
            }
            void AddADSR(double a, double d, double s, double r)
            {
                a >= 0.0 || (a = 0.0);
                d >= 0.0 || (d = 0.0);
                (s <= 1.0 || (s = 1.0)) && (s >= 0.0 || (s = 0.0));
                r >= 0.0 || (r = 0.0);
                int c = ADSRs->size();
                ADSRs->AddElement(c, "f", [](int i, double j){ return XAttribute::bitKlavierAttributes.F<double>(i, j); });
                (*ADSRs)(c)->NewPair(0, a);
                (*ADSRs)(c)->NewPair(1, d);
                (*ADSRs)(c)->NewPair(2, s);
                (*ADSRs)(c)->NewPair(3, r);
                (*ADSRs)(c)->NewPair(4, 1.0);
            }
            void SetADSR(double a, double d, double s, double r)
            {
                ADSRs->Clear();
                AddADSR(a,d,s,r);
            }
            void AddRandomADSR(int df = 5, double a_exp_val = 2.0, double d_exp_val = 5.0, double s_exp_val = 0.7, double r_exp_val = 250.0, double s_var = 0.1)
            {
                std::chi_squared_distribution<double> chi(df);
                std::normal_distribution<double> norm(s_exp_val, s_var);
                auto re_scale = [](double val) {return exp((log(1001) / 10)*val)-1.0; };
                double scaled = re_scale((double)df);
                double a = re_scale(chi(rng)) * (a_exp_val / scaled);
                double d = re_scale(chi(rng)) * (d_exp_val / scaled);
                double s = norm(rng);
                double r = re_scale(chi(rng)) * (r_exp_val / scaled);
                AddADSR(a, d, s, r);
            };
            void AddRandomTranpositionsGauss(int n = 10, int max_cluster = 1, double exp_int = 0, double var_int = 7, char slope = 'e', bool integer = false)
            {
                std::normal_distribution<double> norm(exp_int, var_int);
                std::uniform_int_distribution<int> clu(1, max_cluster);
                auto round = [integer](double val) { return integer ? std::round(val) : val; };
                auto e_slope = [var_int](double val)
                {
                    if (val >= 0) return pow((var_int + 1.0), (val / var_int)) - 1.0;
                    else return -(pow((var_int + 1.0), (-val / var_int)) - 1.0);
                };
                auto l_slope = [var_int](double val)
                {
                    if (val >= 0) return var_int * (log(val + 1.0) / log(var_int + 1.0));
                    else return -(var_int * (log(-val + 1.0) / log(var_int + 1.0)));
                };
                for (int i = 0; i < n; i++)
                {
                    std::vector<double> vals(clu(rng));
                    for (int j = 0; j < vals.size(); j++)
                    {
                        double val = slope == 'e' ? e_slope(norm(rng)) : slope == 'l' ? l_slope(norm(rng)) : norm(rng);
                        vals[j] = round(val);
                    }
                    AddTransposition(vals);
                }
            }
            void RandomTranpositionsGauss(int n = 10, int max_cluster = 1, double exp_int = 0, double var_int = 7, char slope = 'e', bool integer = false)
            {
                transp_offsets->Clear();
                AddRandomTranpositionsGauss(n, max_cluster, exp_int, var_int, slope, integer);
            }
            void AddRandomTranpositionsChiSquared(int n = 10, int max_cluster = 1, bool above = true, int df = 5, double exp_int = 7, double max_int = 12, char slope = 'e', bool integer = false)
            {
                std::chi_squared_distribution<double> chi(df);
                auto e_slope = [max_int](double val) { return pow((max_int + 1.0), (val / max_int)) - 1.0; };
                auto l_slope = [max_int](double val) { return max_int * (log(val + 1.0) / log(max_int + 1.0)); };
                double scaled = slope == 'e' ? exp_int / e_slope((double)df) : slope == 'l' ? exp_int / l_slope((double)df) : exp_int / df;
                int sig = above ? 1 : -1;
                std::uniform_int_distribution<int> clu(1, max_cluster);
                auto round = [integer](double val) { return integer ? std::round(val) : val; };
                for (int i = 0; i < n; i++)
                {
                    std::vector<double> vals(clu(rng));
                    for (int j = 0; j < vals.size(); j++)
                    {
                        double val = slope == 'e' ? e_slope(chi(rng)) : slope == 'l' ? l_slope(chi(rng)) : chi(rng);
                        val *= scaled*sig;
                        vals[j] = round(val);
                    }
                    AddTransposition(vals);
                }
            }
            void RandomTranpositionsChiSquared(int n = 10, int max_cluster = 1, bool above = true, int df = 5, double exp_int = 7, double max_int = 12, char slope = 'e', bool integer = false)
            {
                transp_offsets->Clear();
                AddRandomTranpositionsChiSquared(n, max_cluster, above, df, exp_int, max_int, slope, integer);
            }
            void AddRandomBeatsGauss(int n = 10, double exp_int = 1, double var_int = 1, char slope = 'e', bool integer = false)
            {
                std::normal_distribution<double> norm(exp_int, var_int);
                auto round = [integer](double val) { return integer ? std::round(val) : val; };
                auto e_slope = [var_int](double val)
                {
                    if (val >= 0) return pow((var_int + 1.0), (val / var_int)) - 1.0;
                    else return -(pow((var_int + 1.0), (-val / var_int)) - 1.0);
                };
                auto l_slope = [var_int](double val)
                {
                    if (val >= 0) return var_int * (log(val + 1.0) / log(var_int + 1.0));
                    else return -(var_int * (log(-val + 1.0) / log(var_int + 1.0)));
                };
                for (int i = 0; i < n; i++)
                {
                    double val = slope == 'e' ? e_slope(norm(rng)) : slope == 'l' ? l_slope(norm(rng)) : norm(rng);
                    AddBeatMultiplier(round(val));
                }
            }
            void RandomBeatsGauss(int n = 10, double exp_int = 1, double var_int = 1, char slope = 'e', bool integer = false)
            {
                beats->get(XName::bitKlavierTagNames.BeatMultipliers)->Clear();
                AddRandomBeatsGauss(n, exp_int, var_int, slope, integer);
            }
            void AddRandomBeatsChiSquared(int n = 10, bool above = true, int df = 5, double exp_int = 1, double max_int = 12, char slope = 'e', bool integer = false)
            {
                std::chi_squared_distribution<double> chi(df);
                auto e_slope = [max_int](double val) { return pow((max_int + 1.0), (val / max_int)) - 1.0; };
                auto l_slope = [max_int](double val) { return max_int * (log(val + 1.0) / log(max_int + 1.0)); };
                double scaled = slope == 'e' ? exp_int / e_slope((double)df) : slope == 'l' ? exp_int / l_slope((double)df) : exp_int / df;
                int sig = above ? 1 : -1;
                auto round = [integer](double val) { return integer ? std::round(val) : val; };
                for (int i = 0; i < n; i++)
                {
                    double val = slope == 'e' ? e_slope(chi(rng)) : slope == 'l' ? l_slope(chi(rng)) : chi(rng);
                    val *= scaled*sig;
                    AddBeatMultiplier(round(val));
                }
            }
            void RandomBeatsChiSquared(int n = 10, bool above = true, int df = 5, double exp_int = 1, double max_int = 12, char slope = 'e', bool integer = false)
            {
                beats->get(XName::bitKlavierTagNames.BeatMultipliers)->Clear();
                AddRandomBeatsChiSquared(n, above, df, exp_int, max_int, slope, integer);
            }
            void AddRandomLengthsGauss(int n = 10, double exp_int = 1, double var_int = 1, char slope = 'e', bool integer = false)
            {
                std::normal_distribution<double> norm(exp_int, var_int);
                auto round = [integer](double val) { return integer ? std::round(val) : val; };
                auto e_slope = [var_int](double val)
                {
                    if (val >= 0) return pow((var_int + 1.0), (val / var_int)) - 1.0;
                    else return -(pow((var_int + 1.0), (-val / var_int)) - 1.0);
                };
                auto l_slope = [var_int](double val)
                {
                    if (val >= 0) return var_int * (log(val + 1.0) / log(var_int + 1.0));
                    else return -(var_int * (log(-val + 1.0) / log(var_int + 1.0)));
                };
                for (int i = 0; i < n; i++)
                {
                    double val = slope == 'e' ? e_slope(norm(rng)) : slope == 'l' ? l_slope(norm(rng)) : norm(rng);
                    AddLengthMultiplier(round(val));
                }
            }
            void RandomLengthsGauss(int n = 10, double exp_int = 1, double var_int = 1, char slope = 'e', bool integer = false)
            {
                beats->get(XName::bitKlavierTagNames.LengthMultipliers)->Clear();
                AddRandomLengthsGauss(n, exp_int, var_int, slope, integer);
            }
            void AddRandomLengthsChiSquared(int n = 10, bool above = true, int df = 5, double exp_int = 1, double max_int = 12, char slope = 'e', bool integer = false)
            {
                std::chi_squared_distribution<double> chi(df);
                auto e_slope = [max_int](double val) { return pow((max_int + 1.0), (val / max_int)) - 1.0; };
                auto l_slope = [max_int](double val) { return max_int * (log(val + 1.0) / log(max_int + 1.0)); };
                double scaled = slope == 'e' ? exp_int / e_slope((double)df) : slope == 'l' ? exp_int / l_slope((double)df) : exp_int / df;
                int sig = above ? 1 : -1;
                auto round = [integer](double val) { return integer ? std::round(val) : val; };
                for (int i = 0; i < n; i++)
                {
                    double val = slope == 'e' ? e_slope(chi(rng)) : slope == 'l' ? l_slope(chi(rng)) : chi(rng);
                    val *= scaled*sig;
                    AddLengthMultiplier(round(val));
                }
            }
            void RandomLengthsChiSquared(int n = 10, bool above = true, int df = 5, double exp_int = 1, double max_int = 12, char slope = 'e', bool integer = false)
            {
                beats->get(XName::bitKlavierTagNames.LengthMultipliers)->Clear();
                AddRandomLengthsChiSquared(n, above, df, exp_int, max_int, slope, integer);
            }
            void AddRandomAccentsGauss(int n = 10, double exp_int = 1, double var_int = 1, char slope = 'e', bool integer = false)
            {
                std::normal_distribution<double> norm(exp_int, var_int);
                auto round = [integer](double val) { return integer ? std::round(val) : val; };
                auto e_slope = [var_int](double val)
                {
                    if (val >= 0) return pow((var_int + 1.0), (val / var_int)) - 1.0;
                    else return -(pow((var_int + 1.0), (-val / var_int)) - 1.0);
                };
                auto l_slope = [var_int](double val)
                {
                    if (val >= 0) return var_int * (log(val + 1.0) / log(var_int + 1.0));
                    else return -(var_int * (log(-val + 1.0) / log(var_int + 1.0)));
                };
                for (int i = 0; i < n; i++)
                {
                    double val = slope == 'e' ? e_slope(norm(rng)) : slope == 'l' ? l_slope(norm(rng)) : norm(rng);
                    AddAccentMultiplier(round(val));
                }
            }
            void RandomAccentsGauss(int n = 10, double exp_int = 1, double var_int = 1, char slope = 'e', bool integer = false)
            {
                beats->get(XName::bitKlavierTagNames.AccentMultipliers)->Clear();
                AddRandomAccentsGauss(n, exp_int, var_int, slope, integer);
            }
            void AddRandomAccentsChiSquared(int n = 10, bool above = true, int df = 5, double exp_int = 1, double max_int = 12, char slope = 'e', bool integer = false)
            {
                std::chi_squared_distribution<double> chi(df);
                auto e_slope = [max_int](double val) { return pow((max_int + 1.0), (val / max_int)) - 1.0; };
                auto l_slope = [max_int](double val) { return max_int * (log(val + 1.0) / log(max_int + 1.0)); };
                double scaled = slope == 'e' ? exp_int / e_slope((double)df) : slope == 'l' ? exp_int / l_slope((double)df) : exp_int / df;
                int sig = above ? 1 : -1;
                auto round = [integer](double val) { return integer ? std::round(val) : val; };
                for (int i = 0; i < n; i++)
                {
                    double val = slope == 'e' ? e_slope(chi(rng)) : slope == 'l' ? l_slope(chi(rng)) : chi(rng);
                    val *= scaled*sig;
                    AddAccentMultiplier(round(val));
                }
            }
            void RandomAccentsChiSquared(int n = 10, bool above = true, int df = 5, double exp_int = 1, double max_int = 12, char slope = 'e', bool integer = false)
            {
                beats->get(XName::bitKlavierTagNames.AccentMultipliers)->Clear();
                AddRandomAccentsChiSquared(n, above, df, exp_int, max_int, slope, integer);
            }
            void NumPulses(int n, int skip, std::string opt = "")
            {
                if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.NumBeats(n, opt));
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.BeatsToSkip(skip, opt));
            }
            void NumLayers(int n, std::string opt = "")
            {
                if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.NumClusters(n, opt));
            }
            void Cluster(int min, int max, int cap, double thresh, std::string opt = "")
            {
                if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.ClusterMin(min, opt));
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.ClusterMax(max, opt));
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.ClusterCap(cap, opt));
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.ClusterThresh(thresh, opt));
            }
            void Velocity(int min, int max, std::string opt = "")
            {
                if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.VelocityMin(min, opt));
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.VelocityMax(max, opt));
            }
            void Hold(int min, int max, std::string opt = "")
            {
                if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.HoldMin(min, opt));
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.HoldMax(max, opt));
            }
            void Modes(bool key_on, int pulse_triggered, std::string opt = "")
            {
                if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.OnOffMode(!key_on, opt));
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.Mode(pulse_triggered, opt));
            }
            void RandomSynchronic(int complexity)
            {
                double val = complexity / max_complexity;
                int n_of_notes = floor(val * 30) + 2;
                bool integer = complexity < max_complexity/2;
                int clusters = floor(val*8)+1;
                std::uniform_real_distribution<double> v(1.0, val*3.0 + 1.0);
                std::uniform_int_distribution<int> u(1, n_of_notes);
                RandomAccentsGauss(u(rng), 1.0, v(rng), 'e', integer);
                RandomBeatsGauss(u(rng), 1.0, v(rng), 'e', integer);
                RandomLengthsGauss(u(rng), 1.0, v(rng), 'e', integer);
                RandomTranpositionsGauss(u(rng), clusters, 1.0, v(rng), 'e', integer);
                int adsrs = u(rng);
                ADSRs->Clear();
                for (int i = 1; i <= adsrs; ++i)
                {
                    AddRandomADSR(i, 2.0, 5.0, 0.7, 250.0, v(rng)/10.0);
                }
                NumPulses(floor(n_of_notes*pow(v(rng), 2)), floor(u(rng)));
                NumLayers(clusters);
                Cluster(1, 60, 12, 100.0);
            }
            void Save(std::string file_name = "XSynchronic.xml")
            {
                std::string extra = moded ? "Mod/" : "/";
                file_name = "/Applications/bitKlavier/preparations/Synchronic" + extra + file_name;
                XDocument xdoc(this);
                xdoc.Save(file_name);
            };
    };

    class XNostalgic : public XPreparation
    {
        protected:    
            XAttributeMap<double>* transposition;
            XAttributeMap<double>* transposition_inc;
            XAttributeMap<double>* reverseADSR;
            XAttributeMap<double>* undertowADSR;
            XAttributeMap<Params>* param_attrs;
            std::map<std::string, int> ds = {
                {"?", 0},
                {"waveDistance", 1},
                {"undertow", 2},
                {"transposition", 3},
                {"gain", 4},
                {"blendronicGain", 5},
                {"lengthMultiplier", 6},
                {"beatsToSkip", 7},
                {"mode", 8},
                {"??", 9},
                {"???", 10},
                {"reverseADSR", 11},
                {"undertowADSR", 12},
                {"holdMin", 13},
                {"holdMax", 14},
                {"clusterMin", 15},
                {"clusterThresh", 16},
                {"keyOnReset", 17},
                {"velocityMin", 18},
                {"velocityMax", 19},
                {"transpUsesTuning", 20},
                {"nostalgicUseGlobalSoundSet", 21},
                {"nostalgicSoundSet", 22}
            };
        public:
            XNostalgic(XAttribute* id, XAttribute* name) : XPreparation(id, name, XName::bitKlavierTagNames.Nostalgic, 2, 23, 8)
            {
                XElement* params = new XElement(XName::bitKlavierTagNames.Params, 0);
                appendChild(params);
                XElement* transp = new XElement(XName::bitKlavierTagNames.Transposition, 0);
                XElement* transp_inc = new XElement(XName::bitKlavierTagNames.Transposition_inc, 0);
                XElement* r_adsr = new XElement(XName::bitKlavierTagNames.ReverseADSR, 0);
                XElement* u_adsr = new XElement(XName::bitKlavierTagNames.UndertowADSR, 0);
                params->appendChild(transp);
                params->appendChild(transp_inc);
                params->appendChild(r_adsr);
                params->appendChild(u_adsr);
                transposition = new XAttributeMap<double>(transp, "f", [](int i, double j) { return XAttribute::bitKlavierAttributes.F<double>(i, j); });
                transposition_inc = new XAttributeMap<double>(transp_inc, "f", [](int i, double j) { return XAttribute::bitKlavierAttributes.F<double>(i, j); });
                reverseADSR = new XAttributeMap<double>(r_adsr, "f", [](int i, double j, std::string o) { return XAttribute::bitKlavierAttributes.ADSR.F<double, std::string>(i, j, o); });
                undertowADSR = new XAttributeMap<double>(u_adsr, "f", [](int i, double j, std::string o) { return XAttribute::bitKlavierAttributes.ADSR.F<double, std::string>(i, j, o); });
                param_attrs = new XAttributeMap<Params>(params);
                AllDefault();
            };
            void AllDefault()
            {
                DefaultParamAttributes();
                DefaultReverseADSR();
                DefaultUndertowADSR();
                DefaultTranspositions();
            };
            void DefaultParamAttributes()
            {
                bool first = true;
                for (std::string opt : opts)
                {
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.NostalgicParams.Gain((first ? 1.0 : 0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.NostalgicParams.BlendronicGain((first ? 1.0 : 0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.NostalgicParams.WaveDistance(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.NostalgicParams.Undertow(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.NostalgicParams.LengthMultiplier((first ? 1.0 : 0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.NostalgicParams.BeatsToSkip(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.NostalgicParams.HoldMin((first ? 200.0 : 0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.NostalgicParams.HoldMax((first ? 12000.0 : 0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.NostalgicParams.ClusterMin((first ? 1 : 0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.NostalgicParams.ClusterThresh((first ? 150 : 0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.NostalgicParams.VelocityMin(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.NostalgicParams.VelocityMax((first ? 127 : 0), opt));
                    if (opt == "_inc") continue;
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.NostalgicParams.TranspUsesTuning(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.NostalgicParams.Mode(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.NostalgicParams.KeyOnReset(first, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.NostalgicParams.TargetTypeNostalgicClearAll(false, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.NostalgicParams.NostalgicUseGlobalSoundSet(first, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.NostalgicParams.NostalgicSoundSet((first ? "" : "0"), opt));
                    first = false;
                    if (opt == "") continue;
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.NostalgicParams.Transposition(0, opt));
                };
            };
            void SetParamAttribute(XAttribute* xattr)
            {
                std::string key = xattr->getComparisonString();
                if ((*param_attrs)[key])
                {
                    param_attrs->UpdateCustomPair(xattr);
                    if (ds[key]) GetDirty(ds[key]);
                }
            }
            template <typename T>
            void SetParamAttribute(std::string key, T value)
            {
                if ((*param_attrs)[key])
                {
                    XAttribute* xattr = new XAttribute(key, to_string(value));
                    param_attrs->UpdateCustomPair(xattr);
                    if (ds[key]) GetDirty(ds[key]);
                }
            }
            void DefaultReverseADSR()
            {
                bool first = true;
                for (std::string opt : opts)
                {
                    reverseADSR->UpdatePair(0, (first ? 2.0 : 0.0), opt);
                    reverseADSR->UpdatePair(1, (first ? 5.0 : 0.0), opt);
                    reverseADSR->UpdatePair(2, (first ? 0.9 : 0.0), opt);
                    reverseADSR->UpdatePair(3, (first ? 250.0 : 0.0), opt);
                    first = false;
                };
            };
            void DefaultUndertowADSR()
            {
                bool first = true;
                for (std::string opt : opts)
                {
                    undertowADSR->UpdatePair(0, (first ? 2.0 : 0.0), opt);
                    undertowADSR->UpdatePair(1, (first ? 5.0 : 0.0), opt);
                    undertowADSR->UpdatePair(2, (first ? 0.9 : 0.0), opt);
                    undertowADSR->UpdatePair(3, (first ? 250.0 : 0.0), opt);
                    first = false;
                };
            };
            void SetReverseAttack(double a, std::string opt = "")
            {
                a >= 0.0 || (a = 0.0);
                if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
                reverseADSR->UpdatePair(0, a, opt);
            };
            void SetUndertowAttack(double a, std::string opt = "")
            {
                a >= 0.0 || (a = 0.0);
                if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
                undertowADSR->UpdatePair(0, a, opt);
            };
            void SetReverseDecay(double d, std::string opt = "")
            {
                d >= 0.0 || (d = 0.0);
                if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
                reverseADSR->UpdatePair(1, d, opt);
            };
            void SetUndertowDecay(double d, std::string opt = "")
            {
                d >= 0.0 || (d = 0.0);
                if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
                undertowADSR->UpdatePair(1, d, opt);
            };
            void SetReverseSustain(double s, std::string opt = "")
            {
                (s <= 1.0 || (s = 1.0)) && (s >= 0.0 || (s = 0.0));
                if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
                reverseADSR->UpdatePair(2, s, opt);
            };
            void SetUndertowSustain(double s, std::string opt = "")
            {
                (s <= 1.0 || (s = 1.0)) && (s >= 0.0 || (s = 0.0));
                if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
                undertowADSR->UpdatePair(2, s, opt);
            };
            void SetReverseRelease(double r, std::string opt = "")
            {
                r >= 0.0 || (r = 0.0);
                if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
                reverseADSR->UpdatePair(3, r, opt);
            };
            void SetUndertowRelease(double r, std::string opt = "")
            {
                r >= 0.0 || (r = 0.0);
                if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
                undertowADSR->UpdatePair(3, r, opt);
            };
            void SetReverseADSR(double a, double d, double s, double r, std::string opt = "")
            {
                SetReverseAttack(a, opt);
                SetReverseDecay(d, opt);
                SetReverseSustain(s, opt);
                SetReverseRelease(r, opt);
            };
            void SetUndertowADSR(double a, double d, double s, double r, std::string opt = "")
            {
                SetUndertowAttack(a, opt);
                SetUndertowDecay(d, opt);
                SetUndertowSustain(s, opt);
                SetUndertowRelease(r, opt);
            };
            void RandomReverseADSR(int df = 5, double a_exp_val = 2.0, double d_exp_val = 5.0, double s_exp_val = 0.7, double r_exp_val = 250.0, double s_var = 0.1, std::string opt = "")
            {
                std::chi_squared_distribution<double> chi(df);
                std::normal_distribution<double> norm(s_exp_val, s_var);
                auto re_scale = [](double val) {return exp((log(1001) / 10)*val)-1.0; };
                double scaled = re_scale((double)df);
                double a = re_scale(chi(rng)) * (a_exp_val / scaled);
                double d = re_scale(chi(rng)) * (d_exp_val / scaled);
                double s = norm(rng);
                double r = re_scale(chi(rng)) * (r_exp_val / scaled);
                SetReverseADSR(a, d, s, r, opt);
            };
            void RandomUndertowADSR(int df = 5, double a_exp_val = 2.0, double d_exp_val = 5.0, double s_exp_val = 0.7, double r_exp_val = 250.0, double s_var = 0.1, std::string opt = "")
            {
                std::chi_squared_distribution<double> chi(df);
                std::normal_distribution<double> norm(s_exp_val, s_var);
                auto re_scale = [](double val) {return exp((log(1001) / 10)*val)-1.0; };
                double scaled = re_scale((double)df);
                double a = re_scale(chi(rng)) * (a_exp_val / scaled);
                double d = re_scale(chi(rng)) * (d_exp_val / scaled);
                double s = norm(rng);
                double r = re_scale(chi(rng)) * (r_exp_val / scaled);
                SetUndertowADSR(a, d, s, r, opt);
            };
            void DefaultTranspositions()
            {
                transposition->Clear();
                transposition_inc->Clear();
                transposition->NewPair(0, 0.0);
                transposition_inc->NewPair(0, 0.0);
            };
            void AddTransposition(double n)
            {
                int i = transposition->size();
                transposition->NewPair(i, n);
            };
            template <typename... A>
            void SetTranspositions(A... n)
            {
                transposition->Clear();
                ((AddTransposition(n)), ...);
            };
            template <typename... A>
            void AddTranspositions(A... n)
            {
                ((AddTransposition(n)), ...);
            };
            void RandomTranspositionsGauss(int n = 3, double exp_int = 0, double var_int = 7, char slope = 'e', bool root = true, bool integer = false)
            {
                transposition->Clear();
                std::normal_distribution<double> norm(exp_int, var_int);
                auto e_slope = [var_int](double val)
                {
                    if (val >= 0) return pow((var_int + 1.0), (val / var_int)) - 1.0;
                    else return -(pow((var_int + 1.0), (-val / var_int)) - 1.0);
                };
                auto l_slope = [var_int](double val)
                {
                    if (val >= 0) return var_int * (log(val + 1.0) / log(var_int + 1.0));
                    else return -(var_int * (log(-val + 1.0) / log(var_int + 1.0)));
                };
                auto round = [integer](double val) { return integer ? std::round(val) : val; };
                std::vector<double> vals;
                if (root) vals.push_back(0.0);
                while (vals.size() != n + root)
                {
                    double val = slope == 'e' ? e_slope(norm(rng)) : slope == 'l' ? l_slope(norm(rng)) : norm(rng);
                    if (std::find(vals.begin(), vals.end(), round(val)) != vals.end()) continue;
                    vals.push_back(round(val));
                };
                std::sort(vals.begin(), vals.end());
                for (int i = 0; i < vals.size(); ++i)
                {
                    transposition->NewPair(i, vals[i]);
                }
            };
            void RandomTranspositionsChiSquared(int n = 3, bool above = true, int df = 5, double exp_int = 7, double max_int = 12, char slope = 'e', bool root = true, bool integer = false)
            {
                transposition->Clear();
                std::chi_squared_distribution<double> chi(df);
                auto e_slope = [max_int](double val) { return pow((max_int + 1.0), (val / max_int)) - 1.0; };
                auto l_slope = [max_int](double val) { return max_int * (log(val + 1.0) / log(max_int + 1.0)); };
                double scaled = slope == 'e' ? exp_int / e_slope((double)df) : slope == 'l' ? exp_int / l_slope((double)df) : exp_int / df;
                auto round = [integer](double val) { return integer ? std::round(val) : val; };
                std::vector<double> vals;
                if (root) vals.push_back(0.0);
                int sig = above ? 1 : -1;
                while (vals.size() != n + root)
                {
                    double val = slope == 'e' ? e_slope(chi(rng)) : slope == 'l' ? l_slope(chi(rng)) : chi(rng);
                    val *= scaled*sig;
                    if (std::find(vals.begin(), vals.end(), round(val)) != vals.end()) continue;
                    vals.push_back(round(val));
                };
                std::sort(vals.begin(), vals.end());
                for (int i = 0; i < vals.size(); ++i)
                {
                    transposition->NewPair(i, vals[i]);
                }
            };
            void AddRandomTranspositionsGauss(int n = 3, double exp_int = 0, double var_int = 7, char slope = 'e', bool integer = false)
            {
                std::normal_distribution<double> norm(exp_int, var_int);
                auto e_slope = [var_int](double val)
                {
                    if (val >= 0) return pow((var_int + 1.0), (val / var_int)) - 1.0;
                    else return -(pow((var_int + 1.0), (-val / var_int)) - 1.0);
                };
                auto l_slope = [var_int](double val)
                {
                    if (val >= 0) return var_int * (log(val + 1.0) / log(var_int + 1.0));
                    else return -(var_int * (log(-val + 1.0) / log(var_int + 1.0)));
                };
                int size = transposition->size();
                auto round = [integer](double val) { return integer ? std::round(val) : val; };
                std::vector<double> vals;
                for (auto it = transposition->FirstAttribute(); it != transposition->LastAttribute(); ++it)
                {
                    vals.push_back(std::stod((*it)->getValue()->getComparisonString()));
                }
                while (vals.size() != n + size)
                {
                    double val = slope == 'e' ? e_slope(norm(rng)) : slope == 'l' ? l_slope(norm(rng)) : norm(rng);
                    if (std::find(vals.begin(), vals.end(), round(val)) != vals.end()) continue;
                    vals.push_back(round(val));
                };
                std::sort(vals.begin(), vals.end());
                for (int i = 0; i < vals.size(); ++i)
                {
                    transposition->UpdatePair(i, vals[i]);
                }
            };
            void AddRandomTranspositionsChiSquared(int n = 3, bool above = true, int df = 5, double exp_int = 7, double max_int = 12, char slope = 'e', bool integer = false)
            {
                std::chi_squared_distribution<double> chi(df);
                auto e_slope = [max_int](double val) { return pow((max_int + 1.0), (val / max_int)) - 1.0; };
                auto l_slope = [max_int](double val) { return max_int * (log(val + 1.0) / log(max_int + 1.0)); };
                double scaled = slope == 'e' ? exp_int / e_slope((double)df) : slope == 'l' ? exp_int / l_slope((double)df) : exp_int / df;
                int size = transposition->size();
                auto round = [integer](double val) { return integer ? std::round(val) : std::round(val * 1000) / 100; };
                std::vector<double> vals;
                int sig = above ? 1 : -1;
                for (auto it = transposition->FirstAttribute(); it != transposition->LastAttribute(); ++it)
                {
                    vals.push_back(std::stod((*it)->getValue()->getComparisonString()));
                }
                while (vals.size() != n + size)
                {
                    double val = slope == 'e' ? e_slope(chi(rng)) : slope == 'l' ? l_slope(chi(rng)) : chi(rng);
                    val *= scaled*sig;
                    if (std::find(vals.begin(), vals.end(), round(val)) != vals.end()) continue;
                    vals.push_back(round(val));
                };
                std::sort(vals.begin(), vals.end());
                for (int i = 0; i < vals.size(); ++i)
                {
                    transposition->UpdatePair(i, vals[i]);
                }
            };
            void NoteLengthMultiplier(double val, std::string opt = "")
            {
                if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.NostalgicParams.LengthMultiplier(val, opt));
            };
            void WaveDistance(double val, std::string opt = "")
            {
                if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.NostalgicParams.WaveDistance(val, opt));
            }
            void RandomWaveDistance(double lambda = 0.01)
            {
                std::exponential_distribution<double> e(lambda);
                WaveDistance(e(rng));
            }
            void Undertow(double val, std::string opt = "")
            {
                if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.NostalgicParams.Undertow(val, opt));
            }
            void RandomUndertow(double lambda = 0.002)
            {
                std::exponential_distribution<double> e(lambda);
                Undertow(e(rng));
            }
            void RandomNostalgic(int complexity)
            {
                double val = complexity / max_complexity;
                int n_of_notes = floor(val * 13);
                RandomTranspositionsGauss(n_of_notes, 0.0, val*7.0, 'e', true, complexity < max_complexity/2);
                RandomReverseADSR(n_of_notes+1, 2.0, 5.0, 0.7, 250.0, val*5.0);
                RandomUndertowADSR(n_of_notes+1, 2.0, 5.0, 0.7, 250.0, val*5.0);
                RandomWaveDistance();
                RandomUndertow();
                NoteLengthMultiplier(1.0+val*5.0);
            };
            void Save(std::string file_name = "XNostalgic.xml")
            {
                std::string extra = moded ? "Mod/" : "/";
                file_name = "/Applications/bitKlavier/preparations/Nostalgic" + extra + file_name;
                XDocument xdoc(this);
                xdoc.Save(file_name);
            };
    };

    class XTempo : public XPreparation
    {
        protected:
            XAttributeMap<Params>* param_attrs;
            std::map<std::string, int> ds = {
                {"?", 0},
                {"tempo", 1},
                {"system", 2},
                {"at1History", 3},
                {"at1Subdivisions", 4},
                {"at1Min", 5},
                {"at1Max", 6},
                {"at1Mode", 7},
                {"subdivisions", 8}
            };
        public:
            XTempo(XAttribute* id, XAttribute* name) : XPreparation(id, name, XName::bitKlavierTagNames.Tempo, 4, 9, 10)
            {
                XElement* params = new XElement(XName::bitKlavierTagNames.Params, 0);
                appendChild(params);
                param_attrs = new XAttributeMap<Params>(params);
                DefaultParamAttributes();
            }
            void DefaultParamAttributes()
            {
                bool first = true;
                for (std::string opt : opts)
                {
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TempoParams.Tempo((first ? 120.0 : 0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TempoParams.At1History((first ? 4 : 0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TempoParams.At1Subdivisions((first ? 1.0 : 0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TempoParams.At1Min((first ? 100.0 : 0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TempoParams.At1Max((first ? 2000.0 : 0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TempoParams.Subdivisions((first ? 1.0 : 0), opt));
                    if (opt == "_inc") continue;
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TempoParams.System(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TempoParams.At1Mode(0, opt));
                    first = false;
                }
            }
            void SetParamAttribute(XAttribute* xattr)
            {
                std::string key = xattr->getComparisonString();
                if ((*param_attrs)[key])
                {
                    param_attrs->UpdateCustomPair(xattr);
                    if (ds[key]) GetDirty(ds[key]);
                }
            }
            template <typename T>
            void SetParamAttribute(std::string key, T value)
            {
                if ((*param_attrs)[key])
                {
                    XAttribute* xattr = new XAttribute(key, to_string(value));
                    param_attrs->UpdateCustomPair(xattr);
                    if (ds[key]) GetDirty(ds[key]);
                }
            }
            void SetTempo(double val, std::string opt = "")
            {
                if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TempoParams.Tempo(val, opt));
            }
            void SetSubdivisions(double val, std::string opt = "")
            {
                if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TempoParams.Subdivisions(val, opt));
            }
            void SetConstantTempo(double tempo, double subdiv, std::string opt = "")
            {
                if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TempoParams.Tempo(tempo, opt));
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TempoParams.Subdivisions(subdiv, opt));
                if (opt == "_inc") return;
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TempoParams.System(0, opt));
            }
            void SetAdaptiveTempo(double min, double max, double subdiv, int history = 4, int mode = 0, std::string opt = "")
            {
                if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TempoParams.At1History(history, opt));
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TempoParams.At1Subdivisions(subdiv, opt));
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TempoParams.At1Min(min, opt));
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TempoParams.At1Max(max, opt));
                if (opt == "_inc") return;
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TempoParams.System(1, opt));
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TempoParams.At1Mode(mode, opt));
            }
            void RandomTempo(int complexity)
            {
                std::exponential_distribution<double> e1(3.0/complexity);
                std::exponential_distribution<double> e2(complexity/max_complexity);
                SetConstantTempo(e1(rng), e2(rng));
            }
            void Save(std::string file_name = "XTempo.xml")
            {
                std::string extra = moded ? "Mod/" : "/";
                file_name = "/Applications/bitKlavier/preparations/Tempo" + extra + file_name;
                XDocument xdoc(this);
                xdoc.Save(file_name);
            };
    };

    class XTuning : public XPreparation
    {
        protected:
            XAttributeMap<Params>* param_attrs;
            XAttributeMap<double>* custom_scale;
            XAttributeMap<double>* custom_scale_inc;
            XAttributeMap<double>* absolute_offsets;
            XAttributeMap<double>* absolute_offsets_inc;
            XAttributeMap<Params>* spring_param_attrs;
            XAttributeMap<double>* tethers;
            XAttributeMap<double>* springs;
            XAttributeMap<double>* interval_scale;
            XAttributeMap<bool>* spring_mode;
            std::map<std::string, int> ds = {
                {"?", 0},
                {"nToneSemitoneWidth", 13},
                
            };
        public:
            XTuning(XAttribute* id, XAttribute* name) : XPreparation(id, name, XName::bitKlavierTagNames.Tuning, 3, 30, 9)
            {
                XElement* params = new XElement(XName::bitKlavierTagNames.Params, 0);
                appendChild(params);
                XElement* cscale = new XElement(XName::bitKlavierTagNames.CustomScale, 0);
                XElement* cscale_inc = new XElement(XName::bitKlavierTagNames.CustomScale_inc, 0);
                XElement* aoffsets = new XElement(XName::bitKlavierTagNames.AbsoluteOffsets, 0);
                XElement* aoffsets_inc = new XElement(XName::bitKlavierTagNames.AbsoluteOffsets_inc, 0);
                XElement* stuning = new XElement(XName::bitKlavierTagNames.Springtuning, 0);
                XElement* tths = new XElement(XName::bitKlavierTagNames.Tethers, 0);
                XElement* sprgs = new XElement(XName::bitKlavierTagNames.Springs, 0);
                XElement* iscale = new XElement(XName::bitKlavierTagNames.IntervalScale, 0);
                XElement* smode = new XElement(XName::bitKlavierTagNames.SpringMode, 0);
                *stuning << tths << sprgs << iscale << smode;
                *params << cscale << cscale_inc << aoffsets << aoffsets_inc << stuning;
                param_attrs = new XAttributeMap<Params>(params);
                custom_scale = new XAttributeMap<double>(cscale, "f", [](int i, double j) { return XAttribute::bitKlavierAttributes.F<double>(i, j); });
                custom_scale_inc = new XAttributeMap<double>(cscale_inc, "f", [](int i, double j) { return XAttribute::bitKlavierAttributes.F<double>(i, j); });
                absolute_offsets = new XAttributeMap<double>(aoffsets, "f", [](int i, double j) { return XAttribute::bitKlavierAttributes.F<double>(i, j); });
                absolute_offsets_inc = new XAttributeMap<double>(aoffsets_inc, "f", [](int i, double j) { return XAttribute::bitKlavierAttributes.F<double>(i, j); });
                spring_param_attrs = new XAttributeMap<Params>(stuning);
                tethers = new XAttributeMap<double>(tths, "t", [](int i, double j) { return XAttribute::bitKlavierAttributes.T<double>(i, j); });
                springs = new XAttributeMap<double>(sprgs, "s", [](int i, double j) { return XAttribute::bitKlavierAttributes.S<double>(i, j); });
                interval_scale = new XAttributeMap<double>(iscale, "s", [](int i, double j) { return XAttribute::bitKlavierAttributes.S<double>(i, j); });
                spring_mode = new XAttributeMap<bool>(smode, "s", [](int i, bool j) { return XAttribute::bitKlavierAttributes.S<bool>(i, j); });
                AllDefault();
            }
            void AllDefault()
            {
                DefaultParamAttributes();
                DefaultSpringParams();
                DefaultOffsets();
                DefaultSpringTuning();
            }
            void DefaultParamAttributes()
            {
                bool first = true;
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TuningParams.ScaleName("XScale"));
                for (std::string opt : opts)
                {
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TuningParams.Offset(0.0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TuningParams.AdaptiveClusterThresh((first ? 100 : 0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TuningParams.AdaptiveHistory((first ? 4 : 0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TuningParams.NToneRoot((first ? 60 : 0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TuningParams.NToneSemitoneWidth((first ? 100.0 : 0.0), opt));
                    if (opt == "_inc") continue;
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TuningParams.Scale((first ? 3 : 0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TuningParams.Fundamental(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TuningParams.AdaptiveIntervalScale(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TuningParams.AdaptiveInversional(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TuningParams.AdaptiveAnchorScale(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TuningParams.AdaptiveAnchorFund(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TuningParams.AdaptiveSystem(0, opt));
                    first = false;
                    if (opt == "") continue;
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TuningParams.CustomScale(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TuningParams.AbsoluteOffsets(0, opt));
                };
            }
            void SetParamAttribute(XAttribute* xattr)
            {
                std::string key = xattr->getComparisonString();
                if ((*param_attrs)[key])
                {
                    param_attrs->UpdateCustomPair(xattr);
                }
            }
            template <typename T>
            void SetParamAttribute(std::string key, T value)
            {
                if ((*param_attrs)[key])
                {
                    XAttribute* xattr = new XAttribute(key, to_string(value));
                    param_attrs->UpdateCustomPair(xattr);
                }
            }
            void DefaultSpringParams()
            {
                bool first = true;
                for (std::string opt : opts)
                {
                    spring_param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SpringParams.Rate((first ? 100.0 : 0.0), opt));
                    spring_param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SpringParams.Drag((first ? 0.15 : 0.0), opt));
                    spring_param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SpringParams.TetherStiffness((first ? 0.5 : 0.0), opt));
                    spring_param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SpringParams.IntervalStiffness((first ? 0.5 : 0.0), opt));
                    spring_param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SpringParams.Stiffness((first ? 1.0 : 0.0), opt));
                    spring_param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SpringParams.TetherWeightGlobal((first ? 0.5 : 0.0), opt));
                    spring_param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SpringParams.TetherWeightSecondaryGlobal((first ? 0.1 : 0.0), opt));
                    if (opt == "_inc") continue;
                    spring_param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SpringParams.Active(0, opt));
                    spring_param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SpringParams.IntervalTuningId((first ? 1 : 0), opt));
                    spring_param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SpringParams.IntervalFundamental((first ? 16 : 0), opt));
                    spring_param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SpringParams.FundamentalSetsTether(first, opt));
                    first = false;
                };
            }
            void SetSpringParamAttribute(XAttribute* xattr)
            {
                std::string key = xattr->getComparisonString();
                if ((*spring_param_attrs)[key])
                {
                    spring_param_attrs->UpdateCustomPair(xattr);
                }
            }
            template <typename T>
            void SetSpringParamAttribute(std::string key, T value)
            {
                if ((*spring_param_attrs)[key])
                {
                    XAttribute* xattr = new XAttribute(key, to_string(value));
                    spring_param_attrs->UpdateCustomPair(xattr);
                }
            }
            void DefaultOffsets()
            {
                for (int i = 0; i < 12; ++i)
                {
                    custom_scale->UpdatePair(i, 0.0);
                }
                custom_scale_inc->Clear();
                for (int i = 0; i < 256; ++i)
                {
                    absolute_offsets->UpdatePair(i, 0.0);
                }
                absolute_offsets_inc->Clear();
            }
            void DefaultSpringTuning()
            {
                for (int i = 0; i < 128; ++i)
                {
                    tethers->UpdatePair(i, 0.5);
                    if (i < 12)
                    {
                        springs->UpdatePair(i, 0.5);
                        interval_scale->UpdatePair(i, 0.0);
                        spring_mode->UpdatePair(i, true);
                    }
                }
            }
            void SetCustomScale(std::vector<double> offs)
            {
                offs.resize(12);
                for (int i = 0; i < 12; ++i)
                {
                    custom_scale->UpdatePair(i, offs[i]);
                }
                SetParamAttribute(XAttribute::bitKlavierAttributes.TuningParams.Scale(8));
            }
            void RandomCustomScale(double mean = 0.0, double std_dev = 25.0)
            {
                std::normal_distribution<double> n(mean, std_dev);
                for (int i = 0; i < 12; ++i)
                {
                    custom_scale->UpdatePair(i, n(rng));
                }
                SetParamAttribute(XAttribute::bitKlavierAttributes.TuningParams.Scale(8));
            }
            void SetCustomSpringScale(std::vector<double> offs)
            {
                offs.resize(12);
                for (int i = 0; i < 12; ++i)
                {
                    interval_scale->UpdatePair(i, offs[i]);
                }
                SetSpringParamAttribute(XAttribute::bitKlavierAttributes.SpringParams.IntervalTuningId(8));
            }
            void RandomCustomSpringScale(double mean = 0.0, double std_dev = 25.0)
            {
                std::normal_distribution<double> n(mean, std_dev);
                for (int i = 0; i < 12; ++i)
                {
                    interval_scale->UpdatePair(i, n(rng));
                }
                SetSpringParamAttribute(XAttribute::bitKlavierAttributes.SpringParams.IntervalTuningId(8));
            }
            void AddAbsoluteOffset(int key, double off)
            {
                key = std::min(255, std::max(0, key));
                absolute_offsets->UpdatePair(key, off);
            }
            void AddAbsoluteOffsets(std::vector<std::tuple<int, double>> offs)
            {
                for (std::tuple<int, double> t : offs)
                {
                    AddAbsoluteOffset(std::get<0>(t), std::get<1>(t));
                }
            }
            void SetAbsoluteOffsets(std::vector<std::tuple<int, double>> offs)
            {
                for (int i = 0; i < 256; ++i)
                {
                    absolute_offsets->UpdatePair(i, 0.0);
                }
                for (std::tuple<int, double> t : offs)
                {
                    AddAbsoluteOffset(std::get<0>(t), std::get<1>(t));
                }
            }
            void RandomAbsoluteOffsets(int n = 10, double key_mean = 60, double key_stddev = 32, double off_mean = 0.0, double off_stddev = 25.0)
            {
                std::normal_distribution<double> norm(off_mean, off_stddev);
                std::vector<int> keys = getRandomKeys(n, 0, 256, key_mean, key_stddev);
                std::vector<std::tuple<int, double>> offs(n);
                for (int i = 0; i < n; ++i)
                {
                    std::tuple<int, double> t(keys[i], norm(rng));
                    offs[i] = t;
                }
                SetAbsoluteOffsets(offs);
            }
            void AddTether(int key, double val)
            {
                key = std::min(127, std::max(0, key));
                val = std::min(1.0, std::max(0.0, val));
                tethers->UpdatePair(key, val);
            }
            void AddTethers(std::vector<std::tuple<int, double>> tths)
            {
                for (std::tuple<int, double> t : tths)
                {
                    AddTether(std::get<0>(t), std::get<1>(t));
                }
            }
            void SetTethers(std::vector<std::tuple<int, double>> tths)
            {
                for (int i = 0; i < 128; ++i)
                {
                    tethers->UpdatePair(i, 0.5);
                }
                for (std::tuple<int, double> t : tths)
                {
                    AddTether(std::get<0>(t), std::get<1>(t));
                }
            }
            void RandomTethers(int n = 10, double key_mean = 60, double key_stddev = 32, double tth_mean = 0.5, double tth_stddev = 0.25)
            {
                std::normal_distribution<double> norm(tth_mean, tth_stddev);
                std::vector<int> keys = getRandomKeys(n, 0, 128, key_mean, key_stddev);
                std::vector<std::tuple<int, double>> tths(n);
                for (int i = 0; i < n; ++i)
                {
                    std::tuple<int, double> t(keys[i], norm(rng));
                    tths[i] = t;
                }
                SetTethers(tths);
            }
            void SetSprings(std::vector<double> sprgs, std::vector<bool> modes)
            {
                sprgs.resize(12);
                modes.resize(12);
                for (int i = 0; i < 12; ++i)
                {
                    double val = std::min(1.0, std::max(0.0, sprgs[i]));
                    springs->UpdatePair(i, val);
                    spring_mode->UpdatePair(i, modes[i]);
                }
            }
            void RandomSprings(double mean = 0.5, double std_dev = 0.25)
            {
                std::normal_distribution<double> n(mean, std_dev);
                std::bernoulli_distribution b(0.5);
                for (int i = 0; i < 12; ++i)
                {
                    double val = std::min(1.0, std::max(0.0, n(rng)));
                    springs->UpdatePair(i, val);
                    spring_mode->UpdatePair(i, b(rng));
                }
            }
            void RandomNormalTuning(int complexity)
            {
                SetParamAttribute(XAttribute::bitKlavierAttributes.TuningParams.AdaptiveSystem(0));
                SetSpringParamAttribute(XAttribute::bitKlavierAttributes.SpringParams.Active(false));
                double val = complexity / max_complexity;
                int n_of_notes = floor(val * 128);
                RandomCustomScale(0.0, 24.0*val+1.0);
                RandomAbsoluteOffsets(n_of_notes, 60, 32, 0.0, 24.0*val+1.0);
                std::normal_distribution<double> norm(100.0, 9.0*val + 1.0);
                std::normal_distribution<double> norm2(0.0, 1.0*val + 1.0);
                std::uniform_int_distribution<int> t(0, 127);
                std::uniform_int_distribution<int> f(0, 11);
                SetParamAttribute(XAttribute::bitKlavierAttributes.TuningParams.Fundamental(f(rng)));
                SetParamAttribute(XAttribute::bitKlavierAttributes.TuningParams.NToneSemitoneWidth(norm(rng)));
                SetParamAttribute(XAttribute::bitKlavierAttributes.TuningParams.NToneRoot(t(rng)));
                SetParamAttribute(XAttribute::bitKlavierAttributes.TuningParams.Offset(norm2(rng)));
            }
            void RandomAdaptiveTuning(int complexity)
            {
                SetParamAttribute(XAttribute::bitKlavierAttributes.TuningParams.AdaptiveSystem(1));
                SetSpringParamAttribute(XAttribute::bitKlavierAttributes.SpringParams.Active(false));
                double val = complexity / max_complexity;
                int n_of_notes = floor(val * 128);
                RandomCustomScale(0.0, 24.0*val+1.0);
                RandomAbsoluteOffsets(n_of_notes, 60, 32, 0.0, 24.0*val+1.0);
                std::normal_distribution<double> norm2(0.0, 1.0*val + 1.0);
                std::uniform_int_distribution<int> f(0, 11);
                SetParamAttribute(XAttribute::bitKlavierAttributes.TuningParams.Fundamental(f(rng)));
                SetParamAttribute(XAttribute::bitKlavierAttributes.TuningParams.Offset(norm2(rng)));
                SetParamAttribute(XAttribute::bitKlavierAttributes.TuningParams.AdaptiveIntervalScale(8));
            }
            void RandomAdaptiveAnchoredTuning(int complexity)
            {
                SetParamAttribute(XAttribute::bitKlavierAttributes.TuningParams.AdaptiveSystem(2));
                SetSpringParamAttribute(XAttribute::bitKlavierAttributes.SpringParams.Active(false));
                double val = complexity / max_complexity;
                int n_of_notes = floor(val * 128);
                RandomCustomScale(0.0, 24.0*val+1.0);
                RandomAbsoluteOffsets(n_of_notes, 60, 32, 0.0, 24.0*val+1.0);
                std::normal_distribution<double> norm2(0.0, 1.0*val + 1.0);
                std::uniform_int_distribution<int> f(0, 11);
                std::uniform_int_distribution<int> scale(0, 39);
                SetParamAttribute(XAttribute::bitKlavierAttributes.TuningParams.Fundamental(f(rng)));
                SetParamAttribute(XAttribute::bitKlavierAttributes.TuningParams.Offset(norm2(rng)));
                SetParamAttribute(XAttribute::bitKlavierAttributes.TuningParams.AdaptiveIntervalScale(8));
                SetParamAttribute(XAttribute::bitKlavierAttributes.TuningParams.AdaptiveAnchorScale(scale(rng)));
                SetParamAttribute(XAttribute::bitKlavierAttributes.TuningParams.AdaptiveAnchorFund(f(rng)));
            }
            void RandomSpringTuning(int complexity)
            {
                SetParamAttribute(XAttribute::bitKlavierAttributes.TuningParams.AdaptiveSystem(3));
                SetSpringParamAttribute(XAttribute::bitKlavierAttributes.SpringParams.Active(true));
                double val = complexity / max_complexity;
                int n_of_notes = floor(val * 128);
                RandomCustomScale(0.0, 24.0*val+1.0);
                RandomCustomSpringScale(0.0, 24.0*val+1.0);
                RandomAbsoluteOffsets(n_of_notes, 60, 32, 0.0, 24.0*val+1.0);
                RandomTethers(n_of_notes, 60, 32, 0.0, 0.24*val+0.01);
                RandomSprings(0.5, 0.24*val+0.01);
                std::normal_distribution<double> norm2(0.0, 1.0*val + 1.0);
                std::uniform_int_distribution<int> f(0, 11);
                std::chi_squared_distribution<double> chi(floor(val*6));
                std::normal_distribution<double> norm(0.5, 0.24*val+0.01);
                std::uniform_int_distribution<int> u(0, 16);
                SetParamAttribute(XAttribute::bitKlavierAttributes.TuningParams.Fundamental(f(rng)));
                SetParamAttribute(XAttribute::bitKlavierAttributes.TuningParams.Offset(norm2(rng)));
                SetSpringParamAttribute(XAttribute::bitKlavierAttributes.SpringParams.Rate(chi(rng)*100.0));
                SetSpringParamAttribute(XAttribute::bitKlavierAttributes.SpringParams.Drag(std::min(1.0, std::max(0.0, norm(rng)))));
                SetSpringParamAttribute(XAttribute::bitKlavierAttributes.SpringParams.IntervalStiffness(std::min(1.0, std::max(0.0, norm(rng)))));
                SetSpringParamAttribute(XAttribute::bitKlavierAttributes.SpringParams.TetherStiffness(std::min(1.0, std::max(0.0, norm(rng)))));
                SetSpringParamAttribute(XAttribute::bitKlavierAttributes.SpringParams.FundamentalSetsTether(false));
                SetSpringParamAttribute(XAttribute::bitKlavierAttributes.SpringParams.IntervalFundamental(u(rng)));
            }
            void Save(std::string file_name = "XTuning.xml")
            {
                std::string extra = moded ? "Mod/" : "/";
                file_name = "/Applications/bitKlavier/preparations/Tuning" + extra + file_name;
                XDocument xdoc(this);
                xdoc.Save(file_name);
            };
    };

    class XCompressor : public XElement
    {
        protected:
            XAttribute* name;
            XAttributeMap<Params>* attrs;
        public:
            XCompressor(XAttribute* c_name) : XElement(XName::bitKlavierTagNames.Equalizer, 0)
            {
                name = setAttribute(c_name);
                attrs = new XAttributeMap<Params>(this);
                DefaultParamAttributes();
            }
            void DefaultParamAttributes()
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
            void SetParamAttribute(XAttribute* xattr)
            {
                std::string key = xattr->getComparisonString();
                if ((*attrs)[key])
                {
                    attrs->UpdateCustomPair(xattr);
                }
            }
            template <typename T>
            void SetParamAttribute(std::string key, T value)
            {
                if ((*attrs)[key])
                {
                    XAttribute* xattr = new XAttribute(key, to_string(value));
                    attrs->UpdateCustomPair(xattr);
                }
            }
    };

    class XEqualizer : public XElement
    {
        protected:
            XAttributeMap<Params>* attrs;
        public:
            XEqualizer() : XElement(XName::bitKlavierTagNames.Equalizer, 0)
            {
                attrs = new XAttributeMap<Params>(this);
                DefaultParamAttributes();
            }
            void DefaultParamAttributes()
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
            void SetParamAttribute(XAttribute* xattr)
            {
                std::string key = xattr->getComparisonString();
                if ((*attrs)[key])
                {
                    attrs->UpdateCustomPair(xattr);
                }
            }
            template <typename T>
            void SetParamAttribute(std::string key, T value)
            {
                if ((*attrs)[key])
                {
                    XAttribute* xattr = new XAttribute(key, to_string(value));
                    attrs->UpdateCustomPair(xattr);
                }
            }
    };

    class XGeneral : public XElement
    {
        protected:
            XAttributeMap<Params>* attrs;
        public:
            XGeneral() : XElement(XName::bitKlavierTagNames.General, 0)
            {
                attrs = new XAttributeMap<Params>(this);
                DefaultParamAttributes();
            }
            void DefaultParamAttributes()
            {
                attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.GeneralParams.GlobalGain(1.0));
                attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.GeneralParams.TempoMultiplier(1.0));
                attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.GeneralParams.TuningFund(440.0));
                attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.GeneralParams.InvertSustain(false));
                attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.GeneralParams.NoteOnSetsNoteOffVelocity(false));
            }
            void SetParamAttribute(XAttribute* xattr)
            {
                std::string key = xattr->getComparisonString();
                if ((*attrs)[key])
                {
                    attrs->UpdateCustomPair(xattr);
                }
            }
            template <typename T>
            void SetParamAttribute(std::string key, T value)
            {
                if ((*attrs)[key])
                {
                    XAttribute* xattr = new XAttribute(key, to_string(value));
                    attrs->UpdateCustomPair(xattr);
                }
            }
    };

    class XBlendronic : public XPreparation
    {
        protected:
            XAttributeMap<Params>* param_attrs;
            XElementMap<double>* beats;
            XElementMap<bool>* states;
        public:
            enum Beats
            {
                BEATS,
                DELAYS,
                SMOOTHS,
                COEFFS
            };
            XBlendronic(XAttribute* id, XAttribute* name) : XPreparation(id, name, XName::bitKlavierTagNames.Blendronic, 16, 8, 17)
            {
                XElement* params = new XElement(XName::bitKlavierTagNames.Params, 0);
                appendChild(params);
                param_attrs = new XAttributeMap<Params>(params);
                beats = new XElementMap<double>(params);
                states = new XElementMap<bool>(params);
                beats->AddCustomElement(XName::bitKlavierTagNames.Beats, "f", [](int i, double j){ return XAttribute::bitKlavierAttributes.F<double>(i, j); });
                beats->AddCustomElement(XName::bitKlavierTagNames.Beats_inc, "f", [](int i, double j){ return XAttribute::bitKlavierAttributes.F<double>(i, j); });
                states->AddCustomElement(XName::bitKlavierTagNames.BeatsStates, "b", [](int i, bool j){ return XAttribute::bitKlavierAttributes.B<bool>(i, j); });
                states->AddCustomElement(XName::bitKlavierTagNames.BeatsStates_inc, "b", [](int i, bool j){ return XAttribute::bitKlavierAttributes.B<bool>(i, j); });
                beats->AddCustomElement(XName::bitKlavierTagNames.DelayLengths, "f", [](int i, double j){ return XAttribute::bitKlavierAttributes.F<double>(i, j); });
                beats->AddCustomElement(XName::bitKlavierTagNames.DelayLengths_inc, "f", [](int i, double j){ return XAttribute::bitKlavierAttributes.F<double>(i, j); });
                states->AddCustomElement(XName::bitKlavierTagNames.DelayLengthsStates, "b", [](int i, bool j){ return XAttribute::bitKlavierAttributes.B<bool>(i, j); });
                states->AddCustomElement(XName::bitKlavierTagNames.DelayLengthsStates_inc, "b", [](int i, bool j){ return XAttribute::bitKlavierAttributes.B<bool>(i, j); });
                beats->AddCustomElement(XName::bitKlavierTagNames.SmoothLengths, "f", [](int i, double j){ return XAttribute::bitKlavierAttributes.F<double>(i, j); });
                beats->AddCustomElement(XName::bitKlavierTagNames.SmoothLengths_inc, "f", [](int i, double j){ return XAttribute::bitKlavierAttributes.F<double>(i, j); });
                states->AddCustomElement(XName::bitKlavierTagNames.SmoothLengthsStates, "b", [](int i, bool j){ return XAttribute::bitKlavierAttributes.B<bool>(i, j); });
                states->AddCustomElement(XName::bitKlavierTagNames.SmoothLengthsStates_inc, "b", [](int i, bool j){ return XAttribute::bitKlavierAttributes.B<bool>(i, j); });
                beats->AddCustomElement(XName::bitKlavierTagNames.FeedbackCoefficients, "f", [](int i, double j){ return XAttribute::bitKlavierAttributes.F<double>(i, j); });
                beats->AddCustomElement(XName::bitKlavierTagNames.FeedbackCoefficients_inc, "f", [](int i, double j){ return XAttribute::bitKlavierAttributes.F<double>(i, j); });
                states->AddCustomElement(XName::bitKlavierTagNames.FeedbackCoefficientsStates, "b", [](int i, bool j){ return XAttribute::bitKlavierAttributes.B<bool>(i, j); });
                states->AddCustomElement(XName::bitKlavierTagNames.FeedbackCoefficientsStates_inc, "b", [](int i, bool j){ return XAttribute::bitKlavierAttributes.B<bool>(i, j); });
                AllDefault();
            }
            void AllDefault()
            {
                DefaultParamAttributes();
                DefaultBeats();
            }
            void DefaultParamAttributes()
            {
                bool first = true;
                for (std::string opt : opts)
                {
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.BlendronicParams.OutGain((first ? 1.0 : 0.0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.BlendronicParams.DelayBufferSize((first ? 5.0 : 0.0), opt));
                    first = false;
                    if (opt == "") continue;
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.BlendronicParams.Beats(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.BlendronicParams.BeatsStates(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.BlendronicParams.DelayLengths(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.BlendronicParams.DelayLengthsStates(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.BlendronicParams.SmoothLengths(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.BlendronicParams.SmoothLengthsStates(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.BlendronicParams.FeedbackCoefficients(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.BlendronicParams.FeedbackCoefficientsStates(0, opt));
                };
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.BlendronicParams.TargetTypeBlendronicBeatSync(false));
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.BlendronicParams.TargetTypeBlendronicClear(false));
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.BlendronicParams.TargetTypeBlendronicOpenCloseInput(false));
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.BlendronicParams.TargetTypeBlendronicOpenCloseOutput(false));
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.BlendronicParams.TargetTypeBlendronicPatternSync(false));
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.BlendronicParams.TargetTypeBlendronicPausePlay(false));
            };
            void SetParamAttribute(XAttribute* xattr)
            {
                std::string key = xattr->getComparisonString();
                if ((*param_attrs)[key])
                {
                    param_attrs->UpdateCustomPair(xattr);
                }
            }
            template <typename T>
            void SetParamAttribute(std::string key, T value)
            {
                if ((*param_attrs)[key])
                {
                    XAttribute* xattr = new XAttribute(key, to_string(value));
                    param_attrs->UpdateCustomPair(xattr);
                }
            }
            void DefaultBeats()
            {
                beats->ClearChildAttributes();
                states->ClearChildAttributes();
                beats->get(XName::bitKlavierTagNames.Beats)->NewPair(0, 4.0);
                beats->get(XName::bitKlavierTagNames.Beats)->NewPair(1, 3.0);
                beats->get(XName::bitKlavierTagNames.Beats)->NewPair(2, 2.0);
                beats->get(XName::bitKlavierTagNames.Beats)->NewPair(3, 3.0);
                beats->get(XName::bitKlavierTagNames.Beats_inc)->NewPair(0, 0.0);
                states->get(XName::bitKlavierTagNames.BeatsStates)->NewPair(0, true);
                states->get(XName::bitKlavierTagNames.BeatsStates)->NewPair(1, true);
                states->get(XName::bitKlavierTagNames.BeatsStates)->NewPair(2, true);
                states->get(XName::bitKlavierTagNames.BeatsStates)->NewPair(3, true);
                states->get(XName::bitKlavierTagNames.BeatsStates_inc)->NewPair(0, false);
                beats->get(XName::bitKlavierTagNames.DelayLengths)->NewPair(0, 4.0);
                beats->get(XName::bitKlavierTagNames.DelayLengths)->NewPair(1, 3.0);
                beats->get(XName::bitKlavierTagNames.DelayLengths)->NewPair(2, 2.0);
                beats->get(XName::bitKlavierTagNames.DelayLengths)->NewPair(3, 3.0);
                beats->get(XName::bitKlavierTagNames.DelayLengths_inc)->NewPair(0, 0.0);
                states->get(XName::bitKlavierTagNames.DelayLengthsStates)->NewPair(0, true);
                states->get(XName::bitKlavierTagNames.DelayLengthsStates)->NewPair(1, true);
                states->get(XName::bitKlavierTagNames.DelayLengthsStates)->NewPair(2, true);
                states->get(XName::bitKlavierTagNames.DelayLengthsStates)->NewPair(3, true);
                states->get(XName::bitKlavierTagNames.DelayLengthsStates_inc)->NewPair(0, false);
                beats->get(XName::bitKlavierTagNames.SmoothLengths)->NewPair(0, 50.0);
                beats->get(XName::bitKlavierTagNames.SmoothLengths_inc)->NewPair(0, 0.0);
                states->get(XName::bitKlavierTagNames.SmoothLengthsStates)->NewPair(0, true);
                states->get(XName::bitKlavierTagNames.SmoothLengthsStates_inc)->NewPair(0, false);
                beats->get(XName::bitKlavierTagNames.FeedbackCoefficients)->NewPair(0, 0.95);
                beats->get(XName::bitKlavierTagNames.FeedbackCoefficients_inc)->NewPair(0, 0.0);
                states->get(XName::bitKlavierTagNames.FeedbackCoefficientsStates)->NewPair(0, true);
                states->get(XName::bitKlavierTagNames.FeedbackCoefficientsStates_inc)->NewPair(0, false);
            };
            void Add(Beats beat_type, double val)
            {
                switch (beat_type)
                {
                    case BEATS:
                        AddBeat(val);
                        break;
                    case DELAYS:
                        AddDelayLength(val);
                        break;
                    case SMOOTHS:
                        AddSmoothLength(val);
                        break;
                    case COEFFS:
                        AddFeedbackCoefficient(val);
                        break;
                }
            };
            template <typename... A>
            void Set(Beats beat_type, A... vals)
            {
                switch (beat_type)
                {
                    case BEATS:
                        (SetBeats(vals), ...);
                        break;
                    case DELAYS:
                        (SetDelayLengths(vals), ...);
                        break;
                    case SMOOTHS:
                        (SetSmoothLengths(vals), ...);
                        break;
                    case COEFFS:
                        (SetFeedbackCoefficients(vals), ...);
                        break;
                }
            };
            void AddBeat(double beat)
            {
                XAttributeMap<double>* bts = beats->get(XName::bitKlavierTagNames.Beats);
                int c = bts->size();
                bts->UpdatePair(c, beat);
                states->get(XName::bitKlavierTagNames.BeatsStates)->UpdatePair(c, true);
            }
            template <typename... A>
            void SetBeats(A... beat)
            {
                beats->get(XName::bitKlavierTagNames.Beats)->Clear();
                states->get(XName::bitKlavierTagNames.BeatsStates)->Clear();
                (AddBeat(beat), ...);
            }
            template <typename... A>
            void AddBeats(A... beat)
            {
                (AddBeat(beat), ...);
            }
            void AddDelayLength(double delay)
            {
                XAttributeMap<double>* dl = beats->get(XName::bitKlavierTagNames.DelayLengths);
                int c = dl->size();
                dl->UpdatePair(c, delay);
                states->get(XName::bitKlavierTagNames.DelayLengthsStates)->UpdatePair(c, true);
            }
            template <typename... A>
            void SetDelayLengths(A... delays)
            {
                beats->get(XName::bitKlavierTagNames.DelayLengths)->Clear();
                states->get(XName::bitKlavierTagNames.DelayLengthsStates)->Clear();
                (AddDelayLength(delays), ...);
            }
            template <typename... A>
            void AddDelayLengths(A... delays)
            {
                (AddDelayLength(delays), ...);
            }
            void AddSmoothLength(double smooth)
            {
                XAttributeMap<double>* sl = beats->get(XName::bitKlavierTagNames.SmoothLengths);
                int c = sl->size();
                sl->UpdatePair(c, smooth);
                states->get(XName::bitKlavierTagNames.SmoothLengthsStates)->UpdatePair(c, true);
            }
            template <typename... A>
            void SetSmoothLengths(A... smooths)
            {
                beats->get(XName::bitKlavierTagNames.SmoothLengths)->Clear();
                states->get(XName::bitKlavierTagNames.SmoothLengthsStates)->Clear();
                (AddSmoothLength(smooths), ...);
            }
            template <typename... A>
            void AddSmoothLengths(A... smooths)
            {
                (AddSmoothLength(smooths), ...);
            }
            void AddFeedbackCoefficient(double coeff)
            {
                XAttributeMap<double>* fc = beats->get(XName::bitKlavierTagNames.FeedbackCoefficients);
                int c = fc->size();
                fc->UpdatePair(c, coeff);
                states->get(XName::bitKlavierTagNames.FeedbackCoefficientsStates)->UpdatePair(c, true);
            }
            template <typename... A>
            void SetFeedbackCoefficients(A... coeffs)
            {
                beats->get(XName::bitKlavierTagNames.FeedbackCoefficients)->Clear();
                states->get(XName::bitKlavierTagNames.FeedbackCoefficientsStates)->Clear();
                (AddFeedbackCoefficient(coeffs), ...);
            }
            template <typename... A>
            void AddFeedbackCoefficients(A... coeffs)
            {
                (AddFeedbackCoefficient(coeffs), ...);
            }
            void AddRandomBeatsChiSquared(Beats beat_type = BEATS, int n = 10, int df = 5, double exp_val = 5.0, double min_val = 0.0, double max_val = 10.0, double curve = 12.0, char slope = 'e')
            {
                std::chi_squared_distribution<double> chi(df);
                auto e_slope = [curve](double val) { return pow((curve + 1.0), (val / curve)) - 1.0; };
                auto l_slope = [curve](double val) { return curve * (log(val + 1.0) / log(curve + 1.0)); };
                double scaled = slope == 'e' ? exp_val / e_slope((double)df) : slope == 'l' ? exp_val / l_slope((double)df) : exp_val / df;
                for (int i = 0; i < n; i++)
                {
                    double val = slope == 'e' ? e_slope(chi(rng)) : slope == 'l' ? l_slope(chi(rng)) : chi(rng);
                    Add(beat_type, std::max(std::min(val*scaled, max_val), min_val));
                }
            }
            void RandomBeatsChiSquared(Beats beat_type = BEATS, int n = 10, int df = 5, double exp_val = 5.0, double min_val = 0.0, double max_val = 10.0, double curve = 12.0, char slope = 'e')
            {
                switch (beat_type)
                {
                    case BEATS:
                        beats->get(XName::bitKlavierTagNames.Beats)->Clear();
                        states->get(XName::bitKlavierTagNames.BeatsStates)->Clear();
                        break;
                    case DELAYS:
                        beats->get(XName::bitKlavierTagNames.DelayLengths)->Clear();
                        states->get(XName::bitKlavierTagNames.DelayLengthsStates)->Clear();
                        break;
                    case SMOOTHS:
                        beats->get(XName::bitKlavierTagNames.SmoothLengths)->Clear();
                        states->get(XName::bitKlavierTagNames.SmoothLengthsStates)->Clear();
                        break;
                    case COEFFS:
                        beats->get(XName::bitKlavierTagNames.FeedbackCoefficients)->Clear();
                        states->get(XName::bitKlavierTagNames.FeedbackCoefficientsStates)->Clear();
                        break;
                }
                AddRandomBeatsChiSquared(beat_type, n, df, exp_val, min_val, max_val, curve, slope);
            };
            void RandomBlendronic(int complexity)
            {
                double val = complexity / max_complexity;
                double ival = 1 - val;
                int n_of_notes = floor(val * 30) + 2;
                double b_center = pow(2.0, 1+ival);
                double d_center = pow(2.0, 1+ival);
                double s_center = pow(50.0, 1+(ival*2.5));
                double c_center = pow(0.8, 1/(1+val));
                std::uniform_int_distribution<int> u(1, n_of_notes);
                RandomBeatsChiSquared(BEATS, u(rng), 3, b_center, 0, b_center*(1+2.5*ival));
                RandomBeatsChiSquared(DELAYS, u(rng), 3, d_center, 0, d_center*(1+2.5*ival));
                RandomBeatsChiSquared(SMOOTHS, u(rng), 3, s_center, 0, s_center*(1+2.5*ival));
                RandomBeatsChiSquared(COEFFS, u(rng), 3, c_center, 0, 0.995); 
            }
            void Save(std::string file_name = "XBlendronic.xml")
            {
                std::string extra = moded ? "Mod/" : "/";
                file_name = "/Applications/bitKlavier/preparations/Blendronic" + extra + file_name;
                XDocument xdoc(this);
                xdoc.Save(file_name);
            };
    };

    class XResonance : public XPreparation
    {
        protected:
            XAttributeMap<Params>* param_attrs;
            XAttributeMap<double>* ADSR;
            XAttributeMap<int>* closest_keys;
            XAttributeMap<int>* closest_keys_inc;
            XAttributeMap<double>* offsets;
            XAttributeMap<double>* offsets_inc;
            XAttributeMap<double>* gains;
            XAttributeMap<double>* gains_inc;
            XAttributeMap<int>* add;
            XAttributeMap<int>* add_inc;
        public:
            XResonance(XAttribute* id, XAttribute* name) : XPreparation(id, name, XName::bitKlavierTagNames.Resonance, 18, 14, 19)
            {
                XElement* params = new XElement(XName::bitKlavierTagNames.Params, 0);
                appendChild(params);
                param_attrs = new XAttributeMap<Params>(params);
                XElement* adsr = new XElement(XName::bitKlavierTagNames.ADSR, 0);
                XElement* ck = new XElement(XName::bitKlavierTagNames.ClosestKeys, 0);
                XElement* ck_inc = new XElement(XName::bitKlavierTagNames.ClosestKeys_inc, 0);
                XElement* os = new XElement(XName::bitKlavierTagNames.Offsets, 0);
                XElement* os_inc = new XElement(XName::bitKlavierTagNames.Offsets_inc, 0);
                XElement* g = new XElement(XName::bitKlavierTagNames.Gains, 0);
                XElement* g_inc = new XElement(XName::bitKlavierTagNames.Gains_inc, 0);
                XElement* a = new XElement(XName::bitKlavierTagNames.Add, 0);
                XElement* a_inc = new XElement(XName::bitKlavierTagNames.Add_inc, 0);
                *params << adsr << ck << ck_inc << os << os_inc << g << g_inc << a << a_inc;
                closest_keys = new XAttributeMap<int>(ck, "i", [](int i, int j) { return XAttribute::bitKlavierAttributes.I<int>(i, j); });
                closest_keys_inc = new XAttributeMap<int>(ck_inc, "i", [](int i, int j) { return XAttribute::bitKlavierAttributes.I<int>(i, j); });
                offsets = new XAttributeMap<double>(os, "f", [](int i, double j) { return XAttribute::bitKlavierAttributes.F<double>(i, j); });
                offsets_inc = new XAttributeMap<double>(os_inc, "f", [](int i, double j) { return XAttribute::bitKlavierAttributes.F<double>(i, j); });
                gains = new XAttributeMap<double>(g, "f", [](int i, double j) { return XAttribute::bitKlavierAttributes.F<double>(i, j); });
                gains_inc = new XAttributeMap<double>(g_inc, "f", [](int i, double j) { return XAttribute::bitKlavierAttributes.F<double>(i, j); });
                add = new XAttributeMap<int>(a, "i", [](int i, int j) { return XAttribute::bitKlavierAttributes.I<int>(i, j); });
                add_inc = new XAttributeMap<int>(a_inc, "i", [](int i, int j) { return XAttribute::bitKlavierAttributes.I<int>(i, j); });
                ADSR = new XAttributeMap<double>(adsr, "f", [](int i, double j, std::string o) { return XAttribute::bitKlavierAttributes.ADSR.F<double, std::string>(i, j, o); });
                AllDefault();
            }
            void AllDefault()
            {
                DefaultParamAttributes();
                DefaultADSR();
                DefaultResonances();
            }
            void DefaultParamAttributes()
            {
                bool first = true;
                for (std::string opt : opts)
                {
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.ResonanceParams.Gain((first ? 1.0 : 0.0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.ResonanceParams.BlendronicGain((first ? 1.0 : 0.0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.ResonanceParams.StarttimeMin((first ? 400 : 0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.ResonanceParams.StarttimeMax((first ? 4000 : 0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.ResonanceParams.MaxSympStrings((first ? 24 : 0), opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.ResonanceParams.FundamentalKey(0, opt));
                    if (opt == "_inc") continue;
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.ResonanceParams.ResonanceUseGlobalSoundSet(first, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.ResonanceParams.ResonanceSoundSet((first ? "\0" : "0"), opt));
                    first = false;
                    if (opt == "") continue;
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.ResonanceParams.ClosestKeys(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.ResonanceParams.Offsets(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.ResonanceParams.Gains(0, opt));
                    param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.ResonanceParams.Add(0, opt));
                };
            }
            void SetParamAttribute(XAttribute* xattr)
            {
                std::string key = xattr->getComparisonString();
                if ((*param_attrs)[key])
                {
                    param_attrs->UpdateCustomPair(xattr);
                }
            }
            template <typename T>
            void SetParamAttribute(std::string key, T value)
            {
                if ((*param_attrs)[key])
                {
                    XAttribute* xattr = new XAttribute(key, to_string(value));
                    param_attrs->UpdateCustomPair(xattr);
                }
            }
            void DefaultADSR()
            {
                bool first = true;
                for (std::string opt : opts)
                {
                    ADSR->UpdatePair(0, (first ? 2.0 : 0.0), opt);
                    ADSR->UpdatePair(1, (first ? 5.0 : 0.0), opt);
                    ADSR->UpdatePair(2, (first ? 0.9 : 0.0), opt);
                    ADSR->UpdatePair(3, (first ? 250.0 : 0.0), opt);
                    first = false;
                };
            };
            void SetAttack(double a, std::string opt = "")
            {
                a >= 0.0 || (a = 0.0);
                if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
                ADSR->UpdatePair(0, a, opt);
            };
            void SetDecay(double d, std::string opt = "")
            {
                d >= 0.0 || (d = 0.0);
                if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
                ADSR->UpdatePair(1, d, opt);
            };
            void SetSustain(double s, std::string opt = "")
            {
                (s <= 1.0 || (s = 1.0)) && (s >= 0.0 || (s = 0.0));
                if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
                ADSR->UpdatePair(2, s, opt);
            };
            void SetRelease(double r, std::string opt = "")
            {
                r >= 0.0 || (r = 0.0);
                if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
                ADSR->UpdatePair(3, r, opt);
            };
            void SetADSR(double a, double d, double s, double r, std::string opt = "")
            {
                SetAttack(a, opt);
                SetDecay(d, opt);
                SetSustain(s, opt);
                SetRelease(r, opt);
            };
            void RandomADSR(int df = 5, double a_exp_val = 2.0, double d_exp_val = 5.0, double s_exp_val = 0.7, double r_exp_val = 250.0, double s_var = 0.01, std::string opt = "")
            {
                std::chi_squared_distribution<double> chi(df);
                std::normal_distribution<double> norm(s_exp_val, s_var);
                auto re_scale = [](double val) {return exp((log(1001) / 10)*val)-1.0; };
                double scaled = re_scale((double)df);
                double a = re_scale(chi(rng)) * (a_exp_val / scaled);
                double d = re_scale(chi(rng)) * (d_exp_val / scaled);
                double s = norm(rng);
                double r = re_scale(chi(rng)) * (r_exp_val / scaled);
                SetADSR(a, d, s, r, opt);
            };
            void DefaultResonances()
            {
                closest_keys->Clear();
                closest_keys_inc->Clear();
                add->Clear();
                add_inc->Clear();
                for (int i = 0; i < 128; ++i)
                {
                    offsets->UpdatePair(i, 0.0);
                    gains->UpdatePair(i, 1.0);
                }
                offsets_inc->Clear();
                gains_inc->Clear();
            }
            void AddResonance(std::tuple<int, double, double> res)
            {
                if (!closest_keys->HasValue(std::get<0>(res)))
                {
                    int c = closest_keys->size();
                    closest_keys->NewPair(c, std::get<0>(res));
                };
                offsets->UpdatePair(std::get<0>(res), std::get<1>(res));
                gains->UpdatePair(std::get<0>(res), std::max(0.0, std::get<2>(res)));
            }
            void AddResonances(std::vector<std::tuple<int, double, double>> res)
            {
                for (int i = 0; i < res.size(); ++i)
                {
                    AddResonance(res[i]);
                }
            }
            void SetResonances(std::vector<std::tuple<int, double, double>> res)
            {
                DefaultResonances();
                for (int i = 0; i < res.size(); ++i)
                {
                    AddResonance(res[i]);
                }
            }
            void HoldNote(int note)
            {
                if (add->HasValue(note))
                {
                    add->RemoveWithValue(note);
                }
                else
                {
                    int c = add->size();
                    add->NewPair(c, note);
                }
            }
            void SetFundamentalKey(int note, std::string opt = "")
            {
                if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
                param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.ResonanceParams.FundamentalKey(note, opt));
            }
            void SetRandomResonances(int n = 10, double res_var = 1.0, double offset_var = 100.0, double gain_var = 0.1)
            {
                DefaultResonances();
                std::normal_distribution<double> norm(0.0, res_var);
                std::normal_distribution<double> off(0.0, offset_var);
                std::normal_distribution<double> gain(1.0, gain_var);
                std::vector<int> ck;
                for (int i = 0; i < n; ++i)
                {
                    int val;
                    do
                    {
                        if (i < 25)
                        {
                            val = floor(std::max(0.0, 12.0 * log2(i + norm(rng))));
                        }
                        else
                        {
                            val = floor(exp((i+15.0+norm(rng))/12.0));
                        }
                    }
                    while (std::find(ck.begin(), ck.end(), val) != ck.end());
                    ck.push_back(val);
                }
                std::sort(ck.begin(), ck.end());
                for (int i : ck)
                {
                    std::tuple<int, double, double> res(i, off(rng), gain(rng));
                    AddResonance(res);
                }
            }
            void RandomResonance(int complexity)
            {
                double val = complexity / max_complexity;
                int n_of_notes = floor(val * 18);
                SetRandomResonances(n_of_notes, val + 1.0, val*100.0 + 10.0, 0.5*val+0.1);
                RandomADSR(n_of_notes+1, 2.0, 5.0, 0.7, 250.0, val*5.0);
                SetFundamentalKey(getRandomKeys(1, 0, 127, 20, 16)[0]);
                int n2 = floor(n_of_notes/2);
                std::vector<int> h = getRandomKeys(n2);
                for (int i : h) HoldNote(i);
            }
            void Save(std::string file_name = "XResonance.xml")
            {
                std::string extra = moded ? "Mod/" : "/";
                file_name = "/Applications/bitKlavier/preparations/Resonance" + extra + file_name;
                XDocument xdoc(this);
                xdoc.Save(file_name);
            };
    };

    class XReset : public XPreparation
    {
        public:
            XReset(XAttribute* id, XAttribute* name) : XPreparation(id, name, XName::bitKlavierTagNames.Item, 13, 0, 0)
            {
                just_item = true;
            };
            void Mod() {};
    };

    class XComment : public XPreparation
    {
        public:
            XComment(std::string comment) : XPreparation(XAttribute::bitKlavierAttributes.ID(0), XAttribute::bitKlavierAttributes.Name("comment"), XName::bitKlavierTagNames.Item, 15, 0, 0)
            {
                just_item = true;
                ChangeText(comment);
            }
            void ChangeText(std::string comment)
            {
                text->setValue(comment);
            }
            void Mod() {};
    };

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
            BitKlavier(XAttribute* g_name) : XElement(XName::bitKlavierTagNames.Gallery, 0)
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
            void DefaultParamAttributes()
            {
                sType = setAttribute(XAttribute::bitKlavierAttributes.GalleryParams.SampleType(5));
                sfURL = setAttribute(XAttribute::bitKlavierAttributes.GalleryParams.SoundfontURL("XSynth"));
                sfInst = setAttribute(XAttribute::bitKlavierAttributes.GalleryParams.SoundfontInst(0));
                dfPiano = setAttribute(XAttribute::bitKlavierAttributes.GalleryParams.DefaultPiano(1));
            }
            void SetGeneral(XGeneral* gen)
            {
                general = gen;
            }
            void SetEqualizer(XEqualizer* equalizer)
            {
                eq = equalizer;
            }
            void SetCompressor(XCompressor* compressor)
            {
                comp = compressor;
            }
            void AddPiano(XPiano* piano)
            {
                for (auto it = piano->BeginPreparations(); it != piano->EndPreparations(); ++it)
                {
                    appendChild(*it);
                }
                appendChild(piano);
            }
            void Save()
            {
                std::string file_name = "/Applications/bitKlavier/galleries/" + to_string(*name->getValue()) + ".xml";
                XDocument xdoc(this);
                xdoc.Save(file_name);
            };
    };
};