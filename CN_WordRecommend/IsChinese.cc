#include <iostream>
#include<string>
using namespace std;
class IsChinese{
public :bool static dealword(const string &str){//判断是否为中文
    
        int i = 0;
    for (; i < str.length(); i++)
        {
            //不是全角字符
            if (str[i] >= 0 && str[i] <= 127)
            {
                return false;
            }
            else
            {
                //中文是2个字节
                i++;
            }
        }
    return true;
    
    }
};
