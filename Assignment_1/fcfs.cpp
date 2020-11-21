#include<bits/stdc++.h>

using namespace std;

struct process
{
	int at,bt,wt,ct,tat;
	string id;
	
	process()
	{
		id = "";
		at = bt = wt = ct = tat = -1;
	}
};

bool compare(process p1, process p2)
{
	if(p1.at==p2.at)
	{
		return p1.id < p2.id;
	}
	return p1.at < p2.at;
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
		cin>>p1[i].id>>p1[i].at>>p1[i].bt;
	}
	sort(p1,p1+n,compare);
	int time = 0;
	float tat_av = 0, wat_avg = 0;
	for(i=0;i<n;++i)
	{
		time += p1[i].bt;
		p1[i].ct = time;
		p1[i].tat = p1[i].ct - p1[i].at;
		p1[i].wt = p1[i].tat - p1[i].bt;
		tat_av += p1[i].tat;
		wat_avg += p1[i].wt;
	}
	cout<<"\nCPU scheduling is as follows :-\n";
	cout<<"PID\tAT\tBT\tCT\tTAT\tWT\n";
	for(i=0;i<n;++i)
	{
		cout<<p1[i].id<<"\t"<<p1[i].at<<"\t"<<p1[i].bt<<"\t"<<p1[i].ct<<"\t"<<p1[i].tat<<"\t"<<p1[i].wt<<endl;
	}
	cout<<endl;
	cout<<"Average turn around time: "<<tat_av / n<<endl;
	cout<<"Average waiting time: "<<wat_avg / n<<endl;
	return 0;
}
