#include <iostream>
#include "../Include/WebPageSeacher.h"
//直接查询
string WebPageSeacher::doQuery(string str)
{
for(auto it:_webquery.getquery(str))
{	

    _outcome=_outcome+"\n标题："+it.title+"\n"+"链接："+it.link+"\n"+"内容："+it.description+"\n"+"全："+it.content+"\n";
 
}
return _outcome;
}
//获取json
string WebPageSeacher::doQueryjson( string str )
{
	nlohmann::json _jwebs;
        nlohmann::json pjweb;
 	vector<nlohmann::json> vjwebs;
for(auto it:_webquery.getquery(str))
{	
 pjweb["docid"]=it.docid;
 pjweb["link"]=it.link;
 pjweb["title"]=it.title;
 pjweb["description"]=it.description;
 pjweb["content"]=it.content;
    vjwebs.push_back(pjweb);
}
_jwebs["webs"]=vjwebs;
_dumpjson=_jwebs.dump();
return _dumpjson;
}

