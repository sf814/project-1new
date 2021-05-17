
#include "all_include.h"

char service_buf[1000];
char service_ret_buf[1000];
char send_msg_buf[500];
/* ==================================注册链=========================================== */
 void insert_person_data_to_list(struct person_list *person_head,char *buf)
{
	//1. 为新节点申请空间。
	struct person_list *new = malloc(sizeof(struct person_list));

	//2. 为数据域和指针域赋值。
	char seqs[] = ",";
	//id
	char *tmp = strtok(buf,seqs);
	strcpy(new->id,tmp);

	//姓名
	tmp = strtok(NULL,seqs);
	strcpy(new->name,tmp);

	//身份
	tmp = strtok(NULL,seqs);
	strcpy(new->status,tmp);

	//身份折扣
    tmp = strtok(NULL,seqs);
	new->status_off=atof(tmp);
	//vip等级f
	tmp = strtok(NULL,seqs);
	strcpy(new->vip_level,tmp);
	//vip折扣
	tmp = strtok(NULL,seqs);
	new->vip_off=atof(tmp);
	//实名认证
	tmp = strtok(NULL,seqs);
	new->verify=atoi(tmp);
	//有误买票
	tmp = strtok(NULL,seqs);
	new->ticket=atoi(tmp);
	//机票名
	tmp = strtok(NULL,seqs);
	strcpy(new->ticket_name,tmp);
	//出发时间
	tmp = strtok(NULL,seqs);
	strcpy(new->ticket_date,tmp);
	//积分
	tmp = strtok(NULL,seqs);
	new->money_num=atoi(tmp);
	//vip余额
	tmp = strtok(NULL,seqs);
	new->vip_money=atoi(tmp);
	//密码
	tmp = strtok(NULL,seqs);
	strcpy(new->passwd,tmp);
	//取票
	tmp = strtok(NULL,seqs);
	new->ticket_take=atoi(tmp);
	//发票
	tmp = strtok(NULL,seqs);
	new->ticket_bill=atoi(tmp);

    //send_bufto_client("***99**\n");
    //new->status_off=1;
    //strcpy(new->vip_level,"normal");
    //new->vip_off=1;
    //new->verify=0;
    //new->ticket=0;
    new->money=100000;
    //new->money_num=0;


	new->next = person_head;

	//3. 寻找最后一个节点。
	struct person_list *p = NULL;
	p = person_head->prev;

	p->next = new;
	new->prev = p;
	person_head->prev = new;
    //send_bufto_client("**88***\n");
	return;
} 

void read_person_file(struct person_list *person_head,char *filename)
{	
	//1. 打开文件
	FILE *fp = fopen(filename,"r");
	if(fp == NULL)
		send_bufto_client("fopen error!\n");

	//2. 读取文件。
	char buf[200] = {0};
	fread(buf,200,1,fp);

	//3. 关闭文件。
	fclose(fp);

	//4. 将buf分隔后，插入到链表中。
	insert_person_data_to_list(person_head,buf);

	return;
}

void init_person_list(struct person_list *person_head)
{
	//1. 打开目录。
    //send_bufto_client("***11**\n");
	DIR *dp = opendir("./person_data");
	if(dp == NULL)
		send_bufto_client("opendir error!");

	//2. 切换目录。
	chdir("./person_data");

	//3. 读取该目录的下的内容。
	struct dirent *ep = NULL;
	while(1)
	{
		ep = readdir(dp);
		if(ep == NULL)
			break;
		if(ep->d_name[0] == '.')
			continue;
		read_person_file(person_head,ep->d_name);
	}

	chdir("..");

	//4. 关闭目录。
	closedir(dp);
	return;
}

/* ==================================注册链=========================================== */





/* ==================================注册新用户=========================================== */
void person_head_logup(struct person_list *person_head)
{
	char id[10];
    char name[10]; 
    char status[10];//身份      军人    医生    学生    普通人
	char passwd[10];
	struct person_list * old=NULL;
	
	send_bufto_client("请依次输入你的ID，姓名，职业，密码\n");
	//scanf("%s%s%s%s",id,name,status,passwd);
	ret_buf(id,sizeof(id));
	//send_bufto_client("***%s**\n",id);
	ret_buf(name,sizeof(name));
	ret_buf(status,sizeof(status));
	ret_buf(passwd,sizeof(passwd));
	for(old=person_head->next;old!=person_head;old=old->next)
	{
		if(strcmp(old->name,name)==0)
		{send_bufto_client("该用户名已存在，请重新注册\n");
		return;}
	}

	struct person_list *new=malloc(sizeof(struct person_list));
	strcpy(new->id,id);	
	strcpy(new->name,name);	
	strcpy(new->status,status);
	new->status_off=1;
	strcpy(new->vip_level,"normal");
	new->vip_off=1;

	new->verify=0;
	new->ticket=0;
	memset(new->ticket_name,0,sizeof(new->ticket_name));
	memset(new->ticket_date,0,sizeof(new->ticket_date));
	strcpy(new->ticket_name,"ticket_name");
	//send_bufto_client("***%s\n",new->ticket_date);
	strcpy(new->ticket_date,"ticket_date");
	new->money=10000;
	new->money_num=0;
	new->vip_money=0;

	//send_bufto_client("%s\n",new->ticket_name);
	//send_bufto_client("%s\n",new->ticket_date);
	memset(new->passwd,0,sizeof(new->passwd));
	strcpy(new->passwd,passwd);
	new->ticket_take=0;
	new->ticket_bill=0;

	struct person_list *p=NULL;
	p=person_head->prev;

	p->next=new;
	new->next=person_head;
	new->prev=p;
	person_head->prev=new;
	
	save_newperson_file(new);
}
/* ==================================注册新用户=========================================== */





/* ==================================登录链=========================================== */

int person_head_login(struct person_list * person_head,struct person_list *person_head_log)
{	
	int x=0;
	char name[10];
	char passwd[10];
	//1. 为新节点申请空间。
	
	struct person_list *p =NULL;
	send_bufto_client("请输入你的姓名\n");
	//scanf("%s",name);
	ret_buf(name,sizeof(name));
	for(p=person_head->next;p!=person_head;p=p->next)
	{
		if(strcmp(p->name,name)==0)
		{
			x=1;
			send_bufto_client("请输入密码\n");
			//scanf("%s",passwd);
			ret_buf(passwd,sizeof(passwd));
			if(strcmp(p->passwd,passwd)==0)
			{
				struct person_list *new = malloc(sizeof(struct person_list));
				strcpy(new->id,p->id);
				strcpy(new->name,p->name);
				strcpy(new->status,p->status);
				new->status_off=p->status_off;
				strcpy(new->vip_level,p->vip_level);
				new->vip_off=p->vip_off;
				new->verify=p->verify;
				new->ticket=p->ticket;
				strcpy(new->ticket_name,p->ticket_name);
				new->money=p->money;
				new->money_num=p->money_num;
				new->vip_money=p->vip_money;
				strcpy(new->passwd,p->passwd);				
				new->ticket_take=p->ticket_take;
				new->ticket_bill=p->ticket_bill;


				new->next=person_head_log;


				person_head_log->next=new;
				person_head_log->prev=new;
				new->next=person_head_log;
				new->prev=person_head_log;
				send_bufto_client("登陆成功\n");
				return 1;

			}
			else
			send_bufto_client("密码错误\n");
			return 2;

		}
	}
	if(x==1)
	send_bufto_client("不存在该用户\n");
	return 2;	

}

/* ==================================登录链=========================================== */






/* ==================================公安链=========================================== */

 void insert_real_data_to_list(struct real_info *real_head,char *buf)
{
	//1. 为新节点申请空间。
	struct real_info *new = malloc(sizeof(struct real_info));

	//2. 为数据域和指针域赋值。
	char seqs[] = ",";
	char *tmp = strtok(buf,seqs);
	strcpy(new->id,tmp);

	tmp = strtok(NULL,seqs);
	strcpy(new->name,tmp);

	tmp = strtok(NULL,seqs);
	strcpy(new->status,tmp);


	new->next = real_head;

	//3. 寻找最后一个节点。
	struct real_info *p = NULL;
	p = real_head->prev;

	p->next = new;
	new->prev = p;
	real_head->prev = new;

	return;
} 

void read_real_file(struct real_info *real_head,char *filename)
{	
	//1. 打开文件
	FILE *fp = fopen(filename,"r");
	if(fp == NULL)
		send_bufto_client("fopen error!\n");

	//2. 读取文件。
	char buf[200] = {0};
	fread(buf,200,1,fp);

	//3. 关闭文件。
	fclose(fp);

	//4. 将buf分隔后，插入到链表中。
	insert_real_data_to_list(real_head,buf);

	return;
}

void init_real_list(struct real_info *real_head)
{
    //send_bufto_client("**22***\n");
	//1. 打开目录。
	DIR *dp = opendir("./real_info");
	if(dp == NULL)
		send_bufto_client("opendir error!");

	//2. 切换目录。
	chdir("./real_info");

	//3. 读取该目录的下的内容。
	struct dirent *ep = NULL;
	while(1)
	{
		ep = readdir(dp);
		if(ep == NULL)
			break;
		if(ep->d_name[0] == '.')
			continue;
		read_real_file(real_head,ep->d_name);
	}
	
	chdir("..");
	
	//4. 关闭目录。
	closedir(dp);
	return;
}



/* ==================================公安链=========================================== */








/* ==================================飞机链=========================================== */

void insert_plane_data_to_list(struct plane_list *plane_head,char *buf)
{
    //send_bufto_client("***\n");
	//1. 为新节点申请空间。
	struct plane_list *new = malloc(sizeof(struct plane_list));

	//2. 为数据域和指针域赋值。
	char seqs[] = ",";
	char *tmp = strtok(buf,seqs);
	strcpy(new->name_plane,tmp);

	tmp = strtok(NULL,seqs);
	strcpy(new->start,tmp);

	tmp = strtok(NULL,seqs);
	strcpy(new->end,tmp);

    tmp = strtok(NULL,seqs);
	strcpy(new->time_date,tmp);

    tmp = strtok(NULL,seqs);
	strcpy(new->plane_type,tmp);

    tmp = strtok(NULL,seqs);
	strcpy(new->time_hour,tmp);

    tmp = strtok(NULL,seqs);
	new->money = atoi(tmp);

	tmp = strtok(NULL,seqs);
	new->ticket_num = atoi(tmp);
    


	new->next = plane_head;

	//3. 寻找最后一个节点。
	struct plane_list *p = NULL;
	p = plane_head->prev;

	p->next = new;
	new->prev = p;
	plane_head->prev = new;
    //send_bufto_client("**33*\n");
	return;
} 

void read_plane_file(struct plane_list *plane_head,char *filename)
{	
	//1. 打开文件
    //send_bufto_client("***55**\n");
	FILE *fp = fopen(filename,"r");
	if(fp == NULL)
		send_bufto_client("fopen error!\n");

	//2. 读取文件。
	char buf[200] = {0};
	fread(buf,200,1,fp);

	//3. 关闭文件。
	fclose(fp);

	//4. 将buf分隔后，插入到链表中。
	insert_plane_data_to_list(plane_head,buf);
    //send_bufto_client("***44**\n");
	return;
}

void init_plane_list(struct plane_list *plane_head)
{
    //send_bufto_client("***54225**\n");
	//1. 打开目录。
	DIR *dp = opendir("./plane_data");
	if(dp == NULL)
	    perror("opendir");
    //send_bufto_client("***54225**\n");
	//2. 切换目录。
	chdir("./plane_data");
    //send_bufto_client("***5455**\n");
	//3. 读取该目录的下的内容。
	struct dirent *ep = NULL;

	while(1)
	{
		ep = readdir(dp);
		if(ep == NULL)
			break;
		if(ep->d_name[0] == '.')
			continue;
		read_plane_file(plane_head,ep->d_name);
	}
    //send_bufto_client("***575**\n");
	chdir("..");

	//4. 关闭目录。
	closedir(dp);
	return;
} 


//删除连
void init_plane_delete_list(struct plane_list *plane_delete_head)
{
    //send_bufto_client("***54225**\n");
	//1. 打开目录。
	DIR *dp = opendir("./plane_delete");
	if(dp == NULL)
	    perror("opendir");
    //send_bufto_client("***54225**\n");
	//2. 切换目录。
	chdir("./plane_delete");
    //send_bufto_client("***5455**\n");
	//3. 读取该目录的下的内容。
	struct dirent *ep = NULL;

	while(1)
	{
		ep = readdir(dp);
		if(ep == NULL)
			break;
		if(ep->d_name[0] == '.')
			continue;
		read_plane_file(plane_delete_head,ep->d_name);
	}
    //send_bufto_client("***575**\n");
	chdir("..");

	//4. 关闭目录。
	closedir(dp);
	return;
}
/* ==================================飞机链=========================================== */






/* ==================================成交链=========================================== */

void insert_deal_data_to_list(struct deal_list *deal_head,char *buf)
{
	//send_bufto_client("opendir error!");
	//1. 为新节点申请空间。
	struct deal_list *new = malloc(sizeof(struct deal_list));

	//2. 为数据域和指针域赋值。
	char seqs[] = ",";
	char *tmp = strtok(buf,seqs);
	strcpy(new->name_pay,tmp);

	tmp = strtok(NULL,seqs);
	strcpy(new->name_get,tmp);

	tmp = strtok(NULL,seqs);
	strcpy(new->name_plane,tmp);

    tmp = strtok(NULL,seqs);
	new->money = atoi(tmp);



	new->next = deal_head;

	//3. 寻找最后一个节点。
	struct deal_list *p = NULL;
	p = deal_head->prev;

	p->next = new;
	new->prev = p;
	deal_head->prev = new;

	return;
} 

void read_deal_file(struct deal_list *deal_head,char *filename)
{	
	//1. 打开文件
	FILE *fp = fopen(filename,"r");
	if(fp == NULL)
		send_bufto_client("fopen error!\n");

	//2. 读取文件。
	char buf[200] = {0};
	fread(buf,200,1,fp);

	//3. 关闭文件。
	fclose(fp);

	//4. 将buf分隔后，插入到链表中。
	insert_deal_data_to_list(deal_head,buf);

	return;
}

void init_deal_list(struct deal_list *deal_head)
{
    //send_bufto_client("***545**\n");
	
	//1. 打开目录。
	DIR *dp = opendir("./deal_data");
	if(dp == NULL)
		send_bufto_client("opendir error!");

	//2. 切换目录。
	chdir("./deal_data");

	//3. 读取该目录的下的内容。
	struct dirent *ep = NULL;
	while(1)
	{
		ep = readdir(dp);
		if(ep == NULL)
			break;
		if(ep->d_name[0] == '.')
			continue;
		read_deal_file(deal_head,ep->d_name);
	}

	chdir("..");

	//4. 关闭目录。
	closedir(dp);
	return;
}
/* ==================================成交链=========================================== */


/* ==================================新成交单=========================================== */
void new_deal_insert(struct deal_list *deal_head,struct plane_list *plane,struct person_list *person,struct person_list *person_take,int return_money)
{
	char name_pay[10];
    char name_get[10];
    char name_plane[10];
    int money;
	struct deal_list *new=malloc(sizeof(struct deal_list));
	strcpy(new->name_pay,person->name);
	strcpy(new->name_get,person_take->name);
	strcpy(new->name_plane,plane->name_plane);
	new->money=return_money;
	

	struct deal_list *p=NULL;
	p=deal_head->prev;

	p->next=new;
	new->next=deal_head;
	new->prev=p;
	deal_head->prev=new;
	
	save_deal_file(new);
}
/* ==================================新成交单=========================================== */

/* ==================================删除成交单=========================================== */
void delete_deal_list(struct deal_list *deal_head,struct deal_list *new)
{
	//路径。
	char filename[100] = {0};
	sprintf(filename,"rm ./deal_data/%s_%s.txt",new->name_pay,new->name_plane);	
	system(filename);
	return;
}

/* ==================================删除成交单=========================================== */


/* ==================================删除修改信息后原文件=========================================== */
void delete_old_person_list(struct person_list *new)
{
	//路径。
	sprintf(send_msg_buf,"****%s\n",new->id);
	send_bufto_client(send_msg_buf);

	char filename[100] = {0};
	sprintf(filename,"rm ./person_data/%s.txt",new->id);	
	system(filename);
	return;
}
/* ==================================删除修改信息后原文件=========================================== */