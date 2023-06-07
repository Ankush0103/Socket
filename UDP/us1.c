// Day6 - UDP Server Client Program Implementation
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
int sock, b, len, r, s;
char buff[128];
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
	b = bind(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if(b<0)
	{
		printf("\nError\n");
		close(sock);
		exit(0);
	}
	len = sizeof(cli_addr);
	r = recvfrom(sock, buff, 128, 0, (struct sockaddr*)&cli_addr, &len);
	if(r<0)
	{
		printf("\nError\n");
		close(sock);
		exit(0);
	}
	else
	{
		s = sendto(sock, buff, 128, 0, (struct sockaddr*)&cli_addr, sizeof(cli_addr));
		if(s<0)
			printf("\nError\n");	
		else
			printf("\nServer echoed back\n");
	}	
	return 0;
}
