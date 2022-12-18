#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <cstring>
#include "acNode.h"

using namespace std;




//char * stringToTwoB1(string &value, bool flag = false){
//
//    char *ch1 = new char[value.length()+1];
//    strcpy(ch1,value.c_str());
//
//    char *ch = new char[(value.length()+1)*2];
//    int nowJ = 0;
//
//    for(int i = 0; i < value.length();i++){
////        cout<<i<<" "<<nowJ<<endl
////        cout<<value[i]<<endl;
//        if(nowJ%2 == 0){
//            if(uint8_t(value[i]) <= 0x7f){//说明当前是ASCII
//                ch[nowJ++] = uint8_t(2);
//                ch[nowJ++] = uint8_t(value[i]);
//            }
//            else{
//                ch[nowJ++] = uint8_t(value[i]);
//            }
//        }
//        else{
//            ch[nowJ++] = uint8_t(value[i]);
//        }
//    }
//    ch[nowJ] = '\0';
//
//    if(nowJ%2!=0) cout<<"this is a error"<<endl;
//
//    if(flag) {
//        cout<<"error";
//        cout<<strlen(ch1)<<" "<<strlen(ch)<<endl;
//        cout<<value<<endl;
//        for(int i = 0; i < strlen(ch1); i++) cout<<int(uint8_t(ch1[i]))<<" ";cout<<endl;
//        for(int i = 0; i < strlen(ch); i++) cout<<int(uint8_t(ch[i]))<<" ";cout<<endl;
//
//    }
//
//    return ch;
//}
//
//
//int main(){
//    string str = "孙建钊asd好人1203";
//    cout<<str.length();
//    char *ch;
//    ch = stringToTwoB1(str,true);
//    cout<<"endl"<<endl;
//    cout<<ch<<endl;
//    cout<< strlen(ch)<<endl;
//    return 0;
//}



//如果不是在i%8==0的情况下进行搜索，可能搜索出来的内容比较大，因为某个单词可能是另一个单词的后面加另一个单词的前面的部分，这样会认为找到了
//仅支持GBK文件编码
//可以查出来所有的内容例如查找的单词DD  则可以在DDD中查出两次


//查看具体出错的原因
//
//int main() {
//    cout<<"qwe"<<endl;
//    cout<<"孙建钊"<<endl;
//    int mList[] = {2,4,16,256};
//    for(int i = 3; i < 4; ++i){
//        acNode::m = mList[i];
//        acNode *root = new acNode(0);//
//        root->init();
//        string wordsFile = "./../../keyword.txt";   /*"./../../5.txt";  //"./../../dict.txt";*/
//        string contentFile = /*"./../../4.txt";*/  "./../../content.txt"; "./../../1.txt";  //"./../../words.txt";*/
//        std::ifstream wordsStream;
//        wordsStream.open(wordsFile);
//        string str;
//        int k = 0;
//        cout<<"insert\n";
//        string word = "图像中心距";
//        while(true){
//            getline(wordsStream,str);
//            if(str.empty()) break;
////            cout<<str<<endl;
//            if(str == word) cout<<str<<endl;
//            /*if(str == word)*/
//            if(str == word )
//            root->insert_node(str,true);
//            else root->insert_node(str);
//        }
//        wordsStream.close();
//        cout<<"buildFail\n";
//        root->buildFail();
//
//        cout<<"query\n";
//        std::ifstream contentStream;
//        contentStream.open(contentFile);
//        int lines= 0;
//
//
//        ofstream ofs;
//        ofs.open("./../../results.txt",ios::out);
//        int count = 0;
//        int preCount = 0;
//        while(getline(contentStream,str)){
//            if(str.empty()) break;
//            lines += 1;
////            cout<<lines<<endl;
//            if(lines % 10000 == 0) {
//                cout<<lines<<endl;
//            }
////            cout<<str<<endl;
//            if(lines == 648359) {
//                cout<<str;
//            }
//            root->query(str, true);
//            count = root->queryWord(word);
//            if(count - preCount > 0) {
//                cout<<"find:"<<count<<endl;
//                ofs<<lines<<" "<<count-preCount<<endl;
//            }
//            preCount = count;
//
//        }
//        ofs.close();
//        contentStream.close();
//    }
//    return 0;
//}
//



//
////检查一个出错的行，并输出
//
//int main() {
//    cout<<"qwe"<<endl;
//    cout<<"孙建钊"<<endl;
//    int mList[] = {2,4,16,256};
//    for(int i = 1; i < 2; ++i){
//        acNode::m = mList[i];
//        acNode *root = new acNode(0);//
//        root->init();
//        string wordsFile = "./../../keyword.txt";  /*"./../../7.txt"; /*"./../../2.txt";*/  //"./../../dict.txt";*/
//        string contentFile = "./../../4.txt";   /*"./../../content.txt"; /*"./../../1.txt";*/  /*"./../../words.txt";*/
//        std::ifstream wordsStream;
//        wordsStream.open(wordsFile);
//        string str;
//        int k = 0;
//        cout<<"insert\n";
//        string word = "儿茶素";
//        while(true){
//            getline(wordsStream,str);
//            if(str.empty()) break;
//            if(str == word) cout<<str<<endl;
//            if(str == word) root->insert_node(str, true);
//            else root->insert_node(str);
//        }
//        wordsStream.close();
//        cout<<"buildFail\n";
//        root->buildFail();
//
//        cout<<"query\n";
//        std::ifstream contentStream;
//        contentStream.open(contentFile);
//        int lines= 0;
//
//
//        ofstream ofs;
//        ofs.open("./../../results.txt",ios::out);
//        int count = 0;
//        int preCount = 0;
//        while(getline(contentStream,str)){
//            if(str.empty()) break;
//            lines += 1;
////            cout<<lines<<endl;
//            if(lines % 10000 == 0) {
//                cout<<lines<<endl;
//            }
////            cout<<str<<endl;
//            root->query(str, true);
//            count = root->queryWord(word);
//            if(lines == 16470){
//                cout<<str<<endl;
//            }
//
//            if(count - preCount > 0) {
//
//                cout<<count<<endl;
//                ofs<<lines<<" "<<count-preCount<<endl;
//            }
//            preCount = count;
//
//        }
//        ofs.close();
//        contentStream.close();
//    }
//    return 0;
//}









//真正运行的程序
int main() {
    int mList[] = {2,4,16,256};
    string results[] = {"2m.txt","4m.txt","16m.txt","256m.txt"};
    for(int i = 0; i < 4; ++i){
        acNode::m = mList[i];
        acNode *root = new acNode(0);//
        root->init();
        string wordsFile = /*"./rank1w.txt";*/"./keyword.txt"; //"./../../keyword.txt";    /*"./../../6.txt";*/  /*"./../../2.txt";  /*"./../../dict.txt";*/
        string contentFile = "./content.txt"; //"./../../content.txt";  /*"./../../1.txt"; /* //"./../../words.txt";*/
        std::ifstream wordsStream;
        wordsStream.open(wordsFile);
        string str;
        cout<<"insert\n";
        while(true){
            getline(wordsStream,str);
            if(str.empty()) break;
            root->insert_node(str);
        }
        wordsStream.close();
        cout<<"buildFail\n";
        root->buildFail();
        cout<<"query\n";
        std::ifstream contentStream;
        contentStream.open(contentFile);
        int lines= 0;
        while(getline(contentStream,str)){
            if(str.empty()) break;
            lines += 1;
            if(lines % 100000 == 0) {
                cout<<lines<<endl;
            }
            root->query(str);
        }
        contentStream.close();



        wordsStream.open(wordsFile);
        //写入内容
        int num = 0;
         ofstream ofs;
//         ofs.open("./../../result.txt",ios::out);
        ofs.open("./"+results[i],ios::out);

         while(getline(wordsStream,str)){
             if(str.empty()) break;
             int count = root->queryWord(str);
//             cout<<str<<" "<<count<<endl;
             ofs<<str<<" "<<count<<endl;
             num+=count;
         }
         ofs.close();
         wordsStream.close();
         cout<<"当前为"<<root->m<<"阶"<<endl;
         cout<<"总查找次数为："<<num<<endl;
         cout<<"状态节点数为："<<root->stateNode<<endl;
         cout<<"状态转移次数为："<<root->stateTransition<<endl;
         root->close();//释放空间
    }
    return 0;
}
