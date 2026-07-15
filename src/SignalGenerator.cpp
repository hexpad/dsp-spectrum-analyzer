#include "SignalGenerator.h"

#include <cmath>
#include <random>

std::vector<double> SignalGenerator::generateSine(
    double frequency,
    double amplitude,
    double duration,
    double sampleRate,
    double phase)
{
    int sampleCount = static_cast<int>(duration * sampleRate);

    std::vector<double> samples;

    for (int i = 0; i < sampleCount; i++)
    {
        double time = i / sampleRate;

        double sample =
            amplitude *
            std::sin(
                2.0 *
                    M_PI *
                    frequency *
                    time +
                phase);

        samples.push_back(sample);
    }

    return samples;
}

std::vector<double> SignalGenerator::generateSquare(
    double frequency,
    double amplitude,
    double duration,
    double sampleRate,
    double phase)
{
    int sampleCount = static_cast<int>(duration * sampleRate);

    std::vector<double> samples;

    for (int i = 0; i < sampleCount; i++)
    {
        double time = i / sampleRate;

        double sample =
            std::sin(
                2.0 *
                    M_PI *
                    frequency *
                    time +
                phase);

        if (sample >= 0.0)
        {
            samples.push_back(amplitude);
        }
        else
        {
            samples.push_back(-amplitude);
        }
    }

    return samples;
}

std::vector<double> SignalGenerator::addSignals(
    const std::vector<double>& signal1,
    const std::vector<double>& signal2)
{
    std::vector<double> result;

    if (signal1.size() != signal2.size())
    {
        return result;
    }

    for (int i = 0; i < signal1.size(); i++)
    {
        result.push_back(
            signal1[i] +
            signal2[i]);
    }

    return result;
}

std::vector<double> SignalGenerator::addNoise(
    const std::vector<double>& signal,
    double noiseAmplitude)
{
    std::vector<double> noisySignal;

    std::random_device randomDevice;
    std::mt19937 engine(randomDevice());

    std::uniform_real_distribution<double> distribution(
        -noiseAmplitude,
        noiseAmplitude);

    for (int i = 0; i < signal.size(); i++)
    {
        noisySignal.push_back(
            signal[i] +
            distribution(engine));
    }

    return noisySignal;
}

std::vector<double> SignalGenerator::movingAverage(
    const std::vector<double>& signal,
    int windowSize)
{
    std::vector<double> filteredSignal;

    if (windowSize <= 0 ||
        windowSize > signal.size())
    {
        return filteredSignal;
    }

    for (int i = 0;
         i <= signal.size() - windowSize;
         i++)
    {
        double sum = 0.0;

        for (int j = 0;
             j < windowSize;
             j++)
        {
            sum += signal[i + j];
        }

        filteredSignal.push_back(
            sum / windowSize);
    }

    return filteredSignal;
}

std::vector<double> SignalGenerator::computeDFT(
    const std::vector<double>& signal)
{
    std::vector<double> spectrum;

    int sampleCount = signal.size();

    for (int k = 0;
         k <= sampleCount / 2;
         k++)
    {
        double real = 0.0;
        double imag = 0.0;

        for (int n = 0;
             n < sampleCount;
             n++)
        {
            double angle =
                2.0 *
                M_PI *
                k *
                n /
                sampleCount;

            real +=
                signal[n] *
                std::cos(angle);

            imag -=
                signal[n] *
                std::sin(angle);
        }

        double magnitude =
            std::sqrt(
                real * real +
                imag * imag);

        spectrum.push_back(magnitude);
    }

    return spectrum;
}

int SignalGenerator::findPeak(
    const std::vector<double>& spectrum)
{
    if (spectrum.empty())
    {
        return -1;
    }

    int peakIndex = 0;

    for (int i = 1;
         i < spectrum.size();
         i++)
    {
        if (spectrum[i] >
            spectrum[peakIndex])
        {
            peakIndex = i;
        }
    }

    return peakIndex;
}
