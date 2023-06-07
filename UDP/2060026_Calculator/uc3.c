// Day6 - UDP Server Client Calculator Implementation
// Client Side
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

struct sockaddr_in serv_addr1;
int x, y, z;
char sbuff1[128], cbuff1[128], cbuff2[128], cbuff3[128];
char serv_ip[128] = "127.0.0.1";
unsigned int serv_port = 26000;
int sock1, b1, l, len1, a, sc1, sc2, sc3, rc1, rc2, rc3;

int main()
{
	sock1 = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock1 < 0)
	{
		printf("\nSocket Error\n");
		close(sock1);
		exit(0);
	}
	serv_addr1.sin_family = AF_INET;
	serv_addr1.sin_port = htons(serv_port);
	inet_aton(serv_ip, &(serv_addr1.sin_addr));
	/*b1 = bind(sock1, (struct sockaddr *)&serv_addr1, sizeof(serv_addr1));
	if(b1<0)
	{
		printf("Bind Error\n");
		close(sock1);
		exit(0);
	}*/
	len1 = sizeof(serv_addr1);
	for(;;)
	{
		printf("Enter operand1: \n");
		scanf("%s", cbuff1);
		sc1 = sendto(sock1, cbuff1, 128, 0, (struct sockaddr *)&serv_addr1, sizeof(serv_addr1));
		if(strcmp(cbuff1, "bye")==0)
			break;
		if(sc1<0)
			printf("\nSc1 error\n");
				
		printf("Enter operand2: \n");
		scanf("%s", cbuff2);
		if(strcmp(cbuff2, "bye")==0)
			break;
		sc2 = sendto(sock1, cbuff2, 128, 0, (struct sockaddr *)&serv_addr1, sizeof(serv_addr1));
		if(sc2<0)
			printf("\nSc2 Error\n");
		printf("Enter operator: \n");
		scanf("%s", cbuff3);
		if(strcmp(cbuff3, "bye")==0)
			break;
		sc3 = sendto(sock1, cbuff3, 128, 0, (struct sockaddr *)&serv_addr1, sizeof(serv_addr1));
		if(sc3<0)
			printf("\nSc3 Error\n");
				
		rc1 = recvfrom(sock1, sbuff1, 128, 0, 	(struct sockaddr *)&serv_addr1, &len1);
		if(rc1<0)
		{
			printf("\nrc1 Error\n");
			close(sock1);
			exit(0);
		}
		else
			printf("Result is: %s\n", sbuff1);			
		
	}
	return 0;

}
