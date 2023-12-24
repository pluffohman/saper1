#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#define SPACE ' '
#define COUNTBOMBS 10
#define BOMBS '@'

using namespace std;

void BombPlacing(char** Area, int a, int b)
{
	int x = 0;
	int y = 0;
	for (int i = 0; i < COUNTBOMBS; i++)
	{
		x = rand() % 10;
		y = rand() % 10;

		if (x != a && y != b)
		{
			Area[x][y] = BOMBS;
		}
		else i--;
	}
}

inline bool Loser(int x, int y, char** Area)
{
	if (Area[x - 1][y - 1] != BOMBS)return false;
	else return true;
}

void PlayingArea(char** Area, int Rows, int Columns)
{
	cout << "       1   2   3   4   5   6   7   8   9   10" << endl;
	for (int i = 0; i < Rows; i++)
	{
		cout << "     -----------------------------------------" << endl;
		if (i + 1 == 10)cout << "  ";
		else cout << "   ";
		cout << i + 1 << SPACE;
		for (int j = 0; j < Columns; j++)
		{
			cout << "| " << Area[i][j] << SPACE;
			if (j == 9)cout << "|" << endl;
		}
	}
}

inline void Open(int x, int y, char** Area)
{
	if (Area[x - 1][y - 1] == '#')Area[x - 1][y - 1] = SPACE;
	else if (Area[x - 1][y - 1] == SPACE)cout << "Эта ячейка уже была открыта!" << endl;
}

void LastFight(char** PlayerArea, char** EnemyArea, int Rows, int Columns)
{
	for (int i = 0; i < Columns; i++)
	{
		for (int j = 0; j < Rows; j++)
		{
			if (EnemyArea[i][j] == BOMBS)PlayerArea[i][j] = EnemyArea[i][j];
		}
	}
	PlayingArea(PlayerArea, Rows, Columns);
}

int main()
{
	system("chcp 1251");
	system("cls");
	srand(time(NULL));

	const int Columns = 10;
	const int Rows = 10;
	int x = 0, y = 0;
	bool Flag = false;
	int Turns = 90;
	int Choise = 0;
	char Repeat = '-';

	char** PlayerArea = new char* [Rows];
	for (int i = 0; i < Rows; i++)
	{
		PlayerArea[i] = new char[Columns] {};
	}
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Columns; j++)
			PlayerArea[i][j] = '#';
	}


	char** EnemyArea = new char* [Rows];
	for (int i = 0; i < Rows; i++)
	{
		EnemyArea[i] = new char[Columns] {};
	}
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Columns; j++)
		{
			EnemyArea[i][j] = '#';
		}
	}

	do
	{
		do
		{
			cout << "---------Игра \"Сапёр\"---------" << endl;
			cout << "1 - Играть" << endl;
			cout << "0 - Выход" << endl;
			cin >> Choise;
			if (Choise != 0 && Choise != 1)
			{
				cout << "Неверный ввод!" << endl;
				Sleep(500);
				system("cls");
			}
			if (Choise == 1)break;
			if (Choise == 0)
			{
				cout << "До новых встреч!" << endl;
				exit(0);
			}
		} while (Choise != 0 && Choise != 1);

		do
		{
			system("cls");
			PlayingArea(PlayerArea, Rows, Columns);

			x = 0, y = 0;
			cout << endl;
			cout << "Введите x: ";
			do
			{
				cin >> x;
				if (x < 1 || x > Columns)cout << "Нет такой ячейки! повторите ввод: ";
			} while (x < 1 || x > Columns);

			cout << "Введите y: ";
			do
			{
				cin >> y;
				if (y < 1 || y > Columns)cout << "Нет такого столбца! повторите ввод: ";
			} while (y < 1 || y > Columns);

			if (Loser(x, y, EnemyArea) == true)
			{
				cout << "Ты проиграл!" << endl;
				LastFight(PlayerArea, EnemyArea, Rows, Columns);
				break;
			}
			else Open(x, y, PlayerArea);
			Turns--;

			if (Flag == false)
			{
				BombPlacing(EnemyArea, x, y);
				Flag = true;
			}

			if (Turns == 0)
			{
				cout << "Ты победил!" << endl;
				LastFight(PlayerArea, EnemyArea, Rows, Columns);
				break;
			}
			Sleep(500);
		} while (true);

		cout << endl;
		cout << "Играть ещё? (Y - Да, N - Нет)" << endl;
		do
		{
			cin >> Repeat;
			if (Repeat != 'n' && Repeat != 'N' && Repeat != 'y' && Repeat != 'Y')cout << "Неккоректное значение!" << endl;
			else system("cls");
		} while (Repeat != 'n' && Repeat != 'N' && Repeat != 'y' && Repeat != 'Y');
	} while (Repeat != 'n' && Repeat != 'N');

	for (int i = 0; i < 10; i++)
	{
		if (PlayerArea[i])
		{
			delete[]PlayerArea[i];
			PlayerArea[i] = nullptr;
		}
		else cout << "Память уже была освобождена!" << endl;
	}
	if (PlayerArea)
	{
		delete[]PlayerArea;
		PlayerArea = nullptr;
	}
	else cout << "Память уже была освобождена!" << endl;

	for (int i = 0; i < 10; i++)
	{
		if (EnemyArea[i])
		{
			delete[]EnemyArea[i];
			EnemyArea[i] = nullptr;
		}
		else cout << "Память уже была освобождена!" << endl;
	}
	if (EnemyArea)
	{
		delete[]EnemyArea;
		EnemyArea = nullptr;
	}
	else cout << "Память уже была освобождена!" << endl;
	cout << "До новых встреч!" << endl;
	system("pause");
}
