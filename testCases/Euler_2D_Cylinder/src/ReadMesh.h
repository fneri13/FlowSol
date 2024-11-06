#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#pragma once
void ReadMeshFile(std::string filename, std::vector<std::vector<double>> &xgrid, std::vector<std::vector<double>> &ygrid){
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open file " + filename);  // Throw an exception
    }

    int ndim = 0, i_nodes = 0, j_nodes = 0;
    std::string indexing;

    // Read metadata
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("NDIM") != std::string::npos) {
            sscanf(line.c_str(), "NDIM= %d", &ndim);
        } else if (line.find("I_NODES") != std::string::npos) {
            sscanf(line.c_str(), "I_NODES= %d", &i_nodes);
        } else if (line.find("J_NODES") != std::string::npos) {
            sscanf(line.c_str(), "J_NODES= %d", &j_nodes);
        } else if (line.find("INDEXING") != std::string::npos) {
            indexing = line.substr(line.find('=') + 2);
        } else {
            // Reached the coordinate section
            break;
        }
    }

    std::cout << "\n\n--------- MESH FILE PROPERTIES ---------\n";
    std::cout << "Number of coordinates dimensions: " << ndim << std::endl;
    std::cout << "Number of nodes along first axis i: " << i_nodes << std::endl;
    std::cout << "Number of nodes along second axis j: " << j_nodes << std::endl;
    std::cout << "Indexing order of the nodes: " << indexing << std::endl;
    std::cout << "\n----------------------------------------\n\n";

    // Initialize 2D vectors for x and y with dimensions (i_nodes, j_nodes)
    xgrid.resize(i_nodes);
    ygrid.resize(j_nodes);
    for (int i=0; i<i_nodes; i++){ 
        xgrid.at(i).resize(j_nodes);
        ygrid.at(i).resize(j_nodes);
    }
    double x_val, y_val;
    unsigned long int i=0;
    unsigned long int j=0;

    // Read coordinates
    do {
        if (sscanf(line.c_str(), "%lf %lf", &x_val, &y_val) == 2) {
            xgrid[i][j] = x_val;
            ygrid[i][j] = y_val;
            
            j++;
            if (j == j_nodes) { // End of row, move to next row
                j = 0;
                i++;
            }
            if (i == i_nodes) { // Stop if we've filled the 2D array
                break;
            }
        }
    } while (std::getline(file, line));

    file.close();


    // Output coordinates for verification
    std::cout << "Coordinates (in 2D arrays):" << std::endl;
    for (int row = 0; row < i_nodes; ++row) {
        for (int col = 0; col < j_nodes; ++col) {
            std::cout << "x[" << row << "][" << col << "] = " << xgrid[row][col] 
                      << ", y[" << row << "][" << col << "] = " << ygrid[row][col] << std::endl;
        }
    }
}

