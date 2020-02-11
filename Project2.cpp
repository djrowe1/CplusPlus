//David Rowe
//COP2535
//Project 2 - Sorting & Searching Algorithm Analysis
#include<iostream>
#include<fstream>
#include<iomanip>

using std::ifstream;

//To do
//Class & Variables with 2 Arrays
//Open 'random' file
//		Verify file opened properly
//Read file & store the same data into 2 seperate arrays
//Close 'survey' file
//Sort Array1 with the 'bubble sort' and count number of exchanges
//Sort Array2 with the 'selection sort' and count number of exhanges
//Search Array1 with a 'linear search' for value 869 and count number of comparisons
//Search Array2 with a 'binary search' for value 869 and count number of comparisons
//Display results of performance

class Algo
{
private:
	int static const SIZE = 200;
	int static const LOOPS = 4;			
	int array1[SIZE] = { 0 };			//array for bubble sort & linear search
	int array2[SIZE] = { 0 };			//array for selection sort & binary search
	int iteration[LOOPS] = { 0 };		//array to hold number of exchanges and comparisons
	ifstream dataIn;
	int bubbleCount = 0;				//variable to hold exchange count returned from method
	int selectCount = 0;				//variable to hold exchange count returned from method
	int linearCount = 0;				//variable to hold comparision count returned from method
	int binaryCount = 0;				//variable to hold comparision count returned from method OR
	
	//methods
	void openFile();					//open random file
	void validate();					//confirm file opened properly
	void readFile();					//read file and store values into arrays
	void closeFile();					//close random file
	void bubbleSort();					//Sort Array1 with the 'bubble sort' and count number of exchanges
	void selectSort();					//Sort Array2 with the 'selection sort' and count number of exhanges
	void linearSearch();				//Search Array1 with a 'linear search' for value 869 and count number of comparisons
	void binarySearch();				//Search Array2 with a 'binary search' for value 869 and count number of comparisons
	void displayResults();				//display performance results of sorts and searches

public:
	void driver();						//execute methods in the correct order
};

/******************************Method Defs****************************************/
//Algo::openFile
//open the random file
void Algo::openFile()
{
	dataIn.open("random.txt");
	validate();
}

//Algo::valiadte
//confirm file opened properly
void Algo::validate()
{
	if (!dataIn)
	{
		std::cerr << "Random data file did not open properly.";
		exit(123);
	}
}

//Algo::readFile
//read file and store values into arrays
void Algo::readFile()
{
	int values = 0;						//local variable to store random values into arrays
	int index = 0;						//local counter variable for iterating arrays

	while (dataIn >> values)			//read data values into temp variable
	{
		array1[index] = values;			//store data value into array1
		array2[index] = values;			//store data value into array2
		index++;						//increment index counter for arrays
	}
}

//Algo::closeFile
//close random file
void Algo::closeFile()
{
	dataIn.close();
}

//Algo::bubbleSort
//Sort Array1 with the 'bubble sort' and return number of exchanges
void Algo::bubbleSort()
{
	int temp;
	bool madeAswap;

	do
	{
		madeAswap = false;
		for (int count = 0; count < (SIZE - 1); count++)
		{
			if (array1[count] > array1[count + 1])			//swaps values of elements if first-position element > second-position element
			{
				temp = array1[count];						//stores first-position element into temp variable
				array1[count] = array1[count + 1];			//re-assigns f-p element with the value of the second-position element
				array1[count + 1] = temp;					//re-assigns s-p element with the value of the f-p element
				madeAswap = true;							//toggles boolean flag to keep while loop iterating
				iteration[0]++;								//counts number of exchanges performed by bubble sort
			}
		}
	} while (madeAswap);									//Continue sorting loop while true
}

//Algo::selectSort
//Sort Array2 with the 'selection sort' and return number of exhanges
void Algo::selectSort()
{
	int startScan, minIndex, minValue;

	for (startScan = 0; startScan < (SIZE - 1); startScan++)
	{
		minIndex = startScan;
		minValue = array2[startScan];							//minValue is first-position element

		for (int index = startScan + 1; index < SIZE; index++)	//iterates once for each pass of the inner array's sort
		{
			if (array2[index] < minValue)						//finds smallest remaining value to be swapped
			{	minValue = array2[index];						//holds new lowest value found on current iteration
				minIndex = index;								//holds old element location of lowest value for swapping with higher value
			}
		}
		array2[minIndex] = array2[startScan];					//stores higher value (previous lowest value) in (current) lowest values old location
		array2[startScan] = minValue;							//Stores current lowest value in the current element iteration
		iteration[1]++;											//counts number of exchanges performed by selection sort
	}
}

//Algo::linearSearch
//Search Array1 with a 'linear search' for value 869 and return number of comparisons
void Algo::linearSearch()
{
	int nugget = 869;							//search value
	int index = 0;
	int position = -1;
	bool found = false;

	while (index < SIZE && !found)
	{
		if (array1[index] == nugget)
		{
			found = true;						//toggles flag to break loop if value found
			position = -1;						//assigns found value element location to variable
		}
		index++;
		iteration[2]++;							//counts number of comparisons performed by linear search
	}
}

//Algo::binarySearch
//Search Array2 with a 'binary search' for value 869 and return number of comparisons
void Algo::binarySearch()
{
	int first = 0,
		last = SIZE - 1,
		middle,
		position = -1,
		nugget = 869;
	bool found = false;

	while (!found && first <= last)
	{
		middle = (first + last) / 2;
		iteration[3]++;							//counts number of comparisons performed by binary search
		if (array2[middle] == nugget)
		{
			found = true;						//toggles flag to break loop if value found
			position = middle;					//assigns found value element location to variable
		}
		else if (array2[middle] > nugget)		//if value is in first half of array
			last = middle - 1;
		else
			first = middle + 1;					//if value is in last half of array
	}
}

//Algo::displayResults
//display performance results of sorts and searches
void Algo::displayResults()
{
	using std::cout;
	using std::endl;

	cout << "Sort and Search Alogrithm Analysis" << endl << endl;
	cout << "The number of exchanges performed by the bubble sort: " << iteration[0] << endl;
	cout << "The number of exchanges performed by the selection sort: " << iteration[1] << endl << endl;
	cout << "The number of comparisons made by the linear search: " << iteration[2] << endl;
	cout << "The number of comparisons made by the binary search: " << iteration[3] << endl << endl;
}

//Algo::driver
//execute methods in the correct order
void Algo::driver()
{
	openFile();
	readFile();
	closeFile();
	bubbleSort();
	selectSort();
	linearSearch();
	binarySearch();
	displayResults();
}

/*********************************Main*******************************************/
int main()
{
	Algo aObj;
	aObj.driver();
}