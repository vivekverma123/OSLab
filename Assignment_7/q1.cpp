#include<bits/stdc++.h>
using namespace std;

int main()
{
	
	int n;
	cout << "Enter the number of processes: ";
	cin >> n;
	int r;
	cout << "Enter the total number of instances present of the resource: ";
	cin >> r;
	vector < vector<int> > safe_sequences;
	vector<int> cur_sequence(n);
	vector<int> allocated(n), maxi(n);
	for(int i = 0; i < n; i++)
	{
		cur_sequence[i] = i;
		cout<<"Enter the no. of resources already allocated to P"<<i<<": ";
		cin>>allocated[i];
	}
	
	for(int i = 0; i < n; i++)
	{
		cout<<"Enter the maximum requirement of P"<<i<<": ";
		cin>>maxi[i];
	}
	while(true)
	{
		int cont = 0; //indicates that current sequence will lead to a deadlock
		vector <int> need(n);
		int available = r;
		for(int i = 0; i < n; i++) 
		{
			available -= allocated[i];
			need[i] = maxi[i] - allocated[i];
		}
		for(int i = 0; i < n; i++)
		{
			if(need[cur_sequence[i]] > available)
			{
				cont = 1;
				break;
			}
			available += allocated[cur_sequence[i]];
		}
		if(cont==0) 
		{	
			safe_sequences.push_back(cur_sequence);
		}
		int flag = next_permutation(cur_sequence.begin(), cur_sequence.end());
		if(!flag) 
		{
			break;
		}
	}
	cout << "\n\nAll the safe sequences are listed below:\n";
	for(int i = 0; i <safe_sequences.size(); i++)
	{
		for(int j = 0; j < n; j++) 
		{
			cout <<"P"<<safe_sequences[i][j]<<" ";
		}
		cout<<"\n";
	}
	cout << "\n\nEnter the sequence you want to check for safe(only index of process): ";
	vector<int> check(n);
	for(int i = 0; i < n; i++) 
	{
		cin >> check[i];
	}
	int yes = 0;
	for(int i = 0; i < safe_sequences.size(); i++)
	{
		int flag = 0;
		for(int j = 0; j < n; j++)
		{
			if(safe_sequences[i][j] != check[j])
			{
				flag = 1;
				break;
			}
		}
		if(flag == 0)
		{
			yes = 1;
			break;
		}
	}
	if(yes) 
	{
		cout <<"Yes, the given sequence is a safe sequence.\n";
	}
	else 
	{
		cout<<"No, the given sequence is not a safe sequence.\n";
	}
	return 0;
}
