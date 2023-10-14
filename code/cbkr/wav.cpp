#include "wav.hpp"

namespace WAV
{
    wave_file::WAVE(short* buff, int number_of_samples)
    {
        Buffer = buff;
        NumberSamples = number_of_samples;
    }
    void wave_file::Save(const char* file_name, int sample_rate, short bits_per_sample, short number_of_channels)
    {
        SampleRate = sample_rate;
        BitsPerSample = bits_per_sample;
        NumberChannels = number_of_channels;
        SubChunkSize1 = 16;
        ByteRate = static_cast<int>(SampleRate * NumberChannels * BitsPerSample / 8);
        BlockAlign = NumberChannels * BitsPerSample / 8;
        DataSize = NumberChannels * NumberSamples * BitsPerSample / 8;
        FileSize = 36 + DataSize;
        short pcm = 1;
        std::ofstream wav(file_name, std::ios::binary);
        wav.write("RIFF", 4);
        wav.write(reinterpret_cast<const char*>(&FileSize), 4);
        wav.write("WAVE", 4);
        wav.write("fmt ", 4);
        wav.write(reinterpret_cast<const char*>(&SubChunkSize1), 4);
        wav.write(reinterpret_cast<const char*>(&pcm), 2);
        wav.write(reinterpret_cast<const char*>(&NumberChannels), 2);
        wav.write(reinterpret_cast<const char*>(&SampleRate), 4);
        wav.write(reinterpret_cast<const char*>(&ByteRate), 4);
        wav.write(reinterpret_cast<const char*>(&BlockAlign), 2);
        wav.write(reinterpret_cast<const char*>(&BitsPerSample), 2);
        wav.write("data", 4);
        wav.write(reinterpret_cast<const char*>(&DataSize), 4);
        for (int i = 0; i < NumberSamples; i++)
        {
            short sample = Buffer[i];
            wav.write(reinterpret_cast<const char*>(&sample), BitsPerSample/8);
        }
        wav.close();
    }
    wave_file wave_file::convolve(WAVE* other)
    {
        int N = NumberSamples;
        int M = other->NumberSamples;
        int K = N + M - 1;
        short* x = Buffer;
        short* h = other->Buffer;
        short* y = new short[K];

        fftw_complex* X = fftw_alloc_complex(N);
        fftw_complex* H = fftw_alloc_complex(M);
        fftw_complex* Y = fftw_alloc_complex(K);

        for (int n = 0; n < N; n++)
        {
            X[n][0] = x[n] / static_cast<double>(INT16_MAX);
            X[n][1] = 0;
            H[n][0] = h[n] / static_cast<double>(INT16_MAX);
            H[n][1] = 0;
        }

        fftw_plan plan_X = fftw_plan_dft_1d(N, X, X, FFTW_FORWARD, FFTW_ESTIMATE);
        fftw_plan plan_H = fftw_plan_dft_1d(M, H, H, FFTW_FORWARD, FFTW_ESTIMATE);
        fftw_plan plan_Y = fftw_plan_dft_1d(K, Y, Y, FFTW_BACKWARD, FFTW_ESTIMATE);
        fftw_execute(plan_X);
        fftw_execute(plan_H);

        for (int k = 0; k < N; k++)
        {
            double re = X[k][0] * H[k][0] - X[k][1] * H[k][1];
            double im = X[k][0] * H[k][1] + X[k][1] * H[k][0];
            Y[k][0] = re;
            Y[k][1] = im;
        }

        fftw_execute(plan_Y);

        for (int n = 0; n < K; n++)
        {
            y[n] = (Y[n][0] / N) * INT16_MAX;
        }

        fftw_destroy_plan(plan_X);
        fftw_destroy_plan(plan_H);
        fftw_destroy_plan(plan_Y);
        fftw_free(X);
        fftw_free(H);
        fftw_free(Y);

        return wave_file(y, K);
    }
}