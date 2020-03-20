#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "string.h"
#include "stringHelper.h"
#include "structures.h"

Artist ChangeArtistName(char* name, Artist artist)
{
	if (name != NULL)
	{
		strcmp(artist.name, name);
	}

	return artist;
}

Artist SetNewArtistInfo(char* name, DateTime birthDate, Artist prevArtist)
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