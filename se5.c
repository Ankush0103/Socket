// Day4- TCP Server Client Command on file Implentation
// Server Side
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct sockaddr_in serv_addr, cli_addr;
char serv_ip[128] = "127.0.0.1";
unsigned int serv_port = 25004;
int sock, b, l, len, a, rd, w, rd2, w3;
char buff[128], buff1[128], buff2[2048], rbuff[128];
char ebuff[128], ebuff1[128], ebuff2[2048];
FILE *ptr;
int main()
{
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock<0)
	{
		printf("\nSock Error\n");
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
	for(;;)
	{
		rd = read(a, buff, 128);
		if(rd<0)
		{
			printf("\nerror\n");
			close(sock);
			exit(0);
		}
		else
		{
			if(strcmp("bye", buff)==0)
				break;
			printf("\nExpression recived: %s\n");
			strcat(rbuff, "find ");
			strcat(rbuff, buff);
			strcat(rbuff, "* >sef5");
			system(rbuff);
			ptr = fopen("sef5", "r");
			while(fgets(buff1, 128, ptr)!='\0')
				strcat(buff2, buff1);
			w = write(a, buff2, 2048);
			if(w<0)
			{
				printf("\nError\n");
				close(sock);
				exit(0);
			}
		}
		
		rd2 = read(a, ebuff, 128);
		if(rd2<0)
		{
			printf("\nerror\n");
			close(sock);
			exit(0);
		}
		else
		{
			if(strcmp("bye", ebuff)==0)
				break;
			printf("Filename received: %s\n", ebuff);
			ptr = fopen(ebuff, "r");
			while(fgets(ebuff, 128, ptr)!='\0')
				strcat(ebuff1, ebuff);
			w3 = write(a, ebuff2, 2048);
			if(w3<0)
			{
				printf("\nError\n");
				close(sock);
				exit(0);
			}
		}
		
	}
}

