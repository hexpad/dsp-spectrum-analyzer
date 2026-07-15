#include "SignalGenerator.h"

#include <fstream>
#include <iomanip>
#include <iostream>

int main()
{
    SignalGenerator generator;

    double sampleRate = 200.0;
    double duration = 1.0;

    // Generate signals
    std::vector<double> signal1 =
        generator.generateSine(
            3.0,
            1.0,
            duration,
            sampleRate);

    std::vector<double> signal2 =
        generator.generateSine(
            7.0,
            0.5,
            duration,
            sampleRate);

    // Combine signals
    std::vector<double> signal =
        generator.addSignals(
            signal1,
            signal2);

    // Add noise
    signal =
        generator.addNoise(
            signal,
            0.20);

    // Apply moving average filter
    std::vector<double> filteredSignal =
        generator.movingAverage(
            signal,
            5);

    // Compute spectra
    std::vector<double> spectrum =
        generator.computeDFT(
            signal);

    std::vector<double> filteredSpectrum =
        generator.computeDFT(
            filteredSignal);

    // Peak detection (filtered spectrum)
    int peakIndex =
        generator.findPeak(
            filteredSpectrum);

    if (peakIndex == -1)
    {
        std::cerr << "No peak detected.\n";
        return 1;
    }

    double peakFrequency =
        peakIndex *
        sampleRate /
        filteredSignal.size();

    std::cout << "=====================================\n";
    std::cout << "      DSP Spectrum Analyzer v0.3\n";
    std::cout << "=====================================\n\n";

    std::cout << std::fixed << std::setprecision(2);

    std::cout << "Sample Rate    : "
              << sampleRate
              << " Hz\n";

    std::cout << "Duration       : "
              << duration
              << " s\n";

    std::cout << "Samples        : "
              << filteredSignal.size()
              << "\n\n";

    std::cout << "Peak Frequency : "
              << peakFrequency
              << " Hz\n";

    std::cout << "Peak Magnitude : "
              << filteredSpectrum[peakIndex]
              << "\n\n";

    // -----------------------------
    // signal.csv
    // -----------------------------
    std::ofstream signalFile("signal.csv");

    if (!signalFile)
    {
        std::cerr << "Failed to create signal.csv\n";
        return 1;
    }

    signalFile << "Time,Amplitude\n";

    for (int i = 0; i < signal.size(); i++)
    {
        double time = i / sampleRate;

        signalFile << time
                   << ","
                   << signal[i]
                   << '\n';
    }

    signalFile.close();

    // -----------------------------
    // filtered_signal.csv
    // -----------------------------
    std::ofstream filteredSignalFile(
        "filtered_signal.csv");

    if (!filteredSignalFile)
    {
        std::cerr << "Failed to create filtered_signal.csv\n";
        return 1;
    }

    filteredSignalFile << "Time,Amplitude\n";

    for (int i = 0; i < filteredSignal.size(); i++)
    {
        double time = i / sampleRate;

        filteredSignalFile << time
                           << ","
                           << filteredSignal[i]
                           << '\n';
    }

    filteredSignalFile.close();

    // -----------------------------
    // spectrum.csv
    // -----------------------------
    std::ofstream spectrumFile(
        "spectrum.csv");

    if (!spectrumFile)
    {
        std::cerr << "Failed to create spectrum.csv\n";
        return 1;
    }

    spectrumFile << "Frequency,Magnitude\n";

    for (int i = 0; i < spectrum.size(); i++)
    {
        double frequency =
            i * sampleRate / signal.size();

        spectrumFile << frequency
                     << ","
                     << spectrum[i]
                     << '\n';
    }

    spectrumFile.close();

    // -----------------------------
    // filtered_spectrum.csv
    // -----------------------------
    std::ofstream filteredSpectrumFile(
        "filtered_spectrum.csv");

    if (!filteredSpectrumFile)
    {
        std::cerr << "Failed to create filtered_spectrum.csv\n";
        return 1;
    }

    filteredSpectrumFile
        << "Frequency,Magnitude\n";

    for (int i = 0; i < filteredSpectrum.size(); i++)
    {
        double frequency =
            i * sampleRate /
            filteredSignal.size();

        filteredSpectrumFile
            << frequency
            << ","
            << filteredSpectrum[i]
            << '\n';
    }

    filteredSpectrumFile.close();

    std::cout << "Generated Files\n";
    std::cout << "---------------\n";
    std::cout << "signal.csv\n";
    std::cout << "filtered_signal.csv\n";
    std::cout << "spectrum.csv\n";
    std::cout << "filtered_spectrum.csv\n\n";

    std::cout << "Analysis completed successfully.\n";

    return 0;
}
