#include "xsynchronic.hpp"

namespace bkr
{
    XSynchronic::XSynchronic(XAttribute* id, XAttribute* name) : XPreparation(id, name, XName::bitKlavierTagNames.Synchronic, 1, 25, 7)
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
    void XSynchronic::AllDefault()
    {
        DefaultBeats();
        DefaultParamAttributes();
        DefaultADSRs();
    }
    void XSynchronic::DefaultBeats()
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
    void XSynchronic::DefaultParamAttributes()
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
    void XSynchronic::SetParamAttribute(XAttribute* xattr)
    {
        std::string key = xattr->getComparisonString();
        if ((*param_attrs)[key])
        {
            param_attrs->UpdateCustomPair(xattr);
            if (ds[key]) GetDirty(ds[key]);
        }
    }
    template <typename T>
    void XSynchronic::SetParamAttribute(std::string key, T value)
    {
        if ((*param_attrs)[key])
        {
            XAttribute* xattr = new XAttribute(key, to_string(value));
            param_attrs->UpdateCustomPair(xattr);
            if (ds[key]) GetDirty(ds[key]);
        }
    }
    void XSynchronic::DefaultADSRs()
    {
        SetADSR(3.0, 3.0, 1.0, 30.0);
    };
    void XSynchronic::AddTransposition(double transp)
    {
        int c = transp_offsets->size();
        transp_offsets->AddElement(c, "f", [](int i, double j){ return XAttribute::bitKlavierAttributes.F<double>(i, j); });
        (*transp_offsets)(c)->NewPair(0, transp);
        states->get(XName::bitKlavierTagNames.TranspOffsetsStates)->UpdatePair(c, true);
    };
    void XSynchronic::AddTranspositions(std::vector<double> transps)
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
    void XSynchronic::SetTranspositions(A... n)
    {
        transp_offsets->Clear();
        ((AddTransposition(n)), ...);
    };
    template <typename... A>
    void XSynchronic::AddTranspositions(A... n)
    {
        ((AddTransposition(n)), ...);
    };
    void XSynchronic::AddBeatMultiplier(double beat)
    {
        XAttributeMap<double>* beatMultipliers = beats->get(XName::bitKlavierTagNames.BeatMultipliers);
        int c = beatMultipliers->size();
        beatMultipliers->UpdatePair(c, beat);
        states->get(XName::bitKlavierTagNames.BeatMultipliersStates)->UpdatePair(c, true);
    }
    template <typename... A>
    void XSynchronic::SetBeatMultipliers(A... n)
    {
        beats->get(XName::bitKlavierTagNames.BeatMultipliers)->Clear();
        (AddBeatMultiplier(n), ...);
    }
    template <typename... A>
    void XSynchronic::AddBeatMultipliers(A... n)
    {
        (AddBeatMultiplier(n), ...);
    }
    void XSynchronic::AddLengthMultiplier(double length)
    {
        XAttributeMap<double>* lengthMultipliers = beats->get(XName::bitKlavierTagNames.LengthMultipliers);
        int c = lengthMultipliers->size();
        lengthMultipliers->UpdatePair(c, length);
        states->get(XName::bitKlavierTagNames.LengthMultipliersStates)->UpdatePair(c, true);
    }
    template <typename... A>
    void XSynchronic::SetLengthMultipliers(A... n)
    {
        beats->get(XName::bitKlavierTagNames.LengthMultipliers)->Clear();
        (AddLengthMultiplier(n), ...);
    }
    template <typename... A>
    void XSynchronic::AddLengthMultipliers(A... n)
    {
        (AddLengthMultiplier(n), ...);
    }
    void XSynchronic::AddAccentMultiplier(double accent)
    {
        XAttributeMap<double>* accentMultipliers = beats->get(XName::bitKlavierTagNames.AccentMultipliers);
        int c = accentMultipliers->size();
        accentMultipliers->UpdatePair(c, accent);
        states->get(XName::bitKlavierTagNames.AccentMultipliersStates)->UpdatePair(c, true);
    }
    template <typename... A>
    void XSynchronic::SetAccentMultipliers(A... n)
    {
        beats->get(XName::bitKlavierTagNames.AccentMultipliers)->Clear();
        (AddAccentMultiplier(n), ...);
    }
    template <typename... A>
    void XSynchronic::AddAccentMultipliers(A... n)
    {
        (AddAccentMultiplier(n), ...);
    }
    void XSynchronic::AddADSR(double a, double d, double s, double r)
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
    void XSynchronic::SetADSR(double a, double d, double s, double r)
    {
        ADSRs->Clear();
        AddADSR(a,d,s,r);
    }
    void XSynchronic::AddRandomADSR(int df, double a_exp_val, double d_exp_val, double s_exp_val, double r_exp_val, double s_var)
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
    void XSynchronic::AddRandomTranpositionsGauss(int n, int max_cluster, double exp_int, double var_int, char slope, bool integer)
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
            AddTranspositions(vals);
        }
    }
    void XSynchronic::RandomTranpositionsGauss(int n, int max_cluster, double exp_int, double var_int, char slope, bool integer)
    {
        transp_offsets->Clear();
        AddRandomTranpositionsGauss(n, max_cluster, exp_int, var_int, slope, integer);
    }
    void XSynchronic::AddRandomTranpositionsChiSquared(int n, int max_cluster, bool above, int df, double exp_int, double max_int, char slope, bool integer)
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
            AddTranspositions(vals);
        }
    }
    void XSynchronic::RandomTranpositionsChiSquared(int n, int max_cluster, bool above, int df, double exp_int, double max_int, char slope, bool integer)
    {
        transp_offsets->Clear();
        AddRandomTranpositionsChiSquared(n, max_cluster, above, df, exp_int, max_int, slope, integer);
    }
    void XSynchronic::AddRandomBeatsGauss(int n, double exp_int, double var_int, char slope, bool integer)
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
    void XSynchronic::RandomBeatsGauss(int n, double exp_int, double var_int, char slope, bool integer)
    {
        beats->get(XName::bitKlavierTagNames.BeatMultipliers)->Clear();
        AddRandomBeatsGauss(n, exp_int, var_int, slope, integer);
    }
    void XSynchronic::AddRandomBeatsChiSquared(int n, bool above, int df, double exp_int, double max_int, char slope, bool integer)
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
    void XSynchronic::RandomBeatsChiSquared(int n, bool above, int df, double exp_int, double max_int, char slope, bool integer)
    {
        beats->get(XName::bitKlavierTagNames.BeatMultipliers)->Clear();
        AddRandomBeatsChiSquared(n, above, df, exp_int, max_int, slope, integer);
    }
    void XSynchronic::AddRandomLengthsGauss(int n, double exp_int, double var_int, char slope, bool integer)
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
    void XSynchronic::RandomLengthsGauss(int n, double exp_int, double var_int, char slope, bool integer)
    {
        beats->get(XName::bitKlavierTagNames.LengthMultipliers)->Clear();
        AddRandomLengthsGauss(n, exp_int, var_int, slope, integer);
    }
    void XSynchronic::AddRandomLengthsChiSquared(int n, bool above, int df, double exp_int, double max_int, char slope, bool integer)
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
    void XSynchronic::RandomLengthsChiSquared(int n, bool above, int df, double exp_int, double max_int, char slope, bool integer)
    {
        beats->get(XName::bitKlavierTagNames.LengthMultipliers)->Clear();
        AddRandomLengthsChiSquared(n, above, df, exp_int, max_int, slope, integer);
    }
    void XSynchronic::AddRandomAccentsGauss(int n, double exp_int, double var_int, char slope, bool integer)
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
    void XSynchronic::RandomAccentsGauss(int n, double exp_int, double var_int, char slope, bool integer)
    {
        beats->get(XName::bitKlavierTagNames.AccentMultipliers)->Clear();
        AddRandomAccentsGauss(n, exp_int, var_int, slope, integer);
    }
    void XSynchronic::AddRandomAccentsChiSquared(int n, bool above, int df, double exp_int, double max_int, char slope, bool integer)
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
    void XSynchronic::RandomAccentsChiSquared(int n, bool above, int df, double exp_int, double max_int, char slope, bool integer)
    {
        beats->get(XName::bitKlavierTagNames.AccentMultipliers)->Clear();
        AddRandomAccentsChiSquared(n, above, df, exp_int, max_int, slope, integer);
    }
    void XSynchronic::NumPulses(int n, int skip, std::string opt)
    {
        if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
        param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.NumBeats(n, opt));
        param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.BeatsToSkip(skip, opt));
    }
    void XSynchronic::NumLayers(int n, std::string opt)
    {
        if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
        param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.NumClusters(n, opt));
    }
    void XSynchronic::Cluster(int min, int max, int cap, double thresh, std::string opt)
    {
        if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
        param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.ClusterMin(min, opt));
        param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.ClusterMax(max, opt));
        param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.ClusterCap(cap, opt));
        param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.ClusterThresh(thresh, opt));
    }
    void XSynchronic::Velocity(int min, int max, std::string opt)
    {
        if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
        param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.VelocityMin(min, opt));
        param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.VelocityMax(max, opt));
    }
    void XSynchronic::Hold(int min, int max, std::string opt)
    {
        if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
        param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.HoldMin(min, opt));
        param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.HoldMax(max, opt));
    }
    void XSynchronic::Modes(bool key_on, int pulse_triggered, std::string opt)
    {
        if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
        param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.OnOffMode(!key_on, opt));
        param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.SynchronicParams.Mode(pulse_triggered, opt));
    }
    void XSynchronic::RandomSynchronic(int complexity)
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
    void XSynchronic::Save(std::string file_name)
    {
        std::string extra = moded ? "Mod/" : "/";
        file_name = "/Applications/bitKlavier/preparations/Synchronic" + extra + file_name;
        XDocument xdoc(this);
        xdoc.Save(file_name);
    };
}