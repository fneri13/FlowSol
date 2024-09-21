FLAGS = -std=c++17 -Wall

all: main.o CPoint.o CLine.o
	@echo "Linking the objects file"
	g++ $(FLAGS) main.o CPoint.o Cline.o -o main
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

clean:
	@echo "Removing everything but the source files"
	rm *.o 
	rm main