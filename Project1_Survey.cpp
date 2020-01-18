//David Rowe
//COP2535
//Project 1 - Survey Histogram

#include<iostream>
#include<fstream>
#include<iomanip>

using std::ifstream;

//To do
//Class & Variables/Array
//Open 'survey' file
//		Verify file opened properly
//Read file & store data into array
//Close 'survey' file
//Display results with histogram

class Survey
{
private:
	int static const SIZE = 10;
	int response[SIZE] = { 0 };					//array to hold survey data
	ifstream dataIn;

	//methods
	void openFile();						//open survey file
	void validate();						//confirm file opened properly
	void readFile();						//read file and store results into array
	void closeFile();						//close survey file
	void displayData();						//display survey results with histogram

public:
	void driver();							//execute methods in the correct order
};

/********************************Methods*****************************************/
//Survey::openFile
//open survey file
void Survey::openFile()
{
	dataIn.open("survey.txt");
	validate();
}

//Survey::validate
//confirm file opened properly
void Survey::validate()
{
	if (!dataIn)
	{
		std::cerr << "Survey data file did not open properly.";
		exit(123);
	}
}

//Survey::readFile
//read file and store results into array
void Survey::readFile()
{
	int compare = 0;							//local variable to store survey data for analysis

	while (dataIn >> compare)					//read data into temp variable
	{
		response[compare-1]++;					//increment array count based on survey data
	}
}

//Survey::closeFile
//close survey file
void Survey::closeFile()
{
	dataIn.close();
}

//Survey::displayData
//display survey results with histogram
void Survey::displayData()
{
	using std::cout;
	using std::endl;
	using std::setw;

	cout << "Rating" << "   " << "Frequency" << endl << endl;
	for (int i = 1; i <= SIZE; i++)						//outerloop iterates through 'rating' of 1 - 10
	{
		cout << setw(2) << i << "       ";
		for (int j = 0; j < response[i - 1]; j++)		//innerloop outputs number of '*' based on array element value
		{
			cout << "*";
		}
		cout << endl;
	}
	cout << endl << endl << endl;
}

//Survey::driver
////execute methods in the correct order
void Survey::driver()
{
	openFile();								//open survey file
	readFile();								//read file and store results into array
	closeFile();							//close survey file
	displayData();							//display survey results with histogram
}

/*********************************Main*******************************************/
int main()
{
	//Create instance of class with object
	Survey dataObj;
	//Call driver to execute methods
	dataObj.driver();
}
