#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
// p2 process

int main()
{

	int fd,fd1;
	int n1,n2,sum;
	fd = open("assi_fifo",O_RDONLY);
	fd1= open("assi_fifo1",O_WRONLY);
	if(fd<0){
		
		perror("open() failed");
		_exit(1);
	}
	printf("waiting for data\n");

	read(fd,&n1,4);
	read(fd,&n2,4);
	printf("value of number is %d and %d\n",n1,n2);

	sum=n1+n2;

	write(fd1,&sum,4);
	printf("now sum send successfully!!!\n");

	close(fd);
	close(fd1);
	



	return 0;
}

