// Day6 - UDP Server Client Chat Implementation
// Client Side
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

struct sockaddr_in serv_addr1;
int sock1, b1, len1, r1, s1;
char buff[128];
char buff2[128];
char serv_ip[] = "127.0.0.1";
unsigned int serv_port = 25000;

int main()
{
	sock1 = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock1<0)
	{
		printf("\nError\n");
		close(sock1);
		exit(0);
	}
	serv_addr1.sin_family = AF_INET;
	serv_addr1.sin_port = htons(serv_port);
	inet_aton(serv_ip, &(serv_addr1.sin_addr));
	len1 = sizeof(serv_addr1);
	for(;;)
	{
		gets(buff2);
		s1 = sendto(sock1, buff2, 128, 0, (struct sockaddr *)&serv_addr1, sizeof(serv_addr1));
		if(strcmp(buff2, "bye") == 0)
			break;
		r1 = recvfrom(sock1, buff, 128, 0, (struct sockaddr *)&serv_addr1, &len1);
		if(r1<0)
			printf("\nError\n"); 
		printf("\nServer: %s\n", buff);
	}
	return 0;
}

