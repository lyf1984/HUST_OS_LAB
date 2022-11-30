#include <pthread.h>
#include<semaphore.h>
#include <unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include <sys/types.h>
sem_t SPACE;//剩余容量
sem_t DATA;//已有数据
sem_t MUTEX;//数据互斥
int data[11];//数据
int producer_order[11] = {1,2,3,4,5,6,7,8,9,10};//保存空白数据的序号
int space_size=10;//空白数据块的数量
int consume_order[11] = {0};//保存已有数据的序号
int data_size=0;//已有数据块的数量


//更新序号数组
void update_order(int r_order,int* order){
	while((order[++r_order])!='\0')
		order[r_order-1]=order[r_order];
	order[r_order-1]='\0';
}

//生产者
void* producer(void* arg){
	int r_data;
	int r_order;
	while(1){
		int i=0,j=0;
		r_data = rand()%1000+(int)arg;//准备生产数据
		sem_wait(&SPACE);
		sem_wait(&MUTEX);
		r_order = rand()%space_size;//随机随即选择空白数据中的一块
		space_size--;//空白数据块数量减一
		data[producer_order[r_order]] = r_data;//存放数据
		consume_order[data_size++]=producer_order[r_order];//增加已有数据块
		//输出信息
		printf("生产者生产数据%d，放入%d号块;	",r_data,producer_order[r_order]);
		update_order(r_order,producer_order);
		printf("当前空白数据区域:[");
		while(producer_order[i]!='\0')
		printf(" %d",producer_order[i++]);
		printf(" ] ");
		printf("当前已有数据区域:[");
		while(consume_order[j]!='\0')
		printf(" %d",consume_order[j++]);
		printf(" ]\n");	
		sem_post(&MUTEX);
		sem_post(&DATA);
		float sleep_time = (0.001)*(rand()%901+100);//等待100ms-1s
		sleep(sleep_time);
	}
}

//消费者
void* consume(void* arg){
	int r_order;
	while(1){
		int i=0,j=0;
		sem_wait(&DATA);
		sem_wait(&MUTEX);
		r_order = rand()%data_size;//随机选择已有数据块中的一块
		data_size--;//已有数据块数量减一
		data[consume_order[r_order]] = 0;//拿取数据
		producer_order[space_size++]=consume_order[r_order];//增加空白数据块
		//输出信息
		printf("消费者拿取%d号数据块;		",consume_order[r_order]);
		update_order(r_order,consume_order);
		printf("当前空白数据区域:[");
		while(producer_order[i]!='\0')
		printf(" %d",producer_order[i++]);
		printf(" ] ");
		printf("当前已有数据区域:[");
		while(consume_order[j]!='\0')
		printf(" %d",consume_order[j++]);
		printf(" ]\n");	
		sem_post(&MUTEX);
		sem_post(&SPACE);
		float sleep_time = 0.001*(rand()%901+100);//等待100ms-1s
		sleep(sleep_time);
	}
}


int main(){
	pthread_t producer_id_1,producer_id_2;
	pthread_t consume_id_1,consume_id_2,consume_id_3;
	sem_init(&SPACE,0,10);
	sem_init(&DATA,0,0);
	sem_init(&MUTEX,0,1);
	pthread_create(&producer_id_1,NULL,(void*)producer,(void*)2000);
	pthread_create(&producer_id_2,NULL,(void*)producer,(void*)1000);
	pthread_create(&consume_id_1,NULL,(void*)consume,NULL);
	pthread_create(&consume_id_2,NULL,(void*)consume,NULL);
	pthread_create(&consume_id_3,NULL,(void*)consume,NULL);
	pthread_join(producer_id_1,NULL);
	pthread_join(producer_id_2,NULL);
	pthread_join(consume_id_1,NULL);
	pthread_join(consume_id_2,NULL);
	pthread_join(consume_id_3,NULL);
	while(1)
	printf("%d\n",rand());
	return 0;
}
