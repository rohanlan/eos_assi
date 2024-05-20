/*The child process send two numbers to the parent process via message queue. The parent process calculate the sum and return via same message queue.
The child process print the result and exit. The parent process wait for completion of the child and then exit.*/

#include<stdio.h>
#include<sys/msg.h>
#include<unistd.h>
#include<sys/wait.h>
#define MQ_KEY 0x1234
#define MQ_KEYR 0x1111
typedef struct msg{

	long type;
	int num1,num2,sum,rsum; 

}msg_t;
typedef struct msg_parent{
	long type;
	int  add;
}msg_pt;

int main()
{
	int mqid,ret,s,ret2,mqid_r;
	mqid = msgget(MQ_KEY,IPC_CREAT | 0600);
	mqid_r=msgget(MQ_KEYR,IPC_CREAT| 0600);
	if(mqid < 0)
	{
		perror("msgget() failed");
		_exit(1);

	}
	ret=fork();
	if(ret==0)
	{
			msg_t m1,m6;
			msg_pt m5;
			m1.type=1;
			printf("sender:please enter two number ");
			scanf("%d%d",&m1.num1,&m1.num2);
			ret=msgsnd(mqid,&m1,8,0);
			if(ret==0)
			{
				printf("msg send successfully!!!");
			}
			ret2=msgrcv(mqid_r,&m5,4,1,0);
		

			printf("result in child is %d\n",m5.add);

			msgctl(mqid_r,IPC_RMID,NULL);

	}
	else
	{
		msg_t m2,m8;
		msg_pt m3;
		m3.type=1;
		ret=msgrcv(mqid,&m2,8,1,0);
		printf("msg reached successfully\n");
		m2.sum=m2.num1 + m2.num2;
		printf("sum is in parent is %d\n",m2.sum);
		m3.add=m2.sum;
	//	m8.sum=m2.sum;
		ret2=msgsnd(mqid_r,&m3,4,0);
		//ret2=msgsnd(mqid,&m8,4,0);
		if(ret2==0)
		{
			printf("parent can send msg effectively\n");
		}
		else
		{
			printf("something went wrong\n");
		}
		wait(&s);

		msgctl(mqid,IPC_RMID,NULL);

		

	}

	return 0;
}


