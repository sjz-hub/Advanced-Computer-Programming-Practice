//
// Created by �ｨ�� on 2022/11/2.
//

#include <cstring>
#include <valarray>
#include <queue>
#include "acNode.h"
using std::string;

int acNode::m = 2;
int acNode::stateNode = 0;
int acNode::stateTransition = 0;

acNode::acNode(int nodeKind): nodeKind(nodeKind) {
    fail = nullptr;
    stateNode++;
    if(nodeKind == 0){//��֧�ڵ�
        ptr = new acNode *[m+1];
        for(int i = 0; i <= m; ++i) ptr[i] = nullptr;
    }
    else {  // Ҷ�ӽڵ�
        ptr = nullptr;
        appearCount = 0;
    }
}

char * stringToTwoB(string &value, bool flag = false){
//    char *ch1 = new char[value.length()+1];
//    strcpy(ch1,value.c_str());
    char *ch = new char[(value.length()+1)*2];
    int nowJ = 0;
    for(int i = 0; i < value.length();i++){
        if(nowJ%2 == 0){
            if(uint8_t(value[i]) <= 128){//˵����ǰ��ASCII
                ch[nowJ++] = uint8_t(0x80);
                ch[nowJ++] = uint8_t(value[i]);
            }
            else{
                ch[nowJ++] = uint8_t(value[i]);
            }
        }
        else{
            ch[nowJ++] = uint8_t(value[i]);
        }
    }
    ch[nowJ] = '\0';
    if(nowJ%2!=0) cout<<value<<endl<<"this is a error"<<nowJ<<endl;
    return ch;
}

int acNode::queryWord(std::string &value){
    acNode *now = this;
    char *ch = stringToTwoB(value);
    int n = log(m)/log(2);//Ҳ����ÿ���ƶ���λ
    int count = 0; //��¼��ѯ�Ĵ���
    for(int i = 0; i < strlen(ch)*8; i += n){
        count++;
        int num = 0;//��ʾ��ǰnλ�����ƵĴ�С
        for(int j = 0 ; j < n; j++){
            num *= 2;
            num += ( ch[(j+i)/8]>>(7-(j+i)%8) & 1 );
        }
        //��Ϊ����0��ʾ����$
        num++; //���Լ�1
        if(now->ptr[num] == nullptr){
            delete ch;//�ͷſռ�
            return 0;//˵��һ�����Ҳ��������
        }
        if(i == strlen(ch)*8 - n){//˵���������һ�α�����
            if(now->ptr[num]->nodeKind == 1){//Ҷ�ӽڵ�
                if(now->ptr[num]->value == value) {
                    delete ch;//�ͷſռ�
                    return now->ptr[num]->appearCount;//return ++count;
                }
                else {
                    delete ch;//�ͷſռ�
                    return -1;
                }
            }
            else{//�ڲ��ڵ�
                if(now->ptr[num]->ptr[0] != nullptr && now->ptr[num]->ptr[0]->value == value) {
                    delete ch;//�ͷſռ�
                    return now->ptr[num]->ptr[0]->appearCount;//return ++count;
                }
                else {
                    delete ch;//�ͷſռ�
                    return -1;//�Ҳ���
                }
            }
        }
        else{//�������һ�α���
            if(now->ptr[num]->nodeKind == 1){//�������һ�α���������Ҷ�ӽڵ㣬˵���Ҳ���
                delete ch;//�ͷſռ�
                return -1;
            }
            now = now->ptr[num];
        }
    }

    delete ch;//�ͷſռ�

}

int acNode::query(string &value,ofstream &ofs,long long int nowIndex,int &wordNum,vector<string> &vec, bool flag){
//    cout<<"queryStart\n";
    acNode *now = this;
    char *ch = stringToTwoB(value,flag);
    if(flag) cout<<ch<<" "<<strlen(ch)<<endl;
//    cout<<value<<" "<<value.length()<<endl;
    int n = log(m)/log(2);//Ҳ����ÿ���ƶ���λ
    for(int i = 0; i < strlen(ch)*8; i+=n){
        int num = 0;
        for(int j = 0 ; j < n; j++){
            num *= 2;
            num += ( ch[(j+i)/8]>>(7-(j+i)%8) & 1 );
        }
        if(flag) cout<<++num<<" ";
    }
    if(flag) cout<<endl;


    bool rootK = false;//��ʶ��ǰ�Ƿ���Ҫi+=n
    for(int i = 0; i < strlen(ch)*8; i += n){
        int num = 0;//��ʾ��ǰnλ�����ƵĴ�С
        for(int j = 0 ; j < n; j++){
            num *= 2;
            num += ( ch[(j+i)/8]>>(7-(j+i)%8) & 1 );
        }
        //��Ϊ����0��ʾ����$
        num++; //���Լ�1
        if(flag) cout<<i<<" "<<now->dep<<" "<<num<<endl;
        if(now->ptr[num] == nullptr) {//˵����ǰ�����Ҳ�����
            acNode *temp = now;
            now = now->fail;
            stateTransition++;
            if(flag) cout<<"a";
            if(now == this) { //�������now  now->fail������     now�Ļ����ܻ����һֱû�иýڵ�����    now->fail���ܻ���� ���θ��� �ӹ������
                if(flag) cout<<rootK<<"b";
                if(rootK){
                    i += n;
                    rootK= false;
                }
                else rootK= true;
            }
            else{
                if(flag) cout<<"c";
                rootK = false;
            }
            i -= n;
            continue;
        }
        rootK = false;


        //����˵��ptr[num]�����ҵ�������һ�����ڲ��ڵ㣬��Ϊ���ﲻ���Ҷ�ӽڵ�

        if((i+n) % 16 == 0 /*true*/){
            acNode *pa = now->ptr[num]->fail;
            while(pa != this){
                if(pa->ptr[0] != nullptr) {
                    pa->ptr[0]->appearCount++;
                    vec.push_back(pa->ptr[0]->value);
                    if(flag) cout<<"*"<<pa->ptr[0]->value<<" "<<pa->ptr[0]->appearCount<<" "<<i<<endl;
                }
                pa = pa->fail;
            }
            if(now->ptr[num]->ptr[0] != nullptr){//˵���ҵ���һ������
                now->ptr[num]->ptr[0]->appearCount++;
                vec.push_back(now->ptr[num]->ptr[0]->value);
                if(flag) cout<<"ko"<<now->ptr[num]->ptr[0]->value<<" "<<now->ptr[num]->ptr[0]->appearCount<<" "<<i<<endl;
            }
        }
        now = now->ptr[num];
    }
    delete ch;//�ͷſռ�
}

/*0 2 4 6 8 10 12 14 16
 * 0 4 8 12 16
 * 0 8 16
 *
 *
 * */

void acNode::init() {
    fail = this;  // root��failָ��ָ������
    dep = 0;
    stateNode = 0;
    stateTransition = 0;
}




//��ָ��ptr[1]~ptr[m]����ָ��ptr[0]
void acNode::buildFail() {
    acNode * root = this;  //root�ڵ�
    this->fail = this;
    std::queue<acNode *> q;

    for(int i = 1; i <= m; ++i){//����root�ڵ�ĺ��ӽڵ�  root�ĺ��ӽڵ㶼����ֱ��ָ��root
        if(root->ptr[i] == nullptr) continue;
        root->ptr[i]->fail = root;
        root->ptr[i]->dep = root->dep+1;
        if(root->ptr[i]->nodeKind == 0) q.push(root->ptr[i]);
        else cout<<"ad";
    }
    //�ӵ�2�㿪ʼ����BFS����
    while(!q.empty()){//��ʼBFS����
        acNode *now = q.front();
        q.pop();
        //��ʼ������ǰ�ڵ�ĺ��ӽڵ�
        for(int i = 1; i <= m; ++i){
            if(now->ptr[i] == nullptr) continue;
            now->ptr[i]->dep = now->dep + 1;
            q.push(now->ptr[i]); //ֻ���ڲ��ڵ�Ż����
            acNode *parentFail = now->fail;
            //����fail
            if(parentFail->ptr[i] != nullptr) {//˵�����׽ڵ��fail�ĺ��Ӵ��ڵ�ǰ��ͬ������
                now->ptr[i]->fail = parentFail->ptr[i];
            }
            else{//û���ҵ�
                while(true){
                    parentFail = parentFail->fail;
                    //֮ǰ���������ifд���ˣ��ͻᵼ�³�����
                    if(parentFail->ptr[i]!= nullptr) {
                        now->ptr[i]->fail = parentFail->ptr[i];
                        break;
                    }
                    if(parentFail == parentFail->fail) {//˵������root�ڵ��˶�
                        now->ptr[i]->fail = parentFail;
                        break;
                    }

                }
            }

        }

    }
}




//��Ҷ�ӽڵ㶼����ptr[0]��

void acNode::insert_node(string value, bool flag){
//    saveKeyNum ++;
    acNode *now = this;
    /*char *ch = new char[value.length()+1];
    strcpy(ch,value.c_str());*/
    char *ch = stringToTwoB(value,flag);
    if(flag) cout<<ch<<" "<<strlen(ch)<<endl;
    int n = log(m)/log(2);//Ҳ����ÿ���ƶ���λ
    for(int i = 0; i < strlen(ch)*8; i += n){
        int num = 0;//��ʾ��ǰnλ�����ƵĴ�С
        for(int j = 0 ; j < n; j++){
            num *= 2;
            num += ( ch[(j+i)/8]>>(7-(j+i)%8) & 1 );
        }
        //��Ϊ����0��ʾ����$
        num++; //���Լ�1
        if(flag)
            cout<<num<<" ";
//        if(value == "�헔�����ؗ�����") cout<<"S";
        if(i == strlen(ch)*8 - n){//˵���������һ�α�����
            if(now->ptr[num] == nullptr){//Ϊ�գ������ֱ�Ӳ���Ҷ�ӽڵ�
                acNode *new_node = new acNode(1);//
                new_node->value = value;//����Ҷ�ӽڵ��ֵ
//                now->ptr[num] = new_node;    //��������˸��ģ�����Ϊ��ptr[0]
                now->ptr[num] = new acNode(0);
                now->ptr[num]->ptr[0] = new_node;
            }
            else{//��Ϊ�գ�˵���Ѿ������ڲ��ڵ�
                if(now->ptr[num]->nodeKind == 1){//����Ҷ�ӽڵ㣬������ղ�������ֵ��֮ǰ�ʹ���
                    //��������ʱ�����в�����Ҳ���ǲ��ظ����в���
                }
                else{//���ýڵ�ŵ���һ���Ӧ�ڵ��ptr[0]��
                    acNode *new_node = new acNode(1);//
                    new_node->value = value;//����Ҷ�ӽڵ��ֵ
                    now->ptr[num]->ptr[0] = new_node;
                }
            }
        }
        else{
            if(now->ptr[num] == nullptr){//˵����û�н��п���
                now->ptr[num] = new acNode(0);//����Ϊ�ڲ��ڵ�
                now = now->ptr[num];//����now,ָ����һ��
            }
            else{//˵���Ѿ������ˣ��鿴��next��Ҷ�ӻ����ڲ�
                acNode *temp = now->ptr[num];
                if(temp->nodeKind == 1){//Ҷ�ӽڵ�
                    //�����µķ�֧�ڵ�
                    acNode *new_node = new acNode(0);
                    new_node->ptr[0] = now->ptr[num];//��Ҷ�ӽڵ�ŵ���һ���node�е�ptr�ĵ�һ��λ��
                    now->ptr[num] = new_node;
                    now = now->ptr[num];//����now��ֵ�������´�ѭ��
                }
                else{//�ڲ��ڵ�
                    now = now->ptr[num];//����now��ָ����һ��
                }
            }
        }
    }
    delete ch;//�ͷſռ�
}


void acNode::dfsDestoryNode(acNode *now){
    if(now->ptr!= nullptr){
        for(int i = 0; i <= m; ++i){
            if(now->ptr[i] == nullptr) continue;
            dfsDestoryNode(now->ptr[i]);
        }
    }
    delete now;
}

void acNode::close() {
    acNode* root = this;
//    cout<<"close";
    dfsDestoryNode(root);
//    cout<<"end";
}



