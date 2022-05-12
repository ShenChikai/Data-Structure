all:

cave: cave.cpp
	g++ -g -Wall -std=c++11 cave.cpp -o cave

company: main.cpp company.h company.cpp
	g++ -g -Wall -std=c++11 main.cpp company.h company.cpp -o runCompany

cleanCompany:
	rm runCompany

cleanCave:
	rm cave

clean:
	rm runCompany cave