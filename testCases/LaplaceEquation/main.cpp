#include <iostream>
#include <vector>
#include "../../src/include/CGeometry/CStructGrid.h"

int main(int argc, char* argv[]) {

    double xmax =1.0;
    double xmin =0.0;
    double ymax =0.5;
    double ymin =0.0;
    int nx {5};
    int ny {3};

    std::vector<std::vector<double>> xGrid(nx, std::vector<double>(ny));
    std::vector<std::vector<double>> yGrid(nx, std::vector<double>(ny));

    for (int i=0; i<nx; i++){
        for (int j=0; j<ny; j++){
            xGrid[i][j] = xmin + (xmax-xmin)*(static_cast<double>(i)/(nx-1));
            yGrid[i][j] = ymin + (ymax-ymin)*(static_cast<double>(j)/(ny-1));
        }
    }
    CStructGrid grid(xGrid, yGrid);
    grid.printInfo();



    

    return 0;
}