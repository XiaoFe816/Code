#include "common.h"

int fu()
{

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("socket is error\n");
        exit(-1);
    }

    //2.绑定服务器
    struct sockaddr_in addr;
    addr.sin_family = PF_INET;
    addr.sin_port = htons(8888);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int ret = bind(fd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0)
    {
        printf("bind error\n");
        exit(-1);
    }

    //3.监听
    ret = listen(fd, 1);
    if (ret < 0)
    {
        perror("listen error\n");
        exit(-1);
    }
    //4.accept
    struct sockaddr_in clientaddr;
    socklen_t len = sizeof(clientaddr);
    int newfd = accept(fd, (struct sockaddr *)&clientaddr, &len);
    printf("链接成功!\n");
    char buff[128] = "";
    char *errmsg1 = NULL;
    while (1)
    {
        ret = recv(newfd, buff, sizeof(buff), 0);
        if (ret <= 0)
        {
            printf("客户点餐完毕\n");
            break;
        }
    }
    
    printf("%s\n",buff);//显示桌号
    char sqlbuff[128];
    bzero(sqlbuff,128);
    puts(ORDER_MSG);
	sprintf(sqlbuff,"select * from dingdan where 菜名编号 = %s;",buff);
	if(sqlite3_exec(db,sqlbuff,sql_values,NULL,&errmsg1) != 0)
		SQL_ERROR(errmsg1,-3);
/*
    char *sqlbuf2 = "delete from dingdan;";
	sqlite3_exec(db, sqlbuf2, NULL, NULL, &errmsg1);
*/	
    return 0;
}
