#include "all_include.h"
char service_buf[1000];
char service_ret_buf[1000];

void plane_search(struct plane_list *plane_head)
{
    char info[10];
	int info_money;
	int choice;
	struct plane_list *p=NULL;
	int x=0;
	while(1)
	{
		
		printf("请选择要查询的条件目的地、出发日期、机型、价格\n");
		show_ui_pick_plane();
		//scanf("%d",&choice);
		choice=ret_choice(service_buf);	
		switch (choice)
		{
			case 1://目的地
				{
					int x=0;
					printf("请输入您要去往的目的地\n");
					//scanf("%s",info);
					ret_buf(info,sizeof(info));
					for(p=plane_head->next;p!=plane_head;p=p->next)
					{
						if(strcmp(info,p->end)==0)
						{
							printf("航班号:%s	始发地:%s	目的地:%s	日期:%s	   机型:%s		出发时间:%s		票价:%d		余票:%d\n",p->name_plane,p->start
							,p->end,p->time_date,p->plane_type,p->time_hour,p->money,p->ticket_num);
							x++;
							break;
						}
					}
					if(x==0)
					printf("暂无改航班\n");

				}
				break;

			case 2://出发日期
				{
					int x=0;
					printf("请输入您的出发日期\n");
					//scanf("%s",info);
					ret_buf(info,sizeof(info));
					for(p=plane_head->next;p!=plane_head;p=p->next)
					{
						if(strcmp(info,p->time_date)==0)
						{
							printf("航班号:%s	始发地:%s	目的地:%s	日期:%s	   机型:%s		出发时间:%s		票价:%d		余票:%d\n",p->name_plane,p->start
							,p->end,p->time_date,p->plane_type,p->time_hour,p->money,p->ticket_num);
							x++;
							break;
						}
					}
					if(x==0)
					printf("暂无改航班\n");

				}
				break;

			case 3://机型
				{
					int x=0;
					printf("请输入您想要的机型\n");
					//scanf("%s",info);
					ret_buf(info,sizeof(info));
					for(p=plane_head->next;p!=plane_head;p=p->next)
					{
						if(strcmp(info,p->plane_type)==0)
						{
							printf("航班号:%s	始发地:%s	目的地:%s	日期:%s	   机型:%s		出发时间:%s		票价:%d		余票:%d\n",p->name_plane,p->start
							,p->end,p->time_date,p->plane_type,p->time_hour,p->money,p->ticket_num);
							x++;
							break;
						}
						
					}
					if(x==0)
					printf("暂无改航班\n");

				}
				break;

			case 4://价格
				{
					int x=0;
					printf("请输入您要的价格\n");
					//scanf("%d",&info_money);
					info_money=ret_choice(service_buf);	
					for(p=plane_head->next;p!=plane_head;p=p->next)
					{
						if(info_money==p->money)
						{
							printf("航班号:%s	始发地:%s	目的地:%s	日期:%s	   机型:%s		出发时间:%s		票价:%d		余票:%d\n",p->name_plane,p->start
							,p->end,p->time_date,p->plane_type,p->time_hour,p->money,p->ticket_num);
							x++;
							break;
						}
					}
					if(x==0)
						printf("暂无改航班\n");

				}
				break;


			 case 5://放回上一级
			 	x++;
				break; 

			default:
				printf("请输出正确指令\n");	
				getchar();	
				break;
		}
    
		if(x!=0)
			break;
		break;
			
	}
}
						
					
					
				