#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include<stdlib.h>
#include <semaphore.h>
sem_t MUTEX;
void* func_A(void *arg);
void* func_B(void *arg);
int main(){
	pthread_t th_A,th_B;
	int result;
	sem_init(&MUTEX,0,1);
	result = pthread_create(&th_A,NULL,func_A,NULL);
	if(result!=0)
	{
	printf("create thread A failed\nerror code:%d\n",result);
	return 0;
	}
	result = pthread_create(&th_B,NULL,func_B,NULL);
	if(result!=0)
	{
	printf("create thread B failed\nerror code:%d\n",result);
	return 0;
	}
	//回收线程
	pthread_join(th_A,NULL);
	pthread_join(th_B,NULL);
	return 0;
}

//thread A
void* func_A(void* arg){
	int i;
	for(i=1;i<=1000;i++){
	sem_wait(&MUTEX);
	printf("A:%04d\n",i);
	sem_post(&MUTEX);
	sleep(0.5);
	}
	pthread_exit(NULL);
}
//thread B
void* func_B(void* arg){
	int i;
	for(i=1000;i>=1;i--){
	sem_wait(&MUTEX);
	printf("B:%04d\n",i);
	sem_post(&MUTEX);
	sleep(0.5);
	}
	pthread_exit(NULL);
}
