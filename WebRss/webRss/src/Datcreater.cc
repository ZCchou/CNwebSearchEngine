#include "../include/Datcreater.h"

//处理所有文件
void Datcreater::HandleAllFile()
{
RssReader rss;
for(auto it:_allfilenames)
{
    rss.parseRss(it);
}
    rss.deduplicate();//去重
    rss.dump(_rippageplace);
    cout<<"写入网页完成"<<endl;
}
//生成文件集
void Datcreater::setFilenames()
{
getFiles(_websplace, _allfilenames);

    
}
void Datcreater::getFiles( string path, vector<string>& files )  
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
                        

