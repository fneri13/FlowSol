#include "../../include/CGeometry/CSquare.h"
#include "../../utils/functions_algebra.h"
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

    CTriangle t1(point_1, point_2, point_3);
    CTriangle t2(point_3, point_4, point_1);

    triangles.push_back(t1);
    triangles.push_back(t2);

    // Perimeter
    perimeter = 0.0;
    for (auto &lin:lines){
        perimeter += lin.getLength();
    }

    // Area
    area_vector.resize(3);
    for (size_t i=0; i<3; i++){
        area_vector.at(i) = triangles.at(0).getAreaVector().at(i) + triangles.at(1).getAreaVector().at(i); 
    }

    area = computeMagnitude(area_vector);
    area_versor.resize(3);
    for (size_t i=0; i<3; i++){
        area_versor.at(i) = area_vector.at(i)/area; 
    }

    // Baricenter
    baricenter.setX((triangles.at(0).getBaricenter().getX()*triangles.at(0).getArea() + triangles.at(1).getBaricenter().getX()*triangles.at(0).getArea())/2);
    baricenter.setY((triangles.at(0).getBaricenter().getY()*triangles.at(0).getArea() + triangles.at(1).getBaricenter().getY()*triangles.at(0).getArea())/2);
    baricenter.setZ((triangles.at(0).getBaricenter().getZ()*triangles.at(0).getArea() + triangles.at(1).getBaricenter().getZ()*triangles.at(0).getArea())/2);
    
}

// Destructor
CSquare::~CSquare() {
    // Destructor implementation, if needed
}

void CSquare::printInfo() const {
    std::cout << "Print info of the composing triangles ======================\n";
    for (auto &tr: triangles){
        tr.printInfo();
        std::cout << "\n";
    } 

    std::cout << "Print info of the global square ======================\n";
    std::cout << "Area magnitude: " << area << std::endl;
    std::cout << "Area vector: (" << area_vector[0] << "," << area_vector[1] << "," << area_vector[2] << ")\n";
    std::cout << "Area versor: (" << area_versor[0] << "," << area_versor[1] << "," << area_versor[2] << ")\n";

    std::cout << "\nPrint info of the baricenter ======================\n";
    baricenter.printInfo();
}