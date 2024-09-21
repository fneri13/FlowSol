FLAGS = -std=c++17 -Wall

all: main.o CPoint.o CLine.o CTriangle.o
	@echo "Linking the objects file"
	g++ $(FLAGS) main.o CPoint.o Cline.o CTriangle.o -o main
	echo "Deleting the object files"

debug: main.o CPoint.o CLine.o CTriangle.o
	@echo "Linking the objects file debug mode"
	g++ $(FLAGS) -g main.o CPoint.o Cline.o CTriangle.o -o main
	echo "Deleting the object files"
	
main.o: 
	@echo "Compiling the main file"
	g++ $(FLAGS) -c main.cpp

CPoint.o:
	@echo "Compiling the CPoint.cpp file"
	g++ $(FLAGS) -c ../../src/classes/CGeometry/CPoint.cpp

CLine.o:
	@echo "Compiling the CLine.cpp file"
	g++ $(FLAGS) -c ../../src/classes/CGeometry/CLine.cpp

CTriangle.o:
	@echo "Compiling the CTriangle.cpp file"
	g++ $(FLAGS) -c ../../src/classes/CGeometry/CTriangle.cpp

clean:
	@echo "Removing everything but the source files"
	rm *.o 
	rm main