#ifndef XKEYMAP_H
#define XKEYMAP_H

#include "xpreparation.hpp"

namespace bkr
{
    //Class for the Keymap preparation
    class XKeymap : public XPreparation
    {
        protected:
            XElement* midiInputs;
            XElement* midiInputIdentifiers;
            XAttributeMap<int>* keys;
            XAttributeMap<bool>* options;
            XAttributeMap<bool>* t_states;
            XAttributeMap<double>* vel_curve;
            XElementMap<int>* harmonizer;
        public:
            //Constructor
            XKeymap(XAttribute* id, XAttribute* name);
            //Initiate all default options
            void AllDefault();
            //Set all states to default
            void DefaultStates();
            //Set a target state
            void SetTargetState(int key, bool val);
            //Set all options to default
            void DefaultOptions();
            //Set an option
            void SetOptionAttribute(XAttribute* xattr);
            //Set an option
            template <typename T>
            void SetOptionAttribute(std::string key, T value);
            //Fill the keymap
            void Full();
            //Add a key to the keymap
            void AddKey(int k);
            //Add multiple keys to the keymap
            void AddKeys(std::vector<int> k);
            //Add multiple keys to the keymap
            template <typename... A>
            void AddKeys(A... ks);
            //Set the keys of the keymap
            void SetKeys(std::vector<int> k);
            //Set the keys of the keymap
            template <typename... A>
            void SetKeys(A... ks);
            //Clear all keys
            void ClearKeys();
            //Set the default velocity curve
            void DefaultVelocityCurving();
            //Setters
            void SetAsymmetricalWarp(double val);
            void SetSymmetricalWarp(double val);
            void SetScale(double val);
            void SetOffset(double val);
            void InvertVelocity(bool val);
            void SetVelocityCurving(double asymm_wrap, double symm_wrap, double scale, double voffset, bool invert);
            //Set a random velocity curve
            void RandomVelocityCurving(int df = 5, double exp_val = 3, double offset_variance = 0.1);
            //Set a default harmonizer
            void DefaultHarmonizer();
            //Set a random harmonizer, within a certain range
            void RandomRangeHarmonizer(int n = 12, int lowestHarm = 0, int highestHarm = 127, int lowestKey = 0, int highestKey = 127, bool with_root = true);
            //Add a random harmonizer, within a certain range
            void AddRandomRangeHarmonizer(int n = 3, int lowestHarm = 0, int highestHarm = 127, int lowestKey = 0, int highestKey = 127);
            //Set a random harmonizer, sparsed across the keymap
            void RandomSparseHarmonizer(int n = 12, double sparseness = 0.5, int lowestHarm = 0, int highestHarm = 127, int lowestKey = 0, int highestKey = 127, bool with_root = true);
            //Set a random harmonizer
            void RandomHarmonizer(int n = 12, double density = 0.5, int lowestHarm = 0, int highestHarm = 127, std::vector<int> ks = {60}, bool with_root = true);
            //Add a random harmonizer, sparsed across the keymap
            void AddRandomSparseHarmonizer(int n = 3, double sparseness = 0.5, int lowestHarm = 0, int highestHarm = 127, int lowestKey = 0, int highestKey = 127);
            //Set a random Keymap preparation
            void RandomKeymap(int complexity);
            //Modify the preparation (Not allowed)
            void Mod();
            //Save the preparation to bitKlavier
            void Save(std::string file_name = "XKeymap.xml");
    };
}

#endif