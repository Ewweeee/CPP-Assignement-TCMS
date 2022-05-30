//preprocessor directive used to prevent header files from being included multiple times
#pragma once

#include <iostream>
using namespace std;

//global variable
int sizeofLinkedList = 0;

//Tuition Center Structure - indicates various locations
struct TuitionCenter {
	int centerCode;
	string centerName;
	string branch;
};

//User access structure - implemented for user login
struct Access {
	//Access can be store as static variables, store in heap (+ pointer)
	//Choice 1 / 2 : Come here
	//Else go to tutor struct check ID and credentials
	//Change this
	string userCode;
	string userType;
	string credentials;
};


//Tutor Structure - to store tutor's information (Linked List)
struct Tutor {
	//Example
	// Tutor ID : Branch Char + Auto Generated
	// B001 Abu Bukit Jalil
	// C001 Aba CH
	// C002 Bud CH
	// K003 CAT KL
	// P004 ACA PU
	string tutorID;
	string firstName;
	string lastName;
	string dateJoined;
	string dateTerminated;
	double hourlyRate;
	string phoneNumber;
	string address;
	string credential;
	TuitionCenter center;
	string branch = center.branch;
	string subjectCode;
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
	Tutor(string tutorID, string firstName, string lastName, string dateJoined, string	dateTerminated, double hourlyRate, string phoneNumber, string address, string credential, string branch, string subjectCode, string subjectName, int rating)
	{
		this->tutorID = tutorID;//get set
		this->firstName = firstName;//get set
		this->lastName = lastName; //get set
		this->dateJoined = dateJoined; //get
		this->dateTerminated = dateTerminated; //get set
		this->hourlyRate = hourlyRate;//get set
		this->phoneNumber = phoneNumber;//get set
		this->address = address;//get set
		this->credential = credential;//get set
		this->branch = branch; //get set
		this->subjectCode = subjectCode;//get set
		this->subjectName = subjectName; //get set
		this->rating = rating;//get
	}

	//Tutor's Destructor
	~Tutor()
	{
		cout << "Tutor " << tutorID << "is added successfully." << endl;
	}

	//Tutor's Methods
	string getTutorID() {
		return tutorID;
	}

	void setTutorID(string tutorID) {
		tutorID = tutorID;
	}

	string getFirstName() {
		return firstName;
	}

	void setFirstName(string firstName) {
		firstName = firstName;
	}

	string getLastName() {
		return lastName;
	}

	void setLastName(string firstName) {
		lastName = lastName;
	}

	string getDateJoined() {
		return dateJoined;
	}

	string getDateTerminated() {
		return dateTerminated;
	}

	void setDateTerminated(string dateTerminated) {
		dateTerminated = dateTerminated;
	}

	double getHourlyRate() {
		return hourlyRate;
	}

	void setHourlyRate(double hourlyRate) {
		hourlyRate = hourlyRate;
	}

	string getphoneNumber() {
		return phoneNumber;
	}

	void setphoneNumber(string phoneNumber) {
		phoneNumber = phoneNumber;
	}

	string getAddress() {
		return address;
	}

	void setAddress() {
		address = address;
	}

	string getCredential() {
		return credential;
	}

	void setCredential(string credential) {
		credential = credential;
	}

	string getBranch() {
		return branch;
	}

	void setBranch(string branch) {
		branch = branch;
	}

	string getSubjectCode() {
		return subjectCode;
	}

	void setSubjectCode(string subjectCode) {
		subjectCode = subjectCode;
	}

	string getSubjectName() {
		return subjectName;
	}

	void setSubjectName(string subjectName) {
		subjectName = subjectName;
	}

	int getRating() {
		return rating;
	}

	void setRating(int rating) {
		rating = rating;
	}

	void addTutor() {
		cout << "New tutor is added successfully." << endl;
		cout << "Tutor ID :  " << tutorID << endl;
		cout << "Tutor Name : " << tutorID << endl;
	}
}*head, *tail;