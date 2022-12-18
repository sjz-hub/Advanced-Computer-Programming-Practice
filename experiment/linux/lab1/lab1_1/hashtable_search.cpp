#include<iostream>
#include<string>
#include <fstream>
#include <utility>
//#include <mshtmlc.h>
#include <valarray>

#include "HashFunc.h"

// 可以考虑使用线性表来模拟链表
using namespace std;

int N,M,a;

class readFile{ //读取文件函数
private:
    ifstream infile;
    int lines;
    void Lines(){
        lines = 0;
        while(!getNextLine().empty()){
            lines++;
        }
    }
public:
    readFile(){
        infile = static_cast<basic_ifstream<char>>(nullptr);
    }
    readFile(string filePath){
        infile.open(filePath);
        Lines();
        infile.close();
        infile.open(filePath);
    }
    int getLines(){
        return lines;
    }
    string getNextLine(){
        string str;
        if(getline(infile,str)){
            return str;
        }
        return "";
    }
};

class linkList{//链表类
private:
    linkList *next; //指向下一个链表的指针
    string value; //该节点的值
public:
    linkList() {
        next = nullptr;
    }
    void addLink(linkList *nextLink){
        linkList *temp = next;
        next = nextLink;
        nextLink->setNext(temp);
    }
    void setNext(linkList * temp){
        next = temp;
    }
    linkList * getNext(){
        return next;
    }
    void setValue(string str) {
        value = std::move(str);
    }
    string getValue(){
        return value;
    }
};

class Hash{
private:
    readFile *file; //读取文件的指针
    linkList *hashList; //hash表的头节点
    string dictPath; //字典路径
    int selectHashFunc;//选择hash的标志
    string selectHashName;//选择的hash的名字
public:
    Hash(const string& dictPath,int selectHashFunc=0){
        this->dictPath = dictPath;
        this->selectHashFunc = selectHashFunc;
        file = new readFile(dictPath);
        selectHashNameFunc();
        N = file->getLines();
        M = N / a;

        hashList = hashDict();

    }
    linkList *getHashList() const;//返回headList指针
    void selectHashNameFunc();//确定选择的hash的名字
    unsigned int getHashKey(char *str); //返回字符串的hash值
    void printResult(); //输出结果
    linkList* hashDict(); // 对字典建立hash表

};

class Query{
private:
    readFile *file; //读取文件的指针
    Hash *hash; //hash表的指针
    string wordsPath; //文件的地址
    int needQueryNum;//需要查询的单词数
    int alreadyFindNum;//查询到的次数
    int sumLength;//查询的总长度
    int alreadySumLength; //查询到的计算的总长度
public:
    Query(Hash *hash,string wordsPath=""){
        this->wordsPath = std::move(wordsPath);
        this->hash = hash;
        needQueryNum = 0;
        alreadyFindNum = 0;
        sumLength = 0;
        alreadySumLength = 0;
    }
    pair<bool,int> queryHash(const string& str); //<是否查到，查询次数> 查询str是否在hash表中
    void query(); //查询wordsPath文件在hash表中出现的结果
    void printResult();//输出结果

};

void Hash::selectHashNameFunc(){
    switch(selectHashFunc) {
        case 0: selectHashName = "RSHash";break;
        case 1: selectHashName = "JSHash";break;
        case 2: selectHashName = "PJWHash";break;
        case 3: selectHashName = "ELFHash";break;
        case 4: selectHashName = "BKDRHash";break;
        case 5: selectHashName = "SDBMHash";break;
        case 6: selectHashName = "DJBHash";break;
        case 7: selectHashName = "DEKHash";break;
        case 8: selectHashName = "BPHash";break;
        case 9: selectHashName = "FNVHash";break;
        case 10: selectHashName = "APHash";break;
        default: selectHashName = "ELFHash";break;
    }
}

//
unsigned int Hash::getHashKey(char *str) {
    //在这里调用不同的hash函数
    switch(selectHashFunc) {
        case 0: return HashFunc::RSHash(str);break;
        case 1: return HashFunc::JSHash(str);break;
        case 2: return HashFunc::PJWHash(str);break;
        case 3: return HashFunc::ELFHash(str);break;
        case 4: return HashFunc::BKDRHash(str);break;
        case 5: return HashFunc::SDBMHash(str);break;
        case 6: return HashFunc::DJBHash(str);break;
        case 7: return HashFunc::DEKHash(str);break;
        case 8: return HashFunc::BPHash(str);break;
        case 9: return HashFunc::FNVHash(str);break;
        case 10: return HashFunc::APHash(str);break;
        default: return HashFunc::ELFHash(str);break;
    }
}

linkList* Hash::hashDict(){
    hashList = new linkList[M]; //动态申请一个内存空间用来做数组链表
    string str;

    while(true){
        str = file->getNextLine();
        if(str.empty()) break;
        char *value = const_cast<char *>(str.c_str());
        unsigned int key = getHashKey(value);
        key %= M; //将计算得到的Hash值对M进行求余
        if(!hashList[key].getValue().empty()){
            linkList *temp = new linkList;
            temp->setValue(str);
            hashList[key].addLink(temp);
        }
        else{
            hashList[key].setValue(str);
        }

    }
    return hashList;
}

pair<bool,int> Query::queryHash(const std::string& str){
    char *value = const_cast<char *>(str.c_str());
    unsigned int key = hash->getHashKey(value);
    key %= M;
    pair<bool,int> ans;
    ans.first = false;
    ans.second = 0;
    linkList *temp = &hash->getHashList()[key];
    while(true){
        ans.second++;
        if(temp->getValue() == str) {
            ans.first = true;
            break;
        }
        else {
            if(temp->getNext()==nullptr){
                break;
            }
            else{
                temp = temp->getNext();
            }
        }
    }
    return ans;
}

void Hash::printResult() {
    cout<<"使用的hash函数为："<<selectHashName<<endl;
}

linkList *Hash::getHashList() const {
    return hashList;
}

void Query::printResult(){
    cout<<"需要查询的个数为："<<needQueryNum<<endl;
    cout<<"查询到的个数为："<<alreadyFindNum<<endl;
    cout<<"查询总长度为："<<sumLength<<endl;
    cout<<"总的平均查询长度为："<<(float)sumLength / needQueryNum<<endl;
    cout<<"查询到的平均查询长度："<<(float)alreadySumLength / alreadyFindNum<<endl;
}

void Query::query() {
    file = new readFile(wordsPath);
    needQueryNum = file->getLines();
    alreadyFindNum= 0;
    sumLength = 0;
    string str;
    while(true){
        str = file->getNextLine();
        if(str.empty()) break;
        pair<int,int> ans = queryHash(str);
        alreadyFindNum += ans.first;
        sumLength += ans.second;
        if(ans.first) alreadySumLength += ans.second;
    }
    free(file);
}
int main(){

    //配置属性
    //a = 1; //在这里修改装填因子 1 2 5 10 50
    cout<<"输入装填因子:";
    cin>>a;
    string dict = /*"./../../1.txt";*/  "./dict.txt";
    string words = /*"./../../2.txt";*/ "./words.txt";
    int temp;
    for(int i = 0; i < 11; i++) {
        cout << "**************************************" << endl;

        Hash hash = Hash(dict, i);

        Query query = Query(&hash, words);

        query.query();
        hash.printResult();
        query.printResult();


   }

    // 写入results.txt
    /*ofstream ofs;
    ofs.open("./../../results.txt",ios::out);
    Hash hash = Hash(dict,0);
    Query query = Query(&hash);
    readFile file = readFile(words);
    for(int i = 0; i < file.getLines();i++){
        string str = file.getNextLine();
        pair<bool,int> ans = query.queryHash(str);
        if(ans.first){
            ofs<<str<<endl;

        }
    }*/

    return 0;
}
