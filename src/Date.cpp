#include<Date.h>

MyDate::MyDate(int d, int m, int y)
{
    if ((d>days_in_month(m, y))||(d<1)||(m>12)||(m<=0))
        d=m=y=1;
    day=d;
    month=m;
    year=y;
}
MyDate::MyDate(const MyDate &orig)
{
    day=orig.day;
    month=orig.month;
    year=orig.year;
}
MyDate::~MyDate()
{
}
int MyDate::getDay() const
{
    return day;
}
int MyDate::getMonth() const
{
    return month;
}
int MyDate::getYear() const
{
    return year;
}
void MyDate::set(int d, int m, int y)
{
    if ((d<=days_in_month(m, y)&&d>0)&&(m<=12&&m>0))
    {
        day=d;
        month=m;
        year=y;
    }
}
int MyDate::days_in_month (int m, int y)
{
    return (m==2 ? 28-(4-y%4)/4 : (31-(m+1)%9%2));
}
ostream &operator <<(ostream &output, MyDate object)
{
    output<<object.day<<'/'<<object.month<<'/'<<object.year;
    return output;
}
void MyDate::print() const
{
    cout<<day<<'/'<<month<<'/'<<year;
}
int MyDate::operator++(int)
{
    if ((day<=days_in_month(month, year)&&day>0)&&(month<=12&&month>0))
    {
        if (++day>days_in_month(month, year))
        {
            day=1;
            month%=12;
            ++month;
        }
        return 0;
    }
    else
    {
        if (++day>days_in_month(month, year))
        {
            day=1;
            ++month%=12;
        }
        return -1;
    }
}
