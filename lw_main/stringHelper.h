#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "stdlib.h"
#include "math.h"
#include "stdbool.h"

char* NumberToString(unsigned long num)
{
	unsigned long temp = num;
	int changingSize = 0;
	while (temp != 0)
	{
		temp /= 10;
		changingSize++;
	}

	temp = num;
	int pos = 0;
	char* str = (char*)malloc(sizeof(char) * 8);
	for (int i = 1; i < changingSize + 1; i++)
	{
		int powed = (int)(temp / (unsigned long)pow(10, changingSize - i)) % 10;

		switch (powed)
		{
			case 0:	str[pos++] = '0'; break;
			case 1:	str[pos++] = '1'; break;
			case 2:	str[pos++] = '2'; break;
			case 3:	str[pos++] = '3'; break;
			case 4:	str[pos++] = '4'; break;
			case 5:	str[pos++] = '5'; break;
			case 6:	str[pos++] = '6'; break;
			case 7:	str[pos++] = '7'; break;
			case 8:	str[pos++] = '8'; break;
			case 9:	str[pos++] = '9'; break;
		}
	}
	str[pos++] = '\0';

	return str;
}

char** SliceStrings(char** strReturn, int retPos, int pos, char* str, char separator)
{
	if (pos == strlen(str))
	{
		return strReturn;
	}

	char* tempStr = (char*)malloc(sizeof(char) * 100);

	int strElements = 0;
	while (str[pos] != separator || str[pos] != '/0')
	{
		tempStr[strElements++] = str[pos++];
	}
	tempStr[strElements] = '/0';

	strReturn[retPos] = (char*)malloc(sizeof(char) * strElements);
	strReturn[retPos] = strpbrk(strReturn[retPos], tempStr);

	return SliceStrings(strReturn, ++retPos, pos, str, separator);
}

char** Split(char* str, char separator)
{
	int countElements = 1;
	for (size_t i = 0; i < strlen(str); i++) if (str[i] == separator) countElements++;

	char** strReturn = (char**)malloc(countElements);
	
	strReturn = SliceStrings(strReturn, 0, 0, str, separator);

	return strReturn;
}

long FromStringToNumber(char* str)
{
	int startPosition = 0;
	bool isNegative = false;

	if (str[startPosition] == '-')
	{
		isNegative = true;
		startPosition = 1;
	}
	long number = 0;

	for (size_t i = startPosition; i < strlen(str); i++)
	{
		int asciiNumber = (int)str[i];
		if (asciiNumber > 47 && asciiNumber < 58)
		{
			number *= 10;
			number += asciiNumber - 48;
		}
	}

	if (isNegative)
	{
		number *= -1;
	}

	return number;
}

char* concat(char* s1, char* s2) {

	size_t len1 = strlen(s1);
	size_t len2 = strlen(s2);

	char* result = malloc(len1 + len2 + 1);

	if (!result) {
		fprintf(stderr, "malloc() failed: insufficient memory!\n");
		return NULL;
	}

	memcpy(result, s1, len1);
	memcpy(result + len1, s2, len2 + 1);

	return result;
}