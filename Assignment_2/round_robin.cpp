#include<bits/stdc++.h>

using namespace std;

struct process
{
	int at,bt,tat,wt,ct,rt,id;
	process()
	{
		at = bt = tat = wt = ct = rt = id;
	}	
};

void update_queue(queue <int> &q1, process p1[], int time, int n, bool pushed[])
{
	int i;
	for(i=0;i<n;++i)
	{
		if(p1[i].at<=time and pushed[i]==false)
		{
			q1.push(p1[i].id);
			pushed[i] = true;
		}
	}
}

void round_robin(process p1[], int n, int q, float &avg1, float &avg2)
{
	avg1 = 0, avg2 = 0;
	int time1 = 0,completed = 0;
	queue <int> ready;
	int rem[n],i,j;
	bool pushed[n] = {}, visited[n] = {};
	for(i=0;i<n;++i)
	{
		rem[i] = p1[i].bt;
	}
	update_queue(ready,p1,time1,n,pushed);
	while(completed<n)
	{
		if(ready.empty()==false)
		{
			int temp = ready.front();
			ready.pop();
			if(visited[temp]==false)
			{
				visited[temp] = true;
				p1[temp].rt = time1;
			}
			if(rem[temp]<=q)
			{	
				//updating time variable
				time1 = time1 + rem[temp];
				//assigning completion time
				p1[temp].ct = time1;
				//updating remaining time
				rem[temp] = 0;
				//computing turn around time
				p1[temp].tat = p1[temp].ct - p1[temp].at;
				//computing waiting time
				p1[temp].wt = p1[temp].tat - p1[temp].bt;
				//updatint complete variable
				completed = completed + 1;
				//computing the averages
				avg1 += p1[temp].tat;
				avg2 += p1[temp].wt;
				//updating ready queue
				update_queue(ready,p1,time1,n,pushed);
			}
			else
			{
				//updating remaning time
				rem[temp] = rem[temp] - q;
				//updating time variable
				time1 = time1 + q;
				update_queue(ready,p1,time1,n,pushed);
				ready.push(temp);
			}
		}	
		else
		{
			time1 += q;
			update_queue(ready,p1,time1,n,pushed);	
		}
	}
	avg1 /= n;
	avg2 /= n;
	cout<<"Time quantum: "<<q<<endl;
	cout<<"ID\tAT\tBT\tST\tFT\tTAT\tWT\n";
	for(i=0;i<n;++i)
	{			cout<<p1[i].id<<"\t"<<p1[i].at<<"\t"<<p1[i].bt<<"\t"<<p1[i].rt<<"\t"<<p1[i].ct<<"\t"<<p1[i].tat<<"\t"<<p1[i].wt<<"\r"<<endl;
	}
	cout<<"Average Turn Around Time: "<<avg1<<endl;
	cout<<"Aversge Waiting Time: "<<avg2<<endl;
	int t1,t2;
	t1 = INT_MAX;
	t2 = INT_MIN;
	for(i=0;i<n;++i)
	{
		t1 = min(p1[i].at,t1);
		t2 = min(p1[i].ct,t2);
	}
	cout<<"Throughput: "<<n / (t2 - t1)<<endl;
}

int main()
{
	int n,q1,q2,i;
	cout<<"Enter the number of processes followed by 2 time quantums: ";
	cin>>n>>q1>>q2;
	process p1[n];
	cout<<"Enter the arrival time and burst time for each process: "<<endl;
	for(i=0;i<n;++i)
	{
		p1[i].id = i;
		cin>>p1[i].at>>p1[i].bt;
	}
	float a,b,c,d;
	round_robin(p1,n,q1,a,b);
	round_robin(p1,n,q2,c,d);
	cout<<"The differences are :-\n";
	cout<<"Average turn around time: "<<abs(c-a)<<endl;
	cout<<"Average turn around time: "<<abs(d-b)<<endl;
	return 0;
}
