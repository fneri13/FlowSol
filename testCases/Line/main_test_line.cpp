#include <iostream>
#include "../../src/include/CGeometry/CLine.h"

int main(int argc, char* argv[]) {

    CPoint point_1(0.0, 0.0, 0.0);
    CPoint point_2(1.0, 2.0, 0.0);
    CPoint point_3(0.0, 2.0, 0.0);
    
    CLine line1(point_1, point_2);
    std::cout<< "Line 1: \n";
    line1.print_info();
    
    CLine line2(point_2, point_3);
    std::cout<< "Line 2: \n";
    line2.print_info();
    
    CLine line3(point_3, point_1);
    std::cout<< "Line 3: \n";
    line3.print_info();
    

    return 0;
}
