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

public:
    CLine(CPoint p1, CPoint p2);

    // Destructor
    ~CLine();

    void compute_mid_point();

    void print_info() const;

    double get_length() const;
};

#endif // CLINE_H
