#include "../../include/CGeometry/OneDimensionalFV.h"
#include "../../include/CGeometry/RoeScheme.h"
#include <iostream>

// Constructor
OneDimensionalFV::OneDimensionalFV(double leng, int nPoints) {
    length = leng;
    nPointsHalo = nPoints+2;
    InstantiateDataArrays();
    dx = length/(nPoints-1);
    for (int i=0; i<nPointsHalo; i++){x[i] = (i-1)*dx;}
}

//Destructor
OneDimensionalFV::~OneDimensionalFV(){
    std::cout<< "\n\n\n";
    std::cout<<"---------------- DATA STRUCTURE DEALLOCATION ----------------" << std::endl;
}

void OneDimensionalFV::InstantiateDataArrays(){
    x.resize(nPointsHalo);
    rho.resize(nPointsHalo);
    u.resize(nPointsHalo);
    p.resize(nPointsHalo);
    e.resize(nPointsHalo);
    U1.resize(nPointsHalo);
    U2.resize(nPointsHalo);
    U3.resize(nPointsHalo);
}

void OneDimensionalFV::PrintDataOnScreen(){
    std::cout << "x [m]" << std::endl;
    for (int i=0; i<nPointsHalo; i++){std::cout<<x[i]<<std::endl;}
}

void OneDimensionalFV::SetLeftRightInitialCondition(double rhoL, double rhoR, double uL, double uR, double pL, double pR){
    double xMean = x[1]+length/2;
    for (int i=0; i<nPointsHalo; i++){
        if (x.at(i)<=xMean){
            rho.at(i) = rhoL;
            u.at(i) = uL;
            p.at(i) = pL;
            e.at(i) = pL/(gmma-1.0)/rhoL;
        }
        else{
            rho.at(i) = rhoR;
            u.at(i) = uR;
            p.at(i) = pR;
            e.at(i) = pR/(gmma-1.0)/rhoR;
        }
    }
}

void OneDimensionalFV::SetBoundaryConditions(unsigned short BC){
    BC_type = BC;
    if (BC==0){
        // std::cout << "Setting Reflective Boundary Conditions" << std::endl;
        SetReflectiveBoundaryConditions();
    }
    else if (BC==1){
        // std::cout << "Setting Reflective Boundary Conditions" << std::endl;
        SetTransparentBoundaryConditions();
    }
}

void OneDimensionalFV::SetReflectiveBoundaryConditions(){
    rho.at(0) = rho.at(1);
    rho.at(nPointsHalo-1) = rho.at(nPointsHalo-2);

    u.at(0) = -u.at(1);
    u.at(nPointsHalo-1) = -u.at(nPointsHalo-2);

    p.at(0) = p.at(1);
    p.at(nPointsHalo-1) = p.at(nPointsHalo-2);

    e.at(0) = e.at(1);
    e.at(nPointsHalo-1) = e.at(nPointsHalo-2);
}

void OneDimensionalFV::SetTransparentBoundaryConditions(){
    rho.at(0) = rho.at(1);
    rho.at(nPointsHalo-1) = rho.at(nPointsHalo-2);

    u.at(0) = u.at(1);
    u.at(nPointsHalo-1) = u.at(nPointsHalo-2);

    p.at(0) = p.at(1);
    p.at(nPointsHalo-1) = p.at(nPointsHalo-2);

    e.at(0) = e.at(1);
    e.at(nPointsHalo-1) = e.at(nPointsHalo-2);
}

void OneDimensionalFV::ComputeConservatives(){
    for (int i=0; i<nPointsHalo; i++){
        U1[i] = rho[i];
        U2[i] = rho[i]*u[i];
        U3[i] = rho[i]*(0.5*u[i]*u[i]+e[i]);
    }
}

void OneDimensionalFV::ComputePrimitives(){
    for (int i=0; i<nPointsHalo; i++){
        rho[i] = U1[i];
        u[i] = U2[i]/U1[i];
        e[i] = U3[i]/rho[i]-0.5*u[i]*u[i];
        p[i] = (gmma-1)*rho[i]*e[i];
    }
}

void OneDimensionalFV::SolveSystem(double timeMax, double cflMax, int method){
        double time {0.0};
        dt = ComputeTimeStep(cflMax);
        int timeSteps = timeMax/dt;
        std::vector<double> fL (3, 0.0);
        std::vector<double> fR (3, 0.0);
        std::vector<double> U1old, U2old, U3old; // copies needed during the iterations
        int iTime = 1;
        SetBoundaryConditions(BC_type);
        ComputeConservatives();

        while (time<=timeMax){
            std::cout << "Time step " << iTime << " : " << timeSteps << std::endl;
            U1old = U1;
            U2old = U2;
            U3old = U3;
            for (int ix=1; ix<nPointsHalo-1; ix++){
                if (ix==1){
                    fL = ComputeFluxVector(ix-1, ix, method);
                    fR = ComputeFluxVector(ix, ix+1, method);
                }
                else {
                    fL = fR;
                    fR = ComputeFluxVector(ix, ix+1, method);
                }

                // here there is probbaly the need to store the old solution, otherwise there is aliasing during the calculation proceeding along x
                U1.at(ix) = U1old.at(ix) + dt/dx*(fL.at(0)-fR.at(0));
                U2.at(ix) = U2old.at(ix) + dt/dx*(fL.at(1)-fR.at(1));
                U3.at(ix) = U3old.at(ix) + dt/dx*(fL.at(2)-fR.at(2));
            }
            ComputePrimitives();
            SetBoundaryConditions(BC_type);
            WriteResults(iTime);
            time += dt;
            iTime ++;
        }

    }

std::vector<double> OneDimensionalFV::ComputeFluxVector(int il, int ir, int method){
    double rhoL = rho[il];
    double rhoR = rho[ir];
    double uL = u[il];
    double uR = u[ir];
    double pL = p[il];
    double pR = p[ir];
    std::vector<double> flux_roe (3,0.0);
    if (method==0){
        RoeScheme roe(rhoL, rhoR, uL, uR, pL, pR);
        roe.ComputeAVGVariables();
        roe.ComputeAveragedEigenvalues();
        roe.ComputeAveragedEigenvectors();
        roe.ComputeWaveStrengths();
        flux_roe = roe.ComputeFlux();
    }
    return flux_roe;
}

double OneDimensionalFV::ComputeTimeStep(double cflMax){
    CFL = cflMax;
    double max_eig {0.0};
    double a {0.0};
    double tstep {0.0};
    for (int i=0; i<nPointsHalo; i++){
        a = sqrt(p[i]*gmma/rho[i]);
        if (abs(u[i])+abs(a)>=max_eig){max_eig=abs(u[i])+abs(a);}
    }
    tstep = dx*cflMax/max_eig;
    return tstep;
}

void OneDimensionalFV::WriteResults(int iTime){
    int width = 12;
    std::filesystem::path dir = "Results";

    // Now create the directory
    std::filesystem::create_directory(dir);

    // Open the file "results/sol.dat" for writing
    std::ostringstream oss;
    oss << "Results/Sol_" << std::setw(4) << std::setfill('0') << iTime << ".dat";
    std::string filename = oss.str();
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file for writing.\n";
    }   
    file << std::setw(width) << std::left << "x"
        << std::setw(width) << std::left << "Density"
        << std::setw(width) << std::left << "Velocity"
        << std::setw(width) << std::left << "Pressure"
        << std::setw(width) << std::left << "Energy" << "\n";
    file << std::scientific << std::setw(10) << std::setprecision(3);
    for (int i = 1; i < nPointsHalo-1; ++i) {
        file << std::setw(width) << x[i]
             << std::setw(width) << rho[i]
             << std::setw(width) << u[i]
             << std::setw(width) << p[i]
             << std::setw(width) << e[i] << "\n";
    }
    
    file.close();


}