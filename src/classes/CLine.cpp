#include "../headers/CLine.h"
#include <iostream>

// Constructor
CLine::CLine(CPoint p1, CPoint p2) {
    line.push_back(p1);
    line.push_back(p2);
    CPoint mid_point = compute_mid_point();
}

// Destructor
CLine::~CLine() {
    // Destructor implementation, if needed
}

CPoint CLine::compute_mid_point() {
    double xm, ym, zm;
    xm = 0.5 * (line[0].getX() + line[1].getX());
    ym = 0.5 * (line[0].getY() + line[1].getY());
    zm = 0.5 * (line[0].getZ() + line[1].getZ());
    CPoint mid_point(xm, ym, zm);
    return mid_point;
}

void CLine::print_info() const {
    std::cout<<"Point 1: \n";
    line[0].printInfo();

    std::cout<<"Point 2: \n";
    line[1].printInfo();

    std::cout<<"Mid Point: \n";
    // mid_point.printInfo();

}