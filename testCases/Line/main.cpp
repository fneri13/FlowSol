#include <iostream>
#include "../../src/include/CGeometry/CLine.h"
#include "../../src/include/CGeometry/CPoint.h"

int main(int argc, char* argv[]) {

    CPoint point_1(0.0, 0.0, 0.0);
    CPoint point_2(1.0, 2.0, 3.0);
    CPoint point_3(-2.0, 3.0, -4.0);
    
    CLine line1(point_1, point_2);
    std::cout<< "\nLine 1 =========================\n";
    line1.printInfo();
    
    CLine line2(point_2, point_3);
    std::cout<< "\nLine 2 =========================\n";
    line2.printInfo();
    
    CLine line3(point_3, point_1);
    std::cout<< "\nLine 3 =========================\n";
    line3.printInfo();
    

    return 0;
}
