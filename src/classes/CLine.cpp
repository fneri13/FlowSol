#include "../headers/CLine.h"
#include <iostream>

// Constructor
CLine::CLine(CPoint p1, CPoint p2) {
    line.push_back(p1);
    line.push_back(p2);
    compute_mid_point();
    
    double dx = line[1].getX() - line[0].getX();
    double dy = line[1].getY() - line[0].getY();
    double dz = line[1].getZ() - line[0].getZ();
    
    length = sqrt(dx * dx + dy * dy + dz * dz);
    
    if (length != 0.0) {
        versor.push_back(dx / length);
        versor.push_back(dy / length);
        versor.push_back(dz / length);

        direction_vector.push_back(dx);
        direction_vector.push_back(dy);
        direction_vector.push_back(dz);
    } else {
        // Handle the case where the length is zero (to avoid division by zero)
        versor.push_back(0.0);
        versor.push_back(0.0);
        versor.push_back(0.0);
        
        direction_vector.push_back(0.0);
        direction_vector.push_back(0.0);
        direction_vector.push_back(0.0);
    }
}

// Destructor
CLine::~CLine() {
    // Destructor implementation, if needed
}

// Compute mid point
void CLine::compute_mid_point() {
    double mid_x = (line[0].getX() + line[1].getX()) / 2.0;
    double mid_y = (line[0].getY() + line[1].getY()) / 2.0;
    double mid_z = (line[0].getZ() + line[1].getZ()) / 2.0;
    mid_point.setX(mid_x);
    mid_point.setY(mid_y);
    mid_point.setZ(mid_z);
}

// Print information about the line
void CLine::print_info() const {
    std::cout << "Line endpoints:" << std::endl;
    std::cout << "Point 1: ";
    line[0].printInfo();
    std::cout << "Point 2: ";
    line[1].printInfo();
    std::cout << "Midpoint: ";
    mid_point.printInfo();
    std::cout << "Length: " << length << "\n";
    std::cout << "Versor: (" << versor[0] << ", " << versor[1] << ", " << versor[2] << ")" << std::endl;
    

}

double CLine::get_length() const {
    return length;
}

std::vector<double> CLine::get_direction_vector() const{
    return direction_vector;
}