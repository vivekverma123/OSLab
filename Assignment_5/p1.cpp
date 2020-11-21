#include<bits/stdc++.h>

using namespace std;
 
int Mutex=1,full=0,empty=3,x=0;
 
int main()
{
	int choice;
	void producer_utility();
	void consumer_utility();
	int wait(int),signal(int);
	cout<<"Enter the buffer size: ";
	cin>>empty;
	cout<<"1. Producer"<<endl;
	cout<<"2. Consumer"<<endl;
	cout<<"3. Exit"<<endl;
	while(true)
	{
		cout<<"Enter your choice (1/2/3): ";
		cin>>choice;
		switch(choice)
		{
			case 1:	
				if((Mutex==1) and (empty!=0))
				{
					producer_utility();
				}
				else
				{
					cout<<"Buffer full!!!"<<endl;
				}
				break;
				
			case 2:	
				if((Mutex==1) and (full!=0))
				{
					consumer_utility();
				}
				else
				{
					cout<<"Buffer empty!!!"<<endl;
				}
				break;
				
			case 3:
				exit(0);
				break;
			
			default:
				cout<<"Invalid Choice"<<endl;
		}
	}
	return 0;
}
 
int wait(int s)
{
	s -= 1;
	return s;
}
 
int signal(int s)
{
	s += 1;
	return s;
}
 
void producer_utility()
{
	Mutex = wait(Mutex);
	full = signal(full);
	empty = wait(empty);
	x += 1;
	cout<<"Item "<<x<<" produced!"<<endl;
	Mutex = signal(Mutex);
}
 
void consumer_utility()
{
	Mutex = wait(Mutex);
	full = wait(full);
	empty = signal(empty);
	cout<<"Item "<<x<<" consumed!"<<endl;
	x -= 1;
	Mutex = signal(Mutex);
}
