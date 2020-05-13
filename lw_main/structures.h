#pragma once
struct DateTime
{
	int year;	// год
	int month;	// месяц
	int day;	// день
	int hours;	// час
	int minutes;// минуты
};

struct Login
{
	char* login;				// Логин
	unsigned long password;		// Пароль
	unsigned long hashSalt;		// Хэш
};

struct User
{
	int permission;		// Право доступа
	struct Login login;	// Структурная переменная логина
};

struct Artist
{
	int id;		// Уникальный ключ
	char* name;	// Имя
	struct DateTime birthDate; // Структурная переменная Даты
};

struct Perfomance
{
	int id;		// Уникальный ключ
	char* title;	// Название представления
	int ticketCount;// Количество билетов
	long ticketCost;// Стоимость билетов
	struct DateTime time; // Время проведения представления
};

struct ArtistPerfomances
{
	int artistId;		// Уникальный ключ артиста
	int perfomanceId;	// Уникальный ключ представления
	char* role;			// Роль участника представления
	long salary;		// Зарплата
};