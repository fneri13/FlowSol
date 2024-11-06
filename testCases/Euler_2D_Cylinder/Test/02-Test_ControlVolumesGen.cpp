#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "../src/ReadMesh.h"
#include "../src/Generate2DControlVolumes.h"

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }
    
    std::vector<std::vector<double>> X;
    std::vector<std::vector<double>> Y;
    
    try {
        ReadMeshFile(argv[1], X, Y);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    Generate2DControlVolumes(X, Y);

    return 0;
}
