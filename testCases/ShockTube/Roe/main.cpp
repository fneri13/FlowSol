#include <iostream>
#include "../../../src/include/CGeometry/OneDimensionalFV.h"

int main() {
    double LENGTH {1.0};
    int NX {200};
    double TIME_MAX {1.0};
    double CFL_MAX {0.5};
    double RHOL {1.0}; 
    double RHOR {0.125};
    double UL {0.0}, UR{0.0};
    double PL {1.0}, PR {0.1};
    unsigned short BCs {0};

    OneDimensionalFV domain(LENGTH, NX);
    domain.SetLeftRightInitialCondition(RHOL, RHOR, UL, UR, PL, PR);
    domain.SetBoundaryConditions(BCs);
    domain.SolveSystem(TIME_MAX, CFL_MAX, 0);
    

    return 0;
}