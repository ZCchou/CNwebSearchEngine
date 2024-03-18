#include "../include/InvertIndex.h"
void InvertIndex::getwebitem(){
    
    RssInvertIndex reader;
    reader.parseRss("../../../data/rippage.dat");
    cout<<"reader.parseRss"<<" has done"<<endl;
    vector<RssItem> prssitem=reader.getWebData();
    for(auto it:prssitem)
    {   ++_N;
        _webitem.insert(make_pair(it.docid,it.description));
    }
}

void InvertIndex::geninvertindexitem() {

WordSegment wordse;
double n=_N;
    //遍历文章
    for(auto webitem:_webitem)
{   cout<<"剩余文章数"<<n--<<endl;
    vector<string> words= wordse(webitem.second);
    set<string> unmultiwords(words.begin(),words.end());//单词去重
    //过滤非中文字符
    for(auto itword=unmultiwords.begin();itword!=unmultiwords.end();)
    {   
        if(dealword(*itword))
        ++itword;
        else{
           itword= unmultiwords.erase(itword);
        }
    }
    
    //计算分母
    
    //TF_IDF算法的分母
    long double undernumi=0;
    for(auto word:unmultiwords)
    {
    
        int TF=0;
        //计算词本文中的词频
        for(auto wordforfre:words)
        {
            if(wordforfre==word)
            {++TF;}
        }
        double weight;
        double DF=_wordfre.find(word)->second;
        double IDF=log2(_N/(DF+1));
        weight=TF*IDF;
        undernumi+=(weight*weight);
    }
    //遍历词
    for(auto inputword:unmultiwords)
    { 
        if(dealword(inputword))
        {
        int TF=0;
        //计算词本文中的词频
        for(auto wordforfre:words)
        {
            if(wordforfre==inputword)
            {++TF;}
        }
        double weight;
        double DF=_wordfre.find(inputword)->second;
        double IDF=log2(_N/(DF+1));
        weight=TF*IDF;
       // 得到真的权值
        double oldw=weight;
        weight=weight/sqrt(undernumi);

        int webid=atoi(webitem.first.c_str());
        
        //cout<<"word="<<inputword<<"  N="<<_N<<"  DF="<<DF<<"  TF="<<TF<<"  IDF="<<IDF<<" fakeweight="<<oldw<<"undernumi="<<undernumi<<"  weight="<<weight<<endl;
        bool wordexsit=false;
        //如果词在容器中已经有,插入文章id和权值
        if(_wordinvertindex.find(inputword)!=_wordinvertindex.end())
        {   
            _wordinvertindex.find(inputword)->second.insert(make_pair(webid,weight));
            //_worddic.find(inputword)->second.insert(webitem.first);
            wordexsit=true;
    
        }
        //如果没有，插入词，文章id权值
        if(!wordexsit)
        {
            map<int,double> pvector;
            pvector.insert(make_pair(webid,weight));
            _wordinvertindex.insert(make_pair(inputword,pvector));
        }
        }   
    }
}

}
//读文件生成词频
void InvertIndex::readFile()
{
    cout<<"readFile"<<endl;
    ifstream ifs("../../../data/rippage.dat");
if(!ifs){
cerr<<"ifstream is not good"<<endl;
return;
        }
    int count=0;
    size_t length;//记录文章长
    ifs.seekg(0,std::ios::end);//找到文章末尾
    length=ifs.tellg();//获取文章长度
    ifs.seekg(0,std::ios::beg);//回到文章首部
    char* buffer=new char[length];//读到缓存
    ifs.read(buffer,length);
    vector<string> results=_wordse(buffer);
    string word;
    for(auto it:results)
    {
        word=it;
        //单词合法
        if(dealword(word))
        {    
        cout<<"生成第"<<++count<<"个词"<<word<<"的词频"<<endl;
        genworddic(word);//统计词频
        }
    }

ifs.close();
}

bool InvertIndex::dealword(string word){
return IsChinese::dealword(word);

}
//生成词频索引
void InvertIndex::genworddic(string word) {
if(word==string("")||!dealword(word))
   {    return;
   }
//插入正常的字符串
       if(_wordfre.empty())
       {
       _wordfre.insert(make_pair(word,0));
       }   

	   bool exsit=false;
           for(auto it=_wordfre.begin();it!=_wordfre.end();it++)
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
               _wordfre.insert(make_pair(word,1));
               }     
}

//写文件
void InvertIndex::WriteInvert() {


    {
          
   ofstream ofs("../../../data/Invertindex.dat");
   if(!ofs.good()){
   cerr<<"ofs is not good"<<endl;
   return;
   }
   else
   {
  for(auto it = _wordinvertindex.begin(); it != _wordinvertindex.end(); ++it)
  {ofs<<it->first<<" ";
   for(auto it2=it->second.begin();it2!=it->second.end();++it2)
   {
    ofs<<it2->first<<" ";
    ofs<<it2->second<<" ";
   }
   ofs<<endl;
   }
   }
   ofs.close();
    }
}
