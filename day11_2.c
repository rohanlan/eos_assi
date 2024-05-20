/*The child process send two numbers to the parent process via pipe. The parent process calculate the sum and return via another pipe. The child process
print the result and exit. The parent process wait for completion of the child and then exit*/
#include<stdio.h>
#include<sys/wait.h>
#include<sys/msg.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
	int arr1[2],arr2[2],ret,ret1,num1,num2,sum;
	ret=pipe(arr1);
	ret=pipe(arr2);
	ret1=fork();

	if(ret1==0)
	{
			close(arr1[0]);
			close(arr2[1]);
			printf("enter two number\n");
			scanf("%d%d",&num1,&num2);
			write(arr1[1],&num1,4);
			write(arr1[1],&num2,4);

			read(arr2[0],&sum,4);
			printf("sum is %d\n",sum);




	}
	else
	{
		close(arr1[1]);
		close(arr2[0]);
		read(arr1[0],&num1,4);
		read(arr1[0],&num2,4);
		sum = num1 + num2;
		
		write(arr2[1],&sum,4);




	}


}
