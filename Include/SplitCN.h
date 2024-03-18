#ifndef __SPLITCN_H__
#define __SPLITCN_H__
#include <iostream>
#include<string>
#include<vector>
using namespace std;
class SplitCN{
public:static vector <string> split_chinese(string s) {
      std::vector <std::string> t;
      for (size_t i = 0; i < s.length();) {
          int cplen = 1;
          // 以下的几个if，要参考这里 https://en.wikipedia.org/wiki/UT
          if ((s[i] & 0xf8) == 0xf0)      // 11111000, 11110000
              cplen = 4;
          else if ((s[i] & 0xf0) == 0xe0) // 11100000
              cplen = 3;
          else if ((s[i] & 0xe0) == 0xc0) // 11000000
              cplen = 2;
          if ((i + cplen) > s.length())
              cplen = 1;
          t.push_back(s.substr(i, cplen));
          i += cplen;
      }
      return t;
  }
};
#endif