#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>
#include "TwoCTrieNode.h"

using namespace  std;
int main() {
    TwoCTrieNode *root = new TwoCTrieNode(true);//一开始应该叶子节点
    root->value = new unsigned char[2];
    root->length = 0;
    string dictFile = "./dict.txt";//"./../../dict.txt";
    string wordsFile = "./words.txt";//"./../../words.txt";

    //创建树，向里面写入内容
    ifstream dictStream;
    dictStream.open(dictFile);
    string str;
    int k = 0;
    while(true){
        k++;
        getline(dictStream,str);
        if(str.empty()) break;
        root->insert_node(str);
    }
    dictStream.close();
    //查询树
    ifstream wordsStream;
    wordsStream.open(wordsFile);
    int querySuccessNum = 0;//查询到的元素的个数
    int querySuccessNodeLength = 0;//查询到的元素的个数总的比较的次数
    int s = 0;
    while(1){
        getline(wordsStream,str);
        if(str.empty()) break;
        s++;
        int count = root->query(str);
        if(count != -1){
            querySuccessNum++;
            querySuccessNodeLength += count;
        };
    }
    wordsStream.close();
    cout<<"平均存储开销："<<(float)TwoCTrieNode::treeNodeNum/TwoCTrieNode::saveKeyNum<<endl;
    cout<<"平均查找开销："<<(float)querySuccessNodeLength / querySuccessNum<<endl;
    cout<<"查询到的元素的个数："<<querySuccessNum<<endl;
    cout<<"总共的查询数："<<s<<endl;

    return 0;
}
