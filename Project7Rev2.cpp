//David Rowe
//COP2000.001
//Project 7 REV 2 - November Temperature Statistics
//Determines the number of days in November where the temperature was above, below, and at the daily average.

#include <iostream>
#include <fstream>

using std::ifstream;
using std::cout;
using std::cin;
using std::endl;
using std::cerr;

//to do
//declare variables - main & class
//open file
	//validate file opened properly
//read file
//calculate average
//assign statistics to arrays
//close file
//display results

class Averages
{
private:
	int sumAvg;						//calculated value - holds the average temperature for the month
	const static int DAYS = 3;		//number of array elements
	int stat[DAYS];					//array holds statistical data for daily temps in a month
	ifstream inNov;					//input file

	void openFile();
	void validate();
	void readFile();
	void calcAvg();
	void closeFile();
	void displayStats();

public:
	Averages();
	void driver();
};

/**********************************Method Definitions*************************************/

//Averages::Averages
//constructor for daily temperature averages
Averages::Averages()
{
	//initialize member variables
	sumAvg = 0;

	//initialize array elements to zero
	for (int set = 0; set < DAYS; set++)
	{
		stat[set] = 0;
	}
}

//Averages::openfile
//open the NovTemps.txt file for processing
void Averages::openFile()
{
	inNov.open("NovTemps.txt");

	//test that file opened properly
	validate();
}

//Averages::validate
//validate that input file has opened properly
void Averages::validate()
{
	if (!inNov)
	{
		cerr << "NovTemps.txt file did not open properly." << endl;
		exit(9999);
	}
}

//Averages::readFile
//read daily temps from input file and assign daily temp values to arrays
void Averages::readFile()
{
	//find the average daily temp for the month
	calcAvg();

	//count daily temp statistics and assign to the correct array element
	int compare = 0;			//local variable for comparing daily temps to average

	while (inNov >> compare)
	{
		if (compare < sumAvg)
			stat[0]++;
		else if (compare == sumAvg)
			stat[1]++;
		else if (compare > sumAvg)
			stat[2]++;
	}
}

//Averages::calcAvg
//calculate the average daily temp for the month
void Averages::calcAvg()
{
	int sum = 0;				//local variable for adding daily temps
	int total = 0;				//local variable for holding the total sum of daily temps
	int count = 0;				//local variable for counting number of days in the month

	//finds the average daily temp for the month
	while (inNov >> sum)
	{
		total = total + sum;
		count = count + 1;
	}

	sumAvg = total / count;		//holds the daily average temperature for the month
	inNov.clear();				//clear eof
	inNov.seekg(0);				//seek beginning of file
}

//Averages::closeFile
//close the input file
void Averages::closeFile()
{
	inNov.close();
}

//Averages::displayStats
//display array statistics showing daily temp ranges for the month
void Averages::displayStats()
{
	cout << "Daily Temperature Average for the month was: " << sumAvg << " degrees." << endl << endl;
	cout << "The number of days in the month below average temperature was: " << stat[0] << " days." << endl;
	cout << "The number of days in the month that were average temperature: " << stat[1] << " days." << endl;
	cout << "The number of days in the month above average temperature was: " << stat[2] << " days." << endl << endl;
}

//Averages::driver
//calls method definitions in correct order
void Averages::driver()
{
	openFile();
	readFile();
	closeFile();
	displayStats();
}

/*************************************Driver**********************************************/
int main()
{
	Averages avgObj;

	avgObj.driver();

	return 0;
}