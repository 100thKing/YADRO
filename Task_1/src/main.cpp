#include "include/qam.hpp"
#include "include/noise.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {

    QAMModulator qpskMod(QAMType::QPSK);
    QAMModulator QAM16Mod(QAMType::QAM16);
    QAMModulator QAM64Mod(QAMType::QAM64);

    QAMDemodulator qpskDemod(QAMType::QPSK);
    QAMDemodulator QAM16Demod(QAMType::QAM16);
    QAMDemodulator QAM64Demod(QAMType::QAM64);

    // create txt file
    std::ofstream outputFile("result.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open file: result.txt" << std::endl;
        return 1;
    }

    // Number of bits
    std::vector<bool> randomBits(100000);
    
    
    for (size_t i = 0; i < randomBits.size(); ++i) {
        randomBits[i] = rand() % 2;
    }
    for (auto bit : randomBits) {
        outputFile << bit;
    }
    outputFile << std::endl;

    // modulate
    auto symbolsQPSK = qpskMod.modulate(randomBits);
    auto symbolsQAM16 = QAM16Mod.modulate(randomBits);
    auto symbolsQAM64 = QAM64Mod.modulate(randomBits);
    
    for (auto i = 0.1; i < 2.0; i+=0.1) {
        GaussianNoiseAdder noise(i);
        outputFile << i << std::endl;

        // add noise
        auto noisySymbolsQPSK = noise.addNoise(symbolsQPSK);
        auto noisySymbolsQAM16 = noise.addNoise(symbolsQAM16);
        auto noisySymbolsQAM64 = noise.addNoise(symbolsQAM64);
        
        // demodulate
        auto bitsAfterQPSK = qpskDemod.demodulate(noisySymbolsQPSK);
        auto bitsAfterQAM16 = QAM16Demod.demodulate(noisySymbolsQAM16);
        auto bitsAfterQAM64 = QAM64Demod.demodulate(noisySymbolsQAM64);

        // data output to a file
        for (auto bit : bitsAfterQPSK) {
            outputFile << bit;
        }
        outputFile << std::endl;

        for (auto bit : bitsAfterQAM16) {
            outputFile << bit;
        }
        outputFile << std::endl;

        for (auto bit : bitsAfterQAM64) {
            outputFile << bit;
        }
        outputFile << std::endl;
    }

    // close file
    outputFile.close();
    return 0;
}
