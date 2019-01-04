vectf98: vectorTestFiltered.cpp
	g++ vectorTestFiltered_98.cpp -ggdb3 -O0 -o 98vectorFilt -I. -lbenchmark -lpthread
vectf: vectorTestFiltered.cpp
	g++ vectorTestFiltered.cpp -ggdb3 -O0 --std=c++11 -o vectorFilt -I. -lbenchmark -lpthread
vect: vectorTest.cpp
	g++ vectorTest.cpp -ggdb3 -O0 --std=c++11 -o vectorTest -I. -lbenchmark -lpthread
map: mapSetTest.cpp
	g++ mapSetTest.cpp -ggdb3 -O0 --std=c++11 -o mapSetTest -I. -lbenchmark -lpthread
bst: bstBenchmark.cpp
	g++ bstBenchmark.cpp -ggdb3 -O0 --std=c++11 -o bstBenchmark -I. -lbenchmark -lpthread
mystack: myStack.cpp
	g++ myStack.cpp -ggdb3 -O0 --std=c++11 -o myStack -I. -lbenchmark -lpthread

