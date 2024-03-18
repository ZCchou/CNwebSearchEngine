#ifndef __RSSWEBPAGE_H__
#define __RSSWEBPAGE_H__
#include <iostream>
#include"WebPage.h"
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include<vector>
#include<regex>
#include "tinyxml2.h"
    using namespace tinyxml2;
    using namespace std;
/*    struct WebPage {
        string docid;
        string title;
        string link;
        string description;
        string content;
    };
 */      
    class RssWebpage{
    public:
        RssWebpage(){}
        void parseRss(const string filepath);//����
        void dump(const string & filename);//���
        string htmlfilter(string line);//����html
        vector<WebPage> getWebData();
    private:
        vector<WebPage> _rss;
    };  
#endif