#include<stdio.h>
#include<stdlib.h>
#include <sys/stat.h>
#include<sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<signal.h>
#include<unistd.h>
#include<wait.h>
void handler(int arg)
{
	printf("child:%d bye world!\n",getpid());
	exit(0);
}	

int main()
{
	pid_t pid;
	int shm_id;
	int* share_mem;
	shm_id = shmget(IPC_PRIVATE,sizeof(int),IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
	pid = fork();
	if(pid == 0)
	{
		signal(SIGUSR1,handler);
		share_mem = (int*)shmat(shm_id,0,0);
		*share_mem = getpid();
		shmdt(share_mem);
		while(1)
		{
			printf("child:%d I m child process alive!\n",getpid());
			sleep(1);
		}
	}
	if(pid>0)
	{
		char input;
		int child_pid;
		sleep(4);
		share_mem = (int*)shmat(shm_id,0,0);
		child_pid = *share_mem;
		shmdt(share_mem);
		shmctl(shm_id,IPC_RMID,NULL);
		while(1)
		{
			sleep(2);
			kill(child_pid,SIGSTOP);
			printf("father:%d kill child process:%d [Y/N]",getpid(),child_pid);
			input = getchar();
			getchar();//吃掉回车符
			if(input=='y'||input=='Y')
			{
				kill(child_pid,SIGUSR1);
				kill(child_pid,SIGCONT);
				wait(NULL);
				break;
			}
			kill(child_pid,SIGCONT);
		}
	}
	return 0;
}
		

