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
    //按值排序
    static bool cmp(pair<double,size_t> a, pair<double,size_t> b) {
	return a.first > b.first;
}

    //存放查询到的集合
    vector<WebPage> _resultwebs;
    //存放临时网页
    string _web;
    //存放真正向量
    map<size_t,map<string,double>> _Y;
   //存放基准值
    map<string,double> _X;
    //存放向量
    map<size_t,map<string,double>> _PY;
    //存放文档相关交集
    set<size_t> _idresult;
    //存放排序后的文章id和余弦值
    vector<pair<double,size_t>> _idcos;
    //存放倒排索引
    map<string,map<size_t,double>> _wordinvertindex;
    //存放临时web
    WebPage _webpage;
    //文章开始与结尾的位置
    int _start;
    int _end;
    //文章总数
    int _N=0;
    
    //string _InvertIndexDataplace="/home/zcz2002/project/websearch/WebInvertIndexData/Invertindex.dat";
   // string _offsetplace="/home/zcz2002/project/websearch/OffSetData/offset.dat";
   // string _rippageplace="/home/zcz2002/project/websearch/RipPageData/rippage.dat";
    string _InvertIndexDataplace="../data/Invertindex.dat";
    string _offsetplace="../data/offset.dat";
    string _rippageplace="../data/rippage.dat";
public:
    //获得所有查询的文章,对外暴露
    vector<WebPage> getquery(string);
    //根据id获得文章
    WebPage query(size_t );
private:
    //根据文章的id获取开始与结尾的位置
    void  setoffset(size_t );
    //设置文章
    void setwebpage();
    //根据文章的起始与结尾获取文章
    void setweb();
    //设置倒排索引库
    void setinvertindex();
    //设置文章id交集
    void  setdocidresult(string input);
    //设置向量Y
    void setY();
    //求基准值X
    void setbase(string);
    //求余弦值
    void setcossim();
    //设置排序后的文章
    void setallwebs(string);
    //获得文章总数
    void getN(){
    RssWebpage reader;
    reader.parseRss(_rippageplace);
    vector<WebPage> prssitem=reader.getWebData();
    for(auto it:prssitem)
    {   ++_N;
    }

		} 
};
