all: make

make: main.cpp Counter.cpp
	g++ -std=c++14 main.cpp Counter.cpp -o counter -lboost_system -lboost_filesystem
.PHONY: clean

clean: 
	rm counter