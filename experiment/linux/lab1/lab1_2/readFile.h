//
// Created by 孙建钊 on 2022/9/27.
//

#ifndef BF_SEARCH_READFILE_H
#define BF_SEARCH_READFILE_H

#include <fstream>
using namespace std;


class readFile{ //读取文件
private:
    ifstream infile; //文件变量
    int lines;//获取的文件行数
    void Lines(); //获取文件行数的函数
public:
    readFile();
    readFile(std::string filePath);
    int getLines(); //返货lines的值
    string getNextLine(); //返回下个字符串，返回空表示已经读完
};

#endif //BF_SEARCH_READFILE_H
