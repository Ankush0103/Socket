#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int sock_cd , sock_c ,w_c1 ,w_c2 , r_c , w_op;
struct sockaddr_in serv1_struct;
char serv1_IP[] = "127.0.0.1";
unsigned int serv1_port = 51350;
char x[128] , y[128] , op[128] , r[128];
int ch;

int main()
{	sock_cd = socket(AF_INET,SOCK_STREAM,0);
 	if(sock_cd < 0)
 	{	printf("Socket not created!! \n");
 	        close(sock_cd);
 	        exit(0);
 	}
 	
 	serv1_struct.sin_family = AF_INET;
	serv1_struct.sin_port = htons(serv1_port);
	inet_aton(serv1_IP, &serv1_struct.sin_addr);
	
	sock_c = connect(sock_cd,(struct sockaddr*)&serv1_struct, sizeof(serv1_struct));
	
	
 	printf("Enter the first operand: ");
 	scanf("%s",x);
	printf("Enter the second operand: ");
 	scanf("%s",y);
 	printf("The following options are available:- \n");
 	printf("1.Addition\n");
	printf("2.Subtraction\n");
	printf("3.Multiplication\n");
	printf("4.Division\n");
	printf("\nEnter your choice: ");
	scanf("%d",&ch);
	w_c1 = write(sock_cd,x,128 , 0);
	w_c2 = write(sock_cd,y,128, 0);
	if(w_c1 >=0 && w_c2 >=0)
		printf("Operands are sent to the server.\n");
	else
	{	printf("Sending error!!");
		close(sock_cd);
		exit(0);
	}
	switch(ch)
	{	case 1:
			
			strcpy(op,"+");
			break;
		case 2:
			strcpy(op,"-");
			break;
		case 3:
			strcpy(op,"*");
			break;
		case 4:
			
			strcpy(op,"/");
			break;
	}
	w_op = write(sock_cd,op,128);
	if(w_op >= 0)
		printf("The operator is sent to the server.\n");
	else
	{	printf("Sending error!!");
		close(sock_cd);
		exit(0);
	}
	r_c = read(sock_cd , r , 128);
	if(r_c >=0)
		printf("\nThe result of the operation sent from the server is:  %s" , r);
	else
	{	printf("Receiving error!!");
		close(sock_cd);
		exit(0);
	}
	return 0;
}

