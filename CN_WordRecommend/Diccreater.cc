#include "Diccreater.h"
#include "JsonReader.h"
//处理所有文件
void Diccreater::HandleAllFile()
{
WriteDiction tq;

for(auto it:_allfilenames)
{
  cout<<it<<endl;
  tq.readFile(it);
}
tq.Writedic();//写词和词频
tq.Letterinsert();//参数是词频统计写出来的文件名
tq.Writell();//写字母行号

}
//生成文件集
void Diccreater::setFilenames()
{
getFiles(_websplace, _allfilenames);

    
}
void Diccreater::getFiles( string path, vector<string>& files )  
{   
    string dot= ".";
    string ddot = "..";
    //目录流指针
   const char *cpath=path.c_str();
    DIR *dirStream;
    dirStream=opendir(cpath);
    //文件信息
    struct dirent* dirInfo;
    while((dirInfo=readdir(dirStream)))
    {   string fname=dirInfo->d_name;
        //去除.和..
        if((fname!=dot)&&(fname!=ddot))    
        {
        fname=_websplace+string("/")+fname;
        files.push_back(fname);
       }   
    }
}
                        

