/************************************************************************************
**						@->>作者：廖铁钢
**						@->>版本：2.0
**						@->>设计日期：2021-8-12
*************************************************************************************/

#include "common.h"
 
int main()
{
	node_t *stuhead = load_student();	//加载学生链表
	node_t *th_head = load_teacher();	//加载教师链表
	SYSERR(NULL,==,stuhead,"create_dlist error",-1);
	SYSERR(NULL,==,th_head,"create_dlist error",-1);
	menu(th_head,stuhead);		//进入主界面
	ifsave(stuhead);
	destroy_dlist(&stuhead);	//销毁学生链表
	destroy_dlist(&th_head);	//销毁教师链表
	return 0;
}
