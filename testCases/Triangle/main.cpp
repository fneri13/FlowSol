#include <iostream>
#include "../../src/include/CGeometry/CPoint.h"
#include "../../src/include/CGeometry/CLine.h"
#include "../../src/include/CGeometry/CTriangle.h"

int main(int argc, char* argv[]) {

    CPoint point_1(0.0, 0.0, 0.0);
    CPoint point_2(1.0, 0.0, 0.0);
    CPoint point_3(1.0, 1.0, 1.0);
    
    CTriangle triangle(point_1, point_2, point_3);
    triangle.computeNormal();
    triangle.printInfo();

    
    return 0;
}
