#pragma once
#include "stdio.h"
#include "string.h"
#include "stringHelper.h"
#include "structures.h"

struct ArtistPerfomances* DeleteArtistPerfomance(int artistId, int perfomanceId, struct ArtistPerfomances* artistPerfomances, int* artPerfCount)
{
	for (size_t i = 0; i < *artPerfCount; i++)
	{
		if (artistId != -1)
		{
			if (artistId == artistPerfomances[i].artistId)
			{
				artistPerfomances[*artPerfCount - 1].artistId = artistPerfomances[i].artistId;
				artistPerfomances[*artPerfCount - 1].perfomanceId = artistPerfomances[i].perfomanceId;
				artistPerfomances[*artPerfCount - 1].salary = artistPerfomances[i].salary;
				(artistPerfomances[*artPerfCount - 1].role, artistPerfomances[i].artistId);

				*artPerfCount--;
				artistPerfomances = (struct ArtistPerfomances*)realloc(artistPerfomances, sizeof(struct ArtistPerfomances) * (*artPerfCount));
				i--;
				continue;
			}
		}

		if (perfomanceId != -1)
		{
			if (perfomanceId == artistPerfomances[i].perfomanceId)
			{
				artistPerfomances[*artPerfCount - 1].artistId = artistPerfomances[i].artistId;
				artistPerfomances[*artPerfCount - 1].perfomanceId = artistPerfomances[i].perfomanceId;
				artistPerfomances[*artPerfCount - 1].salary = artistPerfomances[i].salary;
				(artistPerfomances[*artPerfCount - 1].role, artistPerfomances[i].artistId);

				*artPerfCount--;
				artistPerfomances = (struct ArtistPerfomances*)realloc(artistPerfomances, sizeof(struct ArtistPerfomances) * (*artPerfCount));
				i--;
			}
		}
	}

	return artistPerfomances;
}

struct ArtistPerfomances InitArtPerf(int artistId, int perfId, char* role, long salary)
{
	struct ArtistPerfomances artPerf;
	artPerf.artistId = artistId;
	artPerf.perfomanceId = perfId;
	artPerf.role = role;
	artPerf.salary = salary;

	return artPerf;
}

struct ArtistPerfomances* GetArtPerfFromFile(char* fileName, int* count)
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

	struct ArtistPerfomances* artPerfs = (struct ArtistPerfomances*)malloc(sizeof(struct ArtistPerfomances));

	int size = 0;

	char splitted[100][100];

	char separator = '\n';
	int pos = 0;
	int retPos = 0;
	while (buffer[pos] != '\0')
	{
		char tempStr[200];

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


		artPerfs = (struct ArtistPerfomances*)realloc(artPerfs, sizeof(struct ArtistPerfomances) * (i + 1));
		artPerfs[i].artistId = (int)strtol(splittedUser[0], (char**)NULL, 10);
		artPerfs[i].perfomanceId = (int)strtol(splittedUser[1], (char**)NULL, 10);
		artPerfs[i].salary = (int)strtol(splittedUser[2], (char**)NULL, 10);

		artPerfs[i].role = (char*)malloc(sizeof(char));
		strcpy(artPerfs[i].role, splittedUser[3]);
		(*count) += 1;
	}

	return artPerfs;
}

int SetArtPerfInFile(char* fileName, struct ArtistPerfomances* artPerfomances, int count)
{
	if (artPerfomances == NULL)
		return 0;

	char* buffer = (char*)malloc(0);
	buffer[0] = '\0';

	for (size_t i = 0; i < count; i++)
	{
		buffer = Concat(buffer, NumberToString(artPerfomances[i].artistId));
		buffer = Concat(buffer, (char*)";");
		buffer = Concat(buffer, NumberToString(artPerfomances[i].perfomanceId));
		buffer = Concat(buffer, (char*)";");
		buffer = Concat(buffer, NumberToString(artPerfomances[i].salary));
		buffer = Concat(buffer, (char*)";");
		buffer = Concat(buffer, artPerfomances[i].role);
		buffer = Concat(buffer, (char*)";");
		buffer = Concat(buffer, (char*)"\n");
	}

	FILE* file;
	file = fopen(fileName, "w");
	fwrite(buffer, sizeof(char), strlen(buffer), file);
	fclose(file);

	return 1;
}

enum FindBy
{
	Art = 1,
	Perf,
	Salary,
	Role
};

struct ArtistPerfomances* FindArtPerfByParam(struct ArtistPerfomances* artPerfomances, int artPerfCount, struct Artist* artists, int artCount,
	struct Perfomance* perfomances, int perfCount, char* name, char* title, long salary, char* role, int findBy, int* foundCount)
{
	(*foundCount) = 0;
	struct ArtistPerfomances* foundPerfomances = (struct ArtistPerfomances*)malloc(0);

	switch (findBy)
	{
	case Art:
	{
		for (size_t i = 0; i < artCount; i++)
		{
			if (strcmp(artists[i].name, name) == 0)
			{
				for (size_t j = 0; j < artPerfCount; j++)
				{
					if (artists[i].id == artPerfomances[j].artistId)
					{
						(*foundCount)++;
						foundPerfomances = (struct ArtistPerfomances*)realloc(foundPerfomances, sizeof(struct ArtistPerfomances*) * (*foundCount));
						foundPerfomances[(*foundCount) - 1] = artPerfomances[j];
					}
				}
			}
		}

		break;
	}
	case Perf:
	{
		for (size_t i = 0; i < perfCount; i++)
		{
			if (strcmp(perfomances[i].title, title) == 0)
			{
				for (size_t j = 0; j < artPerfCount; j++)
				{
					if (perfomances[i].id == artPerfomances[j].perfomanceId)
					{
						(*foundCount)++;
						foundPerfomances = (struct ArtistPerfomances*)realloc(foundPerfomances, sizeof(struct ArtistPerfomances*) * (*foundCount));
						foundPerfomances[(*foundCount) - 1] = artPerfomances[j];
					}
				}
			}
		}

		break;
	}
	case Salary:
	{
		for (size_t i = 0; i < artPerfCount; i++)
		{
			if (artPerfomances[i].salary == salary)
			{
				(*foundCount)++;
				foundPerfomances = (struct ArtistPerfomances*)realloc(foundPerfomances, sizeof(struct ArtistPerfomances*) * (*foundCount));
				foundPerfomances[(*foundCount) - 1] = artPerfomances[i];
			}
		}

		break;
	}
	case Role:
	{
		for (size_t i = 0; i < artPerfCount; i++)
		{
			if (strcmp(artPerfomances[i].role, role) == 0)
			{
				(*foundCount)++;
				foundPerfomances = (struct ArtistPerfomances*)realloc(foundPerfomances, sizeof(struct ArtistPerfomances*) * (*foundCount));
				foundPerfomances[(*foundCount) - 1] = artPerfomances[i];
			}
		}

		break;
	}
	}

	return foundPerfomances;
}