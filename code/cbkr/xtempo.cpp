#include "xtempo.hpp"

namespace bkr
{
    XTempo::XTempo(XAttribute* id, XAttribute* name) : XPreparation(id, name, XName::bitKlavierTagNames.Tempo, 4, 9, 10)
    {
        XElement* params = new XElement(XName::bitKlavierTagNames.Params, 0);
        appendChild(params);
        param_attrs = new XAttributeMap<Params>(params);
        DefaultParamAttributes();
    }
    void XTempo::DefaultParamAttributes()
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
    void XTempo::SetParamAttribute(XAttribute* xattr)
    {
        std::string key = xattr->getComparisonString();
        if ((*param_attrs)[key])
        {
            param_attrs->UpdateCustomPair(xattr);
            if (ds[key]) GetDirty(ds[key]);
        }
    }
    template <typename T>
    void XTempo::SetParamAttribute(std::string key, T value)
    {
        if ((*param_attrs)[key])
        {
            XAttribute* xattr = new XAttribute(key, to_string(value));
            param_attrs->UpdateCustomPair(xattr);
            if (ds[key]) GetDirty(ds[key]);
        }
    }
    void XTempo::SetTempo(double val, std::string opt = "")
    {
        if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
        param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TempoParams.Tempo(val, opt));
    }
    void XTempo::SetSubdivisions(double val, std::string opt = "")
    {
        if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
        param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TempoParams.Subdivisions(val, opt));
    }
    void XTempo::SetConstantTempo(double tempo, double subdiv, std::string opt = "")
    {
        if (std::find(std::begin(opts), std::end(opts), opt) == std::end(opts)) opt = "";
        param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TempoParams.Tempo(tempo, opt));
        param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TempoParams.Subdivisions(subdiv, opt));
        if (opt == "_inc") return;
        param_attrs->UpdateCustomPair(XAttribute::bitKlavierAttributes.TempoParams.System(0, opt));
    }
    void XTempo::SetAdaptiveTempo(double min, double max, double subdiv, int history = 4, int mode = 0, std::string opt = "")
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
    void XTempo::RandomTempo(int complexity)
    {
        std::exponential_distribution<double> e1(3.0/complexity);
        std::exponential_distribution<double> e2(complexity/max_complexity);
        SetConstantTempo(e1(rng), e2(rng));
    }
    void XTempo::Save(std::string file_name = "XTempo.xml")
    {
        std::string extra = moded ? "Mod/" : "/";
        file_name = "/Applications/bitKlavier/preparations/Tempo" + extra + file_name;
        XDocument xdoc(this);
        xdoc.Save(file_name);
    };
}