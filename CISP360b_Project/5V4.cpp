//CISP360
//T/TH 1:30-2:50pm
//Spring 2017
//Team 13 Project: Dynamic Study Guide and Random Question Generator for C++
//Write a program for students to study C++.

//team13.cpp

#include <iostream>  //cout, cin
#include <cstdlib>   //srand, rand
#include <string>    //string
#include <fstream>   //ifstream
#include <vector>    //vector
#include <iomanip>   //setw, setprecision

using namespace std;

//Prototypes
void welcomeUser();
void inputValue(string, int &);
void getInfo(string &, string &, string &);
void selSubject(string &studentID, string &fullName, string &firstName, int &numQuestionsRequested, int &numAnswersCorrect);
void genTest(string &, int &, int &);
void testMessage(string);
void valInput(string &);
void checkCin();
void askQuestions(vector<string>, vector<string>, int, int &);
void displayResults(string, string, int&, int);
vector<string> getFile(vector<string> *, string);
string concatName(string, string);
vector<string> questions;
vector<string> answers;
int *dynArray(int);

int main()
{
	//Declare variables
	srand((unsigned int)time(NULL)); //Use system time to randomize questions
	string studentID,                //Student Info
		firstName,
		fullName;
	int numQuestionsRequested = 0,   // number of questions requested
		numAnswersCorrect = 0;       // number of answers correct
	 
    // Displays welcome prompt message
	welcomeUser(); 

	// Get info from user
	getInfo(fullName, firstName, studentID); 

	// Select Test Subject
	selSubject(studentID, fullName, firstName,numQuestionsRequested,numAnswersCorrect);

	// Generate Test - currently in selSubject function
	//genTest(firstName, numQuestionsRequested, numAnswersCorrect);
	
	// Display Test Results - currently in selSubject function
	//displayResults(studentID, fullName, numQuestionsRequested, numAnswersCorrect);

	system("pause");
	return 0;
}
// *************************************************************
// Function used to display a greeting when starting the 
// program.
// *************************************************************
void welcomeUser()
{
	cout << "**************************************************" << endl;
	cout << setw(45) << "Welcome to the CISP360 Exam Study Guide" << endl;
	cout << "**************************************************" << endl;
}
// *************************************************************
// Function used to display a message to user 
// *************************************************************
void testMessage(string firstName)
{
	cout << "\nHi " << firstName << "! You'll be taking a test, please answer with True or False.\n\n";
	cout << "How many questions do you want?  ";

}// *************************************************************
// Function used to open and read a document
// and return the contents to a vector
// *************************************************************
vector<string> getFile(vector<string> *vecNames, string description)
{
	string line;
	ifstream fin(description);
	if (fin)
	{
		while (getline(fin, line)) {
			vecNames->push_back(line);
		}
	}
	else
	{
		cout << "We are sorry, there is something wrong with the pathing for the Questions document.";
		cout << endl;
	}
	return *vecNames;
}
//*************************************************************
//  This function displays a query and accepts input value    
//*************************************************************
void inputValue(string description, int &value)
{
	cin >> value;
	while (cin.fail() || value > 50 || value <1) { // If cin fails to receive a value matching the declared data type.
		cin.clear();               // Clear the error flag within cin.
		cin.ignore(10000, '\n');   // Ignore the newline character in the buffer to prevent an infinite loop.
		cout << description;
		cin >> value;
	}
}
//*************************************************************
// This function displays query and accepts input value for   *
// student ID, first name and last name                                                 *
//*************************************************************
void getInfo(string &fullName, string &first, string &id)
{

	string last;	   // last name

	cout << "Please Enter your student ID: ";
	cin >> id;
	cout << "Please Enter your first name: ";
	cin >> first;
	cout << "Please Enter your second name: ";
	cin >> last;

	fullName = concatName(first, last);
}
//*************************************************************
// This function concatentates the first and last name in to
//  one string var
//*************************************************************
string concatName(string first, string last)
{
	string fullName;
	fullName = last + ", " + first;
	return fullName;
}
// ************************************************************
// This function brings in question and answer vectors and
// randomizes order for test
// ************************************************************
void askQuestions(vector<string> questions, vector<string> answers, int numQuestionsRequested, int &numAnswersCorrect)
{
	int r = 0;
	const int NUM_QUESTIONS = 50;
	string ans;
	int *questionsArray = nullptr; // Dynamically allocated array for indexes of questions asked.
	int *answersArray = nullptr; // Dynamically allocated array for indexes of C/IC answers. ( C = 1 and IC = 0)
	questionsArray = dynArray(numQuestionsRequested);
	answersArray = dynArray(numQuestionsRequested);

	for (int i = 0; i < numQuestionsRequested; i++) {

		if (i != 0) { // Checks to make sure it's not the first element.
			do { // Loops until 'r' is a unique number to prevent repeated questions.
				r = rand() % 50 + 1;
				*(questionsArray + i) = r;
			} while ((*(questionsArray + (i - 1))) == r);
		}
		else { // If it's the first element no checks need to be done.
			r = (rand() % 50 + 1);
			*(questionsArray) = r;
		}

		cout << questions[r] << endl;
		cout << "True or False : ";
		cin >> ans;
		valInput(ans);
		if (ans == answers[r]) {
			cout << "\nCORRECT!\n";
			numAnswersCorrect++;
			*(answersArray + i) = 1;
		}
		else {
			cout << "\nIncorrect!\n";
		}
	}
	delete[] questionsArray;
	delete[] answersArray;
}

//*********************************************************************
// This function dynamically allocates
// an integer array of size len with all elements initialized at zero.
//*********************************************************************
int *dynArray(int len) {
	int *vault = nullptr;
	vault = new int[len];

	for (int i = 0; i < len; i++) {
		*(vault + i) = 0;
	}
 	return vault;
}
//********************************************************************
// This function receives the information from the other modules 
// and displays it. 
//********************************************************************
void displayResults(string studentID, string fullName, int &numQuestionsRequested, int numAnswersCorrect)
{
	double grade = (numAnswersCorrect * 1.0 / numQuestionsRequested) * 100;
	cout << endl << endl;
	cout << "====================================================" << endl;
	cout << "Id:   " << studentID << endl;
	cout << "Name: " << fullName << endl;
	cout << "Number of questions: " << numQuestionsRequested << endl;
	cout << "Number of answers correct: " << numAnswersCorrect << endl;
	cout << "You scored " << grade << "%" << endl;

	if (grade > 90)
	{
		cout << "Congrats you will do well on the test! Keep it up!";
	}
	else if (grade > 80)
	{
		cout << "Good job but you need to study more for an A!";
	}
	else if (grade > 70)
	{
		cout << "You are on the right track and you should keep studying.";
	}
	else if (grade > 60)
	{
		cout << "You need to study more or else you will not pass!";
	}
	else
	{
		cout << "You have to study more or else you will fail!";
	}
	cout << endl;
}

//*************************************************************
// Definition of function valInput. This function validates   
// for True or False                            
//*************************************************************
void valInput(string &answer)
{
	do {
		cout << endl;
		//convert lower case to upper case
		if (answer == "true") {
			answer = "True";
		}
		else if (answer == "false") {
			answer = "False";
		}
		if (answer != "True" && answer != "False") {
			cout << "Please enter True or False: ";
			cin >> answer;
			checkCin();
		}
	} while (answer != "True" && answer != "False");
}

//*************************************************************
// Definition of function selSubject.                         *
// This function randomly generates a list of 10 questions for*
// area of study selected                                     *
//*************************************************************

void selSubject(string &studentID, string &fullName,string &firstName,int &numQuestionsRequested, int &numAnswersCorrect)
{
	int choice;
	do {
		cout << "\n        Subject Menu" << endl;
		cout << "------------------------------" << endl;
		cout << "1. Arrays" << endl;
		cout << "2. Pointers" << endl;
		cout << "3. Vectors" << endl;
		cout << "4. Dynamic Arrays" << endl;
		cout << "5. Quit this progam" << endl;
		cout << "------------------------------" << endl;
		cout << "Enter your choice (1-5): ";
		cin >> choice;
		checkCin();
		while (choice > 5 || choice < 1) //Validate entry for number within 1-5 range
		{
			cout << "The valid choices are 1, 2, 3, 4, and 5. Please choose: ";
			cin >> choice;
			checkCin();
		}
		if (choice == 1)
		{
			getFile(&questions, "questionsArrays.txt");
			getFile(&answers, "answersArrays.txt");
			genTest(firstName, numQuestionsRequested, numAnswersCorrect);
			displayResults(studentID, fullName, numQuestionsRequested, numAnswersCorrect);
		}
		else if (choice == 2)
		{
			getFile(&questions, "questionsPointers.txt");
			getFile(&answers, "answersPointers.txt");
			genTest(firstName, numQuestionsRequested, numAnswersCorrect);
			displayResults(studentID, fullName, numQuestionsRequested, numAnswersCorrect);
		}
		else if (choice == 3)
		{
			getFile(&questions, "questionsVectors.txt");
			getFile(&answers, "answersVectors.txt");
			genTest(firstName, numQuestionsRequested, numAnswersCorrect);
			displayResults(studentID, fullName, numQuestionsRequested, numAnswersCorrect);

		}
		else if (choice == 4)
		{
			getFile(&questions, "questionsDynamicArrays.txt");
			getFile(&answers, "answersDynamicArrays.txt");
			genTest(firstName, numQuestionsRequested, numAnswersCorrect);
			displayResults(studentID, fullName, numQuestionsRequested, numAnswersCorrect);

		}

	} while (choice != 5); //If 5 selected exit program
}

//*************************************************************
// Concatentate the first and last name in to one string var
// function
//*************************************************************
void genTest(string &firstName, int &numQuestionsRequested, int &numAnswersCorrect)
{
	testMessage(firstName);
	inputValue("You must enter a number from 1 through 50: ", numQuestionsRequested);
	askQuestions(questions, answers, numQuestionsRequested, numAnswersCorrect);
}
//*************************************************************
// Function to validate cin for data type
//*************************************************************
void checkCin()
{
	while (cin.fail()) {                      // If cin fails to receive a value matching the declared data type.
		cout << "Data Type not permitted.\n"; // Notify the user of error.
		cin.clear();                          // Clear the error flag within cin.
		cin.ignore(10000, '\n');              // Ignore the newline character in the buffer to prevent an infinite loop.
	}
}