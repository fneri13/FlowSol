#include <iostream>
#include "../include/CGeometry/CPoint.h"
#include "../include/CGeometry/CLine.h"
#include "../include/CGeometry/CTriangle.h"

int main(int argc, char* argv[]) {

    CPoint point_1(3.0, 4.0, 2.0);
    CPoint point_2(-4.0, 1.0, 0.1);
    CPoint point_3(2.1, 1.3, 1.2);
    
    CTriangle triangle(point_1, point_2, point_3);
    triangle.compute_normal();
    triangle.print_info();

    
    return 0;
}
