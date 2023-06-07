#include <stdio.h>
//#include <sys/type.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

int sock1,c, len1,r1,r2,s1,s2;
char rbuff[2048] ,rbuff1[2048], sbuff[128],sbuff1[128] ;
struct sockaddr_in serv_addr1,cli_addr1;
char serv_ip[] = "127.0.0.1";
unsigned int serv_port = 6000;
len1 = sizeof(serv_addr1);

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
		printf("Enter your expression\n");
		scanf("%s",&sbuff);
		s1 = sendto(sock1,sbuff,128,0,(struct sockaddr*)&serv_addr1, sizeof(serv_addr1));
		if(strcmp(sbuff,"Bye")==0)
			break;
		if(s1<0)
		{
			printf("Write error\n");
			close(sock1);
			exit(0);
		}
		else
		{	
			r1 = read(sock1, rbuff ,2048,0,(struct sockaddr*)&serv_addr1, &len1);
			if(r1<0)
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
			s2 = sendto(sock1,sbuff1,128,0,(struct sockaddr*)&serv_addr1,sizeof(serv_addr1));
			if(strcmp(sbuff,"Bye")==0)
				break;
			if(s2<0)
			{
				printf("Write error1\n");
				close(sock1);
				exit(0);
			}
			else
			{
				r2 = recvfrom(sock1,rbuff1,2048,0,(struct sockaddr*)&serv_addr1, &len1);
				if(r2<0)
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

