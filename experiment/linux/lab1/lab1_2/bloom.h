//
// Created by 孙建钊 on 2022/9/28.
//

#ifndef BF_SEARCH_BLOOM_H
#define BF_SEARCH_BLOOM_H


#include <string>
#include "Bit.h"
#include "readFile.h"

using namespace std;

class bloom{
private:
    long long int M; //计算出来的数组长度
    long long int N; //给定的字符串的个数
    float fp;//允许错误率
    int K; //hash函数个数
    Bit *bit; //位数组
    string dictPath; //字典文件路径
    readFile * file; //读取dict.txt文件变量
    int *seed; //创建不同的hash函数时使用的随机种子
public:
    bloom(float fp, string dictPath, int *seed=nullptr);
    long long int * getHashKey(const string& str, int num); //字符串 hash个数，返回该字符串的num个hash值
    uint32_t MurmurHash2(const void * key, int len, uint32_t seed);//hash的母函数
    void createDict(); //构建hash字典
    bool queryString(string str);//查询一个字符串是否存在 存在返回true 不存在返回false
    void queryFile(string filePath,string resultFile);//对一个文件的字符串进行查询 将查询到的内容放到该文件中
};

#endif //BF_SEARCH_BLOOM_H
