#include "qsynth.hpp"

template <typename T>
void clog(T val)
{
    std::cout << val << std::endl;
};
std::string documents = std::string(getenv("HOME")) + "/Documents/";

namespace QSynth
{
    std::string MIDI2NAME::Note(int midi)
    {
        MIDI2NAME m;
        int note = midi % 12;
        int octave = midi / 12 - 1;
        char buffer[16];
        sprintf(buffer, "%s%d", m.m2n[note].c_str(), octave);
        return std::string(buffer);
    }
    
    double FrequencyByMidi(int midi)
    {
        return pow(2.0, (midi-69) / 12.0) * tunning;
    };

    int MidiByFrequency(double freq)
    {
        return 12*log2(freq / tunning) + 69;
    }
    
    double Envelope::env(double t) {
        return t < A ? pow(t/A, pow(2, qA)) :
            t < A + D ? 1 - (1 - S)*pow((t-A) / D, pow(2, qD)) :
            t < A + D + lS ? S :
            t < A + D + lS + R ? S*(1 - pow((t - (A + D + lS)) / R, pow(2, qR))) : 0;
    }

    Envelope ARTICULATION::Piano(int key)
    {
        double d = -0.6552 * key + 73.76;
        Envelope piano = {0.01, 1.0, 0.2, 0.0, 1.0, 0.2, d, -2.0};
        return piano;
    };

    double Waves::f(double x) { return 0; }
    Waves* Waves::RandomWave()
    {
        std::uniform_int_distribution<int> uni(0, 9);
        int i = uni(rng);
        if (i == 0) return new sine_wave();
        else if (i == 1) return new cosine_wave();
        else if (i == 2) return new sano_wave();
        else if (i == 3) return new tan_wave();
        else if (i == 4) return new cubic_wave();
        else if (i == 5) return new power5_wave();
        else if (i == 6) return new power7_wave();
        else if (i == 7) return new saw_wave();
        else if (i == 8) return new tri_wave();
        else if (i == 9) return new sqr_wave();
        else return new noise_wave();
    }

    double sine_wave::f(double x)
    {
        return sin(x*2*M_PI/period);
    }

    double cosine_wave::f(double x)
    {
        return cos(x*2*M_PI/period);
    }

    double sano_wave::f(double x)
    {
        return pow(-1, floor(2*x/period)) * sqrt(sin(2*(std::fmod(x, (period/2.0)))*M_PI/period));
    }

    double tan_wave::f(double x)
    {
        return pow(-1, floor(2*x/period)) * tan(M_PI * (std::fmod(x, (period/2.0)) - (period/4.0)) / period);
    }

    double cubic_wave::f(double x)
    {
        return pow(-1, floor(2*x/period)) * pow(4 * (std::fmod(x, (period/2.0)) - (period/4.0)) / period, 3);
    }

    double power5_wave::f(double x)
    {
        return pow(-1, floor(2*x/period)) * pow(4 * (std::fmod(x, (period/2.0)) - (period/4.0)) / period, 5);
    }

    double power7_wave::f(double x)
    {
        return pow(-1, floor(2*x/period)) * pow(4 * (std::fmod(x, (period/2.0)) - (period/4.0)) / period, 7);
    }

    double saw_wave::f(double x)
    {
        return 2 * (x/period - floor(x/period)) - 1;
    }

    double tri_wave::f(double x)
    {
        return pow(-1, floor(2*x/period)) * (2 * (2*x/period - floor(2*x/period)) - 1);
    }

    double sqr_wave::f(double x)
    {
        return pow(-1, floor(2*x/period));
    }

    double noise_wave::f(double x)
    {
        return uni(rng);
    }

    LFO::LFO(double frequency, double amplitude) :
        freq(frequency), amp(amplitude)
    {
        wave_form = new sine_wave();
    }
    LFO::LFO(double frequency, double amplitude, Waves* wave) :
        freq(frequency), amp(amplitude)
    {
        wave_form = wave;
    }
    double LFO::operator()(double x)
    {
        return (amp * wave_form->f(x*freq));
    }
    void LFO::ChangeParams(double frequency, double amplitude)
    {
        freq = frequency;
        amp = amplitude;
    }
    double LFO::GetFrequency()
    {
        return freq;
    }
    double LFO::GetAmplitude()
    {
        return amp;
    }
    LFO* LFO::RandomLFO(int complexity)
    {
        double val = complexity / max_complexity;
        Waves* wave = Waves::RandomWave();
        double miuf = val * 5;
        double miua = val * 2;
        std::normal_distribution<double> freq(miuf, val);
        std::normal_distribution<double> amp(miua, val);
        return new LFO(freq(rng), amp(rng), wave);
    }
    LFO* LFO::RandomLFO(int complexity, Waves* wave)
    {
        double val = complexity / max_complexity;
        double miuf = val * 5;
        double miua = val * 2;
        std::normal_distribution<double> freq(miuf, val);
        std::normal_distribution<double> amp(miua, val);
        return new LFO(freq(rng), amp(rng), wave);
    }

    void Bell::AssertVariables()
    {
        A > 0 || (A = __FLT_MIN__);
        B >= 0 || (B = 0);
    }
    void Bell::AssertWobbleVariables(double& a, double& b)
    {
        a > 0 || (a = __FLT_MIN__);
        b >= 0 || (b = 0);
    }
    Bell::Bell(double a, double b, double c) :
        A(a), B(b), C(c) { DefaultLFOs(); AssertVariables(); };
    double Bell::operator()(double x)
    {
        double a = A + (*LFO_a)(x);
        double b = B + (*LFO_b)(x);
        double c = C + (*LFO_c)(x);
        AssertWobbleVariables(a, b);
        double e1 = pow(x - c, 2) / (a * b);
        return log(a) * exp(-e1);
    };
    void Bell::DefaultLFOs()
    {
        LFO_a = new LFO(1.0, 0.02);
        LFO_b = new LFO(1.0, 0.02);
        LFO_c = new LFO(1.0, 0.02);
    }
    void Bell::SetLFO_A(LFO* lfo)
    {
        LFO_a = lfo;
    }
    void Bell::SetLFO_B(LFO* lfo)
    {
        LFO_b = lfo;
    }
    void Bell::SetLFO_C(LFO* lfo)
    {
        LFO_c = lfo;
    }
    void Bell::SetLFOs(LFO* lfo_a, LFO* lfo_b, LFO* lfo_c)
    {
        LFO_a = lfo_a;
        LFO_b = lfo_b;
        LFO_c = lfo_c;
    }
    Bell* Bell::RandomBell(int complexity)
    {
        double val = complexity / max_complexity;
        double a = val * 1.7 + 1;
        double b = val * 10;
        int df = floor(val * 2.0);
        std::chi_squared_distribution<double> chi(df);
        double c = chi(rng);
        Bell* bell = new Bell(a, b, c);
        bell->SetLFOs(LFO::RandomLFO(complexity), LFO::RandomLFO(complexity), LFO::RandomLFO(complexity));
        return bell;
    }
    Bell* Bell::RandomBell(int complexity, Waves* wave)
    {
        double val = complexity / max_complexity;
        double a = val * 1.7 + 1;
        double b = val * 10;
        int df = floor(val * 2.0);
        std::chi_squared_distribution<double> chi(df);
        double c = chi(rng);
        Bell* bell = new Bell(a, b, c);
        bell->SetLFOs(LFO::RandomLFO(complexity, wave), LFO::RandomLFO(complexity, wave), LFO::RandomLFO(complexity, wave));
        return bell;
    }

    double HarmMapping::operator()(double x)
    {
        double base = exp(-pow(x-1, 2)/2.0);
        std::vector<double> vec(this->size());
        std::transform(this->begin(), this->end(), vec.begin(), [x](Bell* b) { return (*b)(x); });
        double sum = std::accumulate(vec.begin(), vec.end(), base);
        return sum / (size() + 1);
    }
    HarmMapping* HarmMapping::RandomHarmMapping(int complexity)
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
    HarmMapping* HarmMapping::RandomHarmMapping(int complexity, Waves* wave)
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

    FSeries::FSeries(double pitch_ratio, HarmMapping* an, Waves* wave, int n, double amplitude, double h_shape) : freq_ratio(pitch_ratio), N(n), amp(amplitude), shape(h_shape)
    {
        a_n = an;
        wave_form = wave;
    };
    FSeries::FSeries(double pitch_ratio, HarmMapping* an, Waves* wave) : freq_ratio(pitch_ratio), N(50), amp(1.0), shape(1.0)
    {
        a_n = an;
        wave_form = wave;
    };
    double FSeries::operator()(double x)
    {
        double sum = 0.0;
        for (int i = 1; i <= N; ++i)
        {
            double damp = 1 - (1 - amp + 1/pow(N, 2)) * pow(i, shape)/N;
            sum += damp * (*a_n)(i) * wave_form->f(i*x*freq_ratio);
        }
        return sum;
    }
    Waves* FSeries::GetWaveForm()
    {
        return wave_form;
    }
    void FSeries::SetAmp(double val)
    {
        amp = val;
    }
    FSeries* FSeries::RandomFSeries(int complexity)
    {
        double val = complexity / max_complexity;
        int n = floor(val * 10) + 10;
        Waves* wave = Waves::RandomWave();
        std::uniform_real_distribution<double> u(0, 1);
        std::chi_squared_distribution<double> chi(1);
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
        return new FSeries(pitch, HarmMapping::RandomHarmMapping(complexity), wave, n, amplitude, chi(rng));
    };
    FSeries* FSeries::RandomFSeries(int complexity, Waves* wave)
    {
        double val = complexity / max_complexity;
        int n = floor(val * 10) + 10;
        Waves* w = new Waves(wave);
        std::uniform_real_distribution<double> u(0, 1);
        std::chi_squared_distribution<double> chi(1);
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
        return new FSeries(pitch, HarmMapping::RandomHarmMapping(complexity, wave), w, n, amplitude, chi(rng));
    };

    double FSeriesVector::operator()(double x, double amp)
    {
        double s = 0.0;
        for (auto w : *this)
        {
            w->SetAmp(amp);
            s += (*w)(x);
        }
        return s;
    } 

    SynthNote::SynthNote() : 
        dur(1.0), amp(.8), freq(100.0)
    {
        SetADSR(0.003, 0, 0.005, 0, 0.875, (dur - 0.008), 0.25, 0);
    };
    void SynthNote::AddWave(FSeries* wave)
    {
        waves.push_back(wave);
    }
    void SynthNote::SetAttack(double val)
    {
        ADSR.A = val;
    }
    void SynthNote::SetQAttack(double val)
    {
        ADSR.qA = val;
    }
    void SynthNote::SetDecay(double val)
    {
        ADSR.D = val;
    }
    void SynthNote::SetQDecay(double val)
    {
        ADSR.qD = val;
    }
    void SynthNote::SetSustain(double val)
    {
        ADSR.S = val;
    }
    void SynthNote::SetLSustain(double val)
    {
        ADSR.lS = val;
    }
    void SynthNote::SetRelease(double val)
    {
        ADSR.R = val;
    }
    void SynthNote::SetQRelease(double val)
    {
        ADSR.qR = val;
    }
    void SynthNote::SetADSR(double atk, double qatk, double dc, double qdc, double sus, double lsus, double rel, double qrel)
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
    void SynthNote::NoADSR()
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
    void SynthNote::SetArticulation(Envelope art)
    {
        ADSR = art;
        dur = art.lS + art.A + art.D;
    }
    void SynthNote::SetDuration(double val)
    {
        dur = val;
        ADSR.lS = val - ADSR.A - ADSR.D;
    }
    void SynthNote::SetPitch(double val)
    {
        freq = val;
    }
    void SynthNote::SetAmplitude(double val)
    {
        amp = val;
    }
    double SynthNote::GetDuration()
    {
        return dur;
    }
    double SynthNote::GetPitch()
    {
        return freq;
    }
    double SynthNote::GetAmplitude()
    {
        return amp;
    }
    int SynthNote::GetShortNumberOfSamples()
    {
        return static_cast<int>(dur * sample_rate);
    }
    int SynthNote::GetNumberOfSamples()
    {
        return static_cast<int>((dur+ADSR.R) * sample_rate);
    }
    double SynthNote::GetSampleRate()
    {
        return sample_rate;
    }
    double SynthNote::operator()(int sample)
    {
        double t = sample / sample_rate;
        return ADSR.env(t) * waves(t*freq, amp);
    }
    short* SynthNote::Play(double note, double velocity)
    {
        amp = velocity / 127.0;
        freq = FrequencyByMidi(note);
        return Buffer();
    }
    short* SynthNote::Buffer()
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
    double* SynthNote::DoubleBuffer()
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
    void SynthNote::ToWAV(const char* file_name = "SynthNote.wav")
    {
        short* buff = Buffer();
        int nSamples = static_cast<int>((dur+ADSR.R) * sample_rate);
        WAV::wave_file wav(buff, nSamples);
        wav.Save(file_name, sample_rate);
    }
    void SynthNote::AddRandomWave(int complexity)
    {
        AddWave(FSeries::RandomFSeries(complexity));
    }
    void SynthNote::AddRandomWave(int complexity, Waves* wave)
    {
        AddWave(FSeries::RandomFSeries(complexity, wave));
    }
    void SynthNote::AddRandomWaves(int complexity)
    {
        double val = complexity / max_complexity;
        int n = floor(val * 10) + 1;
        for (int _ = 0; _ < n; _ ++)
        {
            AddWave(FSeries::RandomFSeries(complexity));
        }
    }
    void SynthNote::AddRandomWaves(int complexity, Waves* wave)
    {
        double val = complexity / max_complexity;
        int n = floor(val * 10) + 1;
        for (int _ = 0; _ < n; _ ++)
        {
            AddWave(FSeries::RandomFSeries(complexity, wave));
        }
    }

    XSynth::XSynth(SynthNote* synth_note, std::vector<int> notes, std::vector<int> vels = {1,2,3,4,5,6,7,8}, std::vector<int> rels = {1}) :
        midinotes(notes)
    {
        sn = synth_note;
        harm_sn = nullptr;
        rel_sn = nullptr;
        CreateMap(vels, rels);
    }
    XSynth::XSynth(SynthNote* synth_note, SynthNote* harm_note, std::vector<int> notes, std::vector<int> vels = {1,2,3,4,5,6,7,8}, std::vector<int> rels = {1}) :
        midinotes(notes)
    {
        sn = synth_note;
        harm_sn = harm_note;
        rel_sn = nullptr;
        CreateMap(vels, rels);
    }
    XSynth::XSynth(SynthNote* synth_note, SynthNote* harm_note, SynthNote* rel_note, std::vector<int> notes, std::vector<int> vels = {1,2,3,4,5,6,7,8}, std::vector<int> rels = {1}) :
        midinotes(notes)
    {
        sn = synth_note;
        harm_sn = harm_note;
        rel_sn = rel_note;
        CreateMap(vels, rels);
    }
    void XSynth::CreateMap(std::vector<int> vels = {1,2,3,4,5,6,7,8}, std::vector<int> rels = {1})
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
    void XSynth::SaveSamplesToBitKlavier(std::string sample_name = "XSynth", bool override = true)
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
}