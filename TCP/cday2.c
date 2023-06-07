// Day 2- TCP Server Client Chat
// Client Side
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct sockaddr_in serv_addr1;
char serv_ip[128] = "127.0.0.1";
unsigned int serv_port = 25000;
char buff2[128], buff[128];
int sock1, c, rd1, w1;

int main()
{
	sock1 = socket(AF_INET, SOCK_STREAM, 0);
	if(sock1<0)
	{
		printf("\nSock error\n");
		close(sock1);
		exit(0);
	}
	serv_addr1.sin_family = AF_INET;
	serv_addr1.sin_port = htons(serv_port);
	inet_aton(serv_ip, &(serv_addr1.sin_addr));
	c = connect(sock1, (struct sockaddr*)&serv_addr1, sizeof(serv_addr1));
	if(c<0)
	{
		printf("\nConnect error\n");
		close(sock1);
		exit(0);
	}
	for(;;)
	{
		gets(buff2);
		w1 = write(sock1, buff2, 128);
		if(strcmp("bye", buff2) == 0)
			break;
		rd1 = read(sock1, buff, 128);
		if(rd1<0)
			printf("\n Read Error\n");
		printf("\nServer: %s\n", buff);
	}
	close(sock1);
	exit(0);
}
