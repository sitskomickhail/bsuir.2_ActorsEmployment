#pragma once
#include "stdio.h"
#include "string.h"
#include "stringHelper.h"
#include "structures.h"

typedef struct ArtistPerfomances ArtPerf;


ArtPerf* GetArtistPerfomancesFromFile(char* fileName, int& count)
{
	count = 0;
	FILE* file = fopen(fileName, "r");
	if (file == NULL)
	{
		FILE* file = fopen(fileName, "w");
		fclose(file);

		return NULL;
	}

	ArtPerf* artPerf = (ArtPerf*)malloc(sizeof(ArtPerf) * count);
	ArtPerf tempAP;

	while (fread(&tempAP, sizeof(ArtPerf), 1, file))
	{
		artPerf = (ArtPerf*)realloc(artPerf, ++count * sizeof(ArtPerf));
		artPerf[count - 1] = tempAP;
	}

	fclose(file);

	return artPerf;
}

void SetArtistPerfomancesInFile(char* fileName, ArtPerf* artPerf, int count)
{
	FILE* file = fopen(fileName, "w");
	fwrite(artPerf, sizeof(ArtPerf), count, file);
	fclose(file);
}

void AddArtistPerfomanceInFile(char* fileName, ArtPerf artPerf)
{
	FILE* file = fopen(fileName, "a");
	fwrite(&artPerf, sizeof(ArtPerf), 1, file);
	fclose(file);
}