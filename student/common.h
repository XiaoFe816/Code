/************************************************************************************
**						@->>作者：廖铁钢
**						@->>版本：2.0
**						@->>设计日期：2021-8-12
*************************************************************************************/

ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "dlist.h"

#define USERNAME "admin"
#define PASSWORD "admin"
#define TEACHER "teacher.txt"
#define STUDENT "student.txt"

#define SYSERR(x,option,y,m,z) if( (x) option (y) )\
{\
	printf("%s:%s:%d:%s\n",__FILE__,__func__,__LINE__,m);\
	return z;\
}


#define PTEACHER "\t序列号	编号	姓名	密码  性别	年龄	薪资\n"
#define PSTUDENT "\t序列号	学号	姓名	密码  性别	年龄	班级	C语言	数学	语文	总成绩\n"
#define PSGRADE "\t序列号	学号	姓名	性别	班级	C语言	数学	语文	总成绩\n"

typedef struct teacher
{
	int order;	//序号
	int tid;	//教师工号
	char tname[30]; //教师名字
	char tpass[20]; //教师密码
	char sex[10];	//教师性别
	int age;	//教师年龄
	int salary;	//教师薪资
}th_t;	//建立教师结构体，并给该结构体类型取别名:th_t

typedef struct student
{
	int order;	//序号
	int sid;	//学生学号
	char name[30];	//学生名字
	char spass[20]; //学生密码
	char sex[10];	//学生性别
	int age;	//学生年龄
	int classid;	//学生班级
	int C;		//C语言成绩
	int math;	//数学成绩
	int chinese;	//语文成绩
	int total;	//总成绩
}stu_t;	//建立学生结构体，并给该结构体类型取别名:stu_t


//功能：使程序暂时处于暂停状态，按2下会车程序继续运行
//参数：无
//返回值：无
void mypause(void);


//功能：对数据num进行地址传递,判断数据是否在指定范围内
//参数：整型指针数据：num
//返回值：无
void num_range(int *num);


//功能：只确认是否保存链表存放的学生的数据
//参数：学生链表头节点：stuhead
//返回值：无
void ifsave(node_t *stuhead);


//功能：只确认是否保存链表存放的教师的数据
//参数：教师链表头节点：th_head
//返回值：无
void ifsave_th(node_t *th_head);


//功能：比较教师编号大小
//参数：任意型数据*data1,*data2
//返回值：@数据1>数据2 返回大于0的整型数
//	 @数据1=数据2 返回0
//	 @数据1<数据2 返回小于0的整型数
int cmp_th_tid(void *data1,void *data2);


//功能：比较教师名字的ASCII值大小
//参数：任意型数据*data1,*data2
//返回值：@数据1>数据2 返回大于0的整型数
//	@数据1=数据2 返回0
//	@数据1<数据2 返回小于0的整型数
int cmp_th_tname(void *data1,void *data2);


//功能：比较教师密码的ASCII值大小
//参数：任意型数据*data1,*data2
//返回值：@数据1>数据2 返回大于0的整型数
//	@数据1=数据2 返回0
//	@数据1<数据2 返回小于0的整型数
int cmp_th_tpass(void *data1,void *data2);


//功能：比较教师年龄大小
//参数：任意型数据*data1,*data2
//返回值：@数据1>数据2 返回大于0的整型数
//	@数据1=数据2 返回0
//	@数据1<数据2 返回小于0的整型数
int cmp_th_age(void *data1,void *data2);


//功能：比较教师薪水大小
//参数：任意型数据*data1,*data2
//返回值：@数据1>数据2 返回大于0的整型数
//	 @数据1=数据2 返回0
//	 @数据1<数据2 返回小于0的整型数
int cmp_th_salary(void *data1,void *data2);
/******************************************************************/
/******************************************************************/
//功能：比较学生学号大小
//参数：任意型数据*data1,*data2
//返回值：@数据1>数据2 返回大于0的整型数
//	  @数据1=数据2 返回0
//	  @数据1<数据2 返回小于0的整型数
int cmp_stu_sid(void *data1,void *data2);


//功能：比较学生名字ASCII值大小
//参数：任意型数据*data1,*data2
//返回值：@数据1>数据2 返回大于0的整型数
//	@数据1=数据2 返回0
//	@数据1<数据2 返回小于0的整型数
int cmp_stu_name(void *data1,void *data2);


//功能：比较学生密码ASCII值大小
//参数：任意型数据*data1,*data2
//返回值：@数据1>数据2 返回大于0的整型数
//	@数据1=数据2 返回0
//	@数据1<数据2 返回小于0的整型数
int cmp_stu_pass(void *data1,void *data2);


//功能：比较学生年龄大小
//参数：任意型数据*data1,*data2
//返回值：@数据1>数据2 返回大于0的整型数
//	@数据1=数据2 返回0
//	@数据1<数据2 返回小于0的整型数
int cmp_stu_age(void *data1,void *data2);


//功能：比较学生所在班级大小
//参数：任意型数据*data1,*data2
//返回值：@数据1>数据2 返回大于0的整型数
//	@数据1=数据2 返回0
//	 @数据1<数据2 返回小于0的整型数
int cmp_stu_class(void *data1,void *data2);


//功能：比较学生C语言成绩大小
//参数：任意型数据*data1,*data2
//返回值：@数据1>数据2 返回大于0的整型数
//	@数据1=数据2 返回0
//	@数据1<数据2 返回小于0的整型数
int cmp_stu_Cgrade(void *data1,void *data2);


//功能：比较学生数学成绩大小
//参数：任意型数据*data1,*data2
//返回值：@数据1>数据2 返回大于0的整型数
//	 @数据1=数据2 返回0
//	@数据1<数据2 返回小于0的整型数
int cmp_stu_math(void *data1,void *data2);


//功能：比较学生语文成绩大小
//参数：任意型数据*data1,*data2
//返回值：@数据1>数据2 返回大于0的整型数
//	@数据1=数据2 返回0
//	@数据1<数据2 返回小于0的整型数
int cmp_stu_chinese(void *data1,void *data2);


//功能：比较学生总成绩大小
//参数：任意型数据*data1,*data2
//返回值：@数据1>数据2 返回大于0的整型数
//	@数据1=数据2 返回0
//	@数据1<数据2 返回小于0的整型数
int cmp_stu_total(void *data1,void *data2);


//功能：进入主界面，并将教师链表和学生链表的头节点的地址进行值传递
//参数：教师链表头节点：th_head
//	学生链表的头节点:student
//返回值：函数运行成功返回0，失败返回非0值
int menu(node_t *th_head,node_t *stuhead);

/******************************************/
//		###管理员操作函数###
/******************************************/

//功能：进入管理员登录界面，并将教师链表和学生链表的头节点的地址进行值传递
//参数：教师链表头节点：th_head
//	学生链表的头节点:student
//返回值：函数运行成功返回0，失败返回非0值
int manager_login(node_t *th_head,node_t *stuhead);


//功能：进入管理员操作界面，并将教师链表和学生链表的头节点的地址进行值传递
//参数：教师链表头节点：th_head
//	学生链表的头节点:student
//返回值：函数运行成功返回0，失败返回非0值
int manager_menu(node_t *th_head,node_t*stuheadh);

/******************************************/
//		###教师操作函数###
/******************************************/


//功能：加载教师链表
//参数：无
//返回值：教师链表的头节点的地址
node_t *load_teacher();


//功能：教师全部信息排序，并将教师链表的头节点的进行地址传递
//参数：教师链表的头节点的地址：th_head
//返回值：函数运行成功返回0，失败返回非0值
int teacher_all(node_t *th_head);

//功能：教师登录验证，并将教师链表和学生链表的头节点的进行地址传递
//参数：教师链表的头节点的地址：th_head
//	学生链表的头节点的地址：stuhead
//返回值：函数运行成功返回0，失败返回非0值
int teacher_login(node_t *th_head,node_t *stuhead);


//功能：进入教师操作界面，并将教师链表、学生链表的头节点和当前教师的结构体数据进行地址传递
//参数：教师链表的头节点的地址：th_head
//	学生链表的头节点的地址：stuhead
//	登录验证成功后在链表中找到当前教师的结构体数据：th	
//返回值：函数运行成功返回0，失败返回非0值
int teacher_menu(node_t *th_head,node_t *stuhead,th_t *th);


//功能：执行添加教师操作，并将教师链表的头节点的进行地址传递
//参数：教师链表的头节点的地址：th_head
//返回值：函数运行成功返回0，失败返回非0值
int add_teacher(node_t *th_head);


//功能：执行删除教师操作，并将教师链表的头节点进行地址传递
//参数：教师链表的头节点的地址：th_head
//返回值：函数运行成功返回0，失败返回非0值
int delete_teacher(node_t *th_head);


//功能：执行修改教师信息的操作，并将教师链表的头节点进行地址传递
//参数：教师链表的头节点的地址：th_head
//返回值：函数运行成功返回0，失败返回非0值
int updata_teacher(node_t *th_head);


//功能：执行查找教师操作，并将教师链表的头节点进行地址传递
//参数：教师链表的头节点的地址：th_head
//返回值：函数运行成功返回0，失败返回非0值
int find_teacher(node_t *th_head);


//功能：对教师结构体的成员order进行正序排序，并将教师链表的头节点进行地址传递
//参数：教师链表的头节点的地址：th_head
//返回值：函数运行成功返回0，失败返回非0值
int order_set_teacher(node_t *th_head);


//功能：对教师结构体的成员order进行逆序排序，并将教师链表的头节点进行地址传递
//参数：教师链表的头节点的地址：th_head
//返回值：函数运行成功返回0，失败返回非0值
int niorder_set_teacher(node_t *th_head);


//功能：教师修改学生的各项成绩，并将学生链表的头节点进行地址传递
//参数：学生链表的头节点的地址：stuhead
//返回值：函数运行成功返回0，失败返回非0值
int updata_grade(node_t *stuhead);


//功能：教师修改个人信息，并将教师链表的头节点和当前教师的结构体数据进行地址传递
//参数：教师链表的头节点的地址：th_head
//	当前教师的结构体指针的地址：th
//返回值：函数运行成功返回0，失败返回非0值
int teacher_updata_menu(node_t *th_head,th_t *th);


//功能：是否保存教师信息，并将教师链表的头节点进行地址传递
//参数：教师链表的头节点的地址：th_head
//返回值：无
void save_teacher(node_t *th_head);


//功能：单个显示教师全部信息
//参数：任意型数据：(void) *data
//返回值：无
void show_teacher(void *data);

/******************************************/
//		###学生操作函数###
/******************************************/

//功能：加载学生表
//参数：无
//返回值：学生链表的头节点的地址
node_t *load_student();


//功能：学生登录验证，并将学生链表的头节点进行地址传递
//参数：学生链表的头节点的地址：stuhead
//返回值：函数运行成功返回0，失败返回非0值
int student_login(node_t *stuhead);


//功能：学生操作界面，并将学生链表的头节点和当前学生的结构体数据进行地址传递
//参数：学生链表的头节点的地址：stuhead
//	登录验证成功的学生的结构体指针的地址：stu
//返回值：函数运行成功返回0，失败返回非0值
int student_menu(node_t *stuhead,stu_t *stu);

//功能：显示学生全部信息，并将学生链表的头节点的地址进行地址传递
//参数：学生链表的头节点的地址：stuhead
//返回值：函数运行成功返回0，失败返回非0值
int student_all(node_t *stuhead);


//功能：添加学生，并将学生链表的头节点进行地址传递
//参数：学生链表的头节点的地址：stuhead
//返回值：函数运行成功返回0，失败返回非0值
int add_student(node_t* stuhead);


//功能：删除学生，并将学生链表的头节点进行地址传递
//参数：学生链表的头节点的地址：stuhead
//返回值：函数运行成功返回0，失败返回非0值
int delete_student(node_t *stuhead);


//功能：修改学生信息，并将学生链表的头节点进行地址传递
//参数：学生链表的头节点的地址：stuhead
//返回值：函数运行成功返回0，失败返回非0值
int updata_student(node_t *stuhead);


//功能：对学生结构体的成员order进行正序排序，并将学生链表的头节进行地址传递
//参数：学生链表的头节点的地址：stuhead
//返回值：函数运行成功返回0，失败返回非0值
int find_student(node_t *stuhead);


//功能：查找学生，并将学生链表的头节点进行地址传递
//参数：学生链表的头节点的地址：stuhead
//返回值：函数运行成功返回0，失败返回非0值
int order_set_student(node_t *stuhead);

//功能：对学生结构体的成员order进行逆序排序，并将学生链表的头节点进行地址传递
//参数：学生链表的头节点的地址：stuhead
//返回值：函数运行成功返回0，失败返回非0值
int niorder_set_student(node_t *stuhead);


//功能：单个显示学生全部信息
//参数：任意型数据：(void)*data
//返回值：无
void show_student(void *data);

//功能：单个显示学生成绩信息
//参数：任意型数据：(void)*data
//返回值：无
void student_grade(void *data);


//功能：是否保存学生师信息，并将学生链表的头节点进行地址传递
//参数：学生链表的头节点的地址：stuhead
//返回值：无
void save_student(node_t *stuhead);

#endif


