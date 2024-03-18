#include"../Include/WebQuery.h"

    vector <WebPage> WebQuery::getquery(string input)
{   
    setallwebs(input);
    return _resultwebs;
}
    void WebQuery::setallwebs(string input)
{   
    cout<<"读入倒排库"<<endl;
    setinvertindex();
    cout<<"读入倒排库完成"<<endl;
    cout<<"获取文章交集"<<endl;
    setdocidresult(input);
    setY();
    for(auto it:_Y)
    {cout<<"Y= "<<it.first<<endl;
        for(auto it2:it.second)
            cout<<it2.first<<"  "<<it2.second<<endl;
    }
    cout<<"求基准值X"<<endl;
    setbase(input);
    for(auto it:_X)
    {cout<<"X= "<<it.first<<"Xw= "<<it.second<<endl;}
    cout<<"求余弦值"<<endl;
    setcossim();
    cout<<"读取查询的网页"<<endl;
    for(auto it:_idcos)
    {   
 //       cout<<"docweight="<<it.first<<"  "<<"docid="<<it.second<<endl;
        _resultwebs.push_back(query(it.second));
    }
    for(auto it:_resultwebs)
    {
  //      cout<<endl<<it.link<<endl;
    }


}

    //根据id搜索文章
    WebPage WebQuery::query(size_t id)
{
    setoffset(id);
    setweb();
    setwebpage();
    return _webpage;
}


 void WebQuery::setcossim()
{
    //遍历文章向量Y
for(auto yit:_Y)
{
double wcos=0;
//a*b
double wtop=0;
//|a|*|b|
double wund=0;
//计算top
for(auto it:yit.second)
{
    wtop+=(it.second)*(_X.find(it.first)->second);
}
//计算under
double wa=0;
double wb=0;
for(auto it:yit.second)
{
   wa+= (it.second)*(it.second);
}
for(auto it:_X)
{
   wb+= (it.second)*(it.second);
}
wund=sqrt(wb)+sqrt(wa);
wcos=wtop/wund;
_idcos.push_back(make_pair(wcos,yit.first));
}
sort(_idcos.begin(), _idcos.end(),cmp ); 
}

void WebQuery::setbase(string input)
{   
    map<string,double> fakeweight;
    map<string,double> weight;
    set<string> word; 
    map<string,double>_TF;    
    istringstream iss(input);
    string iword;
    
    //double TF=1;
    double DF=0;
    for(auto it: _Y)
    {   
        ++DF;
    }
//    cout<<"DF="<<DF<<endl;
    double N=0;
    for(auto it:_Y.begin()->second)
        {
        word.insert(it.first);
        }
    getN();
    N=_N;
 //   cout<<"N="<<N<<endl;
    double IDF=log2(N/(DF+1));
  //  cout<<"IDF="<<IDF<<endl;
    
    while(iss>>iword)
    {
   //     cout<<"iword="<<iword<<endl;
        if(word.find(iword)!=word.end())
        {
            if(_TF.find(iword)!=_TF.end())
            {
                _TF.find(iword)->second++;
            }
            else
            {
                _TF.insert(make_pair(iword,1));
            }
        }
    }
    //生成假权值
for(auto it:_TF)
{   
    //cout<<"_TF="<<it.second<<endl;
    double w=it.second*IDF;
    //cout<<"fw="<<w<<endl;
    fakeweight.insert(make_pair(it.first,w));
}
double m=0; 
for(auto it:fakeweight)
{
    //
    //cout<<it.second<<endl;
m+=it.second;
}
//cout<<"m="<<m<<endl;
for(auto it:fakeweight)
{
    weight.insert(make_pair(it.first,it.second/sqrt(m)));
}
_X=weight;
}


void WebQuery::setwebpage()
{
RssWebpage rss;
rss.parseRss("pweb.dat");
WebPage ptiem; 
for(auto it:rss.getWebData())
_webpage=it;
_webpage.setdoc(_web);
}

void WebQuery::setinvertindex()
{
ifstream ifs(_InvertIndexDataplace);
if(!ifs.good())
    {
    cerr<<"stream is not good"<<endl;
    return ;
    }
string word;
size_t docid;
double weight;
string line;
while(getline(ifs,line))
{   
    map<size_t,double> pi;
    istringstream iss(line);
    iss>>word;
    while(iss>>docid&&iss>>weight)
    {
        pi.insert(make_pair(docid,weight));
    }
    _wordinvertindex.insert(make_pair(word,pi));

}
ifs.close();
/*
for(auto it:_wordinvertindex){
    cout<<it.first<<" "<<endl;
    for(auto it2:it.second)
        cout<<it2.first<<"  "<<it2.second<<endl;
}
*/
}


void WebQuery:: setdocidresult(string input)
{   
       cout<<input<<endl;
    istringstream iss(input);
    string  word;
    
   // map<size_t,double> presult;
    iss>>word;
    //找到单词
    //生成向量
    if(_wordinvertindex.find(word)!=_wordinvertindex.end())
    {
    auto it=_wordinvertindex.find(word);
    map<string,double> pmap;
    for(auto it2:it->second)
    {//it2=map<size_t,double>
        pmap.insert(make_pair(word,it2.second));
    if(_PY.find(it2.first)==_PY.end())    
        _PY.insert(make_pair(it2.first,pmap));
    else
        _PY.find(it2.first)->second.insert(make_pair(word,it2.second));
    }
    }

    //set用来求交集
    set<size_t> id;
    if(_wordinvertindex.find(word)!=_wordinvertindex.end())
    for(auto it:_wordinvertindex.find(word)->second )
    {
        id.insert(it.first);
    }
    else
    {   //循环检查是否有该词直到遍历完
        while(iss>>word&&_wordinvertindex.find(word)==_wordinvertindex.end());
    //向量生成
        if(_wordinvertindex.find(word)!=_wordinvertindex.end())
    {
    auto it=_wordinvertindex.find(word);
        map<string,double> pmap;
    for(auto it2:it->second)
    {//it2=map<size_t,double>
        pmap.insert(make_pair(word,it2.second));
    if(_PY.find(it2.first)==_PY.end())    
        _PY.insert(make_pair(it2.first,pmap));
    else
        _PY.find(it2.first)->second.insert(make_pair(word,it2.second));
    }
    }
        //读第一个集合
        if(_wordinvertindex.find(word)!=_wordinvertindex.end())
        for(auto it:_wordinvertindex.find(word)->second )
    {
        id.insert(it.first);
    }
        else return;
    }
    while(iss>>word)
    {
        //生成向量Y
    if(_wordinvertindex.find(word)!=_wordinvertindex.end())
    {
    auto it=_wordinvertindex.find(word);
        map<string,double> pmap;
    for(auto it2:it->second)
    {//it2=map<size_t,double>
        pmap.insert(make_pair(word,it2.second));
    if(_PY.find(it2.first)==_PY.end())    
        _PY.insert(make_pair(it2.first,pmap));
    else
        _PY.find(it2.first)->second.insert(make_pair(word,it2.second));
    }
    }
    //生成交集
           set<size_t> pid;
           set<size_t>ppid;
           if(_wordinvertindex.find(word)!=_wordinvertindex.end())
            {
        for(auto it:_wordinvertindex.find(word)->second)
        {
            pid.insert(it.first);
        }
            set_intersection(pid.begin(),pid.end(),id.begin(),id.end(),inserter(ppid,ppid.end()));
            id=ppid;
            cout<<word<<"存在"<<endl;
            //copy(ppid.begin(),ppid.end(),id.begin());
       }
    }
    _idresult=id;

}

void WebQuery:: setY(){

    for(auto idresult:_idresult)
    {
       if(_PY.find(idresult)!=_PY.end())
       {
            _Y.insert(*_PY.find(idresult));
       }
    }
}



void WebQuery:: setoffset(size_t docid)
{
ifstream ifs(_offsetplace);
if(!ifs.good())
    {
    cerr<<"stream is not good"<<endl;
    return ;
    }

string line;
for(size_t i=0;i<docid;++i)
{    getline(ifs,line);}
    istringstream iss(line);
    size_t pid;
    iss>>pid;
    iss>>_start;
    iss>>_end;
    ifs.close();        
//cout<<"docid= "<<docid<<endl;
//cout<<"start= "<<_start<<endl;
//cout<<"end= "<<_end<<endl;
//cout<<"doclength"<<_start-_end<<endl;    
    }


void WebQuery:: setweb()
{
ifstream ifs(_rippageplace);
if(!ifs.good())
    {
    cerr<<"stream is not good"<<endl;
    return ;
    }
ifs.seekg(_start,ios::beg);
string web;
string line;
int lenth=_end-_start;
int read=0;
while(read<lenth)
{   
    getline(ifs,line);
    ++read;
    read+=line.size();
    //cout<<line<<endl;
    web=web+line+"\n";
}
    //cout<<_web;
ifs.close();
    ofstream ofs("pweb.dat");
    ofs<<web;
    _web=web;
    ofs.close();
    }


