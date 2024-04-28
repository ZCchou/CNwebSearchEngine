#pragma once
#include <fstream>
#include"nlohmann/json.hpp"
using namespace std;
class JsonReader
{
public:
    JsonReader(string);
    ~JsonReader() {}
    string findlocal(string);
private:
nlohmann::json _jdata;
};

