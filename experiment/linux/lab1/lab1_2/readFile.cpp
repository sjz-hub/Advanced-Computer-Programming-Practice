//
// Created by 孙建钊 on 2022/9/27.
//

#include "readFile.h"


readFile::readFile(){
    infile = static_cast<basic_ifstream<char>>(nullptr);
}

readFile::readFile(string filePath){
    infile.open(filePath);
    Lines();
    infile.close();
    infile.open(filePath);
}

int readFile::getLines(){
    return lines;
}

string readFile::getNextLine(){
    string str;
    if(getline(infile,str)){
        return str;
    }
    return "";
}

void readFile::Lines(){
    lines = 0;
    while(!getNextLine().empty()){
        lines++;
    }
}

