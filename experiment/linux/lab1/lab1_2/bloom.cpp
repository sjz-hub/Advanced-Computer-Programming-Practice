//
// Created by 孙建钊 on 2022/9/28.
//

#include <utility>
#include <valarray>
#include <iostream>
#include "bloom.h"

using namespace std;

bloom::bloom(float fp, string dictPath, int *seed) {
    this->fp = fp;
    this->dictPath = dictPath;


    //获取n
    file = new readFile(dictPath);
    this->N = file->getLines();
    //计算k m  km都是向下取整
    M = int(N * 1.4427 * log((1 / fp)) / log(2) );
    K = int(0.693147 * M / N);


    //设置随机种子
    this->seed = new int[K];
    if(seed == nullptr){ //默认的随机种子
        for(int i = 0; i < K; i++){;
            this->seed[i] = i + 1;
        }
    }
    else{
        for(int i = 0; i < K; i++){
            this->seed[i] = seed[i];
        }
    }
    bit = new Bit(M);
    createDict();

}

long long int *bloom::getHashKey(const string& str, int num) {


    //获得字符串的长度
    int len = str.length();

    char *value = const_cast<char *>(str.c_str());

    long long int *key = new long long int[num];//创建返回的hash key值的数组

    for(int i = 0; i < num; i++){
        key[i] = MurmurHash2(value, len, seed[i]) % M;
    }

    return key;
}


//传递不同的seed
uint32_t bloom::MurmurHash2(const void * key, int len, uint32_t seed){
    const uint32_t m = 0x5bd1e995;

    const int r = 24;

    uint32_t h = seed ^ len;
    // Mix 4 bytes at a time into the hash
    const unsigned char *data = (const unsigned char *)key;
    while(len >= 4)
    {
        uint32_t k = *(uint32_t *)data;
        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }
    // Handle the last few bytes of the input array
    switch(len)
    {
        case 3: h ^= data[2] << 16;
        case 2: h ^= data[1] << 8;
        case 1: h ^= data[0];
            h *= m;
    };
    // Do a few final mixes of the hash to ensure the last few
    // bytes are well-incorporated.
    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;
    return h;

}

void bloom::createDict() {
    string str; //  每一个字典的字符串
    long long int * key; //多个hash值的key组成的数组
    while(true){
        str = file->getNextLine();
        if(str.empty()) break;//说明此时所有内容读取完毕

        key = getHashKey(str,K);

        for(int i = 0; i < K; i++){
            bit->set(key[i],true);
        }

        free(key);//释放key
    }
}

bool bloom::queryString(string str) {

    long long int * key = getHashKey(str,K);
    int isExist = true;



    for(int i = 0; i < K; i++){
        if(!bit->get(key[i])){
            isExist = false;
            break;
        }
    }

    free(key);
    return isExist;
}

void bloom::queryFile(string filePath, string resultFile) {


    readFile words = readFile(std::move(filePath));
    fstream ofs;
    ofs.open(resultFile,ios::out);




    int allneedQuery = words.getLines(); //所有需要查询的字符串
    int alreadQuery = 0; //查询到的字符串

    while(true){
        string str = words.getNextLine();
        if(str.empty()) break;
        bool isExist = queryString(str);

        //cout<<str<<" "<<isExist<<endl;
        if(isExist){
            ofs<<str<<endl;
            alreadQuery++;
        }
    }





    ofs.close();
    cout<<"所有字符串数："<<allneedQuery<<endl;
    cout<<"查询到的字符串数："<<alreadQuery<<endl;
    cout<<"实际错误率："<<(float(alreadQuery) - 49425) / 49425<<endl;
    cout<<"M:"<<M<<endl;
    cout<<"N:"<<N<<endl;
    cout<<"fp:"<<fp<<endl;
    cout<<"K:"<<K<<endl;
}
