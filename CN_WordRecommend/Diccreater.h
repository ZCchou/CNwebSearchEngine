#ifndef   _DATCREATER_H
#define   _DATCREATER_H
#include "JsonReader.h"
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
vector<string> _allfilenames;//��������ļ���
public: 
Diccreater(){
JsonReader r("../conf/Webqueryconf.json");
_rippageplace=r.findlocal("rippageplace");
_websplace=r.findlocal("websplace");
}
//���������ļ�
void HandleAllFile();
//�����ļ���
void setFilenames();

void getFiles( string path, vector<string>& files ) ;
                        
};


#endif
