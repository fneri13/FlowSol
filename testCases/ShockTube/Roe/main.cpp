#include <iostream>
#include "../../../src/include/CGeometry/OneDimensionalFV.h"

int main() {
    double LENGTH {1.0};
    int NX {2500};
    double TIME_MAX {2.0};
    double CFL_MAX {0.5};
    double RHOL {1.0}; 
    double RHOR {0.125};
    double UL {.0}, UR{.0};
    double PL {1.0}, PR {0.1};
    unsigned short BCs {0};

    OneDimensionalFV domain = OneDimensionalFV(LENGTH, NX);
    // domain.PrintDataOnScreen();
    domain.SetLeftRightInitialCondition(RHOL, RHOR, UL, UR, PL, PR);
    domain.SetBoundaryConditions(BCs);
    domain.ComputeConservatives();
    domain.WriteResults();
    // domain.SolveSystem(TIME_MAX, CFL_MAX, 0);


    return 0;
}