#include "../headers/CPoint.h"
#include <iostream>

// Constructor
CPoint::CPoint(double x, double y, double z) {
    coordinates.push_back(x);
    coordinates.push_back(y);
    coordinates.push_back(z);
}

// Destructor
CPoint::~CPoint() {
    // Destructor implementation, if needed
}

// Getter methods
double CPoint::getX() const {
    return coordinates[0];
}

double CPoint::getY() const {
    return coordinates[1];
}

double CPoint::getZ() const {
    return coordinates[2];
}

// Setter methods
void CPoint::setX(double x) {
    coordinates[0] = x;
}

void CPoint::setY(double y) {
    coordinates[1] = y;
}

void CPoint::setZ(double z) {
    coordinates[2] = z;
}

// Print method
void CPoint::printInfo() const {
    std::cout << "Coordinates: (" << getX() << ", " << getY() << ", " << getZ() << ")" << std::endl;
}
