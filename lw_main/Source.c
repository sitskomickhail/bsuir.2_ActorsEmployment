#define _CRT_SECURE_NO_WARNINGS
#include "locale.h"
#include "stdbool.h"
#include "structures.h"
#include "stdlib.h"
#include "datetime.h"
#include "stringHelper.h"
#include "user.h"
#include "artists.h"
#include "artistPerfomance.h"
#include "perfomances.h"

#define ARTISTS_FILE "artistFile.txt"
#define PERFOMANCE_FILE "perfomanceFile.txt"
#define ARTPERF_FILE "artistPerfomanceFile.txt"
#define LOGIN_FILE "loginFile.txt"

#define EN

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

char* String_WriteLine();
char* Password_WriteLine(char*);
int CaseVariant_WriteLine(int);
DateTime DateTime_WriteLine(bool);


char* AdminMainMenu();
char* UserMainMenu();


char* AdminArtistMenu();
char* EditArtistMenu();
char* SortArtistMenu();
char* FindArtistMenu();
void ShowArtists(Artist*, int);


char* AdminPerfomanceMenu();
char* EditPerfomanceMenu();
char* SortPerfomanceMenu();
char* FindPerfomanceMenu();
void ShowPerfomances(Perfomance*, int);


char* AdminArtPerfMenu();
char* EditArtPerfMenu();
char* FindArtPerfMenu();
void ShowArtistPerfomances(ArtPerf*, int, Artist*, int, Perfomance*, int);


int main()
{
	srand(time(NULL));

#ifdef RU
	setlocale(LC_ALL, "rus");
#endif // RU

	//AddUserInFile(LOGIN_FILE, SetNewUser("user", "user", 2));
	//AddUserInFile(LOGIN_FILE, SetNewUser("admin", "admin", 1));

	while (1)
	{
		system("cls");
#ifdef EN
		printf_s("1 - Login\n2 - Exit\nChoose: ");
#endif // EN
#ifdef RU
		printf_s("1 - Войти в систему\n2 - Выход: ");
#endif // RU

		bool value = true;
		switch (CaseVariant_WriteLine(2))
		{
		case 1:
		{
			system("cls");

#ifdef EN
			char* displayString = "Enter login credentials!\nLogin: ";
			printf_s(displayString);
			char* login = String_WriteLine();
			displayString = Concat(displayString, login);
			displayString = Concat(displayString, "\nPassword: ");
			char* password = Password_WriteLine(displayString);
#endif // EN

#ifdef RU
			char* displayString = "Введите идентификационные данные!\nЛогин: ";
			printf_s(displayString);
			char* login = String_WriteLine();
			displayString = Concat(displayString, login);
			displayString = Concat(displayString, "\nПароль: ");
			char* password = Password_WriteLine(displayString);
#endif // RU


			User currentUser = LoginIn(LOGIN_FILE, login, password);
			system("cls");
			switch (currentUser.permission)
			{
			case Admin:
			{
				int artistCount = 0, perfomanceCount = 0, artPerfomancesCount = 0;

				Artist* artists = GetArtistsFromFile(ARTISTS_FILE, &artistCount);
				Perfomance* perfomances = GetPerfomancesFromFile(PERFOMANCE_FILE, &perfomanceCount);
				ArtPerf* artPerfomances = GetArtPerfFromFile(ARTPERF_FILE, &artPerfomancesCount);

#ifdef EN
				printf_s("You logged in as Administrator\n\n");
#endif // EN
#ifdef RU
				printf_s("Вы вошли как администратор\n\n");
#endif // RU
				while (value)
				{
					printf_s(AdminMainMenu());
					switch (CaseVariant_WriteLine(5))
					{
					case 1: // Работа с артистами
					{
						system("cls");
						while (value)
						{
							printf_s(AdminArtistMenu());
							switch (CaseVariant_WriteLine(8))
							{

							case 1: // Добавление артиста
							{
								system("cls");
								char* name;
								DateTime birthDate;

#ifdef EN
								printf_s("Enter artist's name: ");
								name = String_WriteLine();
								printf_s("\nEnter birth date...\n");
								birthDate = DateTime_WriteLine(true);
#endif // EN
#ifdef RU
								printf_s("Введите имя артиста: ");
								name = String_WriteLine();
								printf_s("\nВведите дату рождения...\n");
								birthDate = DateTime_WriteLine(true);
#endif // RU

								artists = (Artist*)realloc(artists, sizeof(Artist) * (artistCount + 1));
								artists[artistCount++] = SetNewArtistInfo(name, birthDate, artists, artistCount);
#ifdef EN
								printf_s("Artist added");
#endif // EN
#ifdef RU
								printf_s("Артист добавлен...");
#endif // RU
								SetArtistsInFile(ARTISTS_FILE, artists, artistCount);
								system("pause");
								break;
							}
							case 2: // Изменение артиста
							{
								system("cls");
								printf_s(EditArtistMenu());
								switch (CaseVariant_WriteLine(3))
								{
								case 1: //Изменение имени
								{
									system("cls");
									ShowArtists(artists, artistCount);

#ifdef EN
									printf_s("Choose artist for editing: ");
#endif // EN
#ifdef RU
									printf_s("Выберите изменяемого артиста: ");
#endif // RU
									int variant = atoi(String_WriteLine());
									while (variant < 1 || variant > artistCount)
									{
#ifdef EN
										printf_s("Uncorrect choose. Enter again: ");
#endif // EN
#ifdef RU
										printf_s("Некорректный выбор. Введите снова: ");
#endif // RU
										variant = atoi(String_WriteLine());
									}
#ifdef EN
									printf_s("Enter new artist name: ");
#endif // EN
#ifdef RU
									printf_s("Введите новое имя артиста: ");
#endif // RU

									char* newName = String_WriteLine();
									strcpy(artists[variant - 1].name, newName);
									SetArtistsInFile(ARTISTS_FILE, artists, artistCount);
#ifdef EN
									printf_s("Name succesfully changed...");
#endif // EN
#ifdef RU
									printf_s("Имя успешно изменено...");
#endif // Ru
									system("pause");
									break;
								}
								case 2: //Изменение даты рождения
								{
									system("cls");
									ShowArtists(artists, artistCount);

#ifdef EN
									printf_s("Choose artist for editing: ");
#endif // EN
#ifdef RU
									printf_s("Выберите изменяемого артиста: ");
#endif // RU
									int variant = atoi(String_WriteLine());
									while (variant < 1 || variant > artistCount)
									{
#ifdef EN
										printf_s("Uncorrect choose. Enter again: ");
#endif // EN
#ifdef RU
										printf_s("Некорректный выбор. Введите снова: ");
#endif // RU
										variant = atoi(String_WriteLine());
									}
#ifdef EN
									printf_s("Enter new artist's birth date: ");
#endif // EN
#ifdef RU
									printf_s("Введите новую дату рождения артиста: ");
#endif // RU

									DateTime newDate = DateTime_WriteLine(true);
									artists[variant - 1].birthDate = newDate;
									SetArtistsInFile(ARTISTS_FILE, artists, artistCount);
#ifdef EN
									printf_s("Birth date succesfully changed...");
#endif // EN
#ifdef RU
									printf_s("Дата рождения успешно изменена...");
#endif // Ru
									system("pause");
									break;
								}
								case 3: //Выход
								{
									break;
								}
								}
								break;
							}
							case 3: // Удаление артиста
							{
								system("cls");
								ShowArtists(artists, artistCount);

#ifdef EN
								printf_s("Choose artist for deleting (0 - for cancelin): ");
#endif // EN
#ifdef RU
								printf_s("Выберите удаляемого артиста (0 - для отмены): ");
#endif // RU
								int variant = atoi(String_WriteLine());
								while (variant < 0 || variant > artistCount)
								{
#ifdef EN
									printf_s("Uncorrect choose. Enter again: ");
#endif // EN
#ifdef RU
									printf_s("Некорректный выбор. Введите снова: ");
#endif // RU
									variant = atoi(String_WriteLine());
								}

								if (variant == 0)
									break;

								artPerfomances = DeleteArtistPerfomance(artists[variant - 1].id, -1, artPerfomances, &artPerfomancesCount);
								artists[variant - 1].id = artists[artistCount - 1].id;
								artists[variant - 1].birthDate = artists[artistCount - 1].birthDate;
								strcpy(artists[variant - 1].name, artists[artistCount - 1].name);

								artistCount--;
								SetArtPerfInFile(ARTPERF_FILE, artPerfomances, artPerfomancesCount);
								SetArtistsInFile(ARTISTS_FILE, artists, artistCount);
#ifdef EN
								printf_s("Artist successfully deleted");
#endif // EN
#ifdef RU
								printf_s("Артист успешно удален");
#endif // RU

								system("pause");
								break;
							}
							case 4: // Сортировка артистов
							{
								system("cls");
								printf_s(SortArtistMenu());
								switch (CaseVariant_WriteLine(3))
								{
								case 1: // Сортировка по имени
								{
									artists = SortArtistsArray(artists, artistCount, 1);
#ifdef EN
									printf_s("\n\nSorted...");
#endif // EN
#ifdef RU
									printf_s("\n\nОтсортировано...");
#endif // RU
									system("pause");
									break;
								}
								case 2: // Сортировка по дате рождения
								{
									artists = SortArtistsArray(artists, artistCount, 2);
#ifdef EN
									printf_s("\n\nSorted...");
#endif // EN
#ifdef RU
									printf_s("\n\nОтсортировано...");
#endif // RU
									system("pause");
									break;
								}
								case 3: // Выход
								{
									break;
								}
								}
							}
							case 5: // Поиск артистов
							{
								char* name = NULL;
								system("cls");
								printf_s(FindArtistMenu());
								DateTime dateTime;
								dateTime.day = 0;
								switch (CaseVariant_WriteLine(3))
								{
								case 1: // Поиск по имени
								{
#ifdef EN
									printf_s("\nEnter artist's name for find: ");
#endif // EN
#ifdef RU
									printf_s("\nВведите искомое имя актера: ");
#endif // RU
									name = String_WriteLine();
									int findedCount = 0;
									Artist* findedArtists = FindArtistsByParams(artists, artistCount, 1, &findedCount, name, dateTime);
									ShowArtists(findedArtists, findedCount);
									system("pause");
									break;
								}
								case 2: // Поиск по дате рождения
								{
#ifdef EN
									printf_s("\nEnter artist's birth date for find\n");
#endif // EN
#ifdef RU
									printf_s("\nВведите дату рождения актера\n");
#endif // RU
									dateTime = DateTime_WriteLine(true);
									int findedCount = 0;
									Artist* findedArtists = FindArtistsByParams(artists, artistCount, 2, &findedCount, name, dateTime);
									ShowArtists(findedArtists, findedCount);
									system("pause");
									break;
								}
								case 3:
								{
									break;
								}
								}
								system("cls");
								break;
							}
							case 6: // Вывод артистов
							{
								system("cls");
								ShowArtists(artists, artistCount);
								system("pause");
								break;
							}
							case 7: // 5 самых востребованных актеров
							{

								break;
							}
							case 8: // Выход
							{
								value = false;
							}
							}
							system("cls");
						}
						value = true;
						break;
					}
					case 2: // Работа с представлениями
					{
						system("cls");
						while (value)
						{
							printf_s(AdminPerfomanceMenu());
							switch (CaseVariant_WriteLine(7))
							{
							case 1: // Добавление представления
							{
								system("cls");
								char* title = NULL;
								DateTime perfTime;
								perfTime.day = -1;
								int ticketCount = 0;
								int ticketCost = 0;
#ifdef EN
								printf_s("Enter perfomance title: ");
								title = String_WriteLine();

								printf_s("Enter ticket count for perfomance: ");
								ticketCount = atoi(String_WriteLine());
								while (ticketCount < 10)
								{
									printf_s("Uncorrect type. Ticket count must be number-value and 10 or more.\nEnter again:");
									ticketCount = atoi(String_WriteLine());
								}

								printf_s("Enter ticket cost for perfomance: ");
								ticketCost = atoi(String_WriteLine());
								while (ticketCost < 0)
								{
									printf_s("Uncorrect type. Ticket cost must be number-value and non-negative\nEnter again:");
									ticketCost = atoi(String_WriteLine());
								}

								printf_s("\nEnter perfomance date & time\n");
								perfTime = DateTime_WriteLine(false);
#endif // EN
#ifdef RU
								printf_s("Введите название представления: ");
								title = String_WriteLine();

								printf_s("Введите количество билетов на представление: ");
								ticketCount = atoi(String_WriteLine());
								while (ticketCount < 10)
								{
									printf_s("Некорректный ввод. Количество билетов должно записываться числом и в количестве 10 и более.\nВведите снова:");
									ticketCount = atoi(String_WriteLine());
								}

								printf_s("Введите стоимость билета на представление: ");
								ticketCost = atoi(String_WriteLine());
								while (ticketCost < 0)
								{
									printf_s("Некорректный ввод. Стоимость билета должна записываться положительным числом\nВведите снова:");
									ticketCost = atoi(String_WriteLine());
								}

								printf_s("\nВведите дату и время представления\n");
								perfTime = DateTime_WriteLine(false);
#endif // RU

								perfomances = (Perfomance*)realloc(perfomances, sizeof(Perfomance) * (perfomanceCount + 1));
								perfomances[perfomanceCount++] = SetNewPerfomance(title, ticketCount, ticketCost, perfTime, perfomances, perfomanceCount);
#ifdef EN
								printf_s("Perfomance added...");
#endif // EN
#ifdef RU
								printf_s("Представление добавлено...");
#endif // RU
								SetPerfomancesInFile(PERFOMANCE_FILE, perfomances, perfomanceCount);
								system("pause");
								break;
							}
							case 2: // Изменение представления
							{
								system("cls");
								printf_s(EditPerfomanceMenu());
								switch (CaseVariant_WriteLine(5))
								{
								case 1: //Изменение названия
								{
									system("cls");
									ShowPerfomances(perfomances, perfomanceCount);

#ifdef EN
									printf_s("Choose perfomance for editing: ");
#endif // EN
#ifdef RU
									printf_s("Выберите изменяемое представление: ");
#endif // RU
									int variant = atoi(String_WriteLine());
									while (variant < 1 || variant > perfomanceCount)
									{
#ifdef EN
										printf_s("Uncorrect choose. Enter again: ");
#endif // EN
#ifdef RU
										printf_s("Некорректный выбор. Введите снова: ");
#endif // RU
										variant = atoi(String_WriteLine());
									}


#ifdef EN
									printf_s("Enter new perfomance title: ");
#endif // EN
#ifdef RU
									printf_s("Введите новое название представления: ");
#endif // RU

									char* newTitle = String_WriteLine();
									strcpy(perfomances[variant - 1].title, newTitle);
									SetPerfomancesInFile(PERFOMANCE_FILE, perfomances, perfomanceCount);
#ifdef EN
									printf_s("Title succesfully changed...");
#endif // EN
#ifdef RU
									printf_s("Название успешно изменено...");
#endif // RU
									system("pause");
									break;
								}
								case 2: //Изменение количества билетов
								{
									system("cls");
									ShowPerfomances(perfomances, perfomanceCount);

#ifdef EN
									printf_s("Choose perfomance for editing: ");
#endif // EN
#ifdef RU
									printf_s("Выберите изменяемое представление: ");
#endif // RU
									int variant = atoi(String_WriteLine());
									while (variant < 1 || variant > perfomanceCount)
									{
#ifdef EN
										printf_s("Uncorrect choose. Enter again: ");
#endif // EN
#ifdef RU
										printf_s("Некорректный выбор. Введите снова: ");
#endif // RU
										variant = atoi(String_WriteLine());
									}

									int ticketCount;
#ifdef EN
									printf_s("Enter new ticket count for perfomance: ");
									ticketCount = atoi(String_WriteLine());
									while (ticketCount < 10)
									{
										printf_s("Uncorrect type. Ticket count must be number-value and 10 or more.\nEnter again:");
										ticketCount = atoi(String_WriteLine());
									}
#endif // EN
#ifdef RU
									printf_s("Введите новое количество билетов на представление: ");
									ticketCount = atoi(String_WriteLine());
									while (ticketCount < 10)
									{
										printf_s("Некорректный ввод. Количество билетов должно записываться числом и в количестве 10 и более.\nВведите снова:");
										ticketCount = atoi(String_WriteLine());
									}
#endif // RU
									perfomances[variant - 1].ticketCount = ticketCount;
									SetPerfomancesInFile(PERFOMANCE_FILE, perfomances, perfomanceCount);
#ifdef EN
									printf_s("Ticket count succesfully changed...");
#endif // EN
#ifdef RU
									printf_s("Количество билетов успешно изменено...");
#endif // RU
									system("pause");
									break;
								}
								case 3: //Изменение стоимости билетов
								{
									system("cls");
									ShowPerfomances(perfomances, perfomanceCount);

#ifdef EN
									printf_s("Choose perfomance for editing: ");
#endif // EN
#ifdef RU
									printf_s("Выберите изменяемое представление: ");
#endif // RU
									int variant = atoi(String_WriteLine());
									while (variant < 1 || variant > perfomanceCount)
									{
#ifdef EN
										printf_s("Uncorrect choose. Enter again: ");
#endif // EN
#ifdef RU
										printf_s("Некорректный выбор. Введите снова: ");
#endif // RU
										variant = atoi(String_WriteLine());
									}

									int ticketCost;
#ifdef EN
									printf_s("Enter new ticket cost for perfomance: ");
									ticketCost = atoi(String_WriteLine());
									while (ticketCost < 0)
									{
										printf_s("Uncorrect type. Ticket cost must be number-value and non-negative\nEnter again:");
										ticketCost = atoi(String_WriteLine());
									}
#endif // EN
#ifdef RU
									printf_s("Введите новую стоимость билета на представление: ");
									ticketCost = atoi(String_WriteLine());
									while (ticketCost < 0)
									{
										printf_s("Некорректный ввод. Стоимость билета должна записываться положительным числом\nВведите снова:");
										ticketCost = atoi(String_WriteLine());
									}
#endif // RU
									perfomances[variant - 1].ticketCost = ticketCost;
									SetPerfomancesInFile(PERFOMANCE_FILE, perfomances, perfomanceCount);
#ifdef EN
									printf_s("Ticket cost succesfully changed...");
#endif // EN
#ifdef RU
									printf_s("Стоимость билета успешно изменена...");
#endif // RU
									system("pause");
									break;
								}
								case 4: //Изменение даты и времени представления
								{
									system("cls");
									ShowPerfomances(perfomances, perfomanceCount);

#ifdef EN
									printf_s("Choose perfomance for editing: ");
#endif // EN
#ifdef RU
									printf_s("Выберите изменяемое представление: ");
#endif // RU
									int variant = atoi(String_WriteLine());
									while (variant < 1 || variant > perfomanceCount)
									{
#ifdef EN
										printf_s("Uncorrect choose. Enter again: ");
#endif // EN
#ifdef RU
										printf_s("Некорректный выбор. Введите снова: ");
#endif // RU
										variant = atoi(String_WriteLine());
									}

									DateTime perfTime;
#ifdef EN
									printf_s("\nEnter new perfomance date & time\n");
									perfTime = DateTime_WriteLine(false);
#endif // EN
#ifdef RU
									printf_s("\nВведите новую дату и время представления\n");
									perfTime = DateTime_WriteLine(false);
#endif // RU
									perfomances[variant - 1].time = perfTime;
									SetPerfomancesInFile(PERFOMANCE_FILE, perfomances, perfomanceCount);
#ifdef EN
									printf_s("Ticket cost succesfully changed...");
#endif // EN
#ifdef RU
									printf_s("Стоимость билета успешно изменена...");
#endif // RU
									system("pause");
									break;
								}
								case 5: //Выход
								{
									break;
								}
								}
								break;
							}
							case 3: // Удаление представления
							{
								system("cls");
								ShowPerfomances(perfomances, perfomanceCount);

#ifdef EN
								printf_s("Choose perfomance for deleting (0 - for exit): ");
#endif // EN
#ifdef RU
								printf_s("Выберите удаляемое представление (0 - для выхода): ");
#endif // RU
								int variant = atoi(String_WriteLine());
								while (variant < 0 || variant > perfomanceCount)
								{
#ifdef EN
									printf_s("Uncorrect choose. Enter again: ");
#endif // EN
#ifdef RU
									printf_s("Некорректный выбор. Введите снова: ");
#endif // RU
									variant = atoi(String_WriteLine());
								}

								if (variant == 0)
									break;

								artPerfomances = DeleteArtistPerfomance(-1, perfomances[variant - 1].id, artPerfomances, &artPerfomancesCount);
								perfomances[variant - 1].id = perfomances[perfomanceCount - 1].id;
								perfomances[variant - 1].ticketCost = perfomances[perfomanceCount - 1].ticketCost;
								perfomances[variant - 1].ticketCount = perfomances[perfomanceCount - 1].ticketCount;
								perfomances[variant - 1].time = perfomances[perfomanceCount - 1].time;
								strcpy(perfomances[variant - 1].title, perfomances[perfomanceCount - 1].title);

								perfomanceCount--;
								SetArtPerfInFile(ARTPERF_FILE, artPerfomances, artPerfomancesCount);
								SetPerfomancesInFile(PERFOMANCE_FILE, perfomances, perfomanceCount);
#ifdef EN
								printf_s("Perfomance successfully deleted");
#endif // EN
#ifdef RU
								printf_s("Представление успешно удалено");
#endif // RU

								system("pause");
								break;
							}
							case 4: // Сортировка представлений
							{
								system("cls");
								printf_s(SortPerfomanceMenu());
								switch (CaseVariant_WriteLine(5))
								{
								case 1: // Сортировка по названию
								{
									perfomances = SortPerfomancesArray(perfomances, perfomanceCount, 1);
#ifdef EN
									printf_s("\n\nSorted...");
#endif // EN
#ifdef RU
									printf_s("\n\nОтсортировано...");
#endif // RU
									system("pause");
									break;
								}
								case 2: // Сортировка по количеству билетов
								{
									perfomances = SortPerfomancesArray(perfomances, perfomanceCount, 2);
#ifdef EN
									printf_s("\n\nSorted...");
#endif // EN
#ifdef RU
									printf_s("\n\nОтсортировано...");
#endif // RU
									system("pause");
									break;
								}
								case 3: // Сортировка по стоимости билета
								{
									perfomances = SortPerfomancesArray(perfomances, perfomanceCount, 3);
#ifdef EN
									printf_s("\n\nSorted...");
#endif // EN
#ifdef RU
									printf_s("\n\nОтсортировано...");
#endif // RU
									system("pause");
									break;
								}
								case 4: // Сортировка по времени проведения
								{
									perfomances = SortPerfomancesArray(perfomances, perfomanceCount, 4);
#ifdef EN
									printf_s("\n\nSorted...");
#endif // EN
#ifdef RU
									printf_s("\n\nОтсортировано...");
#endif // RU
									system("pause");
									break;
								}
								case 5: // Выход
								{
									break;
								}
								}
								break;
							}
							case 5: // Поиск представлений
							{
								char* title = NULL;
								system("cls");
								printf_s(FindPerfomanceMenu());
								DateTime perfDate;
								int ticketCount = 0;
								int ticketCost = 0;
								perfDate.day = 0;
								switch (CaseVariant_WriteLine(5))
								{
								case 1: // Поиск по названию
								{
#ifdef EN
									printf_s("\nEnter perfomance title for find: ");
#endif // EN
#ifdef RU
									printf_s("\nВведите искомое название представления для поиска: ");
#endif // RU
									title = String_WriteLine();
									int findedCount = 0;
									Perfomance* findedPerfomances = FindPerfomancesByParams(perfomances, perfomanceCount, 1, &findedCount, title, ticketCount, ticketCost, perfDate);
									ShowPerfomances(findedPerfomances, findedCount);
									system("pause");
									break;
								}
								case 2: // Поиск по количеству билетов
								{
#ifdef EN
									printf_s("\nEnter perfomance's ticket count for find: ");
									ticketCount = atoi(String_WriteLine());
									while (ticketCount < 10)
									{
										printf_s("Uncorrect type. Ticket count must be number-value and 10 or more.\nEnter again:");
										ticketCount = atoi(String_WriteLine());
									}
#endif // EN
#ifdef RU
									printf_s("\nВведите количество билетов представления для поиска: ");
									ticketCount = atoi(String_WriteLine());
									while (ticketCount < 10)
									{
										printf_s("Некорректный ввод. Количество билетов должно записываться числом и в количестве 10 и более.\nВведите снова:");
										ticketCount = atoi(String_WriteLine());
									}
#endif // RU
									int findedCount = 0;
									Perfomance* findedPerfomances = FindPerfomancesByParams(perfomances, perfomanceCount, 2, &findedCount, title, ticketCount, ticketCost, perfDate);
									ShowPerfomances(findedPerfomances, findedCount);
									system("pause");
									break;
								}
								case 3: // Поиск по стоимости билетов
								{
#ifdef EN
									printf_s("\nEnter perfomance's ticket cost for find: ");
									ticketCost = atoi(String_WriteLine());
									while (ticketCost < 0)
									{
										printf_s("Uncorrect type. Ticket cost must be number-value and non-negative\nEnter again:");
										ticketCost = atoi(String_WriteLine());
									}
#endif // EN
#ifdef RU
									printf_s("\nВведите стоимость билета представления для поиска: ");
									ticketCost = atoi(String_WriteLine());
									while (ticketCost < 0)
									{
										printf_s("Некорректный ввод. Стоимость билета должна записываться положительным числом\nВведите снова:");
										ticketCost = atoi(String_WriteLine());
									}
#endif // RU
									int findedCount = 0;
									Perfomance* findedPerfomances = FindPerfomancesByParams(perfomances, perfomanceCount, 3, &findedCount, title, ticketCount, ticketCost, perfDate);
									ShowPerfomances(findedPerfomances, findedCount);
									system("pause");
									break;
								}
								case 4: // Поиск по дате представления
								{
#ifdef EN
									printf_s("\nEnter perfomance date & time for find\n");
									perfDate = DateTime_WriteLine(false);
#endif // EN
#ifdef RU
									printf_s("\nВведите искомую дату и время представления\n");
									perfDate = DateTime_WriteLine(false);
#endif // RU
									int findedCount = 0;
									Perfomance* findedPerfomances = FindPerfomancesByParams(perfomances, perfomanceCount, 4, &findedCount, title, ticketCount, ticketCost, perfDate);
									ShowPerfomances(findedPerfomances, findedCount);
									system("pause");
									break;
								}
								case 5: // Выход
								{
									break;
								}
								}
								system("cls");
								break;
							}
							case 6: // Вывод представлений
							{
								system("cls");
								ShowPerfomances(perfomances, perfomanceCount);
								system("pause");
								break;
							}
							case 7: // Выход
							{
								value = false;
							}
							}
							system("cls");
						}
						value = true;
						break;
					}
					case 3: // Работа с представлениями артистов
					{
						while (value)
						{
							system("cls");
							printf_s(AdminArtPerfMenu());
							switch (CaseVariant_WriteLine(6))
							{
							case 1: // Добавление представлений артистов
							{
								system("cls");
#ifdef EN
								printf_s("Artists table\n");
#endif // EN
#ifdef RU
								printf_s("Таблица артистов\n");
#endif // RU

								ShowArtists(artists, artistCount);

#ifdef EN
								printf_s("\n\nPerfomance table\n");
#endif // EN
#ifdef RU
								printf_s("\n\nТаблица представлений\n");
#endif // RU
								ShowPerfomances(perfomances, perfomanceCount);

								int artVariant, perfVariant;

#ifdef EN
								printf_s("Choose any artist: ");
								artVariant = atoi(String_WriteLine());
								while (artVariant < 1 || artVariant > artistCount)
								{
									printf_s("Uncorrect choose. Enter again: ");
									artVariant = atoi(String_WriteLine());
								}
#endif // EN
#ifdef RU
								printf_s("Выберите артиста: ");
								artVariant = atoi(String_WriteLine());
								while (artVariant < 1 || artVariant > artistCount)
								{
									printf_s("Неверный выбор. Введите снова: ");
									artVariant = atoi(String_WriteLine());
								}
#endif // RU


#ifdef EN
								printf_s("Choose any perfomance: ");
								perfVariant = atoi(String_WriteLine());
								while (perfVariant < 1 || perfVariant> artistCount)
								{
									printf_s("Uncorrect choose. Enter again: ");
									perfVariant = atoi(String_WriteLine());
								}
#endif // EN
#ifdef RU
								printf_s("Выберите представление: ");
								perfVariant = atoi(String_WriteLine());
								while (perfVariant < 1 || perfVariant> artistCount)
								{
									printf_s("Неверный выбор. Введите снова: ");
									perfVariant = atoi(String_WriteLine());
								}
#endif // RU

								long salary;
								char* role = NULL;

#ifdef EN
								printf_s("Enter artist salary for perfomance: ");
								salary = atoi(String_WriteLine());
								while (salary < 0)
								{
									printf_s("Salary cannot be negative. Enter value again: ");
									salary = atoi(String_WriteLine());
								}

								printf_s("Enter artists role in perfomance: ");
#endif // EN
#ifdef RU
								printf_s("Введите зарплату артиста за представление: ");
								salary = atoi(String_WriteLine());
								while (salary < 0)
								{
									printf_s("Зарплата не может быть отрицательной. Введите значение снова: ");
									salary = atoi(String_WriteLine());
								}

								printf_s("Введите роль артиста в представлении: ");
#endif // RU

								role = String_WriteLine();
								artPerfomances = (ArtPerf*)realloc(artPerfomances, sizeof(ArtPerf) * (artPerfomancesCount + 1));
								artPerfomances[artPerfomancesCount++] = InitArtPerf(artists[artVariant - 1].id, perfomances[perfVariant - 1].id, role, salary);

								SetArtPerfInFile(ARTPERF_FILE, artPerfomances, artPerfomancesCount);

#ifdef EN
								printf_s("Artist's perfomance added...\n");
#endif // EN
#ifdef RU
								printf_s("Представление артиста добавлено...\n");
#endif // RU
								system("pause");
								break;
							}
							case 2: // Удаление представлений артистов
							{
								system("cls");
								ShowArtistPerfomances(artPerfomances, artPerfomancesCount, artists, artistCount, perfomances, perfomanceCount);

#ifdef EN
								printf_s("Choose artist's perfomance for deleting (0 - for exit): ");
#endif // EN
#ifdef RU
								printf_s("Выберите удаляемое представление артиста (0 - для выхода): ");
#endif // RU
								int variant = atoi(String_WriteLine());
								while (variant < 0 || variant > artPerfomancesCount)
								{
#ifdef EN
									printf_s("Uncorrect choose. Enter again: ");
#endif // EN
#ifdef RU
									printf_s("Некорректный выбор. Введите снова: ");
#endif // RU
									variant = atoi(String_WriteLine());
								}

								if (variant == 0)
									break;

								artPerfomances[variant - 1].artistId = artPerfomances[artPerfomancesCount - 1].artistId;
								artPerfomances[variant - 1].perfomanceId = artPerfomances[artPerfomancesCount - 1].perfomanceId;
								artPerfomances[variant - 1].salary = artPerfomances[artPerfomancesCount - 1].salary;
								strcpy(artPerfomances[variant - 1].role, artPerfomances[artPerfomancesCount - 1].role);

								artPerfomancesCount--;
								SetArtPerfInFile(ARTPERF_FILE, artPerfomances, artPerfomancesCount);

#ifdef EN
								printf_s("Artist's perfomance successfully deleted");
#endif // EN
#ifdef RU
								printf_s("Представление артиста успешно удалено");
#endif // RU

								break;
							}
							case 3: // Изменение представлений артистов
							{

								break;
							}
							case 4: // Поиск представлений артистов
							{

								break;
							}
							case 5: // Вывод представлений артистов
							{
								system("cls");
								ShowArtistPerfomances(artPerfomances, artPerfomancesCount, artists, artistCount, perfomances, perfomanceCount);
								system("pause");
								break;
							}
							case 6: // Выход
							{
								value = false;
								system("cls");
								break;
							}
							}
						}
						value = true;
						break;
					}
					case 4: // Работа с пользователями
					{
						break;
					}
					case 5: // Выход в главное меню
					{
						value = false;
						break;
					}
					system("cls");
					}
				}
				value = true;
				break;
			}
			case SimpleUser:
			{
				printf_s("\n\nYou logged in as User");
				break;
			}
			default: // Некорректный ввод данных
			{
#ifdef EN
				printf_s("\n\nLogin or password are not correct!\n");
#endif // EN
#ifdef RU
				printf_s("\n\nНеверно введен логин или пароль");
#endif // RU

				break;
			}
			}
			break;
		}
		case 2: // Выход
		{
			system("cls");
			system("pause");
			return 0;

			break;
		}
		}
	}
}

#pragma region AllMenu
char* AdminMainMenu()
{
#ifdef EN
	return "1 - Artist tab\n2 - Perfomance tab\n3 - Artists & their perfomances tab\n4 - Users tab\n5 - Exit to main menu: ";
#endif // EN
#ifdef RU
	return "1 - Вкладка артистов\n2 - Вкладка представлений\n3 - Вкладка артистов & их представлений\n4 - Вкладка пользователей\n5 - Выход в главное меню: ";
#endif // RU
}

char* UserMainMenu()
{
#ifdef EN
	return "1 - Artist menu\n2 - Perfomance menu\nChoose: ";
#endif // EN
#ifdef RU
	return "1 - Меню артистов\n2 - Меню представлений\nВаш выбор: ";
#endif
}
#pragma endregion


#pragma region Admin_Controllers

#pragma region ArtistsMenu
char* AdminArtistMenu()
{
#ifdef EN
	return "1 - Add new artist\n2 - Edit artist\n3 - Delete artist\n4 - Sort artists\n5 - Find artist by param\n6 - Show all artits\n7 - Show 5 most demanded actors\n8 - Exit to admin menu: ";
#endif // EN
#ifdef RU
	return "1 - Добавить нового артиста\n2 - Редактировать актера\n3 - Удалить актера\n4 - Сортировать список актеров\n5 - Найти актера по заданному параметру\n6 - Показать всех актеров\n7 - Показать 5 самых востребованных актеров\n8 - Выход в меню администратора: ";
#endif // RU

}

char* EditArtistMenu()
{
#ifdef EN
	return "1 - Update name\n2 - Update birth date\n3 - Cancel: ";
#endif // EN
#ifdef RU
	return "1 - Обновить имя\n2 - Обновить дату рождения\n3 - Отмена: ";
#endif // RU

}

char* SortArtistMenu()
{
#ifdef EN
	return "1 - Sort by name\n2 - Sort by birth date\n3 - Cancel: ";
#endif // EN
#ifdef RU
	return "1 - Сортировать по имени\n2 - Сортировать по дате рождения\n3 - Отмена: ";
#endif // RU
}

char* FindArtistMenu()
{
#ifdef EN
	return "1 - Find by name\n2 - Find by birth date\n3 - Cancel: ";
#endif // EN
#ifdef RU
	return "1 - Поиск по имени\n2 - Поиск по дате рождения\n3 - Отменить";
#endif // RU
}
#pragma endregion



#pragma region PerfomanceMenu
char* AdminPerfomanceMenu()
{
#ifdef EN
	return "1 - Add new perfomance\n2 - Edit perfomance\n3 - Delete perfomance\n4 - Sort perfomances\n5 - Find perfomance by param\n6 - Show all perfomances\n7 - Exit to admin menu: ";
#endif // EN
#ifdef RU
	return "1 - Добавить новое представление\n2 - Редактировать представление\n3 - Удалить представление\n4 - Сортировать список представлений\n5 - Найти представление по заданному параметру\n6 - Показать все представления\n7 - Выход в меню администратора: ";
#endif // RU

}

char* EditPerfomanceMenu()
{
#ifdef EN
	return "1 - Update title\n2 - Update ticket count\n3 - Update ticket cost\n4 - Update perfomance date\n5 - Cancel: ";
#endif // EN
#ifdef RU
	return "1 - Обновить название\n2 - Обновить количество билетов\n3 - Обновить стоимость билета\n4 - Обновить дату представления\n5 - Отмена: ";
#endif // RU

}

char* SortPerfomanceMenu()
{
#ifdef EN
	return "1 - Sort by title\n2 - Sort by ticket count\n3 - Sort by ticket cost\n4 - Sort by perfomance date\n5 - Cancel: ";
#endif // EN
#ifdef RU
	return "1 - Сортировать по названию\n2 - Сортировать по количеству билетов\n3 - Сортировать по стоимости билета\n4 - Сортировать по дате представления\n5 - Отмена: ";
#endif // RU
}

char* FindPerfomanceMenu()
{
#ifdef EN
	return "1 - Find by title\n2 - Find by ticket count\n3 - Find by ticket cost\n4 - Find by perfomance date\n5 - Cancel: ";
#endif // EN
#ifdef RU
	return "1 - Поиск по названию\n2 - Поиск по количеству билетов\n3 - Поиск по стоимости билета\n4 - Поиск по дате представления\n5 - Отменить";
#endif // RU
}
#pragma endregion



#pragma region ArtPerfomanceMenu
char* AdminArtPerfMenu()
{
#ifdef EN
	return "1 - Appoint perfomance to artist\n2 - Delete artist perfomance\n3 - Update artist in perfomance\n4 - Find artist's perfomance\n5 - Show artist's perfomances\n6 - Exit to admin menu: ";
#endif // EN

#ifdef RU
	return "1 - Назначить представление артисту\n2 - Удалить представление артиста\n3 - Изменить представление артиста\n4 - Найти представление артиста\n5 - Показать представления артистов\n6 - Выйти в меню администратора: ";
#endif // RU

}

char* EditArtPerfMenu()
{
#ifdef EN
	return "1 - Update artist\n2 - Update perfomance\n3 - Update salary\n4 - Update role: ";
#endif // EN
#ifdef RU
	return "1 - Обновить артиста\n2 - Обновить представление\n3 - Обновить зарплату\n4 - Обновить роль: ";
#endif // RU
}

char* FindArtPerfMenu()
{
#ifdef EN
	return "1 - Find by artist\n2 - Find by perfomance\n3 - Find by salary\n4 - Find by role";
#endif // EN

#ifdef RU
	return "1 - Поиск по артисту\n2 - Поиск по представлению\n3 - Поиск по зарплате\n4 - Поиск по роли";
#endif // RU

}
#pragma endregion

#pragma endregion



void ShowArtists(Artist* artists, int artistCount)
{
#ifdef EN
	printf_s("   ____________________________________\n");
	printf_s("  |     Name     |      Birth date     |\n");
	printf_s("  |______________|_____________________|\n");
	for (int i = 0; i < artistCount; i++)
		printf_s("%2d|%-14s|%d/%d/%-16d|\n", i + 1, artists[i].name, artists[i].birthDate.day, artists[i].birthDate.month, artists[i].birthDate.year);
	printf_s("  |______________|_____________________|\n");
#endif // EN
#ifdef RU
	printf_s("   ____________________________________\n");
	printf_s("  |      ФИО     |    Дата  рождения   |\n");
	printf_s("  |______________|_____________________|\n");
	for (int i = 0; i < artistCount; i++)
		printf_s("%2d|%-14s|%d.%d.%-16d|\n", i + 1, artists[i].name, artists[i].birthDate.day, artists[i].birthDate.month, artists[i].birthDate.year);
	printf_s("  |______________|_____________________|\n");
#endif // RU
}

void ShowPerfomances(Perfomance* perfomances, int perfomanceCount)
{
#ifdef EN
	printf_s("   ______________________________________________________________________\n");
	printf_s("  |       Title       |    Count    |     Cost     |     Date & Time     |\n");
	printf_s("  |___________________|_____________|______________|_____________________|\n");
	for (int i = 0; i < perfomanceCount; i++)
	{
		if (perfomances[i].time.hours < 12)
			printf_s("%2d|%-19s|%-13d|$%-13d|%d/%d/%d %d:%-7dpm|\n", i + 1, perfomances[i].title, perfomances[i].ticketCount, perfomances[i].ticketCount, perfomances[i].time.month, perfomances[i].time.day, perfomances[i].time.year, perfomances[i].time.hours, perfomances[i].time.minutes);
		else
			printf_s("%2d|%-19s|%-13d|$%-13d|%d/%d/%d %d:%-7dam|\n", i + 1, perfomances[i].title, perfomances[i].ticketCount, perfomances[i].ticketCount, perfomances[i].time.month, perfomances[i].time.day, perfomances[i].time.year, perfomances[i].time.hours - 12, perfomances[i].time.minutes);
	}
	printf_s("  |___________________|_____________|______________|_____________________|\n");
#endif // EN
#ifdef RU
	printf_s("   ______________________________________________________________________\n");
	printf_s("  |      Название     | Количество  |  Стоимость   |     Дата и время    |\n");
	printf_s("  |___________________|_____________|______________|_____________________|\n");
	for (int i = 0; i < perfomanceCount; i++)
		printf_s("%2d|%-19s|%-13d|%-13d$|%d.%d.%d %d:%-7d|\n", i + 1, perfomances[i].title, perfomances[i].ticketCount, perfomances[i].ticketCount, perfomances[i].time.day, perfomances[i].time.month, perfomances[i].time.year, perfomances[i].time.hours, perfomances[i].time.minutes);

	printf_s("  |___________________|_____________|______________|_____________________|\n");
#endif // RU
}

void ShowArtistPerfomances(ArtPerf* artPerfs, int artPerfCount, Artist* artists, int artistCount, Perfomance* perfomances, int perfomanceCount)
{
#ifdef EN
	printf_s("   ___________________________________________________________________________\n");
	printf_s("  |    Artist name    |   Perfomance title   |     Salary     |      Role     |\n");
	printf_s("  |___________________|______________________|________________|_______________|\n");
#endif // EN

#ifdef RU
	printf_s("   ___________________________________________________________________________\n");
	printf_s("  |    ФИО артиста    |Название представления|    Зарплата    |      Роль     |\n");
	printf_s("  |___________________|______________________|________________|_______________|\n");
#endif // RU

	for (int i = 0; i < artPerfCount; i++)
	{
		Artist tempArtist; tempArtist.id = -1;
		Perfomance tempPerfomance; tempPerfomance.id = -1;
		for (size_t j = 0; j < artistCount; j++)
		{
			if (artists[j].id == artPerfs[i].artistId)
			{
				tempArtist = artists[j];
				break;
			}
		}

		for (size_t j = 0; j < perfomanceCount; j++)
		{
			if (perfomances[j].id == artPerfs[i].perfomanceId)
			{
				tempPerfomance = perfomances[j];
				break;
			}
		}


		if (tempArtist.id != -1 && tempPerfomance.id != -1)
			printf_s("%2d|%-19s|%-22s|$%-15d|%-15s|\n", i + 1, tempArtist.name, tempPerfomance.title, artPerfs[i].salary, artPerfs[i].role);
	}
	printf_s("  |___________________|______________________|________________|_______________|\n");
}



char* String_WriteLine()
{
	char* str = (char*)malloc(100);

	gets_s(str, 100);
	if (strlen(str) == 0)
	{
		gets_s(str, 100);
	}
	str[strlen(str)] = '\0';

	return str;
}

char* Password_WriteLine(char* displayString)
{
	int size = 1;
	char* str = (char*)malloc(size);
	char* silentStr = (char*)malloc(size);

	system("cls");
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
			silentStr = (char*)realloc(silentStr, size);

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
				str = (char*)realloc(str, size);
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

int CaseVariant_WriteLine(int topValue)
{
	int value = _getch();
	value -= 48;
	if (value > 0 && value <= topValue)
	{
		return value;
	}

	return 0;
}

DateTime DateTime_WriteLine(bool isArtist)
{
	//YEAR
#ifdef EN
	printf_s("Enter year: ");
#endif // EN
#ifdef RU
	printf_s("Введите год: ");
#endif // RU


	int year = InitYear(atoi(String_WriteLine()));
	while (!year)
	{
#ifdef EN
		printf_s("Uncorrect year. Type again: ");
#endif // EN
#ifdef RU
		printf_s("Некорректно введен год. Введите снова: ");
#endif // RU
		year = InitYear(atoi(String_WriteLine()));
	}


	//MONTH
#ifdef EN
	printf_s("Enter month: ");
#endif // EN
#ifdef RU
	printf_s("Введите месяц: ");
#endif // RU

	int month = InitMonth(atoi(String_WriteLine()));
	while (!month)
	{
#ifdef EN
		printf_s("Uncorrect month. Type again: ");
#endif // EN
#ifdef RU
		printf_s("Некорректно введен месяц. Введите снова: ");
#endif // RU
		month = InitMonth(atoi(String_WriteLine()));
	}


	DateTime date;
	date.year = year;
	date.month = month;

	//DAY
#ifdef EN
	printf_s("Enter day: ");
#endif // EN
#ifdef RU
	printf_s("Введите день: ");
#endif // RU

	int day = InitDay(date, atoi(String_WriteLine()));
	while (!day)
	{
#ifdef EN
		printf_s("Uncorrect day. Type again: ");
#endif // EN
#ifdef RU
		printf_s("Некорректно введен день. Введите снова: ");
#endif // RU
		day = InitDay(date, atoi(String_WriteLine()));
	}

	date.day = day;

	if (isArtist)
		return date;


	//HOURS
#ifdef EN
	printf_s("Enter hours: ");
#endif // EN
#ifdef RU
	printf_s("Введите час: ");
#endif // RU


	int hour = InitHours(atoi(String_WriteLine()));
	while (!hour)
	{
#ifdef EN
		printf_s("Uncorrect hours. Type again: ");
#endif // EN
#ifdef RU
		printf_s("Некорректно введен час. Введите снова: ");
#endif // RU
		hour = InitHours(atoi(String_WriteLine()));
	}


	//MINUTES
#ifdef EN
	printf_s("Enter minutes: ");
#endif // EN
#ifdef RU
	printf_s("Введите минуты: ");
#endif // RU


	int minute = InitMinutes(atoi(String_WriteLine()));
	while (!minute)
	{
#ifdef EN
		printf_s("Uncorrect minutes. Type again: ");
#endif // EN
#ifdef RU
		printf_s("Некорректно введены минуты. Введите снова: ");
#endif // RU
		minute = InitMinutes(atoi(String_WriteLine()));
	}


	date.hours = hour;
	date.minutes = minute;

	return date;
}