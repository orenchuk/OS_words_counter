all: make

make: main.cpp Counter.cpp Timer.cpp
	g++ -std=c++14 main.cpp Counter.cpp Timer.cpp -o counter -lboost_system -Og
.PHONY: clean

clean: 
	rm counter
