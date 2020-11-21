#include<bits/stdc++.h>

using namespace std;

class memory_fixed
{
	private:
		vector <pair<int,int>> p1;
		vector <int> p2;
		bool *arr;
		int n1, n2;
		vector <int> record;
		
	public:
		memory_fixed(vector<int>&,vector<int>&);
		void first_fit();
		void best_fit();
		void worst_fit();
		void clear();
		void display();
};

void memory_fixed::clear()
{
	int i,j;
	for(i=0;i<n1;++i)
	{
		p1[i].first = 0;
		arr[i] = false;
		record[i] = -1;
	}
}

void memory_fixed::display()
{
	int i,j,internal = 0,external = 0;
	cout<<left<<setw(15)<<"Partition"<<left<<setw(15)<<"Fragment Size"<<left<<setw(15)<<"Capacity"<<left<<setw(15)<<"Free Space"<<left<<setw(15)<<"Processes"<<endl;
	for(i=0;i<n1;++i)
	{
		cout<<left<<setw(15)<<i+1<<left<<setw(15)<<p1[i].first<<left<<setw(15)<<p1[i].second<<left<<setw(15)<<p1[i].second - p1[i].first;
		if(record[i]==-1)
		{
			cout<<"N/A";
		}
		else
		{
			internal += p1[i].second - p1[i].first;
			cout<<record[i];
		}
		cout<<endl;
		external += p1[i].second - p1[i].first;
	}
	cout<<"Total internal fragmentation: "<<internal<<endl;
	cout<<"Total external fragmentation: "<<external<<endl;
}	

memory_fixed::memory_fixed(vector <int> &partitions, vector <int> &processes)
{
	p2 = processes;
	n1 = partitions.size();
	n2 = processes.size();
	arr = new bool[n1];
	int i;
	for(i=0;i<n1;++i)
	{
		p1.push_back({0,partitions[i]});
		arr[i] = false;
		record.push_back(-1);
	}
}

void memory_fixed::first_fit()
{
	clear();
	int i,j,flag = 0;
	for(i=0;i<n2;++i)
	{
		flag = 0;
		for(j=0;j<n1;++j)
		{
			if(p2[i]<=p1[j].second and arr[j]==false)
			{
				++flag;
				break;
			}
		}
		if(flag==1)
		{
			arr[j] = true;
			p1[j].first = p2[i];
			record[j] = i + 1;
		}
		else
		{
			cout<<(i+1)<<" "<<" cannot be allocated memory, External Fragmentation"<<endl;
		}
	}
}

void memory_fixed::best_fit()
{
	clear();
	int i,j,best_size,idx = -1;
	for(i=0;i<n2;++i)
	{
		best_size = INT_MAX;
		idx = -1;
		for(j=0;j<n1;++j)
		{
			if(p1[j].second>= p2[i] and arr[j]==false)
			{
				if(p1[j].second<best_size)
				{
					best_size = p1[j].second;
					idx = j;
				}
			}
		}
		if(idx==-1)
		{
			cout<<(i+1)<<" "<<" cannot be allocated memory, External Fragmentation"<<endl;
		}
		else
		{
			p1[idx].first = p2[i];
			arr[idx] = true;
			record[idx] = i + 1;
		}
	}
}

void memory_fixed::worst_fit()
{
	clear();
	int i,j,best_size,idx = -1;
	for(i=0;i<n2;++i)
	{
		best_size = INT_MIN;
		idx = -1;
		for(j=0;j<n1;++j)
		{
			if(p1[j].second>= p2[i] and arr[j]==false)
			{
				if(p1[j].second>best_size)
				{
					best_size = p1[j].second;
					idx = j;
				}
			}
		}
		if(idx==-1)
		{
			cout<<(i+1)<<" "<<" cannot be allocated memory, External Fragmentation"<<endl;
		}
		else
		{
			p1[idx].first = p2[i];
			arr[idx] = true;
			record[idx] = i + 1;
		}
	}
}

int main()
{
	int n1,n2,i;
	cout<<"Enter the number of partitions: ";
	cin>>n1;
	vector <int> v1(n1);
	cout<<"Enter the partition sizes: ";
	for(i=0;i<n1;++i)
	{
		cin>>v1[i];
	}
	cout<<"Enter the number of processes: ";
	cin>>n2;
	vector <int> v2(n2);
	cout<<"Enter the memory requirement of process: ";
	for(i=0;i<n2;++i)
	{
		cin>>v2[i];
	}
	memory_fixed m1(v1,v2);
	cout<<"Fixed Partitioning: First Fit"<<endl;
	m1.first_fit();
	m1.display();
	cout<<"\nFixed Partitioning: Best Fit"<<endl;
	m1.best_fit();
	m1.display();
	cout<<"\nFixed Partitioning: Worst Fit"<<endl;
	m1.worst_fit();
	m1.display();
	return 0;
}
