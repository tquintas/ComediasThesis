#include "xtuning.hpp"

namespace bkr
{
    XTuning::XTuning(XAttribute* id, XAttribute* name) : XPreparation(id, name, XName::bitKlavierTagNames.Tuning, 3, 30, 9)
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
    void XTuning::AllDefault()
    {
        DefaultParamAttributes();
        DefaultSpringParams();
        DefaultOffsets();
        DefaultSpringTuning();
    }
    void XTuning::DefaultParamAttributes()
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
    void XTuning::SetParamAttribute(XAttribute* xattr)
    {
        std::string key = xattr->getComparisonString();
        if ((*param_attrs)[key])
        {
            param_attrs->UpdateCustomPair(xattr);
        }
    }
    template <typename T>
    void XTuning::SetParamAttribute(std::string key, T value)
    {
        if ((*param_attrs)[key])
        {
            XAttribute* xattr = new XAttribute(key, to_string(value));
            param_attrs->UpdateCustomPair(xattr);
        }
    }
    void XTuning::DefaultSpringParams()
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
    void XTuning::SetSpringParamAttribute(XAttribute* xattr)
    {
        std::string key = xattr->getComparisonString();
        if ((*spring_param_attrs)[key])
        {
            spring_param_attrs->UpdateCustomPair(xattr);
        }
    }
    template <typename T>
    void XTuning::SetSpringParamAttribute(std::string key, T value)
    {
        if ((*spring_param_attrs)[key])
        {
            XAttribute* xattr = new XAttribute(key, to_string(value));
            spring_param_attrs->UpdateCustomPair(xattr);
        }
    }
    void XTuning::DefaultOffsets()
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
    void XTuning::DefaultSpringTuning()
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
    void XTuning::SetCustomScale(std::vector<double> offs)
    {
        offs.resize(12);
        for (int i = 0; i < 12; ++i)
        {
            custom_scale->UpdatePair(i, offs[i]);
        }
        SetParamAttribute(XAttribute::bitKlavierAttributes.TuningParams.Scale(8));
    }
    void XTuning::RandomCustomScale(double mean = 0.0, double std_dev = 25.0)
    {
        std::normal_distribution<double> n(mean, std_dev);
        for (int i = 0; i < 12; ++i)
        {
            custom_scale->UpdatePair(i, n(rng));
        }
        SetParamAttribute(XAttribute::bitKlavierAttributes.TuningParams.Scale(8));
    }
    void XTuning::SetCustomSpringScale(std::vector<double> offs)
    {
        offs.resize(12);
        for (int i = 0; i < 12; ++i)
        {
            interval_scale->UpdatePair(i, offs[i]);
        }
        SetSpringParamAttribute(XAttribute::bitKlavierAttributes.SpringParams.IntervalTuningId(8));
    }
    void XTuning::RandomCustomSpringScale(double mean, double std_dev)
    {
        std::normal_distribution<double> n(mean, std_dev);
        for (int i = 0; i < 12; ++i)
        {
            interval_scale->UpdatePair(i, n(rng));
        }
        SetSpringParamAttribute(XAttribute::bitKlavierAttributes.SpringParams.IntervalTuningId(8));
    }
    void XTuning::AddAbsoluteOffset(int key, double off)
    {
        key = std::min(255, std::max(0, key));
        absolute_offsets->UpdatePair(key, off);
    }
    void XTuning::AddAbsoluteOffsets(std::vector<std::tuple<int, double>> offs)
    {
        for (std::tuple<int, double> t : offs)
        {
            AddAbsoluteOffset(std::get<0>(t), std::get<1>(t));
        }
    }
    void XTuning::SetAbsoluteOffsets(std::vector<std::tuple<int, double>> offs)
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
    void XTuning::RandomAbsoluteOffsets(int n, double key_mean, double key_stddev, double off_mean, double off_stddev)
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
    void XTuning::AddTether(int key, double val)
    {
        key = std::min(127, std::max(0, key));
        val = std::min(1.0, std::max(0.0, val));
        tethers->UpdatePair(key, val);
    }
    void XTuning::AddTethers(std::vector<std::tuple<int, double>> tths)
    {
        for (std::tuple<int, double> t : tths)
        {
            AddTether(std::get<0>(t), std::get<1>(t));
        }
    }
    void XTuning::SetTethers(std::vector<std::tuple<int, double>> tths)
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
    void XTuning::RandomTethers(int n, double key_mean, double key_stddev, double tth_mean, double tth_stddev)
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
    void XTuning::SetSprings(std::vector<double> sprgs, std::vector<bool> modes)
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
    void XTuning::RandomSprings(double mean, double std_dev)
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
    void XTuning::RandomNormalTuning(int complexity)
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
    void XTuning::RandomAdaptiveTuning(int complexity)
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
    void XTuning::RandomAdaptiveAnchoredTuning(int complexity)
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
    void XTuning::RandomSpringTuning(int complexity)
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
    void XTuning::Save(std::string file_name)
    {
        std::string extra = moded ? "Mod/" : "/";
        file_name = "/Applications/bitKlavier/preparations/Tuning" + extra + file_name;
        XDocument xdoc(this);
        xdoc.Save(file_name);
    };
}