#ifndef ROESCHEME_H
#define ROESCHEME_H

#include "../Numerics/Euler_Functions.h"
#include <vector>


class RoeScheme {
private:
    double rhoL, rhoR, uL, uR, pL, pR, eL, eR, htL, htR, U1L, U1R, U2L, U2R, U3L, U3R, gmmaGas;
    double rhoAVG, uAVG, vAVG, wAVG, hAVG, aAVG;
    std::vector<double> eigenvalues, alphas;
    std::vector<std::vector<double>> eigenvectors;

public:
    RoeScheme(double, double, double, double, double, double, double);
    void ComputeAVGVariables();
    void ComputeAveragedEigenvalues();
    void ComputeAveragedEigenvectors();
    void ComputeWaveStrengths();
    std::vector<double> ComputeFlux();
    
};

#endif // ROESCHEME_H