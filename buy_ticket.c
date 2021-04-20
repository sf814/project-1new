#include "all_include.h"
//void buy_others_ticket(struct person_list *,struct plane_list *,struct person_list *);

void buy_ticket(struct person_list *person_head,struct plane_list *plane_head,struct person_list *person_head_log,struct deal_list *deal_head)
{
    char buy_name[10];
    int x=0;
    int ticket_cost;
    struct plane_list *p=NULL;
	//show_plane_info_list(plane_head);
	for(p=plane_head->next;p!=plane_head;p=p->next)
	{
		printf("航班号:%s	始发地:%s	目的地:%s	日期:%s	   机型:%s		出发时间:%s		票价:%d		余票:%d\n",p->name_plane,p->start
		,p->end,p->time_date,p->plane_type,p->time_hour,p->money,p->ticket_num);
	}
    printf("请选择要购买的航班号\n");
    scanf("%s",buy_name);
    for(p=plane_head->next;p!=plane_head;p=p->next)
    {
        if(strcmp(p->name_plane,buy_name)==0)//有航班
        {
            x=1;
            if(p->ticket_num>0)//有票
            {       
                //先检测所有的钱能不能买
                if(person_head_log->next->vip_money+person_head_log->next->money+person_head_log->next->money_num>plane_ticket_cost)
                {       
                        //积分购买
                    if(person_head_log->next->money_num>plane_ticket_cost)
                    {
                        
                        //飞机票数-1
                        p->ticket_num--;
                        //登录链数据更新    购票状态    购买机型    money   积分  vip_money  机票   发票 时间
                        person_head_log->next->ticket=1;
                        person_head_log->next->ticket_take=1;
                        person_head_log->next->ticket_bill=1;
                        strcpy(person_head_log->next->ticket_name , p->name_plane);
                        strcpy(person_head_log->next->ticket_date , p->time_date);
                        person_head_log->next->money_num=person_head_log->next->money_num-plane_ticket_cost;
                        ticket_cost=plane_ticket_cost;
                        //更新注册链
                        struct person_list *x=NULL;
                        for(x=person_head->next;x!=person_head;x=x->next)
                        {
                            if(strcmp(x->name,person_head_log->next->name)==0)
                            {
                                x->ticket=1;
                                x->ticket_take=1;
                                x->ticket_bill=1;
                                strcpy(x->ticket_name,p->name_plane);
                                strcpy(x->ticket_date,p->time_date);
                                x->money_num=x->money_num-plane_ticket_cost;
                                break;
                            }
                        }
                        //printf("******%s*****\n",x->name);
                        save_person_file(x);
                        save_plane_file(p);
                        //更新交易链     

                        new_deal_insert(deal_head,p,x,x,ticket_cost);
                        printf("购买成功\n");
                        printf("剩余积分：%d\n",person_head_log->next->money_num);
                        printf("剩余vip余额：%d\n",person_head_log->next->vip_money);
                        printf("我的钱包%d\n",person_head_log->next->money);


                        break;
                    }
                    else if(person_head_log->next->money_num + person_head_log->next->vip_money>plane_ticket_cost)
                    {
                        p->ticket_num--;

                        person_head_log->next->ticket=1;
                        person_head_log->next->ticket_take=1;
                        person_head_log->next->ticket_bill=1;
                        strcpy(person_head_log->next->ticket_name,p->name_plane);
                        strcpy(person_head_log->next->ticket_date , p->time_date);
                        
                        person_head_log->next->vip_money=person_head_log->next->vip_money-(plane_ticket_cost-person_head_log->next->money_num);
                        person_head_log->next->money_num=0;
                        ticket_cost=plane_ticket_cost;
                        //更新注册链
                        struct person_list *x=NULL;
                        for(x=person_head->next;x!=person_head;x=x->next)
                        {
                            if(strcmp(x->name,person_head_log->next->name)==0)
                            {
                                x->ticket=1;
                                x->ticket_take=1;
                                x->ticket_bill=1;
                                strcpy(x->ticket_name,p->name_plane);
                                strcpy(x->ticket_date,p->time_date);
                                x->money_num=0;
                                x->vip_money=x->vip_money-(plane_ticket_cost-x->money_num);
                                break;
                            }
                        }
                        //printf("*****%s********\n",x->name);
                        save_person_file(x);
                        save_plane_file(p);
                        //更新交易链                       
                        new_deal_insert(deal_head,p,x,x,ticket_cost);
                        
                        printf("购买成功\n");
                        printf("剩余积分：%d\n",person_head_log->next->money_num);
                        printf("剩余vip余额：%d\n",person_head_log->next->vip_money);
                        printf("我的钱包%d\n",person_head_log->next->money);
                        break;
                    }
                    else
                    {
                        p->ticket_num--;

                        person_head_log->next->ticket=1;
                        person_head_log->next->ticket_take=1;
                        person_head_log->next->ticket_bill=1;
                        strcpy(person_head_log->next->ticket_name,p->name_plane);
                        strcpy(person_head_log->next->ticket_date , p->time_date);
                        
                        person_head_log->next->money=person_head_log->next->money-(plane_ticket_cost-person_head_log->next->money_num-person_head_log->next->vip_money);
                        person_head_log->next->money_num=0;
                        person_head_log->next->vip_money=0;
                        ticket_cost=plane_ticket_cost;
                        //更新注册链
                        struct person_list *x=NULL;
                        for(x=person_head->next;x!=person_head;x=x->next)
                        {
                            if(strcmp(x->name,person_head_log->next->name)==0)
                            {
                                x->ticket=1;
                                x->ticket_take=1;
                                x->ticket_bill=1;
                                strcpy(x->ticket_name,p->name_plane);
                                strcpy(x->ticket_date,p->time_date);
                                x->money_num=0;
                                x->vip_money=0;
                                x->money=x->money-(plane_ticket_cost-x->money_num-x->vip_money);
                                break;
                            }
                        }
                        //printf("*****%s********\n",x->name);
                        save_person_file(x);
                        save_plane_file(p);
                        //更新交易链                       
                        new_deal_insert(deal_head,p,x,x,ticket_cost);
                        printf("购买成功\n");
                        printf("剩余积分：%d\n",person_head_log->next->money_num);
                        printf("剩余vip余额：%d\n",person_head_log->next->vip_money);
                        printf("钱包余额：%d\n",person_head_log->next->money);
                        break;
                    }
                }
                else
                {
                    printf("余额不足，请及时搬砖\n");
                    break;
                }





            }
            else
            printf("该航班已售罄\n");
            break;
            

        }
        

    }
    //while(getchar() != '\n');
    
    if(x==0)
    printf("无该航班\n");
}




void buy_others_ticket_verify(struct person_list *person_head,struct plane_list *plane_head,struct person_list *person_head_log,struct deal_list *deal_head)
{
    int y=0;
    int z=0;
    char others_id[10];
    struct person_list *q=NULL;
    printf("请输入要乘坐人员的ID\n");
    scanf("%s",others_id);
    for(q=person_head->next;q!=person_head;q=q->next)
    {
        //printf("**++++*\n");
        if(strcmp( q->id,others_id)==0)
        {
            z=1;
           /*  printf("%s\n",q->name);
            printf("%s\n",q->id);
            printf("%d\n",q->ticket);
            printf("%d\n",q->verify); */
            if(q->verify==0)
                {
                    printf("未实名认证\n");
                    break;
                }
            if(q->verify==1)
            {
                if(q->ticket==1)
                    {
                        printf("已经购买，不能重复购买\n");
                        break;
                    }
                else
                   {
                        buy_others_ticket(person_head,plane_head,person_head_log,q,deal_head);
                        break;
                   }
            }
                
        }      
    }
    if(z==0)
    printf("未注册\n");

}

void buy_others_ticket(struct person_list *person_head,struct plane_list *plane_head,struct person_list *person_head_log,struct person_list *q,struct deal_list *deal_head)
{
   
        char buy_name[10];
        int x=0;
        int ticket_cost;
        struct plane_list *p=NULL;
	    //show_plane_info_list(plane_head);
	    for(p=plane_head->next;p!=plane_head;p=p->next)
	    {
	    	printf("航班号:%s	始发地:%s	目的地:%s	日期:%s	   机型:%s		出发时间:%s		票价:%d		余票:%d\n",p->name_plane,p->start
	    	,p->end,p->time_date,p->plane_type,p->time_hour,p->money,p->ticket_num);
	    }
        printf("请选择要购买的航班号\n");
        scanf("%s",buy_name);
        for(p=plane_head->next;p!=plane_head;p=p->next)
        {
            if(strcmp(p->name_plane,buy_name)==0)//有航班
            {
                x=1;
                if(p->ticket_num>0)//有票
                {       
                    //先检测所有的钱能不能买
                    if(person_head_log->next->vip_money+person_head_log->next->money+person_head_log->next->money_num>plane_ticket_cost)
                    {       
                            //积分购买
                        if(person_head_log->next->money_num>plane_ticket_cost)
                        {
                            person_head_log->next->money_num=person_head_log->next->money_num-plane_ticket_cost;
                            ticket_cost=plane_ticket_cost;
                            p->ticket_num--;
                            //被赠与方
                            q->ticket=1;
                            q->ticket_take=1;
                            q->ticket_bill=1;
                            strcpy(q->ticket_date , p->time_date);
                            
                            //更新注册链
                            struct person_list *x=NULL;
                            for(x=person_head->next;x!=person_head;x=x->next)
                            {
                                if(strcmp(x->name,person_head_log->next->name)==0)
                                {                                   
                                    x->money_num=x->money_num-plane_ticket_cost;
                                    break;
                                }
                            }
                            save_person_file(q);
                            save_person_file(x);
                            save_plane_file(p);
                            //更新交易链                       
                            new_deal_insert(deal_head,p,x,q,ticket_cost);
                            //save_file();
                           printf("购买成功\n");
                            printf("剩余积分：%d\n",person_head_log->next->money_num);
                            printf("剩余vip余额：%d\n",person_head_log->next->vip_money);
                            break;
                        }
                        else if(person_head_log->next->money_num + person_head_log->next->vip_money>plane_ticket_cost)
                        {
                            p->ticket_num--;

                            q->ticket=1;
                            q->ticket_take=1;
                            q->ticket_bill=1;
                            strcpy(q->ticket_date , p->time_date);

                            
                            person_head_log->next->vip_money=person_head_log->next->vip_money-(plane_ticket_cost-person_head_log->next->money_num);
                            person_head_log->next->money_num=0;
                            ticket_cost=plane_ticket_cost;
                            //更新注册链
                            struct person_list *x=NULL;
                            for(x=person_head->next;x!=person_head;x=x->next)
                            {
                                if(strcmp(x->name,person_head_log->next->name)==0)
                                {                                   
                                    x->money_num=0;
                                    x->vip_money=x->vip_money-(plane_ticket_cost-x->money_num);
                                    break;
                                }
                            }
                            //save_file();
                            save_person_file(q);
                            save_person_file(x);
                            save_plane_file(p);
                            //更新交易链                       
                            new_deal_insert(deal_head,p,x,q,ticket_cost);
                            printf("购买成功\n");
                            printf("剩余积分：%d\n",person_head_log->next->money_num);
                            printf("剩余vip余额：%d\n",person_head_log->next->vip_money);
                            break;
                        }
                        else
                        {
                            p->ticket_num--;
                            
                            q->ticket=1;
                            q->ticket_take=1;
                            q->ticket_bill=1;
                            strcpy(q->ticket_date , p->time_date);

                            
                            person_head_log->next->money=person_head_log->next->money-(plane_ticket_cost-person_head_log->next->money_num-person_head_log->next->vip_money);
                            person_head_log->next->money_num=0;
                            person_head_log->next->vip_money=0;
                            ticket_cost=plane_ticket_cost;
                            //更新注册链
                            struct person_list *x=NULL;
                            for(x=person_head->next;x!=person_head;x=x->next)
                            {
                                if(strcmp(x->name,person_head_log->next->name)==0)
                                {                                   
                                    x->money_num=0;
                                    x->vip_money=0;
                                    x->money=x->money-(plane_ticket_cost-x->money_num-x->vip_money);
                                    break;
                                }
                            }
                            //save_file();
                            save_person_file(q);
                            save_person_file(x);
                            save_plane_file(p);
                            //更新交易链                       
                            new_deal_insert(deal_head,p,x,q,ticket_cost);
                            printf("购买成功\n");
                            printf("剩余积分：%d\n",person_head_log->next->money_num);
                            printf("剩余vip余额：%d\n",person_head_log->next->vip_money);
                            //printf("剩余vip余额：%d\n",person_head_log->next->money);
                            break;
                        }
                    }
                    else
                    {
                        printf("余额不足，请及时搬砖\n");
                        printf("余额不足，请及时搬砖\n");
                        printf("余额不足，请及时搬砖\n");
                        break;
                    }
                }
                else
                printf("该航班已售罄\n");
                break;

            }       

        }
        //while(getchar() != '\n');   
        if(x==0)
        printf("无该航班\n");
    
} 

void show_ticket_pay(struct person_list * person_head,struct person_list * person_head_log,struct plane_list *plane_head)
{
    
    struct plane_list *p=NULL;
    if(person_head_log->next->ticket==1)
    {  
        for(p=plane_head->next;p!=plane_head;p=p->next)
            {
                if(strcmp(person_head_log->next->ticket_name,p->name_plane)==0)
                {
                    
                    printf("航班号:%s	始发地:%s	目的地:%s	日期:%s	   机型:%s		出发时间:%s		票价:%d		余票:%d\n",p->name_plane,p->start
	    						,p->end,p->time_date,p->plane_type,p->time_hour,p->money,p->ticket_num);
                }
            }
   
    }
    else
    {
        printf("尚未买票\n");
    }
}

//充值
void invest_money(struct person_list *person_head,struct person_list *person_head_log)
{
    int p;
    struct person_list *x=NULL;
    printf("请输入充值额度\n");
    scanf("%d",&p);
    if(p<=person_head_log->next->money)
    {
        if(p<1000)
        {
            person_head_log->next->money = person_head_log->next->money - p;
            person_head_log->next->vip_money = person_head_log->next->vip_money + p;
            person_head_log->next->money_num=p/10;
            for(x=person_head->next;x!=person_head;x=x->next)
            {
                if(strcmp(x->name,person_head_log->next->name)==0)
                {                                   
                    x->money=person_head_log->next->money;
                    x->vip_money=person_head_log->next->vip_money;
                    x->money_num=person_head_log->next->money_num;
                    save_person_file(x);
                    printf("充值成功！\n");
                    printf("您的vip等级：%s\n",person_head_log->next->vip_level);
                    printf("你的余额：%d\n",x->money);
                    break;
                }
            }
            
        }
        if(p>=1000 && p<5000)
        {

            
            for(x=person_head->next;x!=person_head;x=x->next)
            {
                if(strcmp(x->name,person_head_log->next->name)==0)
                {               
                    if(person_head_log->next->vip_off>0.9)
                    {
                        person_head_log->next->money = person_head_log->next->money - p;
                        person_head_log->next->vip_money = person_head_log->next->vip_money + p;
                        person_head_log->next->money_num=p/10;
                        strcpy(person_head_log->next->vip_level,"silver") ; 
                        person_head_log->next->vip_off=0.9;

                        x->money=person_head_log->next->money;
                        x->vip_money=person_head_log->next->vip_money;
                        x->money_num=person_head_log->next->money_num;
                        x->vip_off=0.9;
                        strcpy(x->vip_level,"silver") ;

                        save_person_file(x);
                        printf("充值成功！\n");
                        printf("成为白金会员，购票获9折优惠\n");
                        printf("你的余额：%d\n",x->money);
                    }
                    else
                    {
                        person_head_log->next->money = person_head_log->next->money - p;
                        person_head_log->next->vip_money = person_head_log->next->vip_money + p;
                        person_head_log->next->money_num=p/10;
                        

                        x->money=person_head_log->next->money;
                        x->vip_money=person_head_log->next->vip_money;
                        x->money_num=person_head_log->next->money_num;
                        printf("充值成功！\n");
                        printf("您的vip等级：%s\n",person_head_log->next->vip_level);
                        printf("你的余额：%d\n",x->money);
                        save_person_file(x);
                    }
                    break;
                }
            }
            
        }

        else if(p>=5000 && p<10000)
        {

            
            for(x=person_head->next;x!=person_head;x=x->next)
            {
                if(strcmp(x->name,person_head_log->next->name)==0)
                {               
                    if(person_head_log->next->vip_off > 0.8 )
                    {
                        person_head_log->next->money = person_head_log->next->money - p;
                        person_head_log->next->vip_money = person_head_log->next->vip_money + p;
                        person_head_log->next->money_num=p/10;
                        strcpy(person_head_log->next->vip_level,"gold") ; 
                        person_head_log->next->vip_off=0.8;

                        x->money=person_head_log->next->money;
                        x->vip_money=person_head_log->next->vip_money;
                        x->money_num=person_head_log->next->money_num;
                        x->vip_off=0.8;
                        strcpy(x->vip_level,"gold") ;

                        save_person_file(x);
                        printf("充值成功！\n");
                        printf("成为黄金会员，购票获8折优惠\n");
                        printf("你的余额：%d\n",x->money);
                    }
                    else
                    {
                        person_head_log->next->money = person_head_log->next->money - p;
                        person_head_log->next->vip_money = person_head_log->next->vip_money + p;
                        person_head_log->next->money_num=p/10;
                        

                        x->money=person_head_log->next->money;
                        x->vip_money=person_head_log->next->vip_money;
                        x->money_num=person_head_log->next->money_num;
                        printf("充值成功！\n");
                        printf("您的vip等级：%s\n",person_head_log->next->vip_level);
                        printf("你的余额：%d\n",x->money);
                        save_person_file(x);
                    }
                    break;
                }
            }
            
        }

        else if(p>=10000)
        {

            
            for(x=person_head->next;x!=person_head;x=x->next)
            {
                if(strcmp(x->name,person_head_log->next->name)==0)
                {               
                    if(person_head_log->next->vip_off>0.7)
                    {
                        person_head_log->next->money = person_head_log->next->money - p;
                        person_head_log->next->vip_money = person_head_log->next->vip_money + p;
                        person_head_log->next->money_num=p/10;
                        strcpy(person_head_log->next->vip_level,"diamond") ; 
                        person_head_log->next->vip_off=0.7;

                        x->money=person_head_log->next->money;
                        x->vip_money=person_head_log->next->vip_money;
                        x->money_num=person_head_log->next->money_num;
                        x->vip_off=0.7;
                        strcpy(x->vip_level,"diamond") ;

                        save_person_file(x);
                        printf("充值成功！\n");
                        printf("成为钻石会员，购票获7折优惠\n");
                        printf("你的余额：%d\n",x->money);
                    }
                    else
                    {
                        person_head_log->next->money = person_head_log->next->money - p;
                        person_head_log->next->vip_money = person_head_log->next->vip_money + p;
                        person_head_log->next->money_num=p/10;
                        

                        x->money=person_head_log->next->money;
                        x->vip_money=person_head_log->next->vip_money;
                        x->money_num=person_head_log->next->money_num;
                        printf("充值成功！\n");
                        printf("您的vip等级：%s\n",person_head_log->next->vip_level);
                        printf("你的余额：%d\n",x->money);
                        save_person_file(x);
                    }
                    break;
                }
            }
            
        }

    }
    else
    printf("没钱啦，需要板砖\n");
}

//退票
int return_ticket(struct person_list * person_head,struct person_list * person_head_log,struct plane_list * plane_head,struct deal_list *deal_head)
{
    int choice;
    printf("请确认退票\n");
    printf("=========================================\n");
    printf("            1.确定                       \n");
    printf("            2.取消                        \n");
    printf("=========================================\n");
    scanf("%d",&choice);
    if(choice==2)
    {
        return 2;
    }
    else if(choice==1)
    {
        struct deal_list *p=NULL;
        for(p=deal_head->next;p!=deal_head;p=p->next)
        {
            if(strcmp(person_head_log->next->name,p->name_pay)==0)
            break;
        }

        //登录链
        person_head_log->next->ticket=0;
        person_head_log->next->ticket_take=0;
        person_head_log->next->ticket_bill=0;
        strcpy(person_head_log->next->ticket_name,"0");
        person_head_log->next->vip_money=p->money+person_head_log->next->vip_money;

        struct person_list *q=NULL;
        //修改注册链
        for(q=person_head->next;q!=person_head;q=q->next)
            if(strcmp(q->name,person_head_log->next->name)==0)
            {
                q->ticket=0;
                q->ticket_take=0;
                q->ticket_bill=0;
                strcpy(q->ticket_name,"0");
                q->vip_money=p->money+q->vip_money;
                //printf("*****%s********\n",q->name);
                save_person_file(q);
                break;
            }


        //飞机链
        struct plane_list *q_plane=NULL;
        for(q_plane=plane_head->next;q_plane!=plane_head;q_plane=q_plane->next)
            if(strcmp(q_plane->name_plane,p->name_plane)==0)
                {
                    
                q_plane->ticket_num++;
                save_plane_file(q_plane);
                break;
                }

        //成交链
         struct deal_list *q_deal=NULL;
         for(q_deal=deal_head->next;q_deal!=deal_head;q_deal=q_deal->next)
            if(strcmp(q_deal->name_plane,q_plane->name_plane)==0)
            {
                delete_deal_list(deal_head,q_deal);
            
                q_deal->prev->next=q_deal->next;
                q_deal->next->prev=q_deal->prev;
                
                free(q_deal);
                break;
            }
        printf("退票成功\n");
        return 0;
    }
    else 
    printf("输入有误\n");
    return 0;

}


