// Day6 - UDP Server Client Calculator Implementation
// Server Side
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

struct sockaddr_in serv_addr, cli_addr;
int x, y, z;
char sbuff[128], sbuff1[128], sbuff2[128], sbuff3[128];
char serv_ip[128] = "127.0.0.1";
unsigned int serv_port = 25000;
int sock, b, l, len, a, s, r1, r2, r3;

int main()
{
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock < 0)
	{
		printf("\nSocket Error\n");
		close(sock);
		exit(0);
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(serv_port);
	inet_aton(serv_ip, &(serv_addr.sin_addr));
	b = bind(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if(b<0)
	{
		printf("Bind Error\n");
		close(sock);
		exit(0);
	}
	
	len = sizeof(cli_addr);
	for(;;)
	{
		r1 = recvfrom(sock, sbuff1, 128, 0, (struct sockaddr *)&cli_addr, &len);
		if(strcmp(sbuff1, "bye")==0)
			break;
		x = atoi(sbuff1);
		if(r1<0)
		{
			printf("\nr1 Error\n");
			close(sock);
			exit(0);
		}
		else
		{
			printf("\nRecived Operand1: %d\n", x);
		}
		
		r2 = recvfrom(sock, sbuff2, 128, 0, (struct sockaddr *)&cli_addr, &len);
		if(strcmp(sbuff2, "bye")==0)
			break;
		y = atoi(sbuff2);
		if(r2<0)
		{
			printf("\nr1 Error\n");
			close(sock);
			exit(0);
		}
		else
		{
			printf("\nRecived Operand2: %d\n", y);
		}
		r3 = recvfrom(sock, sbuff3, 128, 0, (struct sockaddr *)&cli_addr, &len);
		if(strcmp(sbuff3, "bye")==0)
			break;
		if(r3<0)
		{
			printf("\nr2 Error\n");
		}
		else
		{
			printf("\nreceived operator: %s\n", sbuff3);
			if(strcmp(sbuff3, "+") == 0)
				z = x + y;
			else if(strcmp(sbuff3, "-") == 0)
				z = x - y;
			else if(strcmp(sbuff3, "*") == 0)
				z = x * y;
			else if(strcmp(sbuff3, "/") == 0)
			{
				if(y==0)
					printf("\nDivison by zero not allowed\n");
				else
					z = x/y;
			}
			sprintf(sbuff, "\n%d\n", z);
			s = sendto(sock, sbuff, 128, 0, (struct sockaddr *)&cli_addr, sizeof(cli_addr));
			printf("Result is %d\n", z);
		}
	}
	return 0;

}
