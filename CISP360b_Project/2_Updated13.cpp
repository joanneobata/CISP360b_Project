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
void inputValue(string, char &);
void getInfo(string &fullName, string &studentId);
void valYesNo(char &);
void AskQs(vector<string> Questions, vector<string> Answers, int &Qasked, int &aRight);

string concateName(string first, string last);
vector<string> getQs();
vector<string> getAs();

int main()
{
	vector<string> Questions(getQs());
	vector<string> Answers(getAs());
	string studentID,
		fullName;
	int Qasked, // number of questions Asked
		aRight; // number of questions right
	char yesno;   //Select Y for Yes or N for No
	
	for (int i = 0; i < 50; i++)
		cout << Questions[i] << endl;
	cout << endl;

	welcomeUser(); // displays welcome prompt message
			
	getInfo(fullName, studentID); // gets info from user 
	
	//AskQs(Questions, Answers, Qasked, aRight);
	
	//valYesNo(yesno);

	//inputValue("Would you like to view another report?", yesno);
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
		while (getline(fin, line))
			questions.push_back(line);
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
void inputValue(string description, char &value)
{
	cout << description << endl;
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
/*void AskQs(vector<string> Questions, vector<string> Answers, int &Qasked, int &aRight)
{
	const int NUM_QUESTIONS = 50;
	const int NUM_ASKED = 10;
	string inp;
	int count = 0;
	int r;
	int remaining = NUM_QUESTIONS;
	double score = 0;

	cout << "\nEnter 'True' or 'False'. Press enter for next question. \n\n";
	while (count != NUM_ASKED) {
		srand(time_t(0));
		//srand((unsigned int)time_t(NULL));
		cin.ignore(10000, '\n');              // Ignore the newline character in the buffer to prevent an infinite loop.

											  // Random numbers divided into 'remaining' buckets, instead of using rand() % remaining.
											  // Adding 'count' pushes the random number past the range of already-used questions and answers
		r = count + (int)(remaining * rand() / (RAND_MAX + 1.0));
		//r = rand() % 50;         //Create random number 1 max 50

		// Ask a question...
		cout << questions[r] << endl;
		// Get an answer!
		getline(cin, inp);

		if (inp == answers[r]) {
			cout << "Correct!\n";
			score += 1;
		}
		else {
			cout << "Incorrect.\n";
		}

		questions[r].swap(questions[count]);
		answers[r].swap(answers[count]);
		count += 1;
		remaining -= 1;
	}
	double correct = score / NUM_ASKED;
	cout << "\nYour score is " << right << fixed << setprecision(0) << correct * 100 << "%.\n\n";
}
*/