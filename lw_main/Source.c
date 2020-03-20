#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "locale.h"
#include "structures.h"
#include "datetime.h"
#include "stringHelper.h"
#include "user.h"

#define ARTISTS_FILE "artistFile.txt"
#define PERFOMANCE_FILE "perfomanceFile.txt"
#define AP_ENTITY_FILE "artistPerfomanceFile.txt"
#define LOGIN_FILE "loginFile.txt"

typedef struct DateTime DateTime;
typedef struct Login Login;
typedef struct Artist Artist;
typedef struct Perfomance Perfomance;
typedef struct ArtistPerfomances ArtPerf;
typedef struct User User;

enum Permissions
{
	Admin = 1,
	SimpleUser
};

int main()
{
	setlocale(LC_ALL, "rus");

	int artistCount = 0, perfomanceCount = 0, artPerfomancesCount = 0;

	Artist* artists = (Artist*)malloc(sizeof(Artist) * 1);
	Perfomance* perfomances = (Perfomance*)malloc(sizeof(Perfomance) * 1);
	ArtPerf* artPerfomances = (ArtPerf*)malloc(sizeof(ArtPerf) * 1);

	User userAdmin = SetNewUser("tempAdmin", "pa$$w0rd", "simple name", 1);
	User user = SetNewUser("tempUser", "pa$$w0rd", "simple name", 2);
	
	FILE* loginFile = fopen(LOGIN_FILE, "w+");
	AddUserInFile(loginFile, userAdmin);
	AddUserInFile(loginFile, user);

	rewind(loginFile);

	User currentUser = LoginIn(loginFile, "tempwUser", "pa$$w0rd");
	if (currentUser.permission == Admin)
	{
		printf_s("You logged in as Administrator");
	}
	else if (currentUser.permission == SimpleUser)
	{
		printf_s("You logged in as User");
	}
	else
	{
		printf_s("Login or password are not correct!");
	}
	//User* users = GetUsersFromFile(loginFile);
	fclose(loginFile);

	return _getch();
}

ArtPerf GetArtistPerfomancesFromFile(FILE* file)
{
	ArtPerf artPerf;

	fscanf(file, "%d", &artPerf.artistId);
	fscanf(file, "%d", &artPerf.perfomanceId);
	fscanf(file, "%s", &artPerf.role);
	fscanf(file, "%l", &artPerf.salary);

	return artPerf;
}

void SetArtistPerfomancesInFile(FILE file, ArtPerf artPerf)
{
	fprintf(&file, "%d ", artPerf.artistId);
	fprintf(&file, "%d ", artPerf.perfomanceId);
	fprintf(&file, "%s ", artPerf.role);
	fprintf(&file, "%l\n", artPerf.salary);
}

