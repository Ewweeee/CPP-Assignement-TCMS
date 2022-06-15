#include <iostream>
#include <string>
#include <iomanip>
#include "Menu.h"
#include "Struct.h"
#include "conio.h"
#include <ctime>
#include <time.h>

using namespace std;

//variables to be input
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
void checkLogin();
//Create new node for predefined tutor listings
Tutor* CreateNewNode(string tutorID, string firstName, string lastName, string dateJoined, string	dateTerminated, double hourlyRate, string phoneNumber,
	string address, string credential, string branch, string subjectCode, string subjectName, int rating)
{
	Tutor* newnode = new Tutor;
	newnode->tutorID = tutorID;
	newnode->firstName = firstName;
	newnode->lastName = lastName;
	newnode->dateJoined = dateJoined;
	newnode->dateTerminated = dateTerminated;
	newnode->hourlyRate = hourlyRate;
	newnode->phoneNumber = phoneNumber;
	newnode->address = address;
	newnode->credential = credential;
	newnode->branch = branch;
	newnode->subjectCode = subjectCode;
	newnode->subjectName = subjectName;
	newnode->rating = rating;
	newnode->previousAddress = NULL;
	newnode->nextAddress = NULL;
	return newnode;
}

Access* CreateNewNode(string userCode, string userType, string branch, string credentials)
{
	Access* newnode = new Access;
	newnode->userCode = userCode;
	newnode->userType = userType;
	newnode->branch = branch;
	newnode->credentials = credentials;
	newnode->previousAddress1 = NULL;
	newnode->nextAddress1 = NULL;
	return newnode;
}

// Function that accepts the password
string takePasswdFromUser(char sp = '*')
{
	int IN_BACK = 8;
	int IN_RET = 13;
	// Stores the password
	string passwd = "";
	char ch_ipt;

	// Until condition is true
	while (true) {
		ch_ipt = _getch();

		// if the ch_ipt
		if (ch_ipt == IN_RET) {
			cout << endl;
			return passwd;
		}
		else if (ch_ipt == IN_BACK && passwd.length() != 0) {
			passwd.pop_back();

			//It will erase
			// previously printed character
			cout << "\b \b";

			continue;
		}

		// Without using this, program
		// will crash as \b can't be
		// print in beginning of line
		else if (ch_ipt == IN_BACK && passwd.length() == 0) {
			continue;
		}

		passwd.push_back(ch_ipt);
		cout << sp;
	}
}

//Auto generated Tutor ID based on the branch
string tutorIDGenerator(int listSize, string branch)
{
	string tutorID = "";
	string newTID;
	string prefix;
	Tutor* current = head;
	Tutor* maxTID = head;

	while (current != NULL)
	{
		maxTID = maxTID->nextAddress;
		int number = 0;

		//Find the max tutor ID
		for (int i = 0; i < ::sizeofLinkedListforTutor; i++)
		{
			if (current->branch == branch && maxTID->branch == branch) {
				if (current->getTutorID() > maxTID->getTutorID()) {
					maxTID = current;
				}
			}
		}

		tutorID = maxTID->getTutorID();
		number = stoi(tutorID.substr(1, 4)) + 1;

		newTID = to_string(number);

		if (branch == "Cheras")
		{
			if (number > 0 && number < 9)
			{
				prefix = "C000";
				newTID = prefix + newTID;
			}
			else
			{
				prefix = "C00";
				newTID = prefix + newTID;
			}
		}
		else if (branch == "Petaling Jaya")
		{
			if (number > 0 && number < 9)
			{
				prefix = "P000";
				newTID = prefix + newTID;
			}
			else
			{
				prefix = "P00";
				newTID = prefix + newTID;
			}
		}
		else if (branch == "Bukit Jalil")
		{
			if (number > 0 && number < 9)
			{
				prefix = "B000";
				newTID = prefix + newTID;
			}
			else
			{
				prefix = "B00";
				newTID = prefix + newTID;
			}
		}

		return newTID;
		current = current->nextAddress;
		//maxTID = maxTID->nextAddress;
	}
}

static void sortedInsertTutorID(Tutor** head_ref, Tutor* newNode)
{
	Tutor* current;

	// if list is empty
	if (*head_ref == NULL)
		*head_ref = newNode;

	// if the node is to be inserted at the beginning
	// of the doubly linked list
	else if (stoi((*head_ref)->tutorID.substr(1)) >= stoi(newNode->tutorID.substr(1)))
	{
		newNode->nextAddress = *head_ref;
		newNode->nextAddress->previousAddress = newNode;
		*head_ref = newNode;
	}
	else
	{
		current = *head_ref;

		while (current->nextAddress != NULL &&
			stoi(current->nextAddress->tutorID.substr(1)) < stoi(newNode->tutorID.substr(1)))	//comparing data (1st lesser than 2nd)
			current = current->nextAddress;		//keep going forward

		//Make the appropriate links /
		newNode->nextAddress = current->nextAddress;	//while loop was finding the right current address to replace the new node

		// if the new node is not inserted
		// at the end of the list
		if (current->nextAddress != NULL)
			newNode->nextAddress->previousAddress = newNode;

		current->nextAddress = newNode;
		newNode->previousAddress = current;
	}
}

void sortByTutorID(Tutor** head_ref)
{
	// Initialize 'sorted' - a sorted doubly linked list
	Tutor* sorted = NULL;

	// Traverse the given doubly linked list and
	// insert every node to 'sorted'
	Tutor* current = *head_ref;
	while (current != NULL) {
		// Store next for next iteration
		Tutor* next = current->nextAddress;

		// removing all the links so as to create 'current'
		// as a new node for insertion
		current->previousAddress = current->nextAddress = NULL;

		// insert current in 'sorted' doubly linked list
		sortedInsertTutorID(&sorted, current);

		// Update current
		current = next;
	}
	*head_ref = sorted;
}

static void sortedInsertHourlyRate(Tutor** head_ref, Tutor* newNode)
{
	Tutor* current;

	// if list is empty
	if (*head_ref == NULL)
		*head_ref = newNode;

	// if the node is to be inserted at the beginning
	// of the doubly linked list

	else if ((*head_ref)->hourlyRate >= newNode->hourlyRate)
	{
		newNode->nextAddress = *head_ref;
		newNode->nextAddress->previousAddress = newNode;
		*head_ref = newNode;
	}
	else
	{
		current = *head_ref;
		while (current->nextAddress != NULL &&
			current->nextAddress->hourlyRate < newNode->hourlyRate)	//comparing data (1st lesser than 2nd)
			current = current->nextAddress;		//keep going forward

		//Make the appropriate links
		newNode->nextAddress = current->nextAddress;	//while loop was finding the right current address to replace the new node

		// if the new node is not inserted
		// at the end of the list
		if (current->nextAddress != NULL)
			newNode->nextAddress->previousAddress = newNode;

		current->nextAddress = newNode;
		newNode->previousAddress = current;
	}
}

void sortByHourlyRate(Tutor** head_ref)
{
	Tutor* sorted = NULL;

	// Traverse the given doubly linked list and
	// insert every node to 'sorted'
	Tutor* current = *head_ref;
	while (current != NULL)
	{
		// Store next for next iteration
		Tutor* next = current->nextAddress;

		// removing all the links so as to create 'current'
		// as a new node for insertion
		current->previousAddress = current->nextAddress = NULL;

		// insert current in 'sorted' doubly linked list

		sortedInsertHourlyRate(&sorted, current);

		// Update current
		current = next;
	}
	*head_ref = sorted;
}

static void sortedInsertOverallPerformance(Tutor** head_ref, Tutor* newNode)
{
	Tutor* current;

	// if list is empty
	if (*head_ref == NULL)
		*head_ref = newNode;

	// if the node is to be inserted at the beginning
	// of the doubly linked list
	else if ((*head_ref)->rating >= newNode->rating)
	{
		newNode->nextAddress = *head_ref;
		newNode->nextAddress->previousAddress = newNode;
		*head_ref = newNode;
	}
	else
	{
		current = *head_ref;
		while (current->nextAddress != NULL &&
			current->nextAddress->rating < newNode->rating)	//comparing data (1st lesser than 2nd)
			current = current->nextAddress;		//keep going forward

		//Make the appropriate links

		newNode->nextAddress = current->nextAddress;	//while loop was finding the right current address to replace the new node

		// if the new node is not inserted
		// at the end of the list
		if (current->nextAddress != NULL)
			newNode->nextAddress->previousAddress = newNode;

		current->nextAddress = newNode;
		newNode->previousAddress = current;
	}
}

void sortByOverallPerformance(Tutor** head_ref)
{
	Tutor* sorted = NULL;

	// Traverse the given doubly linked list and
	// insert every node to 'sorted'
	Tutor* current = *head_ref;
	while (current != NULL)
	{
		// Store next for next iteration
		Tutor* next = current->nextAddress;

		// removing all the links so as to create 'current'
		// as a new node for insertion
		current->previousAddress = current->nextAddress = NULL;

		// insert current in 'sorted' doubly linked list

		sortedInsertOverallPerformance(&sorted, current);

		// Update current
		current = next;
	}
	*head_ref = sorted;
}

//Search Records By Tutor ID / Rating
void searchByTutorID(string keyword)
{
	Tutor* current = head;
	int count = 1;	//list number

	while (current != NULL)
	{
		if ((current->tutorID).find(keyword) != string::npos)	//string::npos---> substring
		{
			cout << "Record No." << count << " : " << current->tutorID << " - " << current->firstName << " - " << current->lastName << " - " << current->dateJoined << " - "
				<< current->dateTerminated << " - " << current->hourlyRate << " - " << current->phoneNumber << " - " << current->address << " - "
				<< current->credential << " - " << current->branch << " - " << current->subjectCode << " - " << current->subjectName << " - "
				<< current->rating << endl;
			count++;
		}

		current = current->nextAddress;
	}
	cout << endl << "Searching is done here! NOTE: If there are no results appear, this means that searched tutor is not found." << endl;
}

void searchByTutorID(string keyword, string branch)
{
	Tutor* current = head;
	int count = 1;	//list number

	while (current != NULL)
	{
		if ((current->tutorID).find(keyword) != string::npos && current->branch == branch)	//string::npos---> substring
		{
			cout << "Record No." << count << " : " << current->tutorID << " - " << current->firstName << " - " << current->lastName << " - " << current->dateJoined << " - "
				<< current->dateTerminated << " - " << current->hourlyRate << " - " << current->phoneNumber << " - " << current->address << " - "
				<< current->credential << " - " << current->branch << " - " << current->subjectCode << " - " << current->subjectName << " - "
				<< current->rating << endl;
			count++;
		}

		current = current->nextAddress;
	}
	cout << endl << "Searching is done here! NOTE: If there are no results appear, this means that searched tutor is not found." << endl;
}

void searchByRating(string keyrating)
{
	Tutor* current = head;
	int count = 1;	//list number

	while (current != NULL)
	{
		if (to_string(current->rating).find(keyrating) != string::npos)	//string::npos---> substring
		{
			cout << "Record No." << count << " : " << current->tutorID << " - " << current->firstName << " - " << current->lastName << " - " << current->dateJoined << " - "
				<< current->dateTerminated << " - " << current->hourlyRate << " - " << current->phoneNumber << " - " << current->address << " - "
				<< current->credential << " - " << current->branch << " - " << current->subjectCode << " - " << current->subjectName << " - "
				<< current->rating << endl;
			count++;
		}

		current = current->nextAddress;
	}
	cout << endl << "Searching is done here! NOTE: If there are no results appear, this means that searched tutor is not found." << endl;
}

void searchByRating(string keyrating, string branch)
{
	Tutor* current = head;
	int count = 1;	//list number

	while (current != NULL)
	{
		if (to_string(current->rating).find(keyrating) != string::npos && current->branch == branch)	//string::npos---> substring
		{
			cout << "Record No." << count << " : " << current->tutorID << " - " << current->firstName << " - " << current->lastName << " - " << current->dateJoined << " - "
				<< current->dateTerminated << " - " << current->hourlyRate << " - " << current->phoneNumber << " - " << current->address << " - "
				<< current->credential << " - " << current->branch << " - " << current->subjectCode << " - " << current->subjectName << " - "
				<< current->rating << endl;
			count++;
		}

		current = current->nextAddress;
	}
	cout << endl << "Searching is done here! NOTE: If there are no results appear, this means that searched tutor is not found." << endl;
}

//Display Tutor List
void displayList()
{
	Tutor* current = head;

	while (current != NULL)
	{
		cout << current->tutorID << " - " << current->firstName << " - " << current->lastName << " - " << current->dateJoined << " - "
			<< current->dateTerminated << " - " << current->hourlyRate << " - " << current->phoneNumber << " - " << current->address << " - "
			<< current->credential << " - " << current->branch << " - " << current->subjectCode << " - " << current->subjectName << " - "
			<< current->rating << endl << endl;

		current = current->nextAddress;
	}
	cout << endl << "List is ended here!" << endl << endl;
}

//Generate Summary Report / By Location Function
void generateReport() {
	int i = 0;
	int choice = 0;
	int totalTutors = 30;
	int totalTutorsInEachLoc = 10;
	//Summary Report Variables
	int emptySlot = 0;
	int occupiedSlot = 0;
	//Location Report Variables
	int BJOcc = 0;
	int CHOcc = 0;
	int PJOcc = 0;
	Tutor* current = head;
	displayReportTypeMenu();
	cin >> choice;
	cout << endl;
	switch (choice)
	{
	case 1:
		if (head != NULL) {
			/*While Current Node != NULL */
			while (current != NULL) {
				occupiedSlot++;
				current = current->nextAddress;
			}
			emptySlot = totalTutors - occupiedSlot; //calculate empty slot
			cout << endl;
			cout << "	TOTAL NUMBER OF TUTORS" << setw(11) << " = " << occupiedSlot << endl;
			cout << "	TOTAL NUMBER OF AVAILABLE SLOT = " << emptySlot << endl;
		}
		else {
			//If LinkedList is Empty, reset the emptySlot = 30
			emptySlot = 30;
			cout << endl;
			cout << "	TOTAL NUMBER OF TUTORS" << setw(11) << " = " << occupiedSlot << endl;
			cout << "	TOTAL NUMBER OF AVAILABLE SLOT = " << emptySlot << endl;
		}
		break;

	case 2:
		while (current != NULL) {
			/* check if tutor id in selected index is NULL */
			if (current->branch == "Bukit Jalil") {
				BJOcc++;
			}
			if (current->branch == "Cheras") {
				CHOcc++;
			}
			if (current->branch == "Petaling Jaya") {
				PJOcc++;
			}
			current = current->nextAddress;
		}
		cout << "Report By Location : " << endl << endl;
		// Location : Bukit Jalil
		cout << string(82, '=') << endl;
		cout << "|" << string(34, ' ') << "Bukit Jalil" << string(35, ' ') << "|" << endl;
		cout << string(82, '=') << endl << endl;
		cout << "    TOTAL NUMBER OF TUTORS" << setw(11) << " = " << BJOcc << endl;
		cout << "    TOTAL NUMBER OF AVAILABLE SLOT = " << totalTutorsInEachLoc - BJOcc << endl << endl;

		// Location : Cheras
		cout << string(82, '=') << endl;
		cout << "|" << string(37, ' ') << "Cheras" << string(37, ' ') << "|" << endl;
		cout << string(82, '=') << endl << endl;
		cout << "    TOTAL NUMBER OF TUTORS" << setw(11) << " = " << CHOcc << endl;
		cout << "    TOTAL NUMBER OF AVAILABLE SLOT = " << totalTutorsInEachLoc - CHOcc << endl << endl;

		// Location : Petaling Jaya
		cout << string(82, '=') << endl;
		cout << "|" << string(33, ' ') << "Petaling Jaya" << string(34, ' ') << "|" << endl;
		cout << string(82, '=') << endl << endl;
		cout << "    TOTAL NUMBER OF TUTORS" << setw(11) << " = " << PJOcc << endl;
		cout << "    TOTAL NUMBER OF AVAILABLE SLOT = " << totalTutorsInEachLoc - PJOcc << endl << endl;
		break;
	}
}

//Add New Tutor Record (inserting node into end of list)
void addTutor(Tutor* newnode)
{
	if (head == NULL)
	{
		head = tail = newnode;
	}
	else
	{
		newnode->previousAddress = tail;
		tail->nextAddress = newnode;
		tail = newnode;
	}
	::sizeofLinkedListforTutor++;
}

void addAccess(Access* newnode)
{
	if (head1 == NULL)
	{
		head1 = tail1 = newnode;
	}
	else
	{
		newnode->previousAddress1 = tail1;
		tail1->nextAddress1 = newnode;
		tail1 = newnode;
	}
	::sizeofLinkedListforAccess++;
}

// get date difference of 2 dates in DD/MM/YYYY format in days
int getDateDifference(string date1, string date2)
{
	// get date1 in DD/MM/YYYY format
	string day1 = date1.substr(0, 2);
	string month1 = date1.substr(3, 2);
	string year1 = date1.substr(6, 4);
	int day1Int = stoi(day1);
	int month1Int = stoi(month1);
	int year1Int = stoi(year1);

	// get date2 in DD/MM/YYYY format
	string day2 = date2.substr(0, 2);
	string month2 = date2.substr(3, 2);
	string year2 = date2.substr(6, 4);
	int day2Int = stoi(day2);
	int month2Int = stoi(month2);
	int year2Int = stoi(year2);

	// get date1 in seconds
	time_t t1 = time(0);
	struct tm now1;
	localtime_s(&now1, &t1);
	now1.tm_mday = day1Int;
	now1.tm_mon = month1Int - 1;
	now1.tm_year = year1Int - 1900;
	time_t t1Seconds = mktime(&now1);

	// get date2 in seconds
	time_t t2 = time(0);
	struct tm now2;
	localtime_s(&now2, &t2);
	now2.tm_mday = day2Int;
	now2.tm_mon = month2Int - 1;
	now2.tm_year = year2Int - 1900;
	time_t t2Seconds = mktime(&now2);

	// get difference in seconds
	int difference = t2Seconds - t1Seconds;

	// get difference in days
	int differenceDays = difference / 86400;
	return differenceDays;
}

//Modify Tutor Record (edit record based on tutorID and the part to be modified)
void modifyTutor(string EdittutorID, int option)
{
	Tutor* current = head;

	while (current != NULL)
	{
		if (current->tutorID == EdittutorID)
		{
			switch (option)
			{
			case 1:
				cout << "Enter New First Name: ";
				cin >> current->firstName;

				cout << "Enter New Last Name: ";
				cin >> current->lastName;

				while (cin.fail())
				{
					cin.clear();	//remove input operation
					cin.ignore(numeric_limits<streamsize>::max(), '\n');	//remove content
					cout << endl << "Please give a valid name! " << endl;
					cout << "Enter New First Name: ";
					cin >> current->firstName;
					cout << "Enter New Last Name: ";
					cin >> current->lastName;
				}

				break;

			case 2:
				cout << "Enter New Join Date: ";
				cin >> current->dateJoined;
				while (cin.fail() || current->dateJoined.size() != 10)
				{
					cin.clear();	//remove input operation
					cin.ignore(numeric_limits<streamsize>::max(), '\n');	//remove content
					cout << endl << "Please give a valid date! " << endl;
					cout << "Enter New Join Date: ";
					cin >> current->dateJoined;
				}
				break;

			case 3:
				cout << "Enter New Terminate Date: ";
				cin >> current->dateTerminated;
				while (cin.fail() || current->dateTerminated.size() != 10)
				{
					cin.clear();	//remove input operation
					cin.ignore(numeric_limits<streamsize>::max(), '\n');	//remove content
					cout << endl << "Please give a valid date! " << endl;
					cout << "Enter New Terminate Date: ";
					cin >> current->dateTerminated;
				}
				break;

			case 4:
				cout << "Enter New Hourly Rate: ";
				cin >> current->hourlyRate;

				while (cin.fail() || current->hourlyRate > 15)	//if letter is found, ask again
				{
					cin.clear();	//remove input operation
					cin.ignore(numeric_limits<streamsize>::max(), '\n');	//remove content
					cout << endl << "Please give a valid hourly rate! " << endl;
					current->hourlyRate = 0;
					cout << "Enter New Hourly Rate: ";
					cin >> current->hourlyRate;
				}

				break;

			case 5:
				cout << "Enter New Phone Number: ";
				cin >> current->phoneNumber;

				while (cin.fail() || current->phoneNumber.size() >= 13 || current->phoneNumber.size() <= 9)
				{
					cin.clear();	//remove input operation
					cin.ignore(numeric_limits<streamsize>::max(), '\n');	//remove content
					cout << endl << "Please give a valid phone number! " << endl;
					cout << "Enter New Phone Number: ";
					cin >> current->phoneNumber;
				}
				break;

			case 6:
				cout << "Enter New Address: ";
				cin >> current->address;
				while (cin.fail())
				{
					cin.clear();	//remove input operation
					cin.ignore(numeric_limits<streamsize>::max(), '\n');	//remove content
					cout << endl << "Please give a valid house address! " << endl;
					cout << "Enter New Address: ";
					cin >> current->address;
				}
				break;

			case 7:
				cout << "Enter New Credential: ";
				cin >> current->credential;
				while (cin.fail())
				{
					cin.clear();	//remove input operation
					cin.ignore(numeric_limits<streamsize>::max(), '\n');	//remove content
					cout << endl << "Please give a valid credential! " << endl;
					cout << "Enter New Credential: ";
					cin >> current->credential;
				}
				break;

			case 8:
				cout << "Enter New Branch: ";
				cin >> current->branch;
				while (cin.fail())
				{
					cin.clear();	//remove input operation
					cin.ignore(numeric_limits<streamsize>::max(), '\n');	//remove content
					cout << endl << "Please give a valid branch! " << endl;
					cout << "Enter New Branch: ";
					cin >> current->branch;
				}
				break;

			case 9:
				cout << "Enter New SubjectCode: ";
				cin >> current->subjectCode;

				cout << "Enter New SubjectName: ";
				cin >> current->subjectName;

				while (cin.fail())
				{
					cin.clear();	//remove input operation
					cin.ignore(numeric_limits<streamsize>::max(), '\n');	//remove content
					cout << endl << "Please give a valid subject! " << endl;
					cout << "Enter New SubjectCode: ";
					cin >> current->subjectCode;

					cout << "Enter New SubjectName: ";
					cin >> current->subjectName;
				}
				break;

			case 10:
				cout << "Enter New Rating: ";
				cin >> current->rating;
				while (cin.fail() || current->rating >= 6 || current->rating <= -1)
				{
					cin.clear();	//remove input operation
					cin.ignore(numeric_limits<streamsize>::max(), '\n');	//remove content
					cout << endl << "Please give a valid rating! " << endl;
					cout << "Enter New Rating: ";
					cin >> current->rating;
				}
				break;
			}
		}
		current = current->nextAddress;
	}
}

string todayDate()
{
	time_t t = time(NULL);
	struct tm now;
	localtime_s(&now, &t);
	string today = to_string(now.tm_mday).append("/").append(to_string(0)).append((to_string(now.tm_mon + 1))).append("/").append(to_string((now.tm_year) + 1900));
	//cout << " Current Date: " << today;

	return today;
}

//Delete Tutor Record (delete based on keyword)
void deleteTutor(string TutorID)
{
	Tutor* current1 = head;
	while (current1 != NULL)
	{
		if (current1->tutorID == TutorID && current1->dateTerminated != "-")
		{
			int diff = getDateDifference(current1->dateTerminated, todayDate());
			if (diff < 180)
			{
				cout << "Cannot delete this tutor as the termination duration from today has not reach at least 6 months!" << endl;
			}
			else
			{
				int choice = 0;
				cout << "Are you sure to delete this tutor? 1- YES, Others- NO" << endl;
				searchByTutorID(TutorID);
				cout << "Enter your choice: ";
				cin >> choice;
				if (choice == 1)
				{
					//list is empty
					if (head == NULL)
					{
						cout << "Empty list!" << endl;
						return;
					}
					//head tutorID is the one to be deleted
					else if (head->tutorID == TutorID)
					{
						Tutor* current = head;
						head = head->nextAddress;
						cout << "Records to be deleted:-";
						cout << current->tutorID << " - " << current->firstName << " - " << current->lastName << " - " << current->dateJoined << " - "
							<< current->dateTerminated << " - " << current->hourlyRate << " - " << current->phoneNumber << " - " << current->address << " - "
							<< current->credential << " - " << current->branch << " - " << current->subjectCode << " - " << current->subjectName << " - "
							<< current->rating << endl << endl;
						cout << TutorID << " is deleted from the list!" << endl;
						delete current;
						::sizeofLinkedListforTutor--;
						return;
					}
					//tutorID to be deleted is not at first place
					else
					{
						Tutor* current = head->nextAddress;
						Tutor* previous = head;

						while (current != NULL)
						{
							if (current->tutorID == TutorID)
							{
								cout << "Records to be deleted:-";
								cout << current->tutorID << " - " << current->firstName << " - " << current->lastName << " - " << current->dateJoined << " - "
									<< current->dateTerminated << " - " << current->hourlyRate << " - " << current->phoneNumber << " - " << current->address << " - "
									<< current->credential << " - " << current->branch << " - " << current->subjectCode << " - " << current->subjectName << " - "
									<< current->rating << endl << endl;
								previous->nextAddress = current->nextAddress;
								cout << TutorID << " is deleted from the list!" << endl;
								delete current;
								::sizeofLinkedListforTutor--;
								return;
							}
							previous = current;
							current = current->nextAddress;
						}
						cout << "Tutor ID " << TutorID << " is not found in the list!" << endl;
					}
				}
			}
		}
		current1 = current1->nextAddress;
	}
}

//Check Whether There Is Slots Available
int checkVacantSlot(string branchname)
{
	int countBJ = 0, countCH = 0, countPJ = 0, totalslot = 10;
	Tutor* current = head;

	// to count how many branches are there in the system
	while (current != NULL)
	{
		if (current->branch == "Bukit Jalil")
		{
			countBJ++;
		}
		else if (current->branch == "Cheras")
		{
			countCH++;
		}
		else
		{
			countPJ++;
		}
		current = current->nextAddress;
	}

	if (branchname == "Bukit Jalil")
	{
		return totalslot - countBJ;
	}
	else if (branchname == "Cheras")
	{
		return totalslot - countCH;
	}
	else if (branchname == "Petaling jaya")
	{
		return totalslot - countPJ;
	}
	else
	{
		cout << "Error!";
	}
}

void checkBranch(string branch, string userCode)
{
	int choice = 0;
	int rlyExit = 0;
	string tutorID = "";
	string name = "";
	string dateJoined = "";
	string phoneNumber = "";
	string address = "";
	string subject = "";
	string branch1 = "";
	int rating = 0;
	string searchTutor = "";
	//do {
	Tutor* current = head;
	//displayAllRecords(sizeofLinkedListforTutor, branch);
	displayTutorMenu();
	cin >> choice;

	switch (choice)
	{
	case 1:
		//View Personal Profile
		while (current != NULL)
		{
			if (current->tutorID == userCode)
			{
				tutorID = userCode;
				name = current->firstName + " " + current->lastName;
				dateJoined = current->dateJoined;
				phoneNumber = current->phoneNumber;
				address = current->address;
				credential = current->credential;
				subject = current->subjectCode + " " + current->subjectName;
				branch1 = current->branch;
			}
			current = current->nextAddress;
		}
		cout << string(82, '=') << endl;
		cout << "|" << string(25, ' ') << "Personal Profile" << string(25, ' ') << "|" << endl;
		cout << string(82, '=') << endl;
		cout << string(1, ' ') << "Tutor ID: " << tutorID << endl;
		cout << string(1, ' ') << "Name: " << name << endl;
		cout << string(1, ' ') << "Date Joined: " << dateJoined << endl;
		cout << string(1, ' ') << "Phone Number: " << phoneNumber << endl;
		cout << string(1, ' ') << "Address: " << address << endl;
		cout << string(1, ' ') << "Credential: " << credential << endl;
		cout << string(1, ' ') << "Subject: " << subject << endl;

		cout << string(82, '=') << endl;
		cout << endl;
		cout << "Directing User Back To Menu..........";
		cout << endl;
		checkBranch(branch1, userCode);
		break;
	case 2:
		//Modify Personal Profile
		displayModifyPersonalInfoMenu();
		int option;
		cin >> option;
		while (current != NULL)
		{
			if (current->tutorID == userCode)
			{
				switch (option)
				{
				case 1:
					cout << "Enter New First Name: ";
					cin >> current->firstName;

					cout << "Enter New Last Name: ";
					cin >> current->lastName;

					while (cin.fail())
					{
						cin.clear();	//remove input operation
						cin.ignore(numeric_limits<streamsize>::max(), '\n');	//remove content
						cout << endl << "Please give a valid name! " << endl;
						cout << "Enter New First Name: ";
						cin >> current->firstName;
						cout << "Enter New Last Name: ";
						cin >> current->lastName;
					}

					break;

				case 2:
					cout << "Enter New Phone Number: ";
					cin >> current->phoneNumber;

					while (cin.fail() || current->phoneNumber.size() >= 13)
					{
						cin.clear();	//remove input operation
						cin.ignore(numeric_limits<streamsize>::max(), '\n');	//remove content
						cout << endl << "Please give a valid phone number! " << endl;
						cout << "Enter New Phone Number: ";
						cin >> current->phoneNumber;
					}

					break;

				case 3:
					cout << "Enter New Address: ";
					cin >> current->address;
					while (cin.fail())
					{
						cin.clear();	//remove input operation
						cin.ignore(numeric_limits<streamsize>::max(), '\n');	//remove content
						cout << endl << "Please give a valid house address! " << endl;
						cout << "Enter New Address: ";
						cin >> current->address;
					}
					break;

				case 4:
					cout << "Enter New Credential: ";
					cin >> current->credential;
					while (cin.fail())
					{
						cin.clear();	//remove input operation
						cin.ignore(numeric_limits<streamsize>::max(), '\n');	//remove content
						cout << endl << "Please give a valid credential! " << endl;
						cout << "Enter New Credential: ";
						cin >> current->credential;
					}
					break;
				}
			}
			current = current->nextAddress;
		}
		cout << "Directing User Back To Menu..........";
		cout << endl;
		checkBranch(branch1, userCode);

		break;
	case 3:
		//View Other Tutor Profile
		do
		{
			sortByTutorID(&head);
			displayAllRecords(sizeofLinkedListforTutor, branch);

			cout << "Who you would like to search? ";
			cin >> searchTutor;

			while (current != NULL)
			{
				if ((current->tutorID).find(searchTutor) != string::npos && current->branch == branch)
				{
					tutorID = current->tutorID;
					name = current->firstName + " " + current->lastName;
					dateJoined = current->dateJoined;
					phoneNumber = current->phoneNumber;
					address = current->address;
					subject = current->subjectCode + " " + current->subjectName;

					cout << "Results found!" << endl;
					cout << tutorID << "-" << name << "-" << dateJoined << "-" << phoneNumber << "-" << address << "-"
						<< subject << endl;
				}

				current = current->nextAddress;
			}
			cout << "Search another tutor? 1 = YES, Others = NO ";
			cin >> choice;
		} while (choice == 1);
		cout << "Directing User Back To Menu..........";
		cout << endl;
		checkBranch(branch1, userCode);

		break;
	case 4:
		//Exit the system
		rlyExit = displayExitMenu();
		if (rlyExit == 1)
		{
			checkLogin();
		}
		else
		{
			exit(0);
		}
		break;

	default:
		cout << "Invalid Choice! Please Re-Enter Your Choice";
		cout << endl;
	}

	//cout << "Anything else to work on this section? 1- YES, Others- NO ";
//	cin >> choice;
//	//current = NULL;
//} while (choice == 1);
}

//Validate HR and Admin's Login Credentials
void checkAccess(string userCode, string credentials)
{
	Access* current = head1;
	bool found = 0, opt = true;
	int i = 0;
	int choice = 0;
	int rlyExit = 0;
	string userType = "";
	string branch = "";
	int slots = 0;
	string searchTutor = "";
	string branchSlot = "";
	string ID = "";

	//Convert The First Letter Of The User Code To UpperCase
	//To ensure that the user code's prefix are in capital letters
	userCode[0] = toupper(userCode[0]);
	userCode[1] = toupper(userCode[1]);

	//Compare HR and Admin User Code & Credentials With The System's Access Records
	while (current != NULL) {
		if (userCode == current->userCode && credentials == current->credentials)
		{
			found = 1;
			userType = current->userType;
			branch = current->branch;
			break;
		}
		current = current->nextAddress1;
	}

	//Check Whether HR and Admin Credentials Are Valid
	if (found == 1 && userType == "HR")
	{
		cout << "Login Successful !!";
		cout << "Welcome " + userCode;

		do {
			cout << endl;
			displayHRMenu();
			cin >> choice;
			switch (choice)
			{
			case 1:
				cout << "Please Choose The Branch That You Would Like To Add" << endl;
				cout << "1. Bukit Jalil \t 2. Petaling Jaya \t 3. Cheras" << endl;
				cout << "Branch: ";
				cin >> choice;
				switch (choice)
				{
				case 1:
					branchSlot = "Bukit Jalil";
					break;
				case 2:
					branchSlot = "Petaling Jaya";
					break;
				case 3:
					branchSlot = "Cheras";
					break;
				default:
					cout << "Invalid Choice !!! Please Try Again!";
					break;
				}
				slots = checkVacantSlot(branchSlot);
				cout << endl << endl;

				if (slots <= 0)
					cout << "Cannot add new tutor anymore! The slots for " << branchSlot << "  are full now!";
				cout << "Current slots in " << branchSlot << ": " << slots << endl;

				do
				{
					cout << "Tutor ID: ";
					cin >> tutorID;
					cout << endl;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');   //remove content

					cout << "Tutor First Name: ";
					getline(cin, firstName);

					cout << "Tutor Last Name: ";
					getline(cin, lastName);
					while (cin.fail())
					{
						cin.clear();	//remove input operation
						cin.ignore(numeric_limits<streamsize>::max(), '\n');	//remove content
						cout << endl << "Please give a valid name! " << endl;
						cout << "Tutor First Name: ";
						getline(cin, firstName);

						cout << "Tutor Last Name: ";
						getline(cin, lastName);
					}

					cout << "Joined Date: ";
					getline(cin, dateJoined);
					while (cin.fail() || dateJoined.size() != 10)
					{
						cin.clear();	//remove input operation
						cin.ignore(numeric_limits<streamsize>::max(), '\n');	//remove content
						cout << endl << "Please give a valid date! " << endl;
						cout << "Joined Date: ";
						getline(cin, dateJoined);
					}

					cout << "Hourly Rate: ";
					cin >> hourlyRate;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					while (cin.fail() || hourlyRate < 40 || hourlyRate > 80)
					{
						cin.clear();	//remove input operation
						cin.ignore(numeric_limits<streamsize>::max(), '\n');	//remove content
						cout << endl << "Please give a valid hourly rate! " << endl;
						cout << "Hourly Rate: ";
						cin >> hourlyRate;
					}

					cout << "Phone Number: ";
					cin >> phoneNumber;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					while (cin.fail() || phoneNumber.size() >= 13 || phoneNumber.size() <= 9)
					{
						cin.clear();	//remove input operation
						cin.ignore(numeric_limits<streamsize>::max(), '\n');	//remove content
						cout << endl << "Please give a valid phone number! " << endl;
						cout << "Phone Number: ";
						cin >> phoneNumber;
					}

					cout << "House Address: ";
					getline(cin, address);
					while (cin.fail())
					{
						cin.clear();	//remove input operation
						cin.ignore(numeric_limits<streamsize>::max(), '\n');	//remove content
						cout << endl << "Please give a valid house address! " << endl;
						cout << "House Address: ";
						getline(cin, address);
					}

					cout << "Credentials: ";
					cin >> credential;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					while (cin.fail())
					{
						cin.clear();	//remove input operation
						cin.ignore(numeric_limits<streamsize>::max(), '\n');	//remove content
						cout << endl << "Please give a valid credential! " << endl;
						cout << "Credential: ";
						cin >> credential;
					}

					cout << "Branch Name: " << branchSlot << endl;

					cout << "Subject Code: ";
					cin >> subjectCode;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');

					cout << "Subject Name: ";
					getline(cin, subjectName);

					while (cin.fail())
					{
						cin.clear();	//remove input operation
						cin.ignore(numeric_limits<streamsize>::max(), '\n');	//remove content
						cout << endl << "Please give a valid subject! " << endl;
						cout << "Subject Code: ";
						cin >> subjectCode;

						cout << "Subject Name: ";
						getline(cin, subjectName);
					}

					Tutor* newnode = CreateNewNode(tutorID, firstName, lastName, dateJoined, "-", hourlyRate, phoneNumber, address, credential, branchSlot, subjectCode, subjectName, 0);
					addTutor(newnode);

					cout << "The following list is sorted as below:";
					sortByTutorID(&head);

					cout << endl << "Do you still want to add a new tutor?"
						<< " 1- YES, Others- NO : ";
					cin >> choice;
					cout << endl;
				} while (choice == 1);
				break;

			case 2:
				//Types of sorting before displaying the tutor lists
				do {
					displaySortMenu();
					cin >> choice;
					switch (choice)
					{
					case 1:
						cout << "Tutor Details sorted by Hourly Rate: " << endl;
						sortByHourlyRate(&head);
						displayList();
						cout << endl;
						break;
					case 2:
						cout << "Tutor Details sorted by Overall Performance: " << endl;
						sortByOverallPerformance(&head);
						displayList();
						cout << endl;
						break;
					case 3:
						cout << "Tutor Details sorted by Tutor ID: " << endl;
						sortByTutorID(&head);
						displayList();
						cout << endl;
						break;
					default:
						cout << "Invalid selection" << endl;
						opt = false;
						break;
					}
				} while (!opt);

				cout << endl;
				//Search tutor
				cout << "Search by? 1- TutorID, 2- Ratings: " << endl;
				cin >> choice;
				if (choice == 1)
				{
					do
					{
						cout << "Which tutor like to search by ID? ";
						cin >> searchTutor;
						searchByTutorID(searchTutor);
						cout << endl;
						cout << "Search tutor again by ID? 1 = YES, Others = NO: ";
						cin >> choice;
					} while (choice == 1);

					cout << "Want to search by ratings instead? 1 = YES, Others = NO: ";
					cin >> choice;
					if (choice == 1)
					{
						do
						{
							cout << "Rating range?";
							cin >> rating;
							searchByRating(to_string(rating));
							cout << endl;
							cout << "Search tutor again by rating? 1 = YES, Others = NO: ";
							cin >> choice;
						} while (choice == 1);
					}
				}
				else if (choice == 2)
				{
					do
					{
						cout << "Rating range? ";
						cin >> rating;
						searchByRating(to_string(rating));
						cout << endl;
						cout << "Search tutor again by rating? 1 = YES, Others = NO: " << endl;
						cin >> choice;
					} while (choice == 1);

					cout << "Want to search by TutorID instead? 1 = YES, Others = NO: " << endl;
					cin >> choice;
					if (choice == 1)
					{
						do
						{
							cout << "Which tutor like to search by ID? ";
							cin >> searchTutor;
							searchByTutorID(searchTutor);
							cout << endl;
							cout << "Search tutor again by ID? 1 = YES, Others = NO: " << endl;
							cin >> choice;
						} while (choice == 1);
					}
				}
				break;
			case 3:
				do
				{
					cout << "Which tutor details to edit? ";
					cin >> tutorID;
					searchByTutorID(tutorID);
					cout << endl;
					do
					{
						displayModifyTutorMenu();
						cin >> choice;
						modifyTutor(tutorID, choice);
						cout << "Do you want to edit again? 1 = YES, 0 = NO: ";
						cin >> choice;
					} while (choice == 1);
					cout << "Do you want to edit another tutor? 1 = YES, 0 = NO: ";
					cin >> choice;
				} while (choice == 1);

				break;

			case 4:
				do
				{
					string keyword;

					cout << "Which tutor do you want to delete? Please provide his/ her Tutor ID: ";
					cin >> keyword;
					cout << endl;

					deleteTutor(keyword);

					//after delete, display list again
					displayList();
					cout << endl << "The current amount of the size is " << ::sizeofLinkedListforTutor << endl;

					cout << "Delete another tutor? 1 = YES, 0 = NO: ";
					cin >> choice;
				} while (choice == 1);

				break;

			case 5:
				generateReport();
				break;
			case 6:

				rlyExit = displayExitMenu();
				if (rlyExit == 1)
				{
					checkLogin();

				}
				else
				{
					exit(0);
				}
				break;

			default:
				cout << "Invalid selection, Please Try Again" << endl;
				break;
			}

			cout << "View menu again? 1- YES, Others- NO:";
			cin >> choice;
		} while (choice == 1);
		return;
	}
	else if (found == 1 && userType == "Admin")
	{
		cout << "Login Successful !! ";
		Access* current = head1;

		while (current != NULL) {
			if (current->userCode == userCode)
			{
				branchSlot = current->branch;
			}
			current = current->nextAddress1;
		}

		do {
			cout << endl;
			displayAdminMenu();
			cin >> choice;
			switch (choice)
			{
			case 1:
				//Add new tutor
				slots = checkVacantSlot(branchSlot);
				cout << endl << endl;

				if (slots <= 0)
					cout << "Cannot add new tutor anymore! The slots for " << branchSlot << "  are full now!";
				cout << "Current slots in " << branchSlot << ": " << slots << endl;

				do
				{
					cout << "Tutor ID: ";
					cin >> tutorID;
					cout << endl;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');   //remove content

					cout << "Tutor First Name: ";
					getline(cin, firstName);

					cout << "Tutor Last Name: ";
					getline(cin, lastName);
					while (cin.fail())
					{
						cin.clear();	//remove input operation
						cin.ignore(numeric_limits<streamsize>::max(), '\n');	//remove content
						cout << endl << "Please give a valid name! " << endl;
						cout << "Tutor First Name: ";
						getline(cin, firstName);

						cout << "Tutor Last Name: ";
						getline(cin, lastName);
					}

					cout << "Joined Date: ";
					getline(cin, dateJoined);
					while (cin.fail() || dateJoined.size() != 10)
					{
						cin.clear();	//remove input operation
						cin.ignore(numeric_limits<streamsize>::max(), '\n');	//remove content
						cout << endl << "Please give a valid date! " << endl;
						cout << "Joined Date: ";
						getline(cin, dateJoined);
					}

					cout << "Hourly Rate: ";
					cin >> hourlyRate;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					while (cin.fail() || hourlyRate < 40 || hourlyRate > 80)
					{
						cin.clear();	//remove input operation
						cin.ignore(numeric_limits<streamsize>::max(), '\n');	//remove content
						cout << endl << "Please give a valid hourly rate! " << endl;
						cout << "Hourly Rate: ";
						cin >> hourlyRate;
					}

					cout << "Phone Number: ";
					cin >> phoneNumber;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					while (cin.fail() || phoneNumber.size() >= 13 || phoneNumber.size() <= 9)
					{
						cin.clear();	//remove input operation
						cin.ignore(numeric_limits<streamsize>::max(), '\n');	//remove content
						cout << endl << "Please give a valid phone number! " << endl;
						cout << "Phone number: ";
						getline(cin, phoneNumber);
					}

					cout << "House Address: ";
					getline(cin, address);
					while (cin.fail())
					{
						cin.clear();	//remove input operation
						cin.ignore(numeric_limits<streamsize>::max(), '\n');	//remove content
						cout << endl << "Please give a valid house address! " << endl;
						cout << "House Address: ";
						getline(cin, address);
					}

					cout << "Credentials: ";
					cin >> credential;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					while (cin.fail())
					{
						cin.clear();	//remove input operation
						cin.ignore(numeric_limits<streamsize>::max(), '\n');	//remove content
						cout << endl << "Please give a valid credential! " << endl;
						cout << "Credentials: ";
						cin >> credential;
					}

					cout << "Branch Name: " << branchSlot << endl;

					cout << "Subject Code: ";
					cin >> subjectCode;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');

					cout << "Subject Name: ";
					getline(cin, subjectName);

					while (cin.fail())
					{
						cin.clear();	//remove input operation
						cin.ignore(numeric_limits<streamsize>::max(), '\n');	//remove content
						cout << endl << "Please give a valid subject! " << endl;
						cout << "Subject Code: ";
						cin >> subjectCode;

						cout << "Subject Name: ";
						getline(cin, subjectName);
					}

					Tutor* newnode = CreateNewNode(tutorID, firstName, lastName, dateJoined, "-", hourlyRate, phoneNumber, address, credential, branchSlot, subjectCode, subjectName, 0);
					addTutor(newnode);

					cout << endl << "Do you still want to add a new tutor? 1- YES, Others- NO: ";
					cin >> choice;
					cout << endl;
				} while (choice == 1);
				/*}*/
				break;

			case 2:
				//View Tutor
				sortByTutorID(&head);
				displayAllRecords(sizeofLinkedListforTutor, branch);
				cout << endl;
				cout << "Search by? 1- TutorID, 2- Ratings: ";
				cin >> choice;
				if (choice == 1)
				{
					do
					{
						cout << "Which tutor like to search by ID? ";
						cin >> searchTutor;

						searchByTutorID(searchTutor, branch);
						cout << endl;
						cout << "Search tutor again by ID? 1 = YES, Others = NO: ";
						cin >> choice;
					} while (choice == 1);

					cout << "Want to search by ratings instead? 1 = YES, Others = NO: ";
					cin >> choice;
					if (choice == 1)
					{
						do
						{
							cout << "Rating range?";
							cin >> rating;
							searchByRating(to_string(rating), branch);
							cout << endl;
							cout << "Search tutor again by rating? 1 = YES, Others = NO: ";
							cin >> choice;
						} while (choice == 1);
					}
				}
				else if (choice == 2)
				{
					do
					{
						cout << "Rating range? ";
						cin >> rating;
						searchByRating(to_string(rating), branch);
						cout << endl;
						cout << "Search tutor again by rating? 1 = YES, Others = NO: " << endl;
						cin >> choice;
					} while (choice == 1);

					cout << "Want to search by TutorID instead? 1 = YES, Others = NO: " << endl;
					cin >> choice;
					if (choice == 1)
					{
						do
						{
							cout << "Which tutor like to search by ID? ";
							cin >> searchTutor;
							searchByTutorID(searchTutor, branch);
							cout << endl;
							cout << "Search tutor again by ID? 1 = YES, Others = NO: " << endl;
							cin >> choice;
						} while (choice == 1);
					}
				}
				break;

			case 3:
				//Exit the system
				rlyExit = displayExitMenu();
				if (rlyExit == 1)
				{
					checkLogin();

				}
				else
				{
					exit(0);
				}

				break;

			default:
				cout << "Invalid selection, Please Try Again." << endl;
				break;
			}

			cout << "View menu again? 1 = YES, Others = NO:";
			cin >> choice;
		} while (choice == 1);
		return;
	}
	else
	{
		cout << "Invalid User Code & Credentials !!! Please Double Check Your Credentials !!!";
		cout << endl;

		cout << string(82, '=') << endl;
		cout << "|" << string(20, ' ') << "Please Select ONE User Type From The Menu" << string(19, ' ') << "|" << endl;
		cout << string(82, '=') << endl;
		/*User Type selection*/
		cout << "1. Admin" << endl;
		cout << "2. HR" << endl;
		cout << endl;
		cout << "Please Enter Your Option : ";

		cin >> choice;
		switch (choice)
		{
		case 1:
			userType = "Admin";
			cout << endl;
			cout << "Please Enter Your User Code : ";
			cin >> userCode;
			cout << endl;
			cout << "Please Enter Your Credentials : ";
			credentials = takePasswdFromUser();

			checkAccess(userCode, credentials);
			break;
		case 2:
			userType = "HR";
			cout << endl;
			cout << "Please Enter Your User Code : ";
			cin >> userCode;
			cout << endl;
			cout << "Please Enter Your Credentials : ";
			credentials = takePasswdFromUser();
			cout << endl;
			checkAccess(userCode, credentials);
			break;

		default:
			cout << "User Account Invalid ! Please Double Check Your Credentials !!!";
			cout << endl;
		}
	}

	cout << "Perform operations again? 1 = YES, 0 = NO: " << endl;
	cin >> choice;
	//} while (choice == 1);
};

//Validate Tutor's Login Credentials
string checkTutor(string userCode, string credentials)
{
	Tutor* current = head;
	bool found = 0;
	int i = 0, choice = 0;
	string branch = "", userType = "";

	//Convert The First Letter Of The User Code To UpperCase
	userCode[0] = toupper(userCode[0]);

	//Compare Tutor's Tutor ID & Credentials With The System's Tutor Records
	while (current != NULL) {
		if (userCode == current->tutorID && credentials == current->credential)
		{
			branch = current->branch;
			found = 1;
			break;
		}
		current = current->nextAddress;
	}

	//Check Whether Tutor Credentials Are Valid
	if (found == 0)
	{
		cout << "Invalid Tutor ID & Credentials !!! Please Double Check Your Credentials !!!";
		cout << endl << endl;

		userType = "Tutor";
		cout << endl;
		cout << "Please Enter Your Tutor ID : ";
		cin >> userCode;
		cout << endl;
		cout << "Please Enter Your Credentials : ";
		credentials = takePasswdFromUser();
		cout << endl;
		checkBranch(checkTutor(userCode, credentials), userCode);
	}
	else
	{
		cout << "Login Successful !!";
		cout << endl;
		return branch;
	}
};

//Validate User Login Based On User Type
void checkLogin()
{
	int choice;
	string userCode, userType, credentials, branch;

	displayUserType();

	cin >> choice;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << endl << "Please provide a valid choice! " << endl;
		cout << "Please Enter Your Option : ";
		cin >> choice;
	}

	switch (choice)
	{
	case 1:
		userType = "Admin";
		cout << endl;
		cout << "Please Enter Your User Code : ";
		cin >> userCode;
		cout << endl;
		cout << "Please Enter Your Credentials : ";
		credentials = takePasswdFromUser();
		checkAccess(userCode, credentials);
		break;
	case 2:
		userType = "HR";
		cout << endl;
		cout << "Please Enter Your User Code : ";
		cin >> userCode;
		cout << endl;
		cout << "Please Enter Your Credentials : ";
		credentials = takePasswdFromUser();
		cout << endl;
		checkAccess(userCode, credentials);
		break;
	case 3:
		userType = "Tutor";
		cout << endl;
		cout << "Please Enter Your Tutor ID : ";
		cin >> userCode;
		cout << endl;
		cout << "Please Enter Your Credentials : ";
		credentials = takePasswdFromUser();
		cout << endl;
		checkBranch(checkTutor(userCode, credentials), userCode);
		break;

	default:
		cout << "User Account Invalid ! Please Double Check Your Credentials !!!";
		cout << endl;
	}
};

int main() {
	head = NULL;

	int choice = 1;
	int exit = 0;
	bool input = true;

	Tutor* newnode = CreateNewNode("B0001", "Wendy", "Foo", "30/05/2019", "30/05/2020", 40.00, "012-0723445", "G122 Banana Condominium",
		"iluvtodrink", "Bukit Jalil", "BJ03", "Chinese", 0);
	addTutor(newnode);

	newnode = CreateNewNode("C0002", "Ali", "Muhammad", "30/05/2022", "-", 45.00, "012-3477690", "A203 Strawberry Apartment",
		"iluvtoeat", "Cheras", "CH04", "Science", 5);
	addTutor(newnode);

	newnode = CreateNewNode("C0001", "Sulaiman", "Bakar", "30/05/2022", "-", 50.00, "019-2344567", "A202 Strawberry Apartment",
		"iluvtoburn", "Cheras", "CH01", "Malay", 4);
	addTutor(newnode);

	newnode = CreateNewNode("P0001", "Kenny", "Tan", "30/05/2022", "30/06/2022", 55.00, "016-1288965", "J901 Watermelon Apartment",
		"iluvtoplay", "Petaling Jaya", "PJ03", "Chinese", 3);
	addTutor(newnode);

	newnode = CreateNewNode("P0002", "Ali", "Tan", "30/05/2019", "10/06/2019", 60.00, "016-1288965", "J901 Watermelon Apartment",
		"iluvtoplay", "Petaling Jaya", "PJ03", "Chinese", 3);
	addTutor(newnode);

	//Initialize admin and HR records
	Access* newnode1 = CreateNewNode("HR001", "HR", "HQ", "12345");
	addAccess(newnode1);

	newnode1 = CreateNewNode("A001", "Admin", "Bukit Jalil", "23456");
	addAccess(newnode1);

	newnode1 = CreateNewNode("A002", "Admin", "Cheras", "34567");
	addAccess(newnode1);

	newnode1 = CreateNewNode("A003", "Admin", "Puchong", "45678");
	addAccess(newnode1);

	//do {
	//	displayStartMenu();
	//	cin >> choice;
	//	switch (choice)
	//	{
	//	case 1:
	//		system("CLS");
	//		checkLogin();
	//		break;
	//	case 2:
	//		displayExitMenu();
	//		break;

	//	default:
	//		cout << "Invalid Choice !!! Please Try Again";
	//		input = false;
	//		system("CLS");
	//		break;
	//	}
	//} while (!input);

	switch (loginInput())
	{
	case 1:
		system("CLS");
		checkLogin();
		break;
	case 2:
		exit = displayExitMenu();
		if (exit == 1)
		{
			checkLogin();
		}
		else
		{
			displayExitMenu();
		}
		break;

	default:
		cout << "Invalid Choice !!! Please Try Again";
		input = false;
		system("CLS");
		break;
	}
	return 0;
}