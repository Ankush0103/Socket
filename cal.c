//SERVER PROGRAM :

#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int sock_d , sock_b , sock_l ,sock_a , cli_len , wr_s, r_s1, r_s2, r_op ;
struct sockaddr_in serv_struct , cli_struct;
char serv_IP[] = "127.0.0.1";
unsigned int serv_port = 51350;
char x1[128] , y1[128] , op_s[128], r_s[128];
int x,y,z;
char ch ;

int main()
{
 	sock_d = socket(AF_INET,SOCK_STREAM,0);
 	if(sock_d < 0)
 	{	printf("Socket not created!! \n");
 	        close(sock_d);
 	        exit(0);
 	}
	serv_struct.sin_family = AF_INET;
	serv_struct.sin_port = htons(serv_port);
	inet_aton(serv_IP, &serv_struct.sin_addr);
	
	sock_b = bind(sock_d, (struct sockaddr*)&serv_struct , sizeof(serv_struct));
	if(sock_b< 0)
 	{	printf("Socket binding failed!! \n");
 	        close(sock_d);
 	        exit(0);
 	}
 	
 	cli_len = sizeof(cli_struct);
 	
 	sock_l = listen(sock_d , 2);
 	if(sock_l < 0)
 	{	printf("Listening failed!!");
 		close(sock_d);
 		exit(0);
 	}
 	
 	sock_a = accept(sock_d , (struct sockaddr*)&cli_struct , &cli_len);
 	if(sock_a < 0)
 	{	printf("Accepting failed!!");
 		close(sock_d);
 		exit(0);
 	}
 	
 	r_s1 = read(sock_a , x1 , 128);
 	r_s2 = read(sock_a , y1 , 128);
 	if(r_s1 >=0 && r_s2 >=0)
 		printf("The operands %s and %s are received from the client\n", x1 , y1);
 	else
 	{	printf("Receiving error\n");
 		close(sock_d);
 		exit(0);
 	}
 	x = atoi(x1);
 	y = atoi(y1);
 	r_op = read(sock_a , op_s ,128);
 	if(r_op >= 0)
 		printf("The operator %s is received from the client\n", op_s);
 	else
 	{	printf("Receiving error\n");
 		close(sock_d);
 		exit(0);
 	}
 	ch = op_s[0];
 	switch(ch)
 	{	case '+':
 			z = x+y;
 			sprintf(r_s , "%d" , z);
 			break;
 		
 		case '-':
 			z = x-y;
 			sprintf(r_s , "%d" , z);
 			break;
 		case '*':
 			z = x*y;
 			sprintf(r_s , "%d" , z);
 			break;
 		case '/':
 			if(y==0)
 				strcpy(r_s , "Dividing by zero is not possible");
 			else
 			{
 				z = x / y;
 				sprintf(r_s , "%d" , z);
 			}
 			break;
 	}
 	wr_s = write(sock_a , r_s , 128 , 0);
 	if(wr_s >=0)
		printf("The result of the operation is sent to the client\n");
 	else
 	{	printf("Sending error");
 		close(sock_d);
 		exit(0);
 	}
 	return 0;
 }

