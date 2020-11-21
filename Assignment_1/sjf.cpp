#include<bits/stdc++.h>

using namespace std;

struct job
{
	int at, bt, st, ct, tat, wt;
	string id;
};

void non_preemptive(job j1[], float &avg1, float &avg2, int n)
{
	avg1 = 0;
	avg2 = 0;
	int rem[n],i;
	for(i=0;i<n;++i)
	{
		rem[i] = j1[i].bt;
	}
	int completed = 0,time = 0;
	while(completed<n)
	{
		int min_time = INT_MAX,min_index = -1;
		for(i=0;i<n;++i)
		{
			if(j1[i].at<=time and rem[i]>0 and rem[i]<min_time)
			{
				min_time = rem[i];
				min_index = i;
			}
		}
		if(min_index==-1)
		{
			time = time + 1;
			continue;
		}
		j1[min_index].st = time;
		j1[min_index].ct = time + j1[min_index].bt;
		rem[min_index] = 0;
		
		time = time + j1[min_index].bt;
		
		min_time = rem[min_index];

		completed += 1;
		min_time = INT_MAX;
			
		j1[min_index].tat = j1[min_index].ct - j1[min_index].at;
		j1[min_index].wt = j1[min_index].tat - j1[min_index].bt;
			
		avg1 += j1[min_index].tat;
		avg2 += j1[min_index].wt;
		
		//time = time + 1;
	}
	avg1 = avg1 / n;
	avg2 = avg2 / n;
	cout<<"ID\tAT\tBT\tST\tCT\tWT\tTAT"<<endl;
	for(i=0;i<n;++i)
	{
		cout<<j1[i].id<<"\t"<<j1[i].at<<"\t"<<j1[i].bt<<"\t"<<j1[i].st<<"\t"<<j1[i].ct<<"\t"<<j1[i].wt<<"\t"<<j1[i].tat<<endl;
	}
}

int main()
{
	int n,i;
	cout<<"Enter the number of processes: ";
	cin>>n;
	job j1[n];
	cout<<"Enter the id, arrival time and burst time separated by spaces:-"<<endl;
	for(i=0;i<n;++i)
	{
		cin>>j1[i].id>>j1[i].at>>j1[i].bt;
	}
	float avg1,avg2;
	cout<<"\nThe job schedule is as follows :-\n";
	non_preemptive(j1,avg1,avg2,n);
	cout<<"Average turn around time: "<<avg1<<endl;
	cout<<"Average waiting time: "<<avg2<<endl;
	return 0;	
}
