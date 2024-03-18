#ifndef __RECOMMEND_H__
#define __RECOMMEND_H__
#include <iostream>
#include<string.h>
#include<string>
#include<set>
#include<map>
#include<vector>
#include<algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include"levenshtein.h"
#include"SplitCN.h"
using namespace std;
class Recommend{
    //内部类用于存放词频和词
    class wordfd
    {public:
        string word;
        int freq;
        int editdistance;
    public :
        wordfd(string iword,int ifreq,int iedit)
        :word(iword),freq(ifreq),editdistance(iedit)
        {
        }

    };
    set<int> _lettercon;//用来存放交集
    vector<wordfd> _result;//存放结果
    map<string,int > _recommendwordfre;//存放推荐词词频
    map<string,int> _wordanddistance;//存放推荐词和变形距离
    string _word;//输入的字符
    string _worddictionname="../data/wordfc.dat";
    string _letterdictionname="../data/letterandlinenum.dat";
    public:
    Recommend(string word,string worddic,string letterdic)
    :_word(word),
     _worddictionname(worddic),
     _letterdictionname(letterdic)
    {
    }
    Recommend(string word)
    :_word(word)
    {}
    Recommend()
    {}
//重设推荐词
void setword(string str){_word=str;}
//对外提供字符串推荐词
string getrecommendword(string str){
    _word=str;
    setcon();
    setwordandfre();
    wordfdsort();
    string recom="\n";
        cout<<"Recommend front 20 words"<<endl;
        int i=0;
        for(auto it:_result)
        {   
            recom=recom+it.word+"\n";
            ++i;
            if(i==20)
            return recom;
        }  
        return recom;
}

//对外提供推荐词
public:vector<string> getrecommendword();
    
private:
    //初始化交集_lettercon
    void setcon();
    //找出行号对应单词,将词和词频存入map
     void setwordandfre();
    //自定义排序规则，先比较最小编辑距离，再比较词频
    //若发现排序顺序错更改大于号
  static  bool cmp(const wordfd &w1,const wordfd &w2);
    //排序
    void wordfdsort();
    //打印
    void printrecommendword();
};
#endif
