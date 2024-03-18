#ifndef _INVERTINDEX_H
#define _INVERTINDEX_H
#include<vector>
#include <map>
#include <string>
#include<set>
#include "RssInvertIndex.h"
#include"../src/IsChinese.cc"
#include"../src/WordSegment.cc"
using namespace std;
class InvertIndex {
public:
	InvertIndex(){
	cout<<"InvertIndex init"<<endl;
	}
    //文章总数
    int _N=0;
    //存放倒排索引
    map<string,map<int,double>> _wordinvertindex;
    //存放网页id和网页
    map<string,string> _webitem;
    //存放词和词频
    map<string,int> _wordfre;
    //存放词和出现的文章id
    map<string,set<string>> _worddic;
    WordSegment _wordse;
void getwebitem();
    
bool dealword(string word);

void geninvertindexitem();

void readFile();

void genworddic(string);
    
void WriteInvert();
    
};

#endif //_INVERTINDEX_H
