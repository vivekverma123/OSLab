#include<bits/stdc++.h>

using namespace std;

struct process
{
	int id,at,bt,priority,st,ft,tat,wt;
};	

int main()
{
	int n,i;
	cout<<"Enter the number of processes: ";
	cin>>n;
	process p1[n];
	int remaining[n];
	cout<<"Enter arrival time, burst time and priority :-\n";
	for(i=0;i<n;++i)
	{
		cin>>p1[i].at>>p1[i].bt>>p1[i].priority;
		p1[i].id = i + 1;
		remaining[i] = p1[i].bt;
	}
	int completed = 0,time = 0;
	bool visited[n] = {};
	float avg1 = 0,avg2 = 0;
	int t1 = INT_MAX,t2 = INT_MIN;
	while(completed<n)
	{
		int min1 = INT_MIN,idx = -1;
		for(i=0;i<n;++i)
		{
			if(p1[i].priority > min1 and remaining[i]>0 and p1[i].at <= time)
			{
				min1 = p1[i].priority;
				idx = i;
			}	
			if(p1[i].priority==min1 and remaining[i]>0 and p1[i].at <= time)
			{
				if(p1[idx].at>p1[i].at)
				{
					idx = i;
				}
			}
		}
		if(idx==-1)
		{
			time += 1;
			continue;
		}
		if(visited[idx]==false)
		{
			p1[idx].st = time;
			visited[idx] = true;
		}
		time += 1;
		remaining[idx] -= 1;
		if(remaining[idx]==0)
		{
			completed += 1;
			p1[idx].ft = time;
			p1[idx].tat = p1[idx].ft - p1[idx].at;
			p1[idx].wt = p1[idx].tat - p1[idx].bt;
			avg1 += p1[idx].tat;
			avg2 += p1[idx].wt;
			t1 = min(t1,p1[idx].at);
			t2 = max(t2,p1[idx].ft);
		}
	}
	cout<<"\nID\tAT\tPTY\tBT\tST\tFT\tTAT\tWT\n";
	for(i=0;i<n;++i)
	{
		cout<<p1[i].id<<"\t"<<p1[i].at<<"\t"<<p1[i].priority<<"\t"<<p1[i].bt<<"\t"<<p1[i].st<<"\t"<<p1[i].ft<<"\t"<<p1[i].tat<<"\t"<<p1[i].wt<<"\r"<<endl;
	}
	cout<<"\nAverage turn around time: "<<avg1 / n<<endl;
	cout<<"Average waiting time: "<<avg2 / n<<endl;
	cout<<"Throughput: "<<(float)n / (float)(t2-t1)<<endl;
	return 0;
}
