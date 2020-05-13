#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "string.h"
#include "stringHelper.h"
#include "structures.h"
#include "stdio.h"

struct Perfomance SetNewPerfomance(char* title, int ticketCount, long ticketCosts, struct DateTime perfDate, struct Perfomance* perfomances, int perfCount)
{
	int id = rand() % 10000 + 1;
	for (size_t i = 0; i < perfCount; i++)
	{
		if (perfomances[i].id == id)
		{
			id = rand() % 10000 + 1;
			i = -1;
		}
	}

	struct Perfomance perfomance;
	perfomance.title = (char*)malloc(sizeof(char));

	perfomance.id = id;
	strcpy(perfomance.title, title);
	perfomance.ticketCount = ticketCount;
	perfomance.ticketCost = ticketCosts;
	perfomance.time = perfDate;

	return perfomance;
}

struct Perfomance* GetPerfomancesFromFile(char* fileName, int* count)
{
	(*count) = 0;

	char* buffer = (char*)malloc(1000);
	buffer[0] = '\0';

	char elem;
	int strPos = 0;

	FILE* file = fopen(fileName, "r");
	if (file == NULL)
	{
		file = fopen(fileName, "w");
		fclose(file);

		return NULL;
	}

	while (fread(&elem, 1, 1, file))
	{
		buffer[strPos++] = elem;
	}

	fclose(file);

	buffer = (char*)realloc(buffer, strPos + 1);
	buffer[strPos] = '\0';

	if (strlen(buffer) == 0)
	{
		return NULL;
	}

	struct Perfomance* perfomances = (struct Perfomance*)malloc(sizeof(struct Perfomance));

	int size = 0;

	char splitted[100][100];

	char separator = '\n';
	int pos = 0;
	int retPos = 0;
	while (buffer[pos] != '\0')
	{
		char* tempStr = (char*)malloc(sizeof(char) * 100);

		int strElements = 0;
		while (buffer[pos] != separator && buffer[pos] != '\0')
		{

			tempStr[strElements++] = buffer[pos++];
		}
		pos++;
		tempStr[strElements] = '\0';

		splitted[retPos][0] = '\0';
		strcpy(splitted[retPos], tempStr);

		size++;
		retPos++;
	}

	for (size_t i = 0; i < size; i++)
	{
		int int_value = 0;
		char splittedUser[100][100];

		separator = ';';
		pos = 0;
		retPos = 0;
		while (pos < strlen(splitted[i]))
		{
			char tempStr[200];

			int strElements = 0;
			while (splitted[i][pos] != separator && splitted[i][pos] != '\0')
			{

				tempStr[strElements++] = splitted[i][pos++];
			}
			pos++;
			tempStr[strElements] = '\0';

			splittedUser[retPos][0] = '\0';
			strcpy(splittedUser[retPos], tempStr);

			retPos++;
		}

		perfomances = (struct Perfomance*)realloc(perfomances, sizeof(struct Perfomance) * (i + 1));
		perfomances[i].id = (int)strtol(splittedUser[0], (char**)NULL, 10);
		perfomances[i].ticketCost = (int)strtol(splittedUser[1], (char**)NULL, 10);
		perfomances[i].ticketCount = (int)strtol(splittedUser[2], (char**)NULL, 10);

		perfomances[i].title = (char*)malloc(sizeof(char) * 50);
		strcpy(perfomances[i].title, splittedUser[3]);

		perfomances[i].time.minutes = (int)strtol(splittedUser[4], (char**)NULL, 10);
		perfomances[i].time.hours = (int)strtol(splittedUser[5], (char**)NULL, 10);
		perfomances[i].time.day = (int)strtol(splittedUser[6], (char**)NULL, 10);
		perfomances[i].time.month = (int)strtol(splittedUser[7], (char**)NULL, 10);
		perfomances[i].time.year = (int)strtol(splittedUser[8], (char**)NULL, 10);

		(*count) += 1;
	}

	return perfomances;
}

int SetPerfomancesInFile(char* fileName, struct Perfomance* perfomances, int count)
{
	if (perfomances == NULL)
		return 0;

	char* buffer = (char*)malloc(sizeof(char));
	buffer[0] = '\0';

	for (size_t i = 0; i < count; i++)
	{
		buffer = Concat(buffer, NumberToString(perfomances[i].id));
		buffer = Concat(buffer, (char*)";");
		buffer = Concat(buffer, NumberToString(perfomances[i].ticketCost));
		buffer = Concat(buffer, (char*)";");
		buffer = Concat(buffer, NumberToString(perfomances[i].ticketCount));
		buffer = Concat(buffer, (char*)";");
		buffer = Concat(buffer, perfomances[i].title);
		buffer = Concat(buffer, (char*)";");
		buffer = Concat(buffer, NumberToString(perfomances[i].time.minutes));
		buffer = Concat(buffer, (char*)";");
		buffer = Concat(buffer, NumberToString(perfomances[i].time.hours));
		buffer = Concat(buffer, (char*)";");
		buffer = Concat(buffer, NumberToString(perfomances[i].time.day));
		buffer = Concat(buffer, (char*)";");
		buffer = Concat(buffer, NumberToString(perfomances[i].time.month));
		buffer = Concat(buffer, (char*)";");
		buffer = Concat(buffer, NumberToString(perfomances[i].time.year));
		buffer = Concat(buffer, (char*)";");
		buffer = Concat(buffer, (char*)"\n");
	}

	FILE* file;
	file = fopen(fileName, "w");
	fwrite(buffer, sizeof(char), strlen(buffer), file);
	fclose(file);

	return 1;
}

enum PerfomanceVariables
{
	Title = 1,
	TicketCount,
	TicketCost,
	DatePerf
};

struct Perfomance* SortPerfomancesArray(struct Perfomance* perfomances, int perfomanceCount, int whatSortBy)
{
	bool changed = true;
	switch (whatSortBy)
	{
	case Title:
	{
		while (changed)
		{
			changed = false;

			for (size_t i = 0; i < perfomanceCount - 1; i++)
			{
				if (strcmp(perfomances[i].title, perfomances[i + 1].title) > 0)
				{
					struct Perfomance perfomance;
					perfomance.id = perfomances[i].id;
					perfomance.time = perfomances[i].time;
					perfomance.ticketCost = perfomances[i].ticketCost;
					perfomance.ticketCount = perfomances[i].ticketCount;
					perfomance.title = (char*)malloc(sizeof(char) * 10);
					strcpy(perfomance.title, perfomances[i].title);


					perfomances[i].id = perfomances[i + 1].id;
					perfomances[i].time = perfomances[i + 1].time;
					perfomances[i].ticketCost = perfomances[i + 1].ticketCost;
					perfomances[i].ticketCount = perfomances[i + 1].ticketCount;
					strcpy(perfomances[i].title, perfomances[i + 1].title);


					perfomances[i + 1].id = perfomance.id;
					perfomances[i + 1].time = perfomance.time;
					perfomances[i + 1].ticketCost = perfomance.ticketCost;
					perfomances[i + 1].ticketCount = perfomance.ticketCount;
					strcpy(perfomances[i + 1].title, perfomance.title);

					changed = true;
				}
			}
		}
	}
	case TicketCount:
	{
		while (changed)
		{
			changed = false;

			for (size_t i = 0; i < perfomanceCount - 1; i++)
			{
				if (perfomances[i].ticketCount > perfomances[i + 1].ticketCount)
				{
					struct Perfomance perfomance;
					perfomance.id = perfomances[i].id;
					perfomance.time = perfomances[i].time;
					perfomance.ticketCost = perfomances[i].ticketCost;
					perfomance.ticketCount = perfomances[i].ticketCount;
					perfomance.title = (char*)malloc(1);
					strcpy(perfomance.title, perfomances[i].title);


					perfomances[i].id = perfomances[i + 1].id;
					perfomances[i].time = perfomances[i + 1].time;
					perfomances[i].ticketCost = perfomances[i + 1].ticketCost;
					perfomances[i].ticketCount = perfomances[i + 1].ticketCount;
					strcpy(perfomances[i].title, perfomances[i + 1].title);


					perfomances[i + 1].id = perfomance.id;
					perfomances[i + 1].time = perfomance.time;
					perfomances[i + 1].ticketCost = perfomance.ticketCost;
					perfomances[i + 1].ticketCount = perfomance.ticketCount;
					perfomances[i + 1].title = (char*)malloc(1);
					strcpy(perfomances[i + 1].title, perfomance.title);

					changed = true;
				}
			}
		}
	}
	case TicketCost:
	{
		while (changed)
		{
			changed = false;

			for (size_t i = 0; i < perfomanceCount - 1; i++)
			{
				if (perfomances[i].ticketCost > perfomances[i + 1].ticketCost)
				{
					struct Perfomance perfomance;
					perfomance.id = perfomances[i].id;
					perfomance.time = perfomances[i].time;
					perfomance.ticketCost = perfomances[i].ticketCost;
					perfomance.ticketCount = perfomances[i].ticketCount;
					perfomance.title = (char*)malloc(1);
					strcpy(perfomance.title, perfomances[i].title);


					perfomances[i].id = perfomances[i + 1].id;
					perfomances[i].time = perfomances[i + 1].time;
					perfomances[i].ticketCost = perfomances[i + 1].ticketCost;
					perfomances[i].ticketCount = perfomances[i + 1].ticketCount;
					strcpy(perfomances[i].title, perfomances[i + 1].title);


					perfomances[i + 1].id = perfomance.id;
					perfomances[i + 1].time = perfomance.time;
					perfomances[i + 1].ticketCost = perfomance.ticketCost;
					perfomances[i + 1].ticketCount = perfomance.ticketCount;
					perfomances[i + 1].title = (char*)malloc(1);
					strcpy(perfomances[i + 1].title, perfomance.title);

					changed = true;
				}
			}
		}
	}
	case DatePerf:
	{
		while (changed)
		{
			changed = false;

			for (size_t i = 0; i < perfomanceCount - 1; i++)
			{
				if (CheckDate(perfomances[i].time, perfomances[i + 1].time) > 0)
				{
					struct Perfomance perfomance;
					perfomance.id = perfomances[i].id;
					perfomance.time = perfomances[i].time;
					perfomance.ticketCost = perfomances[i].ticketCost;
					perfomance.ticketCount = perfomances[i].ticketCount;
					perfomance.title = (char*)malloc(1);
					strcpy(perfomance.title, perfomances[i].title);


					perfomances[i].id = perfomances[i + 1].id;
					perfomances[i].time = perfomances[i + 1].time;
					perfomances[i].ticketCost = perfomances[i + 1].ticketCost;
					perfomances[i].ticketCount = perfomances[i + 1].ticketCount;
					strcpy(perfomances[i].title, perfomances[i + 1].title);


					perfomances[i + 1].id = perfomance.id;
					perfomances[i + 1].time = perfomance.time;
					perfomances[i + 1].ticketCost = perfomance.ticketCost;
					perfomances[i + 1].ticketCount = perfomance.ticketCount;
					perfomances[i + 1].title = (char*)malloc(1);
					strcpy(perfomances[i + 1].title, perfomance.title);

					changed = true;
				}
			}
		}
	}
	}

	return perfomances;
}

struct Perfomance* FindPerfomancesByParams(struct Perfomance* perfomances, int perfomanceCount, int findBy, int* findedCount, char* title, int ticketCount, int ticketCost, struct DateTime date)
{
	(*findedCount) = 0;
	struct Perfomance* findedPerfomances = (struct Perfomance*)malloc(sizeof(struct Perfomance) * 0);

	switch (findBy)
	{
	case Title:
	{
		for (size_t i = 0; i < perfomanceCount; i++)
		{
			if (strcmp(perfomances[i].title, title) == 0)
			{
				(*findedCount)++;
				findedPerfomances = (struct Perfomance*)realloc(findedPerfomances, sizeof(struct Perfomance) * (*findedCount));
				findedPerfomances[(*findedCount) - 1] = perfomances[i];
			}
		}
	}
	case TicketCount:
	{
		for (size_t i = 0; i < perfomanceCount; i++)
		{
			if (perfomances[i].ticketCount == ticketCount)
			{
				(*findedCount)++;
				findedPerfomances = (struct Perfomance*)realloc(findedPerfomances, sizeof(struct Perfomance) * (*findedCount));
				findedPerfomances[(*findedCount) - 1] = perfomances[i];
			}
		}
	}
	case TicketCost:
	{
		for (size_t i = 0; i < perfomanceCount; i++)
		{
			if (perfomances[i].ticketCost == ticketCost)
			{
				(*findedCount)++;
				findedPerfomances = (struct Perfomance*)realloc(findedPerfomances, sizeof(struct Perfomance) * (*findedCount));
				findedPerfomances[(*findedCount) - 1] = perfomances[i];
			}
		}
	}
	case DatePerf:
	{
		for (size_t i = 0; i < perfomanceCount; i++)
		{
			if (CheckDate(perfomances[i].time, date) == 0)
			{
				(*findedCount)++;
				findedPerfomances = (struct Perfomance*)realloc(findedPerfomances, sizeof(struct Perfomance) * (*findedCount));
				findedPerfomances[(*findedCount) - 1] = perfomances[i];
			}
		}
	}
	}

	return findedPerfomances;
}

struct Perfomance* FilterPerfomancesArray(struct Perfomance* perfomances, int perfomanceCount, char** titles, int length, int* ticketsDiapazon, int* costDiapazon, struct DateTime startDate, struct DateTime endDate, int* counter)
{
	struct Perfomance* foundPerfomances = (struct Perfomance*)malloc(sizeof(struct Perfomance) * perfomanceCount);
	(*counter) = 0;

	for (size_t i = 0; i < perfomanceCount; i++)
	{
		if (titles != NULL)
		{
			for (size_t j = 0; j < length; j++)
			{
				if (strstr(perfomances[i].title, titles[j]) != NULL)
				{
					foundPerfomances[(*counter)++] = perfomances[i];
					break;
				}
			}
		}
		else if (ticketsDiapazon != NULL)
		{
			int lowCount = ticketsDiapazon[0];
			int highCount = ticketsDiapazon[1];

			if (perfomances[i].ticketCount >= lowCount && perfomances[i].ticketCount <= highCount)
			{
				foundPerfomances[(*counter)++] = perfomances[i];
			}
		}
		else if (costDiapazon != NULL)
		{
			int lowCost = costDiapazon[0];
			int highCost = costDiapazon[1];

			if (perfomances[i].ticketCost >= lowCost && perfomances[i].ticketCost <= highCost)
			{
				foundPerfomances[(*counter)++] = perfomances[i];
			}
		}
		else
		{
			if (CheckDate(perfomances[i].time, startDate) == 1 && CheckDate(perfomances[i].time, endDate) == -1)
			{
				foundPerfomances[(*counter)++] = perfomances[i];
			}
		}
	}

	return foundPerfomances;
}