#include <iostream>

int main(int argc, char* argv[]) {
    // Printing command-line arguments
    std::cout << "Number of arguments: " << argc << std::endl;
    std::cout << "Argument values:" << std::endl;
    for (int i = 0; i < argc; ++i) {
        std::cout << "argv[" << i << "]: " << argv[i] << std::endl;
    }

    // Your code here

    return 0;
}
