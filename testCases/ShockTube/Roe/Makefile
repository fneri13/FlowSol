# Compiler flags
FLAGS = -std=c++17 -Wall
FLAGS_DBG = -std=c++17 -Wall -g

# Targets
all: main

debug: FLAGS = $(FLAGS_DBG)
debug: main

main: main.o OneDimensionalFV.o RoeScheme.o
	@echo "Linking the object files"
	g++ $(FLAGS) main.o OneDimensionalFV.o RoeScheme.o -o main

main.o: main.cpp
	@echo "Compiling the main file"
	g++ $(FLAGS) -c main.cpp

OneDimensionalFV.o: ../../../src/classes/CGeometry/OneDimensionalFV.cpp
	@echo "Compiling geometry class file"
	g++ $(FLAGS) -c ../../../src/classes/CGeometry/OneDimensionalFV.cpp

RoeScheme.o: ../../../src/classes/CGeometry/RoeScheme.cpp
	@echo "Compiling roe scheme file"
	g++ $(FLAGS) -c ../../../src/classes/CGeometry/RoeScheme.cpp

# Clean target to remove object and executable files
clean:
	@echo "Removing everything but the source files"
	rm *.o
	rm main