#include "xnostalgic.hpp"

namespace bkr
{
    XNostalgic::XNostalgic(XAttribute* id, XAttribute* name) : XPreparation(id, name, XName::bitKlavierTagNames.Nostalgic, 2, 23, 8)
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
    void XNostalgic::AllDefault()
    {
        DefaultParamAttributes();
        DefaultReverseADSR();
        DefaultUndertowADSR();
        DefaultTranspositions();
    };
    void XNostalgic::DefaultParamAttributes()
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
    void XNostalgic::SetParamAttribute(XAttribute* xattr)
    {
        std::string key = xattr->getComparisonString();
        if ((*param_attrs)[key])
        {
            param_attrs->UpdateCustomPair(xattr);
            if (ds[key]) GetDirty(ds[key]);
        }
    }
    template <typename T>
    void XNostalgic::SetParamAttribute(std::string key, T value)
    {
        if ((*param_attrs)[key])
        {
            XAttribute* xattr = new XAttribute(key, to_string(value));
            param_attrs->UpdateCustomPair(xattr);
            if (ds[key]) GetDirty(ds[key]);
        }
    }
    void XNostalgic::DefaultReverseADSR()
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
    void XNostalgic::DefaultUndertowADSR()
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
    void XNostalgic::SetReverseAttack(double a, std::string opt)
    {
        a >= 0.0 || (a = 0.0);
        if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
        reverseADSR->UpdatePair(0, a, opt);
    };
    void XNostalgic::SetUndertowAttack(double a, std::string opt)
    {
        a >= 0.0 || (a = 0.0);
        if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
        undertowADSR->UpdatePair(0, a, opt);
    };
    void XNostalgic::SetReverseDecay(double d, std::string opt)
    {
        d >= 0.0 || (d = 0.0);
        if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
        reverseADSR->UpdatePair(1, d, opt);
    };
    void XNostalgic::SetUndertowDecay(double d, std::string opt)
    {
        d >= 0.0 || (d = 0.0);
        if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
        undertowADSR->UpdatePair(1, d, opt);
    };
    void XNostalgic::SetReverseSustain(double s, std::string opt)
    {
        (s <= 1.0 || (s = 1.0)) && (s >= 0.0 || (s = 0.0));
        if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
        reverseADSR->UpdatePair(2, s, opt);
    };
    void XNostalgic::SetUndertowSustain(double s, std::string opt)
    {
        (s <= 1.0 || (s = 1.0)) && (s >= 0.0 || (s = 0.0));
        if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
        undertowADSR->UpdatePair(2, s, opt);
    };
    void XNostalgic::SetReverseRelease(double r, std::string opt)
    {
        r >= 0.0 || (r = 0.0);
        if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
        reverseADSR->UpdatePair(3, r, opt);
    };
    void XNostalgic::SetUndertowRelease(double r, std::string opt)
    {
        r >= 0.0 || (r = 0.0);
        if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
        undertowADSR->UpdatePair(3, r, opt);
    };
    void XNostalgic::SetReverseADSR(double a, double d, double s, double r, std::string opt)
    {
        SetReverseAttack(a, opt);
        SetReverseDecay(d, opt);
        SetReverseSustain(s, opt);
        SetReverseRelease(r, opt);
    };
    void XNostalgic::SetUndertowADSR(double a, double d, double s, double r, std::string opt)
    {
        SetUndertowAttack(a, opt);
        SetUndertowDecay(d, opt);
        SetUndertowSustain(s, opt);
        SetUndertowRelease(r, opt);
    };
    void XNostalgic::RandomReverseADSR(int df, double a_exp_val, double d_exp_val, double s_exp_val, double r_exp_val, double s_var, std::string opt)
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
    void XNostalgic::RandomUndertowADSR(int df, double a_exp_val, double d_exp_val, double s_exp_val, double r_exp_val, double s_var, std::string opt)
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
    void XNostalgic::DefaultTranspositions()
    {
        transposition->Clear();
        transposition_inc->Clear();
        transposition->NewPair(0, 0.0);
        transposition_inc->NewPair(0, 0.0);
    };
    void XNostalgic::AddTransposition(double n)
    {
        int i = transposition->size();
        transposition->NewPair(i, n);
    };
    template <typename... A>
    void XNostalgic::SetTranspositions(A... n)
    {
        transposition->Clear();
        ((AddTransposition(n)), ...);
    };
    template <typename... A>
    void XNostalgic::AddTranspositions(A... n)
    {
        ((AddTransposition(n)), ...);
    };
    void XNostalgic::RandomTranspositionsGauss(int n, double exp_int, double var_int, char slope, bool root, bool integer)
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
    void XNostalgic::RandomTranspositionsChiSquared(int n, bool above, int df, double exp_int, double max_int, char slope, bool root, bool integer)
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
    void XNostalgic::AddRandomTranspositionsGauss(int n, double exp_int, double var_int, char slope, bool integer)
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
    void XNostalgic::AddRandomTranspositionsChiSquared(int n, bool above, int df, double exp_int, double max_int, char slope, bool integer)
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
    void XNostalgic::NoteLengthMultiplier(double val, std::string opt)
    {
        if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
        param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.NostalgicParams.LengthMultiplier(val, opt));
    };
    void XNostalgic::WaveDistance(double val, std::string opt)
    {
        if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
        param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.NostalgicParams.WaveDistance(val, opt));
    }
    void XNostalgic::RandomWaveDistance(double lambda)
    {
        std::exponential_distribution<double> e(lambda);
        WaveDistance(e(rng));
    }
    void XNostalgic::Undertow(double val, std::string opt)
    {
        if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
        param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.NostalgicParams.Undertow(val, opt));
    }
    void XNostalgic::RandomUndertow(double lambda)
    {
        std::exponential_distribution<double> e(lambda);
        Undertow(e(rng));
    }
    void XNostalgic::RandomNostalgic(int complexity)
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
    void XNostalgic::Save(std::string file_name)
    {
        std::string extra = moded ? "Mod/" : "/";
        file_name = "/Applications/bitKlavier/preparations/Nostalgic" + extra + file_name;
        XDocument xdoc(this);
        xdoc.Save(file_name);
    };
}