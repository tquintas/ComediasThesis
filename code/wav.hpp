#ifndef WAV_H
#define WAV_H

#include <fstream>
extern "C" {
    #include </usr/local/include/fftw3.h>
}

namespace WAV
{
    // Define a struct for working with WAV audio data
    typedef struct WAVE
    {
        short* Buffer;
        short NumberChannels;
        int SubChunkSize1;
        short BitsPerSample;
        int ByteRate;
        short BlockAlign;
        int DataSize;
        int FileSize;
        int SampleRate;
        int NumberSamples;

        // Constructor to initialize the WAVE struct
        WAVE(short* buff, int number_of_samples);

        // Save the WAV audio data to a file
        void Save(const char* file_name = "WaveFile.wav", int sample_rate = 44100, short bits_per_sample = 16, short number_of_channels = 1);

        // Perform convolution with another WAVE object
        WAVE convolve(WAVE* other);
    } wave_file;
}

#endif