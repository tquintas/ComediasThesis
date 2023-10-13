#ifndef XTEMPO_H
#define XTEMPO_H

#include "xpreparation.hpp"

namespace bkr
{
    //Class for the Tempo preparation
    class XTempo : public XPreparation
    {
        protected:
            XAttributeMap<Params>* param_attrs;
            //Dirty map
            std::map<std::string, int> ds = {
                {"?", 0},
                {"tempo", 1},
                {"system", 2},
                {"at1History", 3},
                {"at1Subdivisions", 4},
                {"at1Min", 5},
                {"at1Max", 6},
                {"at1Mode", 7},
                {"subdivisions", 8}
            };
        public:
            //Constructor
            XTempo(XAttribute* id, XAttribute* name);
            //Set the default parameters
            void DefaultParamAttributes();
            //Set a parameter
            void SetParamAttribute(XAttribute* xattr);
            //Set a parameter
            template <typename T>
            void SetParamAttribute(std::string key, T value);
            //Parameter Setters
            void SetTempo(double val, std::string opt = "");
            void SetSubdivisions(double val, std::string opt = "");
            void SetConstantTempo(double tempo, double subdiv, std::string opt = "");
            void SetAdaptiveTempo(double min, double max, double subdiv, int history = 4, int mode = 0, std::string opt = "");
            //Set a random Tempo preparation
            void RandomTempo(int complexity);
            //Save the preparation into bitKlaiver
            void Save(std::string file_name = "XTempo.xml");
    };
}

#endif