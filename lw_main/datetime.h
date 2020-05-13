#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "string.h"
#include "stringHelper.h"
#include "structures.h"

#define OUT_OF_DAY_EXCEPTION 0
#define OUT_OF_MONTH_EXCEPTION 0
#define OUT_OF_YEAR_EXCEPTION 0
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
	if (hour > 24 || hour < 1)
		return OUT_OF_HOUR_EXCEPTION;
	return hour;
}

int InitMinutes(int minute)
{
	if (minute > 59 || minute < 0)
		return OUT_OF_MINUTE_EXCEPTION;
	return minute;
}

char* DateTimeToString_RU(struct DateTime dateTime, bool isArtist)
{
	char* strDate = (char*)malloc(sizeof(char) * 17);

	char* sDay = NumberToString(dateTime.day);
	if (dateTime.day < 10)
	{
		strDate[1] = sDay[0];
		strDate[0] = '0';
	}
	else
	{
		strDate[0] = sDay[0];
		strDate[1] = sDay[1];
	}

	strDate[2] = '.';
	char* sMonth = NumberToString(dateTime.month);
	if (dateTime.month < 10)
	{
		strDate[4] = sMonth[0];
		strDate[3] = '0';
	}
	else
	{
		strDate[3] = sMonth[0];
		strDate[4] = sMonth[1];
	}
	strDate[5] = '.';

	char* sYear = NumberToString(dateTime.year);

	strDate[6] = sYear[0];
	strDate[7] = sYear[1];
	strDate[8] = sYear[2];
	strDate[9] = sYear[3];

	if (isArtist)
	{
		strDate[10] = '\0';
		return strDate;
	}

	strDate[10] = ' ';

	char* sHour = NumberToString(dateTime.hours);
	if (dateTime.hours < 10)
	{
		strDate[12] = sHour[0];
		strDate[11] = '0';
	}
	else
	{
		strDate[11] = sHour[0];
		strDate[12] = sHour[1];
	}
	strDate[13] = ':';

	char* sMinute = NumberToString(dateTime.minutes);
	if (dateTime.minutes < 10)
	{
		strDate[15] = sMinute[0];
		strDate[14] = '0';
	}
	else
	{
		strDate[14] = sMinute[0];
		strDate[15] = sMinute[1];
	}

	strDate[16] = '\0';

	return strDate;
}

char* DateTimeToString_EN(struct DateTime dateTime, bool isArtist)
{
	bool lower = false;

	char* strDate = (char*)malloc(sizeof(char) * 19);

	char* sMonth = NumberToString(dateTime.month);
	if (dateTime.month < 10)
	{
		strDate[1] = sMonth[0];
		strDate[0] = '0';
	}
	else
	{
		strDate[0] = sMonth[0];
		strDate[1] = sMonth[1];
	}
	strDate[2] = '/';

	char* sDay = NumberToString(dateTime.day);
	if (dateTime.day < 10)
	{
		strDate[4] = sDay[0];
		strDate[3] = '0';
	}
	else
	{
		strDate[3] = sDay[0];
		strDate[4] = sDay[1];
	}

	strDate[5] = '/';

	char* sYear = NumberToString(dateTime.year);

	strDate[6] = sYear[0];
	strDate[7] = sYear[1];
	strDate[8] = sYear[2];
	strDate[9] = sYear[3];

	if (isArtist)
	{
		strDate[10] = '\0';
		return strDate;
	}

	strDate[10] = ' ';

	if (dateTime.hours < 12 || dateTime.hours == 24)
		lower = true;
	else
		dateTime.hours -= 12;

	char* sHour = NumberToString(dateTime.hours);
	if (dateTime.hours < 10)
	{
		strDate[12] = sHour[0];
		strDate[11] = '0';
	}
	else
	{
		strDate[11] = sHour[0];
		strDate[12] = sHour[1];
	}
	strDate[13] = ':';

	char* sMinute = NumberToString(dateTime.minutes);
	if (dateTime.minutes < 10)
	{
		strDate[15] = sMinute[0];
		strDate[14] = '0';
	}
	else
	{
		strDate[14] = sMinute[0];
		strDate[15] = sMinute[1];
	}

	if (lower)
	{
		strDate[16] = 'p';
		strDate[17] = 'm';
	}
	else
	{
		strDate[16] = 'a';
		strDate[17] = 'm';
	}

	strDate[18] = '\0';

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