main:acNode.o ELL.o LinkList.o LinkThreeDimMatrix.o closeness.o Hash.o pageRankList.o LinkMatrix.o main.o
	g++ -o main acNode.o ELL.o LinkList.o LinkThreeDimMatrix.o closeness.o Hash.o pageRankList.o LinkMatrix.o main.o

acNode.o:acNode.cpp
	g++ -c -o acNode.o acNode.cpp

ELL.o:ELL.cpp
	g++ -c -o ELL.o ELL.cpp

LinkList.o:LinkList.cpp
	g++ -c -o LinkList.o LinkList.cpp

LinkThreeDimMatrix.o:LinkThreeDimMatrix.cpp
	g++ -c -o LinkThreeDimMatrix.o LinkThreeDimMatrix.cpp

closeness.o:closeness.cpp
	g++ -c -o closeness.o closeness.cpp

Hash.o:Hash.cpp
	g++ -c -o Hash.o Hash.cpp

pageRankList.o:pageRankList.cpp
	g++ -c -o pageRankList.o pageRankList.cpp

ListMatrix.o:LinkMatrix.cpp
	g++ -c -o LinkMatrix.o LinkMatrix.cpp

main.o:main.cpp
	g++ -c -o main.o main.cpp

clean:
	rm *.o main
