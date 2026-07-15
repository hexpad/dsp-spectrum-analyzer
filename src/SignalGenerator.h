#ifndef SIGNAL_GENERATOR_H
#define SIGNAL_GENERATOR_H

#include <vector>

class SignalGenerator
{
public:
    std::vector<double> generateSine(
        double frequency,
        double amplitude,
        double duration,
        double sampleRate,
        double phase = 0.0);

    std::vector<double> addSignals(
        const std::vector<double>& signal1,
        const std::vector<double>& signal2);

    std::vector<double> computeDFT(
        const std::vector<double>& signal);

    std::vector<double> generateSquare(
        double frequency,
        double amplitude,
        double duration,
        double sampleRate,
        double phase = 0.0);

    std::vector<double> addNoise(
        const std::vector<double>& signal,
        double noiseAmplitude);

    int findPeak(
        const std::vector<double>& spectrum);
};

#endif // SIGNAL_GENERATOR_H
