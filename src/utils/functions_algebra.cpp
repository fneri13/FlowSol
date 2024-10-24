#include <vector>
#include "functions_algebra.h"

std::vector<double> crossProduct(const std::vector<double>& v1, const std::vector<double>& v2) {
    std::vector<double> result(3);
    result[0] = v1[1] * v2[2] - v1[2] * v2[1];
    result[1] = v1[2] * v2[0] - v1[0] * v2[2];
    result[2] = v1[0] * v2[1] - v1[1] * v2[0];
    return result;
}

double computeMagnitude(std::vector<double> v1) {
    double mag = 0.0;
    for (double val : v1) {
        mag += val * val;
    }
    return sqrt(mag);
}

