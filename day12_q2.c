#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<signal.h>
int serv_fd;
void signt_handler(int sig){
	shutdown(serv_fd,SHUT_RDWR);
	unlink("/tmp/desd_sock");
	_exit(0);
}
int main()
{
	struct sockaddr_un serv_addr;
	int ret,num1,num2,result,cli_addr,cli_fd;
	socklen_t socklen;
	struct sigaction sa;
	memset(&sa,0,sizeof(struct sigaction));
	sa.sa_handler=signt_handler;
	ret=sigaction(SIGINT,&sa,NULL);
	if(ret <0)
	{
		perror("sigaction() failed");
		_exit(1);
	}
	serv_fd = socket(AF_UNIX,SOCK_STREAM,0);
	if(serv_fd < 0){
		perror("socket() failed");
		_exit(1);
		}

	serv_addr.sun_family = AF_UNIX;
	strcpy(serv_addr.sun_path,"/tmp/desd_sock");
	ret=bind(serv_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if(ret<0)
	{
		perror("bind() failed");
		_exit(1);
	
	}
	listen(serv_fd,5);
	while(1){
	socklen = sizeof(cli_addr);
	cli_fd = accept(serv_fd,(struct sockaddr*)&cli_addr,&socklen);
	if(cli_fd < 0){
		perror("accept() failed");
		_exit(1);
			}
	read(cli_fd,&num1,4);
	read(cli_fd,&num2,4);

	result = num1 + num2;

	printf("%d + %d= %d\n",num1,num2,result);

	write(cli_fd,&result,4);
	close(cli_fd);
	}

	return 0;
}
