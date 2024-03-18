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
    //�ڲ������ڴ�Ŵ�Ƶ�ʹ�
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
    set<int> _lettercon;//������Ž���
    vector<wordfd> _result;//��Ž��
    map<string,int > _recommendwordfre;//����Ƽ��ʴ�Ƶ
    map<string,int> _wordanddistance;//����Ƽ��ʺͱ��ξ���
    string _word;//������ַ�
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
//�����Ƽ���
void setword(string str){_word=str;}
//�����ṩ�ַ����Ƽ���
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

//�����ṩ�Ƽ���
public:vector<string> getrecommendword();
    
private:
    //��ʼ������_lettercon
    void setcon();
    //�ҳ��кŶ�Ӧ����,���ʺʹ�Ƶ����map
     void setwordandfre();
    //�Զ�����������ȱȽ���С�༭���룬�ٱȽϴ�Ƶ
    //����������˳�����Ĵ��ں�
  static  bool cmp(const wordfd &w1,const wordfd &w2);
    //����
    void wordfdsort();
    //��ӡ
    void printrecommendword();
};
#endif
