#ifndef __WEBPAGE_H__
#define __WEBPAGE_H__

#include <iostream>
#include<map>
#include<string>
using namespace std;
class WebPage{
public:
string _doc;
size_t docid;
string link;
string title;
string description;
string content;
map<string,int> _wordsMap;
    
public:
WebPage(){}
WebPage(string doc,size_t docid,string docurl,string doctitle,string description,string doccontent):
    _doc(doc),
    docid(docid),
    link(docurl),
    title(doctitle),
    description(description),
    content(doccontent)
    {   

    }
public:
void setdoc(string doc){
_doc=doc;
}
};
#endif