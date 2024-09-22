#include <iostream>
#include "../../src/include/CGeometry/CPoint.h"
#include "../../src/include/CGeometry/CSquare.h"

int main(int argc, char* argv[]) {

    CPoint point_1(0.0, 0.0, 0.0);
    CPoint point_2(1.0, 0.0, 0.0);
    CPoint point_3(1.0, 2.0, 0.0);
    CPoint point_4(0.0, 2.0, 0.0);
    
    CSquare square(point_1, point_2, point_3, point_4);
    square.printInfo();

    
    return 0;
}
