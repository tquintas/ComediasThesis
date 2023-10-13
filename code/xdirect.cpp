#include "xdirect.hpp"

namespace bkr
{
    XDirect::XDirect(XAttribute* id, XAttribute* name) : XPreparation(id, name, XName::bitKlavierTagNames.Direct, 0, 13, 6)
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
    void XDirect::AllDefault()
    {
        DefaultParamAttributes();
        DefaultADSR();
        DefaultTranspositions();
    };
    void XDirect::DefaultParamAttributes()
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
    void XDirect::SetParamAttribute(XAttribute* xattr)
    {
        std::string key = xattr->getComparisonString();
        if ((*param_attrs)[key])
        {
            param_attrs->UpdateCustomPair(xattr);
            if (ds[key]) GetDirty(ds[key]);
        }
    }
    template <typename T>
    void XDirect::SetParamAttribute(std::string key, T value)
    {
        if ((*param_attrs)[key])
        {
            XAttribute* xattr = new XAttribute(key, to_string(value));
            param_attrs->UpdateCustomPair(xattr);
            if (ds[key]) GetDirty(ds[key]);
        }
    }
    void XDirect::DefaultADSR()
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
    void XDirect::SetAttack(double a, std::string opt = "")
    {
        a >= 0.0 || (a = 0.0);
        if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
        ADSR->UpdatePair(0, a, opt);
    };
    void XDirect::SetDecay(double d, std::string opt = "")
    {
        d >= 0.0 || (d = 0.0);
        if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
        ADSR->UpdatePair(1, d, opt);
    };
    void XDirect::SetSustain(double s, std::string opt = "")
    {
        (s <= 1.0 || (s = 1.0)) && (s >= 0.0 || (s = 0.0));
        if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
        ADSR->UpdatePair(2, s, opt);
    };
    void XDirect::SetRelease(double r, std::string opt = "")
    {
        r >= 0.0 || (r = 0.0);
        if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
        ADSR->UpdatePair(3, r, opt);
    };
    void XDirect::SetADSR(double a, double d, double s, double r, std::string opt = "")
    {
        SetAttack(a, opt);
        SetDecay(d, opt);
        SetSustain(s, opt);
        SetRelease(r, opt);
    };
    void XDirect::RandomADSR(int df = 5, double a_exp_val = 2.0, double d_exp_val = 5.0, double s_exp_val = 0.7, double r_exp_val = 250.0, double s_var = 0.1, std::string opt = "")
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
    void XDirect::DefaultTranspositions()
    {
        transposition->Clear();
        transposition_inc->Clear();
        transposition->UpdatePair(0, 0.0);
        transposition_inc->UpdatePair(0, 0.0);
    };
    void XDirect::AddTransposition(double n)
    {
        int i = transposition->size();
        transposition->NewPair(i, n);
    };
    template <typename... A>
    void XDirect::SetTranspositions(A... n)
    {
        transposition->Clear();
        ((AddTransposition(n)), ...);
    };
    template <typename... A>
    void XDirect::AddTranspositions(A... n)
    {
        ((AddTransposition(n)), ...);
    };
    void XDirect::RandomTranspositionsGauss(int n = 3, double exp_int = 0, double var_int = 7, char slope = 'e', bool root = true, bool integer = false)
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
    void XDirect::RandomTranspositionsChiSquared(int n = 3, bool above = true, int df = 5, double exp_int = 7, double max_int = 12, char slope = 'e', bool root = true, bool integer = false)
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
    void XDirect::AddRandomTranspositionsGauss(int n = 3, double exp_int = 0, double var_int = 7, char slope = 'e', bool integer = false)
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
    void XDirect::AddRandomTranspositionsChiSquared(int n = 3, bool above = true, int df = 5, double exp_int = 7, double max_int = 12, char slope = 'e', bool integer = false)
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
    void XDirect::RandomDirect(int complexity)
    {
        double val = complexity / max_complexity;
        int n_of_notes = floor(val * 13);
        RandomTranspositionsGauss(n_of_notes, 0.0, val*7.0, 'e', true, complexity < max_complexity/2);
        RandomADSR(n_of_notes+1, 2.0, 5.0, 0.7, 250.0, val*5.0);
    };
    void XDirect::Save(std::string file_name = "XDirect.xml")
    {
        std::string extra = moded ? "Mod/" : "/";
        file_name = "/Applications/bitKlavier/preparations/Direct" + extra + file_name;
        XDocument xdoc(this);
        xdoc.Save(file_name);
    };
}