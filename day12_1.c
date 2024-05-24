#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
//p1 client
int main(){
	int fd,fd1;
	int num1,num2,sum;
	fd = open("assi_fifo",O_WRONLY);
	fd1 = open("assi_fifo1",O_RDONLY);
	if(fd < 0){
		perror("open() failed");
		_exit(1);
		}
	printf("enter two number");
	scanf("%d%d",&num1,&num2);

	write(fd,&num1,4);
	write(fd,&num2,4);

	printf("number send successfully!!!\n");

	read(fd1,&sum,4);
	printf("sum is %d\n",sum);
	close(fd);
	close(fd1);
  	return 0;
}
