#pragma once

#ifndef __COMMON_H_
#define __COMMON_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/time.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <sys/un.h>
#include <pthread.h>
#include <sqlite3.h>

//错误提示
#define NET_ERROR(x,y) do{printf("%s : %d ->",__func__,__LINE__);perror(x);exit(y);}while(0);
#define SQL_ERROR(x,y)do{printf("%d error : %s\n",__LINE__,x);exit(y);}while(0);
#define MENU_MSG "菜品编号\t菜名\t\t价格\t会员价格\n"
#define ORDER_MSG "桌号 | 菜名 | 点餐者 | 价格 | 份数 | 总计"
#define M_SIZE 20

//目录的结构体
typedef struct BJmenu
{
    int mid;    //编号
    int id ;    //新编号
    char name[20];//菜名
    int cbprice ;//成本价格
    int price;  //价格
    int vipp;   //vip价格
    int kucun; //库存
}mu_t;

//用户的结构体
typedef struct user
{
    int tableid;//桌号
    char name[20];//登陆者
    int fd;//客户端socket的描述符
}user_t;

//订单的结构体
typedef struct order
{
    int mid; //编号
    char name[20];//菜名
    int price;//价格
    int num ; //数量
    int total;
    int statu;
    char username[20] ;
    int zz;//桌号
   
}o_t;

//库存的结构体
typedef struct  kucun
{
    int mid ;
    char name[20];
    int num ;
}ku_t;

//营业额的结构体
typedef struct Money
{
    int orderid;
    char order_name[20];
    int money;
}mon_t;

mu_t mu[M_SIZE];
ku_t ku[M_SIZE];
o_t dd[M_SIZE]; //定义订单结构体数组

static int i = 0;
sqlite3 *db;
static int m=0;
static int k=0;

int fu();//打开服务端　进行通讯
int xianshi(int len);//显示菜谱
int dingdan(int len);//显示订单
int menu_f();   //主界面

int sql_name(void *para,int num,char** f_value,char** f_name);
int sql_values(void *para,int num,char** f_value,char** f_name);
int sql_msg(sqlite3 *sql,const char *ch);//显示菜谱
int sql_copy(sqlite3 *sql);
int menu_msg(sqlite3 *sql);//查看菜谱目录
int menu_msg1(sqlite3 *sql);//查看自己下单的目录

int menu_insert(sqlite3 *sql);//菜谱的添加
int menu_delete(sqlite3 *sql);//菜谱的删除
int menu_update(sqlite3 *sql);//菜谱的更新
int menu_copy(void *para,int num,char** f_value,char** f_name);//将菜谱目录栏的信息进行复制

int order_msg(sqlite3* sql,int num);///订单信息
int order_delete(sqlite3* sql,int num);//订单的删除


int user_insert(sqlite3 *sql,user_t *user);//添加用户的信息
int user_delete(sqlite3 *sql,user_t user);//注销用户的信息

int kucun_msg(sqlite3 *sql);//查看库存目录
int kucun_init(sqlite3 *sql);//
int kucun_insert(sqlite3 *sql);//库存的添加
int kucun_delete(sqlite3 *sql);//库存的删除
int kucun_copy(void *para,int num,char** f_value,char** f_name);//将库存中的信息进行复制
int kucun_updata(sqlite3* sql,ku_t kucun);//库存的更新

int Money_insert(sqlite3* sql,mon_t* dollr);//营业额的计算

#endif

