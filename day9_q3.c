#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
	int ret6,ret1,ret2,ret3,ret4,ret5,err1,es1,err2,es2,err3,es3,err4,es4,err5,s,es5;
	ret1=fork();
	if(ret1==0)
	{	char *args[]={"gcc","-c","main.c",NULL};
		err1=execvp("gcc",args);
		if(err1<0)
		{
			perror("something bad happen");
			_exit(0);
		}
		wait(&s);
		es1=WEXITSTATUS(s);
	}
	ret2=fork();
	if(ret2==0)	
	{	char *args[]={"gcc","-c","circle.c",NULL};
		err2=execvp("gcc",args);
		if(err2<0)
		{
			perror("something bad happen");
			_exit(0);
		}
		wait(&s);

		es2=WEXITSTATUS(s);
	}
	ret3=fork();
	 if(ret3==0)
	{	char *args[]={"gcc","-c","rect.c",NULL};
		err3=execvp("gcc",args);
		if(err3<0)
		{
			perror("something bad happen");
			_exit(0);
		}
		wait(&s);

		es3=WEXITSTATUS(s);
	}
	ret4=fork();
	 if(ret4==0)
	{	char *args[]={"gcc","-c","square.c",NULL};
		err4=execvp("gcc",args);
		if(err4<0)
		{
			perror("something bad happen");
			_exit(0);
		}
		wait(&s);

		es4=WEXITSTATUS(s);
	}
	printf("all file compiled successfully\n");
	if(!(es1&&es2&&es3&&es4))
	{
		ret5=fork();
		if(ret5==0)
		{
			char *args[]={"gcc","-o","program.out","square.o","rect.o","circle.o","main.o",NULL};
			err5=execvp("gcc",args);
			_exit(0);

		}
		else
		{

			wait(&s);
		}
		es5=WEXITSTATUS(s);
	}
	if(!es5)
	{
		printf(".o file created succesfully\n");
		ret6=fork();
		if(ret6==0)
		{
		char *args[]={"./program.out",NULL};
		err5=execvp("./program.out",args);
		if(err5<0)
		{
			perror(" something went wrong()");
			_exit(1);
		}
		_exit(0);
		}
		else
		{
			wait(&s);
		}

	}






return 0;
}
