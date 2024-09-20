#include "../headers/CTriangle.h"
#include "../utils/functions_algebra.cpp"
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
   
   compute_area();

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

void CTriangle::print_info() const {
    std::cout << "Perimeter: " << perimeter << "\n";
    std::cout << "Area: " << area << "\n";
    std::cout << "Normal versor: (" << normal_versor[0] << "," << normal_versor[1] << "," << normal_versor[2] << ")\n";
    std::cout << "Baricenter: \n";
    baricenter.printInfo();

}

void CTriangle::compute_area() {
    std::vector<double> vec1(3);
    std::vector<double> vec2(3);
    vec1 = lines[0].get_direction_vector();
    vec2 = lines[1].get_direction_vector();
    std::vector<double> vec3 = crossProduct(vec1, vec2);
    double mag = computeMagnitude(vec3);
    area = 0.5*mag;
}

void CTriangle::compute_normal() {
    std::vector<double> vec1(3);
    std::vector<double> vec2(3);
    vec1 = lines[0].get_direction_vector();
    vec2 = lines[1].get_direction_vector();
    std::vector<double> vec3 = crossProduct(vec1, vec2);
    normal_versor.push_back(vec3[0]/2);
    normal_versor.push_back(vec3[1]/2);
    normal_versor.push_back(vec3[2]/2);
}