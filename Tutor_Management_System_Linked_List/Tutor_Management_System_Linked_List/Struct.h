//preprocessor directive used to prevent header files from being included multiple times
#pragma once

#include <iostream>
using namespace std;

//global variable
int sizeofLinkedListforTutor = 0;
int sizeofLinkedListforAccess = 0;

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
	string branch;
	string credentials;
	struct Access* nextAddress1;
	struct Access* previousAddress1;

	//Tutor's Default Constructor
	Access()
	{
		//cout << "Tutor" << endl;
	}

	//Tutor's User-defined Constructor
	Access(string userCode, string userType, string branch, string credentials)
	{
		userCode = userCode;
		userType = userType;
		branch = branch;
		credentials = credentials;
	}
	string getUserCode() {
		return userCode;
	}

	void setUserCode(string userCode) {
		userCode = userCode;
	}

	string getUserType() {
		return userType;
	}

	void setUserType(string userType) {
		userType = userType;
	}

	string getBranch() {
		return branch;
	}

	void setBranch(string branch) {
		branch = branch;
	}

	string getCredentials() {
		return credentials;
	}

	void setCredentials(string credentials) {
		credentials = credentials;
	}

	void PrintBookDetials() {
		cout << "Book Name = " << userCode << endl;
		cout << "Book Author = " << userType << endl;
		cout << "Book Subject = " << branch << endl;
		cout << "Book Page = " << credentials << endl;
	}
}*head1, * tail1;

//Tutor Structure - to store tutor's information (Linked List)
struct Tutor {
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
	}

	//Tutor's User-defined Constructor
	Tutor(string tutorID, string firstName, string lastName, string dateJoined, string	dateTerminated, double hourlyRate, string phoneNumber,
		string address, string credential, string branch, string subjectCode, string subjectName, int rating)
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
		cout << "Tutor " << tutorID << " is removed successfully." << endl;
	}

	//Tutor's Methods
	string getTutorID() {
		return tutorID;
	}

	void setTutorID(int tutorID) {
		this->tutorID = tutorID;
	}

	string getFirstName() {
		return firstName;
	}

	void setFirstName(string firstName) {
		this->firstName = firstName;
	}

	string getLastName() {
		return lastName;
	}

	void setLastName(string firstName) {
		this->lastName = lastName;
	}

	string getDateJoined() {
		return dateJoined;
	}

	string getDateTerminated() {
		return dateTerminated;
	}

	void setDateTerminated(string dateTerminated) {
		this->dateTerminated = dateTerminated;
	}

	double getHourlyRate() {
		return hourlyRate;
	}

	void setHourlyRate(double hourlyRate) {
		this->hourlyRate = hourlyRate;
	}

	string getphoneNumber() {
		return phoneNumber;
	}

	void setphoneNumber(string phoneNumber) {
		this->phoneNumber = phoneNumber;
	}

	string getAddress() {
		return address;
	}

	void setAddress() {
		this->address = address;
	}

	string getCredential() {
		return credential;
	}

	void setCredential(string credential) {
		this->credential = credential;
	}

	string getBranch() {
		return branch;
	}

	void setBranch(string branch) {
		this->branch = branch;
	}

	string getSubjectCode() {
		return subjectCode;
	}

	void setSubjectCode(int subjectCode) {
		this->subjectCode = subjectCode;
	}

	string getSubjectName() {
		return subjectName;
	}

	void setSubjectName(string subjectName) {
		this->subjectName = subjectName;
	}

	int getRating() {
		return rating;
	}

	void setRating(int rating) {
		this->rating = rating;
	}
}*head, * tail;

void displayAllRecords(int lastIndex, string branch) {
	cout << "\t| TUTOR DETAILS |" << endl << endl;

	int i = 0;
	Tutor* current = head;

	while (current != NULL)
	{
		if (current->branch == branch)
		{
			cout << current->tutorID << " - " << current->firstName << " - " << current->lastName << " - " << current->dateJoined << " - "
				<< current->phoneNumber << " - " << current->address << " - " << current->branch << " - " << current->subjectCode << " - "
				<< current->subjectName << " - " << current->rating << endl << endl;
			current = current->nextAddress;
		}
		else
		{
			current = current->nextAddress;
		}
	}

	/*return;*/

//Returning Back To Main Menu (PRESS ENTER)
	cout << setw(10) << "......PRESS ENTER......" << endl;
	cout << "	"; cin.get();
	if (cin.get() == '\n') {
		cout << "......Loading Menu ......" << endl;
	}
}