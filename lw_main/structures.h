#pragma once
struct DateTime
{
	int year;
	int month;
	int day;
	int hours;
	int minutes;
};

struct Login
{
	char* login;
	unsigned long password;
	unsigned long hashSalt;
};

struct User
{
	int permission;
	struct Login login;
};

struct Artist
{
	int id;
	char* name;
	struct DateTime birthDate;
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
	int perfomanceId;
	char* role;
	long salary;
};