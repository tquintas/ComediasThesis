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
            void RandomVelocityCurving(int df, double exp_val, double offset_variance);
            //Set a default harmonizer
            void DefaultHarmonizer();
            //Set a random harmonizer, within a certain range
            void RandomRangeHarmonizer(int n, int lowestHarm, int highestHarm, int lowestKey, int highestKey, bool with_root);
            //Add a random harmonizer, within a certain range
            void AddRandomRangeHarmonizer(int n, int lowestHarm, int highestHarm, int lowestKey, int highestKey);
            //Set a random harmonizer, sparsed across the keymap
            void RandomSparseHarmonizer(int n, double sparseness, int lowestHarm, int highestHarm, int lowestKey, int highestKey, bool with_root);
            //Set a random harmonizer
            void RandomHarmonizer(int n, double density, int lowestHarm, int highestHarm, std::vector<int> ks, bool with_root);
            //Add a random harmonizer, sparsed across the keymap
            void AddRandomSparseHarmonizer(int n, double sparseness, int lowestHarm, int highestHarm, int lowestKey, int highestKey);
            //Set a random Keymap preparation
            void RandomKeymap(int complexity);
            //Modify the preparation (Not allowed)
            void Mod();
            //Save the preparation to bitKlavier
            void Save(std::string file_name);
    };
}

#endif