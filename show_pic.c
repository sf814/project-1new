#include "all_include.h"



void insert_picname_to_list(struct list_node *head,char *picname)
{
	//1. 为新节点申请空间。
	struct list_node *new = malloc(sizeof(struct list_node));

	//2. 为数据域与指针域赋值。
	strcpy(new->picname,picname);
	new->next = head;

	//3. 寻找最后一个节点
	struct list_node *p = NULL;
	p = head->prev;

	//4. 处理指针关系。
	p->next = new;
	new->prev = p;
	head->prev = new;

	return;
}

void mmap_show_bmp(const char *picname)
{
	char bmp_buf[800*480*3] = {0};  //图片每一个像素点都是由3个字节组成，所以一共有800*480*3个字节。
	char lcd_buf[800*480*4] = {0};  //lcd每一个像素点都是由4个字节组成，所以一共有800*480*4个字节。
	char show_buf[800*480*4] = {0};
	int x,y;
	int i,j,k;

	//printf("%s\n",picname);

	//chdir("pwd");
	//1. 访问图片文件。
	FILE *fp = fopen(picname,"r");  //当前的光标在最开头
	if(fp == NULL)
		printf("fopen error!\n");

	//printf("****%s\n",picname);

	//2. 访问lcd液晶设备
	int lcd = open("/dev/fb0",O_RDWR);
	if(lcd < 0)
		printf("open lcd error!\n");

	//3. 跳过54个头数据。
	fseek(fp,54,SEEK_SET);

	//4. 将图片的数据读取到一个缓冲区中。
	int n = fread(bmp_buf,800*480*3,1,fp);
	if(n != 1)
		printf("fread error!\n");

	//5. 24位转32位
	for(i=0,j=0;i<800*480*4;i+=4,j+=3)
	{
		lcd_buf[i] = bmp_buf[j];
		lcd_buf[i+1] = bmp_buf[j+1];
		lcd_buf[i+2] = bmp_buf[j+2];
		lcd_buf[i+3] = 0;
	}

	//6. 上下颠倒
	for(y=0;y<480;y++)
	{
		for(x=0;x<800*4;x++)
		{
			show_buf[800*4*(479-y)+x] = lcd_buf[800*4*y+x];
		}
	}

	//7. 内存映射
	char *p = mmap(NULL,800*480*4,PROT_WRITE|PROT_READ,MAP_SHARED,lcd,0);
	if(p == (void *)-1)
		printf("mmap error!\n");

	//8. 不断将show_buf的内容拷贝到内存空间。
	for(k=0;k<800*480*4;k++)
	{
		memcpy(p+k,&show_buf[k],1);
	}
	
	//9. 撤销映射
	munmap(p,800*480*4);

	//10.关闭文件。
	close(lcd);
	fclose(fp);

	return;
}



int show_world()
{
	//printf("****\n");
	//1. 初始化链表头
	struct list_node *head = NULL;
	head = init_list_pic_head();

	//2. 打开目录。
	DIR *dp = opendir("./pic_data");
	if(dp == NULL)
		printf("opendir error!\n");

	//3. 切换目录。
	chdir("./pic_data");

	//4. 不断读取目录。
	struct dirent *ep = NULL;
	while(1)
	{
		ep = readdir(dp);
		if(ep == NULL)
			break;
		if(ep->d_name[0] == '.')
			continue;
		insert_picname_to_list(head,ep->d_name);
	}

	//5. 遍历链表。
	//show_list_node(head);
	
	//5. 显示第一张图片。
	struct list_node *p = head->next;
	mmap_show_bmp(p->picname);

	//5.5 找到最后一张的指针。
	struct list_node *tmp = NULL;

	//6. 进入触摸屏状态。
	int ts = open("/dev/input/event0",O_RDWR);

	//7. 读取触摸屏的数据。
	struct input_event buf;
	int x,y;
	while(1)
	{
		read(ts,&buf,sizeof(buf));
		if(buf.type == 3 && buf.code == 0)
		{
			x = buf.value;
		}

		if(buf.type == 3 && buf.code == 1)
		{
			y = buf.value;
		}

		if(buf.type == 1 && buf.code == 330 && buf.value == 0)
		{	
			if(x < 300)  //上一张
			{
				if(p->prev == head)  //说明当前正在显示第一张
				{
					p = head->prev;
				}
				else{
					p = p->prev;
				}
				mmap_show_bmp(p->picname);
			}

			if(x > 724)  //下一张
			{
				if(p->next == head)  //说明当前正在显示最后一张
				{
					p = head->next;
				}
				else{
					p = p->next;
				}
				mmap_show_bmp(p->picname);
			}

			if(x > 300 && x < 724)
			{
				return 0;
			}

				
		}
	}

	return 0;
}

int show_black()
{
	//printf("****\n");
	//1. 初始化链表头
	struct list_node *head = NULL;
	head = init_list_pic_head();

	//2. 打开目录。
	DIR *dp = opendir("./pic_data_black");
	if(dp == NULL)
		printf("opendir error!\n");

	//3. 切换目录。
	chdir("./pic_data_black");

	//4. 不断读取目录。
	struct dirent *ep = NULL;
	while(1)
	{
		ep = readdir(dp);
		if(ep == NULL)
			break;
		if(ep->d_name[0] == '.')
			continue;
		insert_picname_to_list(head,ep->d_name);
	}

	//5. 遍历链表。
	//show_list_node(head);
	
	//5. 显示第一张图片。
	struct list_node *p = head->next;
	mmap_show_bmp(p->picname);

	//5.5 找到最后一张的指针。
	struct list_node *tmp = NULL;

	//6. 进入触摸屏状态。
	int ts = open("/dev/input/event0",O_RDWR);

	//7. 读取触摸屏的数据。
	struct input_event buf;
	int x,y;
	
		read(ts,&buf,sizeof(buf));
		if(buf.type == 3 && buf.code == 0)
		{
			x = buf.value;
		}

		if(buf.type == 3 && buf.code == 1)
		{
			y = buf.value;
		}

		if(buf.type == 1 && buf.code == 330 && buf.value == 0)
		{	
			if(x < 300)  //上一张
			{
				if(p->prev == head)  //说明当前正在显示第一张
				{
					p = head->prev;
				}
				else{
					p = p->prev;
				}
				mmap_show_bmp(p->picname);
			}

			if(x > 724)  //下一张
			{
				if(p->next == head)  //说明当前正在显示最后一张
				{
					p = head->next;
				}
				else{
					p = p->next;
				}
				mmap_show_bmp(p->picname);
			}

			if(x > 300 && x < 724)
			{
				return 0;
			}

				
		}
	

	return 0;
}

