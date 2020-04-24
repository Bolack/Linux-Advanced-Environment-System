#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <dirent.h>
#include <fcntl.h>
#define IPADDRESS "127.0.0.1"
#define PORT 8021
#define MAXSIZE 1024
#define LISTENQ 5
#define FDSIZE 1000
#define EPOLLEVENTS 100

//函数声明
//创建套接字并进行绑定
static int socket_bind(const char *ip, int port);
//IO多路复用epoll
static void do_epoll(int listenfd);
//事件处理函数
static void handle_events(int epollfd, struct epoll_event *events, int num, int listenfd, char *buf);
//处理接收到的连接
static void handle_accpet(int epollfd, int listenfd);
//读处理
static void do_read(int epollfd, int fd, char *buf);
//写处理
static void do_write(int epollfd, int fd, char *buf);
//添加事件
static void add_event(int epollfd, int fd, int state);
//修改事件
static void modify_event(int epollfd, int fd, int state);
//删除事件
static void delete_event(int epollfd, int fd, int state);

int remove_back(char *buf);

int ls(char *buf);
int get(char *filename, char *buf, int socketfd);
int put(char *filename, char *buf, int socketfd);
int main(int argc, char *argv[])
{
	int listenfd;
	listenfd = socket_bind(IPADDRESS, PORT);
	listen(listenfd, LISTENQ);
	do_epoll(listenfd);
	return 0;
}

static int socket_bind(const char *ip, int port)
{
	int listenfd;
	struct sockaddr_in servaddr;
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd == -1)
	{
		perror("socket error:");
		exit(1);
	}
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &servaddr.sin_addr);
	servaddr.sin_port = htons(port);
	if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
	{
		perror("bind error: ");
		exit(1);
	}
	return listenfd;
}

static void do_epoll(int listenfd)
{
	int epollfd;
	struct epoll_event events[EPOLLEVENTS];
	int ret;
	char buf[MAXSIZE];
	memset(buf, 0, MAXSIZE);
	//创建一个描述符
	epollfd = epoll_create(FDSIZE);
	//添加监听描述符事件
	add_event(epollfd, listenfd, EPOLLIN);
	for (;;)
	{
		//获取已经准备好的描述符事件
		ret = epoll_wait(epollfd, events, EPOLLEVENTS, -1);
		handle_events(epollfd, events, ret, listenfd, buf);
	}
	close(epollfd);
}

static void
handle_events(int epollfd, struct epoll_event *events, int num, int listenfd, char *buf)
{
	int i;
	int fd;
	//进行选好遍历
	for (i = 0; i < num; i++)
	{
		fd = events[i].data.fd;
		//根据描述符的类型和事件类型进行处理
		if ((fd == listenfd) && (events[i].events & EPOLLIN))
			handle_accpet(epollfd, listenfd);
		else if (events[i].events & EPOLLIN)
			do_read(epollfd, fd, buf);
		else if (events[i].events & EPOLLOUT)
			do_write(epollfd, fd, buf);
	}
}
static void handle_accpet(int epollfd, int listenfd)
{
	int clifd;
	struct sockaddr_in cliaddr;
	socklen_t cliaddrlen;
	clifd = accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddrlen);
	if (clifd == -1)
		perror("accpet error:");
	else
	{
		printf("accept a new client: %s:%d\n", inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);
		//添加一个客户描述符和事件
		add_event(epollfd, clifd, EPOLLIN);
	}
}

static void do_read(int epollfd, int fd, char *buf)
{
	int nread;
	nread = read(fd, buf, MAXSIZE);
	if (nread == -1)
	{
		perror("read error:");
		close(fd);
		delete_event(epollfd, fd, EPOLLIN);
	}
	else if (nread == 0)
	{
		fprintf(stderr, "client close.\n");
		close(fd);
		delete_event(epollfd, fd, EPOLLIN);
	}
	else
	{

		printf("server read message is : %s", buf);
		//修改描述符对应的事件，由读改为写
		modify_event(epollfd, fd, EPOLLOUT);
	}
}

static void do_write(int epollfd, int fd, char *buf)
{
	if (strlen(buf) < 3)
	{
		strcpy(buf, "too little command letter\n");
	}
	else if (strcmp("ls\n", buf) == 0)
	{
		memset(buf, 0, MAXSIZE);
		ls(buf);
		write(fd, buf, strlen(buf));
	}
	else
	{
		char get_command_buf[4];
		strncpy(get_command_buf, buf, 3);
		get_command_buf[4] = '\0';
		if (strcmp("get", get_command_buf) == 0)
		{
			/* get */
			char *filename = buf + 4;
			remove_back(filename);
			if (get(filename, buf, fd) == -1)
			{
				write(fd, buf, strlen(buf));
			}
		}
		else if (strcmp("put", get_command_buf) == 0)
		{

			/* put */
			char *filename = buf + 4;
			/* test if has content */
			char *content = strchr(filename, ' ');
			if (content == NULL)
			{
				strcpy(buf, "no content input\n");
				write(fd, buf, strlen(buf));
			}
			else
			{
				int filenamelenth = content - filename;
				filename[filenamelenth] = '\0';
				content += 1;
				/* find exist */
				printf("filename \"%s\" ,content \"%s\" \n", filename, content);
				if (put(filename, content, fd) == -1)
					/* error */
					write(fd, content, strlen(content));
			}
		}
		else
		{
			strcpy(buf, "bad command line!\n");
			write(fd, buf, strlen(buf));
		}
	}
	modify_event(epollfd, fd, EPOLLIN);
	bzero(buf, MAXSIZE);
}

static void add_event(int epollfd, int fd, int state)
{
	struct epoll_event ev;
	ev.events = state;
	ev.data.fd = fd;
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

static void delete_event(int epollfd, int fd, int state)
{
	struct epoll_event ev;
	ev.events = state;
	ev.data.fd = fd;
	epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev);
}

static void modify_event(int epollfd, int fd, int state)
{
	struct epoll_event ev;
	ev.events = state;
	ev.data.fd = fd;
	epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
}

int ls(char *buf)
{
	printf("in function ls %s\n", buf);
	char *FilePath = "./";
	int i = 0;
	int filesize = 0;
	DIR *dir = NULL;
	struct dirent *entry;

	if ((dir = opendir(FilePath)) == NULL)
	{
		printf("opendir failed!");
		return -1;
	}
	else
	{
		while (entry = readdir(dir))
		{
			i++;
			if (entry->d_type != 4)
			{
				strcat(buf, entry->d_name);
				strcat(buf, "    ");
			}
		}
		strcat(buf, "\n");
		closedir(dir);
	}

	return 0;
}

int get(char *filename, char *buf, int socketfd)
{
	char *FilePath = "./";
	int i = 0;
	int filesize = 0;
	DIR *dir = NULL;
	struct dirent *entry;
	printf("in get filename is %s \n", filename);
	if ((dir = opendir(FilePath)) == NULL)
	{
		printf("opendir failed!\n");
		return -1;
	}
	else
	{
		while (entry = readdir(dir))
		{
			i++;
			if (entry->d_type != 4)
			{
				if (strcmp(filename, entry->d_name) == 0)
				{
					printf("find file \"%s\"\n", filename);
					printf("begin sending !!");
					// ordinary file
					int fd_in = open(filename, O_RDONLY);
					/* no- block IO */
					int flags = fcntl(0, F_GETFL, 0);
					flags |= O_NONBLOCK;
					fcntl(0, F_SETFL, flags);
					int size;
					int writesize;
					while ((size = read(fd_in, buf, 1024)) != 0)
					{
						writesize = write(socketfd, buf, size);
						printf("sending %d\n", writesize);
						// printf("write in %d byte errno %d\n",writesize,errno);
					}
					printf("Closesending!\n");
					closedir(dir);
					return 1;
				}
			}
		}
		printf("no such file \"%s\" \n", filename);
		strcpy(buf, "no such file ");
		strcat(buf, filename);
		strcat(buf, "\n");
		return -1; // didnt find file
		closedir(dir);
	}
}

int remove_back(char *buf)
{
	buf[strlen(buf) - 1] = '\0';
	return 1;
}

int put(char *filename, char *buf, int socketfd)
{
	char *FilePath = "./";
	int i = 0;
	int filesize = 0;
	DIR *dir = NULL;
	struct dirent *entry;

	if ((dir = opendir(FilePath)) == NULL)
	{
		printf("opendir failed!");
		return -1;
	}
	else
	{
		while (entry = readdir(dir))
		{
			if (strcmp(filename, entry->d_name) == 0)
			{
				strcpy(buf, "file already exit in FTP server\n");
				return -1;
			}
		}
		int fd_out = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
		write(fd_out, buf, strlen(buf));
		printf("write successful!");
		close(fd_out);
		return 1;
	}
}
