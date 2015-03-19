#include "unp.h"

#define MAXLINE 			(1024*1024)

int main(int argc, char **argv)
{
	int sockfd, n;
	char recvline[MAXLINE + 1];
	struct sockaddr_in servaddr;

	if(2!=argc)
		err_quit("usage: a.out <IPaddress>");
	if((sockfd=socket(AF_INET, SOCK_STREAM, 0))<0)
		err_sys("socket error");
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);
}

