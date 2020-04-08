#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "string.h"
#include "stringHelper.h"
#include "structures.h"
#include "stdio.h"

struct Perfomance InitPerfomance(struct Perfomance* prevPerfomance, char* title, int ticketCount, long ticketCosts)
{
	int id = 0;
	if (prevPerfomance != NULL)
	{
		id = prevPerfomance->id + 1;
	}

	struct Perfomance perfomance;

	perfomance.id = id;
	perfomance.title = title;
	perfomance.ticketCount = ticketCount;
	perfomance.ticketCost = ticketCosts;

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

	struct Perfomance* perfomances = (struct Perfomance*)malloc(0);

	int size = 0;
	char** splitted = Split(buffer, '\n', &size);

	for (size_t i = 0; i < size; i++)
	{
		int val = 0;
		char** splittedUser = Split(splitted[i], ';', &val);

		perfomances = (struct Perfomance*)realloc(perfomances, sizeof(struct Perfomance) * (i + 1));
		perfomances[i].id = FromStringToNumber(splittedUser[0]);
		perfomances[i].ticketCost = FromStringToNumber(splittedUser[1]);
		perfomances[i].ticketCount = FromStringToNumber(splittedUser[2]);
		perfomances[i].title = (char*)malloc(sizeof(char) * 1);
		perfomances[i].title[0] = '\0';

		perfomances[i].title = Concat(perfomances[i].title, splittedUser[3]);
		(*count) += 1;
	}

	return perfomances;
}

void AddPerfomanceInFile(char* fileName, struct Perfomance perfomance)
{
	char* buffer = (char*)malloc(0);
	buffer[0] = '\0';

	buffer = Concat(buffer, NumberToString(perfomance.id));
	buffer = Concat(buffer, (char*)";");
	buffer = Concat(buffer, NumberToString(perfomance.ticketCost));
	buffer = Concat(buffer, (char*)";");
	buffer = Concat(buffer, NumberToString(perfomance.ticketCount));
	buffer = Concat(buffer, (char*)";");
	buffer = Concat(buffer, perfomance.title);
	buffer = Concat(buffer, (char*)"\n");

	FILE* file;
	file = fopen(fileName, "a+");
	fwrite(buffer, sizeof(char), strlen(buffer), file);
	fclose(file);
}

int SetPerfomancesInFile(char* fileName, struct Perfomance* perfomances, int count)
{
	if (perfomances == NULL)
		return 0;

	char* buffer = (char*)malloc(0);
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
		buffer = Concat(buffer, (char*)"\n");
	}

	FILE* file;
	file = fopen(fileName, "w");
	fwrite(buffer, sizeof(char), strlen(buffer), file);
	fclose(file);

	return 1;
}

int DeletePerfomance(struct Perfomance perfomanceForDelete, struct Perfomance* perfomances, struct ArtistPerfomances* artistPerfomances);