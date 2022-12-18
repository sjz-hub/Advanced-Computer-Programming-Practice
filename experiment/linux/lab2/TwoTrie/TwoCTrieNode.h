//
// Created by 孙建钊 on 2022/10/15.
//

#ifndef TWOCTRIE_TWOCTRIENODE_H
#define TWOCTRIE_TWOCTRIENODE_H

#include <string>

using namespace std;

class TwoCTrieNode {
public:
    static int treeNodeNum;//节点总数
    static int saveKeyNum; //存放的节点总数
    unsigned char * value; //表明当前节点存放的内容
    int length;//表明当前节点存放的内容的长度
    TwoCTrieNode *left;//左节点
    TwoCTrieNode *right;//右节点
    bool isEnd;//是否是一个终点11
    TwoCTrieNode(bool isEnd = false);//初始化函数，length=0,value=null,left=null,right=null,isEnd=false;
    void insert_node(string value);//只有root节点可以调用该函数，root节点中也会存放value，
    int query(string value);//查询，如果查询到了返回查询比较的次数，如果没有查询到，返回-1  只有root节点可以调用
};


#endif //TWOCTRIE_TWOCTRIENODE_H
