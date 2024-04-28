#ifndef   _DATCREATER_H
#define   _DATCREATER_H

#include <iostream>
#include <vector>
#include<string>
#include <sys/types.h>
#include <dirent.h>
#include "InvertIndex.h"
#include"RssReader.h"
#include"../3rdlib/simhash-cppjieba/cppjieba/Jieba.hpp"
#include "../include/JsonReader.h"
#include"RssReader.h"

using namespace std;
class Datcreater{
string  _rippageplace="../../../data/rippage.dat";
string  _websplace="../../../data/web";
vector<string> _allfilenames;//存放所有文件名
public: 
Datcreater(){
JsonReader jsr("../../../conf/WebRssconf.json");
  _rippageplace=jsr.findlocal("rippageplace");
  _websplace=jsr.findlocal("websplace");
	
}
//处理所有文件
void HandleAllFile();
//生成文件集
void setFilenames();

void getFiles( string path, vector<string>& files ) ;
                        
};


#endif