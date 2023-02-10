/************************************************************************************
**						@->>作者：廖铁钢
**						@->>版本：2.0
**						@->>设计日期：2021-8-12
*************************************************************************************/

#include "common.h"

/*
	##：打印教师结构体的全部数据到屏幕上
*/
void show_teacher(void *data)
{
	th_t *thp = (th_t *)data;
	puts("\t_____________________________________________________________________");
	printf("\t%d	%d	%s	%s	%s	%d	%d\n",thp->order,thp->tid,thp->tname,thp->tpass,thp->sex,thp->age,thp->salary);
}

int cmp_th_tid(void *data1,void *data2)	//比较教师工号
{
	th_t *th1 = (th_t *)data1;
	th_t *th2 = (th_t *)data2;
	return th1->tid - th2->tid;
}

int cmp_th_tname(void *data1,void *data2)	//比较教师名字
{
	th_t *th1 = (th_t *)data1;
	th_t *th2 = (th_t *)data2;
	return strcmp(th1->tname,th2->tname);
}

int cmp_th_tpass(void *data1,void *data2)	//比较教师密码
{
	th_t *th1 = (th_t *)data1;
	th_t *th2 = (th_t *)data2;
	return strcmp(th1->tpass,th2->tpass);
}
int cmp_th_age(void *data1,void *data2)	//比较教师年龄
{
	th_t *th1 = (th_t *)data1;
	th_t *th2 = (th_t *)data2;
	return th1->age - th2->age;
}

int cmp_th_salary(void *data1,void *data2)	//比较教师薪水
{
	th_t *th1 = (th_t *)data1;
	th_t *th2 = (th_t *)data2;
	return th1->salary - th2->salary;
}

/*
		##：教师登录验证
		流程：A：(学号 + 名字 + 密码 )登录
			  B：循环与教师链表存放的数据据遍历比较
			  C：账号信息正确进入学生操作界面
			  D:账号信息错误，输入3次后退回上一级界面
*/
int teacher_login(node_t *th_head,node_t *stuhead)
{
	int count = 3;
	while(count--)
	{
		system("clear");
		puts("\t	******学生登录界面******");
		puts("\t	******[1]:学号、名字和密码登录******");
		puts("\t	******[0]:退出登录******");
		puts("\t========================================");
		th_t th[1] = {0};
		node_t *res = th_head->next;

		printf("\t 请选择登录方式：");
		int way = -1;
		scanf("%d",&way);
		putchar(10);
		putchar('\n');
		puts("\t=======================================");
		switch(way)
		{
		case 0 : return -1;
		case 1 : printf("\t请输入教师工号：");
				 scanf("%d",&th->tid);
				 printf("\t请输入教师的名字：");
				 scanf("%s",th->tname);
				 printf("\t请输入教师的登录密码：");
				 scanf("%s",th->tpass);
				 while(res != th_head)
				 {
					 if(!cmp_th_tid(((th_t *)res->data),th) && !strcmp(((th_t *)res->data)->tname,th->tname))
						 if(!strcmp(((th_t *)res->data)->tpass,th->tpass))
						 {
							 teacher_menu(th_head,stuhead,(th_t *)res->data);
							 return 0;
						 }
					 res = res->next;
				 }

				 printf("\t用户名或密码错误，您还有%d次机会重新输入!\n",count);
				 mypause();
				 break;
		default : puts("\t没有此选项，请重新输入！");
				  mypause();
		}

	}
	return 0;
}


int teacher_updata_menu(node_t *th_head,th_t *th)	//教师对个人信息的修改
{
	int i = -1;
	while(i)
	{
		system("clear");
		printf("\t\t	   ——————教师个人信息修改界面——————\n");
		printf("\t\t———————————————	   欢迎您！！！	———————————————\n");
		printf("\t\t———————————————	  %s奥特曼	———————————————\n",th->tname);
		puts("\t\t=================================================");
		puts("\t\t*********	[1].修改姓名		********");
		puts("\t\t*********	[2].修改密码		********");
		puts("\t\t*********	[3].修改年龄		********");
		puts("\t\t*********	[0].退出 		********");
		puts("\t\t————————————————————————————————————————————————");
		printf("\t\t请输入您的选择：");
		scanf("%d",&i);
		switch(i)
		{
		case 0 : return -1;
		case 1 : printf("\t请输入新名字：");
				 scanf("%s",th->tname);
				 printf(PTEACHER);
				 show_teacher(th);
				 break; 
		case 2 : printf("\t请输入新密码：");
				 scanf("%s",th->tpass);
				 printf(PTEACHER);
				 show_teacher(th);
				 break; 
		case 3 : printf("\t请输入新年龄：");
				 scanf("%d",&th->age);
				 printf(PTEACHER);
				 show_teacher(th);
				 break; 
		default : printf("输入错误，请重新选择：\n");
				  mypause();
		}
		ifsave_th(th_head);
		mypause();
	}
	return 0;
}


int add_teacher(node_t *th_head)	//管理员新添教师信息
{
	while(1)
	{
		system("clear");
		th_t thp[10] = {0};
		printf("\t请输入新教师工作编号：");
		scanf("%d",&thp->tid);
		node_t *res = find_vdlist(th_head,&thp->tid,cmp_th_tid);
		if(NULL != res)	//编号是唯一的，判断新输入的编号是否重复
		{
			puts("\t此工作编号已被使用,请换个工号录入信息!");
			mypause();
			break;
		}
		printf("\t请输入新教师名字：");
		scanf("%s",thp->tname);
		printf("\t请输入新教师系统的密码：");
		scanf("%s",thp->tpass);
		printf("\t请输入新教师性别：");
		scanf("%s",thp->sex);
		printf("\t请输入新教师年龄(1~100)：");
		scanf("%d",&thp->age);
		num_range(&thp->age);
		printf("\t请输入新教师薪水：");
		scanf("%d",&thp->salary);
		puts("");
		puts("\t***********************************************");

		insert_tdlist(th_head,thp,sizeof(th_t)); //将新添的教师数据插入到链表尾部
		order_set_teacher(th_head);
		printf(PTEACHER);		//打印教师信息栏
		show_hdlist(th_head,show_teacher); //从链表头到链表尾显示教师信息
		ifsave_th(th_head);
		mypause();
		break;
	}
	return 0;
}

/*
			##：删除教师的信息
			流程：1.从链表尾到链表头显示教师信息
				  2.输入被删除教师的数据
				  3.观察数据是否被删除
*/
int delete_teacher(node_t *th_head)		
{
	while(1)
	{
		th_t *th = (th_t  *)malloc(sizeof(th_t)); //申请堆空间
		SYSERR(NULL,==,th,"malloc error",-1);
		system("claer");
		puts("\t\t	VVVVVVVV 教师信息删除界面 VVVVVVVV");
		puts("\t\t			[1]:按工号删除教师");
		puts("\t\t			[2]:按名字删除教师");
		puts("\t\t			[3]:按年龄删除教师");
		puts("\t\t			[4]:按薪资删除教师");
		puts("\t\t			[0]:退出");
		puts("\t############################################");
		int ch = -1;
		printf("\t请输入要删除的选项:");
		scanf("%d",&ch);
		switch(ch)
		{
		case 0 : return -1;
		case 1 : order_set_teacher(th_head);
				 printf(PTEACHER);		
				 show_tdlist(th_head,show_teacher);
				 printf("\t请输入要删除的教师的工号:");
				 scanf("%d",&th->tid);
				 while(delete_vdlist(th_head,th,cmp_th_tid) == 0);
				 order_set_teacher(th_head);
				 show_tdlist(th_head,show_teacher);
				 break;
		case 2 : order_set_teacher(th_head);
				 printf(PTEACHER);
				 show_tdlist(th_head,show_teacher);
				 printf("\t请输入要删除的教师的名字:");
				 scanf("%s",th->tname);
				 while(delete_vdlist(th_head,th,cmp_th_tid) == 0);
				 order_set_teacher(th_head);
				 show_tdlist(th_head,show_teacher);
				 break;
		case 3 : order_set_teacher(th_head);
				 printf(PTEACHER);
				 show_tdlist(th_head,show_teacher);
				 printf("\t请输入要删除的教师的年龄:");
				 scanf("%d",&th->age);
				 while(delete_vdlist(th_head,th,cmp_th_tid) == 0);
				 order_set_teacher(th_head);
				 show_tdlist(th_head,show_teacher);
				 break;
		case 4 : order_set_teacher(th_head);
				 printf(PTEACHER);
				 show_tdlist(th_head,show_teacher);
				 printf("\t请输入要删除的教师的薪水:");
				 scanf("%d",&th->salary);
				 while(delete_vdlist(th_head,th,cmp_th_tid) == 0);
				 order_set_teacher(th_head);
				 show_tdlist(th_head,show_teacher);
				 break;
		default : puts("\t 指令有误,请再次输入!");
				  mypause();
		}
		free(th);
		th = NULL; //释放内存
		mypause();
	}
	return 0;
}

/*
			##：修改教师的信息
			流程：1.输入被删除教师的工作编号（唯一性）
				  2.按工号指定修改教师的数据
				  3.观察数据是否被修改
*/
int updata_teacher(node_t *th_head)
{
	int ch = -1;
	node_t *res = th_head;
	while(1)
	{
		system("clear");
		puts("\t\t	————————————————教师信息修改界面 ————————————————");
		puts("\t\t	==========	 [1]:按工号修改名字	==========");
		puts("\t\t	==========	 [2]:按工号修改密码	==========");
		puts("\t\t	==========	 [3]:按工号修改年龄	==========");
		puts("\t\t	==========	 [4]:按工号修改薪水	==========");
		puts("\t\t	==========	 [0]:退出	==========");
		puts("\t***********************************************************");
		printf("\t	请输入被修改学生的学号：");
		th_t th1 = {0};
		scanf("%d",&th1.tid);
		if(0 == th1.tid)
			return 0;
		res = find_vdlist(th_head,&th1,cmp_th_tid);
		if(NULL == res)
		{
			puts("\t此工号不存在，无法使用，请重新录入信息！");
			mypause();
			continue;
		}
		th_t *thp = (th_t *)res->data;
		printf("\t请输入要修改的数据项：");
		scanf("%d",&ch);
		switch(ch)
		{
		case 0 : return -1;
		case 1 : printf("\t请输入新名字：");
				 scanf("%s",thp->tname);
				 printf(PTEACHER);
				 show_student(thp);
				 break;
		case 2 : printf("\t请输入新密码：");
				 scanf("%s",thp->tpass);
				 printf(PTEACHER);
				 show_student(thp);
				 break;
		case 3 : printf("\t请输入新年龄(1~100)：");
				 scanf("%d",&thp->age);
				 num_range(&thp->age);
				 printf(PTEACHER);
				 show_student(thp);
				 break;
		case 4 : printf("\t请输入新的薪资：");
				 scanf("%d",&thp->salary);
				 printf(PTEACHER);
				 show_student(thp);
				 break;
		default : puts("输入有误，请重新输入！");
				  mypause();
		}
		thp = NULL;
		ifsave_th(th_head);
		mypause();
		break;
	}
	return 0;
}

/*
			##：查询教师的信息
			流程：1.输入所要查找教师的数据
				  2.观察打印信息是否存在所查询的教师
*/
int find_teacher(node_t *th_head)
{
	while(1)
	{
		system("clear");
		puts("\t\t	*####*	教师信息查询界面	*####*");
		puts("\t---------------------------------------------------------");
		printf("\t\t	[1]:按工号查找教师\n");
		printf("\t\t	[2]:按名字查找教师\n");
		printf("\t\t	[3]:按年龄查找教师\n");
		printf("\t\t	[4]:按薪资查找教师\n");
		printf("\t\t	[0]:退出\n");
		puts("\t==========================================================");
		printf("\t\t请输入您的选择：");
		th_t thp[3] = {0};
		node_t *res = th_head;
		node_t *p = create_dlist();
		int ch = -1;
		scanf("%d",&ch);
		puts("\t_________________________________________________________");
		switch(ch)
		{
		case 1 : printf("\t请输入要查找的教师的工号：");
				 scanf("%d",&thp->tid);
				 res = find_vdlist(th_head,thp,cmp_th_tid);
				 if(NULL != res)
				 {
					 printf(PTEACHER);
					 order_set_teacher(th_head);
					 show_teacher(res->data);
				 }
				 break;
		case 2 : printf("\t请输入要查找的教师的名字：");
				 scanf("%s",thp->tname);
				 while((res = find_vdlist(res,thp,cmp_th_tname)) != NULL)
					 insert_tdlist(p,res->data,sizeof(th_t));
				 printf(PTEACHER);
				 order_set_teacher(th_head);
				 show_hdlist(p,show_teacher);
				 break;
		case 3 : printf("\t请输入要查找的教师的年龄：");
				 scanf("%d",&thp->age);
				 while((res = find_vdlist(res,thp,cmp_th_age)) != NULL)
					 insert_tdlist(p,res->data,sizeof(th_t));
				 printf(PTEACHER);
				 order_set_teacher(th_head);
				 show_hdlist(p,show_teacher);
				 break;
		case 4 : printf("\t请输入要查找的教师的薪水：");
				 scanf("%d",&thp->salary);
				 while((res = find_vdlist(res,thp,cmp_th_salary)) != NULL)
					 insert_tdlist(p,res->data,sizeof(th_t));
				 printf(PTEACHER);
				 order_set_teacher(th_head);
				 show_hdlist(p,show_teacher);
				 break;
		case 0 : return -1;
		default : printf("\t指令输入有误，请再次输入\n");
				  mypause();
		}
		destroy_dlist(&p);
		mypause();
	}

	return 0;
}

/*
			##：指定模式显示教师的信息
			流程：1.输入排序显示的模式
				  2.观察打印信息是否排列正确
*/
int teacher_all(node_t *th_head)
{
	int choice = -1;
	while(choice)
	{
		system("clear");
		puts("\t\t	￥￥￥	教师信息界面	￥￥￥");
		puts("\t\t___________________________________________________");
		printf("\t\t [1]按学号递增排序		[2]按学号递减排序\n");
		printf("\t\t [3]按名字递增排序		[4]按名字递减排序\n");
		printf("\t\t [5]按年龄递增排序		[6]按年龄递减排序\n");
		printf("\t\t [7]按薪水递增排序		[8]按薪水递减排序\n");
		printf("\t\t ==================[0]:退出===================\n");
		printf("\t\t请输入您的选择：");
		scanf("%d",&choice);
		switch(choice)
		{
		case 0: return -1;
		case 1: maopao_sortdlist(th_head,cmp_th_tid);
				order_set_teacher(th_head);
				printf(PTEACHER);
				show_hdlist(th_head,show_teacher);
				break;
		case 2: maopao_sortdlist(th_head,cmp_th_tid);
				niorder_set_teacher(th_head);
				printf(PTEACHER);
				show_tdlist(th_head,show_teacher);
				break;
		case 3: maopao_sortdlist(th_head,cmp_th_tname);
				order_set_teacher(th_head);
				printf(PTEACHER);
				show_hdlist(th_head,show_teacher);
				break;
		case 4: maopao_sortdlist(th_head,cmp_th_tname);
				niorder_set_teacher(th_head);
				printf(PTEACHER);
				show_tdlist(th_head,show_teacher);
				break;
		case 5: maopao_sortdlist(th_head,cmp_th_age);
				order_set_teacher(th_head);
				printf(PTEACHER);
				show_hdlist(th_head,show_teacher);
				break;
		case 6: maopao_sortdlist(th_head,cmp_th_age);
				niorder_set_teacher(th_head);
				printf(PTEACHER);
				show_tdlist(th_head,show_teacher);
				break;
		case 7: maopao_sortdlist(th_head,cmp_th_salary);
				order_set_teacher(th_head);
				printf(PTEACHER);
				show_hdlist(th_head,show_teacher);
				break;
		case 8: maopao_sortdlist(th_head,cmp_th_salary);
				niorder_set_teacher(th_head);
				printf(PTEACHER);
				show_tdlist(th_head,show_teacher);
				break;
		default: printf("输入有误，请重新输入：\n");
				 mypause();
		}
		mypause();
	}
	ifsave_th(th_head);
	return 0;
}

node_t *load_teacher()	//加载教师链表
{
	node_t *th_head = create_dlist();
	FILE* fp = fopen(TEACHER,"r");
	SYSERR(NULL,==,fp,"fopen error",NULL);

	th_t th = {0};
	while(fscanf(fp,"%d	%s	%s	%s	%d	%d\n",&th.tid,th.tname,th.tpass,th.sex,&th.age,&th.salary) != EOF)	//判断是否读取到文件末尾
	{
		insert_tdlist(th_head,&th,sizeof(stu_t));
		//将教师结构体变量里的数据插入到教师链表尾部
		bzero(&th,sizeof(th));
		//清空教师结构体变量里面的数据
	}
	fclose(fp);
	return th_head;
}

void save_teacher(node_t *th_head)	//保存教师的信息到指定文件中
{
	SYSERR(NULL,==,th_head,"th_head is NULL",);
	FILE *fp = fopen(TEACHER,"w");
	SYSERR(NULL,==,fp,"fopen error",);

	node_t *temp = th_head->next;
	th_t *p = NULL;
	while(temp != th_head)
	{
		p = (th_t *)temp->data;	//将学生链表存储的数据给教师结构体指针p
		fprintf(fp,"%d	%s	%s	%s	%d	%d\n",p->tid,p->tname,p->tpass,p->sex,p->age,p->salary);
		//将教师链表存储的数据写入被宏定义的teacher.txt文件里面
		temp = temp->next;
	}
	fclose(fp);
}

int order_set_teacher(node_t *th_head)//将教师结构体的order（序号）正序输出
{
	SYSERR(NULL,==,th_head,"th_head is NULL",-1);
	node_t *temp = th_head->next;
	int count = 0;
	while(temp != th_head)
	{
		((stu_t *)temp->data)->order = ++count;
		temp = temp->next;
	}
	return 0;
}

int niorder_set_teacher(node_t *th_head)//将教师结构体的order（序号）逆序输出
{
	SYSERR(NULL,==,th_head,"th_head is NULL",-1);
	node_t *temp = th_head->next;
	int count = length_dlist(th_head);
	//将教师链表的长度赋值给count,再循环递减逆序输出
	while(temp != th_head)
	{
		((stu_t *)temp->data)->order = count--;
		temp = temp->next;
	}
	return 0;
}


