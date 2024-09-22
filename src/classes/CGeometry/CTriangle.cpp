#include "../../include/CGeometry/CTriangle.h"
#include "../../utils/functions_algebra.cpp"
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

   perimeter = lines[0].getLength() + lines[1].getLength() + lines[2].getLength();
   
   computeArea();

   double x_cg = (point_1.getX() + point_2.getX() + point_3.getX())/3;
   double y_cg = (point_1.getY() + point_2.getY() + point_3.getY())/3;
   double z_cg = (point_1.getZ() + point_2.getZ() + point_3.getZ())/3;
   baricenter.setX(x_cg);
   baricenter.setY(y_cg);
   baricenter.setZ(z_cg);

}

// Destructor
CTriangle::~CTriangle() {
    // Destructor implementation, if needed
}

void CTriangle::printInfo() const {
    std::cout << "Perimeter: " << perimeter << "\n";
    std::cout << "Area magnitude: " << area << "\n";
    std::cout << "Area vector: (" << area_vector[0] << "," << area_vector[1] << "," << area_vector[2] << ")\n";
    std::cout << "Area versor: (" << area_versor[0] << "," << area_versor[1] << "," << area_versor[2] << ")\n";
    std::cout << "Baricenter Information \n";
    baricenter.printInfo();

}

void CTriangle::computeArea() {
    std::vector<double> vec1(3);
    std::vector<double> vec2(3);

    // Compute Area by means of cross product of two sides of the parallelogram
    vec1 = lines[0].getDirectionVector();
    vec2 = lines[2].getDirectionVector(); 
    std::vector<double> vec3(3);
    vec3 = crossProduct(vec1, vec2);

    // Area vector (attention to the sign. Change it in future if it doesn't agree with the convention you have in mind)
    area_vector.resize(3);
    for (size_t i=0; i<3; i++){
        area_vector.at(i) = vec3.at(i)/2.0;
    }

    // Area magnitude
    area = computeMagnitude(area_vector);

    // Area versor
    area_versor.resize(3);
    for (size_t i=0; i<3; i++){
        area_versor.at(i) = area_vector.at(i)/area;
    }

}
