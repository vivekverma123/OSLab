#include<bits/stdc++.h>

using namespace std;

struct process
{
	int at,st,ct,tat,bt,wt,id;
	string type;
};

void find(process p1[], int n)
{
	int time = 0, completed = 0;
	int time1[n],i;
	float avg1 = 0, avg2 = 0;
	bool visited[n] = {};
	for(i=0;i<n;++i)
	{
		time1[i] = p1[i].bt;
	}
	while(completed<n)
	{
		int idx = -1,at = INT_MAX;
		for(i=0;i<n;++i)
		{
			if(p1[i].at <= time and time1[i]>0 and p1[i].type=="System" and p1[i].at < at)
			{
				idx = i;
				at = p1[i].at;
			}
		}
		if(idx==-1)
		{
			at = INT_MAX;
			for(i=0;i<n;++i)
			{
				if(p1[i].at <= time and time1[i]>0 and p1[i].type=="User" and p1[i].at < at)
				{
					idx = i;
					at = p1[i].at;
				}
			}
		}
		if(idx!=-1)
		{
			if(visited[idx]==false)
			{
				p1[idx].st = time;
				visited[idx] = true;
			}
			
			time = time + 1;
			time1[idx] -= 1;
			
			if(time1[idx]==0)
			{
				p1[idx].ct = time;
				
				completed = completed + 1;
				
				p1[idx].tat = p1[idx].ct - p1[idx].at;
				p1[idx].wt = p1[idx].tat - p1[idx].bt;
				
				avg1 += p1[idx].tat;
				avg2 += p1[idx].wt;
			}
		}
		else
		{
			time = time + 1;
		}
	}
	cout<<"\nThe task schedule is as follows :-\n";
	cout<<"ID\tAT\tBT\tType\tST\tCT\tWT\tTAT"<<endl;
	for(i=0;i<n;++i)
	{
		cout<<p1[i].id<<"\t"<<p1[i].at<<"\t"<<p1[i].bt<<"\t"<<p1[i].type<<"\t"<<p1[i].st<<"\t"<<p1[i].ct<<"\t"<<p1[i].wt<<"\t"<<p1[i].tat<<endl;
	}
	avg1 = avg1;
	avg2 = avg2;
	cout<<"\nAverage turn around time: "<<avg1 / n<<endl;
	cout<<"Average waiting time: "<<avg2 / n<<endl;
}

int main()
{
	int n,i;
	cout<<"Enter the number of processes: ";
	cin>>n;
	process p1[n];
	cout<<"Enter the id, arrival time and burst time separated by spaces:-"<<endl;
	for(i=0;i<n;++i)
	{
		cin>>p1[i].id>>p1[i].at>>p1[i].bt>>p1[i].type;
	}
	find(p1,n);
	return 0;
}
