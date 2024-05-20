#include<stdio.h>
#include<sys/wait.h>
#include<sys/msg.h>
#include<unistd.h>
#include<string.h>
int arr[2];
void sigint_handler(int sig)
{
	close(arr[0]);
	close(arr[1]);
	printf("thanks\n");
	_exit(0);

}
int main()
{
	int ret,ret1,count=1;
	char ch='o';
	ret=pipe(arr);
	struct sigaction sa;
	// step2: register signal handler
	memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = sigint_handler;
	ret = sigaction(SIGINT, &sa, NULL);
	while(1)
	{
		write(arr[1],&ch,1);
		count++;
		printf("total byte required is %d byte\n",count);
	}



	return 0;
}
