#include "../headers/CTriangle.h"
#include <iostream>

// Constructor
CTriangle::CTriangle(CPoint point_1, CPoint point_2, CPoint point_3) {
   points.push_back(point_1);
   points.push_back(point_2);
   points.push_back(point_3);

   CLine l1(point_1, point_2);
   CLine l2(point_2, point_3);
   CLine l3(point_3, point_1);
   lines.push_back(l1);
   lines.push_back(l2);
   lines.push_back(l3);

   perimeter = lines[0].get_length() + lines[1].get_length() + lines[2].get_length();
}

// Destructor
CTriangle::~CTriangle() {
    // Destructor implementation, if needed
}

void CTriangle::print_info() const {
    std::cout << "Perimeter: " << perimeter << "\n";
}