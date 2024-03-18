#ifndef   _DATCREATER_H
#define   _DATCREATER_H

#include <iostream>
#include <vector>
#include<string>
#include <sys/types.h>
#include <dirent.h>
#include"Writedic_cn.cc"

using namespace std;
class Diccreater{
string  _rippageplace="../data/rippage.dat";
string  _websplace="../data/web";
vector<string> _allfilenames;//存放所有文件名
public: 
//处理所有文件
void HandleAllFile();
//生成文件集
void setFilenames();

void getFiles( string path, vector<string>& files ) ;
                        
};


#endif