#include "all_include.h"

int main(int argc,char *argv[])
{

	//printf("****\n");
    //1. 申请注册链表头节点。
	struct person_list *person_head = NULL;
	person_head = init_person_list_head();

	//1. 登录节点
	struct person_list *person_head_log = NULL;
	person_head_log = init_person_list_log();

    //1. 申请公安链表头节点。
	struct real_info *real_head = NULL;
	real_head = init_real_list_head();

    //1. 申请飞机链表头节点。
	struct plane_list *plane_head = NULL;
	plane_head = init_plane_list_head();

	//1. 申请飞机删除链
	struct plane_list *plane_delete_head = NULL;
	plane_delete_head = init_plane_list_delete_head();

    //1. 申请成交链表头节点。
	struct deal_list *deal_head = NULL;
	deal_head = init_deal_list_head();

	//printf("**++**\n");
    //3. 将目录下的老用户初始化到链表中。
	init_person_list(person_head);

	//printf("**--**\n");
    //3. 公安初始化到链表中。
	init_real_list(real_head);

	//printf("****----**\n");
    //3. 飞机初始化到链表中。
	init_plane_list(plane_head);
	//printf("***++++++++*\n");
	//飞机删除连
	init_plane_delete_list(plane_delete_head);
	//printf("**------------**\n");
    //3. 成交初始化到链表中。
	init_deal_list(deal_head);

	


	//printf("%s\n",person_head->next->name);
	//printf("%s\n",person_head->next->passwd);
	void show_open_ui();
	while(1)
	{
		show_open_user_ui();
		int choice;
		printf("请输入指令\n");
	    scanf("%d",&choice);
		switch(choice)
		{
			case 1:
			
			user_fun(person_head,person_head_log,real_head,plane_head,deal_head);
			
			break;
		
			case 2:
				{
						
						char ID[10];
						int pass;
						printf("请输入你的ID\n");
						scanf("%s",ID);
						if(strcmp(ID,"a")==0)
							{
								printf("输入密码\n");
								scanf("%d",&pass);
								if(pass==1)
									{
										root_fun(person_head,person_head_log,real_head,plane_head,deal_head,plane_delete_head);
										//continue;
									}
								else
									printf("密码错误\n");
							}
						else
							printf("用户名错误\n");
					
					
				}
				break;
			default:
				printf("输入有误\n");
		}

	}
}