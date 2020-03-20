#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "string.h"
#include "stringHelper.h"
#include "structures.h"

#define OUT_OF_DAY_EXCEPTION -1
#define OUT_OF_MONTH_EXCEPTION -1
#define OUT_OF_YEAR_EXCEPTION -1

enum Months
{
	January = 1,
	February,
	March,
	April,
	May,
	June,
	Jule,
	August,
	September,
	October,
	November,
	December
};



int InitDay(struct DateTime date, int day)
{
	if (date.month == February)
	{
		if (date.year % 4 == 0)
		{
			if (day > 29)
				return OUT_OF_DAY_EXCEPTION;
			return day;
		}
		else
		{
			if (day > 28)
				return OUT_OF_DAY_EXCEPTION;
			return day;
		}
	}
	else if (date.month >= January && date.month < August)
	{
		if (date.month % 2 == 1)
		{
			if (day > 31)
				return OUT_OF_DAY_EXCEPTION;
			return day;
		}
		else
		{
			if (day > 30)
				return OUT_OF_DAY_EXCEPTION;
			return day;
		}
	}
	else
	{
		if (date.month % 2 == 0)
		{
			if (day > 31)
				return OUT_OF_DAY_EXCEPTION;
			return day;
		}
		else
		{
			if (day > 30)
				return OUT_OF_DAY_EXCEPTION;
			return day;
		}
	}
}

int InitMonth(int month)
{
	if (month < 1 || month > 12)
		return OUT_OF_MONTH_EXCEPTION;
	return month;
}

int InitYear(int year)
{
	if (year > 2020 || year < 1900)
		return OUT_OF_YEAR_EXCEPTION;
	return year;
}

char* DateTimeToString(struct DateTime dateTime)
{
	char* strDate = (char*)malloc(sizeof(char) * 11);

	char* sDay = NumberToString(dateTime.day);
	if (dateTime.day < 10)
	{
		sDay[1] = sDay[0];
		sDay[0] = '0';
	}

	char* sMonth = NumberToString(dateTime.month);
	if (dateTime.month < 10)
	{
		sDay[1] = sDay[0];
		sDay[0] = '0';
	}

	char* sYear = NumberToString(dateTime.year);

	strDate = strpbrk(strDate, sDay);
	strDate = strpbrk(strDate, ".");
	strDate = strpbrk(strDate, sMonth);
	strDate = strpbrk(strDate, ".");
	strDate = strpbrk(strDate, sYear);
	strDate[10] = '/0';

	return strDate;
}

struct DateTime StringToDateTime(char* strDate)
{

}