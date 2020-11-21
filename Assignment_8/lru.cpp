#include<bits/stdc++.h>

//implementation differs only on line number 82

using namespace std;

class Cache
{
	private:
		int *cache,n,*time1;
		void increase();
		
	public:
		Cache(int);
		bool find(int x);
		void display();
};

void Cache::display()
{
	cout<<"         \t\tThe contents of cache are : ";
	for(int i=0;i<n;++i)
	{
		cout<<cache[i]<<" ";
	}
	cout<<endl;
}

void Cache::increase()
{
	for(int i=0;i<n;++i)
	{
		if(cache[i]!=-1)
		{
			time1[i] =  time1[i] + 1;
		}	
	}
}

Cache::Cache(int n)
{
	cout<<"\nCache implementing LRU page replacement policy created!\n";
	this -> n = n;
	cache = new int[n];
	time1 = new int[n];
	for(int i=0;i<n;++i)
	{
		cache[i] = -1;
		time1[i] = INT_MAX;
	}
}

bool Cache::find(int x)
{
	bool hit_miss = false;
	int idx = -1,i;
	for(i=0;i<n;++i)
	{
		if(cache[i]==x)
		{
			idx = i;
			break;
		}
	}
	if(idx==-1)
	{
		//miss has occured
		hit_miss = false;
		int last_used = -1, last_used_time = INT_MIN;
		for(i=0;i<n;++i)
		{
			if(time1[i]>last_used_time)
			{
				last_used_time = time1[i];
				last_used = i;
			}
		}
		cache[last_used] = x;
		time1[last_used] = 0;
	}	
	else
	{
		//hit has occured
		hit_miss = true;
		time1[idx] = 0;
	}
	this -> increase();
	return hit_miss;
}	

int main()
{
	int n,f,i,page,faults = 0;
	cout<<"Enter the number of requests: ";
	cin>>n;
	cout<<"Enter the frame size: ";
	cin>>f;
	Cache c1(f);
	cout<<"\n";
	for(i=0;i<n;++i)
	{
		cout<<"Request #"<<i+1<<"\t\t";
		cout<<"Enter the page: ";
		cin>>page;
		if(c1.find(page)==false)
		{
			faults += 1;
			cout<<"         \t\tMiss!"<<endl;
		}
		else
		{
			cout<<"         \t\tHit!"<<endl;
		}
		c1.display();
		cout<<"\n";
	}
	cout<<"         \t\tPage faults: "<<faults<<endl;
	cout<<"         \t\tNumber of hits: "<<n - faults<<endl;
	return 0;
}
