#include <iostream>
#include "../include/CGeometry/CPoint.h"
#include "../include/CGeometry/CLine.h"
#include "../include/CGeometry/CTriangle.h"

int main(int argc, char* argv[]) {

    CPoint point_1(1.0, 2.0, 3.0);
    CPoint point_2(2.0, 3.0, 4.0);
    CPoint point_3(3.0, 4.0, 5.0);
    
    std::cout<< "Point 1: \n";
    point_1.printInfo();

    std::cout<< "Point 2: \n";
    point_2.printInfo();

    std::cout<< "Point 1: \n";
    point_3.printInfo();
    
    return 0;
}
