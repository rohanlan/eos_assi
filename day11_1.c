/*Execute "wc" command from your program (using fork() + exec()). The command should read data from the ﬁle "in.txt" (instead of terminal) and output
should be displayed on termina*/
#include<stdio.h>
#include<string.h>
#include<sys/wait.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{
	int ret,err,s,fd;
	
	ret=fork();
	if(ret==0)
	{	fd=open("in.txt",O_RDONLY);
		dup2(fd,0);
		close(fd);

		err=execlp("wc","wc",NULL);
		if(err < 0)
		{
			perror("output get failed\n");
			_exit(1);

		}
		else
		{
			wait(&s);
		}

	}
	return 0;
	
}

