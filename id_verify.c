

#include "all_include.h"

char service_buf[1000];
char service_ret_buf[1000];
//实名认证
void id_verify(struct person_list *person_head,struct real_info *real_head,struct person_list *person_head_log)
{
    int x=0;
	char verify_name[10];
	char verify_name_id[10];
	send_bufto_client("请输入你的姓名\n");
	//scanf("%s",verify_name);
	ret_buf(verify_name,sizeof(verify_name));	
	struct real_info *p=NULL;
	for(p=real_head->next;p!=real_head;p=p->next)
	{
		if(strcmp(p->name,verify_name)==0)
		{
			x=1;
			
			send_bufto_client("请输入你的id\n");
			//scanf("%s",verify_name_id);
			ret_buf(verify_name_id,sizeof(verify_name_id));
			/* send_bufto_client("%s\n",verify_name_id);
			send_bufto_client("%s\n",p->id);
			send_bufto_client("%s\n",p->status); */
			if(strcmp(p->id,verify_name_id)==0)
			{
				send_bufto_client("认证成功！\n");
				//改变用户状态
				struct person_list *q=NULL;
				for(q=person_head->next;q!=person_head;q=q->next)
					if(strcmp(q->name,p->name)==0)
						{
							q->verify=1;
							person_head_log->next->verify=1;
							//修正身份
							delete_old_person_list(q);
							strcpy(person_head_log->next->id,p->id);
							strcpy(person_head_log->next->status,p->status);

							strcpy(q->status,p->status);
							strcpy(q->id,p->id);
							//修正身份折扣
							if(strcmp(p->status,"soldier")==0 || strcmp(p->status,"doctor")==0)
							{
								person_head_log->next->status_off=0.5;
								q->status_off=0.5;
							}
							//保存新信息到注册链
							save_person_file(q);
							break;
						}
				break;								
			}
			else 
			{
				
				send_bufto_client("认证失败,id错误\n");
				break;
			}
		}
								
		
	}
	if(x==0)
	send_bufto_client("认证失败,姓名有误\n");
	
}

//12.修改信息
void change_message(struct person_list * person_head,struct person_list *person_head_log,struct deal_list * deal_head)
{
	int choice;
	struct person_list * p=NULL;
	struct deal_list *q=NULL;	
		char new_passwd[10];
		send_bufto_client("请输入新的密码:\n");
		//scanf("%s",new_passwd);
		ret_buf(new_passwd,sizeof(new_passwd));
		//登录链
		delete_old_person_list(person_head_log->next);
		strcpy(person_head_log->next->passwd,new_passwd);
		//注册链
		for(p=person_head->next;p!=person_head;p=p->next)
			if(strcmp(person_head_log->next->passwd,p->passwd)==0)
				{strcpy(p->passwd,new_passwd);break;}

		
		save_person_file(p);
		
			
}
//修改未实名信息
void change_message_normal(struct person_list * person_head,struct person_list *person_head_log,struct deal_list * deal_head)
{
	int choice;
	struct person_list * p=NULL;
	struct deal_list *q=NULL;
	send_bufto_client("请输入要修改的信息\n");
	show_change_message_ui();
	//scanf("%d",&choice);
	choice=ret_choice(service_buf);
	switch (choice)
	{
	case 1://姓名
	{
		char new_name[10];
		send_bufto_client("请输入新的姓名:\n");
		//scanf("%s",new_name);
		ret_buf(new_name,sizeof(new_name));
		//登录链
		delete_old_person_list(person_head_log->next);
		strcpy(person_head_log->next->name,new_name);
		//注册链
		for(p=person_head->next;p!=person_head;p=p->next)
			if(strcmp(person_head_log->next->name,p->name)==0)
				{strcpy(p->name,new_name);break;}

		
		save_person_file(p);
		

	}
		
		break;
	case 2://职业
	{
		char new_status[10];
		send_bufto_client("请输入新的职业:\n");
		//scanf("%s",new_status);
		ret_buf(new_status,sizeof(new_status));
		//登录链
		delete_old_person_list(person_head_log->next);
		strcpy(person_head_log->next->status,new_status);
		//注册链
		for(p=person_head->next;p!=person_head;p=p->next)
			if(strcmp(person_head_log->next->status,p->status)==0)
				{strcpy(p->status,new_status);break;}

		
		save_person_file(p);
		

	}
		break;
	
	case 3://ID
	{
		char new_id[10];
		send_bufto_client("请输入新的ID:\n");
		//scanf("%s",new_id);
		ret_buf(new_id,sizeof(new_id));
		//登录链
		delete_old_person_list(person_head_log->next);
		strcpy(person_head_log->next->id,new_id);
		//注册链
		for(p=person_head->next;p!=person_head;p=p->next)
			if(strcmp(person_head_log->next->id,p->id)==0)
				{strcpy(p->id,new_id);break;}

		
		save_person_file(p);
		

	}
		break;

	case 4://密码
	{
		char new_passwd[10];
		send_bufto_client("请输入新的密码:\n");
		//scanf("%s",new_passwd);
		ret_buf(new_passwd,sizeof(new_passwd));
		//登录链
		delete_old_person_list(person_head_log->next);
		strcpy(person_head_log->next->passwd,new_passwd);
		//注册链
		for(p=person_head->next;p!=person_head;p=p->next)
			if(strcmp(person_head_log->next->passwd,p->passwd)==0)
				{strcpy(p->passwd,new_passwd);break;}

		
		save_person_file(p);
		

	}
		break;

	
	default:
		break;
	}

}


void change_message_root(struct person_list * person_head,struct person_list *person_head_log,struct deal_list * deal_head)
{
	int choice;
	char change_id[10];
	int y=0;
	struct person_list * p=NULL;
	struct person_list * x=NULL;
	struct deal_list *q=NULL;
	
	send_bufto_client("请输入要修改人员的ID\n");
	//scanf("%s",change_id);
	ret_buf(change_id,sizeof(change_id));
	for(x=person_head->next;x!=person_head;x=x->next)
	{
		if(strcmp(x->id,change_id)==0)
		{
			y=1;
			show_change_message_ui();
			//scanf("%d",&choice);
			choice=ret_choice(service_buf);	
			switch (choice)
			{
			case 1://姓名
			{
				char new_name[10];
				send_bufto_client("请输入新的姓名:\n");
				//scanf("%s",new_name);
				ret_buf(new_name,sizeof(new_name));
				//登录链
				if(person_head_log->next!=person_head_log)
				strcpy(person_head_log->next->name,new_name);
				//注册链
				
				delete_old_person_list(x);
				strcpy(x->name,new_name);

				save_person_file(x);
				

			}

				break;
			case 2://职业
			{
				char new_status[10];
				send_bufto_client("请输入新的职业:\n");
				//scanf("%s",new_status);
				ret_buf(new_status,sizeof(new_status));
				//登录链
				if(person_head_log->next!=person_head_log)
				strcpy(person_head_log->next->status,new_status);
				//注册链
				delete_old_person_list(x);
				strcpy(x->status,new_status);

				
				save_person_file(x);
				

			}
				break;

			case 3://ID15

			{
				char new_id[10];
				send_bufto_client("请输入新的ID:\n");
				//scanf("%s",new_id);
				ret_buf(new_id,sizeof(new_id));
				//登录链
				if(person_head_log->next!=person_head_log)
				strcpy(person_head_log->next->id,new_id);
				//注册链
				delete_old_person_list(x);
				strcpy(x->id,new_id);
				
				save_person_file(x);
				

			}
				break;

			case 4://密码
			{
				char new_passwd[10];
				send_bufto_client("请输入新的密码:\n");
				//scanf("%s",new_passwd);
				ret_buf(new_passwd,sizeof(new_passwd));
				//登录链
				if(person_head_log->next!=person_head_log)
				strcpy(person_head_log->next->passwd,new_passwd);
				//注册链
				delete_old_person_list(x);
				strcpy(x->passwd,new_passwd);
				
				save_person_file(x);
				

			}
				break;
			default:
				break;
			}
			break;
		}
		

	}
	if(y==0)
	{
		send_bufto_client("无法查找该人员\n");
	}
	

}

