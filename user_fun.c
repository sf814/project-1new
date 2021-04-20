#include "all_include.h"

void user_fun(struct person_list *person_head,struct person_list *person_head_log,struct real_info *real_head,struct plane_list *plane_head,struct deal_list * deal_head)
{		
    while(1)
    {
        int choice;
	    shou_ui_menu();
	    printf("请输入指令\n");
	    scanf("%d",&choice);
		while(getchar()!='\n');
      /*   if(choice<1 &&choice >18)
        {
            printf("输入有误\n");
            //while(getchar()!='\n');
        }
        else */
	    
            switch (choice)
	    {
	    case 1://查看航班信息
	    	{

						struct plane_list *p=NULL;
						//show_plane_info_list(plane_head);
						for(p=plane_head->next;p!=plane_head;p=p->next)
						{
							printf("航班号:%s	始发地:%s	目的地:%s	日期:%s	   机型:%s		出发时间:%s		票价:%d		余票:%d\n",p->name_plane,p->start
							,p->end,p->time_date,p->plane_type,p->time_hour,p->money,p->ticket_num);

						}
						//printf("按任意建返回上一菜单");


	    	}
	    		break;
	    case 2://2.查询航班 
					{
						plane_search(plane_head);
					}
					break;					

		case 3://3.快速查询 
		    {
		    	struct plane_list *p=NULL;
		    	char plane_info[10];
		    	int x=0;
		    	printf("请输入要查询的航班\n");
		    	scanf("%s",plane_info);
		    	for(p=plane_head->next;p!=plane_head;p=p->next)
		    	{
		    		if(strcmp(p->name_plane,plane_info)==0)
		    		{
		    			printf("航班号:%s	始发地:%s	目的地:%s	日期:%s	   机型:%s		出发时间:%s		票价:%d		余票:%d\n",p->name_plane,p->start
		    			,p->end,p->time_date,p->plane_type,p->time_hour,p->money,p->ticket_num);
		    			x++;
    
		    		}
		    	}
		    		if(x==0)
		    		printf("暂无改航班\n" );
		    }
		    break;

	    case 4://4.实名认证 
					{
						int x=0;
						struct person_list *p=NULL;
						if(person_head_log->next==person_head_log)
							{						
								printf("尚未登录，请先登录\n");
								x=person_head_login(person_head,person_head_log);
								if(x==1)
								{

									if(person_head_log->next->verify==0)//实名认证
										{
											id_verify(person_head,real_head,person_head_log);
										}
									else
										{
											printf("已认证，不需要重复操作\n");
											break;
										}
								}
								else if(x==2)
								printf("登录失败\n");
							}
						else
							{
								if(person_head_log->next->verify==0)//实名认证
									{
										id_verify(person_head,real_head,person_head_log);
									}
								else
									{
										printf("已认证，不需要重复操作\n");
										break;
									}					
							}

					}
					break;

	    case 5:// 5.购买机票 
	        {
					int x=0;
					struct person_list *p=NULL;
					if(person_head_log->next==person_head_log)
					{						
						printf("尚未登录，请先登录\n");
						x=person_head_login(person_head,person_head_log);
						if(x==1)
						{
							
								if(person_head_log->next->verify==1)//实名认证
								{
									if(person_head_log->next->ticket==0)
									buy_ticket(person_head,plane_head,person_head_log,deal_head);
									else
									printf("已购票，不可重复购买\n");
								}
								else
								{
									printf("未实名认证\n");
									break;
								}
						}
						else if(x==2)
						printf("登录失败\n");
					}
					else
					{
						if(person_head_log->next->verify==1)//实名认证
							{
								if(person_head_log->next->ticket==0)
								buy_ticket(person_head,plane_head,person_head_log,deal_head);
								else
								printf("已购票，不可重复购买\n");
							}
						else
							{
								printf("未实名认证\n");
								break;
							}
					}
	        }
	        break;
    
	    case 6://6.帮人购买机票
					{
						int x=0;
						struct person_list *p=NULL;
						if(person_head_log->next==person_head_log)
							{						
								printf("尚未登录，请先登录\n");
								x=person_head_login(person_head,person_head_log);
								if(x==1)
								{

										if(person_head_log->next->verify==1)//实名认证
										{
											buy_others_ticket_verify(person_head,plane_head,person_head_log,deal_head);

										}
										else
										{
											printf("未实名认证\n");
											break;
										}
								}
								else if(x==2)
								printf("登录失败\n");
							}
						else
							{
								if(person_head_log->next->verify==1)//实名认证
								{
									buy_others_ticket_verify(person_head,plane_head,person_head_log,deal_head);	
								}
								else
								{
									printf("未实名认证\n");
									break;
								}
							}

					}
					break;

	    case 7://7.查看自己的票 
	        {
					printf("%d\n",person_head_log->next->ticket);
					int x=0;
					struct person_list *p=NULL;
					if(person_head_log->next==person_head_log)
					{						
						printf("尚未登录，请先登录\n");
						x=person_head_login(person_head,person_head_log);
						if(x==1)
							{						
								show_ticket_pay(person_head,person_head_log,plane_head);								
							}
						else if(x==2)
						printf("登录失败\n");
					}
					else
					{
						show_ticket_pay(person_head,person_head_log,plane_head);

					}

	        }			
	        break;
    
	    case 8://8.改签   
	        {
									
					int x=0;
					struct person_list *p=NULL;
					if(person_head_log->next==person_head_log)
					{						
						printf("尚未登录，请先登录\n");
						x=person_head_login(person_head,person_head_log);
						if(x==1)
						{
							
								if(person_head_log->next->ticket==1)//有票								
									{
										int xx;
										xx=return_ticket(person_head,person_head_log,plane_head,deal_head);
										if(xx==2)
										{
											buy_ticket(person_head,plane_head,person_head_log,deal_head);
										}
									
									}
								else//没票
									printf("尚未购票\n");
								
						}
						else if(x==2)
						printf("登录失败\n");
					}

	        }
	        break;
    
	    case 9://9.退票  
					{
						int x=0;
						struct person_list *p=NULL;
						if(person_head_log->next==person_head_log)
						{						
							printf("尚未登录，请先登录\n");
							x=person_head_login(person_head,person_head_log);
							if(x==1)
							{
								
									if(person_head_log->next->ticket==1)//有票								
										return_ticket(person_head,person_head_log,plane_head,deal_head);
									else//没票
										printf("尚未购票\n");
									
							}
							else if(x==2)
							printf("登录失败\n");
						}
						else
						{
							if(person_head_log->next->ticket==1)
								return_ticket(person_head,person_head_log,plane_head,deal_head);
							else//没票
									printf("尚未购票\n");
							
						}
						
						
					}
					break;

	    case 10://10.查询自己的信息
	    	{
					
						int x=0;
						struct person_list *p=NULL;
						if(person_head_log->next==person_head_log)
						{						
							printf("尚未登录，请先登录\n");
							x=person_head_login(person_head,person_head_log);
							if(x==1)
							{

									
										printf("您的vip等级：%s\n",person_head_log->next->id);
										printf("你的姓名：%s\n",person_head_log->next->name);
                                        printf("你的职业：%s\n",person_head_log->next->status);
                                        printf("你的职业折扣：%f\n",person_head_log->next->status_off);
                                        printf("你的VIP等级：%s\n",person_head_log->next->vip_level);
                                        printf("你的vip折扣：%f\n",person_head_log->next->vip_off);
                                        printf("你的使命认证：%d\n",person_head_log->next->verify);
                                        printf("你的是否买票：%d\n",person_head_log->next->ticket);
                                        printf("你的航班号：%s\n",person_head_log->next->ticket_name);
                                        printf("你的出发日期：%s\n",person_head_log->next->ticket_date);
                                        printf("你的余额：%d\n",person_head_log->next->money);
                                        printf("你的积分：%d\n",person_head_log->next->money_num);
                                        printf("你的vip余额：%d\n",person_head_log->next->vip_money);
                                        printf("你的密码：%s\n",person_head_log->next->passwd);
                                        printf("你的是否取票：%d\n",person_head_log->next->ticket_take);
                                        printf("你的是否开发票：%d\n",person_head_log->next->ticket_bill);
									
									
							}
							else if(x==2)
							printf("登录失败\n");
						}
						else
						{
				
							
										printf("您的ID：%s\n",person_head_log->next->id);
										printf("你的姓名：%s\n",person_head_log->next->name);
                                        printf("你的职业：%s\n",person_head_log->next->status);
                                        printf("你的职业折扣：%f\n",person_head_log->next->status_off);
                                        printf("你的VIP等级：%s\n",person_head_log->next->vip_level);
                                        printf("你的vip折扣：%f\n",person_head_log->next->vip_off);
                                        printf("你的使命认证：%d\n",person_head_log->next->verify);
                                        printf("你的是否买票：%d\n",person_head_log->next->ticket);
                                        printf("你的航班号：%s\n",person_head_log->next->ticket_name);
                                        printf("你的出发日期：%s\n",person_head_log->next->ticket_date);
                                        printf("你的余额：%d\n",person_head_log->next->money);
                                        printf("你的积分：%d\n",person_head_log->next->money_num);
                                        printf("你的vip余额：%d\n",person_head_log->next->vip_money);
                                        printf("你的密码：%s\n",person_head_log->next->passwd);
                                        printf("你的是否取票：%d\n",person_head_log->next->ticket_take);
                                        printf("你的是否开发票：%d\n",person_head_log->next->ticket_bill);
							
							
						}
					
	    	}
	    	break;
	    case 11://11.充值 
					{
					
						int x=0;
						struct person_list *p=NULL;
						if(person_head_log->next==person_head_log)
							{						
								printf("尚未登录，请先登录\n");
								x=person_head_login(person_head,person_head_log);
								if(x==1)
								{

										if(person_head_log->next->verify==1)//实名认证
										{
											invest_money(person_head,person_head_log);
										}
										else
										{
											printf("未实名认证\n");
											break;
										}
								}
								else if(x==2)
								printf("登录失败\n");
							}
						else
							{
								if(person_head_log->next->verify==1)//实名认证
								{
									invest_money(person_head,person_head_log);
								}
								else
								{
									printf("未实名认证\n");
									break;
								}
							}
					}
					break;

	    case 12://12.修改信息 
	        {
					int x=0;
					struct person_list *p=NULL;
					if(person_head_log->next==person_head_log)
					{						
						printf("尚未登录，请先登录\n");
						x=person_head_login(person_head,person_head_log);
						if(x==1)
						{
							
								if(person_head_log->next->verify==1)//实名认证
								{
									//实名制，公安，机场手动修改，用户不可任意修改,只可修改密码
									change_message(person_head,person_head_log,deal_head);
								}
								else
								{
									//未实名，仅注册，可随意修改
									change_message_normal(person_head,person_head_log,deal_head);
									break;
								}
						}
						else if(x==2)
						printf("登录失败\n");
					}
					else
					{
						if(person_head_log->next->verify==1)//实名认证
						{
							change_message(person_head,person_head_log,deal_head);
						}
						else
						{
							change_message_normal(person_head,person_head_log,deal_head);
							break;
						}
					}

	        }
	        break;
    
	    case 13://13.取票 
					{
						int x=0;
						struct person_list *p=NULL;
						if(person_head_log->next==person_head_log)
							{						
								printf("尚未登录，请先登录\n");
								x=person_head_login(person_head,person_head_log);
								if(x==1)
									{

									if(person_head_log->next->ticket==1)//有票								
										show_ticket_ui(person_head,person_head_log,plane_head);
									else//没票
										printf("尚未购票\n");

									}
								else if(x==2)
								printf("登录失败\n");
							}
						else
							{
								if(person_head_log->next->ticket==1)
									show_ticket_ui(person_head,person_head_log,plane_head);
								else//没票
									printf("尚未购票\n");
						
							}

					}
					break;

	    case 14://14.开发票  			
	    	{
						int x=0;
						struct person_list *p=NULL;
						if(person_head_log->next==person_head_log)
						{						
							printf("尚未登录，请先登录\n");
							x=person_head_login(person_head,person_head_log);
							if(x==1)
							{

									if(person_head_log->next->ticket==1)//有票								
										show_bill(person_head,person_head_log,plane_head);
									else//没票
										printf("尚未购票\n");

							}
							else if(x==2)
							printf("登录失败\n");
						}
						else
						{
							if(person_head_log->next->ticket==1)
								show_bill(person_head,person_head_log,plane_head);
							else//没票
									printf("尚未购票\n");

						}

	    	}
	    	break;
	    case 15://注册
	        {
				if(person_head_log->next!=person_head_log)
					printf("有用户登陆中，请先退出\n");
				else							
					person_head_logup(person_head);
	        }
	    	break;
	    case 16://登录
	        {
			    if(person_head_log->next==person_head_log)
					person_head_login(person_head,person_head_log);
				else
					printf("已有账户登录，请退出后重新操作\n");
	        }
	    	break;
        case 17://展示风景
            {
                show_world();

            }
			break;
	    case 18://17.退出登录  
					{
						if(person_head_log->next!=person_head_log)
							{
								free(person_head_log->next);
								person_head_log->next=person_head_log;
								person_head_log->prev=person_head_log;							
								printf("退出成功\n");	
							}
						else
							printf("无登录用户\n");	
						show_black();	
					}
					break;

	    case 19://返回初始界面
	    	{
                if(person_head_log->next!=person_head_log)
					{
						free(person_head_log->next);
						person_head_log->next=person_head_log;
						person_head_log->prev=person_head_log;							
						printf("退出成功\n");	
					}
				else
							printf("无登录用户\n");
				
                return;
	        }
        default :
	       printf("输入有误\n");
	    }
        		
    }
		
}