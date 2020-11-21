#include<bits/stdc++.h>

using namespace std;

class deadlock_prevention
{
	private:
		int m,n;	//m processes n types of resources
		vector <int> *allocated,*maximum,*need;
		vector <int> available;		
		
		bool compare(vector <int> &, vector <int> &);
		void add(vector <int>&, vector <int> &);
		
	public:
		bool isSafe(vector <int> &);
		deadlock_prevention(int,int);
		void input();
		bool should_grant(int,vector<int>&);
};

bool deadlock_prevention::compare(vector <int> &v1, vector <int> &v2)
{
	int flag = 0,i;
	for(i=0;i<v1.size();++i)
	{
		if(v1[i]>v2[i])
		{
			return false;
		}
	}
	return true;
}

void deadlock_prevention::add(vector <int> &v1, vector <int> &v2)
{
	int i;
	for(i=0;i<v1.size();++i)
	{
		v1[i] += v2[i];
	}
}

deadlock_prevention::deadlock_prevention(int m, int n)
{
	this -> m = m;
	this -> n = n;
	
	allocated = new vector <int> [m];
	need = new vector <int> [m];
	maximum = new vector <int> [m];
}

void deadlock_prevention::input()
{
	//cout<<"Enter the number of instances available for each resource :-\n";
	int i,temp,j;
	for(i=0;i<n;++i)
	{
		cin>>temp;
		available.push_back(temp);
	}
	//cout<<"\nEnter the allocated matrix :-\n";
	for(i=0;i<m;++i)
	{
		for(j=0;j<n;++j)
		{
			cin>>temp;
			allocated[i].push_back(temp);
		}
	}
	//cout<<"\nEnter the maximum demand matrix :-\n";
	for(i=0;i<m;++i)
	{
		for(j=0;j<n;++j)
		{
			cin>>temp;
			maximum[i].push_back(temp);
			need[i].push_back(maximum[i][j] - allocated[i][j]);
		}
	}
	
	cout<<"\nThe need vector is :-\n";
	for(i=0;i<m;++i)
	{
		for(j=0;j<n;++j)
		{
			cout<<need[i][j]<<" ";
		}
		cout<<endl;
	}
}

void display(vector <int> &v1)
{
	for(int i=0;i<v1.size();++i)
	{
		cout<<v1[i]<<" ";
	}
	cout<<endl;
}

bool deadlock_prevention::isSafe(vector <int> &safe_sequence)
{
	bool finish[m] = {};
	int i,j,flag = 0;
	vector <int> work(available.begin(),available.end());
	do
	{
		flag = 0;
		for(i=0;i<m;++i)
		{
			if(compare(need[i],work)==true and finish[i]==false)
			{
				add(work,allocated[i]);
				finish[i] = true;
				safe_sequence.push_back(i);
				++flag;
			}
			else
			{
			}
		}
		
	}while(flag!=0);
	flag = 0;
	for(i=0;i<m;++i)
	{
		if(finish[i]==false)
		{
			++flag;
		}
	}
	if(flag==0)
	{	
		cout<<"A safe sequence exists!"<<endl;
		return 1;
	}
	else
	{
		cout<<"A safe sequence doesn't exist!"<<endl;
		return 0;
	}
}

bool deadlock_prevention::should_grant(int i, vector <int> &v1)
{
	//if request actually granted
	int j;
	for(j=0;j<n;++j)
	{
		allocated[i][j] += v1[j];
		need[i][j] -= v1[j];
	}
	vector <int> safe_sequence;
	if(compare(v1,available)==false)
	{
		return 0;
	}
	if(isSafe(safe_sequence)==false)
	{
		for(j=0;j<n;++j)
		{
			allocated[i][j] -= v1[j];
			need[i][j] += v1[j];
		}
		return 0;
	}
	else
	{	
		for(j=0;j<safe_sequence.size();++j)
		{
			cout<<safe_sequence[j]<<" ";
		}
		cout<<endl;
		for(j=0;j<n;++j)
		{
			allocated[i][j] -= v1[j];
			need[i][j] += v1[j];
		}
		return 1;
	}
}

int main()
{
	vector <int> safe_sequence;
	deadlock_prevention d1(5,3);
	d1.input();
	vector <int> v1 = {1,0,2};
	if(d1.should_grant(0,v1)==true)
	{
		cout<<"Granted"<<endl;
	}	
	else
	{
		cout<<"Denied"<<endl;
	}
	return 0;
}
