#pragma once
#include "stdio.h"
#include "string.h"
#include "stringHelper.h"
#include "structures.h"

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

User* GetUsersFromFile(char* fileName)
{
	User* users = (User*)malloc(sizeof(User) * 0);
	char* buffer = (char*)malloc(1000);
	buffer[0] = '\0';

	FILE* file = fopen(fileName, "r");

	char elem;
	int count = 0;
	while (fread(&elem, 1, 1, file))
	{
		buffer[count++] = elem;
	}
	
	buffer = (char*)realloc(buffer, count + 1);
	buffer[count] = '\0';

	fclose(file);

	int size = 0;
	char** splitted = Split(buffer, '\n', &size);

	//int size = sizeof(splitted);

	for (size_t i = 0; i < size; i++)
	{
		char** splittedUser = Split(splitted[i], ';', 0);

		users = (User*)realloc(users, i + 1);
		users[i].login.login = (char*)malloc(1);
		users[i].login.login[0] = '\0';

		users[i].login.login = Concat(users[i].login.login, splittedUser[0]);
		users[i].login.password = FromStringToNumber(splittedUser[1]);
		users[i].login.hashSalt = FromStringToNumber(splittedUser[2]);
		users[i].permission = FromStringToNumber(splittedUser[3]);
	}

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
	FILE* file = fopen(fileName, "a+");

	User* users = GetUsersFromFile(fileName);

	for (size_t i = 0; i < (int)(sizeof(users) / sizeof(User)); i++)
	{
		if (CheckHash(users[i].login.login, users[i].login.hashSalt, login))
		{
			if (CheckHash(users[i].login.password, users[i].login.hashSalt, password))
			{
				fclose(file);
				return users[i];
			}
			else
			{
				break;
			}
		}
	}

	/*while (fread_s(&userFromFile, sizeof(userFromFile), sizeof(User), 1, file))
	{
		if (CheckHash(userFromFile.login.login, userFromFile.login.hashSalt, login))
		{
			if (CheckHash(userFromFile.login.password, userFromFile.login.hashSalt, password))
			{
				fclose(file);
				return userFromFile;
			}
			else
			{
				break;
			}
		}
	}*/

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

void SetUsersInFile(char* fileName, User* users, int usersCount)
{
	char* buffer = (char*)malloc(sizeof(char) * 1);
	buffer[0] = '\0';

	for (size_t i = 0; i < usersCount; i++)
	{
		buffer = Concat(buffer, CreateUserString(users[i]));
	}

	FILE* file = fopen(fileName, "w+");
	fwrite(buffer, sizeof(char), strlen(buffer), file);
	fclose(file);
}