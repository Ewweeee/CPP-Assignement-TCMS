//preprocessor directive used to prevent header files from being included multiple times
#pragma once

#include <iostream>
using namespace std;

//Tuition Center Structure - indicates various locations
struct TuitionCenter {
	int centerCode;
	string centerName;
	string branch;
};

//User access structure - implemented for user login
struct Access {
	int userCode;
	string userType;
	string credentials;
	TuitionCenter center;
	string branch = center.branch;
	//Admin & HR branch = HeadQuarter
};

//Tutor Structure - to store tutor's information (Linked List)
struct Tutor {
	//Example
	// Tutor ID : Branch Char + Auto Generated
	// B001 Abu bUKIT jALIL
	// C001 Aba CH
	// C002 Bud CH
	// K003 CAT KL
	// P004 ACA PU

	int tutorID;
	string firstName;
	string lastName;
	string dateJoined;
	string dateTerminated;
	double hourlyRate;
	string phoneNumber;
	string address;
	TuitionCenter center;
	string branch = center.branch;
	int subjectCode;
	string subjectName;
	int rating;
	struct Tutor* nextAddress;
	struct Tutor* previousAddress;

	//Tutor's Default Constructor
	Tutor()
	{
		cout << "Tutor" << endl;
	}

	//Tutor's User-defined Constructor
	Tutor(int tutorID, string firstName, string lastName, string dateJoined, string	dateTerminated, double hourlyRate, string phoneNumber,
		string address, struct TuitionCenter center, int subjectCode, string subjectName, int rating)
	{
		this->tutorID = tutorID;
		this->firstName = firstName;
		this->lastName = lastName;
		this->dateJoined = dateJoined;
		this->dateTerminated = dateTerminated;
		this->hourlyRate = hourlyRate;
		this->phoneNumber = phoneNumber;
		this->center = center;
		this->subjectCode = subjectCode;
		this->subjectName = subjectName;
		this->rating = rating;
	}

	//Tutor's Destructor
	~Tutor()
	{
		cout << "Tutor " << tutorID << "is added successfully." << endl;
	}

	//Tutor's Methods
	string getphoneNumber() {
		return phoneNumber;
	}

	void setphoneNumber(string phoneNumber) {
		this->phoneNumber = phoneNumber;
	}

	void displayTutor() {
		cout << "New tutor is added successfully." << endl;
		cout << "Tutor ID :  " << tutorID << endl;
		cout << "Tutor Name : " << tutorID << endl;
	}
};