#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>

int sock1 ,len,s1,s2,s3,r;
struct sockaddr_in serv_addr1;

char serv_ip[] = "127.0.0.1";
unsigned int serv_port = 6000;
char buff[128] ,buff1[128],buff2[128],rbuff[128];


int main()
{
	sock1 = socket(AF_INET , SOCK_DGRAM,0);
	if(sock1<0)
	{
		printf("Socket error\n");
		exit(0);
	}
	serv_addr1.sin_family = AF_INET;
	serv_addr1.sin_port = htons(serv_port);
	inet_aton(serv_ip , (&serv_addr1.sin_addr));
	while(1)
	{
		printf("Enter first number\n");
		scanf("%s",buff);
		s1 = sendto(sock1,buff,128,0,(struct sockaddr*)&serv_addr1, sizeof(serv_addr1));
		if(strcmp(buff,"Bye")==0)
			break;
		if(s1<0)
		{
			printf("Send error1\n");
			close(sock1);
			exit(0);
		}
		printf("Enter second number\n");
		scanf("%s",buff1);
		s2 = sendto(sock1,buff1,128,0,(struct sockaddr*)&serv_addr1, sizeof(serv_addr1));
		if(strcmp(buff1,"Bye")==0)
			break;
		if(s2<0)
		{
			printf("Send error2\n");
			close(sock1);
			exit(0);
		}
		printf("Enter operator\n");
		scanf("%s",buff2);
		s3 = sendto(sock1,buff2,128,0,(struct sockaddr*)&serv_addr1, sizeof(serv_addr1));
		if(strcmp(buff2,"Bye")==0)
			break;
		if(s3<0)
		{
			printf("Send error3\n");
			close(sock1);
			exit(0);
		}
		len = sizeof(serv_addr1);
		r = recvfrom(sock1,rbuff,128,0,(struct sockaddr*)&serv_addr1, &len);
		if(r<0)
		{
			printf("Receive error\n");
			close(sock1);
			exit(0);
		}
		else
		{
			printf("Result is :%s\n",rbuff);
		}
		
	}
	return 0;
}

