#ifndef ALL_INCLUDE_H_
#define ALL_INCLUDE_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <linux/input.h>
#include <sys/mman.h>
//登录链用户money
#define plane_ticket_cost p->money*person_head_log->next->vip_off * person_head_log->next->status_off

struct person_list
{
    char id[10];
    char name[10]; 
    char status[10];//身份      军人    医生    学生    普通人
    float status_off;//折扣     0.5     0.5     1       1
    char vip_level[10];//normal    白金1000   黄金5000   钻石10000
    float vip_off;//1    0.9     0.8     0.7
    int verify;//0为没实名认证，1为已认证；需要初始化0
    int ticket;//0为无票，1为已购票，需要初始化0
    char ticket_name[20];//购买机型
    char ticket_date[20];//出发时间
    int money;
    int money_num;//    money/100  积分
    int vip_money;//充值的钱
    char passwd[10];
    int ticket_take;//是否取票  0取票   1未取
    int ticket_bill;//是否取票  0取票   1未取

    struct person_list *prev;
    struct person_list *next;
   

};



struct real_info
{
    char id[10];
    char name[10]; 
    char status[10];//身份      军人soldier    医生doctor    学生stuednt    普通人normal

    struct real_info *prev;
    struct real_info *next; 

};

struct plane_list
{
    char name_plane[10];
    char start[5];
    char end[5];
    char time_date[25];//日期
    char plane_type[20];//机型
    char time_hour[25];//时间
    int money;

    int ticket;//0为无票，1为已购票
    int ticket_num;//余票

    struct plane_list *prev;
    struct plane_list *next;
    
};

struct deal_list
{

    //ggy_A001.txt  -> ggy,ggy,A001,2300,10F  依次是购买者，乘坐着、航班号、成交价格、座位
    char name_pay[20];
    char name_get[20];
    char name_plane[20];
    int money;

    struct deal_list *prev;
    struct deal_list *next;
    
};

struct list_node{
	char picname[100];
	struct list_node *next;
	struct list_node *prev;
};





    //用户功能
    void user_fun(struct person_list *,struct person_list *,struct real_info *,struct plane_list *,struct deal_list * );

    void shou_ui_menu();

    //1. 申请注册链表头节点。

	struct person_list *init_person_list_head();

    //1. 登录
    struct person_list *init_person_list_log();

    //1. 申请公安链表头节点。
	struct real_info *init_real_list_head();
	

    //1. 申请飞机链表头节点。
	struct plane_list *init_plane_list_head();
    //删除飞机连
    struct plane_list *init_plane_list_delete_head();


    //1. 申请成交链表头节点。
	struct deal_list *init_deal_list_head();

    struct list_node *init_list_pic_head();
    


    //3. 将目录下的老用户初始化到链表中。
	void init_person_list();
    void read_person_file(struct person_list *,char *);
    void insert_person_data_to_list(struct person_list *,char *);



    //3. 公安初始化到链表中。
	void init_real_list();
    void read_real_file(struct real_info *,char *);
    void insert_real_data_to_list(struct real_info *,char *buf);

    //3. 飞机初始化到链表中。
	void init_plane_list();
    void read_plane_file(struct plane_list *,char *);
    void insert_plane_data_to_list(struct plane_list *,char *buf);

    void init_plane_delete_list(struct plane_list *);

    //3. 成交初始化到链表中。
	void init_deal_list();
    void read_deal_file(struct deal_list *,char *);
    void insert_deal_data_to_list(struct deal_list *,char *);


    

    //显示界面
    void show_ui_pick_plane();
    void show_change_message_ui();
    void show_open_user_ui();
    void show_open_ui();
    

    //查询航班
    void plane_search(struct plane_list *);

    //实名认证
    void id_verify(struct person_list *,struct real_info *,struct person_list *);

    //登录链
    int person_head_login(struct person_list *,struct person_list *);

    //买票
    void buy_ticket(struct person_list *,struct plane_list *,struct person_list *,struct deal_list *);
    void buy_others_ticket(struct person_list *,struct plane_list *,struct person_list *,struct person_list *,struct deal_list *);
    void buy_others_ticket_verify(struct person_list *,struct plane_list *,struct person_list *,struct deal_list *);

    void show_ticket_pay(struct person_list *,struct person_list *,struct plane_list *);
    //保存文件
    void save_person_file(struct person_list *);
    void save_plane_file(struct plane_list *);
    void save_deal_file(struct deal_list *);

    //注册
    void person_head_logup(struct person_list *);
    void save_newperson_file(struct person_list *);

    //更新成交链
    void new_deal_insert(struct deal_list *,struct plane_list *,struct person_list *,struct person_list * , int);

    //充值
    void invest_money(struct person_list *,struct person_list *);

    //12.修改信息
    void change_message(struct person_list * ,struct person_list *,struct deal_list *);
    void change_message_normal(struct person_list * ,struct person_list *,struct deal_list *);
    void change_message_root(struct person_list * ,struct person_list *,struct deal_list *);

    //退票
    int return_ticket(struct person_list * ,struct person_list *,struct plane_list *,struct deal_list *);

    //删除成交单
    void delete_deal_list(struct deal_list *,struct deal_list *);

    //取票
    void show_ticket_ui(struct person_list *,struct person_list *,struct plane_list*);

    //开发票
    void show_bill(struct person_list *,struct person_list *,struct plane_list*);
    
   /*  ************************************* */
   //管理员
   //登陆界面
   void show_root_ui();

   void root_fun(struct person_list *,struct person_list *,struct real_info *,struct plane_list *,struct deal_list *,struct plane_list * );

    //
    int show_world();
    void insert_picname_to_list(struct list_node *,char *);
    void mmap_show_bmp(const char *);

    //
    int show_black();

    //删除修改信息后原文件
    void delete_old_person_list(struct person_list *);



#endif