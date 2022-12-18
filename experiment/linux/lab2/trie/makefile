main:main.o TrieNode.o
	g++ -o main main.o TrieNode.o

main.o:main.cpp
	g++ -c -o main.o main.cpp

TrieNode.o:TrieNode.cpp
	g++ -c -o TrieNode.o TrieNode.cpp

clean:
	rm *.o main
