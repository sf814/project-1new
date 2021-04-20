#include "all_include.h"

/* 登陆前主界面


登陆后主界面
显示用户能使用功能
    1.查看航班信息
    2.查询航班
    3.快速查询
    4.实名认证

    5.购买机票

    6.帮人购买机票
        显示风景
        购买保险
    7.查看自己的票
    8.改签
    9.退票
    10.查询自己的余额
    11.充值
    12.修改信息
    13.取票
    14.开发票
 */

void shou_ui_menu()
{
    printf("=========================================\n");
    printf("            1.查看航班信息                \n");
    printf("            2.查询航班                    \n");
    printf("            3.快速查询                   \n");
    printf("            4.实名认证                    \n");
    printf("            5.购买机票                    \n");
    printf("            6.帮人购买机票                \n");
    printf("            7.查看自己的票                \n");
    printf("            8.改签                        \n");
    printf("            9.退票                        \n");
    printf("            10.查询自己的信息             \n");
    printf("            11.充值                       \n");
    printf("            12.修改信息                   \n");
    printf("            13.取票                      \n");
    printf("            14.开发票                    \n");
    printf("            15.注册                       \n");
    printf("            16.登录                        \n");
    printf("            17.展示风景                    \n");
    printf("            18.退出登录                    \n");
    printf("            19.退出登录并返回初始界面        \n");
    printf("========================================\n");
}

void show_ui_pick_plane()
{
    printf("=========================================\n");
    printf("            1.目的地                     \n");
    printf("            2.出发日期                    \n");
    printf("            3.机型                       \n");
    printf("            4.价格                       \n");
    printf("            5.返回上一级菜单               \n");
    printf("=========================================\n");

}

void show_change_message_ui()
{
    
    printf("=========================================\n");
    printf("            1.姓名                        \n");
    printf("            2.职业                        \n");
    printf("            3.ID                        \n");
    printf("            4.密码                        \n");
    printf("            5.返回上一级菜单               \n");
    printf("=========================================\n");
}


void show_ticket_ui(struct person_list * person_head,struct person_list *person_head_log,struct plane_list*plane_head)
{
    struct plane_list* q=NULL;
    struct person_list* p=NULL;
    if(person_head_log->next->ticket_take==1)
    {
        for(q=plane_head->next;q!=plane_head;q=q->next)
        {
            if(strcmp(q->name_plane,person_head_log->next->ticket_name)==0)
            {
                //更新登陆连
                person_head_log->next->ticket_take=0;
                //更新注册连
                for(p=person_head->next;p!=person_head;p=p->next)
                {
                    if(strcmp(p->name,person_head_log->next->name)==0)
                    {
                        p->ticket_take=0;
                        
                    }
                }

                //保持文件
                save_person_file(p);


                printf("==========================================\n");
                printf("姓名:%s\n",person_head_log->next->name);
                printf("航班号:%s\n",q->name_plane);
                printf("出发日期:%s\n",q->time_date);
                printf("出发时间:%s\n",q->time_hour);
                printf("==========================================\n");
                printf("出票成功\n");
                break;
            }

        }
        
    }
    else
    {
        printf("以取票,无法重复取票\n");
    }

}

void show_bill(struct person_list *person_head,struct person_list *person_head_log,struct plane_list*plane_head)
{
    struct plane_list* q=NULL;
    struct person_list* p=NULL;
    if(person_head_log->next->ticket_bill==1)
    {
        for(q=plane_head->next;q!=plane_head;q=q->next)
        {
            if(strcmp(q->name_plane,person_head_log->next->ticket_name)==0)
            {
                //更新登陆连
                person_head_log->next->ticket_bill=0;
                //更新注册连
                for(p=person_head->next;p!=person_head;p=p->next)
                {
                    if(strcmp(p->name,person_head_log->next->name)==0)
                    {
                        p->ticket_bill=0;
                        
                    }
                }

                //保持文件
                save_person_file(p);


                printf("==========================================\n");
                printf("              XXX航空普通发票              \n");
                printf("姓名:%s\n",person_head_log->next->name);
                printf("金额:%d\n",q->money);
                printf("日期:%s,时间:%s\n",q->time_date,q->time_hour);
                
                printf("==========================================\n");
                printf("出票成功\n");
                break;
            }

        }
        
    }
    else
    {
        printf("已开发票,无法重复开票\n");
    }

}

void show_open_ui()
{
    printf("=========================================\n");
    printf("=========================================\n");
    printf("                                         \n");
    printf("           欢迎使用机票购买系统           \n");
    printf("                                         \n");
    printf("=========================================\n");
    printf("=========================================\n");
    

}
void show_open_user_ui()
{
    printf("            请输入使用用户                 \n");
    printf("             1.普通用户                    \n");
    printf("             2.管理员                      \n");

}
void show_root_ui()
{
    printf("=========================================\n");
    printf("            1.查看所有航班信息            \n");
    printf("            2.查看所有人员               \n");
    printf("            3.录入航班                    \n");
    printf("            4. 删除航班                   \n");
    printf("            5.生效保险                    \n");
    printf("            6.查看删除的航班              \n");
    printf("            7.修改人员信息              \n");
    printf("            8.退出登陆，返回上一级         \n");
    printf("=========================================\n");

}

