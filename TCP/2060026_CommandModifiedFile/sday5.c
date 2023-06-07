// Day 5 - TCP Server Client modified Command File Implemenatation
// Server Side
#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

int sock,b,l,a,len,rd,rd1,w,w1;
char buff[128], buff1[128],buff2[2048],buff3[128];
char ebuff[128],ebuff1[128],ebuff2[2048];
struct sockaddr_in serv_addr,cli_addr;
char serv_ip[] = "127.0.0.1";
unsigned int serv_port = 26000;
FILE * ptr;

int main()
{
	sock = socket(AF_INET , SOCK_STREAM,0);
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
	l = listen(sock,5);
	if(l<0)
	{
		printf("Listen error\n");
		close(sock);
		exit(0);
	}
	len = sizeof(cli_addr);
	a = accept(sock,(struct sockaddr *)&(cli_addr) , &len);
	if(a<0)
	{
		printf("Accept error\n");
		close(sock);
		exit(0);
	}
	for(;;)
	{
		rd = read(a,buff,128);
		if(rd<0)
		{
			printf("Read error\n");
			close(sock);
			exit(0);
		}
		else
		{
			if(strcmp(buff,"bye")==0)
				break;
			printf("Expression received is %s\n",buff);
			buff3[128] = '\0';
			strcat(buff3,"find ");
			strcat(buff3 , buff);
			strcat(buff3, "* >afile2");
			system(buff3);
			ptr =fopen("afile2","r");
			while(fgets(buff1 , 128 , ptr)!='\0')
			{
				strcat(buff2,buff1);
			}
			fclose(ptr);
			w = write(a,buff2,2048);
			if(w<0)
			{
				printf("Write error\n");
				close(sock);
				exit(0);
			}
			rd1 = read(a,ebuff,128);
			if(rd1<0)
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
				w1 = write(a,ebuff2,2048);
				if(w1<0)
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

