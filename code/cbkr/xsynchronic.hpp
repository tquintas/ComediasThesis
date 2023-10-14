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
            void AddRandomADSR(int df, double a_exp_val, double d_exp_val, double s_exp_val, double r_exp_val, double s_var);
            //Add random transposition offsets, following a Gaussian distribution
            void AddRandomTranpositionsGauss(int n, int max_cluster, double exp_int, double var_int, char slope, bool integer);
            //Set random transposition offsets, following a Gaussian distribution
            void RandomTranpositionsGauss(int n, int max_cluster, double exp_int, double var_int, char slope, bool integer);
            //Add random transposition offsets, following a Chi-Squared distribution
            void AddRandomTranpositionsChiSquared(int n, int max_cluster, bool above, int df, double exp_int, double max_int, char slope, bool integer);
            //Set random transposition offsets, following a Chi-Squared distribution
            void RandomTranpositionsChiSquared(int n, int max_cluster, bool above, int df, double exp_int, double max_int, char slope, bool integer);
            //Add random beat multipliers, following a Gaussian distribution
            void AddRandomBeatsGauss(int n, double exp_int, double var_int, char slope, bool integer);
            //Set random beat multipliers, following a Gaussian distribution
            void RandomBeatsGauss(int n, double exp_int, double var_int, char slope, bool integer);
            //Add random beat multipliers, following a Chi-Squared distribution
            void AddRandomBeatsChiSquared(int n, bool above, int df, double exp_int, double max_int, char slope, bool integer);
            //Set random beat multipliers, following a Chi-Squared distribution
            void RandomBeatsChiSquared(int n, bool above, int df, double exp_int, double max_int, char slope, bool integer);
            //Add random length multipliers, following a Gaussian distribution
            void AddRandomLengthsGauss(int n, double exp_int, double var_int, char slope, bool integer);
            //Set random length multipliers, following a Gaussian distribution
            void RandomLengthsGauss(int n, double exp_int, double var_int, char slope, bool integer);
            //Add random length multipliers, following a Chi-Squared distribution
            void AddRandomLengthsChiSquared(int n, bool above, int df, double exp_int, double max_int, char slope, bool integer);
            //Set random length multipliers, following a Chi-Squared distribution
            void RandomLengthsChiSquared(int n, bool above, int df, double exp_int, double max_int, char slope, bool integer);
            //Add random accent multipliers, following a Gaussian distribution
            void AddRandomAccentsGauss(int n, double exp_int, double var_int, char slope, bool integer);
            //Set random accent multipliers, following a Gaussian distribution
            void RandomAccentsGauss(int n, double exp_int, double var_int, char slope, bool integer);
            //Add random length multipliers, following a Chi-Squared distribution
            void AddRandomAccentsChiSquared(int n, bool above, int df, double exp_int, double max_int, char slope, bool integer);
            //Set random length multipliers, following a Chi-Squared distribution
            void RandomAccentsChiSquared(int n, bool above, int df, double exp_int, double max_int, char slope, bool integer);
            //Change parameters
            void NumPulses(int n, int skip, std::string opt);
            void NumLayers(int n, std::string opt);
            void Cluster(int min, int max, int cap, double thresh, std::string opt);
            void Velocity(int min, int max, std::string opt);
            void Hold(int min, int max, std::string opt);
            void Modes(bool key_on, int pulse_triggered, std::string opt);
            //Set a random Synchronic preparation
            void RandomSynchronic(int complexity);
            //Save the preparation into bitKlavier
            void Save(std::string file_name);
    };
}

#endif