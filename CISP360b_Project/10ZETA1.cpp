//CISP360
//T/TH 1:30-2:50pm
//Spring 2017
//Team 13 Project: Dynamic Study Guide and Random Question Generator for C++
//Write a program for students to study C++.

//team13.cpp
//

//
#include <iostream>  //cout, cin
#include <cstdlib>   //srand, rand
#include <string>    //string
#include <fstream>   //ifstream
#include <vector>    //vector
#include <iomanip>   //setw, setprecision
#include <conio.h>  // input/ output (_getch(), _kbhit())
#include <cmath>    // abs()

using namespace std;

// Global Variable
const int MAXQS = 25;
const int MAPHEIGHT = 20;
const int MAPWIDTH = 80;
const char BOR = 176;
const char HL = 178;
const int NUMSTATES = 3;
const int MAX_CHARS = 64;

//Prototypes
void welcomeUser(string &fullName, string &first, string &id);
void inputValue(string, int &);
int getInfo(string &, string &, string &);
void selSubject(vector<string> &, vector<string> &);
void genTest(vector<string>, vector<string>, string, int &, int &);
int testMessage(string);
void valInput(string &);
void checkCin();
void askQuestions(vector<string>, vector<string>, int, int &);
void displayResults(string, string, vector<int>, vector<int>, int);
void getFile(vector<string> &, string);
void valYesNo(char &);
void draw(int);
void drawQs(vector<string>, int);
int formatQs(vector<string>, int);
void ifsDraw(int&, int&, int);
int setUp();
void stateShift(int&, int);
void setupSubject(int &, int &, int);
int newField(string, int = 0);
string concatName(string, string);
int *dynArray(int);
bool searchArr(int *, int, int);
void bField(string);

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
	welcomeUser(fullName, firstName, studentID);

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
void welcomeUser(string &fullName, string &first, string &id)
{
	for (int i = 0; i < MAPHEIGHT; i++) {
		for (int j = 0; j < MAPWIDTH; j++) {
			if (i == 0  || i == MAPHEIGHT - 1) {
				cout << BOR;
			}
			else if(i == 2 && j == 0){
				newField("Welcome to the CISP 360 Study Guide",0);
				j += MAPWIDTH;
			}
			else if(i == 4)
				cout << BOR;
			else if(i == 6 && j == 0){
				i += getInfo(fullName, first, id);
				j += MAPWIDTH;
			}
			else if (j == 0 || j == MAPWIDTH - 1) {
				cout << BOR;
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}
	system("pause");
}

// *************************************************************
// Function used to display a message to user 
// *************************************************************
int testMessage(string firstName)
{
	string greeting = "Welcome, " + firstName + " !";

	int numQuestions = 0;

	for (int i = 0; i < MAPHEIGHT; i++) {
		for (int j = 0; j < MAPWIDTH; j++) {
			if (i == 0 || i == MAPHEIGHT - 1) {
				cout << BOR;
			}
			else if (i == 2 && j == 0) {
				newField(greeting, 0);
				j += MAPWIDTH;
			}
			else if (i == 4)
				cout << BOR;
			else if (i == 6 && j == 0) {

				i += newField("You'll be taking a test on your selected subject.", 14);
				cout << endl;
				i += newField(" ");
				cout << endl;

				i += newField("Please answer the questions with a True or False.", 14);
				cout << endl;
				i += newField(" ");
				cout << endl;

				i += newField("How many questions did you want to take ?", 14);
				cout << endl;

				inputValue("You must enter a number from 1 through 25! ", numQuestions);
				i += newField(" ");
				j += MAPWIDTH;

			}
			else if (j == 0 || j == MAPWIDTH - 1) {
				cout << BOR;
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}
	system("pause");
	return numQuestions;
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
		cout << "\nWe are sorry, there is something wrong with the pathing for the Questions document.";
		cout << endl;
		exit(EXIT_FAILURE);
	}
}
//*************************************************************
//  This function displays a query and accepts input value    
//*************************************************************
void inputValue(string description, int &value)
{

	cout << setw(MAPWIDTH / 3) << "   # ";
	cin >> value;
	while (cin.fail() || value > MAXQS || value <1) { // If cin fails to receive a value matching the declared data type.
		cin.clear();               // Clear the error flag within cin.
		cin.ignore(10000, '\n');   // Ignore the newline character in the buffer to prevent an infinite loop.
		newField(description, 14);
		cout << endl;

		cout << setw(MAPWIDTH / 3) << "   # ";
		cin >> value;
	}
}
//*************************************************************
// This function displays query and accepts input value for   *
// student ID, first name and last name                                                 *
//*************************************************************
int getInfo(string &fullName, string &first, string &id)
{
	int acc = 0;
	string last;	   // last name

	acc += newField("Please Enter your student ID", 0);
	cout << endl;
	newField(" ");
	cout << endl;

	cout << setw(MAPWIDTH /3) << "   # ";
	cin >> id;
	cout << endl;
	acc += newField(" ");
	cout << endl;

	acc += newField("Please Enter your first name", 0);
	cout << endl;
	newField(" ");
	cout << endl;

	cout << setw(MAPWIDTH / 3) << "   : ";
	cin >> first;
	cout << endl;
	acc += newField(" ");
	cout << endl;

	acc += newField("Please Enter your second name", 0);
	cout << endl;
	newField(" ");
	cout << endl;

	cout << setw(MAPWIDTH / 3) << "   : ";
	cin >> last;
	cout << endl;
	acc += newField(" ");

	fullName = concatName(first, last);
	return 2 * acc;
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
	string tmp;
	int *questionsArray = nullptr; // Dynamically allocated array for indexes of questions asked.
	questionsArray = dynArray(numQuestionsRequested);

	for (int i = 0; i < numQuestionsRequested; i++) {

		if (i != 0) { // Checks to make sure it's not the first element.
			do { // Loops until 'r' is a unique number to prevent repeated questions.
				r = ((rand() % MAXQS));
				*(questionsArray + i) = r;
			} while (searchArr(questionsArray, i, r)); // Calls a (boolean returning) search module on r.
		}
		else { // If it's the first element no checks need to be done.
			r = (rand() % MAXQS);
			*(questionsArray) = r;
		}
		//
		drawQs(questions, r);

		//
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
		system("pause");
		system("cls");
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
	int choice = setUp();
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
	numQuestionsRequested = testMessage(firstName);
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
bool searchArr(int *ptr, int len, int val) {
	for (int i = 0; i < len; i++) {
		if (*(ptr + i) == val)
			return true;
	}
	return false;
}

///
//
//

void draw(int state = 0) {
	for (int i = 0; i < MAPHEIGHT; i++) {
		for (int j = 0; j < MAPWIDTH; j++) {
			ifsDraw(i, j, state);
		}
		cout << endl;
	}
}

void drawQs(vector<string> questions, int r) {
	for (int i = 0; i < MAPHEIGHT; i++) {
		for (int j = 0; j < MAPWIDTH; j++) {
			if (i == 0 || i == MAPHEIGHT - 1) {
				cout << BOR;
			}

			else if (i == 2 && j == 0){
				newField("Questions");
				j += MAPWIDTH;
			}
			else if (i == 4) {
				cout << BOR;
			}
			else if (i == MAPHEIGHT / 2 && j == 0) {
				i += formatQs(questions, r);
				j += MAPWIDTH;
			}
			else if (j == 0 || j == MAPWIDTH - 1) {
				cout << BOR;
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}
}

int formatQs(vector<string> questions, int r){
	int acc = 0;
	string tmp;
	for (int i = 0; i < questions[r].length(); i++) {
		tmp += questions[r].at(i);
		if (i != 0 && i % MAX_CHARS == 0) {
			bField(tmp);
			++acc;
			tmp.clear();
			tmp += "-";
		}
		else if (i == questions[r].length() - 1){
			++acc;
			bField(tmp);
		}
	}
	return acc;
}

void bField(string msg){
	int padding = 5;
	cout << fixed << left;
	cout << setw(padding) << BOR << setw(MAPWIDTH - (padding + 1)) << msg << BOR;
	cout << endl;
}

int newField(string msg, int k){
	if(k == 0){
		int padding = MAPWIDTH / 10;
		cout << fixed << left;
		cout << setw((3 * padding)) << BOR;			// starts a new sentence
		cout << setw(MAPWIDTH - (4 * padding))
			<< msg;
		cout << setw(padding) << right << BOR;         // ends a new sentence
		return 1;
	}
	else if (k == 1) {
		int padding = MAPWIDTH / 10;
		int len = msg.length();
		cout << fixed << left;
		
		for(int a = 0; a < (3 * padding - 1); a++){
			cout << HL;
		}
		cout << setw(len + 8)
			<< msg;
		for (int a = 0; a < (MAPWIDTH - (len + 3 * padding + 8)); a++) {
			cout << HL;
		}
		cout << BOR;         // ends a new sentence
		return 1;
	}
	else if (k >= 2) {
		int padding = MAPWIDTH / k;
		cout << fixed << left;
		cout << setw((3 * padding)) << BOR;			// starts a new sentence
		cout << setw(MAPWIDTH - (4 * padding))
			<< msg;
		cout << setw(padding) << right << BOR;         // ends a new sentence
		return 1;
	}
}

void setupSubject(int &i, int &j, int s){
	int ar = 0, po = 0, ve = 0, dy = 0;
	if(s == 0)
		ar = 1;
	else if(s == 1)
		po = 1;
	else if(s == 2)
		ve = 1;
	else if(s == 3)
		dy = 1;

	i += newField(" ");
	cout << endl;

	newField(" ");
	cout << endl;
	i += newField("         Arrays", ar);
	cout << endl;
	i += newField(" ");
	cout << endl;

	i += newField("         Pointers", po);
	cout << endl;
	i += newField(" ");
	cout << endl;

	i += newField("         Vectors", ve);
	cout << endl;
	i += newField(" ");
	cout << endl;

	i += newField("         Dynamic Arrays", dy);
	cout << endl;
	i += newField(" ");
	j += MAPWIDTH;
}

void ifsDraw(int &i, int &j, int state) {
	if (i == 0 || i == MAPHEIGHT - 1) {
		cout << BOR;
	}
	else if (i == 2 && j == 0) {
		newField("  SUBJECT MENU", 8);
		cout << endl;
		newField(" ");
		cout << endl;
		newField("  Use your Up, Down arrow keys to navigate the menu.", 15);
		cout << endl;
		newField("Press enter to select your choice.", 10);
		cout << endl;
		newField(" ");
		j += MAPWIDTH;
	}
	else if (i == 3)
		cout << BOR;
	else if (i == 4 && j == 0) {
		setupSubject(i, j, state);
	}
	else if (i == 9)
		cout << BOR;
	else if (j == 0 || j == MAPWIDTH - 1) {
		cout << BOR;
	}
	else {
		cout << " ";
	}

}

int setUp() {
	int states = 0;
	char prs, UP = 72, DOWN = 80, RIGHT = 77, LEFT = 75;

	draw(); // draw menu
	while (true) {
		if (_kbhit()) {
			prs = _getch();	
			if (prs == '\r') {
				system("cls");
				return (states + 1);
			}
			prs = _getch();
			if (prs == UP) {
				system("cls");
				stateShift(states, 2);
				cout << states;
				draw(states);
			}
			if (prs == DOWN) {
				system("cls");
				stateShift(states, 1);
				cout << states;
				draw(states);
			}
		}
	}

}

void stateShift(int &state, int mv) {
	if (mv == 1) {
		if (state >= 0 && state <= 2) {
			++state;
		}
		else {
			state = 0;
		}
	}
	else if (mv == 2) {
		if (state >= 1 && state <= 3) {
			--state;
		}
		else {
			state = 3;
		}
	}
}