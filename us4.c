#include <stdio.h>
//#include <sys/type.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

int a,b,c,d,len,rd,w;
char buff[128], buff1[128],buff2[2048];
struct sockaddr_in serv_struct,cli_struct;
char serv_ip[] = "127.0.0.1";
unsigned int serv_port = 6000;

int main()
{
	a = socket(AF_INET , SOCK_DGRAM,0);
	if(a<0)
	{
		printf("Socket error\n");
		exit(0);
	}
	serv_struct.sin_family = AF_INET;
	serv_struct.sin_port = htons(serv_port);
	inet_aton(serv_ip , (&serv_struct.sin_addr));
	b = bind(a,(struct sockaddr *)&(serv_struct),sizeof(serv_struct));
	if(b<0)
	{
		printf("Bind error\n");
		close(a);
		exit(0);
	}

	for(;;)
	{
		len = sizeof(cli_struct);
		rd = recvfrom(a,buff,128,0,(struct sockaddr*)&cli_struct , &len);
		if(rd<0)
		{
			printf("Read error\n");
			close(a);
			exit(0);
		}
		else
		{
			if(strcmp(buff,"Bye")==0)
				break;
			printf("Command received is %s\n",buff);
			strcat(buff,"> f1");
			system(buff);
			FILE * fp;
			fp =fopen("f1","r");
			while(fgets(buff1 , 128 , fp)!='\0')
			{
				strcat(buff2,buff1);
			}
			w = sendto(a,buff2,2048,0,(struct sockaddr*)&cli_struct , sizeof(cli_struct));
			if(w<0)
			{
				printf("Write error\n");
				close(a);
				exit(0);
			}
		}
	}
	return 0;
}

