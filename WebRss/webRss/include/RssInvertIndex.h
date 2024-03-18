#ifndef _RSSINVERTINDEX_H
#define _RSSINVERTINDEX_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "RssItem.h"
#include<vector>
#include<regex>
#include "tinyxml2.h"
    using namespace tinyxml2;
    using namespace std;       
    class RssInvertIndex{
    public:
        RssInvertIndex(){}
        void parseRss(const string filepath);//½âÎö
        void dump(const string & filename);//Êä³ö
        string htmlfilter(string line);//¹ýÂËhtml
        vector<RssItem> getWebData();
    private:
        vector<RssItem> _rss;
    };  



#endif
