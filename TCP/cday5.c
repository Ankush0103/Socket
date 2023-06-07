// Day 5 - TCP Server Client File Implemenatation
// Client Side
#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

int sock1,c,len1,rd1,rd2,w1,w2;
char rbuff[2048] ,rbuff1[2048], sbuff[128],sbuff1[128] ;
struct sockaddr_in serv_addr1,cli_addr1;
char serv_ip[] = "127.0.0.1";
unsigned int serv_port = 26000;

int main()
{
	sock1 = socket(AF_INET , SOCK_STREAM,0);
	if(sock1<0)
	{
		printf("Socket error\n");
		exit(0);
	}
	serv_addr1.sin_family = AF_INET;
	serv_addr1.sin_port = htons(serv_port);
	inet_aton(serv_ip , (&serv_addr1.sin_addr));
	c = connect(sock1,(struct sockaddr *)&(serv_addr1) , sizeof(serv_addr1));
	if(c<0)
	{
		printf("Connect error\n");
		close(sock1);
		exit(0);
	}
	while(1)
	{
		printf("Enter your expression\n");
		scanf("%s",&sbuff);
		w1 = write(sock1,sbuff,128);
		if(strcmp(sbuff,"bye")==0)
			break;
		if(w1<0)
		{
			printf("Write error\n");
			close(sock1);
			exit(0);
		}
		else
		{
			rd1 = read(sock1, rbuff ,2048);
			if(rd1<0)
			{
				printf("Read error\n");
				close(sock1);
				exit(0);
			}
			else
			{
				printf("Output received is %s\n",rbuff);
			}
			printf("\n");
			printf("Enter file name\n");
			scanf("%s",&sbuff1);
			w2 = write(sock1,sbuff1,128);
			if(strcmp(sbuff,"bye")==0)
				break;
			if(w2<0)
			{
				printf("Write error1\n");
				close(sock1);
				exit(0);
			}
			else
			{
				rd2 = read(sock1,rbuff1,2048);
				if(rd2<0)
				{
					printf("Read error\n");
					close(sock1);
					exit(0);
				}
				else
					printf("Output is %s\n",rbuff1);
			}
		}
	}
	return 0;
}

