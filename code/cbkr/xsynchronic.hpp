#ifndef XSYNCHRONIC_H
#define XSYNCHRONIC_H

#include "xpreparation.hpp"

namespace bkr
{
    //Class for the Synchronic preparation
    class XSynchronic : public XPreparation
    {
        protected:
            XAttributeMap<Params>* param_attrs;
            XElementMap<double>* beats;
            XElementMap<bool>* states;
            XElementMap<double>* ADSRs;
            XElementMap<double>* transp_offsets;
            //Dirty map
            std::map<std::string, int> ds = {
                {"?", 0},
                {"numBeats", 1},
                {"clusterMin", 2},
                {"clusterMax", 3},
                {"clusterCap", 4},
                {"clusterThresh", 5},
                {"mode", 6},
                {"beatsToSkip", 7},
                {"transpOffsets", 8},
                {"accentMultipliers", 9},
                {"lengthMultipliers", 10},
                {"beatMultipliers", 11},
                {"gain", 12},
                {"ADSRs", 13},
                {"onOffMode", 14},
                {"numClusters", 15},
                {"holdMin", 16},
                {"holdMax", 17},
                {"velocityMin", 18},
                {"velocityMax", 19},
                {"midiOutput", 20},
                {"transpUsesTuning", 21},
                {"??", 22},
                {"synchronicUseGlobalSoundSet", 23},
                {"synchronicSoundSet", 24}
            };
        public:
            //Constructor
            XSynchronic(XAttribute* id, XAttribute* name);
            //Set the preparation to its default value
            void AllDefault();
            //Set the default beats
            void DefaultBeats();
            //Set the default parameteres
            void DefaultParamAttributes();
            //Set a parameter
            void SetParamAttribute(XAttribute* xattr);
            //Set a parameter
            template <typename T>
            void SetParamAttribute(std::string key, T value);
            //Set the default ADSR
            void DefaultADSRs();
            //Add a transposition offset
            void AddTransposition(double transp);
            //Add multiple transposition offsets
            void AddTranspositions(std::vector<double> transps);
            //Set the transposition offsets
            template <typename... A>
            void SetTranspositions(A... n);
            //Add multiple transposition offsets
            template <typename... A>
            void AddTranspositions(A... n);
            //Add a beat multiplier
            void AddBeatMultiplier(double beat);
            //Set the beat multipliers
            template <typename... A>
            void SetBeatMultipliers(A... n);
            //Add multiple beat multipliers
            template <typename... A>
            void AddBeatMultipliers(A... n);
            //Add a length multiplier
            void AddLengthMultiplier(double length);
            //Set the length multipliers
            template <typename... A>
            void SetLengthMultipliers(A... n);
            //Add multiple length multipliers
            template <typename... A>
            void AddLengthMultipliers(A... n);
            //Add an accent multiplier
            void AddAccentMultiplier(double accent);
            //Set the accent multipliers
            template <typename... A>
            void SetAccentMultipliers(A... n);
            //Add multiple accent multipliers
            template <typename... A>
            void AddAccentMultipliers(A... n);
            //Add an ADSR envelope
            void AddADSR(double a, double d, double s, double r);
            //Set an ADSR envelope
            void SetADSR(double a, double d, double s, double r);
            //Add a random ADSR envelope
            void AddRandomADSR(int df = 5, double a_exp_val = 2.0, double d_exp_val = 5.0, double s_exp_val = 0.7, double r_exp_val = 250.0, double s_var = 0.1);
            //Add random transposition offsets, following a Gaussian distribution
            void AddRandomTranpositionsGauss(int n = 10, int max_cluster = 1, double exp_int = 0, double var_int = 7, char slope = 'e', bool integer = false);
            //Set random transposition offsets, following a Gaussian distribution
            void RandomTranpositionsGauss(int n = 10, int max_cluster = 1, double exp_int = 0, double var_int = 7, char slope = 'e', bool integer = false);
            //Add random transposition offsets, following a Chi-Squared distribution
            void AddRandomTranpositionsChiSquared(int n = 10, int max_cluster = 1, bool above = true, int df = 5, double exp_int = 7, double max_int = 12, char slope = 'e', bool integer = false);
            //Set random transposition offsets, following a Chi-Squared distribution
            void RandomTranpositionsChiSquared(int n = 10, int max_cluster = 1, bool above = true, int df = 5, double exp_int = 7, double max_int = 12, char slope = 'e', bool integer = false);
            //Add random beat multipliers, following a Gaussian distribution
            void AddRandomBeatsGauss(int n = 10, double exp_int = 1, double var_int = 1, char slope = 'e', bool integer = false);
            //Set random beat multipliers, following a Gaussian distribution
            void RandomBeatsGauss(int n = 10, double exp_int = 1, double var_int = 1, char slope = 'e', bool integer = false);
            //Add random beat multipliers, following a Chi-Squared distribution
            void AddRandomBeatsChiSquared(int n = 10, bool above = true, int df = 5, double exp_int = 1, double max_int = 12, char slope = 'e', bool integer = false);
            //Set random beat multipliers, following a Chi-Squared distribution
            void RandomBeatsChiSquared(int n = 10, bool above = true, int df = 5, double exp_int = 1, double max_int = 12, char slope = 'e', bool integer = false);
            //Add random length multipliers, following a Gaussian distribution
            void AddRandomLengthsGauss(int n = 10, double exp_int = 1, double var_int = 1, char slope = 'e', bool integer = false);
            //Set random length multipliers, following a Gaussian distribution
            void RandomLengthsGauss(int n = 10, double exp_int = 1, double var_int = 1, char slope = 'e', bool integer = false);
            //Add random length multipliers, following a Chi-Squared distribution
            void AddRandomLengthsChiSquared(int n = 10, bool above = true, int df = 5, double exp_int = 1, double max_int = 12, char slope = 'e', bool integer = false);
            //Set random length multipliers, following a Chi-Squared distribution
            void RandomLengthsChiSquared(int n = 10, bool above = true, int df = 5, double exp_int = 1, double max_int = 12, char slope = 'e', bool integer = false);
            //Add random accent multipliers, following a Gaussian distribution
            void AddRandomAccentsGauss(int n = 10, double exp_int = 1, double var_int = 1, char slope = 'e', bool integer = false);
            //Set random accent multipliers, following a Gaussian distribution
            void RandomAccentsGauss(int n = 10, double exp_int = 1, double var_int = 1, char slope = 'e', bool integer = false);
            //Add random length multipliers, following a Chi-Squared distribution
            void AddRandomAccentsChiSquared(int n = 10, bool above = true, int df = 5, double exp_int = 1, double max_int = 12, char slope = 'e', bool integer = false);
            //Set random length multipliers, following a Chi-Squared distribution
            void RandomAccentsChiSquared(int n = 10, bool above = true, int df = 5, double exp_int = 1, double max_int = 12, char slope = 'e', bool integer = false);
            //Change parameters
            void NumPulses(int n, int skip, std::string opt = "");
            void NumLayers(int n, std::string opt = "");
            void Cluster(int min, int max, int cap, double thresh, std::string opt = "");
            void Velocity(int min, int max, std::string opt = "");
            void Hold(int min, int max, std::string opt = "");
            void Modes(bool key_on, int pulse_triggered, std::string opt = "");
            //Set a random Synchronic preparation
            void RandomSynchronic(int complexity);
            //Save the preparation into bitKlavier
            void Save(std::string file_name = "XSynchronic.xml");

            //Add enumeration for BEATS
    };
}

#endif