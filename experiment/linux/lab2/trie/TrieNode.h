//
// Created by 孙建钊 on 2022/10/14.
//

#ifndef TRIE_TRIENODE_H
#define TRIE_TRIENODE_H

#include <string>
#include <iostream>

using namespace std;

class TrieNode {
public:
    static int m; //分支的个数，是2的幂次采访，ptr开辟的空间应该为m+1,第一个表示的是$也就是指向一个具体的叶子节点，表示当前已经是一个字符串了，后m个表示多少种字符
    static int treeNodeNum;//开辟的总的节点
    static int saveKeyNum;//所存储元素的个数
    int nodeKind; //0分支节点，  1叶子节点
    string value;//叶子节点用到的value值
    TrieNode **ptr;//分支节点用到的内容
    TrieNode(int nodeKind);
    void insert_node(string value);//将value插入到trie树中，只有root根节点可以调用该函数
    int query(string value);//查询value，只能root根节点调用，查不到返回-1，查到返回比较的节点的次数
    void init();//只能是head节点进行调用
};


#endif //TRIE_TRIENODE_H
