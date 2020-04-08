#pragma once
#include "stdio.h"
#include "string.h"
#include "stringHelper.h"
#include "structures.h"

struct ArtistPerfomances InitArtPerf(struct ArtistPerfomances* artist, int artistId, int perfId, char* role, long salary)
{

}

struct ArtistPerfomances* GetArtPerfFromFile(char* fileName)
{
	FILE* file;
	file = fopen(fileName, "r");

	int count = 0;
	struct ArtistPerfomances* artistPerf = (struct ArtistPerfomances*)malloc(0);

	struct ArtistPerfomances tempArtPerf;
	while (fread(&tempArtPerf, sizeof(struct ArtistPerfomances), 1, file))
	{
		artistPerf = (struct ArtistPerfomances*)realloc(artistPerf, sizeof(struct ArtistPerfomances) * ++count);
		artistPerf[count - 1] = tempArtPerf;
	}
	fclose(file);

	return artistPerf;
}

int SetArtPerfInFile(char* fileName, struct ArtistPerfomances* artPerfomances)
{

}

void AddArtistPerfomanceInFile(char* fileName, struct ArtistPerfomances* perfomance);