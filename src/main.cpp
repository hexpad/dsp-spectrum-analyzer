#include "SignalGenerator.h"

#include <fstream>
#include <iostream>

int main()
{
    SignalGenerator generator;

    double sampleRate = 100.0;
    double duration = 1.0;

    std::vector<double> cleanSignal =
        generator.generateSine(
            3.0,
            1.0,
            duration,
            sampleRate);

    std::vector<double> signal =
        generator.addNoise(
            cleanSignal,
            0.20);

    std::vector<double> spectrum =
        generator.computeDFT(signal);

    int peakIndex = generator.findPeak(spectrum);

    std::cout << "Peak Index : " << peakIndex << "\n";

    // File
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

    std::ofstream spectrumFile("spectrum.csv");

    if (!spectrumFile)
    {
        std::cerr << "Failed to create spectrum.csv\n";
        return 1;
    }

    spectrumFile << "Frequency,Magnitude\n";

    for (int i = 0; i < spectrum.size(); i++)
    {
        spectrumFile << i
                     << ","
                     << spectrum[i]
                     << '\n';
    }

    spectrumFile.close();

    std::cout << "signal.csv created successfully.\n";
    std::cout << "spectrum.csv created successfully.\n";

    return 0;
}
