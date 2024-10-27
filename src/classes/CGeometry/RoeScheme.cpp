#include "../../include/CGeometry/RoeScheme.h"
#include <iostream>

RoeScheme::RoeScheme(double rhol, double rhor, double ul, double ur, double pl, double pr){
    rhoL = rhol;
    rhoR = rhor;
    uL = ul;
    uR = ur;
    pL = pl;
    pR = pr;
    gmmaGas = 1.4;
    eL = pL/(gmmaGas-1)/rhoL;
    eR = pR/(gmmaGas-1)/rhoR;

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
    eigenvalues.resize(5);
    eigenvalues.at(0) = uAVG - aAVG;
    eigenvalues.at(1) = uAVG;
    eigenvalues.at(2) = uAVG;
    eigenvalues.at(3) = uAVG;
    eigenvalues.at(4) = uAVG + aAVG;
}

void RoeScheme::ComputeAveragedEigenvectors(){
    eigenvectors.resize(5);
    for (int i=0; i<5; i++){ eigenvectors.at(i).resize(5);}

    eigenvectors.at(0).at(0) = 1.0;
    eigenvectors.at(1).at(0) = uAVG-aAVG; 
    eigenvectors.at(2).at(0) = 0.0;
    eigenvectors.at(3).at(0) = 0.0;
    eigenvectors.at(3).at(0) = hAVG-uAVG*aAVG;

    eigenvectors.at(0).at(1) = 1.0; 
    eigenvectors.at(1).at(1) = uAVG;
    eigenvectors.at(2).at(1) = 0.0;
    eigenvectors.at(3).at(1) = 0.0;
    eigenvectors.at(4).at(1) = 0.5*uAVG*uAVG; 

    eigenvectors.at(0).at(2) = 0.0; 
    eigenvectors.at(1).at(2) = 0.0;
    eigenvectors.at(2).at(2) = 1.0;
    eigenvectors.at(3).at(2) = 0.0;
    eigenvectors.at(4).at(2) = 0.0;

    eigenvectors.at(0).at(3) = 0.0; 
    eigenvectors.at(1).at(3) = 0.0;
    eigenvectors.at(2).at(3) = 0.0;
    eigenvectors.at(3).at(3) = 1.0;
    eigenvectors.at(4).at(3) = 0.0;

    eigenvectors.at(0).at(4) = 1.0; 
    eigenvectors.at(1).at(4) = uAVG+aAVG;
    eigenvectors.at(2).at(4) = 0.0;
    eigenvectors.at(3).at(4) = 0.0;
    eigenvectors.at(4).at(4) = hAVG+uAVG*aAVG;
}

void RoeScheme::ComputeWaveStrengths(){
    alphas.resize(5);
    alphas[0] = 0.5/aAVG/aAVG *(pR-pL-rhoAVG*aAVG*(uR-uL));
    alphas[1] = rhoR-rhoL - (pR-pL)/aAVG/aAVG;
    alphas[2] = rhoAVG*vAVG;
    alphas[3] = rhoAVG*wAVG;
    alphas[4] = 0.5/aAVG/aAVG*(pR-pL + rhoAVG*aAVG*(uR-uL));
}

std::vector<double> RoeScheme::ComputeFlux(){
    std::vector<double> fL (5, 0.0); 
    std::vector<double> fR (5, 0.0); 
    std::vector<double> fRoe (5, 0.0); 
    std::vector<double> fOneDim (3, 0.0);

    // Get flux values from EulerFlux
    fL = EulerFlux(U1L, U2L, U3L, gmmaGas);
    fR = EulerFlux(U1R, U2R, U3R, gmmaGas);

    // Compute the mean flux
    for (int i = 0; i < 5; i++) {
        fRoe.at(i) = 0.5 * (fL.at(i) + fR.at(i));
    }

    // Compute Roe flux
    for (int iDim = 0; iDim < 5; iDim++) {
        for (int jVec = 0; jVec < 5; jVec++) {
            fRoe.at(iDim) -= 0.5 * alphas.at(jVec) * abs(eigenvalues.at(jVec)) * eigenvectors.at(iDim).at(jVec);
        }
    }
    
    fOneDim.at(0) = fRoe.at(0);
    fOneDim.at(1) = fRoe.at(1);
    fOneDim.at(2) = fRoe.at(4);

    return fOneDim;
}

