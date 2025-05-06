#ifndef QAM_HPP
#define QAM_HPP

#include <vector>
#include <complex>

enum class QAMType { QPSK, QAM16, QAM64 };

class QAMModulator {
public:
    QAMModulator(QAMType type);
    ~QAMModulator();
    std::vector<std::complex<double>> modulate(const std::vector<bool>& bits);

private:
    QAMType type;
    std::vector<std::complex<double>> modulateQPSK(std::vector<bool> bits);
    std::vector<std::complex<double>> modulateQAM16(std::vector<bool> bits);
    std::vector<std::complex<double>> modulateQAM64(std::vector<bool> bits);
};

class QAMDemodulator {
public:
    QAMDemodulator(QAMType type);
    ~QAMDemodulator();
    std::vector<bool> demodulate(const std::vector<std::complex<double>>& symbols);
private:
    QAMType type;
    std::vector<bool> demodulateQPSK(std::vector<std::complex<double>> symbols);
    std::vector<bool> demodulateQAM16(std::vector<std::complex<double>> symbols);
    std::vector<bool> demodulateQAM64(std::vector<std::complex<double>> symbols);
};

#endif