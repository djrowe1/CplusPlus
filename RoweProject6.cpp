//David Rowe
//COP2000.001
//Project 6 - Game of chance using OOP

#include<iostream>
#include<ctime>
#include<cstdlib>

using std::cout;
using std::cin;
using std::endl;

//To do
//declare variables - class and main()
//create class named Game
	//instantiate object for Game in main()
	//create constructor for seeding generator and setting initial variables - Game()
//promp player for starting cash value - void setBalance()
	//validate player's input, at least $1.00 - void validateBalance()
//start loop in driver method
	//call generator to produce value between 1 and 6 - void roll()
	//display results of the roll (odd or even) and the player's updated balance - void display()
	//ask player if they want to roll again again (if applicable) or quit - void again()
		//validate player's response (y or n) - void validateAgain()
//return loop while player's response is 'y' and has balance of at least $1
//diplsay game over with ending balance - endGame()

class Game
{
private:
	int balance;				//holds player's balance, initially player input
	int dieroll;				//value of random number generated
	char another;				//player input, play again?

	void validateBalance(int& b);		//checks for balance of at least $1.00 entered by player
	void validateAgain(char& a);		//confirms (y or n) entered by player

public:
	Game();						//constructor that will seed generator and set initial balance to zero
	void setBalance();			//holds initial balance entered by player
	void roll();				//calls random generator to return a value between 1 and 6
	void display();				//displays results of roll along with player's updated balance
	void again();				//ask player if they want to roll again or quit
	void driver();				//to call methods in appropriate order
	void endGame();				//display end of game message with player's ending balance
};

/*************************************Method Definitions*********************************************/

//Game: Game
//constructor for class Game
Game::Game()
{
	//seed the random generator
	srand(time(NULL));

	//initialize variables
	balance = 0;
	dieroll = 0;
	another = 'y';				//set to initially enter loop in driver method
}

//Game: setBalance()
//prompts player for starting balance and validates input
void Game::setBalance()
{
	cout << "Rock Your World!!!" << endl << endl;
	cout << "Enter your starting balance (minimum of $1 to play): $";
	cin >> balance;
	cout << endl;

	//validate starting balance
	validateBalance(balance);

	cout << "Starting balance = $" << balance << endl << endl;
}

//Game: validateBalance()
//validate player's starting balance is at least $1
void Game::validateBalance(int& b)
{
	while (!cin || b < 1)
	{
		cout << "Invalid amount entered, please try again: $";
		cin.clear();
		fseek(stdin, 0, SEEK_END);
		cin >> b;
		cout << endl;
	}
}

//Game: roll()
//Random generator will produce a number between 1 and 6
void Game::roll()
{
	dieroll = rand() % 6 + 1;			//roll value between 1 and 6
	cout << "Rolling..." << endl <<endl;
}

//Game: updateBalance()
//update player's current balance based on even/odd roll
void Game::display()
{
	if (dieroll % 2 == 0)				//determines if roll is even
	{
		balance = balance + 1;			//adds $1 to player's balance
		cout << "Yeah!!! Even rolled, you win $1" << endl << endl;
		cout << "Your new balance = $" << balance << endl << endl;
	}
	else
	{
		balance = balance - 1;			//subtracts $1 from player's balance
		cout << "Sorry! Odd rolled, you lose $1" << endl << endl;
		cout << "Your new balance = $" << balance << endl << endl;
	}
}

//Game: again()
//ask player if they want to roll again or quit
void Game::again()
{
	if (balance >= 1)					//only asks player for another roll if they have a balance of $1 or more
	{
		cout << "Do you want to roll again? (y=yes, n=no): ";
		fseek(stdin, 0, SEEK_END);
		cin >> another;
		cout << endl;

		//validate player's answer
		validateAgain(another);
	}
}

//Game: validateAgain()
//confirm (y or n) was entered by player
void Game::validateAgain(char& a)
{
	a = tolower(a);
	while (a != 'y' && a != 'n')
	{
		cout << "Invalid option selected, please try again. (y=yes, n=no): ";
		fseek(stdin, 0, SEEK_END);
		cin >> a;
		a = tolower(a);
		cout << endl;
	}
}
//Game: endGame()
//display end of game message with player's ending balance
void Game::endGame()
{
	cout << "Game over. Your end balance = $" << balance << endl << endl;
	cout << "Thanks for playing!!!" << endl << endl << endl;
}

//Game: driver()
//driver method used to execute methods in correct sequence
void Game::driver()
{
	//set validated balance entered by player
	setBalance();

	//loop while player wants to roll and has a minimum balance of $1
	while (another == 'y' && balance >= 1)
	{
		//call random generator to produce roll
		roll();

		//update balance based on roll
		display();

		//ask player if they want to roll again
		again();
	}
	
	//display end of game message with player's ending balance
	endGame();
}

/****************************************Driver***********************************/

int main()
{
	//instantiate an object for Game class
	Game gameobj;

	//call driver method to execute code methods in correct sequence
	gameobj.driver();

	system("pause");
	return 0;
}