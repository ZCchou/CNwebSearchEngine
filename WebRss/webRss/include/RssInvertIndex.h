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
        void parseRss(const string filepath);//����
        void dump(const string & filename);//���
        string htmlfilter(string line);//����html
        vector<RssItem> getWebData();
    private:
        vector<RssItem> _rss;
    };  



#endif
