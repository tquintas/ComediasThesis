#ifndef XNOSTALGIC_H
#define XNOSTALGIC_H

#include "xpreparation.hpp"

namespace bkr
{
    //Class fir the Nostalgic preparation
    class XNostalgic : public XPreparation
    {
        protected:    
            XAttributeMap<double>* transposition;
            XAttributeMap<double>* transposition_inc;
            XAttributeMap<double>* reverseADSR;
            XAttributeMap<double>* undertowADSR;
            XAttributeMap<Params>* param_attrs;
            //Dirty map
            std::map<std::string, int> ds = {
                {"?", 0},
                {"waveDistance", 1},
                {"undertow", 2},
                {"transposition", 3},
                {"gain", 4},
                {"blendronicGain", 5},
                {"lengthMultiplier", 6},
                {"beatsToSkip", 7},
                {"mode", 8},
                {"??", 9},
                {"???", 10},
                {"reverseADSR", 11},
                {"undertowADSR", 12},
                {"holdMin", 13},
                {"holdMax", 14},
                {"clusterMin", 15},
                {"clusterThresh", 16},
                {"keyOnReset", 17},
                {"velocityMin", 18},
                {"velocityMax", 19},
                {"transpUsesTuning", 20},
                {"nostalgicUseGlobalSoundSet", 21},
                {"nostalgicSoundSet", 22}
            };
        public:
            //Constructor
            XNostalgic(XAttribute* id, XAttribute* name);
            //Set the preparation to its default values
            void AllDefault();
            //Set the default parameters
            void DefaultParamAttributes();
            //Set a parameter
            void SetParamAttribute(XAttribute* xattr);
            //Set a parameter
            template <typename T>
            void SetParamAttribute(std::string key, T value);
            //Set the default Reverse ADSR envelope
            void DefaultReverseADSR();
            //Set the default Undertow ADSR envelope
            void DefaultUndertowADSR();
            //ADSR Setters
            void SetReverseAttack(double a, std::string opt = "");
            void SetUndertowAttack(double a, std::string opt = "");
            void SetReverseDecay(double d, std::string opt = "");
            void SetUndertowDecay(double d, std::string opt = "");
            void SetReverseSustain(double s, std::string opt = "");
            void SetUndertowSustain(double s, std::string opt = "");
            void SetReverseRelease(double r, std::string opt = "");
            void SetUndertowRelease(double r, std::string opt = "");
            void SetReverseADSR(double a, double d, double s, double r, std::string opt = "");
            void SetUndertowADSR(double a, double d, double s, double r, std::string opt = "");
            //Set a random Reverse ADSR envelope
            void RandomReverseADSR(int df = 5, double a_exp_val = 2.0, double d_exp_val = 5.0, double s_exp_val = 0.7, double r_exp_val = 250.0, double s_var = 0.1, std::string opt = "");
            //Set a random Undertow ADSR envelope
            void RandomUndertowADSR(int df = 5, double a_exp_val = 2.0, double d_exp_val = 5.0, double s_exp_val = 0.7, double r_exp_val = 250.0, double s_var = 0.1, std::string opt = "");
            //Set the default transpositions
            void DefaultTranspositions();
            //Add a transposition
            void AddTransposition(double n);
            //Set the transpositions
            template <typename... A>
            void SetTranspositions(A... n);
            //Add multiple transpositions
            template <typename... A>
            void AddTranspositions(A... n);
            //Set random transpositions, following a Gaussian distribution
            void RandomTranspositionsGauss(int n = 3, double exp_int = 0, double var_int = 7, char slope = 'e', bool root = true, bool integer = false);
            //Set random transpositions, following a Chi-Squared distribution
            void RandomTranspositionsChiSquared(int n = 3, bool above = true, int df = 5, double exp_int = 7, double max_int = 12, char slope = 'e', bool root = true, bool integer = false);
            //Add multiple random transpositions, following a Gaussian distribution
            void AddRandomTranspositionsGauss(int n = 3, double exp_int = 0, double var_int = 7, char slope = 'e', bool integer = false);
            //Add multiple random transpositions, following a Chi-Squared distribution
            void AddRandomTranspositionsChiSquared(int n = 3, bool above = true, int df = 5, double exp_int = 7, double max_int = 12, char slope = 'e', bool integer = false);
            //Parameter Setters
            void NoteLengthMultiplier(double val, std::string opt = "");
            void WaveDistance(double val, std::string opt = "");
            void RandomWaveDistance(double lambda = 0.01);
            void Undertow(double val, std::string opt = "");
            void RandomUndertow(double lambda = 0.002);
            //Set a random Nostalgic preparation
            void RandomNostalgic(int complexity);
            //Save the preparation into bitKlavier
            void Save(std::string file_name = "XNostalgic.xml");
    };
}

#endif