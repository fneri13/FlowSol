#ifndef CPOINT_H
#define CPOINT_H
#include <vector>

class CPoint {
private:
    std::vector<double> coordinates;

public:
    CPoint(double x, double y, double z);

    // Destructor
    ~CPoint();

    // Getter methods
    double getX() const;
    double getY() const;
    double getZ() const;

    // Setter methods
    void setX(double x);
    void setY(double y);
    void setZ(double z);

    void printInfo() const;
};

#endif // CPOINT_H
