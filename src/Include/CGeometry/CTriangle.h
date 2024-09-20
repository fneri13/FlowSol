#ifndef CTRIANGLE_H
#define CTRIANGLE_H
#include <vector>
#include "CLine.h"

class CTriangle {
private:
    std::vector<CPoint> points;
    std::vector<CLine> lines;
    double perimeter;
    double area;
    CPoint baricenter;
    std::vector<double> normal;
    std::vector<double> normal_versor;

public:
    CTriangle(CPoint point_1, CPoint point_2, CPoint point_3);
    ~CTriangle();
    void print_info() const;
    void compute_area();
    void compute_normal();
};

#endif 
