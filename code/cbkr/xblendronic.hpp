#ifndef XBLENDRONIC_H
#define XBLENDRONIC_H

#include "xpreparation.hpp"

namespace bkr
{
    //Class for the Blendronic preparation
    class XBlendronic : public XPreparation
    {
        protected:
            XAttributeMap<Params>* param_attrs;
            XElementMap<double>* beats;
            XElementMap<bool>* states;
        public:
            //Beat type
            enum Beats
            {
                BEATS,
                DELAYS,
                SMOOTHS,
                COEFFS
            };
            //Constructor
            XBlendronic(XAttribute* id, XAttribute* name);
            //Set the preparation to its default value
            void AllDefault();
            //Set the default parameters
            void DefaultParamAttributes();
            //Set a parameter
            void SetParamAttribute(XAttribute* xattr);
            //Set a parameter
            template <typename T>
            void SetParamAttribute(std::string key, T value);
            //Set the default beats
            void DefaultBeats();
            //Add a beat of type and value
            void Add(Beats beat_type, double val);
            //Set beats of type
            template <typename... A>
            void Set(Beats beat_type, A... vals);
            //Add a beat
            void AddBeat(double beat);
            //Set the beats
            template <typename... A>
            void SetBeats(A... beat);
            //Add multiple beats
            template <typename... A>
            void AddBeats(A... beat);
            //Add a delay length
            void AddDelayLength(double delay);
            //Set the delay lengths
            template <typename... A>
            void SetDelayLengths(A... delays);
            //Add multiple the delay lengths
            template <typename... A>
            void AddDelayLengths(A... delays);
            //Add a smooth length
            void AddSmoothLength(double smooth);
            //Set the smooth lengths
            template <typename... A>
            void SetSmoothLengths(A... smooths);
            //Add multiple the smooth lengths
            template <typename... A>
            void AddSmoothLengths(A... smooths);
            //Add a feedback coefficient
            void AddFeedbackCoefficient(double coeff);
            //Set the feedback coefficients
            template <typename... A>
            void SetFeedbackCoefficients(A... coeffs);
            //Add multiple feedback coefficients
            template <typename... A>
            void AddFeedbackCoefficients(A... coeffs);
            //Add random beats of type, following a Chi-Squared distribution
            void AddRandomBeatsChiSquared(Beats beat_type, int n, int df, double exp_val, double min_val, double max_val, double curve, char slope);
            //Set random beats of type, following a Chi-Squared distribution
            void RandomBeatsChiSquared(Beats beat_type, int n, int df, double exp_val, double min_val, double max_val, double curve, char slope);
            //Set a random Blendronic preparation
            void RandomBlendronic(int complexity);
            //Save the preparation into bitKlaiver
            void Save(std::string file_name);
    };
}

#endif