/************************************************************************************
**						@->>作者：廖铁钢
**						@->>版本：2.0
**						@->>设计日期：2021-8-12
*************************************************************************************/

#ifndef DLIST_H
#define DLIST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//功能:安全检查宏
//@x:要检查的变量
//@opt:操作符: ==,<,>
//@y:要检查的值; 	if(NULL == p) {  printf("p is null\n"); return -1; }
//@z:返回值			SYSERR(NULL,==,p,"p is null",-1);
//					if(index < 0) {  printf("index must >= 0",-1); }
//					SYSERR(index,<,0,"index must >= 0",-1);
//
//					如果函数定义是: void fun(int *p);  没有返回值
//					if(NULL == p)
//					{
//						printf("p is null\n");
//						return;
//					}
//					SYSERR(NULL,==,p,"p is null\n",);

/*
#define SYSERR(x,opt,y,message,z)		if(x opt y)		\
						{			\
							printf("%s %d %s : error %s\n",__FILE__,__LINE__,__func__,message);							\
							return z;	\
						}
*/

/*链表节点定义:*/
typedef struct node
{
	struct node *prev;		//前向指针
	void *data;		//数据指针,链表更通用
	struct node *next;			//后向指针
}node_t;	//node_t是struct node的类型别名

//功能:创建链表
//参数:无
//返回值:已创建链表的头节点地址
node_t *create_dlist();

//功能:向双循环链表头部插入数据
//@head:要插入的链表头节点
//@data:要插入链表的数据
//@size:数据的字节大小
//返回值为插入成功与否: 0表示成功，非0表示失败
int insert_hdlist(node_t *head,void *data,int size);

//功能:向双向循环链表尾部插入数据
int insert_tdlist(node_t *head,void *data,int size);

//功能:按值从链表中查找某节点
//@head:从哪个链表去查找
//@data:要查找的数据
//@cmpfun:比较函数指针，在调用时必须使用具体的函数名:返回类型必须为int,且有两个参数，
//两个参数必须为void *型
//返回值:如果查找到返回此节点,如果未找到返回NULL;
typedef int (*cmpfun_t)(void *data1,void *data2); //比较函数指针类型
node_t *find_vdlist(node_t *head,void *data,cmpfun_t cmpfun);

//功能:用于遍历显示链表中所有节点的函数
//@head:要显示的链表
//@showfun:显示函数指针，要怎么显示,在调用时必须使用具体的函数名:返回类型必须为void，有1个参数，
//这个参数的类型必须为void *
typedef void (*showfun_t)(void *data);			  //显示函数指针类型
void show_hdlist(node_t *head,showfun_t showfun);
void show_tdlist(node_t *head,showfun_t showfun);

//功能:删除第一个数据节点
//@head:要从哪个链表删除
int delete_hdlist(node_t *head);
//功能:删除链表尾部节点
int delete_tdlist(node_t *head);
//功能:按值删除,只会删除指定值第一次出现的节点
//@head:要从哪个链表删除
//@cmpfun:比较函数指针
//返回值：删除成功返回0，失败返回非0值
int delete_vdlist(node_t *head,void *data,cmpfun_t cmpfun);

//功能:对链表按指定方式排序
//@head:对哪个链表进行排序,
//@cmpfun:比较函数指针,排序的方式,函数指针
//返回值：排序成功返回0,失败返回非0值
int maopao_sortdlist(node_t *head,cmpfun_t cmpfun);

//功能:销毁链表,销毁后head为NULL
//返回值:销毁成功返回0,失败返回非0值
int destroy_dlist(node_t **head);
int length_dlist(node_t *head);
#endif
