//
// Created by 孙建钊 on 2022/9/21.
//

#ifndef SHIYAN1_HASHFUNC_H
#define SHIYAN1_HASHFUNC_H


class HashFunc{
public:
    static unsigned int RSHash(char *str);
    static unsigned int JSHash(char *str);
    static unsigned int PJWHash(char *str);
    static unsigned int ELFHash(char *str); //对str求解hash
    static unsigned int BKDRHash(char *str);
    static unsigned int SDBMHash(char *str);
    static unsigned int DJBHash(char *str);
    static unsigned int DEKHash(char *str);
    static unsigned int BPHash(char *str);
    static unsigned int FNVHash(char *str);
    static unsigned int APHash(char *str);
};


#endif //SHIYAN1_HASHFUNC_H
