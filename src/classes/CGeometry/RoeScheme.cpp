#include "../../include/CGeometry/RoeScheme.h"
#include <iostream>

RoeScheme::RoeScheme(double rhol, double rhor, double ul, double ur, double pl, double pr, double gmma){
    rhoL = rhol;
    rhoR = rhor;
    uL = ul;
    uR = ur;
    pL = pl;
    pR = pr;
    gmmaGas = gmma;
    eL = pL/(gmma-1)/rhoL;
    eR = pR/(gmma-1)/rhoR;

    htL = ComputeTotalEnthalpy(rhoL, uL, pL, eL);
    htR = ComputeTotalEnthalpy(rhoR, uR, pR, eR);
    ComputeEulerConservatives(rhoL, uL, pL, U1L, U2L, U3L, gmmaGas);
    ComputeEulerConservatives(rhoR, uR, pR, U1R, U2R, U3R, gmmaGas);
}

void RoeScheme::ComputeAVGVariables(){
    rhoAVG = sqrt(rhoL*rhoR);
    uAVG = (sqrt(rhoL)*uL + sqrt(rhoR)*uR) / (sqrt(rhoL)+sqrt(rhoR));
    vAVG = 0.0;
    wAVG = 0.0;
    hAVG = (sqrt(rhoL)*htL + sqrt(rhoR)*htR) / (sqrt(rhoL)+sqrt(rhoR));
    aAVG = sqrt((gmmaGas-1)*(hAVG-0.5*uAVG*uAVG));
}

void RoeScheme::ComputeAveragedEigenvalues(){
    eigenvalues[0] = uAVG - aAVG;
    eigenvalues[1] = uAVG;
    eigenvalues[2] = uAVG;
    eigenvalues[3] = uAVG;
    eigenvalues[4] = uAVG + aAVG;
}

void RoeScheme::ComputeAveragedEigenvectors(){
    eigenvectors[0][0] = 1.0;
    eigenvectors[1][0] = uAVG-aAVG; 
    eigenvectors[2][0] = 0.0;
    eigenvectors[3][0] = 0.0;
    eigenvectors[4][0] = hAVG-uAVG*aAVG;

    eigenvectors[0][1] = 1.0; 
    eigenvectors[1][1] = uAVG;
    eigenvectors[2][1] = 0.0;
    eigenvectors[3][1] = 0.0;
    eigenvectors[4][1] = 0.5*uAVG*uAVG; 

    eigenvectors[0][2] = 0.0; 
    eigenvectors[1][2] = 0.0;
    eigenvectors[2][2] = 1.0;
    eigenvectors[3][2] = 0.0;
    eigenvectors[4][2] = 0.0;

    eigenvectors[0][3] = 0.0; 
    eigenvectors[1][3] = 0.0;
    eigenvectors[2][3] = 0.0;
    eigenvectors[3][3] = 1.0;
    eigenvectors[4][3] = 0.0;

    eigenvectors[0][4] = 1.0; 
    eigenvectors[1][4] = uAVG+aAVG;
    eigenvectors[2][4] = 0.0;
    eigenvectors[3][4] = 0.0;
    eigenvectors[4][4] = hAVG+uAVG*aAVG;
}

void RoeScheme::ComputeWaveStrengths(){
    alphas[0] = 1/2/aAVG*aAVG *(pR-pL-rhoAVG*aAVG*(uR-uL));
    alphas[1] = rhoR-rhoL - (pR-pL)/aAVG*aAVG;
    alphas[2] = rhoAVG*vAVG;
    alphas[3] = rhoAVG*wAVG;
    alphas[4] = 1/2/aAVG*aAVG*(pR-pL + rhoAVG*aAVG*(uR-uL));
}

double* RoeScheme::ComputeFlux(){
    // Declare pointers, but don't allocate memory if they are assigned immediately
    double* fL {nullptr}; 
    double* fR {nullptr}; 
    double* fMean = new double[5]{0.0}; // Allocate for fMean only if used
    double* fRoe = new double[5]{0.0}; // Allocate for fRoe only if used

    // Get flux values from EulerFlux
    fL = EulerFlux(U1L, U2L, 0.0, 0.0, U3L, gmmaGas);
    fR = EulerFlux(U1R, U2R, 0.0, 0.0, U3R, gmmaGas);

    // Compute the mean flux
    for (int i = 0; i < 5; i++) {
        fMean[i] = 0.5 * (fL[i] + fR[i]);
    }

    // Compute Roe flux
    for (int iDim = 0; iDim < 5; iDim++) {
        for (int jVec = 1; jVec < 5; jVec++) {
            fRoe[iDim] -= 0.5 * alphas[jVec] * abs(eigenvalues[jVec]) * eigenvectors[iDim][jVec];
        }
    }

    // Allocate fOneDim to return it correctly
    double* fOneDim = new double[3];
    fOneDim[0] = fRoe[0];
    fOneDim[1] = fRoe[1];
    fOneDim[2] = fRoe[4];

    // Clean up dynamically allocated memory
    delete[] fL;
    delete[] fR;
    delete[] fMean;
    delete[] fRoe; 

    return fOneDim; // Caller must delete this array
}
