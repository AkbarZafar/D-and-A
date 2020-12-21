all: openhtdriver orderedhtdriver

openhtdriver: openhttest.cpp
	g++ -std=c++11 -o openhtdriver openhttest.cpp

orderedhtdriver: orderedhttest.cpp
	g++ -std=c++11 -o orderedhtdriver orderedhttest.cpp

clean:
	rm openhtdriver
	rm orderedhtdriver
	
