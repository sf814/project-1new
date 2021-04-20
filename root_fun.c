#include "all_include.h"

void root_fun(struct person_list *person_head,struct person_list *person_head_log,struct real_info *real_head,
struct plane_list *plane_head,struct deal_list * deal_head,struct plane_list *plane_delete_head)
{
while(1)
	{
		int choice;
		show_root_ui();
		printf("请选择功能\n");
		scanf("%d",&choice);
        switch(choice)
        {
            case 1://1.查看所有航班信息 
            {
                struct plane_list *p=NULL;
				//show_plane_info_list(plane_head);
				for(p=plane_head->next;p!=plane_head;p=p->next)
				{
					printf("航班号:%s	始发地:%s	目的地:%s	日期:%s	   机型:%s		出发时间:%s		票价:%d		余票:%d\n",p->name_plane,p->start
					,p->end,p->time_date,p->plane_type,p->time_hour,p->money,p->ticket_num);
				}

            }
            break;


            case 2://1.人员信息
            {
                struct person_list *p=NULL;
				//show_plane_info_list(plane_head);
				for(p=person_head->next;p!=person_head;p=p->next)
				{
					printf("ID:%s	姓名:%s	    职业:%s	    职业折扣:%f	   VIP登记:%s		VIP折扣:%f		是否认证:%d\n",p->id,p->name
                    ,p->status,p->status_off,p->vip_level,p->vip_off,p->verify);
                    printf("是否购票:%d 购买机型：%s      出发时间:%s      积分:%d    充值余额:%d    密码:%s    是否取发票:%d    是否取票:%d\n",p->ticket,p->ticket_name,p->ticket_date,p->money_num
                    ,p->vip_money,p->passwd,p->ticket_take,p->ticket_bill);
                    printf("========================================================================\n");
				}

            }
            break;

            case 3://2.录入航班 
            {
                struct plane_list *p=malloc(sizeof(struct plane_list));
                printf("请依次输入航班信息：\n");
                printf("航班号，始发地，目的地，日期，机型，时间，价格，数量\n");
                scanf("%s%s%s%s%s%s%d%d",p->name_plane,p->start,p->end,p->time_date,p->plane_type,p->time_hour,
                &p->money,&p->ticket_num);
                p->ticket=1;
                p->next=plane_head;

                //struct plane_list * new=NULL;
                //更新飞机连
                p->prev=plane_head->prev;
                
                
                plane_head->prev->next=p;
                plane_head->prev=p;
                //保存到plane_data中
                
                save_plane_file(p);
                printf("录入成功\n");

            }
            break;

            case 4://3. 删除航班 
            {
                printf("****%s****\n",plane_head->prev->name_plane);
                char delete_name[10];
                char delete_date[20];
                printf("请输入要删除的航班号，日期\n");
                scanf("%s%s",delete_name,delete_date);
              
                struct plane_list *q=NULL;
                for(q=plane_head->next;q!=plane_head;q=q->next)
                {
                    
                    if(strcmp(q->name_plane,delete_name)==0 && strcmp(q->time_date,delete_date)==0)
                    {
                     
                        char filename[100] = {0};
                      
	                    sprintf(filename,"cp ./plane_data/%s.txt ./plane_delete",q->name_plane);
                        system(filename);	
                        printf("%s\n",q->name_plane);
                        printf("%s\n",delete_name);
                        sprintf(filename,"rm ./plane_data/%s.txt",q->name_plane);	
                        
	                    system(filename);
                        //将删除航班从飞机连中删除
                        q->prev->next=q->next;
                        q->next->prev=q->prev;
                        

                        //添加到飞机删除连
                        plane_delete_head->prev->next=q;
                        q->prev=plane_delete_head->prev;
                        q->next=plane_delete_head;
                        plane_delete_head->prev=q;
                        
                       
                        printf("移除成功\n");
                        break;
                    }
                    
                }
                
	            //return;

            }
            break;

             case 5://4.生效保险 
            {
                int choice;
                printf("请选择退票航班号或者人员\n");
                
                printf("================================\n");
                printf("            1.航班              \n");
                printf("            2.人员              \n");
                printf("================================\n");
                scanf("%d",&choice);
                switch(choice)
                {
                    case 1:
                    {
                        int x=0;
                        char delete_name[10];
                        char delete_date[20];
                        printf("请输入要退票的航班号，日期\n");
                        scanf("%s%s",delete_name,delete_date);

                        struct plane_list *q=NULL;
                        for(q=plane_head->next;q!=plane_head;q=q->next)
                        {
                            if(strcmp(q->name_plane,delete_name)==0 && strcmp(q->time_date,delete_date)==0)
                            {    
                                x=1;                    
                                char filename[100] = {0};

	                            sprintf(filename,"cp ./plane_data/%s.txt ./plane_delete",q->name_plane);
                                system(filename);	
                                printf("%s\n",q->name_plane);
                                printf("%s\n",delete_name);
                                sprintf(filename,"rm ./plane_data/%s.txt",q->name_plane);	

	                            system(filename);
                                //将删除航班从飞机连中删除
                                q->prev->next=q->next;
                                q->next->prev=q->prev;


                                //添加到飞机删除连
                                plane_delete_head->prev->next=q;
                                q->prev=plane_delete_head->prev;
                                q->next=plane_delete_head;
                                plane_delete_head->prev=q;
                                struct person_list *old_buy=NULL;
                                for(old_buy=person_head->next;old_buy!=person_head;old_buy=old_buy->next)
                                    {
                                        if(strcmp(old_buy->ticket_name,q->name_plane)==0 && strcmp(old_buy->ticket_date,q->time_date)==0)
                                        {
                                            
                                            old_buy->ticket=0;
                                            strcpy(old_buy->ticket_name,"0");
                                            strcpy(old_buy->ticket_date,"0");
                                            old_buy->ticket_take=0;
                                            old_buy->ticket_bill=0;
                                            old_buy->money=old_buy->money+10000;
                                            save_person_file(old_buy);
                                            
                                        }
                                    }


                                printf("移除成功\n");
                                break;
                            }
                        }
                        if(x==0)
                        {
                            printf("输入有误，请确认信息正确\n");
                        } 
                    }
                    break;
                    case 2:
                    {
                        int x=0;
                        char delete_name[10];
                        char delete_id[10];
                        struct person_list *old_buy=NULL;
                        printf("请输入要剔除的人的姓名以及ID\n");
                        scanf("%s%s",delete_name,delete_id);
                        for(old_buy=person_head->next;old_buy!=person_head;old_buy=old_buy->next)
                        {
                            if(strcmp(old_buy->name,delete_name)==0 && strcmp(old_buy->id,delete_id)==0)
                            {
                                x=1;
                                //更新数据包
                                old_buy->ticket=0;
                                strcpy(old_buy->ticket_name,"0");
                                strcpy(old_buy->ticket_date,"0");
                                old_buy->ticket_take=0;
                                old_buy->ticket_bill=0;
                                old_buy->money=old_buy->money+10000;
                                save_person_file(old_buy);
                                break;

                            }
                            
                        }
                        if(x==0)
                        {
                            printf("输入有误，请确认人员信息正确\n");
                        }


                    }
                }

            }
            break; 

            case 6://5.查看删除的航班  
            {
                struct plane_list *p=NULL;
				//show_plane_info_list(plane_head);
				for(p=plane_delete_head->next;p!=plane_delete_head;p=p->next)
				{
					printf("航班号:%s	始发地:%s	目的地:%s	日期:%s	   机型:%s		出发时间:%s		票价:%d		余票:%d\n",p->name_plane,p->start
					,p->end,p->time_date,p->plane_type,p->time_hour,p->money,p->ticket_num);
				}

            }
            break;

            
            case 7://修改人员信息
            {
                change_message_root(person_head,person_head_log,deal_head);

            }
            break;
            

             case 8://6.退出登陆，返回上一级 
            {
                return;
            }
            
        }
	}
}


