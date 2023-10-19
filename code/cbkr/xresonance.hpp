#ifndef XRESONANCE_H
#define XRESONANCE_H

#include "xpreparation.hpp"

namespace bkr
{
    //Class for the Resonance preparation
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
            //Constructor
            XResonance(XAttribute* id, XAttribute* name);
            //Set the preparation to its default value
            void AllDefault();
            //Set the default parameters
            void DefaultParamAttributes();
            //Set a parameter
            void SetParamAttribute(XAttribute* xattr);
            //Set a parameter
            template <typename T>
            void SetParamAttribute(std::string key, T value);
            //Set the default ADSR envelope
            void DefaultADSR();
            //ADSR Setters
            void SetAttack(double a, std::string opt = "");
            void SetDecay(double d, std::string opt = "");
            void SetSustain(double s, std::string opt = "");
            void SetRelease(double r, std::string opt = "");
            void SetADSR(double a, double d, double s, double r, std::string opt = "");
            //Set a random ADSR envelope
            void RandomADSR(int df = 5, double a_exp_val = 2.0, double d_exp_val = 5.0, double s_exp_val = 0.7, double r_exp_val = 250.0, double s_var = 0.01, std::string opt = "");
            //Set the default resonances
            void DefaultResonances();
            //Add a resonance, choosing the key, its transposition offset and its gain
            void AddResonance(std::tuple<int, double, double> res);
            //Add multiple resonances, choosing the keys, each transposition offset and each gain
            void AddResonances(std::vector<std::tuple<int, double, double>> res);
            //Set the resonances, choosing the keys, each transposition offset and each gain
            void SetResonances(std::vector<std::tuple<int, double, double>> res);
            //Toggle note held until pressed again
            void HoldNote(int note);
            //Set the fundamental note
            void SetFundamentalKey(int note, std::string opt = "");
            //Set random resonances
            void RandomResonances(int n = 10, double res_var = 1.0, double offset_var = 100.0, double gain_var = 0.1);
            //Set a random Resonance preparation
            void RandomResonance(int complexity);
            //Save the preparation into bitKlaiver
            void Save(std::string file_name = "XResonance.xml");
    };

}

#endif