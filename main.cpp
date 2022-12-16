#include <iostream>
#include <conio.h>
#include <deque>
#include <thread>
#include <chrono>
#include <random>
#include <windows.h>
#include <string>

using std::cout, std::string, std::deque, std::this_thread::sleep_for, std::to_string, std::chrono::milliseconds, std::chrono::seconds;

// written by chapel1337
// started on 12/14/2022
// finished on 12/16/2022
// extremely disappointed with this, constant attempted and successful revisions plagued this project
// also joined a new discord server, so i was getting constantly distracted
// tried making a colormap, available matchsticks, computer opponent, etcetera; all being consistent failures
// this is probably one of the worst project i have ever made

deque<deque<char>> presetMap
{
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', },
	{ ' ', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', },
	{ ' ', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
};
deque<deque<char>> map{ presetMap };

/*
// available = 0, player1 removed = 1, player2 removed = 2
deque<deque<int>> availableMatches
{
	{ 0 },
	{ 0, 0, 0, },
	{ 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, },
};
*/

int selectedMatchPositionX{};
int selectedMatchPositionY{};

int matchPositionX{ 8 };
deque<int> matchPositionY{ 2, 3, 4 };

int matchesLeft{ 16 };
short nims{};

int currentPlayer{};

int computerOpponent{};
bool nimAnimations{};

void menu(const short postion);

void clear()
{
	system("cls");
}

void setTextColor(const int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void resetTextColor()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void title(const string& input)
{
	SetConsoleTitleA(("nim - " + input).c_str());
}

void title(const string& input, const int i)
{
	SetConsoleTitleA(("nim - " + input + to_string(i)).c_str());
}

short getRandom(short min, short max)
{
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<> random{ min, max };

	return random(mt);
}

// hell
void setMatchPosition()
{
	if (selectedMatchPositionY == 0 && selectedMatchPositionX == 0)
	{
		matchPositionX = 8;

		matchPositionY[0] = 2;
		matchPositionY[1] = 3;
		matchPositionY[2] = 4;
	}

	else if (selectedMatchPositionY == 1 && selectedMatchPositionX == 0)
	{
		matchPositionX = 6;

		matchPositionY[0] = 6;
		matchPositionY[1] = 7;
		matchPositionY[2] = 8;
	}
	else if (selectedMatchPositionY == 1 && selectedMatchPositionX == 1)
	{
		matchPositionX = 8;

		matchPositionY[0] = 6;
		matchPositionY[1] = 7;
		matchPositionY[2] = 8;
	}
	else if (selectedMatchPositionY == 1 && selectedMatchPositionX == 2)
	{
		matchPositionX = 10;

		matchPositionY[0] = 6;
		matchPositionY[1] = 7;
		matchPositionY[2] = 8;
	}

	else if (selectedMatchPositionY == 2 && selectedMatchPositionX == 0)
	{
		matchPositionX = 4;

		matchPositionY[0] = 10;
		matchPositionY[1] = 11;
		matchPositionY[2] = 12;
	}
	else if (selectedMatchPositionY == 2 && selectedMatchPositionX == 1)
	{
		matchPositionX = 6;

		matchPositionY[0] = 10;
		matchPositionY[1] = 11;
		matchPositionY[2] = 12;
	}
	else if (selectedMatchPositionY == 2 && selectedMatchPositionX == 2)
	{
		matchPositionX = 8;

		matchPositionY[0] = 10;
		matchPositionY[1] = 11;
		matchPositionY[2] = 12;
	}
	else if (selectedMatchPositionY == 2 && selectedMatchPositionX == 3)
	{
		matchPositionX = 10;

		matchPositionY[0] = 10;
		matchPositionY[1] = 11;
		matchPositionY[2] = 12;
	}
	else if (selectedMatchPositionY == 2 && selectedMatchPositionX == 4)
	{
		matchPositionX = 12;

		matchPositionY[0] = 10;
		matchPositionY[1] = 11;
		matchPositionY[2] = 12;
	}

	else if (selectedMatchPositionY == 3 && selectedMatchPositionX == 0)
	{
		matchPositionX = 2;

		matchPositionY[0] = 14;
		matchPositionY[1] = 15;
		matchPositionY[2] = 16;
	}
	else if (selectedMatchPositionY == 3 && selectedMatchPositionX == 1)
	{
		matchPositionX = 4;

		matchPositionY[0] = 14;
		matchPositionY[1] = 15;
		matchPositionY[2] = 16;
	}
	else if (selectedMatchPositionY == 3 && selectedMatchPositionX == 2)
	{
		matchPositionX = 6;

		matchPositionY[0] = 14;
		matchPositionY[1] = 15;
		matchPositionY[2] = 16;
	}
	else if (selectedMatchPositionY == 3 && selectedMatchPositionX == 3)
	{
		matchPositionX = 8;

		matchPositionY[0] = 14;
		matchPositionY[1] = 15;
		matchPositionY[2] = 16;
	}
	else if (selectedMatchPositionY == 3 && selectedMatchPositionX == 4)
	{
		matchPositionX = 10;

		matchPositionY[0] = 14;
		matchPositionY[1] = 15;
		matchPositionY[2] = 16;
	}
	else if (selectedMatchPositionY == 3 && selectedMatchPositionX == 5)
	{
		matchPositionX = 12;

		matchPositionY[0] = 14;
		matchPositionY[1] = 15;
		matchPositionY[2] = 16;
	}
	else if (selectedMatchPositionY == 3 && selectedMatchPositionX == 6)
	{
		matchPositionX = 14;

		matchPositionY[0] = 14;
		matchPositionY[1] = 15;
		matchPositionY[2] = 16;
	}
}

void winLose(const short position)
{
	clear();

	if (currentPlayer == 1)
	{
		title("player 1 wins!");

		cout << "	player 1 wins!\n\n";
	}
	else
	{
		title("player 2 wins!");

		cout << "	player 2 wins!\n\n";
	}

	cout << "	would you like to play again?\n\n";

	if (position == 0)
	{
		cout << "	> yes <\n";
	}
	else
	{
		cout << "	yes\n";
	}

	if (position == 1)
	{
		cout << "	> no <\n";
	}
	else
	{
		cout << "	no\n";
	}

	const int keyInput{ _getch() };

	if ((keyInput == 'W' || keyInput == 'w') && position != 0)
	{
		winLose(position - 1);
	}
	else if ((keyInput == 'S' || keyInput == 's') && position != 1)
	{
		winLose(position + 1);
	}
	else if (keyInput == 13 || keyInput == ' ')
	{
		map = presetMap;

		matchesLeft = 16;
		nims = 0;

		selectedMatchPositionY = 0;
		selectedMatchPositionX = 0;

		setMatchPosition();

		if (position == 1)
		{
			menu(0);
		}
	}
	else
	{
		winLose(position);
	}
}

void refresh()
{
	clear();

	if (matchesLeft == 0)
	{
		winLose(0);
	}

	// cout << "selected match: " << selectedMatchPositionX << ", " << selectedMatchPositionY << '\n';
	cout << "matches left: " << matchesLeft << "\n\n";

	/*
	cout << "match x: " << matchPositionX << '\n';
	cout << "match y: ";
	for (int i{}; i < matchPositionY.size(); ++i)
	{
		cout << matchPositionY[i] << ' ';
	}
	cout << "\n\n";
	*/

	cout << "current player nims: " << nims << '\n';
	cout << "current player: " << currentPlayer << "\n\n";

	if (nims == 2)
	{
		cout << "current player has reached maximum nims!";
	}
	cout << "\n\n";

	for (unsigned int i{}; i < map.size(); ++i)
	{
		for (int o{}; o < 35; ++o)
		{
			cout << ' ';
		}

		for (unsigned int o{}; o < map[i].size(); ++o)
		{
			if (i != 0 && i != map.size() - 1 && map[i - 1][o] == ' ' && map[i + 1][o] == '#')
			{
				setTextColor(4);
			}
			else
			{
				setTextColor(6);
			}

			for (unsigned int p{}; p < matchPositionY.size(); ++p)
			{
				if (p == 0)
				{
					continue;
				}

				if (i == matchPositionY[p] && o == matchPositionX)
				{
					setTextColor(8);
				}
			}

			cout << map[i][o] << map[i][o];

			resetTextColor();
		}

		cout << '\n';
	}
}

void help()
{
	clear();
	title("help");

	cout << "	help\n\n";

	cout << "	to win the game, have the opponent remove the last matchstick\n\n";

	cout << "	to nim (remove) a matchstick, press enter\n";
	cout << "	to exit the game, press esc\n";
	cout << "	to end your turn, press g\n\n";
	cout << "	use w, a, s, and d to change the selected match\n\n";

	cout << "	written by chapel1337\n";
	cout << "	started on 12/14/2022, finished on 12/16/2022\n\n";

	cout << "	> okay <\n";

	_getch();
	menu(0);
}

void nimSelectedMatch()
{
	// const int originalmatchPositionX{ matchPositionX };

	/*
	if (random == 0)
	{
		while (matchPositionX != 13)
		{
			for (int i{}; i < matchPositionY.size(); ++i)
			{
				if (presetMap[matchPositionY[i]][matchPositionX - 1] == '#')
				{
					map[matchPositionY[i]][matchPositionX - 1] = '#';
				}

				map[matchPositionY[i]][matchPositionX] = ' ';
				map[matchPositionY[i]][matchPositionX + 1] = '#';
			}

			++matchPositionX;

			sleep_for(milliseconds(75));
			refresh();
		}

		for (int i{}; i < matchPositionY.size(); ++i)
		{
			map[matchPositionY[i]][matchPositionX] = ' ';
		}
	}
	*/

	if (nimAnimations)
	{
		const short random{ getRandom(1, 2) };

		if (random == 1)
		{
			map[matchPositionY[2]][matchPositionX] = ' ';

			refresh();
			sleep_for(milliseconds(250));

			map[matchPositionY[1]][matchPositionX] = ' ';

			refresh();
			sleep_for(milliseconds(250));

			map[matchPositionY[0]][matchPositionX] = ' ';
		}
		else if (random == 2)
		{
			map[matchPositionY[0]][matchPositionX] = ' ';

			refresh();
			sleep_for(milliseconds(250));

			map[matchPositionY[1]][matchPositionX] = ' ';

			refresh();
			sleep_for(milliseconds(250));

			map[matchPositionY[2]][matchPositionX] = ' ';
		}
	}
	else
	{
		for (unsigned int i{}; i < matchPositionY.size(); ++i)
		{
			map[matchPositionY[i]][matchPositionX] = ' ';
		}
	}

	// availableMatches[selectedMatchPositionY][selectedMatchPositionX] = currentPlayer + 1;

	if (map[matchPositionY[0] - 2][matchPositionX] != ' ')
	{
		--selectedMatchPositionX;
		--selectedMatchPositionY;
	}
	else if (map[matchPositionY[2] + 2][matchPositionX] != ' ')
	{
		++selectedMatchPositionX;
		++selectedMatchPositionY;
	}
	else if (map[matchPositionY[0]][matchPositionX + 2] != ' ')
	{
		++selectedMatchPositionX;
	}
	else if (map[matchPositionY[0]][matchPositionX - 2] != ' ')
	{
		--selectedMatchPositionX;
	}

	--matchesLeft;

	setMatchPosition();
}

void getInput()
{
	int keyInput{ _getch() };

	if ((keyInput == 'W' || keyInput == 'w') && map[matchPositionY[0] - 2][matchPositionX] != ' ')
	{
		--selectedMatchPositionX;
		--selectedMatchPositionY;
	}
	else if ((keyInput == 'S' || keyInput == 's') && map[matchPositionY[2] + 2][matchPositionX] != ' ')
	{
		++selectedMatchPositionX;
		++selectedMatchPositionY;
	}
	else if ((keyInput == 'D' || keyInput == 'd') && map[matchPositionY[0]][matchPositionX + 2] != ' ') //(selectedMatchPositionY == 1 && selectedMatchPositionX != 2) && (selectedMatchPositionY == 2 && selectedMatchPositionX != 4) && (selectedMatchPositionY == 3 && selectedMatchPositionX != 6))
	{
		++selectedMatchPositionX;
	}
	else if ((keyInput == 'A' || keyInput == 'a') && map[matchPositionY[0]][matchPositionX - 2] != ' ')
	{
		--selectedMatchPositionX;
	}
	else if (keyInput == 'G' || keyInput == 'g')
	{
		nims = 0;

		if (computerOpponent == 0)
		{
			if (currentPlayer == 0)
			{
				currentPlayer = 1;
			}
			else
			{
				currentPlayer = 0;
			}
		}
		/*
		else if (computerOpponent == 1)
		{
			currentPlayer = 1;

			int turnsRandom{ getRandom(0, 1) };
			int randomY{ getRandom(0, 3) };
			int randomX{ getRandom(0, availableMatches[randomY].size()) };

			while (availableMatches[randomY][randomX] != 0)
			{
				randomY = getRandom(0, 3);
				randomX = getRandom(0, availableMatches[randomY].size());
			}

			selectedMatchPositionY = randomY;
			selectedMatchPositionX = randomX;

			setMatchPosition();
			nimSelectedMatch();
			
			if (turnsRandom == 1)
			{
				while (availableMatches[randomY][randomX] != true)
				{
					randomY = getRandom(0, 3);
					randomX = getRandom(0, availableMatches[randomY].size());
				}

				selectedMatchPositionY = randomY;
				selectedMatchPositionX = randomX;

				setMatchPosition();
				nimSelectedMatch();
			}

			currentPlayer = 0;
		}
		*/
	}
	else if (keyInput == 27)
	{
		menu(0);
	}
	else if ((keyInput == 13 || keyInput == ' ') && nims != 2)
	{
		// added 1, 1 check because i cannot for the life of me get the repositioning to work
		if (selectedMatchPositionY == 1 && selectedMatchPositionX == 1 && map[2][8] == '#')
		{
			getInput();
		}
		else
		{
			++nims;

			nimSelectedMatch();
		}
	}
	else
	{
		getInput();
	}

	setMatchPosition();
	refresh();
	getInput();
}

void options(const short position)
{
	clear();
	title("options");

	cout << "\n	options\n\n";

	/*
	if (position == 0)
	{
		cout << "	> toggle computer opponent <\n";
	}
	else
	{
		cout << "	toggle computer opponent\n";
	}
	*/

	if (position == 0)
	{
		cout << "	> toggle nim animations <\n";
	}
	else
	{
		cout << "	toggle nim animations\n";
	}

	if (position == 1)
	{
		cout << "	> back <\n";
	}
	else
	{
		cout << "	back\n";
	}

	const int keyInput{ _getch() };

	if ((keyInput == 'W' || keyInput == 'w') && position != 0)
	{
		options(position - 1);
	}
	else if ((keyInput == 'S' || keyInput == 's') && position != 1)
	{
		options(position + 1);
	}
	else if (keyInput == 13 || keyInput == ' ')
	{
		switch (position)
		{
			/*
		case 0:
			if (computerOpponent)
			{
				computerOpponent = false;

				clear();

				cout << "	computer opponent disabled\n";
				sleep_for(seconds(2));
			}
			else
			{
				computerOpponent = true;

				clear();

				cout << "	computer opponent enabled\n";
				sleep_for(seconds(2));
			}
			break;
			*/
		case 0:
			if (nimAnimations)
			{
				nimAnimations = false;

				clear();

				cout << "	nim animations disabled\n";
				sleep_for(seconds(2));
			}
			else
			{
				nimAnimations = true;

				clear();

				cout << "	nim animations enabled\n";
				sleep_for(seconds(2));
			}
			break;

		case 1:
			menu(0);
			break;
		}
	}
	else
	{
		options(position);
	}
}

void quit()
{
	for (short i{ 3 }; i > 0; --i)
	{
		clear();
		title("qutting in ", i);

		cout << "	quitting in " << i;

		sleep_for(seconds(1));
	}

	exit(1);
}

void menu(const short position)
{
	clear();
	title("menu");

	cout << "\n	nim\n\n";

	if (position == 0)
	{
		cout << "	> start <\n";
	}
	else
	{
		cout << "	start\n";
	}

	if (position == 1)
	{
		cout << "	> options <\n";
	}
	else
	{
		cout << "	options\n";
	}

	if (position == 2)
	{
		cout << "	> help <\n";
	}
	else
	{
		cout << "	help\n";
	}

	if (position == 3)
	{
		cout << "	> quit <\n";
	}
	else
	{
		cout << "	quit\n";
	}

	const int keyInput{ _getch() };

	if ((keyInput == 'W' || keyInput == 'w') && position != 0)
	{
		menu(position - 1);
	}
	else if ((keyInput == 'S' || keyInput == 's') && position != 3)
	{
		menu(position + 1);
	}
	else if (keyInput == 13 || keyInput == ' ')
	{
		switch (position)
		{
		case 0:
			refresh();
			getInput();
			break;

		case 1:
			options(0);
			break;

		case 2:
			help();
			break;

		case 3:
			quit();
			break;
		}
	}
	else
	{
		menu(position);
	}
}

int main()
{
	menu(0);
}