#ifndef NOISE_HPP
#define NOISE_HPP
#include <vector>
#include <complex>
#include <random>

class GaussianNoiseAdder {
public:
    GaussianNoiseAdder(double sigma);
    ~GaussianNoiseAdder();
    std::vector <std::complex<double>> addNoise(const std::vector<std::complex<double>>& symbols);

private:
    double sigma;
};

#endif