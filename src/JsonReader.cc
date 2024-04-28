#include <iostream>
#include "../Include/JsonReader.h"
string JsonReader::findlocal(string localname)
{
return _jdata[localname];
}
JsonReader::JsonReader(string ConfJsonName)
{
std::ifstream file(ConfJsonName);
    if (!file.is_open()) {
        std::cerr << "Failed to open JSON file.\n";
    }
    // 读取 JSON 数据
    
    file >>_jdata;
    
}
