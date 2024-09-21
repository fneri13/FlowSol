#ifndef CLINE_H
#define CLINE_H
#include <vector>
#include "CPoint.h"

class CLine {
private:
    std::vector<CPoint> line;
    CPoint mid_point;
    double length;
    std::vector<double> direction_vector;
    std::vector<double> versor;

public:
    CLine(CPoint p1, CPoint p2);

    // Destructor
    ~CLine();
    void computeMidPoint();
    void printInfo() const;
    double getLength() const;
    std::vector<double> getDirectionVector() const;
};

#endif // CLINE_H
