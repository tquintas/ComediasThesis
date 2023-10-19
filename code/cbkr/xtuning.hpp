#ifndef XTUNING_H
#define XTUNING_H

#include "xpreparation.hpp"

namespace bkr
{
    //Class for the Tuning preparation
    class XTuning : public XPreparation
    {
        protected:
            XAttributeMap<Params>* param_attrs;
            XAttributeMap<double>* custom_scale;
            XAttributeMap<double>* custom_scale_inc;
            XAttributeMap<double>* absolute_offsets;
            XAttributeMap<double>* absolute_offsets_inc;
            XAttributeMap<Params>* spring_param_attrs;
            XAttributeMap<double>* tethers;
            XAttributeMap<double>* springs;
            XAttributeMap<double>* interval_scale;
            XAttributeMap<bool>* spring_mode;
            //Dirty map
            std::map<std::string, int> ds = {
                {"?", 0},
                {"nToneSemitoneWidth", 13},
                
            };
        public:
            //Constructor
            XTuning(XAttribute* id, XAttribute* name);
            //Set the preparation to its default values
            void AllDefault();
            //Set the default parameters;
            void DefaultParamAttributes();
            //Set a parameter
            void SetParamAttribute(XAttribute* xattr);
            //Set a parameter
            template <typename T>
            void SetParamAttribute(std::string key, T value);
            //Set the default spring parameters
            void DefaultSpringParams();
            //Set a spring parameter
            void SetSpringParamAttribute(XAttribute* xattr);
            //Set a spring parameter
            template <typename T>
            void SetSpringParamAttribute(std::string key, T value);
            //Set the default pitch offsets
            void DefaultOffsets();
            //Set the default spring tuning
            void DefaultSpringTuning();
            //Set a custom temperament
            void SetCustomScale(std::vector<double> offs);
            //Set a random custom temperament
            void RandomCustomScale(double mean, double std_dev);
            //Set a custom spring temperament
            void SetCustomSpringScale(std::vector<double> offs);
            //Set a random spring temperament
            void RandomCustomSpringScale(double mean = 0.0, double std_dev = 25.0);
            //Add a key's absolute pitch offset
            void AddAbsoluteOffset(int key, double off);
            //Add multiple keys' absolute pitch offsets
            void AddAbsoluteOffsets(std::vector<std::tuple<int, double>> offs);
            //Set the multiple keys' absolute pitch offsets
            void SetAbsoluteOffsets(std::vector<std::tuple<int, double>> offs);
            //Set random keys' absolute pitch offsets
            void RandomAbsoluteOffsets(int n = 10, double key_mean = 60, double key_stddev = 32, double off_mean = 0.0, double off_stddev = 25.0);
            //Add a key's tether, for its weight in spring tuning
            void AddTether(int key, double val);
            //Add multiple keys' tethers, for their weight in spring tuning
            void AddTethers(std::vector<std::tuple<int, double>> tths);
            //Set the keys' tethers, for their weight in spring tuning
            void SetTethers(std::vector<std::tuple<int, double>> tths);
            //Set random keys' tethers, for their weight in spring tuning
            void RandomTethers(int n = 10, double key_mean = 60, double key_stddev = 32, double tth_mean = 0.5, double tth_stddev = 0.25);
            //Set the interval springs' stiffness, and if each interval is relative to the moving fundamental or to a local fundamental
            //The order is 8P -> 2ªm
            void SetSprings(std::vector<double> sprgs, std::vector<bool> modes);
            //Set random interval springs' stiffness
            void RandomSprings(double mean = 0.5, double std_dev = 0.25);
            //Set a random plain Tuning
            void RandomNormalTuning(int complexity);
            //Set a random Adaptive Tuning
            void RandomAdaptiveTuning(int complexity);
            //Set a random Adaptive Anchored Tuning
            void RandomAdaptiveAnchoredTuning(int complexity);
            //Set a random Spring Tuning
            void RandomSpringTuning(int complexity);
            //Save the preparation into bitKlavier
            void Save(std::string file_name = "XTuning.xml");
    };

}

#endif