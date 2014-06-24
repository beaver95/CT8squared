#include<Chess_tournament_64.h>

char Match::Res_List_S[]={'1','S','0','+','=','-'};
int Player::IDP=0;
std::string Match::Res_List[]={"1:0","1/2","0:1","+:-"," = ","-:+"," + "," - ","N/A"};
std::string Chess_Player::Title_List[]={"Grandmaster","International Master","FIDE Master","Candidate Master","1st Category","2nd Category","3rd Category","4th Category"};
std::string Chess_Player::Title_List_S[]={"GM","IM","FM","CM","1C","2C","3C","4C"};

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
