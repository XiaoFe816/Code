#include "common.h"


char *errmsg = NULL;
char sqlbuf2[128] = "";

/************************
作用：查看菜谱目录
参数1：数据库的地址
返回值：成功返回0　失败返回非0
************************/
int menu_msg(sqlite3 *sql)
{
	puts("\t\t\t=======================菜单=========================");
	putchar(10);
	char *sqlbuf1 = "select * from menu;";//显示menu表中的所有内容
	if (sqlite3_exec(sql, sqlbuf1, sql_name, NULL, &errmsg) != 0)//sql_name的回调函数，作用是显示表名
		SQL_ERROR(errmsg, -2);
	
	if (sqlite3_exec(sql, sqlbuf1, sql_values, NULL, &errmsg) != 0)//sql_value的回调函数，作用是显示表中的内容
		SQL_ERROR(errmsg, -3);
	putchar(10);
	puts("====================================");
	return 0;
}

/************************
作用：查看菜谱目录
参数1：数据库的地址
返回值：成功返回0　失败返回非0
************************/
int sql_copy(sqlite3 *sql)
{

	char *sqlbuf1 = "select * from menu;";//显示menu表中的所有内容
	if (sqlite3_exec(sql, sqlbuf1, menu_copy, NULL, &errmsg) != 0)//menu_copy的回调函数，作用是复制菜谱目录表中的内容
		SQL_ERROR(errmsg, -2);
	putchar(10);
	puts("====================================");
	return 0;

}
/**************************
作用：查看自己下单的菜谱
参数1：数据库的地址
返回值：成功返回0　失败返回非0
***************************/
int menu_msg1(sqlite3 *sql)
{
	puts("====================================");
	putchar(10);
	char *sqlbuf1 = "select * from kehu;";//显示库存表中的所有内容
	if (sqlite3_exec(sql, sqlbuf1, sql_name, NULL, &errmsg) != 0)//sql_name的回调函数，作用是显示表名
		SQL_ERROR(errmsg, -2);
	
	if (sqlite3_exec(sql, sqlbuf1, sql_values, NULL, &errmsg) != 0)//sql_value的回调函数，作用时显示表中的内容
		SQL_ERROR(errmsg, -3);
	putchar(10);
	puts("====================================");
	return 0;
}

/**************************
作用：查看自己下单的菜谱
参数1：数据库的地址
参数2：表名
返回值：成功返回0　失败返回非0
**************************/
int sql_msg(sqlite3 *sql,const char *ch)
{
	char sqlbuf1[128] = "";
	sprintf(sqlbuf1,"select * from %s;",ch);
	if(sqlite3_exec(sql,sqlbuf1,sql_values,NULL,&errmsg) != 0)//sql_value的回调函数，作用时显示表中的内容
		SQL_ERROR(errmsg,-2);
	return 0;
}

/**************************
作用：查看库存目录
参数1：数据库的地址
返回值：成功返回0　失败返回非0
**************************/
int kucun_msg(sqlite3 *sql)
{
	puts("====================================");
	putchar(10);
	char *sqlbuf1 = "select * from kucun;";//显示库存表中的所有内容
	if (sqlite3_exec(sql, sqlbuf1, sql_name, NULL, &errmsg) != 0)//sql_name的回调函数，作用是显示表名
		SQL_ERROR(errmsg, -2);
	if (sqlite3_exec(sql, sqlbuf1, sql_values, NULL, &errmsg) != 0)//sql_value的回调函数，作用时显示表中的内容
		SQL_ERROR(errmsg, -3);
	putchar(10);
	puts("====================================");
	return 0;
}

/**************************
作用：查看库存目录
参数1：数据库的地址
返回值：成功返回0　失败返回非0
**************************/
int kucun_init(sqlite3 *sql)
{
	char *sqlbuf1 = "select * from kucun;";//显示库存表中的所有内容
	if (sqlite3_exec(sql, sqlbuf1, kucun_copy, NULL, &errmsg) != 0)//kucun_copy的回调函数，作用是复制库存表中的内容
		SQL_ERROR(errmsg, -2);
	return 0;
}

/**************************
作用：回调函数：显示表名
参数1：传进来的值
参数2：列
参数3：表中的内容
参数4：表名
返回值：成功返回0　失败返回非0
**************************/
int sql_name(void *para, int num, char **f_value, char **f_name)
{
	static int flag = 1;//设置一个静态变量　因为回调函数有内置循环
	 if (flag != 0)
	 {
		for (i = 0; i < num; i++)
		{
			if (i == num - 1)
			{
				printf("%s\n", f_name[i]);//打印表名
				break;
			}
			printf("%s | ", f_name[i]);
		}
	 }
	flag = 0;
	return 0;
}

/**************************
作用：回调函数：显示表中的内容
参数1：传进来的值
参数2：列
参数3：表中的内容
参数4：表名
返回值：成功返回0　失败返回非0
**************************/
int sql_values(void *para, int num, char **f_value, char **f_name)
{
	for (i = 0; i < num; i++)
	{
		if (i == num - 1)
		{
			printf("%s\n", f_value[i]);//打印表名
			break;
		}
		printf("%s | ", f_value[i]);
	}
	return 0;
}

/**************************
作用：添加菜品
参数1：数据库的地址
返回值：成功返回0　失败返回非0
**************************/
int menu_insert(sqlite3 *sql)
{
	putchar(10);
	menu_msg(db);//显示菜谱
	putchar(10);
	int i = 1;
	mu_t marr[2];
	while (i)
	{
		bzero(sqlbuf2, 128);
		printf("请录入新菜编号:");
		scanf("%d", &marr->mid);
		printf("请录入新菜菜名:");
		scanf("%s", marr->name);
		printf("请录入新菜成本价格");
		scanf("%d", &marr->cbprice);
		printf("请录入新菜卖出价格:");
		scanf("%d", &marr->price);
		printf("请录入新菜卖出会员价:");
		scanf("%d", &marr->vipp);
		printf("请录入新菜的库存:");
		scanf("%d", &marr->kucun);
		sprintf(sqlbuf2, "insert into menu(菜品编号,菜名,价格,会员价格) values(%d,'%s',%d,%d);", marr->mid, marr->name, marr->price, marr->vipp);
		if (sqlite3_exec(sql, sqlbuf2, NULL, NULL, &errmsg) != 0)
			SQL_ERROR(errmsg, -3);
		sprintf(sqlbuf2, "insert into kucun(菜名编号,菜名,数量) values(%d,'%s',%d);", marr->mid, marr->name, marr->kucun);
		if (sqlite3_exec(sql, sqlbuf2, NULL, NULL, &errmsg) != 0)
			SQL_ERROR(errmsg, -3);

		putchar(10);
		menu_msg(db);
		putchar(10);
		puts("====================================");
		printf("是否继续添加:　(1是/0否)");
		scanf("%d", &i);
	}

	return 0;
}

/*******************************
作用：将桌号，名字，fd插入user的表中
参数1：数据库的地址
参数2：user_t类型的结构体指针
返回值：成功返回0　失败返回非0
********************************/
int user_insert(sqlite3 *sql,user_t *user)
{
	bzero(sqlbuf2,128);
	sprintf(sqlbuf2,"insert into user(桌号,名字,fd) values(%d,'%s',%d);",user->tableid,user->name,user->fd);
	if(sqlite3_exec(sql,sqlbuf2,NULL,NULL,&errmsg) != 0)
		SQL_ERROR(errmsg,-3);
	return 0;
}

/**************************
作用：删除菜品
参数1：数据库的地址
返回值：成功返回0　失败返回非0
**************************/
int menu_delete(sqlite3 *sql)
{
	int i = 1;
	mu_t marr[2];
	while (i)
	{
		putchar(10);
		menu_msg(db);//打印出菜谱
		putchar(10);
		bzero(sqlbuf2, 128);
		printf("请输入要删除的菜品的编号:");//通过菜品编号来删除表中的菜品
		scanf("%d", &marr->mid);

		sprintf(sqlbuf2, "delete from menu where 菜品编号 = %d;", marr->mid);//删除菜谱目录中的菜谱
		if (sqlite3_exec(sql, sqlbuf2, NULL, NULL, &errmsg) != 0)
			SQL_ERROR(errmsg, -3);
		sprintf(sqlbuf2, "delete from kucun where 菜名编号 = %d;", marr->mid);//删除库存表中的菜谱
		if (sqlite3_exec(sql, sqlbuf2, NULL, NULL, &errmsg) != 0)
			SQL_ERROR(errmsg, -3);

		putchar(10);
		menu_msg(db);
		putchar(10);
		puts("====================================");
		printf("是否继续删除:　(1是/0否)");
		scanf("%d", &i);
	}
	return 0;
}

/**********************************
作用：从订单表中显示输入的桌号的那一栏信息
参数1：数据库的地址
参数2：订单结构体类型的指针
返回值：成功返回0　失败返回非0
**********************************/
int order_msg(sqlite3* sql,int num)
{
	bzero(sqlbuf2,128);
	sprintf(sqlbuf2,"select * from dingdan where 菜名编号 = %d;",num);
	if(sqlite3_exec(sql,sqlbuf2,sql_values,NULL,&errmsg) != 0)
		SQL_ERROR(errmsg,-3);
	return 0;
}

/**********************************
作用：从订单表中删除输入的桌号的那一栏信息
参数1：数据库的地址
参数2：订单结构体类型的指针
返回值：成功返回0　失败返回非0
**********************************/
int order_delete(sqlite3* sql,int num)
{
	bzero(sqlbuf2,128);
	sprintf(sqlbuf2,"delete from dingdan where 菜名编号 = %d ;",num);
	if(sqlite3_exec(sql,sqlbuf2,NULL,NULL,&errmsg) != 0)
		SQL_ERROR(errmsg,-3);
	return 0;
}

/**********************************
作用：向money(营业额)表中插入信息
参数1：数据库的地址
参数2：营业额结构体类型的指针
返回值：成功返回0　失败返回非0
**********************************/
int Money_insert(sqlite3* sql,mon_t* dollr)
{
	bzero(sqlbuf2,128);
	sprintf(sqlbuf2,"insert into money(订单号,点餐者,money) values(%d,'%s',%d);",dollr->orderid,dollr->order_name,dollr->money);
	if(sqlite3_exec(sql,sqlbuf2,NULL,NULL,&errmsg) != 0)
		SQL_ERROR(errmsg,-3);

	return 0;
}

/**********************************
作用：向money(营业额)表中插入信息
参数1：数据库的地址
参数2：营业额结构体类型的指针
返回值：成功返回0　失败返回非0
**********************************/
int kucun_insert(sqlite3 *sql)
{
	int i = 0;
	int len_menu = 0;
	while (mu[len_menu].mid != 0)//判断目录类型的结构体中的菜品编号是否等于0
		len_menu++;
	for (i = 0; i<len_menu; i++)
	{
		mu[i].kucun = 100;
		sprintf(sqlbuf2, "insert into kucun(菜名编号,菜名,数量) values(%d,'%s',%d);", mu[i].mid, mu[i].name, mu[i].kucun);
		if (sqlite3_exec(db, sqlbuf2, NULL, NULL, &errmsg) != 0)
			SQL_ERROR(errmsg, -3);
	}
	return 0;
}

/**********************************
作用：通过socket描述符锁定用户
参数1：数据库的地址
参数2：客户结构体类型的指针
返回值：成功返回0　失败返回非0
**********************************/
int user_delete(sqlite3 *sql,user_t user)
{
	bzero(sqlbuf2,128);
	sprintf(sqlbuf2,"delete from user where 桌号= %d",user.tableid);
	if(sqlite3_exec(sql,sqlbuf2,NULL,NULL,&errmsg) != 0)
		SQL_ERROR(errmsg,-4);
	return 0;
}


/**********************************
作用：清空库存信息
参数1：数据库的地址
返回值：成功返回0　失败返回非0
**********************************/
int kucun_delete(sqlite3 *sql)
{
	bzero(sqlbuf2,128);
	sprintf(sqlbuf2,"delete from kucun");
	if(sqlite3_exec(sql,sqlbuf2,NULL,NULL,&errmsg) != 0)
		SQL_ERROR(errmsg,-4);
	return 0;
}


/**********************************
作用：清空库存信息
参数1：数据库的地址
返回值：成功返回0　失败返回非0
**********************************/
int menu_update(sqlite3 *sql)
{
	int i = 1;
	mu_t marr[2] = {0};
	bzero(sqlbuf2, 128);

	putchar(10);
	menu_msg(db);
	putchar(10);

	puts("***********************************");
	printf("[1]->修改菜品编号\n");
	printf("[2]->使用菜品编号修改价格\n");
	printf("[3]->使用菜品编号修改会员价格\n");
	printf("[0]->退出\n");
	puts("***********************************");
	int ch;
	printf("请选择:");
	while (i)
	{
		scanf("%d", &ch);
		switch (ch)
		{
		case 1:
			printf("请输入要修改的菜品的编号:");
			scanf("%d", &marr->mid);
			printf("请输入菜品的新编号:");
			scanf("%d", &marr->id);
			sprintf(sqlbuf2, "update menu set 菜品编号 = %d where 菜品编号 = %d;", marr->id, marr->mid);
			if (sqlite3_exec(sql, sqlbuf2, NULL, NULL, &errmsg) != 0)
				SQL_ERROR(errmsg, -3);
			break;
		case 2:
			printf("请输入要修改的菜品的编号:");
			scanf("%d", &marr->mid);
			printf("请输入要修改的菜品的价格:");
			scanf("%d", &marr->price);
			sprintf(sqlbuf2, "update menu set 价格 = %d where 菜品编号 = %d;", marr->price, marr->mid);
			if (sqlite3_exec(sql, sqlbuf2, NULL, NULL, &errmsg) != 0)
				SQL_ERROR(errmsg, -3);
			break;
		case 3:
			printf("请输入要修改的菜品的编号:");
			scanf("%d", &marr->mid);
			printf("请输入要修改的菜品的会员价格:");
			scanf("%d", &marr->vipp);
			sprintf(sqlbuf2, "update menu set 会员价格 = %d where 菜品编号 = %d;", marr->vipp, marr->mid);
			if (sqlite3_exec(sql, sqlbuf2, NULL, NULL, &errmsg) != 0)
				SQL_ERROR(errmsg, -3);
			break;
		}
		putchar(10);
		menu_msg(db);
		putchar(10);
		puts("====================================");
		putchar(10);
		printf("是否继续修改:　(1是/0否)");
		scanf("%d", &i);
	}
}



/**********************************
作用：拷贝菜谱目录中的值
参数1：数据库的地址
参数2：列
参数3：表中的数据
参数4：表名
返回值：成功返回0　失败返回非0
**********************************/
int menu_copy(void *para,int num,char** f_value,char** f_name)
{
	printf("****************%d\n",m);
	// printf("%d %s %d %d\n",atoi(&f_value[0][m]),&f_value[1][m],atoi(&f_value[2][m]),atoi(&f_value[3][m]));

	for(i=0 ; i<num ; i++)
	{
		if(0 == i)
		{
			printf("%s |",f_value[i]);
			mu[m].mid = atoi(&f_value[0][i]);
		}
		if(1 == i)
		{
			printf("%s |",f_value[i]);
			strcpy(mu[m].name,f_value[i]);
		}
		if(2 == i)
		{
			printf("%s |",f_value[i]);
			mu[m].price = atoi(&(*(f_value[i])));
		}
		if(i == num-1)
		{
			printf("%s\n",f_value[i]);
			mu[m].vipp = atoi(&(*(f_value[i])));
			break;
		}	
	}
	printf("%d %s %d %d\n",mu[m].mid,mu[m].name,mu[m].price,mu[m].vipp);
	m++;	
	return 0;
}

/**********************************
作用：拷贝库存中的值
参数1：数据库的地址
参数2：列
参数3：表中的数据
参数4：表名
返回值：成功返回0　失败返回非0
**********************************/
int kucun_copy(void *para,int num,char** f_value,char** f_name)
{
	printf("****************%d\n",k);
	// printf("%d %s %d %d\n",atoi(&f_value[0][m]),&f_value[1][m],atoi(&f_value[2][m]),atoi(&f_value[3][m]));

	for(i=0 ; i<num ; i++)
	{
		if(0 == i)
		{
			printf("%s |",f_value[i]);
			ku[k].mid = atoi(&f_value[0][i]);
		}
		if(1 == i)
		{
			printf("%s |",f_value[i]);
			strcpy(ku[k].name,f_value[i]);
		}
		if(i == num-1)
		{
			printf("%s\n",f_value[i]);
			ku[k].num = atoi(&(*(f_value[i])));
			break;
		}	
	}
	printf("%d %s %d\n",ku[k].mid,ku[k].name,ku[k].num);
	k++;	
	return 0;
}

/**********************************
作用：修改库存信息
参数1：数据库的地址
参数2：库存结构体类型的指针
返回值：成功返回0　失败返回非0
**********************************/
int kucun_updata(sqlite3* sql,ku_t kucun)
{
	bzero(sqlbuf2,128);
	sprintf(sqlbuf2,"update kucun set 数量=%d where 菜名编号 = %d;",kucun.num,kucun.mid);
	if(sqlite3_exec(sql,sqlbuf2,NULL,NULL,&errmsg) != 0)
		SQL_ERROR(errmsg,-3);

	return 0;
}