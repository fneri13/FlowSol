#ifndef ONEDIMENSIONALFV_H
#define ONEDIMENSIONALFV_H
#include <vector>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <iomanip>


class OneDimensionalFV {
private:
    double* x {nullptr};
    double* rho {nullptr};
    double* u {nullptr};
    double* p {nullptr};
    double* e {nullptr};
    double* U1 {nullptr};
    double* U2 {nullptr};
    double* U3 {nullptr};
    double gmma {1.4};
    double dt {0.0};
    double CFL {0.0};
    int nPointsHalo {0};
    double length {0.0};
    double dx {0.0};
    unsigned short BC_type {0};

public:
    OneDimensionalFV(double length, int nPoints);
    ~OneDimensionalFV();

    /*
    Instantiate the base data structure
    */
    void InstantiateDataArrays();
    
    /*
    Print the asic data structure
    */
    void PrintDataOnScreen();

    /*
    Set left and right values on the 1D-domain
    */
    void SetLeftRightInitialCondition(double rhoL, double rhoR, double uL, double uR, double pL, double pR);
    
    /*
    Set a certain Boundary condition for the problem
    */
    void SetBoundaryConditions(unsigned short);
    
    /*
    Set reflective boundary conditions on the primitive variables, and update the conservative variables
    */
    void SetReflectiveBoundaryConditions();

    /*
    Given the current primitive variables, compute the conservative ones
    */
    void ComputeConservatives();

    /*
    Compute conservatives from the specified input to the specified outputs
    */
    void ConsFromPrim(const double *rho, const double *u, const double *p, const double *e, double *U1, double *U2, double *U3);

    void SolveSystem(double timeMax, double cflMax, int method);

    double ComputeTimeStep(double cflMax);

    double* ComputeFluxVector(int il, int ir, int method);

    void WriteResults();
};

#endif // ONEDIMENSIONALFV_H