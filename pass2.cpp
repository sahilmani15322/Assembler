#include<bits/stdc++.h>
using namespace std;

struct symtab		
{
	int index;
	string symbol;
	int address;
}symtab[50];
struct littab		
{
	int index;
	string value; 
	int address;
	int pool;
}littab[50];
void initialize()
{
	int i;
	int count=0;
	for(i=1;;i++)
	{
		cin>>symtab[i].index>>symtab[i].symbol>>symtab[i].address;
		if(symtab[i].index==-1)
			break;
	}
	for(i=1;;i++)
	{
		cin>>littab[i].index>>littab[i].value>>littab[i].address>>littab[i].pool;
		count++;
		if(littab[i].index==-1)
			break;
	}
}
int main()
{
	int count=1;
	freopen("pass2_input.txt","r+",stdin);
	initialize();
	cin.clear();
	freopen("pass1_output.txt","r+",stdin);
	freopen("pass2_output.txt","w",stdout);
	string read_each_line;
	int index,i;
	while(getline(cin,read_each_line))
	{	
		vector<string>v;
		int i;
		istringstream abc(read_each_line);
		copy(istream_iterator<string>(abc),istream_iterator<string>(),back_inserter(v));
		if(v.size()==1)
		{
			
			for(int j=count;;j++)
			{
				if(count!=littab[j].pool)
				{
					count=littab[j].pool;
					break;
				}	
				cout<<" "<<littab[j].address<<endl;
				
			}continue;
		}
		
		for(i=0;i<v.size();i++)
		{
			if(isdigit(v[i][0]))
				cout<<" "<<v[i];
			else if(v[i][1]=='D' || v[i][1]=='I')
				cout<<" "<<v[i][4]<<v[i][5];
			else if(v[i][1]=='L')
				{
					index=v[i][3]-'0';
					cout<<" "<<littab[index].address;
				}
			else if(v[i][1]=='S')
				{
					index=v[i][3]-'0';
					cout<<" "<<symtab[index].address;
				}
			
		}cout<<"\n";
	}
		
}

