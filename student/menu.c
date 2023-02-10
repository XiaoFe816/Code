/************************************************************************************
**						@->>作者：廖铁钢
**						@->>版本：2.0
**						@->>设计日期：2021-8-12
*************************************************************************************/

#include "common.h"

void num_range(int *num)	//判断数据是否越界
{
	while(*num >= 100 || *num < 0)
	{
		printf("\t数据超出范围！请再次输入：");
		scanf("%d",num);
	}
}

void mypause(void)	//暂时使程序停止
{
	puts("按回车键继续");
	getchar();
	getchar();
	getchar();
}

void ifsave(node_t *stuhead)	//是否保存学生信息
{
	int choose = -1;
	puts("\t 是否保存信息：[0]:存档 	[others]:不存档");
	puts("*************************************************************");
	printf("\t\t\t请选择：");
	scanf("%d",&choose);
	if(!choose)
		save_student(stuhead);
}

void ifsave_th(node_t *th_head) //是否保存教师信息
{
	int choose = -1;
	puts("\t 是否保存信息：[0]:存档 	[others]:不存档");
	puts("*************************************************************");
	printf("\t\t\t请选择：");
	scanf("%d",&choose);
	if(!choose)
		save_teacher(th_head);
}

int menu(node_t *th_head,node_t *stuhead) //主界面
{
	int ch = -1;
	while(ch)
	{
		system("clear");
		printf("\t\t *=*=*   欢迎进入学生信息管理系统  *=*=*  \t\t\n");
		puts("\t\t————————	加载中...	————————");
		puts("------------------------------------------------------------------------------");
		//		sleep(1);
		printf("\t\t ********	①  管理员登录	********\n");
		printf("\t\t ********	②  教师登录	********\n");
		printf("\t\t ********	③  学生登录	********\n");
		printf("\t\t ********	0 ：退出	********\n");
		puts("\t\t------------------------------------------");
		printf("\t\t请输入您的选择：");
		scanf("%d",&ch);
		getchar();
		puts("");
		puts("\t\tWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
		switch(ch)
		{
		case 1 : manager_login(th_head,stuhead);
				 break;
		case 2 : teacher_login(th_head,stuhead);
				 break;
		case 3 : student_login(stuhead);
				 break;
		case 0 : break;
		default : printf("\t输入错误，请重新选择：\n");
				  mypause();
		}
	}
	return 0;
}


/*
		##：管理员登录验证
		流程：A：输入账号信息
			  B：判断登录信息是否正确
			  C:账号信息错误，输入3次后回到主界面
*/
int manager_login(node_t *th_head,node_t *stuhead)
{
	int count = 3;
	char name[20] = "";
	char pass[20] = "";

	while(count--)
	{
		printf("\t\t￥请输入管理员的用户名￥：");
		scanf("%s",name);
		puts("\t\t======================================");
		printf("\t\t￥请输入管理员的用户名￥：");
		scanf("%s",pass);
		puts("\t\t======================================");

		if( !strcmp(name,USERNAME) && !strcmp(pass,PASSWORD))
		{
			manager_menu(th_head,stuhead);
			return 0;
		}
		else
			printf("\t用户名或密码错误，您还有%d次重新输入的机会！\n",count);
		mypause();
	}
	return 0;
}


int manager_menu(node_t *th_head,node_t *stuhead) //管理员操作界面
{
	int ch = -1;
	while(ch)
	{
		system("clear");
		printf("\t\t		 ——————管理员界面——————\n");
		puts("\t\t————————————————————	加载中...	————————————————————");
		puts("\t\t%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
		//		sleep(2);
		puts("\t\t	*********	[1].查看学生信息	********");
		puts("\t\t	*********	[2].修改学生信息	********");
		puts("\t\t	*********	[3].增添学生		********");
		puts("\t\t	*********	[4].查找学生		********");
		puts("\t\t	*********	[5].删除学生		********");
		puts("\t\t	*********	[6].查看教师信息	********");
		puts("\t\t	*********	[7].修改教师信息	********");
		puts("\t\t	*********	[8].添加教师		********");
		puts("\t\t	*********	[9].查找教师		********");
		puts("\t\t	*********	[10.删除教师		********");
		puts("\t\t	*********	[0].退出 		********");
		puts("\t\t========================================================");
		printf("\t\t请输入您的选择：");
		scanf("%d",&ch);
		switch(ch)
		{
		case 1 : student_all(stuhead);
				 break;
		case 2 : updata_student(stuhead);
				 break; 
		case 3 : add_student(stuhead);
				 break; 
		case 4 : find_student(stuhead);
				 break; 
		case 5 : delete_student(stuhead);
				 break; 
		case 6 : teacher_all(th_head);
				 break; 
		case 7 : updata_teacher(th_head);
				 break; 
		case 8 : add_teacher(th_head);
				 break; 
		case 9 : find_teacher(th_head); 
				 break; 
		case 10 : delete_teacher(th_head);
				  break; 
		case 0 : break;
		default : printf("输入错误，请重新选择：\n");
				  mypause();
		}
	}
	return 0;
}

int teacher_menu(node_t *th_head,node_t *stuhead,th_t *th) //教师操作界面
{
	int ch = -1;
	while(ch)
	{
		system("clear");
		printf("\t\t	   ——————教师界面——————\n");
		printf("\t\t———————————————	   欢迎您！!！	———————————————	\n");
		printf("\t\t———————————————	 %s奥特曼	———————————————	\n",th->tname);
		puts("\t\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
		puts("\t\t*********	[1].查看个人信息	********");
		puts("\t\t*********	[2].修改个人信息	********");
		puts("\t\t*********	[3].查看所有学生信息	********");
		puts("\t\t*********	[4].查找学生信息	********");
		puts("\t\t*********	[5].修改学生成绩	********");
		puts("\t\t*********	[0].退出 		********");
		puts("\t\t————————————————————————————————————————————————");
		printf("\t\t请输入您的选择：");
		scanf("%d",&ch);
		switch(ch)
		{
		case 1 : printf(PTEACHER);
				 order_set_teacher(th_head);
				 show_teacher(th);
				 break;
		case 2 : teacher_updata_menu(th_head,th);
				 break;
		case 3 : student_all(stuhead);
				 break; 
		case 4 : find_student(stuhead);
				 break; 
		case 5 : updata_grade(stuhead);
				 break; 
		case 0 : return -1;
		default : printf("输入错误，请重新选择：\n");
				  mypause();
		}
		mypause();
	}
	return 0;
}


int updata_grade(node_t *stuhead)  //教师修改指定学号的学生的成绩
{
	int ch = -1;
	node_t *res = stuhead;
	while(1)
	{
		system("clear");
		puts("\t\t	————————————————学生信息修改界面 ————————————————");
		puts("\t\t	==========	 [1]:按学号修改C语言成绩==========");
		puts("\t\t	==========	 [2]:按学号修改数学成绩	==========");
		puts("\t\t	==========	 [3]:按学号修改语文成绩	==========");
		puts("\t\t	==========	 [0]:退出		==========");
		puts("\t***********************************************************");
		printf("\t	请输入被修改学生的学号：");
		stu_t stu = {0};
		scanf("%d",&stu.sid);
		if(0 == stu.sid)
			return 0;
		res = find_vdlist(stuhead,&stu,cmp_stu_sid);
		if(NULL == res)
		{
			puts("\t此学号不存在，无法使用，请重新录入信息！");
			mypause();
			continue;
		}
		stu_t *stup = (stu_t *)res->data;
		printf("\t请输入要修改的数据项：");
		scanf("%d",&ch);
		switch(ch)
		{
		case 0 : return 0;
		case 1 : printf("\t请输入新C语言成绩(1~100)：");
				 scanf("%d",&stup->C);
				 num_range(&stup->C);
				 printf(PSGRADE);
				 student_grade(stup);
				 break;
		case 2 : printf("\t请输入新数学成绩(1~100)：");
				 scanf("%d",&stup->math);
				 num_range(&stup->C);
				 printf(PSGRADE);
				 student_grade(stup);
				 break;
		case 3 : printf("\t请输入新语文成绩(1~100)：");
				 scanf("%d",&stup->chinese);
				 num_range(&stup->C);
				 printf(PSGRADE);
				 student_grade(stup);
				 break;
		default : printf("输入有误，请重新输入！\n");
				  mypause();
		}
		break;
	}
	mypause();
	ifsave(stuhead);
	return 0;
}

int student_menu(node_t *stuhead,stu_t *stu) //学生操作界面
{
	int ch = -1;
	while(ch)
	{
		system("clear");
		printf("\t\t	   ——————学生个人界面——————\n");
		printf("\t\t————————	您好！假面骑士%s	————————\n",stu->name);
		puts("\t\t			请稍等......");
		puts("\t\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
		sleep(1);
		puts("\t\t*********	[1].查看个人信息	********");
		puts("\t\t*********	[2].修改姓名		********");
		puts("\t\t*********	[3].修改密码		********");
		puts("\t\t*********	[4].修改年龄		********");
		puts("\t\t*********	[5].查看所有学生成绩	********");
		puts("\t\t*********	[0].退出 		********");
		puts("\t\t————————————————————————————————————————————————");
		printf("\t\t请输入您的选择：");
		scanf("%d",&ch);
		switch(ch)
		{
		case 1 : printf(PSTUDENT);
				 order_set_student(stuhead);
				 show_student(stu);
				 break;
		case 2 : printf("\t请输入新名字：");
				 scanf("%s",stu->name);
				 printf(PSGRADE);
				 show_student(stu);
				 break; 
		case 3 : printf("\t请输入新密码：");
				 scanf("%s",stu->spass);
				 printf(PSGRADE);
				 show_student(stu);
				 break; 
		case 4 : printf("\t请输入新年龄（1~100）：");
				 scanf("%d",&stu->age);
				 num_range(&stu->age);
				 printf(PSGRADE);
				 show_student(stu);
				 break; 
		case 5 : maopao_sortdlist(stuhead,cmp_stu_total);
				 niorder_set_student(stuhead);
				 printf(PSGRADE);
				 show_tdlist(stuhead,student_grade);
				 break; 
		case 0 : break;
		default : printf("输入错误，请重新选择：\n");
				  mypause();
		}
		mypause();
	}
	ifsave(stuhead);
	return 0;
}


/*
			##：指定模式显示学生的全部信息
			流程：1.输入排序显示的模式
				  2.观察打印信息是否排列正确
*/
int student_all(node_t *stuhead)	
{
	int choice = -1;
	while(choice)
	{
		system("clear");
		puts("\t\t	￥￥￥	学生信息界面	￥￥￥");
		puts("\t\t___________________________________________________");
		printf("\t\t [1]按学号递增排序		[2]按学号递减排序\n");
		printf("\t\t [3]按C语言成绩递增排序		[4]按C语言成绩递减排序\n");
		printf("\t\t [5]按数学成绩递增排序		[6]按数学成绩递减排序\n");
		printf("\t\t [7]按语文成绩递增排序		[8]按语文成绩递减排序\n");
		printf("\t\t [9]按总成绩递增排序		[10]按总成绩递减排序\n");
		printf("\t\t ==================[0]:退出===================\n");
		printf("\t\t请输入您的选择：");
		scanf("%d",&choice);
		switch(choice)
		{
		case 0: return -1;
		case 1: maopao_sortdlist(stuhead,cmp_stu_sid);
				order_set_student(stuhead);
				printf(PSTUDENT);
				show_hdlist(stuhead,show_student);
				break;
		case 2: maopao_sortdlist(stuhead,cmp_stu_sid);
				niorder_set_student(stuhead);
				printf(PSTUDENT);
				show_tdlist(stuhead,show_student);
				break;
		case 3: maopao_sortdlist(stuhead,cmp_stu_Cgrade);
				order_set_student(stuhead);
				printf(PSTUDENT);
				show_hdlist(stuhead,show_student);
				break;
		case 4: maopao_sortdlist(stuhead,cmp_stu_Cgrade);
				niorder_set_student(stuhead);
				printf(PSTUDENT);
				show_tdlist(stuhead,show_student);
				break;
		case 5: maopao_sortdlist(stuhead,cmp_stu_math);
				order_set_student(stuhead);
				printf(PSTUDENT);
				show_hdlist(stuhead,show_student);
				break;
		case 6: maopao_sortdlist(stuhead,cmp_stu_math);
				niorder_set_student(stuhead);
				printf(PSTUDENT);
				show_tdlist(stuhead,show_student);
				break;
		case 7: maopao_sortdlist(stuhead,cmp_stu_chinese);
				order_set_student(stuhead);
				printf(PSTUDENT);
				show_hdlist(stuhead,show_student);
				break;
		case 8: maopao_sortdlist(stuhead,cmp_stu_chinese);
				niorder_set_student(stuhead);
				printf(PSTUDENT);
				show_tdlist(stuhead,show_student);
				break;
		case 9: maopao_sortdlist(stuhead,cmp_stu_total);
				order_set_student(stuhead);
				printf(PSTUDENT);
				show_hdlist(stuhead,show_student);
				break;
		case 10: maopao_sortdlist(stuhead,cmp_stu_total);
				 niorder_set_student(stuhead);
				 printf(PSTUDENT);
				 show_tdlist(stuhead,show_student);
				 break;
		default: printf("输入有误，请重新输入：\n");
				 mypause();
		}
		mypause();
	}
	ifsave(stuhead);
	return 0;
}


int add_student(node_t *stuhead)	//添加学生
{
	while(1)
	{
		system("clear");
		stu_t stu_p[2] = {0};
		printf("\t请输入新学生的学号：");
		scanf("%d",&stu_p->sid);
		node_t *res = find_vdlist(stuhead,stu_p,cmp_stu_sid);
		if(NULL != res)//学号是唯一的，判断新输入的学号是否重复
		{
			puts("此学号已被使用，无法覆盖，请重新录入信息！");
			mypause();
			break;
		}
		printf("\t请输入新学生的名字：");
		scanf("%s",stu_p->name);
		printf("\t请输入新学生的登录密码：");
		scanf("%s",stu_p->spass);
		printf("\t请输入新学生的性别：");
		scanf("%s",stu_p->sex);
		printf("\t请输入新学生的年龄(1~100)：");
		scanf("%d",&stu_p->age);
		num_range(&stu_p->age);
		printf("\t请输入新学生的班级(1~100)：");
		scanf("%d",&stu_p->classid);
		num_range(&stu_p->classid);
		printf("\t请输入新学生的C语言成绩(1~100)：");
		scanf("%d",&stu_p->C);
		num_range(&stu_p->C);
		printf("\t请输入新学生的数学成绩(1~100)：");
		scanf("%d",&stu_p->math);
		num_range(&stu_p->math);
		printf("\t请输入新学生的语文成绩(1~100)：");
		scanf("%d",&stu_p->chinese);
		num_range(&stu_p->chinese);
		putchar('\n');
		puts("\t==========================");

		insert_tdlist(stuhead,stu_p,sizeof(stu_t));//将新添的学生数据插入到链表尾部
		order_set_student(stuhead);
		printf(PSTUDENT);	//打印学生信息栏
		show_hdlist(stuhead,show_student);	//从链表头到链表尾显示教师信息
		ifsave(stuhead);
		mypause();
		break;
	}
	return 0;
}

/*
			##：删除学生的信息
			流程：1.从链表尾到链表头显示学生信息
				  2.输入被删除学生的数据
				  3.观察数据是否被删除
*/
int delete_student(node_t *stuhead)
{
	while(1)
	{
		stu_t *stu = (stu_t *)malloc(sizeof(stu_t));
		system("clear");
		puts("\t\t	=======学生信息删除界面========");
		puts("\t\t		[1]:按学号删除学生信息");
		puts("\t\t		[2]:按名字删除学生信息");
		puts("\t\t		[3]:按年龄删除学生信息");
		puts("\t\t		[0]:退出");
		int ch = -1;
		printf("\t\t请输入您的选择：");
		scanf("%d",&ch);
		switch(ch)
		{
		case 0 : return -1;
		case 1 : order_set_student(stuhead);
				 printf(PSTUDENT);
				 show_tdlist(stuhead,show_student);
				 printf("\t\t请输入被删除学生的学号：");
				 scanf("%d",&stu->sid);
				 while(delete_vdlist(stuhead,stu,cmp_stu_sid) == 0);
				 order_set_student(stuhead);
				 printf(PSTUDENT);
				 show_tdlist(stuhead,show_student);
				 break;
		case 2 : order_set_student(stuhead);
				 printf(PSTUDENT);
				 show_tdlist(stuhead,show_student);
				 printf("\t\t请输入被删除学生的名字：");
				 scanf("%s",stu->name);
				 while(delete_vdlist(stuhead,stu,cmp_stu_name) == 0);
				 order_set_student(stuhead);
				 show_tdlist(stuhead,show_student);
				 break;
		case 3 : order_set_student(stuhead);
				 printf(PSTUDENT);
				 show_tdlist(stuhead,show_student);
				 printf("\t\t请输入被删除学生的年龄：");
				 scanf("%d",&stu->age);
				 while(delete_vdlist(stuhead,stu,cmp_stu_age) == 0);
				 order_set_student(stuhead);
				 show_tdlist(stuhead,show_student);
				 break;
		default : puts("输入错误，请重新输入您的选择！");
				  mypause();
		}
		free(stu);
		stu = NULL;
		mypause();
	}
	return 0;
}

/*
			##：修改学生的信息
			流程：1.输入被删除学生的工作编号（唯一性）
				  2.按学号指定修改学生的数据
				  3.观察打印信息数据是否被修改
*/
int updata_student(node_t *stuhead)
{
	int ch = -1;
	node_t *res = stuhead;
	while(1)
	{
		system("clear");
		puts("\t\t	————————————————学生信息修改界面 ————————————————");
		puts("\t\t	==========	 [1]:按学号修改名字	==========");
		puts("\t\t	==========	 [2]:按学号修改密码	==========");
		puts("\t\t	==========	 [3]:按学号修改年龄	==========");
		puts("\t\t	==========	 [4]:按学号修改班级	==========");
		puts("\t\t	==========	 [5]:按学号修改C语言成绩==========");
		puts("\t\t	==========	 [6]:按学号修改数学成绩	==========");
		puts("\t\t	==========	 [7]:按学号修改语文成绩	==========");
		puts("\t\t	==========	 [0]:退出		==========");
		puts("\t***********************************************************");
		printf("\t	请输入被修改学生的学号：");
		stu_t stu1 = {0};
		scanf("%d",&stu1.sid);
		if(0 == stu1.sid)
			return 0;
		res = find_vdlist(stuhead,&stu1,cmp_stu_sid);
		if(NULL == res)
		{
			puts("\t此学号不存在，无法使用，请重新录入信息！");
			mypause();
			continue;
		}
		stu_t *stup1 = (stu_t *)res->data;
		printf("\t请输入要修改的数据项：");
		scanf("%d",&ch);
		switch(ch)
		{
		case 0 : return 0;
		case 1 : printf("\t请输入新名字：");
				 scanf("%s",stup1->name);
				 printf(PSTUDENT);
				 show_student(stup1);
				 break;
		case 2 : printf("\t请输入新密码：");
				 scanf("%s",stup1->spass);
				 printf(PSTUDENT);
				 show_student(stup1);
				 break;
		case 3 : printf("\t请输入新年龄(1~100)：");
				 scanf("%d",&stup1->age);
				 num_range(&stup1->age);
				 printf(PSTUDENT);
				 show_student(stup1);
				 break;
		case 4 : printf("\t请输入新班级(1~100)：");
				 scanf("%d",&stup1->classid);
				 num_range(&stup1->classid);
				 printf(PSTUDENT);
				 show_student(stup1);
				 break;
		case 5 : printf("\t请输入新C语言成绩(1~100)：");
				 scanf("%d",&stup1->C);
				 num_range(&stup1->C);
				 printf(PSTUDENT);
				 show_student(stup1);
				 break;
		case 6 : printf("\t请输入新数学成绩(1~100)：");
				 scanf("%d",&stup1->math);
				 num_range(&stup1->math);
				 printf(PSTUDENT);
				 show_student(stup1);
				 break;
		case 7 : printf("\t请输入新语文成绩(1~100)：");
				 scanf("%d",&stup1->chinese);
				 num_range(&stup1->chinese);
				 printf(PSTUDENT);
				 show_student(stup1);
				 break;
		default : puts("输入有误，请重新输入！");
				  mypause();
		}
		break;
	}
	mypause();
	ifsave(stuhead);
	return 0;
}

/*
			##：查询学生的信息
			流程：1.输入所要查找学生的数据
				  2.查找数据在链表中的地址，创建临时链表存放该数据
				  3.观察打印信息是否存在所查询的学生
				  4.销毁临时链表
*/
int find_student(node_t *stuhead)
{
	while(1)
	{
		system("clear");
		puts("\t\t	*####*	学生信息查询界面	*####*");
		puts("\t---------------------------------------------------------");
		printf("\t\t	[1]:按学号查找学生\n");
		printf("\t\t	[2]:按名字查找学生\n");
		printf("\t\t	[3]:按年龄查找学生\n");
		printf("\t\t	[4]:按班级查找学生\n");
		printf("\t\t	[0]:退出\n");
		printf("\t\t请输入您的选择：");
		int ch = -1;
		stu_t *stup = (stu_t *)malloc(sizeof(stu_t)); //申请堆空间
		node_t *res = stuhead;
		node_t *p = create_dlist();
		scanf("%d",&ch);
		puts("\t_________________________________________________________");
		switch(ch)
		{
		case 1 : printf("\t请输入要查找的学生的学号：");
				 scanf("%d",&stup->sid);
				 res = find_vdlist(stuhead,stup,cmp_stu_sid);
				 if(NULL != res)
				 {
					 printf(PSTUDENT);
					 order_set_student(stuhead);
					 show_student(res->data);
				 }
				 break;
		case 2 : printf("\t请输入要查找的学生的名字：");
				 scanf("%s",stup->name);
				 while((res = find_vdlist(res,stup,cmp_stu_name)) != NULL)
					 insert_tdlist(p,res->data,sizeof(stu_t));
				 printf(PSTUDENT);
				 order_set_student(stuhead);
				 show_hdlist(p,show_student);
				 destroy_dlist(&p);
				 break;
		case 3 : printf("\t请输入要查找的学生的年龄：");
				 scanf("%d",&stup->age);
				 while((res = find_vdlist(res,stup,cmp_stu_age)) != NULL)
					 insert_tdlist(p,res->data,sizeof(stu_t));
				 printf(PSTUDENT);
				 order_set_student(stuhead);
				 show_hdlist(p,show_student);
				 destroy_dlist(&p);
				 break;
		case 4 : printf("\t请输入要查找的学生的班级：");
				 scanf("%d",&stup->classid);
				 while((res = find_vdlist(res,stup,cmp_stu_class)) != NULL)
					 insert_tdlist(p,res->data,sizeof(stu_t));
				 printf(PSTUDENT);
				 order_set_student(stuhead);
				 show_hdlist(p,show_student);
				 destroy_dlist(&p);
				 break;
		case 0 : return -1;
		default : printf("\t指令输入有误，请再次输入\n");
				  break;
		}
		free(stup);
		stup = NULL;	//释放内存
		mypause();
	}
	return 0;
}


