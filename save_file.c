#include "all_include.h"

void save_person_file(struct person_list *new)
{
	//的路径。
	char filename[200] = {0};
	sprintf(filename,"./person_data/%s.txt",new->id);
	//send_bufto_client("********")

	//的内容。
	char filebuf[500] = {0};
	sprintf(filebuf,"%s,%s,%s,%f,%s,%f,%d,%d,%s,%s,%d,%d,%d,%s,%d,%d",new->id,new->name,
	new->status,new->status_off,new->vip_level,
	new->vip_off,new->verify,new->ticket,
	new->ticket_name,new->ticket_date,new->money,new->money_num,new->vip_money,
	new->passwd,new->ticket_take,new->ticket_bill);

	// 打开文件。
	FILE *fp = fopen(filename,"w");

	//写入数据到文件中。
	fwrite(filebuf,strlen(filebuf),1,fp);

	//send_bufto_client("+++\n");
	//关闭文件。
	fclose(fp);

	return;
}

void save_newperson_file(struct person_list *new)
{
	//的路径。
	char filename[100] = {0};
	sprintf(filename,"./person_data/%s.txt",new->id);

	//的内容。
	char filebuf[200] = {0};
	sprintf(filebuf,"%s,%s,%s,%f,%s,%f,%d,%d,%s,%s,%d,%d,%d,%s,%d,%d",new->id,new->name,
	new->status,new->status_off,new->vip_level,
	new->vip_off,new->verify,new->ticket,
	new->ticket_name,new->ticket_date,new->money,new->money_num,new->vip_money,
	new->passwd,new->ticket_take,new->ticket_bill);

	// 打开文件。
	FILE *fp = fopen(filename,"w");

	//写入数据到文件中。
	fwrite(filebuf,strlen(filebuf),1,fp);

	//关闭文件。
	fclose(fp);

	return;
}

void save_plane_file(struct plane_list *plane_head)
{

	char filename[50] = {0};
	sprintf(filename,"./plane_data/%s.txt",plane_head->name_plane);


	char filebuf[200] = {0};
	sprintf(filebuf,"%s,%s,%s,%s,%s,%s,%d,%d",plane_head->name_plane,plane_head->start,plane_head->end,
	plane_head->time_date,plane_head->plane_type,plane_head->time_hour,plane_head->money,plane_head->ticket_num);


	FILE *fp = fopen(filename,"w");


	fwrite(filebuf,strlen(filebuf),1,fp);
	send_bufto_client("***\n");

	fclose(fp);

	//return;
}

void save_deal_file(struct deal_list *deal_head)
{

	char filename[100] = {0};
	sprintf(filename,"./deal_data/%s_%s.txt",deal_head->name_pay,deal_head->name_plane);


	char filebuf[200] = {0};
	sprintf(filebuf,"%s,%s,%s,%d",deal_head->name_pay,deal_head->name_get,deal_head->name_plane,
	deal_head->money);

	FILE *fp = fopen(filename,"w");

	fwrite(filebuf,strlen(filebuf),1,fp);

	fclose(fp);

	return;
}