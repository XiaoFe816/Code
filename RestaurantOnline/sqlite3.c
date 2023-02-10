#include "common.h"

int main(int argc, char *argv[])
{

	int ret = sqlite3_open("./menu.db", &db);
	if (ret != SQLITE_OK)
	{
		printf("error : %s\n", sqlite3_errmsg(db));
		exit(-1);
	}
	printf("数据库打开/建立成功!\n");
	sql_copy(db);
	kucun_delete(db);
	kucun_insert(db);
	kucun_init(db);
	int i, a = 1;

	while (a)
	{	
		menu_f();
		printf("请输入: ");
		scanf("%d", &i);
		switch (i)
		{
			case 0 : return -1;//当输入0　退出系统
			case 1 : menu_msg(db) ; break;//查看目录
			case 2 : menu_insert(db); break;//添加菜品
			case 3 : menu_delete(db); break;//删除菜品
			case 4 : menu_update(db); break;//修改菜品
			case 5 : kucun_msg(db); break;//查看库存
			case 6 : sql_msg(db,"money"); break;//查看库存
			case 7 : sql_msg(db,"dingdan"); break;//查看订单
			case 8 : fu(); break;//链接客户端
		}
		printf("是否继续操作 (1是/0否)");
		scanf("%d",&a);
		system("clear");
	}
	sqlite3_exec(db,"delete from dingdan;",NULL,NULL,NULL);
	sqlite3_close(db);
	return 0;
}
