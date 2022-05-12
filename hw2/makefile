all: basic_interpreter

basic_interpreter: main.cpp arithmetic.o boolean.o command.o interpreter.o
	g++ -g -Wall -std=c++11 main.cpp arithmetic.o boolean.o command.o interpreter.o -o basic_interpreter

interpreter.o: interpreter.h interpreter.cpp
	g++ -g -Wall -std=c++11 -c interpreter.cpp -o interpreter.o

arithmetic.o: arithmetic.h arithmetic.cpp
	g++ -g -Wall -std=c++11 -c arithmetic.cpp -o arithmetic.o

boolean.o: boolean.h boolean.cpp
	g++ -g -Wall -std=c++11 -c boolean.cpp -o boolean.o

command.o: command.h command.cpp
	g++ -g -Wall -std=c++11 -c command.cpp -o command.o

clean:
	rm -rf *.o	
