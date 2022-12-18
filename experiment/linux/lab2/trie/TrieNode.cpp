//
// Created by 孙建钊 on 2022/10/14.
//

#include <cstring>
#include <valarray>
#include "TrieNode.h"


int TrieNode::m = 2;//默认为2分支的trie树
int TrieNode::treeNodeNum = 0;
int TrieNode::saveKeyNum = 0;

TrieNode::TrieNode(int nodeKind){
    treeNodeNum++;
    this->nodeKind = nodeKind;
    if(nodeKind == 0){//分支节点
        ptr = new TrieNode * [m+1];
        for(int i = 0; i <= m; i++){
            ptr[i] = nullptr;
        }
    }
    else{//叶子节点

    }
}

void TrieNode::init() {
    this->treeNodeNum = 0;
    this->saveKeyNum = 0;
}

int TrieNode::query(string value){
    TrieNode *now = this;
    char *ch = new char[value.length()+1];
    strcpy(ch,value.c_str());
    int n = log(m)/log(2);//也就是每次移动几位
    int count = 0; //记录查询的次数
    for(int i = 0; i < strlen(ch)*8; i += n){
        count++;
        int num = 0;//表示当前n位二进制的大小
        for(int j = 0 ; j < n; j++){
            num *= 2;
            num += ( ch[(j+i)/8]>>(7-(j+i)%8) & 1 );
        }
        //因为索引0表示的是$
        num++; //所以加1
        if(now->ptr[num] == nullptr) return -1;//说明一定是找不到的情况
        if(i == strlen(ch)*8 - n){//说明这是最后一次遍历了
            if(now->ptr[num]->nodeKind == 1){//叶子节点
                if(now->ptr[num]->value == value) return ++count;
                else return -1;
            }
            else{//内部节点
                if(now->ptr[num]->ptr[0] != nullptr && now->ptr[num]->ptr[0]->value == value) return ++count;
                else return -1;//找不到
            }
        }
        else{//不是最后一次遍历
           if(now->ptr[num]->nodeKind == 1){//不是最后一次遍历遇到了叶子节点，说明找不到
               return -1;
           }
           now = now->ptr[num];
        }
    }
}

void TrieNode::insert_node(string value){
    saveKeyNum ++;
    TrieNode *now = this;
    char *ch = new char[value.length()+1];
    strcpy(ch,value.c_str());
    int n = log(m)/log(2);//也就是每次移动几位
    for(int i = 0; i < strlen(ch)*8; i += n){
        int num = 0;//表示当前n位二进制的大小
        for(int j = 0 ; j < n; j++){
            num *= 2;
            num += ( ch[(j+i)/8]>>(7-(j+i)%8) & 1 );
        }
        //因为索引0表示的是$
        num++; //所以加1
        if(i == strlen(ch)*8 - n){//说明这是最后一次遍历了
            if(now->ptr[num] == nullptr){//为空，则可以直接插入叶子节点
                TrieNode *new_node = new TrieNode(1);//
                new_node->value = value;//设置叶子节点的值
                now->ptr[num] = new_node;
            }
            else{//不为空，说明已经有了内部节点
                if(now->ptr[num]->nodeKind == 1){//若是叶子节点，则表明刚插入的这个值，之前就存在
                    //这里在那时不进行操作，也就是不重复进行插入
                }
                else{//将该节点放到下一层对应节点的ptr[0]上
                    TrieNode *new_node = new TrieNode(1);//
                    new_node->value = value;//设置叶子节点的值
                    now->ptr[num]->ptr[0] = new_node;
                }
            }
        }
        else{
            if(now->ptr[num] == nullptr){//说明还没有进行开辟
                now->ptr[num] = new TrieNode(0);//开辟为内部节点
                now = now->ptr[num];//更改now,指向下一层
            }
            else{//说明已经开辟了，查看其next是叶子还是内部
                TrieNode *temp = now->ptr[num];
                if(temp->nodeKind == 1){//叶子节点
                    //创建新的分支节点
                    TrieNode *new_node = new TrieNode(0);
                    new_node->ptr[0] = now->ptr[num];//将叶子节点放到下一层的node中的ptr的第一个位置
                    now->ptr[num] = new_node;
                    now = now->ptr[num];//更改now的值，用于下次循环
                }
                else{//内部节点
                    now = now->ptr[num];//更改now，指向下一层
                }
            }
        }
    }

}