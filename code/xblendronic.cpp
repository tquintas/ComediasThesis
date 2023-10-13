#include "xblendronic.hpp"

namespace bkr
{
    XBlendronic::XBlendronic(XAttribute* id, XAttribute* name) : XPreparation(id, name, XName::bitKlavierTagNames.Blendronic, 16, 8, 17)
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
    void XBlendronic::AllDefault()
    {
        DefaultParamAttributes();
        DefaultBeats();
    }
    void XBlendronic::DefaultParamAttributes()
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
    void XBlendronic::SetParamAttribute(XAttribute* xattr)
    {
        std::string key = xattr->getComparisonString();
        if ((*param_attrs)[key])
        {
            param_attrs->UpdateCustomPair(xattr);
        }
    }
    template <typename T>
    void XBlendronic::SetParamAttribute(std::string key, T value)
    {
        if ((*param_attrs)[key])
        {
            XAttribute* xattr = new XAttribute(key, to_string(value));
            param_attrs->UpdateCustomPair(xattr);
        }
    }
    void XBlendronic::DefaultBeats()
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
    void XBlendronic::Add(Beats beat_type, double val)
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
    void XBlendronic::Set(Beats beat_type, A... vals)
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
    void XBlendronic::AddBeat(double beat)
    {
        XAttributeMap<double>* bts = beats->get(XName::bitKlavierTagNames.Beats);
        int c = bts->size();
        bts->UpdatePair(c, beat);
        states->get(XName::bitKlavierTagNames.BeatsStates)->UpdatePair(c, true);
    }
    template <typename... A>
    void XBlendronic::SetBeats(A... beat)
    {
        beats->get(XName::bitKlavierTagNames.Beats)->Clear();
        states->get(XName::bitKlavierTagNames.BeatsStates)->Clear();
        (AddBeat(beat), ...);
    }
    template <typename... A>
    void XBlendronic::AddBeats(A... beat)
    {
        (AddBeat(beat), ...);
    }
    void XBlendronic::AddDelayLength(double delay)
    {
        XAttributeMap<double>* dl = beats->get(XName::bitKlavierTagNames.DelayLengths);
        int c = dl->size();
        dl->UpdatePair(c, delay);
        states->get(XName::bitKlavierTagNames.DelayLengthsStates)->UpdatePair(c, true);
    }
    template <typename... A>
    void XBlendronic::SetDelayLengths(A... delays)
    {
        beats->get(XName::bitKlavierTagNames.DelayLengths)->Clear();
        states->get(XName::bitKlavierTagNames.DelayLengthsStates)->Clear();
        (AddDelayLength(delays), ...);
    }
    template <typename... A>
    void XBlendronic::AddDelayLengths(A... delays)
    {
        (AddDelayLength(delays), ...);
    }
    void XBlendronic::AddSmoothLength(double smooth)
    {
        XAttributeMap<double>* sl = beats->get(XName::bitKlavierTagNames.SmoothLengths);
        int c = sl->size();
        sl->UpdatePair(c, smooth);
        states->get(XName::bitKlavierTagNames.SmoothLengthsStates)->UpdatePair(c, true);
    }
    template <typename... A>
    void XBlendronic::SetSmoothLengths(A... smooths)
    {
        beats->get(XName::bitKlavierTagNames.SmoothLengths)->Clear();
        states->get(XName::bitKlavierTagNames.SmoothLengthsStates)->Clear();
        (AddSmoothLength(smooths), ...);
    }
    template <typename... A>
    void XBlendronic::AddSmoothLengths(A... smooths)
    {
        (AddSmoothLength(smooths), ...);
    }
    void XBlendronic::AddFeedbackCoefficient(double coeff)
    {
        XAttributeMap<double>* fc = beats->get(XName::bitKlavierTagNames.FeedbackCoefficients);
        int c = fc->size();
        fc->UpdatePair(c, coeff);
        states->get(XName::bitKlavierTagNames.FeedbackCoefficientsStates)->UpdatePair(c, true);
    }
    template <typename... A>
    void XBlendronic::SetFeedbackCoefficients(A... coeffs)
    {
        beats->get(XName::bitKlavierTagNames.FeedbackCoefficients)->Clear();
        states->get(XName::bitKlavierTagNames.FeedbackCoefficientsStates)->Clear();
        (AddFeedbackCoefficient(coeffs), ...);
    }
    template <typename... A>
    void XBlendronic::AddFeedbackCoefficients(A... coeffs)
    {
        (AddFeedbackCoefficient(coeffs), ...);
    }
    void XBlendronic::AddRandomBeatsChiSquared(Beats beat_type = BEATS, int n = 10, int df = 5, double exp_val = 5.0, double min_val = 0.0, double max_val = 10.0, double curve = 12.0, char slope = 'e')
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
    void XBlendronic::RandomBeatsChiSquared(Beats beat_type = BEATS, int n = 10, int df = 5, double exp_val = 5.0, double min_val = 0.0, double max_val = 10.0, double curve = 12.0, char slope = 'e')
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
    void XBlendronic::RandomBlendronic(int complexity)
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
    void XBlendronic::Save(std::string file_name = "XBlendronic.xml")
    {
        std::string extra = moded ? "Mod/" : "/";
        file_name = "/Applications/bitKlavier/preparations/Blendronic" + extra + file_name;
        XDocument xdoc(this);
        xdoc.Save(file_name);
    };
}