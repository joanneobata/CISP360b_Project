//CISP360
//T/TH 1:30-2:50pm
//Spring 2017
//Team 13 Project: Dynamic Study Guide and Random Question Generator for C++
//Write a program for students to study C++ and for instructors to see how 
//well the students are learning C++.

//team13.cpp

#include <iostream>  //cout, cin
#include <cstdlib>   //srand, rand
#include <string>    //string
#include <fstream>   //ifstream
#include <vector>    //vector
#include <algorithm> //swap 
#include <iomanip>   //setw, setprecision

using namespace std;

//Prototypes
void welcomeUser();
void inputValue(string, int &);
void getInfo(string &fullName, string &studentId);
void valYesNo(char &);
void AskQs(vector<string> Questions, vector<string> Answers, int &Qasked, int &aRight);
void displayResults(string studentID, string fullName, int Qasked, int aRight);

string concateName(string first, string last);
vector<string> getQs();
vector<string> getAs();

int *Arr(int);

int main()
{
	srand(time(0));
	string studentID,
		   fullName;
	int Qasked = 0, // number of questions Asked
		aRight = 0; // number of questions right
	char yesno;   //Select Y for Yes or N for No

	welcomeUser(); // displays welcome prompt message
	getInfo(fullName, studentID); // gets info from user 
	do
	{
		vector<string> Questions(getQs()); // Decleration and Initialization of Vector Questions
		vector<string> Answers(getAs()); // Decleration and Initialization of Vector Questions

		inputValue("You'll be taking a test, please answer with true or false.\nHow many questions do you want? : ", Qasked);

		AskQs(Questions, Answers, Qasked, aRight);
		cout << "Would you like to be quizzed again? ";
		valYesNo(yesno);
	} while (yesno == 'Y');
	displayResults(studentID, fullName, Qasked, aRight);
	system("pause");
	return 0;
}
// *************************************************************
// this function is used to open and read the Questions document
// and return it
// *************************************************************
vector<string> getQs()
{
	vector<string> questions;
	string line;
	ifstream fin("questions.txt");
	if (fin)
	{
		while (getline(fin, line)){
			questions.push_back(line);
		}
	}
	else
	{
		cout << "We are sorry, there is something wrong with the pathing for the Questions document.";
		cout << endl;
	}
	return questions;
}
// *************************************************************
// This function is used to open and read the Answers document
// and return it 
// *************************************************************
vector<string> getAs()
{
	vector<string> answers;
	string line;
	ifstream fin("answers.txt");
	if (fin)
	{
		while (getline(fin, line))
			answers.push_back(line);
	}
	else
	{
		cout << "We are sorry, there is something wrong with the pathing for the Answers documents.";
		cout << endl;
	}

	return answers;
}
// *************************************************************
// This module is used to display a greeting when starting the 
// program.
// *************************************************************
void welcomeUser()
{
	cout << "**************************************************" << endl;
	cout << setw(39) << "Welcome to the Exam study guide" << endl;
	cout << "**************************************************" << endl;
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
// Definition of function inputValue.                         *
//  This function displays query and accepts input value      *
//*************************************************************
void inputValue(string description, int &value)
{
	cout << description;
	cin >> value;
}

//*************************************************************
// Definition of function inputStudentID.                     *
// This function displays query and accepts input value for   *
// student ID                                                 *
//*************************************************************
void getInfo(string &fullName, string &id)
{

	string first,	   // first name 
			last;	   // last name

	cout << "Please Enter your student ID: ";
	cin >> id;
	cout << "Please Enter your first name: ";
	cin >> first;
	cout << "Please Enter your second name: ";
	cin >> last;

	fullName = concateName(first, last);

}
//*************************************************************
// Concatentate the first and last name in to one string var
// function
//*************************************************************
string concateName(string first, string last)
{
	string fullName;
	fullName = last + ", " + first;
	return fullName;
}
// ************************************************************
// module will bring in questions and answer vectors,
//
// ************************************************************
void AskQs(vector<string> Questions, vector<string> Answers, int &Qasked, int &aRight)
{
	int R = 0;
	const int NUM_QUESTIONS = 50;
	string Ans;
	int *Qarray = nullptr; // Dynamically allocated array for indexes of questions asked.
	int *Aarray = nullptr; // Dynamically allocated array for indexes of C/IC answers. ( C = 1 and IC = 0)
	Qarray = Arr(Qasked);
	Aarray = Arr(Qasked);
	 
	for(int i = 0; i < Qasked; i++){
		
		if(i != 0){ // Checks to make sure it's not the first element.
			do{ // Loops until R is a unique number to prevent repeated questions.
				R = rand() % 50 + 1;
				*(Qarray + i) = R;
			} while((*(Qarray + (i - 1))) == R);
		}
		else{ // If it's the first element no checks need to be done.
			R = (rand() % 50 + 1);
			*(Qarray) = R;
		}

		cout << Questions[R] << endl;
		cout << "True or False : ";
		cin >> Ans;

		if(Ans == Answers[R]){
			cout << "\nCORRECT!\n";
			aRight++;
			*(Aarray + i) = 1;
		}
		else{
			cout << "\nIncorrect!\n";
		}
	}
	delete[] Qarray;
	delete[] Aarray;
}

//*********************************************************************
//	This function dynamically allocates
// an integer array of size len with all elements initialized at zero.
//*********************************************************************
int *Arr(int len){
	int *vault = nullptr;
	vault = new int[len];

	for(int i = 0; i < len; i++){
		*(vault + i) = 0;
	}

	return vault;
}
//********************************************************************
// This function receives the information from the other modules 
// and displays it. 
//********************************************************************
void displayResults(string studentID, string fullName, int Qasked, int aRight)
{
	double grade = (aRight * 1.0 / Qasked) * 100;
	cout << endl << endl;
	cout << "====================================================" << endl;
	cout << "Id:   " << studentID << endl;
	cout << "Name: " << fullName << endl;
	cout << "Number of Questions Asked was " << Qasked << endl;
	cout << "Number of answers correct was " << aRight << endl;
	cout << "Your scored a " << grade << "%" << endl;

	if (grade > 90)
	{
		cout << "Congrats you will do well on the test! Keep it up";
	}
	else if (grade > 80)
	{
		cout << "Good job but you need to study more for an A!";
	}
	else if (grade > 70)
	{
		cout << "You are on the right track and you should keep studying";
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
