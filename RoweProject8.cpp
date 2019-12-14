//David Rowe
//COP2000.001
//Project 8 - Class Roster
//Stores student names from class roster in an array, then sorts and displays in ascending alphabetical order

#include <iostream>
#include <fstream>
#include <string>

using std::ifstream;
using std::string;
using std::cout;
using std::endl;
using std::cerr;

//to do
//declare variables - main & class
//open file
	//validate file opened properly
//read file and store data into an array
//close file
//sort array data in ascending alphabetical order
//diplay sorted array data

class Sort
{
private:
	const static int NAMES = 30;		//declare array for holding roster names
	string Roster[NAMES] = { " " };		//initialize array
	ifstream ifile;				//input file object
	void openFile();
	void validate();
	void readFile();
	void closeFile();
	void sortArray();
	void displayRoster();
	   
public:
	void driver();
	Sort();

};

/*******************************************Method Defs*************************************/
//Sort::Sort
//constructor for sorted array
Sort::Sort()
{
	cout << "Student Roster Sorting Program" << endl << endl;
}

//Sort::openFile
//open data file with student names
void Sort::openFile()
{
	ifile.open("Names.txt");
	
	validate();					//confirm file opened properly
}

//Sort::validate
//confirm that data file opened properly
void Sort::validate()
{
	if (!ifile)
	{
		cerr << "Names.txt file did not open properly." << endl;
		exit(9999);
	}
}

//Sort::readFile
//read names from data file into the array
void Sort::readFile()
{
	int i = 0;					//local counter variable

	while (i < NAMES && ifile >> Roster[i])
		i++;
	
	//test
	//for (int k = 0; k < NAMES; k++)
		//cout << Roster[k] << endl;
	//cout << endl << endl;
}

//Sort::closeFile
//close the input file
void Sort::closeFile()
{
	ifile.close();
}

//Sort:SortArray
//sort array names in ascending alphabetical order with "The Bubble Sort"
void Sort::sortArray()
{
	string temp;				//local variable for swaping elements
	bool madeAswap;

	do
	{
		madeAswap = false;
		for (int count = 0; count < (NAMES - 1); count++)
		{
			if (Roster[count] > Roster[count + 1])
			{
				temp = Roster[count];
				Roster[count] = Roster[count + 1];
				Roster[count + 1] = temp;
				madeAswap = true;
			}
		}
	} while (madeAswap);		//loop again while true
}

//Sort:displayRoster
//display sorted array
void Sort::displayRoster()
{
	for (int k = 0; k < NAMES; k++)
		cout << Roster[k] << endl;
	cout << endl << endl;
}

//Sort::driver
//call methods in correct order
void Sort::driver()
{
	openFile();
	readFile();
	closeFile();
	sortArray();
	displayRoster();
}

/*********************************************Driver****************************************/
int main()
{
	Sort sortObj;

	sortObj.driver();

	return 0;
}
