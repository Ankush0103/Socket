#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int sock,b,len,x,y,r,r1,r2,s,result;
struct sockaddr_in serv_addr,cli_addr;
char serv_ip[] = "127.0.0.1";
unsigned int serv_port = 6000;
char sbuff[128] ,sbuff1[128],sbuff2[128],rbuff[128];

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
	for(;;)
	{
		len = sizeof(cli_addr);
		r = recvfrom(sock,sbuff,128,0,(struct sockaddr*)&cli_addr , &len);
		x = atoi(sbuff);
		if(r<0)
		{
			printf("Received error1\n");
			close(sock);
			exit(0);
		}
		else
		{
			printf("Recieved operand is %d\n",x);
		}
		r1 = recvfrom(sock,sbuff1,128,0,(struct sockaddr*)&cli_addr , &len);
		y = atoi(sbuff1);
		if(r1<0)
		{
			printf("Receiver error2\n");
			close(sock);
			exit(0);
		}
		else
		{
			printf("Recieved operand is %d\n",y);
		}
		r2 = recvfrom(sock,sbuff2,128,0,(struct sockaddr*)&cli_addr , &len);
		if(r2<0)
		{
			printf("Receiver error3\n");
			close(sock);
			exit(0);
		}
		else
		{
			printf("Recieved operator is %s\n",sbuff2);
			if(strcmp(sbuff2,"+")==0)
				result = x+y;
			else if(strcmp(sbuff2,"-")==0)
				result = x-y;
			else if(strcmp(sbuff2,"*")==0)
				result = x*y;
			else if(strcmp(sbuff2,"/")==0)
			{
				if(y==0)
					printf("Division by 0 not possible\n");
				else
					result = x/y;
			}
			sprintf(rbuff,"%d",result);
			s = sendto(sock,rbuff,128,0,(struct sockaddr*)&cli_addr , sizeof(cli_addr));
		}
	}
	return 0;
}

