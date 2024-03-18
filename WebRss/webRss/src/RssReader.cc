 #include"../include/RssReader.h"
void RssReader::parseRss(const string filepath){

    XMLDocument doc;
    if(!doc.LoadFile(filepath.c_str())){
    XMLElement *node=doc.FirstChildElement("rss")->FirstChildElement("channel")->FirstChildElement("item");
    while(node){
        RssItem rssi;
        //rssi.link=nullptr;
        //rssi.title=nullptr;
        //rssi.description=nullptr;
        //rssi.content=nullptr;
   XMLElement *title=  node->FirstChildElement("title");
   XMLElement *link=   node->FirstChildElement("link");
   XMLElement *description= node->FirstChildElement("description");
   XMLElement *content  =  node->FirstChildElement("content:encoded");
   if(title){
       const char *ptitle=title->GetText();
       string sptitle=htmlfilter(string(ptitle));
        rssi.title=sptitle;
     //  cout<<sptitle<<endl;
   }
   if(link){
       const char *plink=link->GetText();
       string splink=htmlfilter(string(plink));
        rssi.link=splink;
   //cout<<splink<<endl;
   }
   if(description){
       const char *pdescription=description->GetText();
       string spdescription=htmlfilter(string(pdescription));
        rssi.description=spdescription;
   //cout<<spdescription<<endl;
   }
   if(content){
       const char *pcontent=content->GetText();
       string spcontent=htmlfilter(string(pcontent));
        rssi.content=spcontent;
   }
   _rss.push_back(rssi);
   node=node->NextSiblingElement("item");//下一个兄弟节点
            }
    }
}


void RssReader:: deduplicate()//去重
{
    cout<<"开始去重"<<endl;
    Deduplication dedup(_rss);
    _rss=dedup.webdedup();
    cout<<"去重完毕"<<endl;

}

//过滤html标签
string RssReader::htmlfilter(string line){
regex regAll("<[^>]+>");
    line=regex_replace(line,regAll,"");
//cout<<line<<endl;
return line;
}

void RssReader::dump(const string & filename){
    int start=0;
    int end=0;
    ofstream ofs(filename);
    if(!ofs){cerr<<"open"<<filename<<"failed"<<endl;
        return;}
    for(size_t idx=0;idx!=_rss.size();++idx)
    {
       ofs<<"<doc>\n<docid>"<<to_string(idx+1)
           <<"</docid>\n<title>"<<_rss[idx].title
           <<"</title>\n<link>"<<_rss[idx].link
           <<"</link>\n<description>"<<_rss[idx].description
           <<"</description>\n<content>"<<_rss[idx].content
           <<"</content>\n</doc>\n";
        //计算网页偏移
          string html("<doc>\n<docid>"+to_string(idx+1)+"</docid>\n<title>"+_rss[idx].title+"</title>\n<link>"+_rss[idx].link+"</link>\n<description>"+_rss[idx].description+"</description>\n<content>"+_rss[idx].content+"</content>\n</doc>\n");
      int lenthhtml =html.size();
      //int lenthweb=1+_rss[idx].title.size()+_rss[idx].link.size()+_rss[idx].description.size()+_rss[idx].content.size();
      start=end;
      end=start+lenthhtml;
      offset.InsertOffset(idx+1,start,end);  
    }
    ofs.close();
    offset.Write();
}
