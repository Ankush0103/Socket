// Day6 - UDP Server Client Program Implementation
// Client Side
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct sockaddr_in serv_addr1;
char serv_ip[128] = "127.0.0.1";
unsigned int serv_port = 25000;
int sock1, c, len1, s1, r1;
char buff1[128] = "Hi";
char buff2[128];
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
	c = connect(sock1, (struct sockaddr*)&serv_addr1, sizeof(serv_addr1));
	if(c<0)
	{
		printf("\nError\n");
		close(sock1);
		exit(0);
	}
	len1 = sizeof(serv_addr1);
	s1 = sendto(sock1, buff1, 128, 0, (struct sockaddr*)&serv_addr1, sizeof(serv_addr1));
	r1 = recvfrom(sock1, buff2, 128, 0, (struct sockaddr*)&serv_addr1, &len1);
	if(r1<0)
		printf("\nError\n");
	printf("Connected: %s\n", buff2);
	return 0;
}
