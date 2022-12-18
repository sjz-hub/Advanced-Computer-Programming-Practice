//
// Created by �ｨ�� on 2022/12/5.
//

#ifndef ACAUTO_CLOSENESS_H
#define ACAUTO_CLOSENESS_H

#include "LinkList.h"
#include "LinkMatrix.h"
#include "LinkThreeDimMatrix.h"
#include "ELL.h"
class closeness {
private:
    int wordNum;//���ʵĸ���
    double *wordClose;//���飬ÿ��Ԫ�ر�ʾһ�����ʵ����ķ����� wordClose[i] ��ʾ���ǵ�i������
    LinkThreeDimMatrix *ltm;//���ڴ���ͼ
    int *fa;//����ǵ�������������
    int *faNum; //����ǵ����������ڼ��ϵ�Ԫ�ظ���
    int K;//��ʾ�ҵ�ǰ20����������Է���
    double *score;//�洢ǰ20�������Է���
    int maxWeight;//������ͨ��ʱ����Ϊ�������Ȩ�� Ĭ�ϵ���wordNum
    ELL *ell;
    long long int *distance;
public:
    closeness(LinkThreeDimMatrix *ltm,ELL *ell,int K);
    void dealAllPointWithELL();
    double dealOnePointWithELL(int index,int *dis);
    void dealAllPoint();//�������нڵ�ķ���
    double dealOnePoint(int index,int *dis,int *vis);//����һ���ڵ�ķ���,��������Ϊindex
    pair<string,double> *printCloseScores(int n,string file);//���ǰn�󣬲��ҽ���������������file�ļ���
    int find(int x);
};

#endif //ACAUTO_CLOSENESS_H
