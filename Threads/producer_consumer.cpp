#include<iostream>
#include<thread>

using namespace std;

int mutex = 1,empty = 0,full = 0,n;

void wait(int *ptr)
{
	while(*ptr <= 0);
	(*ptr)--;
}

void signal(int *ptr)
{
	*ptr += 1;
}

void consume()
{
	int i = 0;
	do
	{
		wait(&full);
		wait(&mutex);
		
		printf("Item %d removed from buffer.\n",i);
		
		/* this region is the critical section as only consumer has the access to the buffer */
		
		signal(&mutex);
		signal(&empty);
		
		printf("Item %d consumed from buffer.\n",i);
		
		i += 1;
		if(i==n)
		{
			break;
		}	
		
	}while(1);
}

void produce()
{
	int i = 0;
	do
	{
		printf("Item %d produced.\n",i);
		
		wait(&empty);
		wait(&mutex);
		
		printf("Item %d added to the buffer.\n",i);
		
		/* this region is the critical section as only producer has the access to the buffer */
		
		signal(&mutex);
		signal(&full);
		
		i += 1;
		if(i==n)
		{
			break;
		}	
		
	}while(1);
}

int main()
{
	thread prod,cons;
	printf("Enter the number of items to be produced: ");
	scanf("%d",&n);
	empty = n;
	prod = thread(produce);
	cons = thread(consume);
	prod.join();
	cons.join();
	pthread_exit(NULL);
	return 0;
}
