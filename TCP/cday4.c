// Day4- TCP Server Client Command on file Implentation
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
unsigned int serv_port = 25003;
char buff3[2048], buff4[128];
int sock1, c, rd1, w1;

int main()
{
	sock1 = socket(AF_INET, SOCK_STREAM, 0);
	if(sock1<0)
	{
		printf("\nerror\n");
		close(sock1);
		exit(0);
	}
	serv_addr1.sin_family = AF_INET;
	serv_addr1.sin_port = htons(serv_port);
	inet_aton(serv_ip, &(serv_addr1.sin_addr));
	c = connect(sock1, (struct sockaddr*)&serv_addr1, sizeof(serv_addr1));
	if(c<0)
	{
		printf("\nerror\n");
		close(sock1);
		exit(0);
	}
	for(;;)
	{
		printf("Enter command: \n");
		scanf("%s", &buff4);
		w1 = write(sock1, buff4, 128);
		if(strcmp("bye", buff4)==0)
			break;
		if(w1<0)
		{
			printf("\nerror\n");
			close(sock1);
			exit(0);
		}
		else
		{
			rd1 = read(sock1, buff3, 2048);
			if(rd1<0)
			{
				printf("\nError\n");
				close(sock1);
				exit(0);
			}
			else
				printf("recived Output: %s\n", buff3);
		}		
	}
	
}
