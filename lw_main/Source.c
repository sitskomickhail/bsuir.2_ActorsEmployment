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
	SimpleUser,
	SUPERADMIN = 9999
};

char* String_WriteLine(char*);
char* Password_WriteLine(char*);
long Number_WriteLine(char*);

int main()
{
	char* displayString = "Enter login credentials!\nLogin: ";

	char* login = String_WriteLine(displayString);
	displayString = concat(displayString, login);
	displayString = concat(displayString, "\nPassword: ");

	char* password = Password_WriteLine(displayString);

	User currentUser = LoginIn(LOGIN_FILE, login, password);
	
	switch (currentUser.permission)
	{
	case Admin:
		printf_s("You logged in as Administrator");
		break;
	case SimpleUser:
		printf_s("You logged in as User");
		break;
	case SUPERADMIN:
		printf_s("Welcome! You are a SUPER ADMIN");
		break;
	default:
		printf_s("Login or password are not correct!");
		break;
	}


	int artistCount = 0, perfomanceCount = 0, artPerfomancesCount = 0;

	Artist* artists = (Artist*)malloc(sizeof(Artist) * 1);
	Perfomance* perfomances = (Perfomance*)malloc(sizeof(Perfomance) * 1);
	ArtPerf* artPerfomances = (ArtPerf*)malloc(sizeof(ArtPerf) * 1);

	return _getch();
}

#pragma region AllMenu
char* AdminMainMenu()
{
	return "1 - User menu\n2 - Artist menu\n3 - Perfomance menu\nChoose: ";
}

char* UserMenu()
{
	return "1 - Artist menu\n2 - Perfomance menu\nChoose: ";
}
#pragma endregion


#pragma region User_Controllers

#pragma endregion


#pragma region Admin_Controllers
char* AdminUserMenu()
{
	return "1 - Add new user\n2 - Edit user";
}

char* AdminUserMenu_EditUser()
{
	return "1 - Edit name\n2 - Edit permission";
}

char* AdminArtistMenu()
{
	return "1) Add new Artist\n2) Edit Artist\n 3) Delete artist\n4) Set artist to perfomance\n5) Show all artits\nChoose: ";
}

char* AdminPerfomanceMenu()
{
	return "1) Add new Perfomance\n2) Edit perfomance\n3) Delete perfomance\n4) Show all perfomances\nChoose: ";
}
#pragma endregion

#pragma region SuperAdmin_Controllers
char* SuperAdminUserMenu()
{
	return "1 - Add new user\n2 - Edit user\n3 - Delete user";
}

char* SuperAdminUserMenu_EditUser()
{
	return "1 - Edit name\n2 - Edit permission\n3 - Edit login\n4 - Edit password";
}
#pragma endregion


char* String_WriteLine(char* displayString)
{
	int size = 1;
	char* str = (char*)malloc(size);

	printf_s("%s", displayString);
	while (true)
	{
		char symbol = _getch();
		if ((int)symbol == 13 || symbol == '\r')
		{
			break;
		}

		if ((int)symbol > 31 && (int)symbol < 127)
		{
			str[size - 1] = symbol;
			str = (char*)realloc(str, ++size);
			//printf_s("%c", symbol);
		}
		else if ((int)symbol == 8)
		{
			if (size == 1)
			{
				str[0] = '\0';
			}
			else
			{
				str = (char*)realloc(str, --size);
			}
		}

		system("cls");
		printf_s("%s", displayString);
		str[size - 1] = '\0';
		printf_s("%s", str);
	}

	return str;
}

long Number_WriteLine(char* displayString)
{
	int size = 1;
	char* str = (char*)malloc(size);

	printf_s("%s", displayString);
	while (true)
	{
		char symbol = _getch();
		if ((int)symbol == 13 || symbol == '\r')
		{
			break;
		}

		if ((int)symbol > 47 && (int)symbol < 58)
		{
			str[size - 1] = symbol;
			str = (char*)realloc(str, ++size);
			//printf_s("%c", symbol);
		}
		else if ((int)symbol == 8)
		{
			if (size == 1)
			{
				str[0] = '\0';
			}
			else
			{
				str = (char*)realloc(str, --size);
			}
		}

		system("cls");
		printf_s("%s", displayString);
		str[size - 1] = '\0';
		printf_s("%s", str);
	}

	return FromStringToNumber(str);
}

char* Password_WriteLine(char* displayString)
{
	int size = 1;
	char* str = (char*)malloc(size);
	char* silentStr = (char*)malloc(size);

	printf_s("%s", displayString);
	while (true)
	{
		char symbol = _getch();
		if ((int)symbol == 13 || symbol == '\r')
		{
			break;
		}

		if ((int)symbol > 32 && (int)symbol < 127)
		{
			str[size - 1] = symbol;
			silentStr[size - 1] = '*';
			str = (char*)realloc(str, ++size);
			silentStr = (char*)realloc(silentStr, ++size);			
		}
		else if ((int)symbol == 8)
		{
			if (size == 1)
			{
				str[0] = '\0';
				silentStr[0] = '\0';
			}
			else
			{
				silentStr = (char*)realloc(silentStr, --size);
				str = (char*)realloc(str, --size);
			}
		}

		system("cls");
		printf_s("%s", displayString);
		str[size - 1] = '\0';
		silentStr[size - 1] = '\0';
		printf_s("%s", silentStr);
	}

	return str;
}