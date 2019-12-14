//David Rowe
//COP2000.001
//Project 5 - Highest Division Sales

#include<iostream>
#include<iomanip>
#include<string>

//prototypes
float getSales(std::string div);
void validate(float& s);
void findHighest(float n, float s, float e, float w);

int main()
{
	//To do list
	//Declare variables
	//Get user input for division sales of 4 different divisions
		//call getSales function for North, South, East, and West
			//validate user input
	//Find highest grossing division and display division with sales figure

	using std::string;
	//variables
	float north;						//user input for north division sales
	float south;						//user input for south division sales
	float east;							//user input for east division sales
	float west;							//user input for west division sales
	const string NORTH = "North";		//division assignment variable for getSales
	const string SOUTH = "South";		//division assignment variable for getSales
	const string EAST = "East";			//division assignment variable for getSales
	const string WEST = "West";			//division assignment variable for getSales

	//Get north division sales data from user	/*Would normally call all the getSales functions from one sub-function*/
	north = getSales(NORTH);

	//Get south division sales data from user
	south = getSales(SOUTH);

	//Get east division sales data from user
	east = getSales(EAST);

	//Get west division sales data from user
	west = getSales(WEST);

	//Determine highest grossing division and display results
	findHighest(north, south, east, west);

	system("pause");
	return 0;
}
/*********************************************Function Definitions***********************************/

//Function: getsales
//get user input for division sales and return data to main after validation

float getSales(std::string div)
{
	using std::cout;
	using std::cin;
	using std::endl;

	//local variable
	float sales;		//local variable used to send back sales data for each division

	cout << "Please enter quarterly sales data for the " << div << " Division: ";
	fseek(stdin, 0, SEEK_END);
	cin >> sales;
	fseek(stdin, 0, SEEK_END);
	cout << endl;

	//validate user input data for quarterly sales
	validate(sales);

	//return sales data back to divisions in main
	return sales;
}

//Function: validate
//validates user input for sales data ensuring no negative values or character input
void validate(float& s)
{
	using std::cin;
	using std::cout;
	using std::endl;

	while (!cin || s < 0)
	{
		cout << endl;
		cout << "Invalid input, please enter non-negative numbers only: ";
		cin.clear();
		fseek(stdin, 0, SEEK_END);
		cin >> s;
		fseek(stdin, 0, SEEK_END);
	}
}

//Function: findHighest
//Determine highest grossing division and display results
void findHighest(float n, float s, float e, float w)
{
	using std::cout;
	using std::endl;
	using std::fixed;
	using std::setprecision;

	cout << endl << fixed << setprecision(2);	//formatting

	if (n > s && n > e && n > w)				//selection structure for determining highest sales division
		cout << "The North Division has the highest quarterly sales at: $" << n << endl << endl << endl;
	else if (s > n && s > e && s > w)
		cout << "The South Division has the highest quarterly sales at: $" << s << endl << endl << endl;
	else if (e > n && e > s && e > w)
		cout << "The East Division has the highest quarterly sales at: $" << e << endl << endl << endl;
	else if (w > n && w > s && w > e)
		cout << "The West Division has the highest quarterly sales at: $" << w << endl << endl << endl;
	else
		cout << "There is a tie between 2 or more divisions." << endl << endl << endl;
}
