all: main.cpp Graph.cpp Graph.h
	g++ -o Graph main.cpp Graph.cpp Graph.h
clean:
	rm Graph
