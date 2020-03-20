#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "string.h"
#include "stringHelper.h"
#include "structures.h"

#define OUT_OF_DAY_EXCEPTION -1
#define OUT_OF_MONTH_EXCEPTION -1
#define OUT_OF_YEAR_EXCEPTION -1
#define OUT_OF_HOUR_EXCEPTION -1
#define OUT_OF_MINUTE_EXCEPTION -1

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

	strDate = concat(strDate, sDay);
	strDate = concat(strDate, ".");
	strDate = concat(strDate, sMonth);
	strDate = concat(strDate, ".");
	strDate = concat(strDate, sYear);

	strDate = concat(strDate, " ");

	strDate = concat(strDate, sHour);
	strDate = concat(strDate, ":");
	strDate = concat(strDate, sMinute);

	strDate[16] = '/0';

	return strDate;
}