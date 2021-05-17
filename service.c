#include "all_include.h"
#include "kernel_list.h"

char send_msg_buf[500];
//int service_choice=0;
char service_buf[1000];
char service_ret_buf[1000];
char send_to_client[1000];
int time_hold=0;
//设计链表节点结构体
struct service_list_node{
	int connfd;
	struct list_head list;
};

struct service_list_node *head = NULL;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

struct service_list_node *init_list_head()
{
	//1. 为头节点申请空间
	struct service_list_node *head = NULL;
	head = malloc(sizeof(struct service_list_node));
	if(head == NULL)
		send_bufto_client("malloc error!\n");

	//2. 为指针域赋值。
	INIT_LIST_HEAD(&(head->list));

	return head;
}

int init_sock(char *port)
{
	//1. 创建TCP套接字。
	int sockfd = socket(AF_INET,SOCK_STREAM,0);

	//2. 绑定IP地址。
	struct sockaddr_in srvaddr;
	socklen_t len = sizeof(srvaddr);
	bzero(&srvaddr,len);

	srvaddr.sin_family = AF_INET;
	srvaddr.sin_port = htons(atoi(port));
	srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(sockfd,(struct sockaddr *)&srvaddr,len);

	//3. 设置监听套接字。
	listen(sockfd,5);

	return sockfd;
}

void * service_to_client(void *arg)
{
	usleep(100);
	struct service_list_node *peer=(struct service_list_node *)arg;
	while(1)
	{
		struct service_list_node *p = NULL;
		pthread_mutex_lock(&m);
		list_for_each_entry(p,&(head->list),list)
			{
				if(p->connfd == peer->connfd)  //找到自己
				{
					//continue;
					//send_bufto_client("%d+*+\n",p->connfd);
					//send_bufto_client("***%s--*\n",send_to_client);
					if(strlen(send_to_client)==0)
					continue;
					//send_bufto_client("%d+*==+\n",p->connfd);
					send(p->connfd,send_to_client,strlen(send_to_client),0);
					//send_bufto_client("--*%s++*\n",send_to_client);
					usleep(100);
					bzero(send_to_client,1000);
					time_hold=1;
				}
				//while((atoi)(service_ret_buf)==0);

				//char service_ret_buf[1000];
			}
		pthread_mutex_unlock(&m);
	}
}


int msg_broadcast(char *buf,struct service_list_node *peer)
{
	struct service_list_node *p = NULL;

	pthread_mutex_lock(&m);
	list_for_each_entry(p,&(head->list),list)
	{
		if(p->connfd == peer->connfd)  //找到自己
		{
			continue;
		}
		//while((atoi)(service_ret_buf)==0);
		while(strlen(send_to_client)==0);
		send(p->connfd,buf,strlen(buf),0);
		bzero(send_to_client,1000);
		//char service_ret_buf[1000];
	}
	pthread_mutex_unlock(&m);
}

int msg_send(char *buf,int recv_id)
{
	struct service_list_node *p = NULL;

	pthread_mutex_lock(&m);
	list_for_each_entry(p,&(head->list),list)
	{
		if(p->connfd == recv_id)  //找到私聊的那个人
		{
			while(strlen(send_to_client)==0);

			send(p->connfd,buf,strlen(buf),0);
			pthread_mutex_unlock(&m);

			bzero(send_to_client,1000);
			return 0;
		}
	}

	pthread_mutex_unlock(&m);
	return -1;
}



int get_choice_buf(char *buf,int buf_len)
{
    /* strncpy(service_buf,buf,sizeof(buf));
	sleep(1);
	send_bufto_client("***%s***\n",service_buf); */
	usleep(10);
	for(int i=0;i<buf_len;i++)
	{
		service_buf[i]=buf[i];
	}
	usleep(10);
}

char *send_bufto_client(char *buf)
{
	time_hold=0;
	//usleep(100);
	bzero(send_to_client,1000);
	int buf_len=strlen(buf);
	for(int i=0;i<buf_len-1;i++)
	{
		send_to_client[i]=buf[i];
	}
	while(time_hold==0);
	//usleep(100);
	//send_bufto_client("***%s***\n",send_to_client);
}




//线程工作： 负责监听对应的客户端说的话即可。
void *fun(void *arg)
{
	struct service_list_node *peer = (struct service_list_node *)arg;

	//线程任务： 不断听这个客户端说话。
	char buf[100];
	char *tmp = NULL;
	int recv_id;
	pthread_t send_tid;
	pthread_create(&send_tid,NULL,service_to_client,(void *)(peer));
	while(1)
	{
		bzero(buf,sizeof(buf));


		recv(peer->connfd,buf,sizeof(buf),0);
		int buf_len=sizeof(buf);

        get_choice_buf(buf,buf_len);
		
		/* send_bufto_client("********\n");
		send_bufto_client("*+%s--\n",buf);
		send_bufto_client("**+%s++\n",service_buf);
		send_bufto_client("********\n"); */

		sprintf(send_msg_buf,"from %d client:%s",peer->connfd,buf);
		send_bufto_client(send_msg_buf);

		//客户端想退出
		if(strncmp(buf,"quit",4) == 0)
		{
			close(peer->connfd);
			pthread_mutex_lock(&m);
			list_del(&(peer->list));
			pthread_mutex_unlock(&m);
			free(peer);
			break;
		}

		//客户端想群发
		/* tmp = strstr(buf,":");
		if(tmp == NULL)   //说明没有:，则是群发。
		{	
			msg_broadcast(buf,peer);
		}
		else{              //客户端想私聊   5:hello
			recv_id = atoi(buf);
			msg_send(tmp+1,recv_id);
		} */
		/* if(strlen(send_to_client)!=0)
		service_to_client(peer); */
		//send_bufto_client("++*%s++*\n",send_to_client);

	}

	//客人都走了，服务器就下班了
	pthread_exit(NULL);
}

void * service_fun(void *arg)  //  ./server 50001
{
	bzero(send_to_client,1000);
	//1. 初始化链表头 
	head = init_list_head();

    char* choice=(char *)(arg);

	//2. 初始化监听套接字。
	int sockfd = init_sock(arg);

	struct sockaddr_in cliaddr;
	socklen_t len = sizeof(cliaddr);
	bzero(&cliaddr,len);
	int connfd;
	struct service_list_node *new = NULL;	
	pthread_t tid;

	while(1)
	{
		//3. 不断阻塞等待客户端的连接。
		connfd = accept(sockfd,(struct sockaddr *)&cliaddr,&len);
		if(connfd > 0)  //有客户端连接进来了
		{
			//4. 先打印一下是谁连接进来。
			sprintf(send_msg_buf,"new connection: %s:(%d)\n",inet_ntoa(cliaddr.sin_addr),connfd);
			send_bufto_client(send_msg_buf);

			//5. 尾插到内核链表的末尾。
			new = malloc(sizeof(struct service_list_node));
			if(new != NULL)
			{
				//6. 为数据域赋值
				new->connfd = connfd;

				//7. 为指针域赋值
				pthread_mutex_lock(&m);
				list_add_tail(&(new->list),&(head->list));
				pthread_mutex_unlock(&m);
			}

			//6. 为这个新的客户端分配一个线程，用于监听这个客户单说的话。
			pthread_create(&tid,NULL,fun,(void *)new);
		}
	}

	return (void *)0;
}