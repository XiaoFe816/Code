#include "common.h"

int main()
{

	//1.　创建socket
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0)

	{
		perror("socket is error\n");
		return -1;
	}

	//2.　链接服务器
	struct sockaddr_in ser;
	ser.sin_family = AF_INET; //PF_INET
	ser.sin_port = htons(8888);
	ser.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(ser.sin_zero, 0, sizeof(ser.sin_zero));

	int ret = connect(fd, (struct sockaddr *)&ser, sizeof(ser));
	if (ret < 0)
	{
		perror("connect error\n");
		return -2;
	}

	sqlite3_open("./menu.db", &db);
	sql_copy(db);	//将菜谱的信息拷贝到菜谱结构体中
	kucun_init(db); //将库存的信息拷贝到库存结构体中
	int len_menu = 0;
	while(mu[len_menu].mid != 0)
		len_menu++;
	int sum = 0;

	char *errmsg1 = NULL;
	char sqlbuf3[128] = "";
	xianshi(len_menu);
	int c = 1;
	int x = 0; 
	user_t user = {0};	  //定义用户结构体
	user.fd = fd;

	printf("请输入桌号：");
	scanf("%d", &user.tableid);
	printf("请输入名字：");
	scanf("%s", user.name);
	if (0 == user_insert(db, &user))
		printf("用户验证成功\n");

	int i, j;
	for (i = 0; i < 10; i++)
	{
		dd[i].zz = user.tableid;		   //将桌号写进订单的结构体数组中
		dd[i].statu = 1;				   //订单的状态1
		strcpy(dd[i].username, user.name); //将名字写进订单结构体数组中
	}
	xianshi(len_menu);
	for (i = 0; i < M_SIZE; i++)
	{
		printf("请选择菜品编号：");
		scanf("%d", &dd[i].mid);
		if (!dd[i].mid)
			break;
		printf("请选择份数：");
		scanf("%d", &dd[i].num);
		puts("继续点餐中...,结束点餐请输入[0]");
	}

	int len_order = 0;
	while (dd[len_order].mid != 0)
		len_order++;
	printf("len_menu = %d\n", len_menu);
	printf("len_order = %d\n", len_order);
	for (x = 0; x < len_menu; x++) //将订单写入数据库中的订单表
	{
		for (i = 0; i < len_order; i++)
		{
			if (mu[x].mid == dd[i].mid)
			{
				dd[i].price = mu[i].price;
				strcpy(dd[i].name, mu[x].name);
				dd[i].total = mu[i].price * dd[i].num;
				bzero(sqlbuf3, 128);
				sprintf(sqlbuf3, "insert into dingdan(菜名编号,菜名,价格,份数,总计) values(%d,'%s',%d,%d,%d);", dd[i].zz, dd[i].name, dd[i].price, dd[i].num, dd[i].total);
				if (sqlite3_exec(db, sqlbuf3, NULL, NULL, &errmsg1) != 0)
					SQL_ERROR(errmsg1, -3);
				sum += dd[i].total;
			}
		}
	}

	char buff[128] = "";
	sprintf(buff,"%d",user.tableid);
	send(fd,buff,sizeof(buff), 0);
	// 更新库存
	for (x = 0; x < len_menu; x++)
	{
		// printf("%d	%s	%d\n",ku[x].mid,ku[x].name,ku[x].num);
		for (i = 0; i < len_order; i++)
		{
			if (ku[x].mid == dd[i].mid)
			{
				ku[x].num -= dd[i].num;
				kucun_updata(db,ku[x]);
			}
		}
	}

	mon_t money; //定义营业额的结构体变量
	money.orderid = user.tableid;
	strcpy(money.order_name, user.name);
	money.money = sum;
	Money_insert(db, &money);

	int buy = -1;
	while (buy) //买单
	{
		system("clear");
		printf("请确认您的订单:\n");
		dingdan(len_order);
		printf("您一共消费了:%d￥\n", sum);
		printf("[0]买单		[1]稍后\n");
		puts("===========================");
		scanf("%d", &buy);
		if (!buy)
		{
			system("clear");
			printf("请收好您的账单:\n");
			puts("===========================");
			dingdan(len_order);
			printf("总计                :%d￥\n", sum);
			user_delete(db,user);
		}
		sleep(2);
	}

	close(fd);
	return 0;
}

int xianshi(int len)
{
	system("clear");
	printf("\n\n\t\t————————————————————————————菜单—————————————————————————\n");
	printf("\t\t");
	puts(MENU_MSG);
	for (i = 0; i < len; i++) //显示菜谱信息
	{
		printf("\t\t%d\t\t%s   \t%d\t%d\n", mu[i].mid, mu[i].name, mu[i].price, mu[i].vipp);
		puts("\t\t—————————————————————————————————————————————————————————");
	}
	return 0;
}

int dingdan(int len)
{
	puts(ORDER_MSG);
	for (i = 0; i < len; i++) //显示菜谱信息
	{
		printf("%d | %s %d | %d | %d\n",dd[i].zz, dd[i].name, dd[i].price, dd[i].num, dd[i].total);
		puts("—————————————————————————");
	}
	return 0;
}