#include "include/qam.hpp"
#include <iostream>
#include <complex>
#include <vector>
#include <cmath>

QAMModulator::QAMModulator(QAMType type) : type(type) {}
QAMModulator::~QAMModulator() {}

std::vector<std::complex<double>> QAMModulator::modulate(const std::vector<bool>& bits) {
    std::vector<std::complex<double>> symbols;
    switch (type) {
        case QAMType::QPSK: symbols = modulateQPSK(bits); break;
        case QAMType::QAM16: symbols = modulateQAM16(bits); break;
        case QAMType::QAM64: symbols = modulateQAM64(bits); break;
    }

    return symbols;
}

// modulate QPSK
std::vector<std::complex<double>> QAMModulator::modulateQPSK(std::vector<bool> bits) {
    std::vector<std::complex<double>> symbols;
    for (size_t i = 0; i < bits.size(); i += 2) {
        // True\False omdulate 
        symbols.push_back(std::complex<double>(bits[i] ? 1 : -1, bits[i + 1] ? 1 : -1));
    }

    return symbols;
}

// modulate QAM16
std::vector<std::complex<double>> QAMModulator::modulateQAM16(std::vector<bool> bits) {
    std::vector<std::complex<double>> symbols;

    for (size_t i = 0; i < bits.size(); i += 4) {
        // bin to dex (0..15)
        int index = (bits[i] << 3) | (bits[i + 1] << 2) | (bits[i + 2] << 1) | bits[i + 3];
        
        // convert to the values -3, -1, 1, 3
        double realPart = (index & 0b11) * 2 - 3; 
        double imagPart = ((index >> 2) & 0b11) * 2 - 3;
        
        symbols.push_back(std::complex<double>(realPart, imagPart));
    }

    return symbols;
}

// modulate QAM64
std::vector<std::complex<double>> QAMModulator::modulateQAM64(std::vector<bool> bits) {
    std::vector<std::complex<double>> symbols;

    for (size_t i = 0; i < bits.size(); i += 6) {
        // bin to dex (0..63)
        int index = (bits[i] << 5) | (bits[i + 1] << 4) | (bits[i + 2] << 3) | (bits[i + 3] << 2) | (bits[i + 4] << 1) | bits[i + 5];
        
        // convert to the values -7, -5, -3, -1, 1, 3, 5, 7
        double realPart = (index & 0b111) * 2 - 7; 
        double imagPart = ((index >> 3) & 0b111) * 2 - 7; 

        symbols.push_back(std::complex<double>(realPart, imagPart));
    }

    return symbols;
}

QAMDemodulator::QAMDemodulator(QAMType type) : type(type) {}
QAMDemodulator::~QAMDemodulator() {}

// demodulate QAM
std::vector<bool> QAMDemodulator::demodulate(const std::vector<std::complex<double>>& symbols) {
    std::vector<bool> bits;
    switch (type) {
        case QAMType::QPSK: bits = demodulateQPSK(symbols); break;
        case QAMType::QAM16: bits = demodulateQAM16(symbols); break;
        case QAMType::QAM64: bits = demodulateQAM64(symbols); break;
    }

    return bits;
}

// demodulate QPSK
std::vector<bool> QAMDemodulator::demodulateQPSK(std::vector<std::complex<double>> symbols) {
    std::vector<bool> bits;
    for (const auto& symbol : symbols) {
        // True\False demodulate
        bits.push_back(symbol.real() > 0);
        bits.push_back(symbol.imag() > 0);
    }

    return bits;
}

// demodulate QAM16
std::vector<bool> QAMDemodulator::demodulateQAM16(std::vector<std::complex<double>> symbols) {
    std::vector<bool> bits;
    for (const auto& symbol : symbols) {
        double realPart = symbol.real();
        double imagPart = symbol.imag();

        // Quantiation to the nearest levels -3, -1, 1, 3
        int nearestReal = std::round((realPart + 3) / 2.0) * 2 - 3;
        int nearestImag = std::round((imagPart + 3) / 2.0) * 2 - 3;

        int index = ((nearestImag + 3) / 2) << 2 | ((nearestReal + 3) / 2);

        // dec to bin
        bits.push_back((index & 0b1000) != 0);
        bits.push_back((index & 0b0100) != 0);
        bits.push_back((index & 0b0010) != 0);
        bits.push_back((index & 0b0001) != 0);
    }

    return bits;
}

// demodulate QAM64
std::vector<bool> QAMDemodulator::demodulateQAM64(std::vector<std::complex<double>> symbols) {
    std::vector<bool> bits;
    for (const auto& symbol : symbols) {
        double realPart = symbol.real();
        double imagPart = symbol.imag();
        
        // Quantization to the nearest levels -7, -5, -3, -1, 1, 3, 5, 7
        int nearestReal = std::round((realPart + 7) / 2.0) * 2 - 7;
        int nearestImag = std::round((imagPart + 7) / 2.0) * 2 - 7;

        int index = ((nearestImag + 7) / 2) << 3 | ((nearestReal + 7) / 2);

        // dec to bin
        bits.push_back((index & 0b100000) != 0);
        bits.push_back((index & 0b010000) != 0);
        bits.push_back((index & 0b001000) != 0);
        bits.push_back((index & 0b000100) != 0);
        bits.push_back((index & 0b000010) != 0);
        bits.push_back((index & 0b000001) != 0);
    }

    return bits;
}

