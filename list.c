#include "all_include.h"

//注册
struct person_list *init_person_list_head()
{
	//1. 为头节点申请空间
	struct person_list *head = malloc(sizeof(struct person_list));

	//2. 为头节点赋值。
	head->next = head;
	head->prev = head;

	return head;
}


struct person_list *init_person_list_log()
{
	//1. 为头节点申请空间
	struct person_list *log = malloc(sizeof(struct person_list));

	//2. 为头节点赋值。
	log->next = log;
	log->prev = log;

	return log;
}

//公安
struct real_info *init_real_list_head()
{
	//1. 为头节点申请空间
	struct real_info *head = malloc(sizeof(struct real_info));

	//2. 为头节点赋值。
	head->next = head;
	head->prev = head;

	return head;
}


//飞机
struct plane_list *init_plane_list_head()
{
	//1. 为头节点申请空间
	struct plane_list *head = malloc(sizeof(struct plane_list));

	//2. 为头节点赋值。
	head->next = head;
	head->prev = head;

	return head;
}

//删除连
struct plane_list *init_plane_list_delete_head()
{
	//1. 为头节点申请空间
	struct plane_list *head = malloc(sizeof(struct plane_list));

	//2. 为头节点赋值。
	head->next = head;
	head->prev = head;

	return head;
}


//成交
struct deal_list *init_deal_list_head()
{
	//1. 为头节点申请空间
	struct deal_list *head = malloc(sizeof(struct deal_list));

	//2. 为头节点赋值。
	head->next = head;
	head->prev = head;

	return head;
}

struct list_node *init_list_pic_head()
{
	//1. 为头节点申请空间。
	struct list_node *head = malloc(sizeof(struct list_node));

	//2. 为头节点赋值。
	head->next = head;
	head->prev = head;

	return head;
}





