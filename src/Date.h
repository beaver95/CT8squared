#pragma once

#include<iostream>
#include<stdlib.h>
using namespace std;

class Date
{
public:
	~Date();
	Date(int=1, int=1, int=2000);
	Date(const Date&);
	int getMonth() const;
	int getDay() const;
	int getYear() const;
	void set(int, int, int);
	void print() const;
	friend ostream &operator <<(ostream &, Date);
	int operator++(int);
	Date& operator=(const Date& date)
	{
		day=date.day;
		month=date.month;
		year=date.year;
		return *this;
	}
private:
	int day;
	int month;
	int year;
	int days_in_month(int, int);
};

Date::Date(int d, int m, int y)
{
	if ((d>days_in_month(m, y))||(d<1)||(m>12)||(m<=0))
		d=m=y=1;
	day=d;
	month=m;
	year=y;
}
Date::Date(const Date &orig)
{
	day=orig.day;
	month=orig.month;
	year=orig.year;
}
Date::~Date()
{
}
int Date::getDay() const
{
	return day;
}
int Date::getMonth() const
{
	return month;
}
int Date::getYear() const
{
	return year;
}
void Date::set(int d, int m, int y)
{
	if ((d<=days_in_month(m, y)&&d>0)&&(m<=12&&m>0))
	{
		day=d;
		month=m;
		year=y;
	}
}
int Date::days_in_month (int m, int y)
{
	return (m==2 ? 28-(4-y%4)/4 : (31-(m+1)%9%2));
}
ostream &operator <<(ostream &output, Date object)
{
	output<<object.day<<'/'<<object.month<<'/'<<object.year;
	return output;
}
void Date::print() const
{
	cout<<day<<'/'<<month<<'/'<<year;
}
int Date::operator++(int)
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