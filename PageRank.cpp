//David Rowe
//COP3530 - Project 2 - Simplified PageRank Algorithm using Adjancey List
//Using some logic from lectures and discussion classes

#include<iostream>
#include <iomanip>
#include<string>
#include<sstream>
#include<vector>
#include<unordered_map>
#include<map>
#include<algorithm>
#include <cstring>
using namespace std;

class AdjList {
private:
    //data structures & iterators
    unordered_map<string, vector<string>> graph;
    unordered_map<string, vector<string>>::iterator iter;
    unordered_map<string, vector<string>>::iterator iter2;
    unordered_map<string, vector<string>>::iterator iter3;
    unordered_map<string, double> ranks;
    unordered_map<string, double>::iterator iter4; 
    //methods
    double getRank(string to);                  //returns current rank of page
    int getOutLink(string to);                  //returns number of outdegree links from current page

public:
    //variables
    double initialRank = 0.0;                   //place holder variable
    int iterations = 0;

    //methods
    void pageInsert(string fro, string to);     //adds page to adjancey list
    void PageRank();                            //updates page rank in given number of iterations
};

//returns current rank of page
double AdjList::getRank(string to)
{
    //use seperate data structure
    iter4 = ranks.find(to);
    if (iter4 != ranks.end())
    {
        return iter4->second;
    }
    return 0.0;
}

//returns number of outdegree links from current page
int AdjList::getOutLink(string to)
{
    iter3 = graph.find(to);
    if (iter3 != graph.end())
    {
        return iter3->second.size();
    }
    return 0;
}

//adds page to adjancey list
void AdjList::pageInsert(string fro, string to)
{
    /***build adj list***/
    graph[fro].push_back(to);
    /***build corresponding structure for rank of each page***/
    ranks[fro] = initialRank;
    //page that is only pointed to but does not point, it still has a rank...
    if (graph.find(to) == graph.end())
    {
        graph[to] = {};
        ranks[to] = initialRank;
    }
}

//updates page rank in given number of iterations
void AdjList::PageRank()
{
    //prints the PageRank of all pages after p powerIterations in
    //ascending alphabetical order of webpages and rounding rank two decimal places
    double sum = 0.0;                           //sums page rank algorithm
    unordered_map<string, double> newRank;                //stores new page ranks until current power iteration completed
    //assigned initial page rank (iter 0)
    for (iter4 = ranks.begin(); iter4 != ranks.end(); ++iter4)
    {
        //store ranks in dedicated map for ranks
        iter4->second = double(1.0 / graph.size());   
    }

    /*TO DO
    determine number of out_degree links for each page
    vector.size() inside of map is number of out_degree links
    create list of pages pointing at current page
        detrmine if there's an edge
        if so, store a list of pages with edges for current page*/

    //total iterations for page rank algorithm
    for (int i = 1; i < iterations; i++)
    {
        //iterate through graph to assign page rank for each page in the adjancey list
        for (iter = graph.begin(); iter != graph.end(); ++iter)
        {
            //iterate through graph to count other pages pointing at current page in the outer loop
            for (iter2 = graph.begin(); iter2 != graph.end(); ++iter2)
            {
                if (iter->first != iter2->first)
                {
                    //create vector of pages being pointed to by inner loop graph
                    vector<string> vect = iter2->second;
                    //search local vector to see if any pages are pointing to current page in outer loop
                    for (auto pages : vect)
                    {
                        //do any pages point to (outer loop) current page??
                        if (pages == iter->first)
                        {
                            //page rank algorithm: outerloop page rank sum = sum + inner loop page rank * (1 / number of outdegree links)
                            sum = sum + (getRank(iter2->first) * (1.0 / getOutLink(iter2->first)));
                        }
                    }
                }
            }
            //store each sum total in map for new page rank 
            newRank[iter->first] = sum;
            //reset sum total for next power iteration
            sum = 0;
        }
        //assign new page ranks before next iterations
        for (iter4 = ranks.begin(); iter4 != ranks.end(); ++iter4)
        {
            //value of 'newRank' map holds new page rank which is assigned to second element in pair inside of first vector element for page 
            iter4->second = newRank[iter4->first];
        }
    }

    //display page ranks of all pages in alphabetical order
    //use map so that data in unordered_map can be sorted
    map<string, double> display;
    map<string, double>::iterator iter5;
    for (iter = graph.begin(); iter != graph.end(); ++iter)
    {
        display[iter->first] = ranks[iter->first];
    }
    
    //display page ranks in map -- automatically sorted in ascending order
    for (iter5 = display.begin(); iter5 != display.end(); ++iter5)
    {
        cout << fixed << setprecision(2) << iter5->first << " " << ranks[iter5->first] << endl;
    }
}

int main()
{
    //create object
    AdjList alObj;
    int no_of_lines, power_iterations;
    string from, to;
    //user input
    cin >> no_of_lines;
    cin >> power_iterations;
    alObj.iterations = power_iterations;
    for (int i = 0; i < no_of_lines; i++)
    {
        //input for Adjacency List graph
        cin >> from;
        cin >> to;
        alObj.pageInsert(from, to);
    }

    //call page rank method
    alObj.PageRank();

    return 0;
}