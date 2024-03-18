#include"../include/RssInvertIndex.h"
void RssInvertIndex::parseRss(const string filepath){

    XMLDocument doc;
    if(!doc.LoadFile(filepath.c_str())){
    XMLElement *node=doc.FirstChildElement("doc");
    while(node){
        RssItem rssi;
        //rssi.link=nullptr;
        //rssi.title=nullptr;
        //rssi.description=nullptr;
        //rssi.content=nullptr;
    
   XMLElement *docid=  node->FirstChildElement("docid");
   XMLElement *title=  node->FirstChildElement("title");
   XMLElement *link=   node->FirstChildElement("link");
   XMLElement *description= node->FirstChildElement("description");
   XMLElement *content  =  node->FirstChildElement("content");
   if(docid){
       const char *pdocid=docid->GetText();
       string spdocid=htmlfilter(string(pdocid));
        rssi.docid=spdocid;
       cout<<spdocid<<endl;
   }
   if(title&&title->GetText()){
       const char *ptitle=title->GetText();
       string sptitle=htmlfilter(string(ptitle));
        rssi.title=sptitle;
       cout<<sptitle<<endl;
   }
   if(link&&link->GetText()){
       const char *plink=link->GetText();
       string splink=htmlfilter(string(plink));
        rssi.link=splink;
   cout<<splink<<endl;
   }
   
   if(description&&description->GetText()){
       const char *pdescription=description->GetText();
       string spdescription=htmlfilter(string(pdescription));
        rssi.description=spdescription;
   cout<<spdescription<<endl;
   }
   else{
       rssi.description="";
   }
   if(content&&content->GetText()){
       const char *pcontent=content->GetText();
       string spcontent=htmlfilter(string(pcontent));
        rssi.content=spcontent;
   }
   else{
       rssi.content="";
   }
   _rss.push_back(rssi);
   node=node->NextSiblingElement("doc");//下一个兄弟节点
            }
    }
}
//过滤html标签
string RssInvertIndex::htmlfilter(string line){
regex regAll("<[^>]+>");
    line=regex_replace(line,regAll,"");
//cout<<line<<endl;
return line;
}

void RssInvertIndex::dump(const string & filename){

    ofstream ofs(filename);
    if(!ofs){cerr<<"open"<<filename<<"failed"<<endl;
        return;}
    for(size_t idx=0;idx!=_rss.size();++idx)
    {
       ofs<<"<doc>\n<docid>"<<idx+1
           <<"</docid>\n<title>"<<_rss[idx].title
           <<"</title>\n<link>"<<_rss[idx].link
           <<"</link>\n<description>"<<_rss[idx].description
           <<"</description>\n<content>"<<_rss[idx].content
           <<"</content>\n</doc>";
        ofs<<endl;
    }
    ofs.close();
}
vector<RssItem> RssInvertIndex::getWebData(){
return _rss;
}
