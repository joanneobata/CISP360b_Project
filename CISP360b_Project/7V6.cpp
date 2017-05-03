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

// Global Variable
const int MaxQs = 25;

//Prototypes
void welcomeUser();
void inputValue(string, int &);
void getInfo(string &, string &, string &);
void selSubject(vector<string> &, vector<string> &);
void genTest(vector<string>, vector<string>, string, int &, int &);
void testMessage(string);
void valInput(string &);
void checkCin();
void askQuestions(vector<string>, vector<string>, int, int &);
void displayResults(string, string, vector<int>, vector<int>, int);
void getFile(vector<string> &, string);
void valYesNo(char &);
string concatName(string, string);

int *dynArray(int);
bool searchArr(int *, int, int);

int main()
{
	//Declare variables
	srand((unsigned int)time(NULL)); //Use system time to randomize questions
	string studentID,                //Student Info
		   firstName,
		   fullName;
	vector<string> questions;
	vector<string> answers;
	vector<int> qAsked;
	vector<int> qRight;
	int numQuestionsRequested = 0,   // number of questions requested
		numAnswersCorrect = 0;       // number of answers correct
	int i = 0; // basic counter for each iteration of the loop in main.
	char yesno;

	// Displays welcome prompt message
	welcomeUser();

	// Get info from user
	getInfo(fullName, firstName, studentID);
	do
	{
		// Clears screen
		system("cls");

		// Select Test Subject
		selSubject(questions, answers);

		// Clears screen
		system("cls");

		// Generate Test - currently in selSubject function
		genTest(questions, answers, firstName, numQuestionsRequested, numAnswersCorrect);
		qAsked.push_back(numQuestionsRequested);
		qRight.push_back(numAnswersCorrect);
		i++;
		cout << "Would you like to be quizzed again? ";
		valYesNo(yesno);
	} while (yesno == 'Y');

	// Display Test Results - currently in selSubject function
	system("cls");
	displayResults(studentID, fullName, qAsked, qRight, i);
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
void getFile(vector<string> &vecNames, string description)
{
	string line;
	ifstream fin(description);
	vecNames.clear();
	if (fin)
	{
		while (getline(fin, line)) {
			vecNames.push_back(line);
		}
	}
	else
	{
		cout << "We are sorry, there is something wrong with the pathing for the Questions document.";
		cout << endl;
	}
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
	numAnswersCorrect = 0;
	int r = 0;
	const int NUM_QUESTIONS = 50;
	string ans;
	int *questionsArray = nullptr; // Dynamically allocated array for indexes of questions asked.
	questionsArray = dynArray(numQuestionsRequested);

	for (int i = 0; i < numQuestionsRequested; i++) {

		if (i != 0) { // Checks to make sure it's not the first element.
			do { // Loops until 'r' is a unique number to prevent repeated questions.
				r = rand() % MaxQs + 1;
				*(questionsArray + i) = r;
			} while (searchArr(questionsArray, i, r)); // Calls a (boolean returning) search module on r.
		}
		else { // If it's the first element no checks need to be done.
			r = (rand() % MaxQs + 1);
			*(questionsArray) = r;
		}

		cout << questions[r] << endl;
		cout << "True or False : ";
		cin >> ans;
		valInput(ans);
		if (ans == answers[r]) {
			cout << "\nCORRECT!\n";
			numAnswersCorrect++;
		}
		else {
			cout << "\nIncorrect!\n";
		}
	}
	delete[] questionsArray;
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
void displayResults(string studentID, string fullName, vector<int> qAsked, vector<int> qRight, int i)
{

	cout << endl;
	cout << "====================================================" << endl;
	cout << endl
		 << "                  Report " << i << endl << endl;
	cout << "====================================================" << endl;
	cout << "Id:   " << studentID << endl;
	cout << "Name: " << fullName << endl;
	for (int j = 0; j < i; j++)
	{
		cout << "Quiz: " << j + 1;
		cout << endl;
		cout << "Number of questions: " << qAsked[j] << endl;
		cout << "Number of answers correct: " << qRight[j] << endl;
		double grade = (qRight[j] * 1.0 / qAsked[j]) * 100;
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
		cout << "-----------------------------------------------------";
		cout << endl;
	}
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

void selSubject(vector<string> &questions, vector<string> &answers)
{
	int choice;

	cout << "\n        Subject Menu" << endl;
	cout << "------------------------------" << endl;
	cout << "1. Arrays" << endl;
	cout << "2. Pointers" << endl;
	cout << "3. Vectors" << endl;
	cout << "4. Dynamic Arrays" << endl;
	cout << "------------------------------" << endl;
	do
	{
		cout << "The valid choices are 1, 2, 3, and 4. Please choose: ";
		cin >> choice;
		checkCin();
	} while (choice > 4 || choice < 1); //Validate entry for number within 1-5 range
	if (choice == 1)
	{
		getFile(questions, "questionsArrays.txt");
		getFile(answers, "answersArrays.txt");
	}
	else if (choice == 2)
	{
		getFile(questions, "questionsPointers.txt");
		getFile(answers, "answersPointers.txt");

	}
	else if (choice == 3)
	{
		getFile(questions, "questionsVectors.txt");
		getFile(answers, "answersVectors.txt");
	}
	else if (choice == 4)
	{
		getFile(questions, "questionsArrays.txt");
		getFile(answers, "answersArrays.txt");
	}


}

//*************************************************************
// module to generate a test and send back the number of Q's
// asked and correct
//*************************************************************
void genTest(vector<string> questions, vector<string> answers, string firstName, int &numQuestionsRequested, int &numAnswersCorrect)
{
	testMessage(firstName);
	inputValue("You must enter a number from 1 through 50: ", numQuestionsRequested);
	system("cls");
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
//*************************************************************
// Definition of function getYesNo.                           *
// This function validates for a Y for Yes or N for No answer *
//*************************************************************
void valYesNo(char &answer)
{

	do {
		cin >> answer;
		cout << endl;
		//convert lower case to upper case
		if (answer == 'y') {
			answer = 'Y';
		}
		else if (answer == 'n') {
			answer = 'N';
		}
		if (answer != 'Y' && answer != 'N') {
			cout << "Please enter Y for yes or N for N: ";
		}
	} while (answer != 'Y' && answer != 'N');
}
//*************************************************************
// Function searches a given array (ptr)                      *
// and tests if a provided value lies with in search scope    *
//*************************************************************
bool searchArr(int *ptr, int len, int val){
	for(int i = 0; i < len; i++){
		if(*(ptr + i) == val)
			return true;
	}
	return false;
}