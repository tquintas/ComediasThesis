#include "xml.cpp"

using namespace SerialMatrix;
using namespace QSynth;
using namespace bkr;

void DeleteAllSounds()
{
    std::string fname = documents + "bitSamples/XSynth";
    for (const auto& entry : std::filesystem::directory_iterator(fname))
    {
        if (std::filesystem::is_regular_file(entry))
        {
            std::filesystem::remove(entry.path());
        }
    }
}

void SaveVector(std::vector<std::tuple<int, int>> notes)
{
    std::string fname = documents + "bitSamples/XSynth/remaining_notes.txt";
    std::ofstream file(fname);
    if (file.is_open())
    {
        for (std::tuple<int, int> t : notes)
        {
            file << std::get<0>(t) << " " << std::get<1>(t) << "\n";
        }
        file.close();
    }
    else
    {
        std::cout << "Error opening file." << std::endl;
    }
}

void BuildVector()
{
    std::vector<std::tuple<int, int>> notes;
    for (int i = 21; i < 109; ++i)
    {
        for (int j = 1; j < 9; ++j)
        {
            notes.push_back(std::tuple<int, int>(i, j));
        }
    }
    SaveVector(notes);
}

std::vector<int> LoadVector(std::vector<std::tuple<int, int>>& notes)
{
    std::vector<int> indexes;
    std::string fname = documents + "bitSamples/XSynth/remaining_notes.txt";
    std::ifstream file(fname);
    if (file.is_open())
    {
        int n,m;
        int k = 20;
        int c = 0;
        while (file >> n >> m)
        {
            notes.push_back(std::tuple<int, int>(n,m));
            if (n > k)
            {
                k++;
                indexes.push_back(c);
            }
            c++;
        }
        file.close();
    }
    else
    {
        std::cout << "Error opening file." << std::endl;
    }
    return indexes;
}

void MakeSetupGalleries()
{
    for (int i = 1; i <= 5; ++i)
    {
        XAttribute* g_name = XAttribute::bitKlavierAttributes.Name("XGallery"+to_string(i));
        BitKlavier* bk = new BitKlavier(g_name);
        bk->Save();
    }
}

void MakeSetupNote()
{
    SynthNote* sn = new SynthNote();
    XSynth* qs = new XSynth(sn, std::vector<int>{60}, std::vector<int>{1}, std::vector<int>{});
    qs->SaveSamplesToBitKlavier();
}

void MakeSynth(int complexity)
{
    std::vector<std::tuple<int, int>> notes;
    auto idxs = LoadVector(notes);
    int s = notes.size();
    int s2 = idxs.size();
    if (s == 0)
    {
        BuildVector();
        idxs = LoadVector(notes);
        int s = notes.size();
    }
    int rel = (((88*8) - s) % 88) + 1;
    std::uniform_int_distribution<int> idx(0, s2-1);
    int index = idx(bkr::rng);
    int index2 = idxs[index];
    auto note = notes[index2];
    notes.erase(notes.begin() + index2);
    SaveVector(notes);

    SynthNote* sn = new SynthNote();
    SynthNote* sn2 = new SynthNote();
    SynthNote* sn3 = new SynthNote();

    sine_wave sw = sine_wave();
    sn->AddRandomWave(complexity, sw);
    sn->AddRandomWaves(complexity);
    int complexity2 = floor(sqrt(complexity));
    int complexity3 = floor(sqrt((complexity / bkr::max_complexity)) * bkr::max_complexity);
    sn2->AddRandomWaves(complexity2);
    sn3->AddRandomWaves(complexity3);
    std::vector<int> ns = {std::get<0>(note)};
    std::vector<int> vel = {std::get<1>(note)};
    std::vector<int> relv = {rel};
    XSynth* qs = new XSynth(sn, sn2, sn3, ns, vel, relv);
    qs->SaveSamplesToBitKlavier();
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <integer_argument>, start or setup" << std::endl;
        return 1;
    }
    if (strcmp(argv[1], "start") == 0)
    {
        DeleteAllSounds();
        BuildVector();
        return 0;
    }
    if (strcmp(argv[1], "setup") == 0)
    {
        DeleteAllSounds();
        MakeSetupNote();
        MakeSetupGalleries();
        return 0;
    }
    int complexity = std::atoi(argv[1]);
    bool error = complexity == 0 && argv[1][0] != '0';
    if (error || complexity < 0 || complexity >= 1024)
    {
        std::cerr << "Invalid argument. Please provide a valid integer." << std::endl;
        return 1;
    }

    MakeSynth(complexity);

    return 0;
};