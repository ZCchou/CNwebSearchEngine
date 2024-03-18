#ifndef  __WEBRECOMMENDER_H__
#define  __WEBRECOMMENDER_H__
#include "Recommend.h"
class WordRecommender
{
    Recommend _recommend;
public: string  recommend(string str){

return _recommend.getrecommendword(str);
        }

};
#endif
















