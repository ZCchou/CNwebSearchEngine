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

#include"RssReader.h"

using namespace std;
class Datcreater{
string  _rippageplace="../../../data/rippage.dat";
string  _websplace="../../../data/web";
vector<string> _allfilenames;//��������ļ���
public: 
//���������ļ�
void HandleAllFile();
//�����ļ���
void setFilenames();

void getFiles( string path, vector<string>& files ) ;
                        
};


#endif