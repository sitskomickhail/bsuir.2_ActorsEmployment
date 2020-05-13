#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "string.h"
#include "stringHelper.h"
#include "structures.h"
#include "stdio.h"
#include "stdbool.h"
#include "datetime.h"

struct Artist SetNewArtistInfo(char* name, struct DateTime birthDate, struct Artist* artists, int artCount)
{
	int id = rand() % 10000 + 1;
	for (size_t i = 0; i < artCount; i++)
	{
		if (artists[i].id == id)
		{
			id = rand() % 10000 + 1;
			i = -1;
		}
	}

	struct Artist artist;
	artist.id = id;
	artist.name = (char*)malloc(0);
	strcpy(artist.name, name);
	artist.birthDate = birthDate;

	return artist;
}

struct Artist* GetArtistsFromFile(char* fileName, int* count)
{
	(*count) = 0;

	char buffer[1000];
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
	buffer[strPos] = '\0';

	if (strlen(buffer) == 0)
	{
		return NULL;
	}

	struct Artist* artists = (struct Artist*)malloc(sizeof(struct Artist));

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


		artists = (struct Artist*)realloc(artists, sizeof(struct Artist) * (i + 1));
		artists[i].id = (int)strtol(splittedUser[0], (char**)NULL, 10);

		artists[i].name = (char*)malloc(sizeof(char) * 20);
		strcpy(artists[i].name, splittedUser[1]);

		artists[i].birthDate.day = (int)strtol(splittedUser[2], (char**)NULL, 10);
		artists[i].birthDate.month = (int)strtol(splittedUser[3], (char**)NULL, 10);
		artists[i].birthDate.year = (int)strtol(splittedUser[4], (char**)NULL, 10);

		(*count) += 1;
	}

	return artists;
}

int SetArtistsInFile(char* fileName, struct Artist* artists, int count)
{
	if (artists == NULL)
		return 0;

	char* buffer = (char*)malloc(0);
	buffer[0] = '\0';

	for (size_t i = 0; i < count; i++)
	{
		buffer = Concat(buffer, NumberToString(artists[i].id));
		buffer = Concat(buffer, (char*)";");

		buffer = Concat(buffer, artists[i].name);
		buffer = Concat(buffer, (char*)";");

		buffer = Concat(buffer, NumberToString(artists[i].birthDate.day));
		buffer = Concat(buffer, (char*)";");
		buffer = Concat(buffer, NumberToString(artists[i].birthDate.month));
		buffer = Concat(buffer, (char*)";");
		buffer = Concat(buffer, NumberToString(artists[i].birthDate.year));
		buffer = Concat(buffer, (char*)";");

		buffer = Concat(buffer, (char*)"\n");
	}

	FILE* file;
	file = fopen(fileName, "w");
	fwrite(buffer, sizeof(char), strlen(buffer), file);
	fclose(file);

	return 1;
}

enum SortBy
{
	Name = 1,
	Date
};

struct Artist* SortArtistsArray(struct Artist* artists, int artistCount, int whatSortBy)
{
	bool changed = true;
	switch (whatSortBy)
	{
	case Name:
	{
		while (changed)
		{
			changed = false;

			for (size_t i = 0; i < artistCount - 1; i++)
			{
				if (strcmp(artists[i].name, artists[i + 1].name) > 0)
				{
					struct Artist tempArtist;
					tempArtist.id = artists[i].id;
					tempArtist.birthDate = artists[i].birthDate;
					tempArtist.name = (char*)malloc(sizeof(char) * 10);
					strcpy(tempArtist.name, artists[i].name);

					artists[i].id = artists[i + 1].id;
					artists[i].birthDate = artists[i + 1].birthDate;
					strcpy(artists[i].name, artists[i + 1].name);

					artists[i + 1].id = tempArtist.id;
					artists[i + 1].birthDate = tempArtist.birthDate;
					strcpy(artists[i + 1].name, tempArtist.name);

					changed = true;
				}
			}
		}
	}
	case Date:
	{
		while (changed)
		{
			changed = false;

			for (size_t i = 0; i < artistCount - 1; i++)
			{
				artists[i].birthDate.hours = -1;
				if (CheckDate(artists[i].birthDate, artists[i + 1].birthDate) > 0)
				{
					struct Artist tempArtist;
					tempArtist.id = artists[i].id;
					tempArtist.birthDate = artists[i].birthDate;
					tempArtist.name = (char*)malloc(1);
					strcpy(tempArtist.name, artists[i].name);

					artists[i].id = artists[i + 1].id;
					artists[i].birthDate = artists[i + 1].birthDate;
					strcpy(artists[i].name, artists[i + 1].name);

					artists[i + 1].id = tempArtist.id;
					artists[i + 1].birthDate = tempArtist.birthDate;
					strcpy(artists[i + 1].name, tempArtist.name);

					changed = true;
				}
			}
		}
	}
	}

	return artists;
}

struct Artist* FindArtistsByParams(struct Artist* artists, int artistCount, int findBy, int* findedCount, char* name, struct DateTime date)
{
	(*findedCount) = 0;
	struct Artist* findedArtists = (struct Artist*)malloc(sizeof(struct Artist) * 0);

	switch (findBy)
	{
	case Name:
	{
		for (size_t i = 0; i < artistCount; i++)
		{
			if (strcmp(artists[i].name, name) == 0)
			{
				(*findedCount)++;
				findedArtists = (struct Artist*)realloc(findedArtists, sizeof(struct Artist) * (*findedCount));
				findedArtists[(*findedCount) - 1] = artists[i];
			}
		}
	}
	case Date:
	{
		date.hours = -1;
		for (size_t i = 0; i < artistCount; i++)
		{
			if (CheckDate(artists[i].birthDate, date) == 0)
			{
				(*findedCount)++;
				findedArtists = (struct Artist*)realloc(findedArtists, sizeof(struct Artist) * (*findedCount));
				findedArtists[(*findedCount) - 1] = artists[i];
			}
		}
	}
	}

	return findedArtists;
}

struct Artist* Find5MostDemandedActors(struct Artist* artists, int artistCount, struct ArtistPerfomances* artPerfomances, int artPerfomancesCount, int* foundCount, int** actorsUsings)
{
	(*foundCount) = 0;
	struct Artist* foundArtists = (struct Artist*)malloc(sizeof(struct Artist) * artistCount);
	(*actorsUsings) = (int*)calloc(5, sizeof(int));
	int* actorsUsingCounter = (int*)calloc(artistCount, sizeof(int));

	for (size_t i = 0; i < artistCount; i++)
	{
		for (size_t j = 0; j < artPerfomancesCount; j++)
		{
			if (artists[i].id == artPerfomances[j].artistId)
			{
				actorsUsingCounter[i]++;
			}
		}
	}

	for (size_t i = 0; i < artistCount; i++)
	{
		foundArtists[i].id = artists[i].id;
		foundArtists[i].name = (char*)malloc(sizeof(char) * 15);

		strcpy(foundArtists[i].name, artists[i].name);
		foundArtists[i].birthDate = artists[i].birthDate;
	}

	bool changed = true;
	while (changed)
	{
		changed = false;
		for (size_t i = 0; i < artistCount - 1; i++)
		{
			if (actorsUsingCounter[i] < actorsUsingCounter[i + 1])
			{
				struct Artist tempArtist;
				tempArtist.id = foundArtists[i].id;
				tempArtist.birthDate = foundArtists[i].birthDate;
				tempArtist.name = (char*)malloc(sizeof(char) * 10);
				strcpy(tempArtist.name, foundArtists[i].name);

				foundArtists[i].id = foundArtists[i + 1].id;
				foundArtists[i].birthDate = foundArtists[i + 1].birthDate;
				strcpy(foundArtists[i].name, foundArtists[i + 1].name);

				foundArtists[i + 1].id = tempArtist.id;
				foundArtists[i + 1].birthDate = tempArtist.birthDate;
				strcpy(foundArtists[i + 1].name, tempArtist.name);

				int value = actorsUsingCounter[i];
				actorsUsingCounter[i] = actorsUsingCounter[i + 1];
				actorsUsingCounter[i + 1] = value;

				changed = true;
			}
		}
	}

	foundArtists = (struct Artist*)realloc(foundArtists, sizeof(struct Artist) * 5);
	actorsUsingCounter = (int*)realloc(actorsUsingCounter, sizeof(int) * 5);

	int counter = 0;
	for (size_t i = 0; i < 5; i++)
	{
		if (actorsUsingCounter[i] == 0)
		{
			foundArtists = (struct Artist*)realloc(foundArtists, sizeof(struct Artist) * counter);
			actorsUsingCounter = (int*)realloc(actorsUsingCounter, sizeof(int) * counter);
			break;
		}

		counter++;
	}

	for (size_t i = 0; i < counter; i++)
	{
		(*actorsUsings)[i] = actorsUsingCounter[i];
		(*foundCount)++;
	}

	/*for (size_t i = 0; i < artistCount; i++)
	{
		if ((*foundCount) == 5)
		{
			break;
		}

		int counter = 5;
		for (size_t j = i; j < artistCount; j++)
		{
			if (actorsUsingCounter[i] <= actorsUsingCounter[j])
			{
				counter--;
			}
		}

		if (counter < 5 + (*foundCount))
		{
			(*foundCount)++;
			foundArtists = (struct Artist*)realloc(foundArtists, sizeof(struct Artist) * (*foundCount));
			foundArtists[(*foundCount) - 1] = artists[i];
			(*actorsUsings)[(*foundCount) - 1] = actorsUsingCounter[i];
		}
	}*/

	return foundArtists;
}

struct Artist* FiterArtistsArray(struct Artist* artists, int artistCount, char** filteringNames, int filNCount, struct DateTime filteringStartDate, struct DateTime filteringEndDate, int* count)
{
	struct Artist* foundArtits = (struct Artist*)malloc(sizeof(struct Artist) * artistCount);
	(*count) = 0;

	if (filteringNames != NULL)
	{
		for (size_t i = 0; i < artistCount; i++)
		{
			for (size_t j = 0; j < filNCount; j++)
			{
				if (strstr(artists[i].name, filteringNames[j]) != NULL)
				{
					foundArtits[(*count)++] = artists[i];
					break;
				}
			}
		}
	}
	else
	{
		for (size_t i = 0; i < artistCount; i++)
		{
			if (CheckDate(artists[i].birthDate, filteringStartDate) == 1 && CheckDate(artists[i].birthDate, filteringEndDate) == -1)
			{
				foundArtits[(*count)++] = artists[i];
			}
		}
	}

	return foundArtits;
}