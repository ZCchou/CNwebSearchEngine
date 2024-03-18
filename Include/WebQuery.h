#pragma once
#include <iostream>
#include <sstream>
#include<fstream>
#include "RssWebpage.h"
#include<set>
#include<map>
#include<cmath>
#include<algorithm>
using namespace std;
class WebQuery{
    //��ֵ����
    static bool cmp(pair<double,size_t> a, pair<double,size_t> b) {
	return a.first > b.first;
}

    //��Ų�ѯ���ļ���
    vector<WebPage> _resultwebs;
    //�����ʱ��ҳ
    string _web;
    //�����������
    map<size_t,map<string,double>> _Y;
   //��Ż�׼ֵ
    map<string,double> _X;
    //�������
    map<size_t,map<string,double>> _PY;
    //����ĵ���ؽ���
    set<size_t> _idresult;
    //�������������id������ֵ
    vector<pair<double,size_t>> _idcos;
    //��ŵ�������
    map<string,map<size_t,double>> _wordinvertindex;
    //�����ʱweb
    WebPage _webpage;
    //���¿�ʼ���β��λ��
    int _start;
    int _end;
    //��������
    int _N=0;
    
    //string _InvertIndexDataplace="/home/zcz2002/project/websearch/WebInvertIndexData/Invertindex.dat";
   // string _offsetplace="/home/zcz2002/project/websearch/OffSetData/offset.dat";
   // string _rippageplace="/home/zcz2002/project/websearch/RipPageData/rippage.dat";
    string _InvertIndexDataplace="../data/Invertindex.dat";
    string _offsetplace="../data/offset.dat";
    string _rippageplace="../data/rippage.dat";
public:
    //������в�ѯ������,���Ⱪ¶
    vector<WebPage> getquery(string);
    //����id�������
    WebPage query(size_t );
private:
    //�������µ�id��ȡ��ʼ���β��λ��
    void  setoffset(size_t );
    //��������
    void setwebpage();
    //�������µ���ʼ���β��ȡ����
    void setweb();
    //���õ���������
    void setinvertindex();
    //��������id����
    void  setdocidresult(string input);
    //��������Y
    void setY();
    //���׼ֵX
    void setbase(string);
    //������ֵ
    void setcossim();
    //��������������
    void setallwebs(string);
    //�����������
    void getN(){
    RssWebpage reader;
    reader.parseRss(_rippageplace);
    vector<WebPage> prssitem=reader.getWebData();
    for(auto it:prssitem)
    {   ++_N;
    }

		} 
};
