#pragma once

#include<iostream>
#include<String>
#include<vector>
#include<map>
#include<algorithm>
#include<functional>
#include<ctime>
#include"Date.h"

using namespace std;

class Human;
class Chess_Player;
class Player;
class Arbiter;
class Match;
class Tournament;
class Round_Robin_Tournament;

class Match
{
public:
	Match(int tourn, int white_id, int black_id, int result, const Tournament* tournament)
	{
		Tourn=tourn;
		WhiteID=white_id;
		BlackID=black_id;
		Result=result;
		My_T=tournament;
	}
	int getTourn() const
	{
		return Tourn;
	}
	int getWhite() const
	{
		return WhiteID;
	}
	int getBlack() const
	{
		return BlackID;
	}
	int getResult(int WorB) const
	{
		if(Result==6)
			return 2;
		if(Result==7)
			return 0;
		return 2*WorB-Result%3;
	}
	int getOponentID(int WorB) const
	{
		if(WorB==1)
			return BlackID;
		return WhiteID;
	}
	bool setResult(int result)
	{
		if(result>7||result<0)
			return false;
		Result=result;
		return true;
	}
	bool setResult(const string& result)
	{
		bool flag=true;
		for(int i=0; i<8&&flag; ++i)
			if(result==Res_List[i])
			{
				flag=false;
				Result=i;
			}
		return !flag;
	}
	bool wasPlayed()
	{
		return (Result!=8);
	}
	friend ostream& operator<< (ostream& out, const Match& object);
private:
	int Tourn;
	int WhiteID;
	int BlackID;
	int Result;
	const Tournament* My_T;
	static char Res_List_S[];
	static string Res_List[];
};

class Human
{
protected:
	Human()
	{
		Name="N.";
		Surname="N.";
		Birthday.set(1,1,2000);
	}
	Human(const string &name, const string &surname, const int day, const int month, const int year)
	{
		Name=name;
		Surname=surname;
		Birthday.set(day, month, year);
	}
	Human(const Human& object)
	{
		Name=object.Name;
		Surname=object.Surname;
		Birthday=object.Birthday;
	}
	string getName() const
	{
		return Name;
	}
	string getSurname() const
	{
		return Surname;
	}
	Date getDate() const
	{
		return Birthday;
	}
	string Name;
	string Surname;
	Date Birthday;
};

class Chess_Player:protected Human
{
public:
	Chess_Player(const Human& object, int rating, int title):Human(object)
	{
		Rating=rating;
		Title=title;
	}
	Chess_Player(const string& name, const string& surname, const int day, const int month, const int year, int rating, int title):Human(name, surname, day, month, year)
	{
		Rating=rating;
		Title=title;
	}
	Chess_Player(const Chess_Player& object):Human(object)
	{
		Rating=object.Rating;
		Title=object.Title;
	}
	int getRating() const
	{
		return Rating;
	}
	int getTitle() const
	{
		return Title;
	}
	const string& getTitle_S() const
	{
		return Title_List_S[Title];
	}
	const string& Title_S(int num) const
	{
		return Title_List_S[num];
	}
	const string& getTitle_F() const
	{
		return Title_List[Title];
	}
	const string& Title_F(int num) const
	{
		return Title_List[num];
	}
	friend ostream& operator<< (ostream& out, const Chess_Player& object)
	{
		out<<object.getName()<<' '<<object.getSurname()<<' '<<object.Title_List_S[object.Title]<<' '<<object.Rating<<' '<<object.getDate();
		return out;
	}
	string getName() const
	{
		return Name;
	}
	string getSurname() const
	{
		return Surname;
	}
	Date getDate() const
	{
		return Birthday;
	}
protected:
	Chess_Player():Human()
	{
		Rating=0;
		Title=7;
	}
	static string Title_List[];
	static string Title_List_S[];
	int Rating;
	int Title;
};


class Player:protected Chess_Player
{
public:
	Player():Chess_Player()
	{
		ID=Points=Progress=Bukholz=Berger=Color=0;
		Play=false;
	}
	Player(const Chess_Player& object, const Tournament* tournament, int tourn=0):Chess_Player(object)
	{
		ID=++IDP;
		Points=tourn;
		Progress=tourn*(tourn+1)/2;
		Bukholz=Berger=tourn*tourn;
		Color=0;
		My_T=tournament;
		Play=true;
	}
	Player(const Player& object):Chess_Player(object)
	{
		ID=object.ID;
		Points=object.Points;
		Progress=object.Progress;
		Bukholz=object.Bukholz;
		Berger=object.Berger;
		Color=object.Color;
		Play=object.Play;
		My_T=object.My_T;
		Match_List=object.Match_List;
	}
	bool addMatch(const vector<Match>::const_iterator& iter, const Tournament* key)
	{
		if(My_T!=key)
			return false;
		Match_List.push_back(iter);
		if(iter->getWhite()==ID)
			Color+=1;
		else
			Color-=1;
		return true;
	}
	string getName() const
	{
		return Name;
	}
	string getSurname() const
	{
		return Surname;
	}
	Date getDate() const
	{
		return Birthday;
	}
	int getID() const
	{
		return ID;
	}
	void setPlay(bool play)
	{
		Play=play;
	}
	int getPoints() const
	{
		return Points;
	}
	int getColor() const
	{
		if(Color>1)
			return 1;
		//Must play black
		if(Color<-1)
			return -1;
		//Must play white
		return 0;
	}
	void updateResult(int Tourn);
	void updateKoef(int Tourn);
	friend bool operator==(const Player& object1, const Player& object2)
	{
		return object1.ID==object2.ID;
	}
	friend bool operator==(const Player& object1, int id)
	{
		return object1.ID==id;
	}
	friend int comp(const Player& _Left, const Player& _Right)
	{
		if((_Left.Points)<(_Right.Points))
			return 0;
		if((_Left.Points)>(_Right.Points))
			return 1;
		if((_Left.Bukholz)<(_Right.Bukholz))
			return 0;
		if((_Left.Bukholz)>(_Right.Bukholz))
			return 1;
		if((_Left.Berger)<(_Right.Berger))
			return 0;
		if((_Left.Berger)>(_Right.Berger))
			return 1;
		if((_Left.Progress)<(_Right.Progress))
			return 0;
		if((_Left.Progress)>(_Right.Progress))
			return 1;
		return 0;
	}
	friend ostream& operator<< (ostream& out, const Player& object)
	{
		out.width(14);
		out.setf(ios::left);
		out<<object.getName()<<' ';
		out.width(14);
		out.setf(ios::left);
		out<<object.getSurname()<<' '<<object.Title_List_S[object.Title]<<' '<<object.getDate()<<' ';
		out.width(4);
		out<<(double)object.Points/2<<' ';
		out.width(6);
		out<<(double)object.Berger/4;
		return out;
	}
private:
	int ID;
	int Points;
	int Progress;
	int Bukholz;
	int Berger;
	int Color;
	bool Play;
	const Tournament* My_T;
	vector<vector<Match>::const_iterator> Match_List;
	static int IDP;
};
class Arbiter:protected Human
{
};

class Tournament
{
public:
	void addPlayer(const Player& player)
	{
		T_Players.insert(pair<int, Player>((player.getID()), player));
	}
	void delPlayer(int ID)
	{
		T_Players[ID].setPlay(false);
	}
	const Player& getPlayer(int id) const
	{
		return (T_Players.find(id))->second;
	}
	Tournament(const string& name)
	{
		Name=name;
	}
	Tournament(const Tournament& object)
	{
		Name=object.Name;
		T_Players=object.T_Players;
		T_Matches=object.T_Matches;
	}
	int getNumberOfPlayers()
	{
		return T_Players.size();
	}
	vector<vector<Match>::iterator> getTourn(int tourn)
	{
		vector<vector<Match>::iterator> T_Tourns;
		for(vector<Match>::iterator i=T_Matches.begin(); i<T_Matches.end(); ++i)
			if(i->getTourn()==tourn)
				T_Tourns.push_back(i);
		return T_Tourns;
	}
protected:
	virtual bool makeNextTourn(){return false;}
	virtual bool startTournament(){return false;}
	virtual int getNumberOfTourns(){return 0;}
	virtual vector<Player> getTable(int Tourn){return vector<Player>();}
	string Name;
	map<int, Player> T_Players;
	vector<Match> T_Matches;
};

class Round_Robin_Tournament:public Tournament
{
public:
	Round_Robin_Tournament(const string& name):Tournament(name)
	{
		CurrentTourn=0;
	}
	Round_Robin_Tournament(const Round_Robin_Tournament& object):Tournament(object.Name)
	{
		T_Matches=object.T_Matches;
		T_Players=object.T_Players;
		CurrentTourn=object.CurrentTourn;
	}
	bool startTournament()
	{
		int size=T_Players.size();
		if(size<3||CurrentTourn>0)
			return false;
		if(size%2==0)
		{
			int **arr=new int*[T_Players.size()];
			for(int i=0; i<size; ++i)
				arr[i]=new int[T_Players.size()];
			makeCalendar(arr, size);
			for(int Cur_Tourn_Gen=1; Cur_Tourn_Gen<size; ++Cur_Tourn_Gen)
			{
				for(int player1=1; player1<=size; ++player1)
				{
					int player2=arr[Cur_Tourn_Gen-1][player1-1];
					if(player1<player2)
					{
						if(T_Players[player1].getColor()==1||T_Players[player2].getColor()==-1)
							T_Matches.push_back(Match(Cur_Tourn_Gen, player2, player1, 8, this));
						else
							T_Matches.push_back(Match(Cur_Tourn_Gen, player1, player2, 8, this));
					}
				}
			}
			for(vector<Match>::iterator i=T_Matches.begin(); i<T_Matches.end(); ++i)
			{
				T_Players[i->getWhite()].addMatch(i, this);
				T_Players[i->getBlack()].addMatch(i, this);
			}
			for(int i=0; i<size; ++i)
				delete []arr[i];
			delete []arr;
		}
		else
		{
			for(int Cur_Tourn_Gen=1; Cur_Tourn_Gen<=size; ++Cur_Tourn_Gen)
			{
				for(int player1=1; player1<=size; ++player1)
				{
					int player2=(Cur_Tourn_Gen-player1+size)%size+1;
					if(player1<player2)
					{
						if(T_Players[player1].getColor()==1||T_Players[player2].getColor()==-1)
							T_Matches.push_back(Match(Cur_Tourn_Gen, player2, player1, 8, this));
						else
							T_Matches.push_back(Match(Cur_Tourn_Gen, player1, player2, 8, this));
					}
				}
			}
			for(vector<Match>::iterator i=T_Matches.begin(); i<T_Matches.end(); ++i)
			{
				T_Players[i->getWhite()].addMatch(i, this);
				T_Players[i->getBlack()].addMatch(i, this);
			}
		}
		CurrentTourn=1;
		return true;
	}
	bool addPlayer(const Player& player)
	{
		if(CurrentTourn!=0)
			return false;
		T_Players.insert(pair<int, Player>((player.getID()), player));
		return true;
	}
	void delPlayer(int ID)
	{
		T_Players[ID].setPlay(false);
	}
	const Player& getPlayer(int id) const
	{
		return (T_Players.find(id))->second;
	}
	int getNumberOfTourns()
	{
		if(CurrentTourn!=0)
			return T_Players.size()-1+T_Players.size()%2;
		return 0;
	}
	bool NextTourn()
	{
		if(CurrentTourn==0||CurrentTourn>this->getNumberOfTourns())
			return false;
		bool flag=true;
		vector<vector<Match>::iterator> V(this->getTourn(CurrentTourn));
		for(vector<vector<Match>::iterator>::iterator j=V.begin(); j<V.end()&&flag; ++j)
			flag=(*j)->wasPlayed();
		if(flag)
		{
			for(int i=1; i<=(int)T_Players.size(); ++i)
				T_Players[i].updateResult(CurrentTourn);
			for(int i=1; i<=(int)T_Players.size(); ++i)
				T_Players[i].updateKoef(CurrentTourn);
			++CurrentTourn;
		}
		return flag;
	}
	int getCurrentTourn()
	{
		return CurrentTourn;
	}
	vector<vector<Match>::iterator> getTourn(int tourn)
	{
		vector<vector<Match>::iterator> T_Tourns;
		for(vector<Match>::iterator i=T_Matches.begin(); i<T_Matches.end(); ++i)
			if(i->getTourn()==tourn)
				T_Tourns.push_back(i);
		return T_Tourns;
	}
	vector<Player> getTable(int Tourn)
	{
		vector<Player> Table;
		for(int i=1; i<=(int)T_Players.size(); ++i)
			Table.push_back(T_Players[i]);
		sort(Table.begin(), Table.end(), comp);
		return Table;
	}
private:
	void generate(int** adr, int& N, bool** matrix, bool* line, int k=0, int p=0, int x=0)
	{
		static bool flag=true;
		if(x==N-1)
		{
			flag=false;
			return;
		}
		if(k==N&&p==N/2)
		{
			for(int i=0; i<N; ++i)
				line[i]=true;
			generate(adr, N, matrix, line, 0, 0, x+1);
			for(int i=0; i<N; ++i)
				line[i]=false;
		}
		else if (k<N)
		{
			for(int i=0; i<N; ++i)
			{
				if(line[k]&&line[i]&&matrix[i][k]&&matrix[k][i]&&k!=i&&flag)
				{
					adr[x][k]=i+1;
					adr[x][i]=k+1;
					line[i]=false;
					line[k]=false;
					matrix[i][k]=false;
					matrix[k][i]=false;
					generate(adr, N, matrix, line, k+1, p+1, x);
					matrix[i][k]=true;
					matrix[k][i]=true;
					line[i]=true;
					line[k]=true;
				}
			}
			generate(adr, N, matrix, line, k+1, p, x);
		}
	}
	void makeCalendar(int** out, int N)
	{
		bool **arr=new bool*[N];
		for(int i=0; i<N; ++i)
			arr[i]=new bool[N];
		for(int i=0; i<N; ++i)
			for(int j=0; j<N; ++j)
				arr[i][j]=true;
		bool* arr1=new bool[N];
		for(int i=0; i<N; ++i)
				arr1[i]=true;
		generate(out, N, arr, arr1);
		delete arr1;
		for(int i=0; i<N; ++i)
			delete []arr[i];
		delete []arr;
	}
	int CurrentTourn;
};

char Match::Res_List_S[]={'1','S','0','+','=','-'};
int Player::IDP=0;
string Match::Res_List[]={"1:0","1/2","0:1","+:-"," = ","-:+"," + "," - ","N/A"};
string Chess_Player::Title_List[]={"Grandmaster","International Master","FIDE Master","Candidate Master","1st Category","2nd Category","3rd Category","4th Category"};
string Chess_Player::Title_List_S[]={"g","m","f","cm","1","2","3","4"};

void Player::updateKoef(int Tourn)
{
	int ptr=0;
	Progress=Bukholz=Berger=0;
	for(vector<vector<Match>::const_iterator>::iterator i=Match_List.begin(); (ptr<Tourn)&&(i<Match_List.end()); ++i)
	{
		++ptr;
		int worb=0;
		if((*i)->getWhite()==ID)
			worb=1;
		Progress+=Points;
		Bukholz+=abs(My_T->getPlayer((**i).getOponentID(worb)).getPoints());
		Berger+=abs((**i).getResult(worb)*My_T->getPlayer((**i).getOponentID(worb)).getPoints());
	}
}
void Player::updateResult(int Tourn)
{
	int ptr=0;
	Points=Color=0;
	for(vector<vector<Match>::const_iterator>::iterator i=Match_List.begin(); (ptr<Tourn)&&(i<Match_List.end()); ++i)
	{
		++ptr;
		int worb=0;
		if((*i)->getWhite()==ID)
			worb=1;
		Points+=abs((**i).getResult(worb));
		Color+=2*worb-1;
	}
}

ostream& operator<< (ostream& out, const Match& object)
{
	out.width(14);
	out.setf(ios::left);
	out<<object.My_T->getPlayer(object.WhiteID).getSurname()<<' ';
	out.width(14);
	out.setf(ios::left);
	out<<object.My_T->getPlayer(object.BlackID).getSurname()<<' '<<object.Res_List[object.Result];
	return out;
}