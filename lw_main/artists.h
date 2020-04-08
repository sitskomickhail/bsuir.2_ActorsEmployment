#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "string.h"
#include "stringHelper.h"
#include "structures.h"
#include "stdio.h"

struct Artist ChangeArtistName(char* name, struct Artist artist)
{
	if (name != NULL)
	{
		strcmp(artist.name, name);
	}

	return artist;
}

struct Artist SetNewArtistInfo(char* name, DateTime birthDate, struct Artist prevArtist)
{
	int id;
	if (strlen(prevArtist.name) == 0) { id = 0; }
	else { id = prevArtist.id++; }

	Artist artist;
	artist.id = id;
	strcmp(artist.name, name);
	artist.birthDate = birthDate;
	
	return artist;
}

struct Artist InitArtist(struct Artist* prevArtist, char* artName)
{
	int id = 0;
	if (prevArtist != NULL)
	{
		id = prevArtist->id + 1;
	}

	struct Artist artist;

	artist.id = id;
	artist.name = artName;

	return artist;
}

struct Artist* GetArtistsFromFile(char* fileName, int* count)
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

	struct Artist* artists = (struct Artist*)malloc(0);

	int size = 0;
	char** splitted = Split(buffer, '\n', &size);

	for (size_t i = 0; i < size; i++)
	{
		int val = 0;
		char** splittedUser = Split(splitted[i], ';', &val);

		artists = (struct Artist*)realloc(artists, sizeof(struct Artist) * (i + 1));
		artists[i].id = FromStringToNumber(splittedUser[0]);
		artists[i].name = (char*)malloc(1);
		artists[i].name[0] = '\0';
		artists[i].name = Concat(artists[i].name, splittedUser[1]);
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
		buffer = Concat(buffer, (char*)"\n");
	}

	FILE* file;
	file = fopen(fileName, "w");
	fwrite(buffer, sizeof(char), strlen(buffer), file);
	fclose(file);

	return 1;
}

void AddArtistInFile(char* fileName, struct Artist perfomance);
int DeleteArtist(struct Artist perfomanceForDelete, struct Artist* perfomances, struct ArtistPerfomances* artistPerfomances);