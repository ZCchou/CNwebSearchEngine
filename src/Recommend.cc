#include <iostream>
#include"../Include/Recommend.h"

//对外提供推荐词
vector<string> Recommend::getrecommendword(){
         vector<string> t;
           for(auto it:_result)
           {t.push_back(it.word);
           }
        return t;
       }
    

    //初始化交集_lettercon
    void Recommend::setcon()
    {
    ifstream ifs(_letterdictionname);
    if(!ifs.good())
    {
    cerr<<"stream is not good"<<endl;
    return ;
    }
    vector<string>splitedword=SplitCN::split_chinese(_word);
    for(auto wit:splitedword)
    {
       string line;
       int linenum=1;
       //按行读 
       while(getline(ifs,line))
        {   
        istringstream iss(line);
        string letter;
        iss>>letter;//将第一个字取出
        
        int pnum;
        if(letter==wit)
        {
            while(iss>>pnum){
         _lettercon.insert(pnum);
                            }
        }
        ++linenum;
        }
    }
                        }
//找出行号对应单词,将词和词频存入map
    void Recommend::setwordandfre(){
    
    ifstream ifs(_worddictionname);
    if(!ifs.good())
    {
    cerr<<"stream is not good"<<endl;
    return ;
    }
            int linenum=0;
        //遍历——_lettercon
        for(auto it=_lettercon.begin();it!=_lettercon.end();++it)
        {
            string line;
            while(linenum!=*it)
            {
                getline(ifs,line);
                ++linenum;
            }
            istringstream iss(line);
            string word;
            int frequance;
            //第一次取出单词
            iss>>word;
   //         cout<<"从"<<linenum<<"行取出单词"<<word<<endl;
            //第二次取出词频
            iss>>frequance;
     //       cout<<"取出词频率"<<frequance<<endl;
            //_recommendwordfre.insert(make_pair(word,frequance));
            //存入结果 
            int distance=levenshtein::compare(_word,word);
       //     cout<<"取出距离"<<distance<<endl;
            wordfd pwordfd(word,frequance,distance); 
            _result.push_back(pwordfd);
        }
        ifs.close();
    }
    //自定义排序规则，先比较最小编辑距离，再比较词频
    //若发现排序顺序错更改大于号
bool Recommend::cmp(const wordfd &w1,const wordfd &w2){
    if(w1.editdistance!=w2.editdistance)
        return w1.editdistance<w2.editdistance;
    if(w1.freq!=w2.freq)
        return w1.freq<w2.freq;
    return false;
    }
    //排序
    void Recommend::wordfdsort(){
        sort(_result.begin(),_result.end(),cmp);
    }
    //打印
    void Recommend::printrecommendword(){
        cout<<"推荐前20条"<<endl;
        int i=0;
        for(auto it:_result)
        {   
            cout<<it.word<<endl;
            ++i;
            if(i==20)
            return;
        }  
    }



