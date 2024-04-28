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
vector<string> _allfilenames;//��������ļ���
public: 
Datcreater(){
JsonReader jsr("../../../conf/WebRssconf.json");
  _rippageplace=jsr.findlocal("rippageplace");
  _websplace=jsr.findlocal("websplace");
	
}
//���������ļ�
void HandleAllFile();
//�����ļ���
void setFilenames();

void getFiles( string path, vector<string>& files ) ;
                        
};


#endif