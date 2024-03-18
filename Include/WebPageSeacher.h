#ifndef __WEBPAGESEARCH_H__
#define __WEBPAGESEARCH_H__ 
#include <iostream>
#include<string>
#include"WebQuery.h"
using namespace std;
class WebQuery;
class WebPageSeacher{
WebQuery _webquery;
public:
string doQuery( string str );

};
#endif
