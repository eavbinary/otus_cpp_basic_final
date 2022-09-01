#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <random>

using namespace std;

void singlePlayer(), multiPlayer(), Help();
bool checkFull(), Error(0), Start(0), Change(0), Single(true), Config(true), End(0);
int difficulty = 0;
char keyInput(bool x, bool y), input = ' ', inDiff = ' ', inStart = ' ';

char field[10];
bool checkWin(char);

void AI(int difficulty)
{
	srand((unsigned)time(nullptr));

	if (difficulty == 1)
	{ 
		// Easy
		int check = rand() % 3;
		if (check != 1)
		{
			for (int i = 1; i < 10; i++)
			{ 
				// Check if AI can win
				if (field[i] == ' ')
				{
					field[i] = 'O';
					if (checkWin('O'))
					{
						return;
					}
					else
					{
						field[i] = ' ';
					}
				}
			}
		}
		else if (check != 2)
		{
			for (int i = 1; i < 10; i++)
			{ 
				// Check if Player can win
				if (field[i] == ' ')
				{
					field[i] = 'X';
					if (checkWin('X'))
					{
						field[i] = 'O';
						return;
					}
					else
					{
						field[i] = ' ';
					}
				}
			}
		}
		while (true)
		{
			int i = rand() % 9 + 1;
			if (field[i] == ' ')
			{
				field[i] = 'O';
				return;
			}
		}
	}
	else if (difficulty == 2)
	{ 
		// Medium
		int check = rand() % 2;
		if (check == 1)
		{
			for (int i = 1; i < 10; i++)
			{ 
				// Check if AI can win
				if (field[i] == ' ')
				{
					field[i] = 'O';
					if (checkWin('O'))
					{
						return;
					}
					else
					{
						field[i] = ' ';
					}
				}
			}
		}
		else if (check == 2)
		{
			for (int i = 1; i < 10; i++)
			{ 
				// Check if Player can win
				if (field[i] == ' ')
				{
					field[i] = 'X';
					if (checkWin('X'))
					{
						field[i] = 'O';
						return;
					}
					else
					{
						field[i] = ' ';
					}
				}
			}
		}
		while (true)
		{
			int i = rand() % 9 + 1;
			if (field[i] == ' ')
			{
				field[i] = 'O';
				return;
			}
		}
	}
	else if (difficulty == 3)
	{ 
		// Hard
		for (int i = 1; i < 10; i++)
		{ 
			// Check if AI can win
			if (field[i] == ' ')
			{
				field[i] = 'O';
				if (checkWin('O'))
				{
					return;
				}
				else
				{
					field[i] = ' ';
				}
			}
		}

		for (int i = 1; i < 10; i++)
		{ 
			// Check if Player can win and stop it
			if (field[i] == ' ')
			{
				field[i] = 'X';
				if (checkWin('X'))
				{
					field[i] = 'O';
					return;
				}
				else
				{
					field[i] = ' ';
				}
			}
		}

		// Select middle field if possible (Feld '5').
		if (field[5] == ' ')
		{
			field[5] = 'O';
			return;
		}

		random_device rd;
		mt19937 g(rd());

		int code[4] = {1, 3, 7, 9};
		shuffle(code, code + 3, g);
		for (int i = 0; i < 4; i++)
		{
			int j = code[i];

			if (field[j] == ' ')
			{
				field[j] = 'O';
				return;
			}
		}

		int code2[4] = {2, 4, 6, 8};
		shuffle(code2, code2 + 3, g);
		for (int i = 0; i < 4; i++)
		{
			int j = code2[i];

			if (field[j] == ' ')
			{
				field[j] = 'O';
				return;
			}
		}
	}
	else
	{
		return;
	}
}

void resetField()
{
	for (int i = 0; i < 10; i++)
	{
		field[i] = ' ';
	}
}

void menu()
{
	while (true)
	{
		Single = false;
		Config = true;
		resetField();
		system("cls");
		char inMenu = ' ';

		cout << "\n"
			 << " TIC TAC TOE\n\n"
			 << " MENU\n ====\n"
			 << " 1: Singleplayer\n"
			 << " 2: Multiplayer\n"
			 << " 3: Help\n"
			 << " q: Quit\n";

		if (Error)
			cout << "\n Wrong input! Please try again: ";
		else
			cout << "\n Input: ";
		Error = false;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> inMenu;

		if (inMenu == '1')
			singlePlayer();
		else if (inMenu == '2')
			multiPlayer();
		else if (inMenu == '3')
			Help();
		else if (inMenu == 'q')
			exit(0);
		else
			Error = true;
	}
}

void drawField()
{
	system("cls");
	cout << "\n    TIC  TAC  TOE";
	if (Single)
		cout << " (Singleplayer - Level " << inDiff << ")";
	cout << "\n\n    o-----------o" << endl
		 << "    | " << field[1] << " | " << field[2] << " | " << field[3] << " |" << endl
		 << "    |---|---|---|" << endl
		 << "    | " << field[4] << " | " << field[5] << " | " << field[6] << " |" << endl
		 << "    |---|---|---|" << endl
		 << "    | " << field[7] << " | " << field[8] << " | " << field[9] << " |" << endl
		 << "    o-----------o" << endl;
}

void singlePlayer()
{
	Single = true;
	if (Config)
	{
		Config = false;

		do
		{
			system("cls");
			cout << "\n TIC TAC TOE (Singleplayer)\n";
			cout << "\n LEVEL\n =====\n 1: Easy\n 2: Medium\n 3: Hard\n q: Quit (Back to the menu)\n";
			if (Error)
				cout << "\n Wrong input! Please try again: ";
			else
				cout << "\n Input: ";
			Error = false;
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cin >> inDiff;

			if (inDiff == '1')
				difficulty = 1;
			else if (inDiff == '2')
				difficulty = 2;
			else if (inDiff == '3')
				difficulty = 3;
			else if (inDiff == 'q')
				return;
			else
				Error = true;
		} while (Error == true);

		do
		{
			system("cls");
			cout << "\n TIC TAC TOE (Singleplayer)\n";
			cout << "\n Who should start?\n\n 1: Player\n 2: Computer\n q: Quit (Back to the menu)\n";
			if (Error)
				cout << "\n Wrong input! Please try again: ";
			else
				cout << "\n Input: ";
			Error = false;
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cin >> inStart;
			if (inStart == '1')
				Start = true;
			else if (inStart == '2')
				Start = false;
			else if (inStart == 'q')
				menu();
			else
				Error = true;
		} while (Error == true);
	}

	drawField();

	if (Start)
		cout << "\n The player starts...\n";
	else
		cout << "\n The computer starts...\n";

	if (inStart == '1')
	{
		Start = true;
		Change = true;
	}
	else
	{
		Start = false;
		Change = false;
	}

	while (true)
	{
		if (Change)
		{
			input = keyInput(true, true);
		}
		else
		{
			AI(difficulty);
		}
		drawField();

		if (checkWin('O'))
		{
			cout << "\n You've lost!\n\n";
			End = true;
			break;
		}

		if (checkWin('X'))
		{
			cout << "\n You won! \n\n";
			End = true;
			break;
		}

		if (checkFull())
		{
			cout << "\n Draw!\n\n";
			End = true;
			break;
		}

		Change = !Change;
	}

	if (End)
	{
		char inAdd = ' ';
		cout << "\n The same game again (in turn)?\n\n"
			 << " 1: YES - keep playing!\n"
			 << " 2: NO - back to the menu.\n\n"
			 << " Input: ";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> inAdd;

		if (inAdd == '1')
		{
			resetField();
			Start = !Start;

			if (Start)
			{
				cout << "\n You start!";
				inStart = '1';
			}
			else
			{
				cout << "\n The computer starts!";
				inStart = '2';
			}
			singlePlayer();
		}
		else
		{
			Config = true;
			menu();
		}
	}
}

void multiPlayer()
{
	bool Single = false, End = false, player1Turn = true;
	char input = ' ', inStart = ' ';
	while (true)
	{
		drawField();
		if (checkWin('X'))
		{
			cout << "\n Player 1 has won! Good luck!\n\n";
			End = true;
			break;
		}
		else if (checkWin('O'))
		{
			cout << "\n Player 2 has won! Good luck!\n\n";
			End = true;
			break;
		}
		if (checkFull())
		{
			cout << "\n Draw!\n\n";
			End = true;
			break;
		}
		input = keyInput(player1Turn, Single);
		if (input == 'q')
			return;

		player1Turn = !player1Turn;
	}
	if (End)
	{
		char inAdd = ' ';
		cout << "\n The same game again (alternately)?\n\n"
			 << " 1: YES - keep playing!\n"
			 << " 2: NO - back to the menu.\n\n"
			 << " Input: ";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> inAdd;

		if (inAdd == '1')
		{
			resetField();
			multiPlayer();
		}
		else
		{
			menu();
		}
	}
}

void Help()
{
	system("cls");
	cout << "\n TIC TAC TOE\n\n HELP\n ====\n\n"
		 << " Singleplayer:\n -------------\n In single player mode, you play against the computer.\n\n"
		 << " Multiplayer:\n ------------\n In multiplayer mode, you play against a second player.\n Input switches between X and O.\n"
		 << " You can also play this mode, if you want to test new tactics or just want to play against yourself.\n\n"
		 << " Controls:\n ---------\n To choose a field you must enter a number between 1 and 9.\n"
		 << " The first field is in the top left corner. The second right next to it etc.\n"
		 << " With 'q' you always return to the menu or the program will be closed.\n - - -\n";
	cout << "\n Back to the menu: Please press a button: ";
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin >> input;
}

char keyInput(bool x, bool y)
{
	while (true)
	{
		if (y)
		{
			cout << "\n\n Your input (X): ";
		}
		else
		{
			if (x)
				cout << "\n\n Your input 1 (X): ";
			else
				cout << "\n\n Your input 2 (O): ";
		}
		char input = ' ';
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> input;
		int inputNumber = input - '0';

		if (inputNumber > 9 || inputNumber < 1)
		{
			if (input == 'q')
			{
				menu();
			}
			else
			{
				drawField();
				cout << "\n Incorrect input! Please enter only from 1 to 9.";
			}
		}
		else if (field[inputNumber] != ' ')
		{
			drawField();
			cout << "\n This field is already occupied!";
		}
		else
		{
			if (x)
				field[inputNumber] = 'X';
			else
				field[inputNumber] = 'O';
			return input;
		}
	}
}

bool checkWin(char sign)
{
	if (field[1] == sign && field[2] == sign && field[3] == sign 
	|| field[1] == sign && field[4] == sign && field[7] == sign 
	|| field[1] == sign && field[5] == sign && field[9] == sign 
	|| field[2] == sign && field[5] == sign && field[8] == sign 
	|| field[3] == sign && field[6] == sign && field[9] == sign 
	|| field[3] == sign && field[5] == sign && field[7] == sign 
	|| field[4] == sign && field[5] == sign && field[6] == sign 
	|| field[7] == sign && field[8] == sign && field[9] == sign)
	{
		return true;
	}
	return false;
}

bool checkFull()
{
	for (int i = 1; i <= 9; i++)
	{
		if (field[i] == ' ')
		{
			return false;
		}
	}
	return true;
}

int max(int a, int b)
{
	return a > b ? a : b;
}

int main()
{
	srand((unsigned)time(nullptr));
	menu();
	return 0;
}
