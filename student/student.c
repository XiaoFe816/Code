/************************************************************************************
**						@->>作者：廖铁钢
**						@->>版本：2.0
**						@->>设计日期：2021-8-12
*************************************************************************************/

#include "common.h"

/*
	##：打印学生结构体的全部数据到屏幕上
*/
void show_student(void *data)
{
	stu_t *stup = (stu_t *)data;
	puts("\t__________________________________________________________________________________________");
	printf("\t%d	%d	%s	%s	%s	%d	%d	%d	%d	%d	%d\n",stup->order,stup->sid,stup->name,stup->spass,stup->sex,
			stup->age,stup->classid,stup->C,stup->math,stup->chinese,stup->chinese + stup->math + stup->C);
}

/*
	##：打印学生结构体的部分数据到屏幕上
*/
void student_grade(void *data)
{
	stu_t *stup = (stu_t *)data;
	puts("\t__________________________________________________________________________________________");
	printf("\t%d	%d	%s	%s	%d	%d	%d	%d	%d\n",stup->order,stup->sid,stup->name,stup->sex,stup->classid,stup->C,stup->math,stup->chinese,stup->total);
}


int cmp_stu_sid(void *data1,void *data2)	//比较学生大小
{
	stu_t *stu1 = (stu_t *)data1;
	stu_t *stu2 = (stu_t *)data2;
	return stu1->sid - stu2->sid;
}

int cmp_stu_name(void *data1,void *data2)	//比较学生名字
{
	stu_t *stu1 = (stu_t *)data1;
	stu_t *stu2 = (stu_t *)data2;
	return strcmp(stu1->name,stu2->name);
}

int cmp_stu_pass(void *data1,void *data2)	//比较学生密码
{
	stu_t *stu1 = (stu_t *)data1;
	stu_t *stu2 = (stu_t *)data2;
	return strcmp(stu1->spass,stu2->spass);
}

int cmp_stu_age(void *data1,void *data2)	//比较学生年龄
{
	stu_t *stu1 = (stu_t *)data1;
	stu_t *stu2 = (stu_t *)data2;
	return stu1->age - stu2->age;
}

int cmp_stu_class(void *data1,void *data2)	//比较学生所在班级
{
	stu_t *stu1 = (stu_t *)data1;
	stu_t *stu2 = (stu_t *)data2;
	return stu1->classid - stu2->classid;
}

int cmp_stu_Cgrade(void *data1,void *data2)	//比较学生C语言成绩
{
	stu_t *stu1 = (stu_t *)data1;
	stu_t *stu2 = (stu_t *)data2;
	return stu1->C - stu2->C;
}

int cmp_stu_math(void *data1,void *data2)	//比较学生数学成绩
{
	stu_t *stu1 = (stu_t *)data1;
	stu_t *stu2 = (stu_t *)data2;
	return stu1->math - stu2->math;
}

int cmp_stu_chinese(void *data1,void *data2)	//比较学生语文成绩
{
	stu_t *stu1 = (stu_t *)data1;
	stu_t *stu2 = (stu_t *)data2;
	return stu1->chinese - stu2->chinese;
}

int cmp_stu_total(void *data1,void *data2)	//比较学生总成绩
{
	stu_t *stu1 = (stu_t *)data1;
	stu_t *stu2 = (stu_t *)data2;
	return (stu1->chinese + stu1->math + stu1->C) - (stu2->chinese + stu2->math + stu2->C);
}

/*
		##：学生登录验证
		流程：A：1.学号密码登录		2.名字密码登录
			  B：循环与学生链表存放的数据据遍历比较
			  C：账号（学号或密码）与密码正确进入学生操作界面
			  D:账号信息错误，输入3次后退回上一级界面
*/
int student_login(node_t *stuhead)
{
	int count = 3;
	while(count--)
	{
		system("clear");
		puts("\t	******学生登录界面******");
		puts("\t	******[1]:学号和密码登录******");
		puts("\t	******[2]:名字和密码登录******");
		puts("\t	******[0]:退出登录******");
		puts("\t========================================");
		stu_t *stu = (stu_t *)malloc(sizeof(stu_t));		//为存放输入信息的结构体指针申请一定大小的堆空间
		SYSERR(NULL,==,stu,"malloc error",-1);
		node_t *res = stuhead->next;

		printf("\t 请选择登录方式：");
		int way = -1;
		scanf("%d",&way);
		putchar(10);
		getchar();
		putchar('\n');
		puts("\tOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO");
		switch(way)
		{
		case 0 : return -1;
		case 1 : printf("\t请输入学生学号：");
				 scanf("%d",&stu->sid);
				 printf("\t请输入学生的登录密码：");
				 scanf("%s",stu->spass);
				 while(res != stuhead)
				 {
					 if(!cmp_stu_sid(((stu_t *)res->data),stu))
						 if(!strcmp(((stu_t *)res->data)->spass,stu->spass))
						 {
							 student_menu(stuhead,(stu_t *)res->data);
							 free(stu);
							 stu = NULL;	//释放结构体指针，以免造成内存泄漏，浪费内存
							 return 0;
						 }
					 res = res->next;
				 }
				 break;
		case 2 : printf("\t请输入学生姓名：");
				 scanf("%s",stu->name);
				 printf("\t请输入学生的登录密码：");
				 scanf("%s",stu->spass);
				 while(res != stuhead)
				 {
					 if(!strcmp(((stu_t *)res->data)->name,stu->name))
					 {
						 if(!strcmp(((stu_t *)res->data)->spass,stu->spass))
						 {
							 student_menu(stuhead,(stu_t *)res->data);
							 free(stu);
							 stu = NULL;	//释放结构体指针，以免造成内存泄漏，浪费内存
							 return 0;
						 }
					 }
					 res = res->next;
				 }
				 break;
		default : puts("\t没有此选项，请重新输入！");
		}
		
		printf("\t用户名或密码错误，您还有%d次机会重新输入!\n",count);
		free(stu);
		stu = NULL;		//释放结构体指针，以免造成内存泄漏，浪费内存
		mypause();
	}
	return 0;
}


node_t *load_student()		//加载学生链表
{
	node_t *stuhead = create_dlist();
	FILE* fp = fopen(STUDENT,"r");
	SYSERR(NULL,==,fp,"fopen error",NULL);

	stu_t t = {0};
	while(fscanf(fp,"%d	%s	%s	%s	%d	%d	%d	%d	%d	%d\n",&t.sid,t.name,t.spass,t.sex,
&t.age,&t.classid,&t.C,&t.math,&t.chinese,&t.total) != EOF)	//判断是否读取到文件末尾
	{
		insert_tdlist(stuhead,&t,sizeof(stu_t));	//将学生结构体变量里的数据插入到学生链表尾部
		bzero(&t,sizeof(t));	//清空学生结构体变量里面的数据
	}
	fclose(fp);
	return stuhead;
}


void save_student(node_t *stuhead)	//保存学生的信息到指定文件中
{
	SYSERR(NULL,==,stuhead,"stuhead is NULL",);
	FILE *fp = fopen(STUDENT,"w");
	SYSERR(NULL,==,fp,"fopen error",);

	node_t *temp = stuhead->next;
	stu_t *p = NULL;
	while(temp != stuhead)
	{
		p = (stu_t *)temp->data;	//将学生链表存储的数据给学生结构体指针p
		fprintf(fp,"%d	%s	%s	%s	%d	%d	%d	%d	%d	%d\n",p->sid,p->name,p->spass,p->sex,p->age,p->classid,p->C,p->math,p->chinese,(p->C + p->math + p->chinese));
		//将学生链表存储的数据写入被宏定义的student.txt文件里面
		temp = temp->next;
	}
	fclose(fp);
}

int order_set_student(node_t *stuhead)	//将学生结构体的order（序号）正序输出
{
	SYSERR(NULL,==,stuhead,"stuhead is NULL",-1);
	node_t *temp = stuhead->next;
	int count = 0;
	while(temp != stuhead)
	{
		((stu_t *)temp->data)->order = ++count;
		temp = temp->next;
	}
	return 0;
}

int niorder_set_student(node_t *stuhead)	//将学生结构体的order（序号）逆序输出
{
	SYSERR(NULL,==,stuhead,"stuhead is NULL",-1);
	node_t *temp = stuhead->next;
	int count = length_dlist(stuhead);	
	//将学生链表的长度赋值给count,再循环递减逆序输出
	while(temp != stuhead)
	{
		((stu_t *)temp->data)->order = count--;
		temp = temp->next;
	}
	return 0;
}

