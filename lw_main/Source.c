#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "locale.h"
#include "datetime.h"
#include "structures.h"
#include "stringHelper.h"

#define LOGIN_FILE "loginFile.txt"
#define ARTISTS_FILE "artistFile.txt"
#define PERFOMANCE_FILE "perfomanceFile.txt"
#define AP_ENTITY_FILE "artistPerfomanceFile.txt"

typedef struct DateTime DateTime;
typedef struct Login Login;
typedef struct Artist Artist;
typedef struct Perfomance Perfomance;
typedef struct ArtistPerfomances ArtPerf;

enum Permissions
{
	Admin,
	User
};

int main()
{
	setlocale(LC_ALL, "rus");

	int value = 3;
	while (value)
	{
		printf_s("1) Войти под администратором\n");
		printf_s("2) Войти как пользователь");
		scanf_s("%d", &value);

		switch (value)
		{
		case 1:

			break;
		case 2:

			break;
		default:
			printf_s("Нет такого варианта!");
			break;
		}
	}

	return _getch();
}