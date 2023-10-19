#include "xkeymap.hpp"

namespace bkr
{
    XKeymap::XKeymap(XAttribute* id, XAttribute* name) : XPreparation(id, name, XName::bitKlavierTagNames.Keymap, 5, 0, 0)
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
    void XKeymap::AllDefault()
    {
        Full();
        DefaultStates();
        DefaultOptions();
        DefaultVelocityCurving();
        DefaultHarmonizer();
    };
    void XKeymap::DefaultStates()
    {
        for (int i = 0; i < 22; ++i)
        {
            bool v = (i < 2 || i == 10 || i >= 17);
            t_states->UpdatePair(i, v);
        };
    }
    void XKeymap::SetTargetState(int key, bool val)
    {
        t_states->UpdatePair(key, val);
    }
    void XKeymap::DefaultOptions()
    {
        options->UpdateCustomPair(XAttribute::bitKlavierAttributes.Keymap.HarmonizerPreTranspose<bool>(false));
        options->UpdateCustomPair(XAttribute::bitKlavierAttributes.Keymap.HarmonizerPostTranspose<bool>(false));
        options->UpdateCustomPair(XAttribute::bitKlavierAttributes.Keymap.EndKeystrokes<bool>(false));
        options->UpdateCustomPair(XAttribute::bitKlavierAttributes.Keymap.IgnoreSustain<bool>(false));
        options->UpdateCustomPair(XAttribute::bitKlavierAttributes.Keymap.SustainPedalKeys<bool>(false));
        options->UpdateCustomPair(XAttribute::bitKlavierAttributes.Keymap.ToggleKey<bool>(false));
        options->UpdateCustomPair(XAttribute::bitKlavierAttributes.Keymap.SostenutoMode<bool>(false));
    };
    void XKeymap::SetOptionAttribute(XAttribute* xattr)
    {
        std::string key = xattr->getComparisonString();
        if ((*options)[key])
        {
            options->UpdateCustomPair(xattr);
        }
    }
    template <typename T>
    void XKeymap::SetOptionAttribute(std::string key, T value)
    {
        if ((*options)[key])
        {
            XAttribute* xattr = new XAttribute(key, to_string(value));
            options->UpdateCustomPair(xattr);
        }
    }
    void XKeymap::Full()
    {
        for (int i = 0; i < 128; ++i)
        {
            keys->UpdatePair(i, i);
        };
    };
    void XKeymap::AddKey(int k)
    {
        int c = keys->size();
        keys->NewPair(c, k);
    }
    void XKeymap::AddKeys(std::vector<int> k)
    {
        int c = keys->size();
        for (int i = 0; i < k.size(); i++)
        {
            keys->NewPair(c+i, k[i]);
        }
    }
    template <typename... A>
    void XKeymap::AddKeys(A... ks)
    {
        (AddKey(ks), ...);
    }
    void XKeymap::SetKeys(std::vector<int> k)
    {
        keys->Clear();
        AddKeys(k);
    }
    template <typename... A>
    void XKeymap::SetKeys(A... ks)
    {
        keys->Clear();
        (AddKey(ks), ...);
    }
    void XKeymap::ClearKeys()
    {
        keys->clear();
    };
    void XKeymap::DefaultVelocityCurving()
    {
        vel_curve->UpdateCustomPair(XAttribute::bitKlavierAttributes.Keymap.AsymmetricalWarp<double>(1.0));
        vel_curve->UpdateCustomPair(XAttribute::bitKlavierAttributes.Keymap.SymmetricalWarp<double>(1.0));
        vel_curve->UpdateCustomPair(XAttribute::bitKlavierAttributes.Keymap.Scale<double>(1.0));
        vel_curve->UpdateCustomPair(XAttribute::bitKlavierAttributes.Keymap.Offset<double>(0.0));
        options->UpdateCustomPair(XAttribute::bitKlavierAttributes.Keymap.VelocityInvert<bool>(false));
    };
    void XKeymap::SetAsymmetricalWarp(double val)
    {
        val >= 0.0 || (val = 0.0);
        vel_curve->UpdateCustomPair(XAttribute::bitKlavierAttributes.Keymap.AsymmetricalWarp<double>(val));
    };
    void XKeymap::SetSymmetricalWarp(double val)
    {
        val >= 0.0 || (val = 0.0);
        vel_curve->UpdateCustomPair(XAttribute::bitKlavierAttributes.Keymap.SymmetricalWarp<double>(val));
    };
    void XKeymap::SetScale(double val)
    {
        val >= 0.0 || (val = 0.0);
        vel_curve->UpdateCustomPair(XAttribute::bitKlavierAttributes.Keymap.Scale<double>(val));
    };
    void XKeymap::SetOffset(double val)
    {
        (val >= -1.0 || (val = -1.0)) && (val <= 1.0 || (val = 1.0));
        vel_curve->UpdateCustomPair(XAttribute::bitKlavierAttributes.Keymap.Offset<double>(val));
    };
    void XKeymap::InvertVelocity(bool val)
    {
        options->UpdateCustomPair(XAttribute::bitKlavierAttributes.Keymap.VelocityInvert<bool>(val));
    };
    void XKeymap::SetVelocityCurving(double asymm_wrap, double symm_wrap, double scale, double voffset, bool invert)
    {
        SetAsymmetricalWarp(asymm_wrap);
        SetSymmetricalWarp(symm_wrap);
        SetScale(scale);
        SetOffset(voffset);
        InvertVelocity(invert);
    };
    void XKeymap::RandomVelocityCurving(int df, double exp_val, double offset_variance)
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
    void XKeymap::DefaultHarmonizer()
    {
        harmonizer->ClearAttributes();
        for (int i = 0; i < 128; ++i)
        {
            (*harmonizer)(i)->NewPair(0, i);
        };
    };
    void XKeymap::RandomRangeHarmonizer(int n, int lowestHarm, int highestHarm, int lowestKey, int highestKey, bool with_root)
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
    void XKeymap::AddRandomRangeHarmonizer(int n, int lowestHarm, int highestHarm, int lowestKey, int highestKey)
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
    void XKeymap::RandomSparseHarmonizer(int n, double sparseness, int lowestHarm, int highestHarm, int lowestKey, int highestKey, bool with_root)
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
    void XKeymap::RandomHarmonizer(int n, double density, int lowestHarm, int highestHarm, std::vector<int> ks, bool with_root)
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
    void XKeymap::AddRandomSparseHarmonizer(int n, double sparseness, int lowestHarm, int highestHarm, int lowestKey, int highestKey)
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
    void XKeymap::RandomKeymap(int complexity)
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
    void XKeymap::Mod() {};
    void XKeymap::Save(std::string file_name)
    {
        file_name = "/Applications/bitKlavier/preparations/Keymap" + file_name;
        XDocument xdoc(this);
        xdoc.Save(file_name);
    };
}