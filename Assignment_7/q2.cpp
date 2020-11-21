#include<bits/stdc++.h>
using namespace std;

int main()
{
	
	int n;
	cout<<"Enter the number of processes: ";
	cin>>n;
	int r1, r2;
	cout<<"Enter the total instances of resource 1: ";
	cin>>r1;
	cout<<"Enter the total instances of resource 2: ";
	cin>>r2;
	int allocated[n][2], maxi[n][2];
	for(int i = 0; i < n; i++)
	{
		cout<<"Enter the instance(s) of resource 1 already allocated to P" << i <<": ";
		cin>>allocated[i][0];
		cout<<"Enter the instance(s) of resource 2 already allocated to P" << i <<": ";
		cin>>allocated[i][1];
	}
	
	for(int i = 0; i < n; i++)
	{
		cout<<"Enter the maximum requirement of resource 1 for P"<<i<<": ";
		cin>>maxi[i][0];
		cout<<"Enter the maximum requirement of resource 2 for P"<<i<<": ";
		cin>>maxi[i][1];
	}
	int available1 = r1, available2 = r2;
	for(int i = 0; i < n; i++)
	{
		available1 -= allocated[i][0];
		available2 -= allocated[i][1];
	}
	int need[n][2];
	for(int i = 0; i < n; i++)
	{
		need[i][0] = maxi[i][0] - allocated[i][0];
		need[i][1] = maxi[i][1] - allocated[i][1];
	}
	vector<int> safe_sequence;
	for(int i = 0; i < n; i++)
	{
		int dead_lock = 1;
		for(int j = 0; j < n; j++)
		{
			if(available1 >= need[j][0] && available2 >= need[j][1] && (need[j][0] || need[j][1]))
			{
				dead_lock = 0;
				available1 += allocated[j][0];
				need[j][0] = 0;
				available2 += allocated[j][1];
				need[j][1] = 0;
				cout << "\nAfter completion of process P" << j <<", number of available resource 1 is: "<<available1<<"\n";
				cout << "\nAfter completion of process P" << j <<", number of available resource 2 is: "<<available2<<"\n";
				safe_sequence.push_back(j);
			}
		}
		if(dead_lock) 
		{
			break;
		}
	}
	if(safe_sequence.size() < n) 
	{
		cout << "There is no safe sequence\n";
	}
	else
	{
		cout<<"The safe sequence is: ";
		for(int i = 0; i < n; i++) 
		{
			cout << "P" <<safe_sequence[i]<<" ";
		}
		cout<<"\n";
		cout<<"The last process to be executed is "<<"P"<<safe_sequence[n-1];
	}
	return 0;
}
