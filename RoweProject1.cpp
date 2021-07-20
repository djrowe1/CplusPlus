//David Rowe
//COP3530 - Gator AVL Project 1
//Some code and logic based from class lectures and Weiss textbook

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class StudentInfo
{
private:
    struct Node
    {
        //node element data members
        string GatorID;
        string Name;
        int bf;
        Node* left;
        Node* right;

        Node(string id = "", string student = "", int balFact = 0, Node* left1 = nullptr, Node* right1 = nullptr)
        {
            GatorID = id;
            Name = student;
            bf = balFact;
            left = left1;
            right = right1;
        }
    };

    //AVL tree property methods
    Node* insertStudent(Node* root, string idNum, string Name);    //insert student record node with id and name
    Node* removeStudent(Node* root, string idNum);                 //remove stduent record node based on id number
    bool searchID(Node* root, string idNum);                       //return boolean based record search with student id number
    bool searchName(Node* root, string name);                   //return boolean based record search with student name
    bool nameVal(string name);                                  //validate name input
    bool idVal(string id);                                         //validate id number input
    void displayInorder(Node* root);                            //display student records inorder
    void inHelper(Node* root, vector<Node*>& list);             //helper function for display inorder
    void displayPreorder(Node* root);                           //display student records preorder
    void preHelper(Node* root, vector<Node*>& list);             //helper function for display preorder
    void displayPostorder(Node* root);                          //display student records postorder
    void postHelper(Node* root, vector<Node*>& list);             //helper function for display postorder
    void displayLevelCount(Node* root);                         //display number of tree levels
    void removeInorder(Node* root, int n);                      //remove nth student record based on inorder traversal

    //tree-balance management methods
    int height(Node* root);         //return max height of tree node
    int BalFact(Node* root);        //return balance factor of tree node
    int getNumNode(Node* root);     //return number of records in tree
    Node* smallestID(Node* root);   //return pointer to node with smallest id number
    Node* rotateL(Node* root);      //perform left rotation on right right case
    Node* rotateR(Node* root);      //perform right rotation on left left case
    Node* rotateLR(Node* root);     //perform left right rotation on left right case
    Node* rotateRL(Node* root);     //perform right left rotation on right left case

public:
    StudentInfo();                  //class object constructor for instance of tree structure
    void driver();                  //execute methods in proper order
};

//may need static variable to avoid repitive displays during recursion
static int counter = 0;
static bool toggle = false;

/**********************Class Methods**********************/
//constructor
StudentInfo::StudentInfo()
{
    //not sure if I need this constructor yet
}

//insert student record node with id and name
StudentInfo::Node* StudentInfo::insertStudent(Node* root, string idNum, string Name)
{
    //base case with no records in tree
    if (root == nullptr)
    {
        Node* record = new Node(idNum, Name);
        cout << "successful" << endl;
        return record;
    }
    //left subtree insertion
    if (idNum < root->GatorID)
        root->left = insertStudent(root->left, idNum, Name);
    //right subtree insertion
    else if (idNum > root->GatorID)
        root->right = insertStudent(root->right, idNum, Name);
    else
    {
        //pre-existing Gator ID num
        cout << "unsuccessful" << endl;
        return root;
    }

    //add new height value to current node
    
    //check balance factor of existing root record
    root->bf = BalFact(root);

    //perform rotations as needed to balance AVL tree
    //perform right rotation on left left case
    if (root->bf > 1 && idNum < root->left->GatorID)
        return rotateR(root);
    //perform left rotation on right right case
    else if (root->bf < -1 && idNum > root->right->GatorID)
        return rotateL(root);
    //perform left right rotation on left right case
    else if (root->bf > 1 && idNum > root->left->GatorID)
        return rotateLR(root);
    //perform right left rotation on right left case
    else if (root->bf < -1 && idNum < root->right->GatorID)
        return rotateRL(root);
    //no need for rotation
    return root;
}

//remove stduent record node based on id number
//based code logic from professor Resch BST - slides - 8
StudentInfo::Node* StudentInfo::removeStudent(Node* root, string idNum)
{
    //empty tree case
    if (root == nullptr)
    {
        cout << "unsuccessful" << endl;
        return root;
    }
    //local variables
    string branch = "";
    Node* newParent = root;
    Node* parent = root;
    Node* child = root;
    Node* travRoot = root;
    //remove student record node based on id number
    while (true)
    {
        //remove matching student record
        if (idNum == child->GatorID)
        {
            //case with no child
            if (child->left == nullptr && child->right == nullptr)
            {
                if (branch == "lBranch")        //will always be false on first pass
                    parent->left = nullptr;
                else if (child == root)
                    root = nullptr;
                else
                    parent->right = nullptr;
            }

            //assign parent to child left
            else if (child->left != nullptr && child->right == nullptr)
            {
                if (branch == "lBranch")        //will always be false on first pass
                    parent->left = child->right;
                else if (child == root)
                    child->right = root->right;
                else
                    parent->right = child->left;
            }

            //assign parent to child child of root
            else if (child->left == nullptr && child->right != nullptr)
            {
                if (branch == "lBranch")        //will always be false on first pass
                    parent->left = child->right;
                else if (child == root)
                    root = child->right;
                else
                    parent->right = child->right;
            }

            //case with two children
            else
            {
                //no right child on left side of local root child
                if (child->left->right == nullptr)
                {
                    if (child == root)
                    {
                        child->left->right = parent->right;
                        root = child->left;
                    }
                    else
                        parent->left = child->left;
                }

                //locate furtherest right node of left branch
                else
                {
                    //assign local node to left side of child
                    travRoot = child->left;
                    while (true)
                    {
                        if (travRoot->right == nullptr)
                        {
                            if (travRoot->GatorID < parent->GatorID)
                                parent->left = travRoot;
                            else
                                parent->right = travRoot;
                            //finish assignments
                            newParent->right = nullptr;
                            travRoot->left = child->left;
                            travRoot->right = child->right;
                            break;
                        }
                        else
                        {
                            newParent = travRoot;
                            travRoot = travRoot->right;
                        }
                    }
                }
            }
            cout << "successful" << endl;
            return root;
        }
        //traverse to correct node or to bottom
        else if (idNum > child->GatorID && child->right != nullptr)
        {
            parent = child;
            branch = "rBranch";
            child = child->right;
        }

        else if (idNum < child->GatorID && child->left != nullptr)
        {
            parent = child;
            branch = "lBranch";
            child = child->left;
        }
        //no student record found
        else if (idNum != child->GatorID)
        {
            cout << "unsuccessful" << endl;
            return root;
        }
    }
}

//return boolean based record search with student id number
bool StudentInfo::searchID(Node* root, string idNum)
{
    //case with no records
    if (root == nullptr)
    {
        cout << "unsuccessful" << endl;
        return false;
    }
    //case with matching id number
    if (idNum == root->GatorID)
    {
        cout << root->Name << endl;
        return true;
    }
    //traverse left branch as needed
    if (idNum < root->GatorID)
        searchID(root->left, idNum);
    //traverse right branch as needed
    if (idNum > root->GatorID)
        searchID(root->right, idNum);
    return false;
}

//return boolean based record search with student name
bool StudentInfo::searchName(Node* root, string name)
{
    //track progress through nodes
    //counter--;
    //case with no records
    if (root == nullptr)
    {
        return false;
    }
    //case with matching name
    if (name == root->Name)
    {
        cout << root->GatorID << endl;
        toggle = true;
        return true;
    }
    //end of tree with no match
    /*if (counter == 1)
    {
        cout << "unsuccessful" << endl;
        return false;
    }*/
    //traverse tree to search records
    searchName(root->left, name);
    searchName(root->right, name);

    if (toggle)
        return true;
    else
        return false;
}

//validate name input
bool StudentInfo::nameVal(string name)
{
    if (name.find_first_of("#$%*\\&@!^()0123456789-+=~/{[}]<>,.;:`_|\"?") == string::npos)     //ensures upper or lower case alphabet letters
        return true;
    else
        return false;
}

//validate id number input
bool StudentInfo::idVal(string id)
{
    //check that length is 8 digits long
    //cout << id.size() << endl;
    if (id.size() != 8)
        return false;
    //iterate through string to check for digits
    //id = id.substr(1);
    for (char const& test : id)
    {
        if (isdigit(test) == 0)
        {
            cout << id << endl;
            return false;
        }
    }
    return true;
}

//display student records inorder
void StudentInfo::displayInorder(Node* root)
{
    //create vector to hold student record list inorder
    vector<Node*> list;
    //utilize helper function with recursion to populate vector
    inHelper(root, list);
    //display student records inorder with vector list
    for (unsigned int i = 0; i < list.size(); i++)
    {
        if (i == list.size() - 1)       //no coma after last name
            cout << list[i]->Name;
        else
            cout << list[i]->Name << ", ";
    }
}

//helper function for display inorder
void StudentInfo::inHelper(Node* root, vector<Node*>& list)
{
    if (root == nullptr)
        return;
    else
    {
        inHelper(root->left, list);
        list.push_back(root);
        inHelper(root->right, list);
    }
}

//display student records preorder
void StudentInfo::displayPreorder(Node* root)
{
    //create vector to hold student record list inorder
    vector<Node*> list;
    //utilize helper function with recursion to populate vector
    preHelper(root, list);
    //display student records inorder with vector list
    for (unsigned int i = 0; i < list.size(); i++)
    {
        if (i == list.size() - 1)       //no coma after last name
            cout << list[i]->Name;
        else
            cout << list[i]->Name << ", ";
    }
}

//helper function for display preorder
void StudentInfo::preHelper(Node* root, vector<Node*>& list)
{
    if (root == nullptr)
        return;
    else
    {
        list.push_back(root);
        preHelper(root->left, list);
        preHelper(root->right, list);
    }
}

//display student records postorder
void StudentInfo::displayPostorder(Node* root)
{
    //create vector to hold student record list inorder
    vector<Node*> list;
    //utilize helper function with recursion to populate vector
    postHelper(root, list);
    //display student records inorder with vector list
    for (unsigned int i = 0; i < list.size(); i++)
    {
        if (i == list.size() - 1)       //no coma after last name
            cout << list[i]->Name;
        else
            cout << list[i]->Name << ", ";
    }
}

//helper function for display postorder
void StudentInfo::postHelper(Node* root, vector<Node*>& list)
{
    if (root == nullptr)
        return;
    else
    {
        postHelper(root->left, list);
        postHelper(root->right, list);
        list.push_back(root);
    }
}

//display number of tree levels
void StudentInfo::displayLevelCount(Node* root)
{
    cout << height(root) << endl;
}

//remove nth student record based on inorder traversal
void StudentInfo::removeInorder(Node* root, int n)
{
    //create vector to hold student records in order
    vector<Node*> list;
    //push student record tree into a vector inorder
    inHelper(root, list);
    //delete nth record based on inorder traversal stored in vector
    removeStudent(root, list[n]->GatorID);
}

/***tree-balance management methods***/
//return max height of tree node
int StudentInfo::height(Node* root)
{
    //base case where height is 0
    if (root == nullptr)
        return 0;
    else
    {
        int depth = (1 + std::max(height(root->left), height(root->right)));
        return (depth);
    }
}

//return balance factor of tree node
int StudentInfo::BalFact(Node* root)
{
    //case with no branches
    if (root == nullptr)
        return 0;
    else
    {
        int bal = height(root->left) - height(root->right);
        return bal;
    }
}

//return number of student records in tree
int StudentInfo::getNumNode(Node* root)
{
    vector<Node*> list;
    inHelper(root, list);
    counter = list.size();
    return counter;
}

//return pointer to node with smallest id number
StudentInfo::Node* StudentInfo::smallestID(Node* root)
{
    //traversal node
    Node* smallest = root;
    //move down left branches to smallest record
    while (smallest->left != nullptr)
        smallest = smallest->left;
    return smallest;
}

//perform left rotation on right right case
StudentInfo::Node* StudentInfo::rotateL(Node* root)
{
    Node* newParent = root->right;
    root->right = newParent->left;
    newParent->left = root;
    //update balance factor for root and newParent
    root->bf = BalFact(root);
    newParent->bf = BalFact(newParent);
    return newParent;
}

//perform right rotation on left left case
StudentInfo::Node* StudentInfo::rotateR(Node* root)
{
    Node* newParent = root->left;
    root->left = newParent->right;
    newParent->right = root;
    //update balance factor for root and newParent
    root->bf = BalFact(root);
    newParent->bf = BalFact(newParent);
    return newParent;
}

//perform left right rotation on left right case
StudentInfo::Node* StudentInfo::rotateLR(Node* root)
{
    root->left = rotateL(root->left);        //critical concept
    return rotateR(root);
}

//perform right left rotation on right left case
StudentInfo::Node* StudentInfo::rotateRL(Node* root)
{
    Node* newRoot;
    root->right = rotateR(root->right);
    newRoot = rotateL(root);
    return newRoot;
}

//execute methods in proper order
void StudentInfo::driver()
{
    //execute methods from menu with current object
    //local variables
    int num = 0;
    string idNum = "";
    int linePos = 0;
    int nPos = 0;
    string name = "";
    string data = "";
    string command = "";
    Node* root = nullptr;

    //obtain user input
    cin >> num;

    //parse and process input based on num of commands given
    for (int i = 0; i <= num; i++)
    {
        //process current line of input
        getline(cin, data);
        //setup index for position in the line with first space
        linePos = data.find_first_of(' ');
        //read method command
        command = data.substr(0, linePos);
        //advance index of line position
        data = data.substr(linePos + 1);

        //follow menu command read from line
        if (command == "insert")
        {
            //advance line position to first quote
            data = data.substr(1);
            //move line position index to last quote
            linePos = data.find_first_of('\"');
            //read student name from line
            name = data.substr(0, linePos);
            //read student id number from line
            idNum = data.substr(linePos + 2);
            //idNum = idNum.substr(1);
            //validate student name and id number
            if (nameVal(name) && idVal(idNum))
            {
                //create and insert new student record
                root = insertStudent(root, idNum, name);
            }
            else
                cout << "unsuccessful" << endl;
        }
        //remove student record from tree based on id number
        if (command == "remove")
        {
            //read student id number for record removal
            idNum = data;
            root = removeStudent(root, idNum);
        }
        //search tree for student record based on id number or name
        if (command == "search")
        {
            //search student records by name
            if (data[0] == '"')
            {
                //read student name from line
                name = data.substr(1, data.length() - 2);
                //reset recursion trip counter to avoid duplicate messages
                counter = getNumNode(root);
                toggle = false;
                bool success = searchName(root, name);
                if (!success)
                    cout << "unsuccessful" << endl;
            }
            //search student records by id number
            else
            {
                idNum = data;
                searchID(root, idNum);
            }
        }

        //display student records inorder
        if (command == "printInorder")
        {
            displayInorder(root);
            cout << endl;
        }
        //display student records preorder
        if (command == "printPreorder")
        {
            displayPreorder(root);
            cout << endl;
        }
        //display student records postorder
        if (command == "printPostorder")
        {
            displayPostorder(root);
            cout << endl;
        }
        //display level count of tree
        if (command == "printLevelCount")
        {
            displayLevelCount(root);
        }
        //remove nth inorder student record from tree
        if (command == "removeInorder")
        {
            removeInorder(root, stoi(data));
        }
    }
}

/*************************************Main***************************************/
int main()
{
    //create object and call its driver
    StudentInfo studObj;
    studObj.driver();
    return 0;
}