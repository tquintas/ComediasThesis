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
#include "wav.cpp"

template <typename T>
void clog(T val)
{
    std::cout << val << std::endl;
};

std::string documents = std::string(getenv("HOME")) + "/Documents/";

namespace QSynth
{
    const double tunning = 440.0;
    const double max_complexity = 1024.0;
    std::mt19937 rng(std::random_device{}());

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
        static std::string Note(int midi)
        {
            MIDI2NAME m;
            int note = midi % 12;
            int octave = midi / 12 - 1;
            char buffer[16];
            sprintf(buffer, "%s%d", m.m2n[note].c_str(), octave);
            return std::string(buffer);
        }
    } midi2name;
    
    double FrequencyByMidi(int midi)
    {
        return pow(2.0, (midi-69) / 12.0) * tunning;
    };

    int MidiByFrequency(double freq)
    {
        return 12*log2(freq / tunning) + 69;
    }
    
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
        double env(double t) {
            return t < A ? pow(t/A, pow(2, qA)) :
                t < A + D ? 1 - (1 - S)*pow((t-A) / D, pow(2, qD)) :
                t < A + D + lS ? S :
                t < A + D + lS + R ? S*(1 - pow((t - (A + D + lS)) / R, pow(2, qR))) : 0;
        }
    };

    typedef struct ARTICULATION
    {
        Envelope Staccato = {0.008, 2.0, 0.2, -5.0, 0.0, 1.0, 0.001, 0.0};
        Envelope Reverb = {0.02, 2.0, 10.0, -5.0, 0.0, 12.0, 0.001, 0.0};
        Envelope Piano(int key)
        {
            double d = -0.6552 * key + 73.76;
            Envelope piano = {0.01, 1.0, 0.2, 0.0, 1.0, 0.2, d, -2.0};
            return piano;
        };
        Envelope Release = {0.05, 2.0, 0.005, 0.0, 1.0, 0.005, 0.2, 0.0};
    } articulation;

    typedef struct SINE_WAVE
    {
        double period = 1;
        double f(double x)
        {
            return sin(x*2*M_PI/period);
        }
    } sine_wave;

    typedef struct COSINE_WAVE
    {
        double period = 1;
        double f(double x)
        {
            return cos(x*2*M_PI/period);
        }
    } cosine_wave;

    typedef struct SANO_WAVE
    {
        double period = 1;
        double f(double x)
        {
            return pow(-1, floor(2*x/period)) * sqrt(sin(2*(std::fmod(x, (period/2.0)))*M_PI/period));
        }
    } sano_wave;

    typedef struct TAN_WAVE
    {
        double period = 1;
        double f(double x)
        {
            return pow(-1, floor(2*x/period)) * tan(M_PI * (std::fmod(x, (period/2.0)) - (period/4.0)) / period);
        }
    } tan_wave;

    typedef struct CUBIC_WAVE
    {
        double period = 1;
        double f(double x)
        {
            return pow(-1, floor(2*x/period)) * pow(4 * (std::fmod(x, (period/2.0)) - (period/4.0)) / period, 3);
        }
    } cubic_wave;

    typedef struct POWER5_WAVE
    {
        double period = 1;
        double f(double x)
        {
            return pow(-1, floor(2*x/period)) * pow(4 * (std::fmod(x, (period/2.0)) - (period/4.0)) / period, 5);
        }
    } power5_wave;

    typedef struct POWER7_WAVE
    {
        double period = 1;
        double f(double x)
        {
            return pow(-1, floor(2*x/period)) * pow(4 * (std::fmod(x, (period/2.0)) - (period/4.0)) / period, 7);
        }
    } power7_wave;

    typedef struct SAW_WAVE
    {
        double period = 1;
        double f(double x)
        {
            return 2 * (x/period - floor(x/period)) - 1;
        }
    } saw_wave;

    typedef struct TRIANGLE_WAVE
    {
        double period = 1;
        double f(double x)
        {
            return pow(-1, floor(2*x/period)) * (2 * (2*x/period - floor(2*x/period)) - 1);
        }
    } tri_wave;

    typedef struct SQUARE_WAVE
    {
        double period = 1;
        double f(double x)
        {
            return pow(-1, floor(2*x/period));
        }
    } sqr_wave;

    typedef struct NOISE_WAVE
    {
        double period = 1;
        std::uniform_real_distribution<double> uni{-1, 1};
        double f(double x)
        {
            return uni(rng);
        }
    } noise_wave;

    union Waves
    {
        enum WAVE {SIN, COS, SAN, TAN, CUB, PW5, PW7, SAW, TRI, SQR, NSE} type;
        sine_wave sw;
        cosine_wave csw;
        sano_wave sanw;
        tan_wave tw;
        cubic_wave cw;
        power5_wave p5w;
        power7_wave p7w;
        saw_wave saw;
        tri_wave tri;
        sqr_wave sqr;
        noise_wave noise;
        Waves()
        {
            std::uniform_int_distribution<int> uni(0, 10);
            int i = uni(rng);
            sine_wave w_sine;
            cosine_wave w_cosine;
            sano_wave w_sano;
            tan_wave w_tan;
            cubic_wave w_cubic;
            power5_wave w_power5;
            power7_wave w_power7;
            saw_wave w_saw;
            tri_wave w_tri;
            sqr_wave w_sqr;
            noise_wave w_noise;
            switch (i) {
                case 0:
                    sw = w_sine;
                    type = SIN;
                    break;
                case 1:
                    csw = w_cosine;
                    type = COS;
                    break;
                case 2:
                    sanw = w_sano;
                    type = SAN;
                    break;
                case 3:
                    tw = w_tan;
                    type = TAN;
                    break;
                case 4:
                    cw = w_cubic;
                    type = CUB;
                    break;
                case 5:
                    p5w = w_power5;
                    type = PW5;
                    break;
                case 6:
                    p7w = w_power7;
                    type = PW7;
                    break;
                case 7:
                    saw = w_saw;
                    type = SAW;
                    break;
                case 8:
                    tri = w_tri;
                    type = TRI;
                    break;
                case 9:
                    sqr = w_sqr;
                    type = SQR;
                    break;
                case 10:
                    noise = w_noise;
                    type = NSE;
                    break;
            }
        };
        Waves(sine_wave val) : sw(val) { type = SIN; };
        Waves(cosine_wave val) : csw(val) { type = COS; };
        Waves(sano_wave val) : sanw(val) { type = SAN; };
        Waves(tan_wave val) : tw(val) { type = TAN; };
        Waves(cubic_wave val) : cw(val) { type = CUB; };
        Waves(power5_wave val) : p5w(val) { type = PW5; };
        Waves(power7_wave val) : p7w(val) { type = PW7; };
        Waves(saw_wave val) : saw(val) { type = SAW; };
        Waves(tri_wave val) : tri(val) { type = TRI; };
        Waves(sqr_wave val) : sqr(val) { type = SQR; };
        Waves(noise_wave val) : noise(val) { type = NSE; };
        double f(double x)
        {
            double val;
            switch (type)
            {
                case SIN:
                    val = sw.f(x);
                    break;
                case COS:
                    val = csw.f(x);
                    break;
                case SAN:
                    val = sanw.f(x);
                    break;
                case TAN:
                    val = tw.f(x);
                    break;
                case CUB:
                    val = cw.f(x);
                    break;
                case PW5:
                    val = p5w.f(x);
                    break;
                case PW7:
                    val = p7w.f(x);
                    break;
                case SAW:
                    val = saw.f(x);
                    break;
                case TRI:
                    val = tri.f(x);
                    break;
                case SQR:
                    val = sqr.f(x);
                    break;
                case NSE:
                    val = noise.f(x);
                    break;
            };
            return val;
        };
    };

    template <typename T>
    class LFO
    {
        private:
            Waves* wave_form;
            double freq;
            double amp;
        public:
            LFO(double frequency, double amplitude) :
                freq(frequency), amp(amplitude)
            {
                T wave;
                wave_form = new Waves(wave);
            }
            LFO(double frequency, double amplitude, Waves* wave) :
                freq(frequency), amp(amplitude)
            {
                wave_form = wave;
            }
            double operator()(double x)
            {
                return (amp * wave_form->f(x*freq));
            }
            LFO<Waves>* ConvertToUnion()
            {
                return new LFO<Waves>(freq, amp, wave_form);
            }
            void ChangeParams(double frequency, double amplitude)
            {
                freq = frequency;
                amp = amplitude;
            }
            double GetFrequency()
            {
                return freq;
            }
            double GetAmplitude()
            {
                return amp;
            }
            static LFO<Waves>* RandomLFO(int complexity)
            {
                double val = complexity / max_complexity;
                Waves* w = new Waves();
                double miuf = val * 5;
                double miua = val * 2;
                std::normal_distribution<double> freq(miuf, val);
                std::normal_distribution<double> amp(miua, val);
                return new LFO<Waves>(freq(rng), amp(rng), w);
            }
            template <typename W> static LFO<Waves>* RandomLFO(int complexity, W wave)
            {
                double val = complexity / max_complexity;
                Waves* w = new Waves(wave);
                double miuf = val * 5;
                double miua = val * 2;
                std::normal_distribution<double> freq(miuf, val);
                std::normal_distribution<double> amp(miua, val);
                return new LFO<Waves>(freq(rng), amp(rng), w);
            }
    };

    class Bell
    {
        private:
            double A;
            double B;
            double C;
            LFO<Waves>* LFO_a;
            LFO<Waves>* LFO_b;
            LFO<Waves>* LFO_c;
            void AssertVariables()
            {
                A > 0 || (A = __FLT_MIN__);
                B >= 0 || (B = 0);
            }
            void AssertWobbleVariables(double& a, double& b)
            {
                a > 0 || (a = __FLT_MIN__);
                b >= 0 || (b = 0);
            }
        public:
            Bell(double a, double b, double c) :
                A(a), B(b), C(c) { DefaultLFOs(); AssertVariables(); };
            double operator()(double x)
            {
                double a = A + (*LFO_a)(x);
                double b = B + (*LFO_b)(x);
                double c = C + (*LFO_c)(x);
                AssertWobbleVariables(a, b);
                double e1 = pow(x - c, 2) / (a * b);
                return log(a) * exp(-e1);
            };
            void DefaultLFOs()
            {
                LFO_a = LFO<sine_wave>(1.0, 0.02).ConvertToUnion();
                LFO_b = LFO<sine_wave>(1.0, 0.02).ConvertToUnion();
                LFO_c = LFO<sine_wave>(1.0, 0.02).ConvertToUnion();
            }
            template <typename Wave> void SetLFO_A(LFO<Wave>* lfo)
            {
                LFO_a = lfo->ConvertToUnion();
            }
            template <typename Wave> void SetLFO_B(LFO<Wave>* lfo)
            {
                LFO_b = lfo->ConvertToUnion();
            }
            template <typename Wave> void SetLFO_C(LFO<Wave>* lfo)
            {
                LFO_c = lfo->ConvertToUnion();
            }
            void SetLFOs(LFO<Waves>* lfo_a, LFO<Waves>* lfo_b, LFO<Waves>* lfo_c)
            {
                LFO_a = lfo_a;
                LFO_b = lfo_b;
                LFO_c = lfo_c;
            }
            static Bell* RandomBell(int complexity)
            {
                double val = complexity / max_complexity;
                double a = val * 1.7 + 1;
                double b = val * 10;
                int df = floor(val * 2.0);
                std::chi_squared_distribution<double> chi(df);
                double c = chi(rng);
                Bell* bell = new Bell(a, b, c);
                bell->SetLFOs(LFO<Waves>::RandomLFO(complexity), LFO<Waves>::RandomLFO(complexity), LFO<Waves>::RandomLFO(complexity));
                return bell;
            }
            template <typename T> static Bell* RandomBell(int complexity, T wave)
            {
                double val = complexity / max_complexity;
                double a = val * 1.7 + 1;
                double b = val * 10;
                int df = floor(val * 2.0);
                std::chi_squared_distribution<double> chi(df);
                double c = chi(rng);
                Bell* bell = new Bell(a, b, c);
                bell->SetLFOs(LFO<Waves>::RandomLFO(complexity, wave), LFO<Waves>::RandomLFO(complexity, wave), LFO<Waves>::RandomLFO(complexity, wave));
                return bell;
            }
    };

    class HarmMapping : public std::vector<Bell*>
    {
        public:
            double operator()(double x)
            {
                double base = exp(-pow(x-1, 2)/2.0);
                std::vector<double> vec(this->size());
                std::transform(this->begin(), this->end(), vec.begin(), [x](Bell* b) { return (*b)(x); });
                double sum = std::accumulate(vec.begin(), vec.end(), base);
                return sum / (size() + 1);
            }
            static HarmMapping* RandomHarmMapping(int complexity)
            {
                double val = complexity / max_complexity;
                int n = floor(val * 10) + 1;
                HarmMapping* hm = new HarmMapping();
                for (int _ = 0; _ < n; _++)
                {
                    hm->push_back(Bell::RandomBell(complexity));
                };
                return hm;
            }
            template <typename T> static HarmMapping* RandomHarmMapping(int complexity, T wave)
            {
                double val = complexity / max_complexity;
                int n = floor(val * 10) + 1;
                HarmMapping* hm = new HarmMapping();
                for (int _ = 0; _ < n; _++)
                {
                    hm->push_back(Bell::RandomBell(complexity, wave));
                };
                return hm;
            }
    };

    template <typename T>
    class FSeries
    {
        private:
            int N;
            HarmMapping* a_n;
            Waves* wave_form;
            double freq_ratio;
            double amp;
        public:
            FSeries(double pitch_ratio, HarmMapping* an, T* wave, int n, double amplitude) : freq_ratio(pitch_ratio), N(n), amp(amplitude)
            {
                a_n = an;
                wave_form = new Waves(*wave);
            };
            FSeries(double pitch_ratio, HarmMapping* an, T* wave) : freq_ratio(pitch_ratio), N(50), amp(1.0)
            {
                a_n = an;
                wave_form = new Waves(*wave);
            };
            double operator()(double x)
            {
                double sum = 0.0;
                for (int i = 1; i <= N; ++i)
                {
                    double damp = 1 - (1 - amp) * i/N;
                    sum += damp * (*a_n)(i) * wave_form->f(i*x*freq_ratio);
                }
                return sum;
            }
            Waves* GetWaveForm()
            {
                return wave_form;
            }
            FSeries<Waves>* ConvertToUnion()
            {
                return new FSeries<Waves>(freq_ratio, a_n, wave_form, N, amp);
            }
            void SetAmp(double val)
            {
                amp = val;
            }
            static FSeries<Waves>* RandomFSeries(int complexity)
            {
                double val = complexity / max_complexity;
                int n = floor(val * 10) + 10;
                Waves* w = new Waves();
                std::uniform_real_distribution<double> u(0, 1);
                double r = u(rng);
                double pitch;
                if (r <= 0.5)
                {
                    double val2 = 1.0/(complexity+1);
                    pitch = (1 - val2)*(r*2) + val2;
                }
                else
                {
                    pitch = complexity*(r*2 - 1) + 1;
                }
                double amplitude = exp(-pow(10*(pitch-1), 2));
                return new FSeries<Waves>(pitch, HarmMapping::RandomHarmMapping(complexity), w, n, amplitude);
            };
            template <typename W> static FSeries<Waves>* RandomFSeries(int complexity, W wave)
            {
                double val = complexity / max_complexity;
                int n = floor(val * 10) + 10;
                Waves* w = new Waves(wave);
                std::uniform_real_distribution<double> u(0, 1);
                double r = u(rng);
                double pitch;
                if (r <= 0.5)
                {
                    double val2 = 1.0/(complexity+1);
                    pitch = (1 - val2)*(r*2) + val2;
                }
                else
                {
                    pitch = complexity*(r*2 - 1) + 1;
                }
                double amplitude = exp(-pow(10*(pitch-1), 2));
                return new FSeries<Waves>(pitch, HarmMapping::RandomHarmMapping(complexity, wave), w, n, amplitude);
            };
    };

    template<typename T>
    class FSeriesVector : public std::vector<FSeries<T>*>
    {
        public:
            double operator()(double x, double amp)
            {
                double s = 0.0;
                for (auto w : *this)
                {
                    w->SetAmp(amp);
                    s += (*w)(x);
                }
                return s;
            } 
    };

    class SynthNote
    {
        private:
            double sample_rate = 44100.0;
            double amp;
            double dur;
            double freq;
            FSeriesVector<Waves> waves;
            Envelope ADSR;
        public:
            SynthNote() : 
                dur(1.0), amp(.8), freq(100.0)
            {
                SetADSR(0.003, 0, 0.005, 0, 0.875, (dur - 0.008), 0.25, 0);
            };
            template <typename T> void AddWave(FSeries<T>* wave)
            {
                waves.push_back(wave->ConvertToUnion());
            }
            void SetAttack(double val)
            {
                ADSR.A = val;
            }
            void SetQAttack(double val)
            {
                ADSR.qA = val;
            }
            void SetDecay(double val)
            {
                ADSR.D = val;
            }
            void SetQDecay(double val)
            {
                ADSR.qD = val;
            }
            void SetSustain(double val)
            {
                ADSR.S = val;
            }
            void SetLSustain(double val)
            {
                ADSR.lS = val;
            }
            void SetRelease(double val)
            {
                ADSR.R = val;
            }
            void SetQRelease(double val)
            {
                ADSR.qR = val;
            }
            void SetADSR(double atk, double qatk, double dc, double qdc, double sus, double lsus, double rel, double qrel)
            {
                ADSR.A = atk;
                ADSR.qA = qatk;
                ADSR.D = dc;
                ADSR.qD = qdc;
                ADSR.S = sus;
                ADSR.lS = lsus;
                ADSR.R = rel;
                ADSR.qR = qrel;
                dur = atk + dc + lsus;
            }
            void NoADSR()
            {
                ADSR.A = 0.001;
                ADSR.qA = 0.0;
                ADSR.D = 0.001;
                ADSR.qD = 0.0;
                ADSR.S = 1.0;
                ADSR.lS = dur-0.002;
                ADSR.R = 0.001;
                ADSR.qR = 0.0;
            }
            void SetArticulation(Envelope art)
            {
                ADSR = art;
                dur = art.lS + art.A + art.D;
            }
            void SetDuration(double val)
            {
                dur = val;
                ADSR.lS = val - ADSR.A - ADSR.D;
            }
            void SetPitch(double val)
            {
                freq = val;
            }
            void SetAmplitude(double val)
            {
                amp = val;
            }
            double GetDuration()
            {
                return dur;
            }
            double GetPitch()
            {
                return freq;
            }
            double GetAmplitude()
            {
                return amp;
            }
            int GetShortNumberOfSamples()
            {
                return static_cast<int>(dur * sample_rate);
            }
            int GetNumberOfSamples()
            {
                return static_cast<int>((dur+ADSR.R) * sample_rate);
            }
            double GetSampleRate()
            {
                return sample_rate;
            }
            double operator()(int sample)
            {
                double t = sample / sample_rate;
                return ADSR.env(t) * waves(t*freq, amp);
            }
            short* Play(double note, double velocity)
            {
                amp = velocity / 127.0;
                freq = FrequencyByMidi(note);
                return Buffer();
            }
            short* Buffer()
            {
                int nSamples = static_cast<int>((dur+ADSR.R) * sample_rate);
                float* buff = new float[nSamples];
                short* buff_16 = new short[nSamples];
                float maxabs = 0.0;
                int perc = 0;
                for (int i = 0; i < nSamples; ++i)
                {
                    float sample = (*this)(i);
                    if (std::abs(sample) > maxabs)
                    {
                        maxabs = std::abs(sample);
                    }
                    ((float*)buff)[i] = sample;
                    int perc2 = 100*(i+1) / nSamples;
                    if (perc2 != perc)
                    {
                        perc = perc2;
                        char buffer[6];
                        sprintf(buffer, "%3d%%", perc);
                        clog(std::string(buffer));
                    }
                }
                for (int i = 0; i < nSamples; ++i)
                {
                    if (maxabs > 1) { buff[i] /= maxabs; };
                    buff[i] *= amp;
                    ((short*)buff_16)[i] = buff[i] * INT16_MAX;
                }
                return buff_16;
            }
            double* DoubleBuffer()
            {
                int nSamples = static_cast<int>((dur+ADSR.R) * sample_rate);
                double* buff = new double[nSamples];
                double maxabs = 0.0;
                int perc = 0;
                for (int i = 0; i < nSamples; ++i)
                {
                    double sample = (*this)(i);
                    if (std::abs(sample) > maxabs)
                    {
                        maxabs = std::abs(sample);
                    }
                    ((double*)buff)[i] = sample;
                    int perc2 = 100*(i+1) / nSamples;
                    if (perc2 != perc)
                    {
                        perc = perc2;
                        char buffer[6];
                        sprintf(buffer, "%3d%%", perc);
                        clog(std::string(buffer));
                    }
                }
                for (int i = 0; i < nSamples; ++i)
                {
                    if (maxabs > 1) { buff[i] /= maxabs; };
                    buff[i] *= amp;
                }
                return buff;
            }
            void ToWAV(const char* file_name = "SynthNote.wav")
            {
                short* buff = Buffer();
                int nSamples = static_cast<int>((dur+ADSR.R) * sample_rate);
                WAV::wave_file wav(buff, nSamples);
                wav.Save(file_name, sample_rate);
            }
            void AddRandomWave(int complexity)
            {
                AddWave(FSeries<Waves>::RandomFSeries(complexity));
            }
            template <typename T> void AddRandomWave(int complexity, T wave)
            {
                AddWave(FSeries<Waves>::RandomFSeries(complexity, wave));
            }
            void AddRandomWaves(int complexity)
            {
                double val = complexity / max_complexity;
                int n = floor(val * 10) + 1;
                for (int _ = 0; _ < n; _ ++)
                {
                    AddWave(FSeries<Waves>::RandomFSeries(complexity));
                }
            }
            template <typename T> void AddRandomWaves(int complexity, T wave)
            {
                double val = complexity / max_complexity;
                int n = floor(val * 10) + 1;
                for (int _ = 0; _ < n; _ ++)
                {
                    AddWave(FSeries<Waves>::RandomFSeries(complexity, wave));
                }
            }
    };

    class XSynth : public std::vector<std::tuple<std::string, short*, int>>
    {
        private:
            SynthNote* sn;
            SynthNote* harm_sn;
            SynthNote* rel_sn;
            std::vector<int> midinotes;
        public:
            XSynth(SynthNote* synth_note, std::vector<int> notes, std::vector<int> vels = {1,2,3,4,5,6,7,8}, std::vector<int> rels = {1}) :
                midinotes(notes)
            {
                sn = synth_note;
                harm_sn = nullptr;
                rel_sn = nullptr;
                CreateMap(vels, rels);
            }
            XSynth(SynthNote* synth_note, SynthNote* harm_note, std::vector<int> notes, std::vector<int> vels = {1,2,3,4,5,6,7,8}, std::vector<int> rels = {1}) :
                midinotes(notes)
            {
                sn = synth_note;
                harm_sn = harm_note;
                rel_sn = nullptr;
                CreateMap(vels, rels);
            }
            XSynth(SynthNote* synth_note, SynthNote* harm_note, SynthNote* rel_note, std::vector<int> notes, std::vector<int> vels = {1,2,3,4,5,6,7,8}, std::vector<int> rels = {1}) :
                midinotes(notes)
            {
                sn = synth_note;
                harm_sn = harm_note;
                rel_sn = rel_note;
                CreateMap(vels, rels);
            }
            void CreateMap(std::vector<int> vels = {1,2,3,4,5,6,7,8}, std::vector<int> rels = {1})
            {
                this->clear();
                dynamics d;
                articulation art;
                std::unordered_map<int, int> amps = {
                    {1, d.ppp_vel},
                    {2, d.pp_vel},
                    {3, d.p_vel},
                    {4, d.mp_vel},
                    {5, d.mf_vel},
                    {6, d.f_vel},
                    {7, d.ff_vel},
                    {8, d.fff_vel},
                };
                if (harm_sn != nullptr) harm_sn->SetArticulation(art.Release);
                if (rel_sn != nullptr) 
                {
                    rel_sn->SetArticulation(art.Staccato);
                    std::vector<int> v;
                    double step = 128.0 / (rels.size() + 1);
                    for (double j = step; j < 128.0; j += step)
                    {
                        v.push_back(floor(j));
                    }
                    for (int i = 0; i < rels.size(); ++i)
                    {
                        std::string rel = "rel" + std::to_string(rels[i]);
                        push_back(std::tuple<std::string, short*, int>( rel, rel_sn->Play(v[i], 60), rel_sn->GetNumberOfSamples() ));
                    }
                }
                for (int i : midinotes)
                {
                    sn->SetArticulation(art.Piano(i));
                    std::string note = midi2name::Note(i);
                    for (const auto& pair : amps)
                    {
                        if (vels.end() != std::find(vels.begin(), vels.end(), pair.first))
                        {
                            std::string key = note + "v" + std::to_string(pair.first);
                            std::string harm = "harm" + key;
                            push_back(std::tuple<std::string, short*, int>( key, sn->Play(i, pair.second), sn->GetNumberOfSamples() ));
                            if (harm_sn != nullptr) push_back(std::tuple<std::string, short*, int>( harm, harm_sn->Play(i, floor(pair.second / 2)), harm_sn->GetNumberOfSamples() ));
                        }
                    }
                }
            }
            void SaveSamplesToBitKlavier(std::string sample_name = "XSynth", bool override = true)
            {
                double sr = sn->GetSampleRate();
                std::string folder = documents + "bitSamples/" + sample_name;
                std::string folder2;
                if (override)
                {
                    mkdir(folder.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
                }
                else
                {
                    int counter = 0;
                    do
                    {
                        counter++;
                        std::string folder2 = folder + std::to_string(counter);
                    }
                    while (mkdir(folder2.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1);
                    folder = folder2;
                }
                std::vector<const char*> paths;
                for (const auto& entry : std::filesystem::directory_iterator(folder))
                {
                    if (std::filesystem::is_regular_file(entry))
                    {
                        paths.push_back(entry.path().c_str());
                    }
                }
                for (auto it = begin(); it != end(); ++it)
                {
                    WAV::wave_file wav(std::get<1>(*it), std::get<2>(*it));
                    const char* file = (folder+"/"+std::get<0>(*it)+".wav").c_str();
                    if (override && std::find(paths.begin(), paths.end(), file) != paths.end()) std::filesystem::remove(std::filesystem::path(file));
                    wav.Save(file, sr);
                }
            }
            //complete this, saving stuff to bitklavier
            //create articulation
            //hammer and resonance wavs too
            //by complexity
    };
}