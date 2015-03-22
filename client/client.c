
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "client.h"

#define portnumber		3333
#define MAX_SIZE		1024

int main(int argc, char *argv[])
{
	int sockfd;
	char buffer[MAX_SIZE];
	struct sockaddr_in server_addr;
	struct hostent *host;

	if(2!=argc)
	{
		fprintf(stderr, "Usage:%s hostname\a\n", argv[0]);
		exit(1);
	}

	if(NULL==(host=gethostbyname(argv[1])))
	{
		fprintf(stderr, "Gethostname error\n");
		exit(1);
	}
	if(-1==(sockfd=socket(AF_INET, SOCK_STREAM, 0)))
	{
		fprintf(stderr, "socket error:%s\n", strerror(errno));
		exit(1);
	}
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(portnumber);
	server_addr.sin_addr = *((struct in_addr*)host->h_addr);

	if(-1==connect(sockfd,(struct sockaddr*)(&server_addr), sizeof(struct sockaddr)))
	{
		fprintf(stderr, "connect failed:%s\n", strerror(errno));
		exit(1);
	}

	printf("connect server success.\n");
	printf("input char:\n");

	fgets(buffer,MAX_SIZE, stdin);
	write(sockfd, buffer, strlen(buffer));

	close(sockfd);
}

