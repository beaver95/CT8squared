#include"Chess_tournament_64.h"
#include"Date.h"

char* Name[]=   {"Oleg","Andriy","Volodymyr","Pavlo","Igor","Mark"};
char* Surname[]={"Ivanov    1","Leonidov  2","Son'ko    3","Osypov    4","Yakovenko 5","Sarnavsky 6"};

#include<iostream>

using namespace std;

int WatchTourn(Round_Robin_Tournament& T)
{
	system("cls");
	cout<<"Tourn number "<<T.getCurrentTourn()<<"\n # White          Black          Result\n";
	int pointer=0;
	vector<vector<Match>::iterator> V(T.getTourn(T.getCurrentTourn()));
	for(vector<vector<Match>::iterator>::iterator j=V.begin(); j<V.end(); ++j)
		(++pointer>0 ? cout<<'0'<<pointer<<' '<<(**j)<<endl : cout<<pointer<<' '<<(**j)<<endl);
	cout<<endl;
	int max_tourn=pointer;
	if(V.size()==0)
		return 0;
	pointer=-1;
	cout<<"1.Add result\n0.Back\n";
	while(pointer<0||pointer>5)
		cin>>pointer;
	switch(pointer)
	{
	case 1:
		{
			cout<<"Enter match number\n*0-exit\n";
			cin>>pointer;
			if(pointer<=0||pointer>max_tourn)
				break;
			int res=0;
			while (res<1||res>6)
			{
				cout<<"1.\"1:0\"\n2.\"1/2\"\n3.\"0:1\"\n4.\"+ -\"\n5.\" = \"\n6.\"- +\"\n";
				cin>>res;
			}
			V[pointer-1]->setResult(res-1);
			break;
		}
	}
	return pointer;
}

int startProgram(Round_Robin_Tournament& T)
{
	system("cls");
	int pointer=-1;
	cout<<"1.Add player\n2.Player num\n3.Start tournament\n4.Watch tourn\n5.Next tourn\n6.Show table\n0.Exit\n";
	while(pointer<0||pointer>6)
		cin>>pointer;
	switch(pointer)
	{
	case 1:
		{
			if(T.getCurrentTourn()!=0)
			{
				cout<<"Tournament started\n";
				break;
			}
			cout<<"Enter name, surname, day, month, year:\n";
			string N, S;
			int D, M, Y;
			cin>>N>>S>>D>>M>>Y;
			if(T.addPlayer(Player(Chess_Player(N,S,1,1,1990,0,7), (Tournament*)&T, T.getCurrentTourn())))
				cout<<"Ok!\n";
			else
				cout<<"No!\n";
			break;
		}
	case 2:
		{
			cout<<T.getNumberOfPlayers()<<endl;
			break;
			int id;
			cout<<"Enter ID";
			cin>>id;
			T.delPlayer(id);
			break;
		}
	case 3:
		{
			if(T.startTournament())
				cout<<"Success!\n";
			else
				cout<<"Don't started\n";
			break;
		}
	case 4:
		{
			if(T.getCurrentTourn()==0)
			{
				cout<<"Tournament wasn't started\n";
				break;
			}
			else if(T.getCurrentTourn()>T.getNumberOfTourns())
			{
				cout<<"Tournament is over\n";
				break;
			}
			while(WatchTourn(T)!=0);
			break;
		}
	case 5:
		{
			if(T.NextTourn())
				cout<<"Ok!\n";
			else
				cout<<"No!\n";
			break;
		}
	case 6:
		{
			system("cls");
			if(T.getCurrentTourn()==0)
			{
				cout<<"Tournament wasn't started\n";
				break;
			}
			cout<<"Tournament table after "<<T.getCurrentTourn()-1<<" tourn\n";
			cout<<" # Name           Surname        Title Birthday Points Berger\n";
			vector<Player> V=T.getTable(T.getCurrentTourn());
			for(int i=0; i<T.getNumberOfPlayers(); ++i)
				(i>8 ? cout<<i+1<<' '<<V[i]<<endl : cout<<'0'<<i+1<<' '<<V[i]<<endl);
			break;
		}
	}
	system("pause");
	return pointer;
}

int main()
{
	/*/
	Round_Robin_Tournament T("Open Championship");
	for(int i=0; i<6; ++i)
		T.addPlayer(Player(Chess_Player(Name[i],Surname[i],1,1,1990,0,1),(Tournament*)&T));
	T.startTournament();
	for(int i=1; i<=T.getNumberOfTourns(); ++i)
	{
		vector<vector<Match>::iterator> V(T.getTourn(i));
		for(vector<vector<Match>::iterator>::iterator j=V.begin(); j<V.end(); ++j)
			cout<<(**j)<<endl;
		cout<<endl;
	}
	/*/
	Round_Robin_Tournament T("Open Championship");
	while(startProgram(T)!=0);	
	return 0;
}