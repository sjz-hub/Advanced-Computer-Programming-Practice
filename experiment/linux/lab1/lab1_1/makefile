main:HashFunc.o hashtable_search.o
	g++ -o main HashFunc.o hashtable_search.o

HashFunc.o:HashFunc.cpp
	g++ -c -o HashFunc.o HashFunc.cpp

hashtable_search.o:hashtable_search.cpp
	g++ -c -o hashtable_search.o hashtable_search.cpp

clean:
	rm *.o main
