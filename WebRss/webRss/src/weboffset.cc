#include <iostream>
#include <fstream>
#include<map>
using namespace std;
class weboffset{
//偏移库：webid，偏移量
private:
string _offsetplace="../../../data/offset.dat";
map<size_t,pair<int,int>> _offset;
public:
void InsertOffset(size_t docid,int start,int end)
{
    _offset.insert(make_pair(docid,make_pair(start,end)));
}
//写文件
void Write(){

    ofstream ofs(_offsetplace);
if(!ofs){
    cerr<<"open"<<"offset"<<"failed"<<endl;
    return;
        }
    for(auto it :_offset)
    {
    ofs<<it.first<<" "<<it.second.first<<" "<<it.second.second<<endl;
    }
ofs.close();
cout<<"offsetwritten"<<endl;
}



};
