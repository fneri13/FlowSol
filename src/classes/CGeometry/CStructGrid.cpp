#include "../../include/CGeometry/CStructGrid.h"
#include "../../utils/functions_algebra.h"
#include <iostream>

CStructGrid::CStructGrid(std::vector<std::vector<double>> x, std::vector<std::vector<double>> y){
    xGrid = x;
    yGrid = y;
    ni = xGrid.size();
    nj = yGrid[0].size();
}

void printArray(std::vector<std::vector<double>> arr){
    int nx = arr.size();
    int ny = arr[0].size();
    for (int i=0; i<nx; i++){
        std::cout << "[ ";
        for (int j=0; j<ny; j++){
            std::cout << arr[i][j] << " ";
        }
        std::cout << "]" << std::endl;
    }
    std::cout << std::endl;
}


void CStructGrid::printInfo() const{
    
    printArray(xGrid);
    printArray(yGrid);

}

void CStructGrid::generateDualGrid(){
    for (int i=0; i<ni+1; i++){
        for (int j=0; j<nj+1; j++){
            break;
        }
    }
}