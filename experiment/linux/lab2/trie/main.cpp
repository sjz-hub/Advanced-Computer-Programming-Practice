#include <iostream>
#include <valarray>
#include <fstream>
#include "TrieNode.h"

using namespace std;
int main() {
    int mList[] = {2,4,16,256};
    for(int i = 0; i < 4; ++i){
        TrieNode::m = mList[i];
        TrieNode *head = new TrieNode(0);//内部节点
        head->init();
        string dictFile = "./dict.txt";//"./../../dict.txt";
        string wordsFile = "./words.txt";//"./../../words.txt";
        //创建树，向里面写入内容
        ifstream dictStream;
        dictStream.open(dictFile);
        string str;
        int k = 0;
        while(true){
            getline(dictStream,str);
           // cout<<str<<endl;
            if(str.empty()) break;
            head->insert_node(str);
        }
        dictStream.close();
        //查询树
        ifstream wordsStream;
        wordsStream.open(wordsFile);
        int querySuccessNum = 0;//查询到的元素的个数
        int querySuccessNodeLength = 0;//查询到的元素的个数总的比较的次数
        while(1){
            getline(wordsStream,str);
            if(str.empty()) break;
            int count = head->query(str);
            if(count != -1){
                querySuccessNum++;
                querySuccessNodeLength += count;
            }
        }
        wordsStream.close();
        cout<<"*************m="<<TrieNode::m<<"****************"<<endl;
        cout<<"平均存储开销："<<(float)TrieNode::treeNodeNum/TrieNode::saveKeyNum<<endl;
        cout<<"平均查找开销："<<(float)querySuccessNodeLength / querySuccessNum<<endl;
        cout<<"查询到的元素的个数："<<querySuccessNum<<endl;
//        head->close(sqt);
    }
    return 0;
}
