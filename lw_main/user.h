#pragma once
#include "stdio.h"
#include "string.h"
#include "stringHelper.h"
#include "structures.h"
#include "dos.h"

#define LOGIN_OR_PASSWORD_NOT_CORRECT -1

typedef struct User User;
typedef struct Login Login;

unsigned long CreateHash(char* str, unsigned long hash)
{
	int c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c;

	return hash;
}

bool CheckHash(unsigned long hashPassword, unsigned long hash, char* password)
{
	if (CreateHash(password, hash) == hashPassword)
	{
		return true;
	}
	return false;
}

User* GetUsersFromFile(char* fileName, int* length)
{
	User* users = (User*)malloc(sizeof(User) * 0);
	char buffer[10000];
	buffer[0] = '\0';

	FILE* file = fopen(fileName, "r");

	char elem;
	int count = 0;
	while (fread(&elem, 1, 1, file))
	{
		buffer[count++] = elem;
	}
	fclose(file);
	buffer[count] = '\0';

	int size = 0;

	char splitted[100][100];

	char separator = '\n';
	int pos = 0;
	int retPos = 0;
	while (buffer[pos] != '\0')
	{
		char* tempStr = (char*)malloc(sizeof(char) * 100);

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

		users = (User*)realloc(users, sizeof(User) * (i + 1));
		users[i].login.login = (char*)malloc(sizeof(char));
		
		strcpy(users[i].login.login, splittedUser[0]);
		users[i].login.password = strtol(splittedUser[1], (char**)NULL, 10);
		users[i].login.hashSalt = strtol(splittedUser[2], (char**)NULL, 10);
		users[i].permission = (int)strtol(splittedUser[3], (char**)NULL, 10);
	}
	(*length) = size;
	return users;
}

Login SetLogin(char* login, char* password)
{
	Login login_user;
	login_user.login = login;
	login_user.hashSalt = rand() % 9999 + 1000;
	login_user.password = CreateHash(password, login_user.hashSalt);

	return login_user;
}

User SetNewUser(char* login, char* password, int permission)
{
	User newUser;

	newUser.login = SetLogin(login, password);
	newUser.permission = permission;

	return newUser;
}

User ChangeUserPermission(int permission, User user)
{
	if (permission > 0 && permission < 3)
	{
		user.permission = permission;
	}

	return user;
}

User ChangeLoginPassword(char* login, char* password, User user)
{
	user.login = SetLogin(login, password);

	return user;
}

User LoginIn(char* fileName, char* login, char* password)
{
	int length = 0;
	User* users = GetUsersFromFile(fileName, &length);

	for (size_t i = 0; i < length; i++)
	{
		if (strcmp(users[i].login.login, login) == 0)
		{
			if (CheckHash(users[i].login.password, users[i].login.hashSalt, password))
			{
				return users[i];
			}
			else
			{
				break;
			}
		}
	}

	User userFromFile;
	userFromFile.permission = LOGIN_OR_PASSWORD_NOT_CORRECT;

	return userFromFile;
}

char* CreateUserString(User user)
{
	char* buffer = (char*)malloc(sizeof(char) * 1);
	buffer[0] = '\0';

	buffer = Concat(buffer, user.login.login);
	buffer = Concat(buffer, ";");

	buffer = Concat(buffer, NumberToString(user.login.password));
	buffer = Concat(buffer, ";");

	buffer = Concat(buffer, NumberToString(user.login.hashSalt));
	buffer = Concat(buffer, ";");

	buffer = Concat(buffer, NumberToString(user.permission));
	buffer = Concat(buffer, "\n");

	return buffer;
}

void AddUserInFile(char* fileName, User user)
{
	char* buffer = CreateUserString(user);

	FILE* file = fopen(fileName, "a+");
	fwrite(buffer, sizeof(char), strlen(buffer), file);
	fclose(file);
}