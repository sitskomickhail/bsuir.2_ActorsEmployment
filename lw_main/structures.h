#pragma once
struct DateTime
{
	int year;
	int month;
	int day;
};

struct Login
{
	char* login;
	unsigned long password;
	unsigned long hashSalt;
};

struct Artist
{
	int id;
	char* name;
	struct DateTime birthDate;
	int perfomanceCount;
	struct Login login;
};

struct Perfomance
{
	int id;
	char* title;
	int ticketCount;
	long ticketCost;
	struct DateTime time;
};

struct ArtistPerfomances
{
	int artistId;
	struct Artist artist;
	int perfomanceId;
	struct Perfomance perfomance;
	char* role;
	long salary;
};