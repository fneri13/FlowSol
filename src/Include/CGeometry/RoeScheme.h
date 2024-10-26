#ifndef ROESCHEME_H
#define ROESCHEME_H

#include "../Numerics/Euler_Functions.h"

class RoeScheme {
private:
    double rhoL, rhoR, uL, uR, pL, pR, eL, eR, htL, htR, U1L, U1R, U2L, U2R, U3L, U3R, gmmaGas;
    double rhoAVG, uAVG, vAVG, wAVG, hAVG, aAVG;
    double eigenvalues [5], alphas [5];
    double eigenvectors [5][5];

public:
    RoeScheme(double, double, double, double, double, double, double);
    void ComputeAVGVariables();
    void ComputeAveragedEigenvalues();
    void ComputeAveragedEigenvectors();
    void ComputeWaveStrengths();
    std::vector<double> ComputeFlux();
    
};

#endif // ROESCHEME_H