main:acNode.o main.o
	g++ -o main main.o acNode.o

main.o:main.cpp
	g++ -c -o main.o main.cpp

acNode.o:acNode.cpp
	g++ -c -o acNode.o acNode.cpp

clean:
	rm *.o main
