//
// Created by 孙建钊 on 2022/10/13.
//

#include <iostream>
#include "bplus_node.h"

int bplus_node::m = 3;
int bplus_node::treeNodeNum = 0;
int bplus_node::saveKeyNum = 0;

bplus_node::bplus_node(bplus_node *parent, bool is_leaf_node) {
    treeNodeNum++; //创建的树节点的个数
    key_num = 0; //初始化的时候没有关键字
    keys = new key_type[m+1];
    if(is_leaf_node) child = nullptr; //此时表示是叶子节点，则子节点指针数组设置为空
    else {//此时是内部节点，需要动态申请子节点指针
        child = new bplus_node *[m+1] ;
        for(int i = 0 ; i <= m; i++) child[i] = nullptr;
    }
    this->parent = parent; //设置父节点，如果是头节点的话，传进来则为NULL
    next = nullptr;//兄弟节点先设置为空，后续再进行设置
}

//初始化头节点
void bplus_node::init_head(int m){
    this->parent = nullptr;//父节点为空
    this->key_num = 1;//其key_num只能等于1，因为其永远只有有一个孩子节点，也就是root节点
    bplus_node::m = m;//设置阶数
    bplus_node::treeNodeNum = 0;//设置树中总的节点数为0
    bplus_node::saveKeyNum = 0; //设置树中保存的元素的个数为0
    bplus_node *root = new bplus_node(this,true);//初始的root是叶子节点，但是其内部元素为空
    this->child[this->key_num-1] = root;//设置其孩子节点为root节点
}

void bplus_node::insert_node(key_type key){
    saveKeyNum++;//存储的元素的个数
    bplus_node *root = this->child[0];
    bplus_node *now = root;//表示当前遍历到的节点
    while(true){
        if(now->key_num != 0 && now->child != nullptr && key > now->keys[now->key_num-1]){//说明此时key大于当前节点的最大值需要更换最大值,必须是内部节点才更换
            now->keys[now->key_num-1] = key;
        }
        if(now->child == nullptr){//说明当前遍历到了叶子节点，则需要将内容存放到该叶子节点中
            insert_key(now,key);//向now节点的keys数组中插入一个key，使其仍旧保持有序,同时令now->key_num++
            if(now->key_num > m){//此时说明该节点中存放的内容已经超过了允许存放的最大大小，需要将该节点进行分裂了
                division_node(now); //对该节点进行递归向上分裂
            }
            break;
        }
        int child_index = get_the_next_child(now,key);
        now = now->child[child_index];
    }
}

void bplus_node::insert_key(bplus_node *now,key_type key){
    now->key_num++; //加入了key之后该key_num需要自增
    now->keys[now->key_num-1] = key; //将key首先放到keys的最后移位
    for(int i = now->key_num - 1; i > 0; --i){//从后往前遍历keys，查看keys是否有序
        if(now->keys[i] < now->keys[i-1]){//说明此时顺序不对，调换二者的顺序
            key_type temp = now->keys[i];
            now->keys[i] = now->keys[i-1];
            now->keys[i-1]=temp;
        }
        else break; //一旦第一次遇到有序，则直接退出，因为每次只是插入一个值，因此遇到有序则说明插入的值的位置已经调对了
    }
}

void bplus_node::division_node(bplus_node *now){
    if(now->parent->parent == nullptr){//说明此时now是root也就是根节点，因为该节点需要分裂，则需要对其创建一个新的父节点
        bplus_node *new_parent = new bplus_node(now->parent, false); //这个一定不是叶子节点，因此此时是root节点
        new_parent->key_num = 1;
        //更新新的root节点的keys和child
        new_parent->keys[new_parent->key_num-1] = now->keys[now->key_num-1];
        new_parent->child[new_parent->key_num-1] = now;
        //更新head节点
        now->parent->child[0] = new_parent;
        //更新分裂的节点的父亲
        now->parent = new_parent;
    }
    bplus_node *new_node = new bplus_node(now->parent,now->child == nullptr);//创建新节点，用于分别，如果child为空，说明需要创建的是叶子节点
    int mid = now->key_num / 2; // 从这个下标开始往后的数据都是放到新开辟的节点中
    for(int i = mid; i < now->key_num; ++i){
        new_node->keys[i-mid] = now->keys[i];
        if(now->child != nullptr) {//对于内部节点，还需要进行child的赋值
            new_node->child[i-mid] = now->child[i];//只有内部节点才进行child的复制
            now->child[i]->parent = new_node;  //还要让孩子节点的parent指向父亲
        }
    }
    //更新二者的next
    new_node->next = now->next;
    now->next = new_node;
    //更新新旧节点的key_num
    new_node->key_num = now->key_num - mid;
    now->key_num = mid;//设置原先节点的大小

    int k = 0;
    for(int i = 0; i < now->parent->key_num; i++){
        if(now == now->parent->child[i]){
            k = i +1;
            break;
        }
    }
    insert_child(now->parent,new_node,k);//添加节点，也就是新节点应该放到child[k]上
}

int bplus_node::get_the_next_child(bplus_node *now,key_type key){
    for(int i = 0; i < now->key_num - 1; ++i){ //从前向后进行查询，遇到大于等于该内容的返回
        if(key <= now->keys[i]) return i;
    }
}

void bplus_node::printf(bplus_node *now){
    if(now->child == nullptr){
        for(int i = 0; i < now->key_num; ++i){
            cout<<now->keys[i]<<" ";
        }
        return ;
    }
    for(int i = 0; i < now->key_num;i++){
        printf(now->child[i]);
    }
}

void bplus_node::insert_child(bplus_node *now,bplus_node *new_child,int k){
    now->key_num ++;
    for(int i = now->key_num - 2; i >= k; --i){
        now->keys[i+1] = now->keys[i];
        now->child[i+1] = now->child[i];
    }
    now->child[k] = new_child;
    now->keys[k] = new_child->keys[new_child->key_num-1];
    now->keys[k-1] = now->child[k-1]->keys[now->child[k-1]->key_num-1];
    if(now->key_num > m){
        division_node(now);
    }
}

int bplus_node::query(key_type key){
    bplus_node *now = this->child[0];
    int count = 0;
    while(true){
        count++;
        int index = 0; //找到大于等于key的第一个keys
        for(int i = 0; i < now->key_num; ++i){
            if(key <= now->keys[i]){
                index = i;
                break;
            }
        }
        if(now->child== nullptr){//说明这是叶子节点
            if(key == now->keys[index]) return count;//找到了
            else return -1;//没找到
        }
        else{//内部节点
            now = now->child[index];//接续下次循环
        }
    }
}

void bplus_node::recurFree(bplus_node *now){
    if(now->child == nullptr){
        delete []now->keys;
        delete now;
        return ;
    }
    for(int i = 0; i < now->key_num; ++i){
        recurFree(now->child[i]);
    }
    delete []now->keys;
    delete []now->child;
    delete now;
}

void bplus_node::close(bplus_node *sqt){
    recurFree(this->child[0]);
    delete this;
    delete sqt;
}