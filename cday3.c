// Day 3- TCP Server Client Calculator
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
char buff1[128], buff2[128], buff3[128], rbuff[128];
int sock1, c, rd1, w1, w2, w3;

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
		printf("First Number: \n");
		scanf("%s", &buff1);
		w1 = write(sock1, buff1, 128);
		if(strcmp("bye", buff1)==0)
			break;
		if(w1<0)
			printf("\nError\n");
		printf("Second Number: \n");
		scanf("%s", &buff2);
		w2 = write(sock1, buff2, 128);
		if(strcmp("bye", buff2)==0)
			break;
		if(w2<0)
			printf("\nError\n");
	
		printf("Operator: \n");
		scanf("%s", &buff3);
		w3 = write(sock1, buff3, 128);
		if(strcmp("bye", buff3)==0)
			break;
		if(w3<0)
			printf("\nError\n");
		rd1 = read(sock1, rbuff, 128);
		if(rd1<0)
			printf("\nerror\n");
		else
			printf("Result is %s: \n", rbuff);
	}
	return 0;
}


