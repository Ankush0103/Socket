// Day6 - UDP Server Client Command  Implementation
// Server Side
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

struct sockaddr_in serv_addr, cli_addr;
int sock, b, len, r, s;
char buff[128], buff1[128], buff2[2048];

char serv_ip[] = "127.0.0.1";
unsigned int serv_port = 26000;
FILE *ptr;
int main()
{
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock<0)
	{
		printf("\nError\n");
		close(sock);
		exit(0);
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(serv_port);
	inet_aton(serv_ip, &(serv_addr.sin_addr));
	b = bind(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if(b<0)
	{
		printf("\nError\n");
		close(sock);
		exit(0);
	}
	len = sizeof(cli_addr);
	for(;;)
	{
		r = recvfrom(sock, buff, 128, 0, (struct sockaddr *)&cli_addr, &len);
		if(r<0)
		{
			printf("\nr error\n");
			close(sock);
			exit(0);
		}
		else
		{
			if(strcmp(buff,"bye")==0)
				break;
			printf("Command received is %s\n",buff);
			strcat(buff, "> fe4");
			system(buff);
			ptr = fopen("fe4", "r");
			while(fgets(buff1, 128, ptr)!='\0')
			{
				strcat(buff2, buff1);
			}
			s = sendto(sock, buff2, 2048, 0, (struct sockaddr *)&cli_addr, sizeof(cli_addr));
			if(s<0)
			{
				printf("\nError\n");
				close(sock);
				exit(0);
			}				
		}
	}
	return 0;
}

