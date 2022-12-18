//
// Created by 孙建钊 on 2022/9/21.
//

#include "HashFunc.h"
//
// Created by 孙建钊 on 2022/9/21.
//


// RS Hash
unsigned int HashFunc::RSHash(char *str){
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;
    while (*str){
        hash = hash * a + (*str++);
        a *= b;
    }
    return (hash & 0x7FFFFFFF);
}
// JS Hash
unsigned int HashFunc::JSHash(char *str){
    unsigned int hash = 1315423911;
    while (*str){
        hash ^= ((hash << 5) + (*str++) + (hash >> 2));
    }
    return (hash & 0x7FFFFFFF);
}
//PJW hash
unsigned int HashFunc::PJWHash(char *str){
    unsigned int BitsInUnignedInt = (unsigned int)(sizeof(unsigned int) * 8);
    unsigned int ThreeQuarters = (unsigned int)((BitsInUnignedInt  * 3) / 4);
    unsigned int OneEighth = (unsigned int)(BitsInUnignedInt / 8);
    unsigned int HighBits = (unsigned int)(0xFFFFFFFF) << (BitsInUnignedInt - OneEighth);
    unsigned int hash = 0;
    unsigned int test = 0;
    while (*str){
        hash = (hash << OneEighth) + (*str++);
        if ((test = hash & HighBits) != 0){
            hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }
    return (hash & 0x7FFFFFFF);
}
//ELF
unsigned int HashFunc::ELFHash(char *str) {
    unsigned int hash = 0;
    unsigned int x = 0;
    while (*str)
    {
        hash = (hash << 4) + (*str++);//hash左移4位，把当前字符ASCII存入hash低四位。
        if ((x = hash & 0xF0000000L) != 0)
        {
//如果最高的四位不为0，则说明字符多余7个，现在正在存第7个字符，如果不处理，再加下一个字符时，第
            //一个字符会被移出，因此要有如下处理。
//该处理，如果最高位为0，就会仅仅影响5-8位，否则会影响5-31位，因为C语言使用的算数移位
//因为1-4位刚刚存储了新加入到字符，所以不能>>28
            hash ^= (x >> 24);
//上面这行代码并不会对X有影响，本身X和hash的高4位相同，下面这行代码&~即对28-31(高4位)位清零。
            hash &= ~x;
        }
    }
//返回一个符号位为0的数，即丢弃最高位，以免函数外产生影响。(我们可以考虑，如果只有字符，符号位不可能
    //为负)
    return (hash & 0x7FFFFFFF);
}
// BKDR Hash
unsigned int HashFunc::BKDRHash(char *str){
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;
    while (*str){
        hash = hash * seed + (*str++);
    }
    return (hash & 0x7FFFFFFF);
}
//SDBMHash
unsigned int HashFunc::SDBMHash(char *str){
    unsigned int hash = 0;
    while (*str){
        // equivalent to: hash = 65599*hash + (*str++);
        hash = (*str++) + (hash << 6) + (hash << 16) - hash;
    }
    return (hash & 0x7FFFFFFF);
}
// DJB Hash
unsigned int HashFunc::DJBHash(char *str){
    unsigned int hash = 5381;
    while (*str){
        hash += (hash << 5) + (*str++);
    }
    return (hash & 0x7FFFFFFF);
}
//DEKH hash
unsigned int HashFunc::DEKHash(char* str)
{
    char *ptr = str;
    int len = 0;
    while(*ptr){
        len++;
        *ptr++;
    }
    unsigned int hash = len;
    unsigned int i    = 0;
    while(*str){
        hash = ((hash << 5) ^ (hash >> 27)) ^ (*str++);
    }
    return hash;
}
//BP hash
//unsigned int HashFunc::BPHash(char* str){
//
//    char *ptr = str;
//    int len = 0;
//    while(*ptr){
//        len++;
//        *ptr++;
//    }
//    unsigned int hash = len;
////    unsigned int i    = 0;
//    while(*str){
//        hash = hash << 7 ^ (*str++);
//    }
//    return hash;
//}

unsigned int HashFunc::BPHash (char* str) {

    char *ptr = str;
    unsigned int len = 0;
    while(*ptr){
        len++;
        *ptr++;
    }

    unsigned int hash = len;

    for (int i = 0; i < len; str++, i++) {
        hash = (hash << 7) ^ ((int)(*str));
    }

    return hash;
}

//FNV hash
unsigned int HashFunc::FNVHash(char* str)
{
    const unsigned int fnv_prime = 0x811C9DC5;
    unsigned int hash = 0;
    unsigned int i = 0;
    while(*str){
        hash *= fnv_prime;
        hash ^= (*str++);
    }
    return hash;
}
// AP Hash
unsigned int HashFunc::APHash(char *str){
    unsigned int hash = 0;
    int i;
    for (i=0; *str; i++){
        if ((i & 1) == 0){
            hash ^= ((hash << 7) ^ (*str++) ^ (hash >> 3));
        }
        else{
            hash ^= (~((hash << 11) ^ (*str++) ^ (hash >> 5)));
        }
    }
    return (hash & 0x7FFFFFFF);
}