//
// Created by 孙建钊 on 2022/9/27.
//

#include <cmath>
#include <cstring>
#include "Bit.h"

Bit::Bit(long long int length) {
    this->length = length;
    this->charNum = std::floor(float(length) / 8);
    head = new char[charNum];
    memset(head,0,charNum); //全部初始化为0

}

void Bit::set(long long int index, bool value) {
    //index是位数组的索引，所以需要转换为字符数组的索引bindex和偏移boffset
    long long int bindex = index / 8;
    int boffset = index % 8;





    if(value){//表示设置为1
        char ch = (1 <<(7 - boffset));

        head[bindex] = head[bindex] | ch;
    }
    else{
        char ch = 0;
        for(int i = 0; i < 8; i++){
            if(i != 7 - boffset){
                ch = ch | 1 << (7 - boffset);
            }
        }
        head[bindex] = head[bindex] & ch;
    }

}

bool Bit::get(long long int index) {

    long long int bindex = index / 8;
    int offset = index % 8;
    char ch = head[bindex];
    return ((ch >> (7 - offset)) & 1) != 0;


}
