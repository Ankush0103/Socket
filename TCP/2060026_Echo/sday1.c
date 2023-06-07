// Day-1: TCP Server Client Implentation Program
// Server Side
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct sockaddr_in serv_addr, cli_addr;
char serv_ip[128] = "127.0.0.1";
unsigned int serv_port = 25000;
char buff[128], buff1[128];
int sock, b, l, len, a, rd, w;

int main()
{
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock<0)
	{
		printf("\nError\n");
		close(sock);
		exit(0);
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(serv_port);
	inet_aton(serv_ip, &(serv_addr.sin_addr));
	b = bind(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if(b<0)
	{
		printf("\nError\n");
		close(sock);
		exit(0);
	}
	l = listen(sock, 7);
	if(l<0)
	{
		printf("\nError\n");
		close(sock);
		exit(0);
	}
	len = sizeof(cli_addr);
	a = accept(sock, (struct sockaddr*)&cli_addr, &len);
	if(a<0)
	{
		printf("\nError\n");
		close(sock);
		exit(0);
	}
	rd = read(a, buff, 128);
	if(rd<0)
		printf("\nError\n");
	else
	{
		buff[rd] = '\0';
		w = write(a, buff, 128);
		if(w<0)
			printf("\nError\n");
		else
			printf("\nServer echoed back\n");
	}
	return 0;
}

