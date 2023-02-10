#ifndef COMMON_H
#define COMMON_H


class COMMON
{
public:

//********************************
//定义游戏级别
//********************************
enum gameLeve
{
    LOWLEVE = 0,
    MIDDLELEVE = 1,
    HIGHLEVE = 2,
    CUSOMLEVE = 3
};

//********************************
//低端局行、列、雷数设置
//********************************
enum lowset
{
    LOWROWANDCOL = 9,
    LOWMINENUM = 2
};

//********************************
//一般局行、列、雷数设置
//********************************
enum middleset
{
    MIDDLEROWANDCOL = 16,
    MIDDLEMINENUM = 2
};

//********************************
//高端局行、列、雷数设置
//********************************
enum highset
{
    HIGHROW = 16,
    HIGHCOL = 30,
    HIGHMINENUM = 99
};

//********************************
//图片大小设置
//********************************
enum mapset
{
    MAPWIDTH = 25,
    MAPHEIGHT = 25
};

};

#endif // COMMON_H

