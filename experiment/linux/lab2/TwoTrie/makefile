main:main.o TwoCTrieNode.o
	g++ -o main main.o TwoCTrieNode.o

main.o:main.cpp
	g++ -c -o main.o main.cpp

TwoCTrieNode.o:TwoCTrieNode.cpp
	g++ -c -o TwoCTrieNode.o TwoCTrieNode.cpp

clean:
	rm *.o main
