/************************************************************************************
**						@->>作者：廖铁钢
**						@->>版本：2.0
**						@->>设计日期：2021-8-12
*************************************************************************************/

#include "common.h"


node_t *create_dlist()
{
	node_t *head = (node_t *)malloc(sizeof(node_t));
	SYSERR(NULL,==,head,"head is null",NULL);
	head->prev = head->next = head;
	head->data = NULL;

	return head;
}


int insert_hdlist(node_t *head,void *data,int size)
{
	SYSERR(NULL,==,head,"head is null",-1);
	SYSERR(NULL,==,data,"data is null",-1);
	node_t *newnode = (node_t *)malloc(sizeof(node_t));
	SYSERR(NULL,==,newnode,"malloc error",-2);
	
	newnode->data = malloc(size);
	SYSERR(NULL,==,newnode->data,"malloc error",-2);
	memcpy(newnode->data,data,size);
	newnode->prev = head;
	
	newnode->next = head->next;
	head->next->prev = newnode;
	head->next = newnode;
	return 0;
}

void show_hdlist(node_t *head,showfun_t showfun)
{
	SYSERR(NULL,==,head,"head is null",);
	node_t *temp = head->next;
	while(temp != head && temp->data != NULL)
	{
		showfun(temp->data);
		temp = temp->next;
	}
	printf("\n");
}


void show_tdlist(node_t *head,showfun_t showfun)
{
	SYSERR(NULL,==,head,"head is null",);
	node_t *temp = head->prev;
	while(temp != head && temp->data != NULL)
	{
		showfun(temp->data);
		temp = temp->prev;
	}
	printf("\n");
}


int insert_tdlist(node_t *head,void *data,int size)
{
	SYSERR(NULL,==,head,"head is null",-1);
	SYSERR(NULL,==,data,"data is null",-1);
	node_t *newnode = (node_t *)malloc(sizeof(node_t));
	SYSERR(NULL,==,newnode,"malloc error",-2);
	
	newnode->data = malloc(size);
	SYSERR(NULL,==,newnode->data,"malloc error",-2);
	memcpy(newnode->data,data,size);
	newnode->prev = head->prev;
	newnode->next = head;

	head->prev->next = newnode;
	head->prev = newnode;
	return 0;
}


int insert_idlist(node_t *head,void *data,int size,int index)
{
	SYSERR(NULL,==,head,"head is null",-1);
	SYSERR(NULL,==,data,"data is null",-1);
	SYSERR(index,<,0,"index must >= 0",-1);
	node_t *prev = head;

	int i = 0;
	while((i++ < index) && (prev->next != head))
		prev = prev->next;

	SYSERR(head,==,prev->next,"at list end",-2);
	node_t *newnode = (node_t *)malloc(sizeof(node_t));
	SYSERR(NULL,==,newnode,"malloc error",-3);
	newnode->data = malloc(size);

	SYSERR(NULL,==,newnode->data,"malloc error",-3);
	memcpy(newnode->data,data,size);
	newnode->prev = prev;
	newnode->next = prev->next;

	prev->next->prev = newnode;
	prev->next = newnode;
	return 0;
}


node_t *find_idlist(node_t *head,int index)
{
	SYSERR(NULL,==,head,"head is null",NULL);
	SYSERR(head,==,head->next,"list is null",NULL);
	SYSERR(index,<,0,"index must >= 0",NULL);
	node_t *prev = head;
	
	int i = 0; 
	while(i++ < index && prev->next != head)
		prev = prev->next;

	SYSERR(head,==,prev->next,"at list end",NULL);
	return prev->next;
}


node_t *find_vdlist(node_t *head,void *data,cmpfun_t cmpfun)
{
	SYSERR(NULL,==,head,"head is null",NULL);
	SYSERR(head,==,head->next,"list is null",NULL);
	SYSERR(NULL,==,data,"data is null",NULL);
	node_t *temp = head->next;

	while(temp != head && (temp->data != NULL))
	{
		if(!cmpfun(temp->data,data))
			return temp;
		temp = temp->next;
	}
	return NULL;
}


int delete_hdlist(node_t *head)
{
	SYSERR(NULL,==,head,"head is null",-1);
	SYSERR(head,==,head->next,"list is null",-1);
	node_t *temp = head->next;
	head->next = temp->next;
	
	temp->next->prev = temp->prev;
	free(temp->data);
	free(temp);
	return 0;
}


int delete_tdlist(node_t *head)
{
	SYSERR(NULL,==,head,"head is null",-1);
	SYSERR(head,==,head->next,"list is null",-1);
	node_t *temp = head->prev;
	temp->next->prev = temp->prev;
	
	
	temp->prev->next = temp->next;
	free(temp->data);
	free(temp);
	return 0;
}


int delete_idlist(node_t *head,int index)
{
	SYSERR(NULL,==,head,"head is null",-1);
	SYSERR(head,==,head->next,"list is null",-1);
	SYSERR(index,<,0,"index must >= 0",-1);
	node_t *prev,*current;

	prev = head;
	int i = 0;
	while(i++ < index && prev->next != head)
		prev = prev->next;

	SYSERR(head,==,prev->next,"at list end",-1);
	current = prev->next;
	prev->next = current->next;
	current->next->prev = current->prev;
	
	free(current->data);
	free(current);
	return 0;
}


int delete_vdlist(node_t *head,void *data,cmpfun_t cmpfun)
{
	SYSERR(NULL,==,head,"head is null",-1);
	SYSERR(head,==,head->next,"list is null",-1);
	SYSERR(NULL,==,data,"data is null",-1);
	node_t *temp = head->next;
	int flag = 0;

	while(temp != head && (temp->data != NULL)) 
	{
		if(!cmpfun(temp->data,data))
		{
			flag = 1;
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			free(temp->data);
			free(temp);
			return 0;
		}
		temp = temp->next;
	}
	if(!flag)
		puts("没有此数据");
	return -1;
}


int destroy_dlist(node_t **head)
{
	SYSERR(NULL,==,*head,"head is null",-1);
	node_t *current,*next;
	current = next = (*head)->next;
	while(current != *head)
	{
		next = current->next;
		free(current->data);
		free(current);
		current = next;
	}
	
	free(*head);
	*head = NULL;
	return 0;
}


int length_dlist(node_t *head)
{
	SYSERR(NULL,==,head,"head is null",-1);
	node_t *temp = head->next;
	int i = 0;
	
	while(temp != head)
	{
		i++;
		temp = temp->next;
	}
	return i;
}


int maopao_sortdlist(node_t *head,cmpfun_t cmpfun)
{
	SYSERR(NULL,==,head,"head is null",-1);
	node_t *inext,*jnext;
	void *temp = NULL;
	int flag;

	for(inext = head->next; inext != head; inext = inext->next)
	{
		flag = 0;
		for(jnext = head->next; jnext->next != head; jnext = jnext->next)
		{
			if(cmpfun(jnext->data,jnext->next->data) > 0)
			{
				temp = jnext->data;
				jnext->data = jnext->next->data;
				jnext->next->data = temp;
				flag = 1;		
			}
		}
		if(!flag)
			break;
	}
	return 0;
}
