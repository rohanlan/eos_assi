#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<signal.h>
void signal_hand(int sig)
{
	printf("sigint caught():\n ");

}
int main()
{
	char cmd[512],*ptr,*argc[32];
	int i,ret,err,s;
	signal(SIGINT,signal_hand);
	while(1){
	printf("cmd>");
	gets(cmd);
	i=0;
	ptr=strtok(cmd," ");
	argc[i]=ptr;
	i++;
	do
	{
		ptr=strtok(NULL," ");
		argc[i]=ptr;
		i++;
	}while(ptr!=NULL);
	if(strcmp(argc[0],"exit")==0)
		break;
	else if(strcmp(argc[0],"cd")==0)
		chdir(argc[1]);
	else
	{
		ret=fork();
		if(ret==0)
		{

			err=execvp(argc[0],argc);
			if(err<0)
			{
				perror("bad command");
				_exit(1);
			}
		}
		else
		{
				wait(&s);
		}
	}
}
	printf("bye!\n");
	return 0;
}
