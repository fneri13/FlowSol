#include <stdio.h>
#include <omp.h>
#include <vector>
#include <iostream>
#include <fstream>

void writeMatrixToDatFile(const std::vector<std::vector<double>>& matrix, const std::string& filename) {
    std::ofstream outFile(filename);

    if (!outFile) {
        std::cerr << "Error: Could not open file " << filename << " for writing.\n";
        return;
    }

    // Write matrix elements to the file
    for (const auto& row : matrix) {
        for (const auto& element : row) {
            outFile << element << " ";  // Separate elements with a space
        }
        outFile << "\n";  // Newline after each row
    }

    outFile.close();
    std::cout << "Matrix written to " << filename << "\n";
}


int main (int argc, char *argv[]){
    // iterations max of the mandelbrot function
    int max_iters = 100;

    // size of the picture to be saved
    int i_size = 2500;
    int j_size = 2500;

    // Complex plane domain
    double min_re = -2.0;
    double max_re = 0.7;
    double min_im = -1.2;
    double max_im = 1.2;

    std::vector<std::vector<double>> picture (i_size);
    for (int i=0; i<i_size; i++){picture.at(i).resize(j_size);}

    double d_re = (max_re - min_re) / (i_size-1);
    double d_im = (max_im - min_im) / (j_size-1);

    #pragma omp parallel for collapse(2) schedule(runtime)
        for (int i=0; i<i_size; i++){
            for (int j=0; j<j_size; j++){
                double c_re = min_re + i*d_re;
                double c_im = min_im + j*d_im;
                double z_re = 0.0;
                double z_im = 0.0;
                double iters=0;
                while ((z_re*z_re+z_im*z_im <=4) && (iters<max_iters)){
                    double new_z_re = z_re*z_re-z_im*z_im + c_re;
                    double new_z_im = 2*z_re*z_im+c_im;
                    z_re = new_z_re;
                    z_im = new_z_im;
                    iters += 1.0;
                }
                picture[i][j] = static_cast<double> (iters/max_iters);
            }
        }    

    writeMatrixToDatFile(picture, "mandelbrot.dat");

    return 0;
}