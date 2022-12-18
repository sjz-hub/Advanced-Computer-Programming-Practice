//
// Created by 孙建钊 on 2022/10/15.
//

#include <cstring>
#include <cmath>
#include <iostream>
#include "TwoCTrieNode.h"

int TwoCTrieNode::treeNodeNum = 0;
int TwoCTrieNode::saveKeyNum = 0;

TwoCTrieNode::TwoCTrieNode(bool isEnd){
    treeNodeNum++;
    length = 0;
    value = nullptr;
    left = nullptr;
    right = nullptr;
    this->isEnd = isEnd;

}

//如果使用的char代表一个bit，则不能直接令其 =0，来代表该位置的bit为0，因为0表示的是空，我们可以让0变为2来代替

int TwoCTrieNode::query(string value){
    TwoCTrieNode *now = this;
    char *ch = new char[value.length()*8+1];
    char *tempCh = new char[value.length() +1];
    strcpy(tempCh,value.c_str());
    for(int i = 0; i < value.length() * 8; ++i){
        if( ( ( tempCh[i/8] >> (7 - i%8) ) & 1 ) == 1 ) ch[i] = 1;
        else ch[i] = 2;
    }
    ch[value.length()*8] = '\0';
    int count = 0;//匹配的次数
    for(int i = 0; i < strlen(ch);){
        if(now == nullptr) return -1;
        if(now->length == 0) {
            if(ch[i] == 2) now = now->left;
            else now = now->right;
            continue;
        }
        if(now->length + i <= strlen(ch)){//表明当前value的长度小于等于ch没有比较的长度，可以进行比较
            char *temp = new char [now->length + 1];
            memcpy(temp,ch+i,now->length);
            temp[now->length] = '\0';
            if(strcmp(reinterpret_cast<char *>(now->value), temp) == 0){//表明和当前节点的value部分相等
//                delete temp;//释放内存空间
                ++count;
                if(now->length + i == strlen(ch)){//表明找到了结尾
                    if(now->isEnd /*&& now->str == value*/){//说明找到了
                        return count;
                    }
                    else {
                        return -1;
                    }
                }
                else {//说明ch还没有遍历完
                    i += now->length;
                    if(ch[i] == 2) now = now->left;
                    else now = now->right;
                }
            }
            else {
//                delete temp;
                return -1;//表明匹配不相等，则直接退出
            }
        }
        else {
            return -1;//此时说明没有找到，因为当前节点的value的长度大于ch没有比较的长度
        }
    }
}

void TwoCTrieNode::insert_node(string value){
    saveKeyNum++;
    TwoCTrieNode *now = this;
    char *ch = new char[value.length()*8+1];
    char *tempCh = new char[value.length() +1];
    strcpy(tempCh,value.c_str());
//    转换为0 1 字符数组
    for(int i = 0; i < value.length() * 8; ++i) {
        if (((tempCh[i / 8] >> (7 - i % 8)) & 1) == 1) ch[i] = 1;
        else ch[i] = 2;
    }
    ch[value.length()*8] = '\0';
    int i = 0;
    auto len = strlen(ch);
    while ( i < len) {
        if (ch[i] == 2){
            if (now->left == nullptr){//需要向左侧插入节点，将剩余的内容插入进去，直接结束循环
                TwoCTrieNode *new_node = new TwoCTrieNode(true);
                new_node->length = len - i;
                new_node->value = new unsigned char [new_node->length + 1];
                memcpy(new_node->value,ch+i,new_node->length);
                new_node->value[new_node->length] = '\0';
                now->left = new_node;
                break;
            }
            else
                now = now->left;//查询左节点
        }
        else {
            if (now->right == nullptr) {//向右侧插入节点，然后将剩余的内容插入进去，直接结束循环
                TwoCTrieNode *new_node = new TwoCTrieNode(true);
                new_node->length = len - i;
                new_node->value = new unsigned char[new_node->length + 1];
                memcpy(new_node->value, ch + i, new_node->length);
                new_node->value[new_node->length] = '\0';

                now->right = new_node;
                break;
            } else{
                now = now->right;
            }
        }

        // 求出匹配的位数
        int match_len = 0;
        while (match_len < now->length && i + match_len < len && ch[i + match_len] == now->value[match_len])
            ++match_len;

        i += match_len;
        if (match_len == now->length){ //表明此时当前节点的所有值都被正确匹配
            if (i == len){//表明匹配到了结尾
                now->isEnd = true; //设置成叶子节点就好
                break;
            }
            else{//表明没有匹配到结尾，继续匹配下一个节点就好

            }
        }
        else{//表明当前节点的所有值没有全部匹配成功，则需要对当前节点进行分裂
            //当前节点后半部分没有匹配成功的内容存放到new_node中
            TwoCTrieNode *new_node = new TwoCTrieNode(now->isEnd);
            new_node->length = now->length - match_len;
            new_node->value = new unsigned char [new_node->length + 1];
            memcpy(new_node->value,now->value+match_len,new_node->length);
            new_node->value[new_node->length] = '\0';
            new_node->left = now->left;
            new_node->right = now->right;

            if(new_node->value[0] == 2) {
                now->left = new_node;
                now->right = nullptr;
            }
            else{
                now->left = nullptr;
                now->right = new_node;
            }
            //更改now的内容，存放前面匹配成功的内容
            now->length = match_len;
            now->value[now->length] = '\0';
            if(i == len){//表明ch匹配到了结尾
                now->isEnd = true;
            }
            else{//表明ch也没有匹配到结尾，需要将Ch后半部分没有匹配的内容放入一个新节点
                //插入节点，存储ch后面没有匹配的内容
                TwoCTrieNode *new_value_node = new TwoCTrieNode(true);
                new_value_node->length = len - i;
                new_value_node->value = new unsigned char [new_value_node->length + 1];
                memcpy(new_value_node->value,ch+i,new_value_node->length);
                new_value_node->value[new_value_node->length] = '\0';
                new_value_node->left = nullptr;
                new_value_node->right = nullptr;
                if(new_value_node->value[0] == 2) now->left = new_value_node;
                else now->right = new_value_node;
            }
            break;
        }
    }
}