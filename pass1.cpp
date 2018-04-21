#include<bits/stdc++.h>
using namespace std;

struct optab
{
	string operation;
	string opcode;
	string cls;
}optab[20];

struct littab
{
	int index;
	int address;
	int pool;
	string value;
}littab[10];

struct symtab
{
	int index;
	int address;
	string symbol;
	
}symtab[20];

struct regtab
{
	string regis_type;
	int index;
}reg[6];

struct compare //comparison statements
{
	string compare_type;
	int index;
}compare[7];

int present_in_compare(string v)
{
	for(int i=1;i<7;i++)
	{
		if(v==compare[i].compare_type)
			return i;
	}
		return 0;
}

int is_assembly_directive(vector<string> v)
{
	for(int i=0;i<v.size();i++)
	{
		if(v[i]=="START"||v[i]=="END"||v[i]=="EQU"||v[i]=="LTORG"||v[i]=="ORIGIN")
			return 1;
		 
	}	
	return 0;
}

int present_in_optab(string v)
{
	
	for(int i=1;i<18;i++)
	{
		if(v==optab[i].operation)
			return i;
	}
		return 0;
}
int present_in_regtab(string v)
{
	for(int i=1;i<5;i++)
	{
		if(v==reg[i].regis_type)
			return i;
	}
		return 0;
}
int present_in_symtab(string s,int count)
{
	int i;
	for(i=1;i<count;i++)
	{
		if(s==symtab[i].symbol)
			return i;
	}
	return 0;
}
int present_in_littab(string s,int n,int cpool)
{
	for(int i=1;i<n;i++)
		if(littab[i].value==s && littab[i].pool==cpool)
			return i;
	return 0;
}
int stoi_ds(string s)
{
	int ans=0;
	ans=s[0]-'0';
	return ans;
}
void symbol_print(int n)
{
	for(int i=1;i<n;i++)
		cout<<symtab[i].index<<" "<<symtab[i].symbol<<" "<<symtab[i].address<<endl;
}

void literal_print(int n)
{
	for(int i=1;i<n;i++)
		cout<<littab[i].index<<" "<<littab[i].value<<" "<<littab[i].address<<" "<<littab[i].pool<<endl;
}

int main()
{

	freopen("mot_table_.txt","r",stdin);
	freopen("pass1_output.txt","w",stdout);
	
	int i;
	
	for(i=1;i<18;i++)
		cin>>optab[i].operation>>optab[i].opcode>>optab[i].cls;
	for(i=1;i<5;i++)
		cin>>reg[i].regis_type>>reg[i].index;
	for(i=1;i<7;i++)
		cin>>compare[i].compare_type>>compare[i].index;
		
	
		
	cin.clear();
	
	freopen("pass1_input.txt","r",stdin);
	
	string each_line;
	int location_counter=0,index,symbol_count=1,literal_count=1,current_pool=1,left,right;
	
	while(getline(cin,each_line))
	{	
		vector<string>v;
		
		istringstream abc(each_line);
		
		copy(istream_iterator<string>(abc),istream_iterator<string>(),back_inserter(v));
	
		if(!is_assembly_directive(v))
		cout<<++location_counter<<" ";
		
		for(i=0;i<v.size();i++)
		{	
		
			if(v[i]!=",")
			{
				index=present_in_optab(v[i]);
				
				if(!index)   					//if it is present then will return i which is > than 0 ands not enter the if
				{
					index=present_in_regtab(v[i]);
					if(!index)
					{
						index=present_in_compare(v[i]);
						if(!index)
						{
							index=present_in_symtab(v[i],symbol_count);
							if(!index && isalpha(v[i][0]) && (i==0 || i==v.size()-1 ))
							{
								symtab[symbol_count].index=symbol_count;
								symtab[symbol_count].symbol=v[i];
								if(i==0)
								symtab[symbol_count].address=location_counter;
								else
								symtab[symbol_count].address=-1;
								symbol_count++;
							}
							index=present_in_littab(v[i],literal_count,current_pool);
							if(!index && v[i][0]=='=')
							{
								littab[literal_count].index=literal_count;
								littab[literal_count].value=v[i];
								littab[literal_count].address=-1;
								littab[literal_count].pool=current_pool;
								literal_count++;
							}
						}
						else
							cout<<" "<<compare[index].compare_type;
					}
					else
						cout<<" "<<reg[index].index<<" ";
				}	
				else
					cout<<"("<<optab[index].cls<<","<<optab[index].opcode<<")";
					
				if(i>0 && v[i-1]=="START" && isdigit(v[i][0]))
				{
					cout<<" "<<"(C,"<<v[i]<<") ";
					location_counter=stoi(v[i])-1;
				}
				if(v[i]=="LTORG" || v[i]=="END")
				{
					for(int j=1;j<literal_count;j++)
					{
						if(littab[j].address==-1)
							littab[j].address=++location_counter;
						
						current_pool++;
					}
				}
				index=present_in_symtab(v[i],symbol_count);
				if(index)
				{
					if(i==0)
						symtab[index].address=location_counter;
					else
						cout<<" "<<"(S,"<<symtab[index].index<<") ";
				}
				index=present_in_littab(v[i],literal_count,current_pool);
				if(index)
					cout<<"(L,"<<littab[index].index<<") ";
					
				if(i>0 && v[i-1]=="DC" && isdigit(v[i][1]))
					cout<<" "<<"(C,"<<v[i]<<") ";
				if(i>0 && v[i-1]=="DS" && isdigit(v[i][0]))
				{
					cout<<" "<<"(C,"<<v[i]<<") ";
					location_counter+=stoi_ds(v[i])-1;
				}
				if(v[i]=="EQU")
				{
					left=present_in_symtab(v[i-1],symbol_count);
					right=present_in_symtab(v[i+1],symbol_count);
					if(left && right)
						symtab[left].address=symtab[right].address;
				}
				
			} 
				
					
			}
			cout<<"\n";
		}

	cout.clear();
	freopen("table_output.txt","w",stdout);
	cout<<"***SYMBOL TABLE***"<<endl;
	cout<<"Index Symbol Address"<<endl;
	for(i=1;i<symbol_count;i++)
		cout<<symtab[i].index<<"\t\t"<<symtab[i].symbol<<"\t\t"<<symtab[i].address<<endl;
	cout<<"\n----LITERAL TABLE----"<<endl;
	cout<<"Index Value Address Pooltab"<<endl;
	for(i=1;i<literal_count;i++)
		cout<<littab[i].index<<"\t\t"<<littab[i].value<<"\t"<<littab[i].address<<"\t\t"<<littab[i].pool<<endl;

	cin.clear();
	cout.clear();
	freopen("pass2_input.txt","w",stdout);
	symbol_print(symbol_count);
	cout<<"-1 NULL -1"<<endl;
	literal_print(literal_count);
	cout<<"-1 NULL -1 -1"<<endl;

	return 0;

}
