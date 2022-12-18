#include<iostream>
#include <cstring>
#include <valarray>
#include "readFile.h"
#include "Bit.h"
#include "bloom.h"

using namespace std;



float Log(int a,int b){
    return log(b) / log(a);
}



int main() {
   string dictFile = "./dict.txt";//"./../../dict.txt";
   string wordsFile = "./words.txt";//"./../../words.txt";
   string resultFile = "./result.txt";//"./../../result.txt";
   cout<<"input the fp:";
   float fp;
   cin>>fp;
   bloom filter = bloom(fp,dictFile);
   filter.queryFile(wordsFile,resultFile);

   return 0;
}