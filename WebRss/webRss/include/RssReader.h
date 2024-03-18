#pragma once
 #include <iostream>
 #include <fstream>
 #include <sstream>
 #include <string>
 #include <string.h>
 #include"RssItem.h"
 #include<vector>
 #include"../3rdlib/simhash-cppjieba/Simhasher.hpp"
 #include<regex>
 #include "tinyxml2.h"
 #include "../src/weboffset.cc"
 using namespace tinyxml2;
 using namespace simhash;
     using namespace std; 
     class RssReader{
     public:                                                                                                                                                  
         RssReader(){}
         weboffset offset;
         void parseRss(const string filepath);//解析
         void deduplicate();//去重
         void dump(const string & filename);//输出
         string htmlfilter(string line);//过滤html
     private:
         vector<RssItem> _rss;
     
     
   class Deduplication{
   public:                                           
       Deduplication(vector <RssItem> web):
       _web(web),
       simhasher("../dict/jieba.dict.utf8", "../dict/hmm_model.utf8", "../dict/idf.utf8", "../dict/stop_words.utf8")
       {}  
   private:
   vector <RssItem>_web;//网页库
   Simhasher simhasher;//判断是否重复所用库
   size_t _topN=10;//关键词个数
   public: 
   uint64_t gensimhash (string str)//生成simhash值
   {
       uint64_t u;
       simhasher.make(str,_topN,u);
       return u;
   }
   bool IsDup(uint64_t u1,uint64_t u2)//是否重复
   {
    //海明距离阈值2，则只有两个或以下词不同，判为相似
     return Simhasher::isEqual(u1, u2,2);
   }
   vector<RssItem> webdedup()//网页去重
   {    int i=1;
     uint64_t u1;
     uint64_t u2;
     for(auto it1=_web.begin();it1!=_web.end();++it1)
     {  
         cout<<"去重第"<<i++<<"篇"<<endl;
         for(auto it2=it1;it2!=_web.end();++it2)
         { if(it1!=it2)
             {  
                 u1=gensimhash(it1->title);
                 u2=gensimhash(it2->title);
                 if(IsDup(u1,u2))
                 {
                     it1 = _web.erase(it1);
                 }
             }
         }       
     }
     return _web;
   }
   };    
     };
