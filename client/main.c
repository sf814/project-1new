#include "all_include.h"
#include "kernel_list.h"

extern int main_service_choice=0;
//设计链表节点结构体
struct list_node{
	int connfd;
	struct list_head list;
};

struct list_node *head = NULL;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

struct list_node *init_list_head()
{
	//1. 为头节点申请空间
	struct list_node *head = NULL;
	head = malloc(sizeof(struct list_node));
	if(head == NULL)
		printf("malloc error!\n");

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

int msg_broadcast(char *buf,struct list_node *peer)
{
	struct list_node *p = NULL;

	pthread_mutex_lock(&m);
	list_for_each_entry(p,&(head->list),list)
	{
		if(p->connfd == peer->connfd)  //找到自己
		{
			continue;
		}

		send(p->connfd,buf,strlen(buf),0);
	}
	pthread_mutex_unlock(&m);
}

int msg_send(char *buf,int recv_id)
{
	struct list_node *p = NULL;

	pthread_mutex_lock(&m);
	list_for_each_entry(p,&(head->list),list)
	{
		if(p->connfd == recv_id)  //找到私聊的那个人
		{
			send(p->connfd,buf,strlen(buf),0);
			pthread_mutex_unlock(&m);
			return 0;
		}
	}

	pthread_mutex_unlock(&m);
	return -1;
}

//线程工作： 负责监听对应的客户端说的话即可。
void *fun(void *arg)
{
	struct list_node *peer = (struct list_node *)arg;

	//线程任务： 不断听这个客户端说话。
	char buf[100];
	char *tmp = NULL;
	int recv_id;
	while(1)
	{
		bzero(buf,sizeof(buf));
		recv(peer->connfd,buf,sizeof(buf),0);
		printf("from %d client:%s",peer->connfd,buf);

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
		tmp = strstr(buf,":");
		if(tmp == NULL)   //说明没有:，则是群发。
		{	
			msg_broadcast(buf,peer);
		}
		else{              //客户端想私聊   5:hello
			recv_id = atoi(buf);
			msg_send(tmp+1,recv_id);
		}
	}

	//客人都走了，服务器就下班了
	pthread_exit(NULL);
}

int main(int argc,char *argv[])  //  ./server 50001
{
	//1. 初始化链表头 
	head = init_list_head();

	//2. 初始化监听套接字。
	int sockfd = init_sock(argv[1]);

	struct sockaddr_in cliaddr;
	socklen_t len = sizeof(cliaddr);
	bzero(&cliaddr,len);
	int connfd;
	struct list_node *new = NULL;	
	pthread_t tid;

	while(1)
	{
		//3. 不断阻塞等待客户端的连接。
		connfd = accept(sockfd,(struct sockaddr *)&cliaddr,&len);
		if(connfd > 0)  //有客户端连接进来了
		{
			//4. 先打印一下是谁连接进来。
			printf("new connection: %s:(%d)\n",inet_ntoa(cliaddr.sin_addr),connfd);

			//5. 尾插到内核链表的末尾。
			new = malloc(sizeof(struct list_node));
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

	return 0;
}