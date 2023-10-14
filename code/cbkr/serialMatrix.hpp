#ifndef SERIALMATRIX_H
#define SERIALMATRIX_H

#include "qsynth.hpp"
#include <tuple>
#ifndef breve
#define breve 8.0;
#define semibreve 4.0;
#define minim 2.0;
#define crotchet 1.0;
#define quaver 0.5;
#define semiquaver 0.25;
#define demisemiquaver 0.125;
#define hemidemisemiquaver 0.0625;
#endif //breve

namespace SerialMatrix
{
    //Structure of a Note, with an associated Synth
    typedef struct NOTE
    {
        double frequency;
        double amplitude;
        double tempo;
        QSynth::SynthNote timbre;
        std::tuple<double, double, double> space;
        int sample_offset;
        //Constructors
        NOTE(QSynth::SynthNote sn);
        NOTE(QSynth::SynthNote& sn, double pitch, double amp, double duration, std::tuple<double, double, double> _3d);
    } note;

    //Structure of the value of a note, related to its rhythm, samples per beat and beats per minute
    typedef struct NOTE_VALUE
    {
        double BPM;
        double SPB;
        //Constructor
        NOTE_VALUE(double bpm);
        //Get the duration of the note value
        double duration(double beat_length, double tuple = 1.0);
    } note_value;

    //Class for the creation of melodies
    class Melody
    {
        private:
            std::vector<note*> melody;
            int duration;
            int offset;
            QSynth::SynthNote* main_timbre;
            note_value* BPM;
        public:
            //Constructor
            Melody(QSynth::SynthNote* sn, double bpm);
            //Add a note to the melody
            void AddNote(double pitch, double amp, double beat_length, double tuple = 1.0);
            //Get the buffer of the melody
            short* Buffer();
            //Save the melody as a WAV file
            void ToWAV(const char* file_name = "Melody.wav");
            //Getter
            double GetSampleRate();
            //Convolve and save multiple melodies into a WAV file.
            static void Convolve(std::vector<Melody*> melodies, const char* file_name = "Convolution.wav");
    };

    //Class for a Serial Musical Matrix
    class Matrix
    {
        //Structure of an entry of the matrix
        typedef struct MATRIX_ENTRY
        {
            int i;
            int j;
            int value;
            Matrix* matrix;
            //Constructors
            MATRIX_ENTRY();
            MATRIX_ENTRY(Matrix* mtx, int row, int column, int val);
            //Functions for paths inside the matrix
            MATRIX_ENTRY up(int step);
            MATRIX_ENTRY down(int step);
            MATRIX_ENTRY left(int step);
            MATRIX_ENTRY right(int step);
            MATRIX_ENTRY next(int step, int direction);
        } MatrixEntry;
        
        private:
            MatrixEntry** matrix;
            int size;
            int wrap;
            std::vector<int> prime;
            std::vector<int> inverted;
            std::vector<int> p_idx;
            std::vector<int> i_idx;
        public:
            //Constructor
            Matrix(std::vector<int> melody);
            //Destructor
            ~Matrix();
            //Getter
            MatrixEntry Entry(int i, int j);
            //Print the matrix to the console
            void printMatrix();
            //Get the primes, inverses and retrograde versions
            std::vector<int> P(int i);
            std::vector<int> I(int i);
            std::vector<int> R(int i);
            std::vector<int> RI(int i);
            //Get a random entry equal to t
            MatrixEntry RandomEntry(int t);
            //Get random straight line, of lenght n, starting in t
            std::vector<int> SectionBegin(int t, int n);
            //Get random straight line, of lenght n, ending in t
            std::vector<int> SectionEnd(int t, int n);
            //Get random spiral, of lenght n, starting in t
            std::vector<int> SpiralOut(int t, int n);
            //Get random spiral, of lenght n, ending in t
            std::vector<int> SpiralIn(int t, int n);
            //Get random section of length n
            std::vector<int> RandomSection(int n);
            //Get a random melody based on the matrix
            //The pitches follow the entries of the matrix
            //The rhythms follow the entries such that 1=breve, 2=semibreve, ...
            //The dynamics follow the entries such that 1=pppp, 2=ppp, 3=pp, ..., 11=fff, 12=ffff
            Melody* RandomMelody(int complexity);
    };

};

#endif