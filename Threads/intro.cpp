#include<iostream>
#include<thread>

using namespace std;

mutex m1;

bool mutex1 = true;

void lock(bool &mutex1)
{
	while(mutex1==false);
	mutex1 = false;
}

void unlock(bool &mutex1)
{
	mutex1 = true;
}

void func(int l, int r, int x)
{
	for(int i=l;i<=r;++i)
	{
		//lock(mutex1);
		m1.lock();
		cout<<x<<": "<<i<<endl;
		m1.unlock();
		//unlock(mutex1);
	}
}

int main()
{
	thread t1,t2,t3;
	t1 = thread(func,1,5,1);
	t2 = thread(func,6,10,2);
	t3 = thread(func,11,15,3);
	t1.join();
	t2.join();
	t3.join();
	return 0;
}
