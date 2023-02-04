#include <sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "server.h"
#define MAX 20
#define size 200

char cur_user[20];

int main()
{

       

	struct sockaddr_in server, client;
	int sd, client_addr_len, nsd;
	
	sd = socket(AF_INET, SOCK_STREAM,0);

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8081);

	if(bind(sd,(struct sockaddr *)(&server), sizeof(server))<0){
		printf("Error at bind\n");
	}

	listen(sd,10);
	client_addr_len = sizeof(client);

	while(1){
		nsd = accept(sd, (struct sockaddr *)&client, &client_addr_len);
		if(!fork()){

			close(sd);
			addAdmin(nsd,0);
			mainMenu(nsd);
			exit(0);

		}
		else
		{
			close(nsd);
		}

	}
		
	close(nsd);
	close(sd);
	return 0;
}
