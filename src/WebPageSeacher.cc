#include <iostream>
#include "../Include/WebPageSeacher.h"

string WebPageSeacher::doQuery(string str)
{
    string outcome;
for(auto it:_webquery.getquery(str))
{
    outcome=outcome+"标题："+it.title+"\n"+"链接："+it.link+"\n";
}
return outcome;
}

