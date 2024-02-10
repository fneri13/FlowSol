#include <iostream>
#include "../classes/CPoint.cpp"
#include "../classes/CLine.cpp"
#include "../classes/CTriangle.cpp"

int main(int argc, char* argv[]) {

    CPoint point_1(0.0, 0.0, 0.0);
    CPoint point_2(0.0, 1.0, 0.0);
    CPoint point_3(1.0, 0.0, 0.0);
    
    CTriangle triangle(point_1, point_2, point_3);
    triangle.print_info();
    
    return 0;
}
