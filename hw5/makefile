all: learning doublet

learning: learning.cpp
	g++ -g -Wall -std=c++11 learning.cpp -o learning

doublet: doublet.cpp heap.h
	g++ -g -Wall -std=c++11 doublet.cpp heap.h -o doublet

cleanlearning:
	rm learning

cleandoublet:
	rm doublet

clean:
	rm heap learning doublet