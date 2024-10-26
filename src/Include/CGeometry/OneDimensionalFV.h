#ifndef ONEDIMENSIONALFV_H
#define ONEDIMENSIONALFV_H
#include <vector>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>


class OneDimensionalFV {
private:
    std::vector<double> x, rho, u, p, e, U1, U2, U3;
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
    Driver for the solution of the system
    */
    void SolveSystem(double timeMax, double cflMax, int method);

     /*
    Compute dt according to a cflMax specified and an approximation of max eigenvalue
    */
    double ComputeTimeStep(double cflMax);

     /*
    Compute the euler flux vector at the interface between two cells
    */
    std::vector<double> ComputeFluxVector(int il, int ir, int method);

    /*
    Write the results on .dat file
    */
    void WriteResults(int iTime);

    /*
    Compute the primitives from the conservatives
    */
    void ComputePrimitives();

};

#endif // ONEDIMENSIONALFV_H