# Spectrum Analyzer

A C++ project that generates signals, adds noise, and analyzes the frequency content using a Discrete Fourier Transform (DFT). The results are saved as CSV files.

## Features

- Generate sine and square waves
- Add two signals together
- Add random noise to a signal
- Compute the DFT (magnitude spectrum) of a signal
- Save results as CSV files

## Files

| File | Description |
|------|-------------|
| `SignalGenerator.h` | Class declaration |
| `SignalGenerator.cpp` | Signal generation and DFT implementation |
| `main.cpp` | Demo program |

## How to Build

```bash
g++ -std=c++11 main.cpp SignalGenerator.cpp -o signal_generator
```

## How to Run

```bash
./signal_generator
```

The program:

1. Generates a 3 Hz sine wave (1 second, 100 Hz sample rate)
2. Adds random noise to it
3. Computes the DFT of the noisy signal
4. Creates two output files:
   - `signal.csv` → the noisy signal (Time, Amplitude)
   - `spectrum.csv` → the frequency spectrum (Frequency, Magnitude)

## Results

The CSV files were plotted using [CSV Plot](https://www.csvplot.com/).

### Noisy Signal (Time Domain)

<img width="1295" height="727" alt="signal" src="https://github.com/user-attachments/assets/e885100b-86c5-4a5a-ac0a-4b6d332a645f" />

### Frequency Spectrum (DFT)

<img width="1300" height="730" alt="spectrum" src="https://github.com/user-attachments/assets/aa820c61-2faf-4a31-a689-95ba4cf6396a" />

The peak at frequency bin 3 shows the original 3 Hz sine wave. The spectrum is symmetric, so a mirror peak also appears near bin 97.

