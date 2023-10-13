#ifndef XDIRECT_H
#define XDIRECT_H

#include "xpreparation.hpp"

namespace bkr
{
    //Class for the Direct preparation
    class XDirect : public XPreparation
    {
        protected:
            XAttributeMap<double>* transposition;
            XAttributeMap<double>* transposition_inc;
            XAttributeMap<double>* ADSR;
            XAttributeMap<Params>* param_attrs;
            //Dirty map
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
            //Constructor
            XDirect(XAttribute* id, XAttribute* name);
            //Set preparation to its default value
            void AllDefault();
            //Set all parameters to default
            void DefaultParamAttributes();
            //Set a parameter
            void SetParamAttribute(XAttribute* xattr);
            //Set a parameter
            template <typename T>
            void SetParamAttribute(std::string key, T value);
            //Set the default ADSR
            void DefaultADSR();
            //ADSR Setters
            void SetAttack(double a, std::string opt = "");
            void SetDecay(double d, std::string opt = "");
            void SetSustain(double s, std::string opt = "");
            void SetRelease(double r, std::string opt = "");
            void SetADSR(double a, double d, double s, double r, std::string opt = "");
            //Set a random ADSR
            void RandomADSR(int df = 5, double a_exp_val = 2.0, double d_exp_val = 5.0, double s_exp_val = 0.7, double r_exp_val = 250.0, double s_var = 0.1, std::string opt = "");
            //Set the default transpositions
            void DefaultTranspositions();
            //Add a transposition
            void AddTransposition(double n);
            //Set all the transpositions
            template <typename... A>
            void SetTranspositions(A... n);
            //Add multiple transpositions
            template <typename... A>
            void AddTranspositions(A... n);
            //Set random transpositions, following a Gaussian distribution
            void RandomTranspositionsGauss(int n = 3, double exp_int = 0, double var_int = 7, char slope = 'e', bool root = true, bool integer = false);
            //Set random transpositions, following a Chi-Squared distribution
            void RandomTranspositionsChiSquared(int n = 3, bool above = true, int df = 5, double exp_int = 7, double max_int = 12, char slope = 'e', bool root = true, bool integer = false);
            //Add random transpositions, following a Gaussian distribution
            void AddRandomTranspositionsGauss(int n = 3, double exp_int = 0, double var_int = 7, char slope = 'e', bool integer = false);
            //Add random transpositions, following a Chi-Squared distribution
            void AddRandomTranspositionsChiSquared(int n = 3, bool above = true, int df = 5, double exp_int = 7, double max_int = 12, char slope = 'e', bool integer = false);
            //Set a random Direct preparation
            void RandomDirect(int complexity);
            //Save the preparation into bitKlavier
            void Save(std::string file_name = "XDirect.xml");
    };
}

#endif