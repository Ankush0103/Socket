#include <stdio.h>
//#include <sys/type.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

int a1,b1,c1,d1,len1,rd1,w1;
char rbuff[2048] , sbuff[128] ;
struct sockaddr_in serv1_struct,cli1_struct;
char serv_ip1[] = "127.0.0.1";
unsigned int serv_port1 = 6000;

int main()
{
	a1 = socket(AF_INET , SOCK_DGRAM,0);
	if(a1<0)
	{
		printf("Socket error\n");
		exit(0);
	}
	serv1_struct.sin_family = AF_INET;
	serv1_struct.sin_port = htons(serv_port1);
	inet_aton(serv_ip1 , (&serv1_struct.sin_addr));
	while(1)
	{
		printf("Enter your command\n");
		scanf("%s",&sbuff);
		w1 = sendto(a1,sbuff,128,0,(struct sockaddr*)&serv1_struct , sizeof(serv1_struct));
		if(strcmp(sbuff,"Bye")==0)
			break;
		if(w1<0)
		{
			printf("Send error\n");
			close(a1);
			exit(0);
		}
		else
		{
			len1 = sizeof(serv1_struct);
			rd1 = recvfrom(a1, rbuff ,2048,0,(struct sockaddr*)&serv1_struct , &len1);
			if(rd1<0)
			{
				printf("Write error\n");
				close(a1);
				exit(0);
			}
			else
			{
				printf("Output received is %s\n",rbuff);
			}
		}
	}
	return 0;
}

