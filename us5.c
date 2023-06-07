#include <stdio.h>
//#include <sys/type.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

int sock,b,c,a,len,r,r1,s,s1;
char buff[128], buff1[128],buff2[2048],buff3[128];
char ebuff[128],ebuff1[128],ebuff2[2048];
struct sockaddr_in serv_addr,cli_addr;
char serv_ip[] = "127.0.0.1";
unsigned int serv_port = 6000;

int main()
{
	sock = socket(AF_INET , SOCK_DGRAM,0);
	if(sock<0)
	{
		printf("Socket error\n");
		exit(0);
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(serv_port);
	inet_aton(serv_ip , (&serv_addr.sin_addr));
	b = bind(sock,(struct sockaddr *)&(serv_addr),sizeof(serv_addr));
	if(b<0)
	{
		printf("Bind error\n");
		close(sock);
		exit(0);
	}
	len = sizeof(cli_addr);
	FILE * ptr;

	for(;;)
	{
		r = recvfrom(sock,buff,128,0,(struct sockaddr*)&cli_addr , &len);
		if(r<0)
		{
			printf("Read error\n");
			close(sock);
			exit(0);
		}
		else
		{
			if(strcmp(buff,"Bye")==0)
				break;
			printf("Expression received is %s\n",buff);
			buff3[128] = '\0';
			strcat(buff3,"find ");
			strcat(buff3 , buff);
			strcat(buff3, "* >files");
			system(buff3);
			
			ptr =fopen("files","r");
			while(fgets(buff1 , 128 , ptr)!='\0')
			{
				strcat(buff2,buff1);
			}
			fclose(ptr);
			s = sendto(sock,buff2,2048,0,(struct sockaddr*)&cli_addr , sizeof(cli_addr));
			if(s<0)
			{
				printf("Write error\n");
				close(sock);
				exit(0);
			}
			r1 = recvfrom(sock,ebuff,128,0,(struct sockaddr*)&cli_addr , &len);
			if(r1<0)
			{
				printf("read error 1\n");
				close(sock);
				exit(0);
			}
			else
			{				
				printf("File name received is %s\n",ebuff);
				ptr = fopen(ebuff,"r");
				while(fgets(ebuff1,128,ptr)!='\0')
				{
					strcat(ebuff2,ebuff1);
				}
				fclose(ptr);
				s1 = sendto(sock,ebuff2,2048,0,(struct sockaddr*)&cli_addr , sizeof(cli_addr));
				if(s1<0)
				{
					printf("Write error 1\n");
					close(sock);
					exit(0);
				}
			}
		}
	}
	return 0;
}

