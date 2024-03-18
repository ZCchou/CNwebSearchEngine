#include"WordSegment.cc"
#include <iostream>
#include <fstream>
#include <sstream>
#include<ctype.h>
#include<string.h>
#include<string>
#include<map>
#include<vector>
#include<set>
#include"IsChinese.cc"
#include"SplitCN.h"//中文分字
using namespace std;
class WriteDiction
{
public:
void readFile(const string filename);//读文件
void Writedic();//write a dictionary
void Writewn();//write word and line number
void Letterinsert();//统计单字在词频字典里出现的行号参数为词频字典文件名
void Writell();//写字母和在出现词频行数
WordSegment _wordse;//分词工具
private:
bool dealword(const string &word);//过滤单词
void Finsert(const string &word);//统计词频
map<string,set<int>> _letterNum;//存放字母与行号
map<string, int> _dict;//存词与词频
string  _worddictionname="../data/wordfc.dat";//词频统计写出来的文件名
string _letterdictionname="../data/letterandlinenum.dat";//存放字母与行的文件名
};
void WriteDiction::readFile(const string filename){
ifstream ifs(filename);
if(!ifs){
cerr<<"ifstream is not good"<<endl;
return;
        }


    size_t length;//记录文章长
    ifs.seekg(0,std::ios::end);//找到文章末尾
    length=ifs.tellg();//获取文章长度
    ifs.seekg(0,std::ios::beg);//回到文章首部
   char* buffer=new char[length];//读到缓存
    ifs.read(buffer,length);
    vector<string> results=_wordse(buffer);
    //istringstream iss(line);
    string word;
    for(auto it=results.begin();it!=results.end();++it)
    {
        word=*it;
        //单词合法
        if(dealword(word))
        Finsert(word);//统计词频
    }

ifs.close();
}
bool WriteDiction::dealword(const string &str){//判断是否为中文

return IsChinese::dealword(str);
                        
}
//插入字与行号
void WriteDiction::Letterinsert()//插入字母出现行
{
    ifstream ifs(_worddictionname);

if(!ifs){
cerr<<"ifstream is not good"<<endl;
return;
        }
string line;int linenum=1;
while(getline(ifs,line))
{   
    istringstream iss(line);
    string word;
    iss>>word;
     vector <string>splitedword=SplitCN::split_chinese(word);
    //遍历字符串word
    for(auto wit:splitedword)
    {  
        bool letterexsit=false;
        //遍历存放字母的map
        for(auto it=_letterNum.begin();it!=_letterNum.end();++it)
        {
            if(it->first==wit)//如果字母存在则插入行号
            {
                it->second.insert(linenum);
                letterexsit=true;
            }
        }
        if(!letterexsit)//如果遍历后字母不存在则插入键值和行号
        {
            set<int> pset={linenum};
            string cnwo=wit;
                cout<<cnwo<<endl;
            _letterNum.insert(make_pair(cnwo,pset));
        }
    }
    ++linenum;
    }
    ifs.close();
}
//插入词频
void WriteDiction::Finsert(const string &word){
   //cout<<"Finsert("<<word<<")"<<endl;
   if(word==string(""))
   {    return;
   }
//插入正常的字符串
       if(_dict.empty())
       {
       _dict.insert(make_pair(word,0));
       }   

	   bool exsit=false;
           for(auto it=WriteDiction::_dict.begin();it!=WriteDiction::_dict.end();it++)
           {
               if(word==it->first)
               {
                   ++(it->second);
                   exsit=true;
                   break;
               }
           }
          //若不存在就插入新 
           if(!exsit)
               {
               _dict.insert(make_pair(word,1));
               }                                                            
   }



//写词典
void WriteDiction::Writedic(){

    ofstream ofs(_worddictionname);
   if(!ofs.good()){
   cerr<<"ofs is not good"<<endl;
   return;
   }
   else
   {
  for(auto it = _dict.begin(); it != _dict.end(); ++it)
   ofs<<it->first<<" "<<it->second<<endl;
   }
   ofs.close();
  return ;

}

//写字母+行号
void WriteDiction::Writell(){
    ofstream ofs(_letterdictionname);
   if(!ofs.good()){
   cerr<<"ofs is not good"<<endl;
   return;
   }
   else
   {
  for(auto it = _letterNum.begin(); it != _letterNum.end(); ++it)
  {ofs<<it->first<<" ";
   for(auto it2=it->second.begin();it2!=it->second.end();++it2)
   {
    ofs<<*it2<<" ";
   }
   ofs<<endl;
   }
   }
   ofs.close();
  return ;
}



