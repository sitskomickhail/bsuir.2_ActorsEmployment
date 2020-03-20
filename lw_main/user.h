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

bool CheckPassword(unsigned long hashPassword, unsigned long hash, char* password)
{
	if (CreateHash(password, hash) == hashPassword)
	{
		return true;
	}
	return false;
}

Login SetLogin(char* login, char* password)
{
	Login login_artist;
	login_artist.login = login;
	login_artist.hashSalt = rand() % 9999 + 1000;
	login_artist.password = CreateHash(password, login_artist.hashSalt);

	return login_artist;
}

User SetNewUser(char* login, char* password, char* name, int permission)
{
	User newUser;

	if (strlen(name) > 0)
	{
		newUser.name = name;
	}

	newUser.login = SetLogin(login, password);
	newUser.permission = permission;

	return newUser;
}

User ChangeUserName(char* name, User user)
{
	if (strlen(name) > 0)
	{
		strcmp(user.name, name);
	}

	return user;
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

User LoginIn(FILE* file, char* login, char* password)
{
	User userFromFile;

	while (fread(&userFromFile, sizeof(User), 1, file))
	{
		if (!strcmp(userFromFile.login.login, login))
		{
			if (CheckPassword(userFromFile.login.password, userFromFile.login.hashSalt, password))
			{
				return userFromFile;
			}
			else
			{
				break;
			}
		}
	}

	userFromFile.permission = LOGIN_OR_PASSWORD_NOT_CORRECT;
	return userFromFile;
}

void AddUserInFile(FILE* file, User user)
{
	fwrite(&user, sizeof(User), 1, file);
}

void AddUserInFileWithCount(FILE* file, User* users, int usersCount)
{
	fwrite(users, sizeof(User), usersCount, file);
}

User* GetUsersFromFile(FILE* file)
{
	User* users = (User*)malloc(sizeof(User) * 0);
	User user;
	int index = 0;

	while (fread(&user, sizeof(User), 1, file))
	{
		users = (User*)realloc(users, index + 1);
		users[index++] = user;
	}	

	return users;
}