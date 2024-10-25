#include "../../include/CGeometry/OneDimensionalFV.h"
#include "../../include/CGeometry/RoeScheme.h"
#include <iostream>

// Constructor
OneDimensionalFV::OneDimensionalFV(double leng, int nPoints) {
    length = leng;
    nPointsHalo = nPoints+2;
    InstantiateDataArrays();
    dx = length/nPoints;
    for (int i=0; i<nPointsHalo; i++){x[i] = (i-1)*dx;}
}

//Destructor
OneDimensionalFV::~OneDimensionalFV(){
    std::cout<< "\n\n\n";
    std::cout<<"---------------- DATA STRUCTURE DEALLOCATION ----------------" << std::endl;

    delete [] x;
    std::cout << "X array deleted from memory" << std::endl;

    delete [] rho;
    delete [] u;
    delete [] p;
    delete [] e;
    std::cout << "Density array deleted from memory" << std::endl;
    std::cout << "Velocity array deleted from memory" << std::endl;
    std::cout << "Pressure array deleted from memory" << std::endl;
    std::cout << "Energy array deleted from memory" << std::endl;

    delete [] U1;
    delete [] U2;
    delete [] U3;
    std::cout << "U1 array deleted from memory" << std::endl;
    std::cout << "U2 array deleted from memory" << std::endl;
    std::cout << "U3 array deleted from memory" << std::endl;
}

void OneDimensionalFV::InstantiateDataArrays(){
    x = new double [nPointsHalo];
    rho = new double [nPointsHalo];
    u = new double [nPointsHalo];
    p = new double [nPointsHalo];
    e = new double [nPointsHalo];
    U1 = new double [nPointsHalo];
    U2 = new double [nPointsHalo];
    U3 = new double [nPointsHalo];
}

void OneDimensionalFV::PrintDataOnScreen(){
    std::cout << "x [m]" << std::endl;
    for (int i=0; i<nPointsHalo; i++){std::cout<<x[i]<<std::endl;}
}

void OneDimensionalFV::SetLeftRightInitialCondition(double rhoL, double rhoR, double uL, double uR, double pL, double pR){
    double xMean = x[1]+length/2;
    for (int i=0; i<nPointsHalo; i++){
        if (x[i]<=xMean){
            rho[i] = rhoL;
            u[i] = uL;
            p[i] = pL;
            e[i] = pL/(gmma-1.0)/rhoL;
        }
        else{
            rho[i] = rhoR;
            u[i] = uR;
            p[i] = pR;
            e[i] = pR/(gmma-1.0)/rhoR;
        }
    }
}

void OneDimensionalFV::SetBoundaryConditions(unsigned short BC){
    BC_type = BC;
    if (BC==0){
        std::cout << "Setting Reflective Boundary Conditions" << std::endl;
        SetReflectiveBoundaryConditions();
    }
}

void OneDimensionalFV::SetReflectiveBoundaryConditions(){
    rho[0] = rho[1];
    rho[nPointsHalo-1] = rho[nPointsHalo-2];

    u[0] = -u[1];
    u[nPointsHalo-1] = -u[nPointsHalo-2];

    p[0] = p[1];
    p[nPointsHalo-1] = p[nPointsHalo-2];

    e[0] = e[1];
    e[nPointsHalo-1] = e[nPointsHalo-2];

    ComputeConservatives();
}

void OneDimensionalFV::ComputeConservatives(){
    ConsFromPrim(rho, u, p, e, U1, U2, U3);
}

void OneDimensionalFV::ConsFromPrim(const double *density, const double *velocity, const double *pressure, const double *energy, double *cons1, double *cons2, double *cons3){
    for (int i=0; i<nPointsHalo; i++){
        U1[i] = density[i];
        U2[i] = density[i]*velocity[i];
        U3[i] = density[i]*(0.5*velocity[i]*velocity[i]+energy[i]);
    }
}

void OneDimensionalFV::SolveSystem(double timeMax, double cflMax, int method){
        double time {0.0};
        dt = ComputeTimeStep(cflMax);
        int timeSteps = timeMax/dt;
        double *fL;
        double *fR;

        while (time<=timeMax){
            std::cout << "Time step " << time/dt << ":" << timeSteps << std::endl;
            for (int ix=1; ix<nPointsHalo-1; ix++){
                if (ix==1){
                    fL = ComputeFluxVector(ix-1, ix, method);
                    fR = ComputeFluxVector(ix, ix+1, method);
                }
                else {
                    fL = fR;
                    fR = ComputeFluxVector(ix, ix+1, method);
                }
            }
            time += dt;
        }

    }

double* OneDimensionalFV::ComputeFluxVector(int il, int ir, int method){
    double rhoL = rho[il];
    double rhoR = rho[ir];
    double uL = u[il];
    double uR = u[ir];
    double pL = p[il];
    double pR = p[ir];
    double* flux_roe;
    if (method==0){
        RoeScheme roe(rhoL, rhoR, uL, uR, pL, pR, gmma);
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
    double max_eig {0};
    double a {0};
    double tstep {0};
    for (int i=0; i<nPointsHalo; i++){
        a = sqrt(p[i]*gmma/rho[i]);
        if (abs(u[i])+abs(a)>=max_eig){max_eig=abs(u[i])+abs(a);}
    }
    tstep = dx*cflMax/max_eig;
    return tstep;
}

void OneDimensionalFV::WriteResults(){
    int width = 12;
    std::filesystem::create_directory("Results");

    // Open the file "results/sol.dat" for writing
    std::ofstream file("Results/Sol.dat");
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