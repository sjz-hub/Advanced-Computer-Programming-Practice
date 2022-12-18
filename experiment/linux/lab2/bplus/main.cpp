#include <iostream>
#include <fstream>
#include "bplus_node.h"

using namespace std;
int main() {

    int mList[] = {2,4,6,8,10};
    for(int i = 0; i < 5; ++i){
        bplus_node *head = new bplus_node();
        bplus_node *sqt = new bplus_node();
        head->init_head(mList[i]);//初始化头节点
        sqt->next = head->child[0];

        string dictFile = "./dict.txt";//"./../../dict.txt";
        string wordsFile = "./words.txt";//"./../../words.txt";

        //创建B+树，向里面写入内容
        ifstream dictStream;
        dictStream.open(dictFile);
        string str;
        while(true){
            getline(dictStream,str);
            if(str.empty()) break;
            head->insert_node(str);
        }
        dictStream.close();

        //查询B+树
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
        cout<<"*************m="<<bplus_node::m<<"****************"<<endl;
        cout<<"平均存储开销："<<(float)bplus_node::treeNodeNum/bplus_node::saveKeyNum<<endl;
        cout<<"平均查找开销："<<(float)querySuccessNodeLength / querySuccessNum<<endl;
        cout<<"查询到的元素的个数："<<querySuccessNum<<endl;
        head->close(sqt);
    }


    return 0;
}
