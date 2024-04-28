#ifndef __WEBPAGESEARCH_H__
#define __WEBPAGESEARCH_H__ 
#include <iostream>
#include<string>
#include"WebQuery.h"
#include"nlohmann/json.hpp"
#include<vector>
using namespace std;
class WebQuery;
class WebPageSeacher{
string _outcome;
WebQuery _webquery;
string _dumpjson;
public:
string doQuery( string str );
string doQueryjson(string str );

};
#endif
