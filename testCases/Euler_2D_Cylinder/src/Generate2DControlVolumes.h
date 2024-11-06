#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#pragma once
/*
Generate the 2-dimensional cell centered control volumes for the nodes coordinate arrays stored in xgrid and ygrid
*/
void Generate2DControlVolumes(const std::vector<std::vector<double>> &xgrid, const std::vector<std::vector<double>> &ygrid){
    int i_nodes = xgrid.size();
    int j_nodes = ygrid.at(0).size();

    int i_elems = i_nodes-1;
    int j_elems = j_nodes-1;

    std::vector<std::vector<double>> xElems (i_elems, std::vector<double> (j_elems, 0.0));
    std::vector<std::vector<double>> yElems (i_elems, std::vector<double> (j_elems, 0.0));

    for (int i=0; i<i_elems; i++){
        for (int j=0; j<j_elems; j++){
            xElems[i][j] = 0.25*(xgrid[i][j] + xgrid[i+1][j] + xgrid[i][j+1] + xgrid[i+1][j+1]);
            yElems[i][j] = 0.25*(ygrid[i][j] + ygrid[i+1][j] + ygrid[i][j+1] + ygrid[i+1][j+1]);
        }
    }

    // Output coordinates for verification
    std::cout << "\n\n--------- ELEMENTS PROPERTIES ---------\n";
    
    for (int row = 0; row < i_elems; ++row) {
        for (int col = 0; col < j_elems; ++col) {
            std::cout << "x[" << row << "][" << col << "] = " << xElems[row][col] 
                      << ", y[" << row << "][" << col << "] = " << yElems[row][col] << std::endl;
        }
    }
    std::cout << "\n-----------------------------------------\n\n";
}

