#ifndef CTRIANGLE_H
#define CTRIANGLE_H
#include <vector>
#include "CLine.h"
#include "CPoint.h"

class CTriangle {
private:
    std::vector<CPoint> points;
    std::vector<CLine> lines;
    double perimeter;
    CPoint baricenter;
    std::vector<double> area_vector; // the normal Area vector
    double area; // Area magnitude
    std::vector<double> area_versor; // the normal Area versor (magnitude one)

public:
    CTriangle(CPoint point_1, CPoint point_2, CPoint point_3);
    ~CTriangle();
    void printInfo() const;
    void computeArea();
};

#endif 
