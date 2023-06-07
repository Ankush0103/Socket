// Day 3- TCP Server Client Calculator
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
unsigned int serv_port = 25000;
int sock, b, l, len, a, rd, rd1, rd2, w;
char buff_serv[128];
int x, y, z;
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
	for(;;)
	{
		rd = read(a, buff_serv, 128);
		x = atoi(buff_serv);
		if(rd<0)
			printf("\nerror\n");
		else
			printf("\nRecieved Operator: %d\n", x);
		rd1 = read(a, buff_serv, 128);
		y = atoi(buff_serv);
		if(rd1<0)
			printf("\nerror\n");
		else
			printf("\nRecieved Operator: %d\n", y);
		
		rd2 = read(a, buff_serv, 128);
		//y = atoi(buff_serv);
		if(rd2<0)
			printf("\nerror\n");
		else
		{
			printf("\nRecieved Operand: %s\n", buff_serv);
			if(strcmp(buff_serv, "+")==0)
				z = x + y;
			else if(strcmp(buff_serv, "-")==0)
				z = x - y;
			else if(strcmp(buff_serv, "*")==0)
				z = x * y;
			else if(strcmp(buff_serv, "/") == 0)
				if(y==0)
					printf("\nDivision by zero not allowed\n");
				else
					z = x / y;
			sprintf(buff_serv, "\n%d\n", z);
			printf("\nResult: %s\n", buff_serv);
			w = write(a, buff_serv, 128);
		
		}
		
	}
}
