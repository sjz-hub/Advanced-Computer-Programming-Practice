//
// Created by 孙建钊 on 2022/10/13.
//

#ifndef NODE_BPLUS_NODE_H
#define NODE_BPLUS_NODE_H

#include <string>
using namespace std;
#define key_type string
class bplus_node {
public:
    static int m;//表示阶数
    static int treeNodeNum;//树中总的结点数
    static int saveKeyNum; //树中存储的元素的个数
    int key_num; //该节点中的关键字的个数，可以看作keys[]的逻辑边界
    key_type *keys; //存放的关键字   内部节点存放的是每个孩子节点的最大值  叶子节点存放的就是各个关键字
    bplus_node **child; //子节点的指针数组，同时用于判断是否是叶子节点，为空肯定就是叶子节点，因为叶子节点没有孩子
    bplus_node *parent; // 父节点指针
    bplus_node *next;//兄弟节点，仅在叶子节点内有意义
public:
    bplus_node(bplus_node *parent= nullptr, bool is_leaf_node=false);
    void insert_node(key_type key); //向B+树中插入节点，只有head指针可以调用，head是头指针，key则是该节点所插入的内容的hash值  头指针会指向一个root，root才是真正的根节点
    void insert_key(bplus_node *now,key_type key);//向node节点的keys数组中插入一个key，使其仍旧保持有序,同时令now->key_num++,只用于叶子节点
    void division_node(bplus_node *now);//节点向上递归分裂,对节点now进行分裂，同时更新因分裂导致需要更新的所有内容
    int get_the_next_child(bplus_node *now,key_type key); //根据key的值找到now中下属节点的id,也就是应该是now->child[id]
    void insert_child(bplus_node *now,bplus_node *new_child,int k);//将new_child插入到now中的合适位置，用于内部节点，同时更新keys和key_num,新节点需要放到now->child[k]上
    void init_head(int m);//初始化头节点 传递进来阶数
    int query(key_type key);//只有head节点可以调用，头节点，不是根节点, 查找成功时返回查找的次数，查找不成功的时候返回-1
    void printf(bplus_node *now);//递归输出now及其子节点的内容
    void close(bplus_node *sqt);//释放空间，只能由head节点调用,传递进来sqt指针
    void recurFree(bplus_node *now);//递归关闭now及其子节点
};


#endif //NODE_BPLUS_NODE_H
