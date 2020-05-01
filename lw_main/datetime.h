#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "string.h"
#include "stringHelper.h"
#include "structures.h"

#define OUT_OF_DAY_EXCEPTION 0
#define OUT_OF_MONTH_EXCEPTION 0
#define OUT_OF_YEAR_EXCEPTION 0
#define OUT_OF_HOUR_EXCEPTION 0
#define OUT_OF_MINUTE_EXCEPTION 0

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

int InitHours(int hour)
{
	if (hour > 23 || hour < 0)
		return OUT_OF_HOUR_EXCEPTION;
	return hour;
}

int InitMinutes(int minute)
{
	if (minute > 59 || minute < 0)
		return OUT_OF_MINUTE_EXCEPTION;
	return minute;
}

char* DateTimeToString(struct DateTime dateTime)
{
	char* strDate = (char*)malloc(sizeof(char) * 17);

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

	char* sHour = NumberToString(dateTime.hours);
	if (dateTime.hours < 10)
	{
		sHour[1] = sHour[0];
		sHour[0] = '0';
	}

	char* sMinute = NumberToString(dateTime.minutes);
	if (dateTime.minutes < 10)
	{
		sMinute[1] = sMinute[0];
		sMinute[0] = '0';
	}

	strDate = Concat(strDate, sDay);
	strDate = Concat(strDate, ".");
	strDate = Concat(strDate, sMonth);
	strDate = Concat(strDate, ".");
	strDate = Concat(strDate, sYear);

	strDate = Concat(strDate, " ");

	strDate = Concat(strDate, sHour);
	strDate = Concat(strDate, ":");
	strDate = Concat(strDate, sMinute);

	strDate[16] = '/0';

	return strDate;
}

int CheckDate(struct DateTime date1, struct DateTime date2)
{
	if (date1.year > date2.year) return 1;
	else if (date1.year < date2.year) return -1;

	if (date1.month > date2.month) return 1;
	else if (date1.month < date2.month) return -1;

	if (date1.day > date2.day) return 1;
	else if (date1.day < date2.day) return -1;

	if (date1.hours == -1 || date2.hours == -1)
		return 0;


	if (date1.hours > date2.hours) return 1;
	else if (date1.hours < date2.hours) return -1;

	if (date1.minutes > date2.minutes) return 1;
	else if (date1.minutes < date2.minutes) return -1;

	return 0;
}