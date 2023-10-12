#ifndef QSYNTH_H
#define QSYNTH_H

#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <functional>
#include <cmath>
#include <vector>
#include <numeric>
#include <random>
#include <unordered_map>
#include <map>
#include <filesystem>
#include <sys/stat.h>
#include <sys/types.h>
#include "wav.hpp"

namespace QSynth
{
    const double tunning = 440.0;
    const double max_complexity = 1024.0;
    std::mt19937 rng(std::random_device{}());

    //Structure of most used dynamics
    typedef struct DYNAMICS
    {
        double pppp = 1/12.0;
        int pppp_vel = static_cast<int>(1/12.0 * 127.0);
        double ppp = 2/12.0;
        int ppp_vel = static_cast<int>(2/12.0 * 127.0);
        double pp = 3/12.0;
        int pp_vel = static_cast<int>(3/12.0 * 127.0);
        double piu_p = 4/12.0;
        int piu_p_vel = static_cast<int>(4/12.0 * 127.0);
        double p = 5/12.0;
        int p_vel = static_cast<int>(5/12.0 * 127.0);
        double mp = 6/12.0;
        int mp_vel = static_cast<int>(6/12.0 * 127.0);
        double mf = 7/12.0;
        int mf_vel = static_cast<int>(7/12.0 * 127.0);
        double f = 8/12.0;
        int f_vel = static_cast<int>(8/12.0 * 127.0);
        double piu_f = 9/12.0;
        int piu_f_vel = static_cast<int>(9/12.0 * 127.0);
        double ff = 10/12.0;
        int ff_vel = static_cast<int>(10/12.0 * 127.0);
        double fff = 11/12.0;
        int fff_vel = static_cast<int>(11/12.0 * 127.0);
        double ffff = 1.0;
        int ffff_vel = 127;
    } dynamics;

    typedef struct MIDI2NAME
    {
        std::map<int, std::string> m2n = {
            {0, "C"},
            {1, "C#"},
            {2, "D"},
            {3, "Eb"},
            {4, "E"},
            {5, "F"},
            {6, "F#"},
            {7, "G"},
            {8, "Ab"},
            {9, "A"},
            {10, "Bb"},
            {11, "B"}
        };
        //Get note name from midi value
        static std::string Note(int midi);
    } midi2name;
    
    //Get frequency from midi value
    double FrequencyByMidi(int midi);

    //Get midi note from frequency value
    int MidiByFrequency(double freq);
    
    //Structure of an Envelope
    struct Envelope
    {
        double A;
        double qA;
        double D;
        double qD;
        double S;
        double lS;
        double R;
        double qR;
        //Get envelope value at the point t
        double env(double t);
    };

    //Structure of most used articulations
    typedef struct ARTICULATION
    {
        Envelope Staccato = {0.008, 2.0, 0.2, -5.0, 0.0, 1.0, 0.001, 0.0};
        Envelope Reverb = {0.02, 2.0, 10.0, -5.0, 0.0, 12.0, 0.001, 0.0};
        //Get the right envelope of a piano, given the midi key
        Envelope Piano(int key);
        Envelope Release = {0.05, 2.0, 0.005, 0.0, 1.0, 0.005, 0.2, 0.0};
    } articulation;

    //Main class for all waves
    class Waves
    {
        public:
            double period = 1;
            //Amplitude value at the point x
            virtual double f(double x);
            //Get an random wave profile
            static Waves* RandomWave();
    };

    class sine_wave : public Waves
    {
        double f(double x) override;
    };

    class cosine_wave : public Waves
    {
        double f(double x) override;
    };

    class sano_wave : public Waves
    {
        double f(double x) override;
    };

    class tan_wave : public Waves
    {
        double f(double x) override;
    };

    class cubic_wave : public Waves
    {
        double f(double x) override;
    };

    class power5_wave : public Waves
    {
        double f(double x) override;
    };

    class power7_wave : public Waves
    {
        double f(double x) override;
    };

    class saw_wave : public Waves
    {
        double f(double x) override;
    };

    class tri_wave : public Waves
    {
        double f(double x) override;
    };

    class sqr_wave : public Waves
    {
        double f(double x) override;
    };

    class noise_wave : public Waves
    {
        std::uniform_real_distribution<double> uni{-1, 1};
        double f(double x) override;
    };

    //Class for a LFO, with a wave profile, a frequency and an amplitude
    class LFO
    {
        private:
            Waves* wave_form;
            double freq;
            double amp;
        public:
            //Constructors (sine wave for default)
            LFO(double frequency, double amplitude);
            LFO(double frequency, double amplitude, Waves* wave);
            //Get the value of the LFO at the point x
            double operator()(double x);
            //Setter
            void ChangeParams(double frequency, double amplitude);
            //Getters
            double GetFrequency();
            double GetAmplitude();
            //Get random LFOs
            static LFO* RandomLFO(int complexity);
            static LFO* RandomLFO(int complexity, Waves* wave);
    };

    //Class for a Bell function: ln(a) * e^( -(x - c)^2 / (a * b) )
    //Each variable a, b and c have associated LFOs
    //This functions are associated with the amplitude of the harmomic components of a sound
    //a - scale parameter (amplitude of main harmonic)
    //b - shape parameter (density of harmonin content)
    //c - shift parameter (position of the main harmonic)
    class Bell
    {
        private:
            double A;
            double B;
            double C;
            LFO* LFO_a;
            LFO* LFO_b;
            LFO* LFO_c;
            //Check if a > 0 and b > 0;
            void AssertVariables();
            void AssertWobbleVariables(double& a, double& b);
        public:
            //Constructor (no LFOs)
            Bell(double a, double b, double c);
            //Get the bell function value at the point x
            double operator()(double x);
            //Insert default LFOs
            void DefaultLFOs();
            //Setters
            void SetLFO_A(LFO* lfo);
            void SetLFO_B(LFO* lfo);
            void SetLFO_C(LFO* lfo);
            void SetLFOs(LFO* lfo_a, LFO* lfo_b, LFO* lfo_c);
            //Get random Bell functions
            static Bell* RandomBell(int complexity);
            static Bell* RandomBell(int complexity, Waves* wave);
    };

    //Sequence of all the bell curves that define an harmonic profile
    class HarmMapping : public std::vector<Bell*>
    {
        public:
            //Get the value of the mapping at the point x 
            double operator()(double x);
            //Get random harmonic mappings
            static HarmMapping* RandomHarmMapping(int complexity);
            static HarmMapping* RandomHarmMapping(int complexity, Waves* wave);
    };

    //Class for the short fourier wave series: ∑_i HarmMapping(i) * Waves(i)
    //N is the number of harmonic components
    //freq_ratio is a factor that is multiplied by the frequency, representing the main harmonic of this component of the synth
    //the amplitude excites or damps the harmonic content, regarding how strong it is
    //the shape draws the damping
    class FSeries
    {
        private:
            int N;
            HarmMapping* a_n;
            Waves* wave_form;
            double freq_ratio;
            double amp;
            double shape;
        public:
            //Constructors
            FSeries(double pitch_ratio, HarmMapping* an, Waves* wave, int n, double amplitude, double h_shape);
            FSeries(double pitch_ratio, HarmMapping* an, Waves* wave);
            //Get the value at the point x;
            double operator()(double x);
            //Getters
            Waves* GetWaveForm();
            //Setters
            void SetAmp(double val);
            //Get random Fourier Series;
            static FSeries* RandomFSeries(int complexity);
            static FSeries* RandomFSeries(int complexity, Waves* wave);
    };

    //A vector with all the components of the synth
    //Since FSeries only constitues one type of Wave, with this vector, the synth can have different wave profiles
    class FSeriesVector : public std::vector<FSeries*>
    {
        public:
            //Get the value at the point x;
            double operator()(double x, double amp);
    };

    //Class to create the sound profile of a Synth
    class SynthNote
    {
        private:
            double sample_rate = 44100.0;
            double amp;
            double dur;
            double freq;
            FSeriesVector waves;
            Envelope ADSR;
        public:
            //Constructor
            SynthNote();
            //Add a wave profile to the components of the synth
            void AddWave(FSeries* wave);
            //Setters
            void SetAttack(double val);
            void SetQAttack(double val);
            void SetDecay(double val);
            void SetQDecay(double val);
            void SetSustain(double val);
            void SetLSustain(double val);
            void SetRelease(double val);
            void SetQRelease(double val);
            void SetADSR(double atk, double qatk, double dc, double qdc, double sus, double lsus, double rel, double qrel);
            void NoADSR();
            void SetArticulation(Envelope art);
            void SetDuration(double val);
            void SetPitch(double val);
            void SetAmplitude(double val);
            //Getters
            double GetDuration();
            double GetPitch();
            double GetAmplitude();
            int GetShortNumberOfSamples();
            int GetNumberOfSamples();
            double GetSampleRate();
            //Get the value at a sample
            double operator()(int sample);
            //Get the buffer from a midi note and a velocity
            short* Play(double note, double velocity);
            //Get the buffer
            short* Buffer();
            //Get the buffer but with double precision
            double* DoubleBuffer();
            //Save the synthnote to a WAV file
            void ToWAV(const char* file_name = "SynthNote.wav");
            //Add random waves to the FSeriesVector
            void AddRandomWave(int complexity);
            void AddRandomWave(int complexity, Waves* wave);
            void AddRandomWaves(int complexity);
            void AddRandomWaves(int complexity, Waves* wave);
    };

    //Class for the complete Synth
    //Each element of the vector is a tuplet with the name of the note, the buffer and the number of samples of the note
    //For each Synth is specified the main sound, the resonance synth and the release synth
    class XSynth : public std::vector<std::tuple<std::string, short*, int>>
    {
        private:
            SynthNote* sn;
            SynthNote* harm_sn;
            SynthNote* rel_sn;
            std::vector<int> midinotes;
        public:
            //Constructors
            XSynth(SynthNote* synth_note, std::vector<int> notes, std::vector<int> vels = {1,2,3,4,5,6,7,8}, std::vector<int> rels = {1});
            XSynth(SynthNote* synth_note, SynthNote* harm_note, std::vector<int> notes, std::vector<int> vels = {1,2,3,4,5,6,7,8}, std::vector<int> rels = {1});
            XSynth(SynthNote* synth_note, SynthNote* harm_note, SynthNote* rel_note, std::vector<int> notes, std::vector<int> vels = {1,2,3,4,5,6,7,8}, std::vector<int> rels = {1});
            //Create the notes mapping and the correct buffers
            void CreateMap(std::vector<int> vels = {1,2,3,4,5,6,7,8}, std::vector<int> rels = {1});
            //Save the synth to bitKlavier
            void SaveSamplesToBitKlavier(std::string sample_name = "XSynth", bool override = true);
            //complete this, saving stuff to bitklavier
            //create articulation
            //hammer and resonance wavs too
            //by complexity
    };
}

#endif