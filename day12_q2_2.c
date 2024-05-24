#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <signal.h>

int main(int argc,char*argv[])
{
	if(argc!=3)
	{
		printf("invalid command line\n");
		_exit(1);
	}
	struct sockaddr_un serv_addr;
	int cli_fd,ret,num1,num2,result;
	cli_fd = socket(AF_UNIX,SOCK_STREAM,0);
	if(cli_fd < 0){
		perror("socket() failed");
		_exit(1);
	}
	serv_addr.sun_family=AF_UNIX;
	strcpy(serv_addr.sun_path,"/tmp/desd_sock");
	ret=connect(cli_fd,(struct sockaddr*) &serv_addr,sizeof(serv_addr));
	if(ret < 0){
		perror("connect() failed");
		_exit(1);
		}
	num1=atoi(argv[1]);
	num2=atoi(argv[2]);
	write(cli_fd,&num1,4);
	write(cli_fd,&num2,4);
	printf("data send successfully!!!\n");
	read(cli_fd,&result,sizeof(int));
	printf("%d + %d = %d\n",num1,num2,result);
	close(cli_fd);
	
	return 0;
}

