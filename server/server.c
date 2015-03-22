
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "server.h"


#define portnumber		3333
#define MAX_SIZE		1024

int main(int argc, char *argv[])
{
	int sockfd, new_fd;
	struct sockaddr_in	server_addr;
	struct sockaddr_in	client_addr;
	int sin_size;
	int nbytes;
	char buffer[MAX_SIZE];

	if(-1==(sockfd=socket(AF_INET, SOCK_STREAM, 0)))
	{
		fprintf(stderr, "socket error:%s\n\a", strerror(errno));
		exit(1);
	}
	bzero(&server_addr, sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(portnumber);

	if(-1==bind(sockfd, (struct sockaddr*)(&server_addr), sizeof(struct sockaddr)))
	{
		fprintf(stderr, "Bind error:%s\n\a", strerror(errno));
		exit(1);
	}
	if(-1==listen(sockfd, 5))
	{
		fprintf(stderr, "Listen error:%s\a\a", strerror(errno));
		exit(1);
	}

	while(1)
	{
		if(-1==(new_fd = accept(sockfd, (struct sockaddr_in*)(&client_addr), sizeof(struct sockaddr_in))))
		{
			fprintf(stderr, "accept error:%s\n\a", strerror(errno));
			exit(1);
		}
		fprintf(stderr, "server get from %s\n\a", inet_ntoa(client_addr.sin_addr));
		if(-1==(nbytes = read(new_fd, buffer, MAX_SIZE)))
		{
			fprintf(stderr, "read error:%s\n\a", strerror(errno));
			exit(1);
		}
		buffer[nbytes] = '\0';
		printf("server accept:%s\n", buffer);

		close(sockfd);
	}
}

