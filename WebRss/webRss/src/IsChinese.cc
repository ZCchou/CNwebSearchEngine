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
bool static isChineseCharacter(char c) {
    // 判断是否是中文字符（Unicode范围）
    return (c >= 0x4E00 && c <= 0x9FFF);
}

bool static isChineseText(const std::string& text) {
    for (char c : text) {
        // 如果是中文字符且不是中文标点符号，返回true
        if (isChineseCharacter(c) && !(c >= 0x3000 && c <= 0x303F)) {
            return true;
        }
    }
    // 如果没有中文字符，或者全部是中文标点符号，返回false
    return false;
}

};
