main:bplus_node.o main.o
	g++ -o main bplus_node.o main.o

main.o:main.cpp
	g++ -c -o main.o main.cpp

bplus_node.o:bplus_node.cpp
	g++ -c -o bplus_node.o bplus_node.cpp

clean:
	rm *.o main
