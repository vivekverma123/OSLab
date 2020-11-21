#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>

void *thread1(void *name)
{
	int *myid = (int *)name; 
	//printf("Thread %d started\n", *(int*)name);
	for(int i=0;i<10;++i)
	{
		printf("%d: %d\n",*(int*)name,i);
	}
	//printf("Thread %d ended\n", *(int*)name);
}


int main()
{
	pthread_t tid1,tid2,tid3;
	int *val1 = (int*)malloc(sizeof(int));
	*val1 = 1;
	pthread_create(&tid1, NULL, thread1, (void*)val1); 
	int *val2 = (int*)malloc(sizeof(int));
	*val2 = 2;
	pthread_create(&tid2, NULL, thread1, (void*)val2); 
	int *val3 = (int*)malloc(sizeof(int));
	*val3 = 3;
	pthread_create(&tid3, NULL, thread1, (void*)val3); 
	pthread_exit(NULL);
	return 0;
}
