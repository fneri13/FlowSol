#ifndef CSTRUCTGRID_H
#define CSTRUCTGRID_H
#include <vector>

class CStructGrid {
private:
    int ni, nj;
    std::vector<std::vector<double>> xGrid, yGrid;
    std::vector<std::vector<double>> xGridDual, yGridDual;

public:
    CStructGrid(std::vector<std::vector<double>> x, std::vector<std::vector<double>> y);
    void printInfo() const;
    void generateDualGrid();
};

#endif 