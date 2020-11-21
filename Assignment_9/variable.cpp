#include<bits/stdc++.h>

using namespace std;

class memory_variable
{
	private:
		vector <pair<int,int>> p1;
		vector <int> p2;
		bool *arr;
		int n1, n2;
		vector <vector <int>> record;
		
	public:
		memory_variable(vector<int>&,vector<int>&);
		void first_fit();
		void best_fit();
		void worst_fit();
		void clear();
		void display();
};

void memory_variable::clear()
{
	int i,j;
	for(i=0;i<n1;++i)
	{
		p1[i].first = 0;
		arr[i] = false;
		record[i].clear();
	}
}

void memory_variable::display()
{
	int i,j,internal = 0, external = 0;
	cout<<left<<setw(15)<<"Partition"<<left<<setw(15)<<"Fragment Size"<<left<<setw(15)<<"Capacity"<<left<<setw(15)<<"Free Space"<<left<<setw(15)<<"Processes"<<endl;
	for(i=0;i<n1;++i)
	{
	cout<<left<<setw(15)<<i+1<<left<<setw(15)<<p1[i].first<<left<<setw(15)<<p1[i].second<<left<<setw(15)<<p1[i].second - p1[i].first;
		for(j=0;j<record[i].size();++j)
		{
			cout<<record[i][j]<<" ";
		}
		if(record[i].size()==0)
		{
			cout<<"N/A";
		}
		else
		{
			internal += p1[i].second - p1[i].first;
		}
		cout<<endl;
		external += p1[i].second - p1[i].first;
	}
	cout<<"Total internal fragmentation: "<<internal<<endl;
	cout<<"Total external fragmentation: "<<external<<endl;
}	

memory_variable::memory_variable(vector <int> &partitions, vector <int> &processes)
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
		vector <int> temp;
		record.push_back(temp);
	}
}

void memory_variable::first_fit()
{
	clear();
	int i,j,flag = 0;
	for(i=0;i<n2;++i)
	{
		flag = 0;
		for(j=0;j<n1;++j)
		{
			if(p2[i]<=p1[j].second - p1[j].first)
			{
				++flag;
				break;
			}
		}
		if(flag==1)
		{
			p1[j].first += p2[i];
			record[j].push_back(i+1);
		}
		else
		{
			cout<<(i+1)<<" "<<" cannot be allocated memory, External Fragmentation"<<endl;
		}
	}
}

void memory_variable::best_fit()
{
	clear();
	int i,j,best_size,idx = -1;
	for(i=0;i<n2;++i)
	{
		best_size = INT_MAX;
		idx = -1;
		for(j=0;j<n1;++j)
		{
			if(p1[j].second - p1[j].first>= p2[i])
			{
				if(p1[j].second<best_size)
				{
					best_size = p1[j].second - p1[j].first;
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
			p1[idx].first += p2[i];
			record[idx].push_back(i+1);
		}
	}
}

void memory_variable::worst_fit()
{
	clear();
	int i,j,best_size,idx = -1;
	for(i=0;i<n2;++i)
	{
		best_size = INT_MIN;
		idx = -1;
		for(j=0;j<n1;++j)
		{
			if(p1[j].second - p1[j].first>= p2[i])
			{
				if(p1[j].second - p1[j].second >= best_size)
				{
					best_size = p1[j].second - p1[j].second;
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
			p1[idx].first += p2[i];
			record[idx].push_back(i + 1);
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
	memory_variable m1(v1,v2);
	cout<<"Variable Partitioning: First Fit"<<endl;
	m1.first_fit();
	m1.display();
	cout<<"\nVariable Partitioning: Best Fit"<<endl;
	m1.best_fit();
	m1.display();
	cout<<"\nVariable Partitioning: Worst Fit"<<endl;
	m1.worst_fit();
	m1.display();
	return 0;
}
