#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
	int pid,sig_no;
	printf("enter process id\n");
	scanf("%d",&pid);
	printf("enter signal number\n");
	scanf("%d",&sig_no);
	int ret=kill(pid,sig_no);
	printf("return number is %d",ret);

	return 0;
}
