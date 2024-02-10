#ifndef CLINE_H
#define CLINE_H
#include <vector>
#include "CPoint.h"

class CLine {
private:
    std::vector<CPoint> line;
    // CPoint mid_point;

public:
    CLine(CPoint p1, CPoint p2);

    // Destructor
    ~CLine();

    void printInfo();

    CPoint compute_mid_point();

    void print_info() const;
};

#endif // CLINE_H
