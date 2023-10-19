#include "xresonance.hpp"

namespace bkr
{
    XResonance::XResonance(XAttribute* id, XAttribute* name) : XPreparation(id, name, XName::bitKlavierTagNames.Resonance, 18, 14, 19)
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
    void XResonance::AllDefault()
    {
        DefaultParamAttributes();
        DefaultADSR();
        DefaultResonances();
    }
    void XResonance::DefaultParamAttributes()
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
    void XResonance::SetParamAttribute(XAttribute* xattr)
    {
        std::string key = xattr->getComparisonString();
        if ((*param_attrs)[key])
        {
            param_attrs->UpdateCustomPair(xattr);
        }
    }
    template <typename T>
    void XResonance::SetParamAttribute(std::string key, T value)
    {
        if ((*param_attrs)[key])
        {
            XAttribute* xattr = new XAttribute(key, to_string(value));
            param_attrs->UpdateCustomPair(xattr);
        }
    }
    void XResonance::DefaultADSR()
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
    void XResonance::SetAttack(double a, std::string opt)
    {
        a >= 0.0 || (a = 0.0);
        if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
        ADSR->UpdatePair(0, a, opt);
    };
    void XResonance::SetDecay(double d, std::string opt)
    {
        d >= 0.0 || (d = 0.0);
        if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
        ADSR->UpdatePair(1, d, opt);
    };
    void XResonance::SetSustain(double s, std::string opt)
    {
        (s <= 1.0 || (s = 1.0)) && (s >= 0.0 || (s = 0.0));
        if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
        ADSR->UpdatePair(2, s, opt);
    };
    void XResonance::SetRelease(double r, std::string opt)
    {
        r >= 0.0 || (r = 0.0);
        if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
        ADSR->UpdatePair(3, r, opt);
    };
    void XResonance::SetADSR(double a, double d, double s, double r, std::string opt)
    {
        SetAttack(a, opt);
        SetDecay(d, opt);
        SetSustain(s, opt);
        SetRelease(r, opt);
    };
    void XResonance::RandomADSR(int df, double a_exp_val, double d_exp_val, double s_exp_val, double r_exp_val, double s_var, std::string opt)
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
    void XResonance::DefaultResonances()
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
    void XResonance::AddResonance(std::tuple<int, double, double> res)
    {
        if (!closest_keys->HasValue(std::get<0>(res)))
        {
            int c = closest_keys->size();
            closest_keys->NewPair(c, std::get<0>(res));
        };
        offsets->UpdatePair(std::get<0>(res), std::get<1>(res));
        gains->UpdatePair(std::get<0>(res), std::max(0.0, std::get<2>(res)));
    }
    void XResonance::AddResonances(std::vector<std::tuple<int, double, double>> res)
    {
        for (int i = 0; i < res.size(); ++i)
        {
            AddResonance(res[i]);
        }
    }
    void XResonance::SetResonances(std::vector<std::tuple<int, double, double>> res)
    {
        DefaultResonances();
        for (int i = 0; i < res.size(); ++i)
        {
            AddResonance(res[i]);
        }
    }
    void XResonance::HoldNote(int note)
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
    void XResonance::SetFundamentalKey(int note, std::string opt)
    {
        if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
        param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.ResonanceParams.FundamentalKey(note, opt));
    }
    void XResonance::RandomResonances(int n, double res_var, double offset_var, double gain_var)
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
    void XResonance::RandomResonance(int complexity)
    {
        double val = complexity / max_complexity;
        int n_of_notes = floor(val * 18);
        RandomResonances(n_of_notes, val + 1.0, val*100.0 + 10.0, 0.5*val+0.1);
        RandomADSR(n_of_notes+1, 2.0, 5.0, 0.7, 250.0, val*5.0);
        SetFundamentalKey(getRandomKeys(1, 0, 127, 20, 16)[0]);
        int n2 = floor(n_of_notes/2);
        std::vector<int> h = getRandomKeys(n2);
        for (int i : h) HoldNote(i);
    }
    void XResonance::Save(std::string file_name)
    {
        std::string extra = moded ? "Mod/" : "/";
        file_name = "/Applications/bitKlavier/preparations/Resonance" + extra + file_name;
        XDocument xdoc(this);
        xdoc.Save(file_name);
    };
}