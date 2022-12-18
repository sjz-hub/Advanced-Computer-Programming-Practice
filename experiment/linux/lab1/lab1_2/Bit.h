//
// Created by 孙建钊 on 2022/9/27.
//

#ifndef BF_SEARCH_BIT_H
#define BF_SEARCH_BIT_H


class Bit {
private:
    long long int length;//表示这个二进制数组的长度
    char *head;//使用char数组模拟位数组
    long long int charNum;//创建的char数组的长度
public:
    Bit(long long int length);
    void set(long long int index, bool value);//true表示设置为1 false表示设置为0
    bool get(long long int index); //true表示为1 false表示为0
};


#endif //BF_SEARCH_BIT_H
