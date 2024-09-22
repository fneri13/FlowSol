#ifndef CSQUARE_H
#define CSQUARE_H
#include <vector>
#include "CLine.h"
#include "CPoint.h"
#include "CTriangle.h"

class CSquare {
private:
    std::vector<CTriangle> triangles;
    std::vector<CPoint> points;
    std::vector<CLine> lines;
    double perimeter;
    double area;
    CPoint baricenter;
    std::vector<double> area_vector;
    std::vector<double> area_versor;

public:
    CSquare(CPoint point_1, CPoint point_2, CPoint point_3, CPoint point_4);
    ~CSquare();
    void printInfo() const;
};

#endif 
