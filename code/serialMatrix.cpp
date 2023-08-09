#include "qsynth.cpp"
#include <tuple>
#define breve 8.0;
#define semibreve 4.0;
#define minim 2.0;
#define crotchet 1.0;
#define quaver 0.5;
#define semiquaver 0.25;
#define demisemiquaver 0.125;
#define hemidemisemiquaver 0.0625;

void print(std::vector<int> v)
{
    for (int k : v)
    {
        std::cout << k << ' ';
    }
    std::cout << std::endl;
}

namespace SerialMatrix
{
    typedef struct NOTE
    {
        double frequency;
        double amplitude;
        double tempo;
        QSynth::SynthNote timbre;
        std::tuple<double, double, double> space;
        int sample_offset;
        NOTE(QSynth::SynthNote sn)
        {
            timbre = sn;
            frequency = sn.GetPitch();
            amplitude = sn.GetAmplitude();
            tempo = sn.GetDuration();
            space = std::tuple<double, double, double>(0, 0, 0);
        }
        NOTE(QSynth::SynthNote& sn, double pitch, double amp, double duration, std::tuple<double, double, double> _3d)
        {
            frequency = pitch;
            amplitude = amp;
            tempo = duration;
            space = _3d;
            sn.SetAmplitude(amplitude);
            sn.SetDuration(tempo);
            sn.SetPitch(frequency);
            timbre = sn;
        }
    } note;

    typedef struct NOTE_VALUE
    {
        double BPM;
        double SPB;
        NOTE_VALUE(double bpm) : BPM(bpm) { SPB = 60.0 / bpm; };
        double duration(double beat_length, double tuple = 1.0)
        {
            return (beat_length / tuple) * SPB;
        }
    } note_value;

    class Melody
    {
        private:
            std::vector<note*> melody;
            int duration;
            int offset;
            QSynth::SynthNote* main_timbre;
            note_value* BPM;
        public:
            Melody(QSynth::SynthNote* sn, double bpm) :
                duration(0), offset(0)
            {
                main_timbre = sn;
                BPM = new note_value(bpm);
            }
            void AddNote(double pitch, double amp, double beat_length, double tuple = 1.0)
            {
                main_timbre->SetAmplitude(amp);
                main_timbre->SetDuration(BPM->duration(beat_length, tuple));
                main_timbre->SetPitch(pitch);

                note* n = new note(*main_timbre);
                n->sample_offset = offset;
                duration = offset + main_timbre->GetNumberOfSamples();
                offset = offset + main_timbre->GetShortNumberOfSamples();
                melody.push_back(n);
            }
            short* Buffer()
            {
                double* dbuff = new double[duration]();
                short* buff_16 = new short[duration];
                for (note* n : melody)
                {
                    double* buff = n->timbre.DoubleBuffer();
                    int off = n->sample_offset;
                    for (int i = 0; i < n->timbre.GetNumberOfSamples(); i++)
                    {
                        dbuff[i+off] += buff[i];
                    }
                }
                double maxi = 0.0;
                for (int i = 0; i < duration; i++)
                {
                    maxi = std::max(maxi, dbuff[i]);
                }
                for (int i = 0; i < duration; i++)
                {
                    if (maxi >= 1) { dbuff[i] /= maxi; };
                    ((short*)buff_16)[i] = dbuff[i] * INT16_MAX;
                }
                return buff_16;
            }
            void ToWAV(const char* file_name = "Melody.wav")
            {
                short* buff = Buffer();
                WAV::wave_file wav(buff, duration);
                wav.Save(file_name, GetSampleRate());
            }
            double GetSampleRate()
            {
                return main_timbre->GetSampleRate();
            }
            static void Convolve(std::vector<Melody*> melodies, const char* file_name = "Convolution.wav")
            {
                Melody* first = melodies[0];
                WAV::wave_file wav(first->Buffer(), first->duration);
                for (int i = 1; i < melodies.size(); i++)
                {
                    short* buff = melodies[i]->Buffer();
                    int nsamples = melodies[i]->duration;
                    WAV::wave_file wav2(buff, nsamples);
                    wav = wav.convolve(&wav2);
                }
                wav.Save(file_name, first->GetSampleRate());
            }
    };

    class Matrix
    {
        typedef struct MATRIX_ENTRY
        {
            int i;
            int j;
            int value;
            Matrix* matrix;
            MATRIX_ENTRY() {};
            MATRIX_ENTRY(Matrix* mtx, int row, int column, int val)
            {
                matrix = mtx;
                i = row;
                j = column;
                value = val;
            }
            MATRIX_ENTRY up(int step)
            {
                return matrix->Entry(i - step, j);
            }
            MATRIX_ENTRY down(int step)
            {
                return matrix->Entry(i + step, j);
            }
            MATRIX_ENTRY left(int step)
            {
                return matrix->Entry(i, j - step);
            }
            MATRIX_ENTRY right(int step)
            {
                return matrix->Entry(i, j + step);
            }
            MATRIX_ENTRY next(int step, int direction)
            {
                return direction == 0 ? right(step) : direction == 1 ? up(step) : direction == 2 ? left(step) : down(step);
            }
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
            Matrix(std::vector<int> melody)
            {
                size = melody.size();
                wrap = std::min(size, 12);
                matrix = new MatrixEntry*[size];
                std::vector<int> intervals;
                for (int i = 0; i < size; ++i)
                {
                    if (i == 0) 
                    {
                        intervals.push_back(0);
                    }
                    else
                    {
                        intervals.push_back(melody[i]-melody[i-1]);
                    }
                    matrix[i] = new MatrixEntry[size];
                }
                prime.reserve(size);
                prime = melody;
                inverted.reserve(size);
                p_idx.reserve(size);
                i_idx.reserve(size);
                int r = melody[0];
                std::transform(intervals.begin(), intervals.end(), inverted.begin(), [&r, this](int x) { r = (r - x + wrap) % wrap; return r; });
                int p1 = prime[0];
                for (int i = 0; i < size; i++)
                {
                    int r2 = inverted[i];
                    p_idx[(r2 - p1 + wrap) % wrap] = i;
                    i_idx[(prime[i] - p1 + wrap) % wrap] = i;
                    for (int j = 0; j < size; j++)
                    {
                        r2 = (r2 + intervals[j] + wrap) % wrap;
                        MatrixEntry me(this, i, j, r2); 
                        matrix[i][j] = me;
                    }
                }
            }
            ~Matrix()
            {
                for (int i = 0; i < size; i++)
                {
                    delete matrix[i];
                }
                delete matrix;
            }
            MatrixEntry Entry(int i, int j)
            {
                return matrix[(i + size) % size][(j + size) % size];
            }
            void printMatrix()
            {
                int p1 = prime[0];
                for (int i = -1; i <= size; i++)
                {
                    if (i != -1 && i != size)
                    {
                        std::cout << "P" << (inverted[i] - p1 + wrap) % wrap << '\t';
                    }
                    for (int j = 0; j < size; j++)
                    {
                        if (i == -1)
                        {
                            std::cout << '\t' << "I" << (prime[j] - p1 + wrap) % wrap;
                        }
                        else if (i == size)
                        {
                            std::cout << '\t' << "RI" << (prime[j] - p1 + wrap) % wrap;
                        }
                        else
                        {
                            std::cout << Entry(i,j).value << '\t';
                        }
                    }
                    if (i != -1 && i != size)
                    {
                        std::cout << "R" << (inverted[i] - p1 + wrap) % wrap << '\t' << std::endl;
                    }
                    else
                    {
                        std::cout << std::endl;
                    }
                }
            }
            std::vector<int> P(int i)
            {
                std::vector<int> p(size);
                for (int j = 0; j < size; j++)
                {
                    p.push_back(Entry(p_idx[i], j).value);
                }
                return p;
            }
            std::vector<int> I(int i)
            {
                std::vector<int> p;
                for (int j = 0; j < size; j++)
                {
                    p.push_back(Entry(j, i_idx[i]).value);
                }
                return p;
            }
            std::vector<int> R(int i)
            {
                std::vector<int> p;
                for (int j = size-1; j >= 0; j--)
                {
                    p.push_back(Entry(p_idx[i], j).value);
                }
                return p;
            }
            std::vector<int> RI(int i)
            {
                std::vector<int> p;
                for (int j = size-1; j >= 0; j--)
                {
                    p.push_back(Entry(j, i_idx[i]).value);
                }
                return p;
            }
            MatrixEntry RandomEntry(int t)
            {
                srand(time(0));
                int p1 = prime[0];
                int row = rand() % size;
                int v0 = matrix[row][0].value;
                int col = i_idx[(wrap - (v0 - t)) % wrap];
                return matrix[row][col];
            }
            std::vector<int> SectionBegin(int t, int n)
            {
                srand(time(0));
                std::vector<int> p;
                MatrixEntry entry = RandomEntry(t);
                p.push_back(entry.value);
                int dir = rand() % 4;
                while (p.size() < n)
                {
                    entry = entry.next(1, dir);
                    p.push_back(entry.value);
                }
                return p;
            }
            std::vector<int> SectionEnd(int t, int n)
            {
                std::vector<int> v = SectionBegin(t,n);
                std::reverse(v.begin(), v.end());
                return v;
            }
            std::vector<int> SpiralOut(int t, int n)
            {
                srand(time(0));
                std::vector<int> p;
                MatrixEntry entry = RandomEntry(t);
                p.push_back(entry.value);
                int dir = rand() % 4;
                int pos = rand() % 2;
                int count = 2;
                auto a = [](int i) { return floor( pow(i, 2) / 4.0); };
                while (p.size() < n)
                {
                    entry = entry.next(1, dir);
                    p.push_back(entry.value);
                    if (p.size() - 1 == a(count))
                    {
                        dir = pos ? (dir + 1) % 4 : (2*dir - 1) % 4;
                        count++;
                    }
                }
                return p;
            }
            std::vector<int> SpiralIn(int t, int n)
            {
                std::vector<int> v = SpiralOut(t,n);
                std::reverse(v.begin(), v.end());
                return v;
            }
            std::vector<int> RandomSection(int n)
            {
                std::mt19937 rng(std::random_device{}());
                std::uniform_int_distribution<int> note(0, size-1);
                std::uniform_int_distribution<int> no(0, 3);
                int i = no(rng);
                int t = note(rng);
                return i == 0 ? SectionBegin(t,n) : i == 1 ? SectionEnd(t,n) : i == 2 ? SpiralIn(t,n) : SpiralOut(t,n);
            }
            Melody* RandomMelody(int complexity)
            {
                std::mt19937 rng(std::random_device{}());
                int ubpm = floor((complexity / QSynth::max_complexity) * 60) + 60;
                std::normal_distribution<double> norm(ubpm, 10);
                std::uniform_int_distribution<int> oct(4, 8);
                int bpm = floor(norm(rng));
                QSynth::SynthNote* sn = new QSynth::SynthNote();
                sn->AddRandomWaves(complexity);
                Melody* m = new Melody(sn, bpm);
                int n = floor((complexity / QSynth::max_complexity) * 20);
                std::vector<int> pitches = RandomSection(n);
                std::vector<int> rhythms = RandomSection(n);
                std::vector<int> velocity = RandomSection(n);
                int octave = oct(rng)*12;
                int slow = 3 - floor((complexity / QSynth::max_complexity) * 3);
                double diff = QSynth::max_complexity - complexity;
                std::vector<double> freqs(n);
                std::transform(pitches.begin(), pitches.end(), freqs.begin(), [octave](int p) { return QSynth::FrequencyByMidi(octave + p); });
                std::vector<double> durations(n);
                std::transform(rhythms.begin(), rhythms.end(), durations.begin(), [slow](int p) { return pow(2, slow - p); });
                std::vector<double> amps(n);
                std::transform(velocity.begin(), velocity.end(), amps.begin(), [diff, this](int p) { return (p + diff) / (size + diff - 1); });
                for (int i = 0; i < n; i++)
                {
                    m->AddNote(freqs[i], amps[i], durations[i]);
                    std::cout << "Added note with pitch of " << freqs[i] << "Hz, amplitude of " << amps[i] << " and duration of " << durations[i] << "." << std::endl;
                }
                return m;
            }
    };

};