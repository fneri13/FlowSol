#include "../../include/CGeometry/CSquare.h"
#include "../../utils/functions_algebra.cpp"
#include <iostream>

// Constructor
CSquare::CSquare(CPoint point_1, CPoint point_2, CPoint point_3, CPoint point_4) {
    points.push_back(point_1);
    points.push_back(point_2);
    points.push_back(point_3);
    points.push_back(point_4);

    CLine l1(point_1, point_2);
    CLine l2(point_2, point_3);
    CLine l3(point_3, point_4);
    CLine l4(point_4, point_1);

    lines.push_back(l1);
    lines.push_back(l2);
    lines.push_back(l3);
    lines.push_back(l4);

    CTriangle t1(point_1, point_2, point_4);
    CTriangle t2(point_2, point_3, point_4);

    triangles.push_back(t1);
    triangles.push_back(t2);
}

// Destructor
CSquare::~CSquare() {
    // Destructor implementation, if needed
}

void CSquare::printInfo() const {
    std::cout << "Perimeter: " << perimeter << "\n";
    std::cout << "Area: " << area << "\n";
    std::cout << "Normal versor: (" << normal_versor[0] << "," << normal_versor[1] << "," << normal_versor[2] << ")\n";
    std::cout << "Baricenter: \n";
    baricenter.printInfo();
}

void CSquare::computeArea() {
   
}

void CSquare::computeNormal() {
    
}