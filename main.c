#include "all_include.h"
//extern int service_choice=0;
//extern char service_choice[1000];
extern char service_buf[1000];
extern char service_ret_buf[1000];
//extern char send_to_client[1000];

int ret_choice(char *service_buf)
{
			int choice=0;
			while((atoi)(service_buf)==0);
			choice=(atoi)(service_buf);
			bzero(service_buf,1000);
			return choice;
}

char *ret_buf(char *buf,int buf_len)
{
	//send_bufto_client("%s**ret_11111\n",service_buf);
	bzero(buf,strlen(buf));
	while(strlen(service_buf)==0);
	/* send_bufto_client("%s*sfvdfv*\n",service_buf);
	send_bufto_client("%s**\n",service_buf);
	send_bufto_client("%s**\n",service_buf); */
	/* if(buf_len==1)
	return (char *)0; */
	for(int i=0;i<strlen(service_buf)-1;i++)
	{
		buf[i]=service_buf[i];
	}
	//send_bufto_client("**%s**\n",buf);
	//send_bufto_client("service_buf**%s**\n",service_buf);
	bzero(service_buf,1000);
}


int main(int argc,char *argv[])
{

	//send_bufto_client("****\n");
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

	//send_bufto_client("**++**\n");
    //3. 将目录下的老用户初始化到链表中。
	init_person_list(person_head);

	//send_bufto_client("**--**\n");
    //3. 公安初始化到链表中。
	init_real_list(real_head);

	//send_bufto_client("****----**\n");
    //3. 飞机初始化到链表中。
	init_plane_list(plane_head);
	//send_bufto_client("***++++++++*\n");
	//飞机删除连
	init_plane_delete_list(plane_delete_head);
	//send_bufto_client("**------------**\n");
    //3. 成交初始化到链表中。
	init_deal_list(deal_head);

	pthread_t tid;
	pthread_create(&tid,NULL,service_fun,(void *)argv[1]);
	//bzero(service_buf,1000);
	void show_open_ui();
	while(1)
	{
		sleep(1);
		show_open_user_ui();
		int choice;
		bzero(service_buf,1000);
		//send_bufto_client("请输入指令\n");
		send_bufto_client("请输入指令\n");
	    //scanf("%d",&choice);
		choice=ret_choice(service_buf);	
		switch(choice)
		{
			case 1:
			
			user_fun(person_head,person_head_log,real_head,plane_head,deal_head);
			
			break;
		
			case 2:
				{
						
						char ID[10];
						bzero(ID,10);
						int pass;
						send_bufto_client("请输入你的ID\n");
						//send_bufto_client("请输入你的ID\n");
						//scanf("%s",ID);
						/* while((atoi)(service_buf)==0);
						strncpy(ID,service_buf,10);
						bzero(service_buf,1000); */

						ret_buf(ID,sizeof(ID));
						//send_bufto_client("**cs**%s\n",ID);
						if(strcmp(ID,"a")==0)
							{
								send_bufto_client("输入密码\n");
								//scanf("%d",&pass);
								pass=ret_choice(service_buf);	
								if(pass==1)
									{
										root_fun(person_head,person_head_log,real_head,plane_head,deal_head,plane_delete_head);
										//continue;
									}
								else
									send_bufto_client("密码错误\n");
							}
						else
							send_bufto_client("用户名错误\n");
					
					
				}
				break;
			default:
				send_bufto_client("输入有误\n");
		}

	}
}



