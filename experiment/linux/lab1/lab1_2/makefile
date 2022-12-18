main:bf_search.o readFile.o Bit.o bloom.o 
	g++ -o main bf_search.o readFile.o Bit.o bloom.o

bf_search.o:bf_search.cpp
	g++ -c -o bf_search.o bf_search.cpp

readFile.o:readFile.cpp
	g++ -c -o readFile.o readFile.cpp

Bit.o:Bit.cpp
	g++ -c -o Bit.o Bit.cpp

bloom.o:bloom.cpp
	g++ -c -o bloom.o bloom.cpp

clean:
	rm *.o main
