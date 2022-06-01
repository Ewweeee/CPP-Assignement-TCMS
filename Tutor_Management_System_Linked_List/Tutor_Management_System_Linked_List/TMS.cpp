#include <iostream>
#include <string>
#include <iomanip>
#include "Menu.h"
#include "Struct.h"
#include "conio.h"
using namespace std;

//Function Prototype

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

			// Cout statement is very
			// important as it will erase
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
{	// to change:
	//different inseertion sort (2 * 3 times)
	// 
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
	// to change:
	//different insertion sort (2 * 3 times)
	// 
	// Initialize 'sorted' - a sorted doubly linked list
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
	// to change:
	//different insertion sort (2 * 3 times)
	// 
	// Initialize 'sorted' - a sorted doubly linked list
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
	int position = 1;

	while (current != NULL)
	{
		if ((current->tutorID).find(keyword) != string::npos)	//string::npos---> substring
		{
			cout << count << ". " << position << " - " << current->tutorID << " - " << current->firstName << " - " << current->lastName << " - " << current->dateJoined << " - "
				<< current->dateTerminated << " - " << current->hourlyRate << " - " << current->phoneNumber << " - " << current->address << " - "
				<< current->credential << " - " << current->branch << " - " << current->subjectCode << " - " << current->subjectName << " - "
				<< current->rating << endl;
			count++;
		}
		position++;
		current = current->nextAddress;
	}
	cout << endl << "Searching is done here!" << endl;
}

void searchByRating(string keyrating)
{
	Tutor* current = head;
	int count = 1;	//list number
	int position = 1;

	while (current != NULL)
	{
		if (to_string(current->rating).find(keyrating) != string::npos)	//string::npos---> substring
		{
			cout << count << ". " << position << " - " << current->tutorID << " - " << current->firstName << " - " << current->lastName << " - " << current->dateJoined << " - "
				<< current->dateTerminated << " - " << current->hourlyRate << " - " << current->phoneNumber << " - " << current->address << " - "
				<< current->credential << " - " << current->branch << " - " << current->subjectCode << " - " << current->subjectName << " - "
				<< current->rating << endl;
			count++;
		}
		position++;
		current = current->nextAddress;
	}
	cout << endl << "Searching is done here!" << endl;

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
	cout << "Please Enter Your Choice: " << endl;
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
				break;

			case 2:
				cout << "Enter New Join Date: ";
				cin >> current->dateJoined;

				break;

			case 3:
				cout << "Enter New Terminate Date: ";
				cin >> current->dateTerminated;

				break;

			case 4:
				cout << "Enter New Hourly Rate: ";
				cin >> current->hourlyRate;

				break;

			case 5:
				cout << "Enter New Phone Number: ";
				cin >> current->phoneNumber;

				break;

			case 6:
				cout << "Enter New Address: ";
				cin >> current->address;

				break;

			case 87:
				cout << "Enter New Credential: ";
				cin >> current->credential;

				break;

			case 8:
				cout << "Enter New Branch: ";
				cin >> current->branch;

				break;

			case 9:
				cout << "Enter New SubjectCode: ";
				cin >> current->subjectCode;

				cout << "Enter New SubjectName: ";
				cin >> current->subjectName;

				break;

			case 10:
				cout << "Enter New Rating: ";
				cin >> current->rating;

				break;
			}
		}
		current = current->nextAddress;
	}
}

//Delete Tutor Record (delete based on keyword)
void deleteTutor(string TutorID)
{
	int choice = 0;
	cout << "Are you sure to delete this tutor? 1- YES, Others- NO" << endl;
	searchByTutorID(TutorID);
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
					cout << TutorID << "is deleted from the list!" << endl;
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

//Validate Tutor's Login Credentials
string checkTutor(string userCode, string credentials)
{
	Tutor* current = head;
	bool found = 0;
	int i = 0;
	string branch = "";

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
		cout << endl;
		return branch;
	}
	else
	{
		cout << "Login Successful !!";
		cout << endl;
		return branch;
	}
};

void checkBranch(string branch, string userCode)
{
	Tutor* current = head;
	int choice;
	displayAllRecords(sizeofLinkedListforTutor, branch);
	displayTutorMenu();
	cin >> choice;
	string tutorID = "";
	string name = "";
	string dateJoined = "";
	string phoneNumber = "";
	string address = "";
	string subject = "";
	int rating = 0;

	string searchTutor = "";

	switch (choice)
	{
	case 1:
		cout << "1. View Personal Profile" << endl;

		while (current != NULL)
		{
			if (current->tutorID == userCode)
			{
				tutorID = userCode;
				name = current->firstName + " " + current->lastName;
				dateJoined = current->dateJoined;
				phoneNumber = current->phoneNumber;
				address = current->address;
				subject = current->subjectCode + " " + current->subjectName;
			}
			current = current->nextAddress;
		}
		cout << string(82, '=') << endl;
		cout << "|" << string(2, ' ') << "Personal Profile" << string(25, ' ') << "|" << endl;
		cout << string(82, '=') << endl;
		cout << string(1, ' ') << "Tutor ID: " << tutorID << endl;
		cout << string(1, ' ') << "Name: " << name << endl;
		cout << string(1, ' ') << "Date Joined: " << dateJoined << endl;
		cout << string(1, ' ') << "Phone Number: " << phoneNumber << endl;
		cout << string(1, ' ') << "Address: " << address << endl;
		cout << string(1, ' ') << "Subject: " << subject << endl;

		cout << string(82, '=') << endl;
		break;
	case 2:
		cout << "2. Modify Personal Profile" << endl;
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

					break;

				case 2:
					cout << "Enter New Phone Number: ";
					cin >> current->phoneNumber;

					break;

				case 3:
					cout << "Enter New Address: ";
					cin >> current->address;

					break;

				case 4:
					cout << "Enter New Credential: ";
					cin >> current->credential;

					break;
				}
			}
			current = current->nextAddress;
		}

		break;
	case 3:
		cout << "3. View Other Tutor Profile" << endl;
		cout << "Who you would like to search? ";
		cin >> searchTutor;

		while (current != NULL)
		{
			if ((current->tutorID).find(searchTutor) != string::npos && current->branch == branch)
			{
				tutorID = current->tutorID;
				name = current->firstName + current->lastName;
				dateJoined = current->dateJoined;
				phoneNumber = current->phoneNumber;
				address = current->address;
				subject = current->subjectCode + current->subjectName;

				cout << "Results found!" << endl;
				cout << tutorID << "-" << name << "-" << dateJoined << "-" << phoneNumber << "-" << address << "-"
					<< subject << endl;
			}

			current = current->nextAddress;
		}
		cout << "Cannot find tutor!";
		break;
	case 4:
		displayExitMenu();
		break;

	default:
		cout << "Invalid Choice! Please Re-Enter Your Choice";
		cout << endl;
	}

}

//Validate HR and Admin's Login Credentials
void checkAccess(string userCode, string credentials)
{
	Access* current = head1;
	bool found = 0;
	int i = 0;
	string userType;

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
			break;
		}
		current = current->nextAddress1;
	}

	//Check Whether HR and Admin Credentials Are Valid
	if (found == 1 && userType == "HR")
	{
		int choice = 0;
		string searchTutor = "";
		cout << "Login Successful !!";
		cout << "Welcome " + userCode;
		/*Sleep(1000);
		system("CLS");*/
		displayHRMenu();
		cin >> choice;
		switch (choice)
		{
		case 1:
			//while (choice == 1)
			//{
			do
			{
				cout << "Tutor ID: ";
				cin >> tutorID;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');   //remove content

				cout << "Tutor First Name: ";
				getline(cin, firstName);

				cout << "Tutor Last Name: ";
				getline(cin, lastName);

				cout << "Joined Date: ";
				getline(cin, dateJoined);

				cout << "Hourly Rate: RM";
				cin >> hourlyRate;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				cout << "Phone Number: ";
				cin >> phoneNumber;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				cout << "House Address: ";
				getline(cin, address);

				cout << "Credentials: ";
				cin >> credential;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				cout << "Branch Name: ";
				getline(cin, branch);

				cout << "Subject Code: ";
				cin >> subjectCode;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				cout << "Subject Name: ";
				getline(cin, subjectName);

				Tutor* newnode = CreateNewNode(tutorID, firstName, lastName, dateJoined, "-", hourlyRate, phoneNumber, address, credential, branch, subjectCode, subjectName, 0);
				addTutor(newnode);

				cout << endl << "Do you still want to add a new tutor?"
					<< " 1- Yes, others -No : ";
				cin >> choice;
				cout << endl;
			} while (choice == 1);
			/*}*/
			break;

		case 2:
			cout << " Search by? 1- TutorID, 2- Ratings";
			cin >> choice;
			if (choice == 1)
			{
				do
				{
					cout << "Which tutor like to search by ID?";
					cin >> searchTutor;
					searchByTutorID(searchTutor);
					cout << endl;
					cout << "Search tutor again by ID? 1 = YES, Others = NO:";
					cin >> choice;
				} while (choice == 1);

				cout << "Want to search by ratings instead? 1 = YES, Others = NO:";
				cin >> choice;
				if (choice == 1)
				{
					do
					{
						cout << "Which tutor like to search by rating?";
						cin >> rating;
						searchByRating(to_string(rating));
						cout << endl;
						cout << "Search tutor again by rating? 1 = YES, Others = NO:";
						cin >> choice;
					} while (choice == 1);
				}
			}
			else if (choice == 2)
			{
				do
				{
					cout << "Which tutor like to search by rating? ";
					cin >> rating;
					searchByRating(to_string(rating));
					cout << endl;
					cout << "Search tutor again by rating? 1 = YES, Others = NO:" << endl;
					cin >> choice;
				} while (choice == 1);

				cout << "Want to search by TutorID instead? 1 = YES, Others = NO:" << endl;
				cin >> choice;
				if (choice == 1)
				{
					do
					{
						cout << "Which tutor like to search by ID? ";
						cin >> searchTutor;
						searchByTutorID(searchTutor);
						cout << endl;
						cout << "Search tutor again by ID? 1 = YES, Others = NO:" << endl;
						cin >> choice;
					} while (choice == 1);
				}
			}
			break;
		case 3:
			do
			{
				cout << "Which tutor details to edit?";
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
				cout << " Do you want to edit another tutor? 1 = YES, 0 = NO:";
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
			displayExitMenu();
			break;

		default:
			cout << "Invalid selection, Please Try Again" << endl;
		}
		return;
	}
	else if (found == 1 && userType == "Admin")
	{
		cout << "Login Successful !! ";
		/*Sleep(1000);
		system("CLS");*/
		displayAdminMenu();
		return;
	}
	else
	{
		cout << "Invalid User Code & Credentials !!! Please Double Check Your Credentials !!!";
		cout << endl;
	}
};

//Validate User Login Based On User Type
void checkLogin()
{
	int choice;
	string userCode, userType, credentials, branch;

	displayUserType();

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

//Check Whether There Is Slots Available
void checkVacantSlot();


int main() {
	/*string credentials;
	cout << "Please Enter Your Credentials : ";
	credentials = takePasswdFromUser();*/

	head = NULL;

	int choice = 1;

	Tutor* newnode = CreateNewNode("B0001", "Wendy", "Foo", "30/5/2022", "-", 19.00, "012-0723445", "G122 Banana Condominium",
		"iluvtodrink", "Bukit Jalil", "BJ03", "Chinese", 0);
	addTutor(newnode);

	newnode = CreateNewNode("C0002", "Ali", "Muhammad", "30/5/2022", "-", 20.00, "012-3477690", "A203 Strawberry Apartment",
		"iluvtoeat", "Cheras", "CH04", "Science", 5);
	addTutor(newnode);

	newnode = CreateNewNode("C0001", "Sulaiman", "Bakar", "30/5/2022", "-", 15.00, "019-2344567", "A202 Strawberry Apartment",
		"iluvtoburn", "Cheras", "CH01", "Malay", 4);
	addTutor(newnode);

	newnode = CreateNewNode("P0001", "Kenny", "Tan", "30/5/2022", "-", 22.00, "016-1288965", "J901 Watermelon Apartment",
		"iluvtoplay", "Petaling Jaya", "PJ03", "Chinese", 3);
	addTutor(newnode);

	newnode = CreateNewNode("P0002", "Ali", "Tan", "30/5/2022", "-", 22.00, "016-1288965", "J901 Watermelon Apartment",
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

	//checkLogin();
	checkAccess("HR001", "12345");
	cout << endl;
	sortByTutorID(&head);
	displayList();
	////Add function
	//while (choice == 1)
	//{
	//	cout << "Tutor ID: ";
	//	cin >> tutorID;
	//	cin.ignore(numeric_limits<streamsize>::max(), '\n');   //remove content

	//	cout << "Tutor First Name: ";
	//	getline(cin, firstName);

	//	cout << "Tutor Last Name: ";
	//	getline(cin, lastName);

	//	cout << "Joined Date: ";
	//	getline(cin, dateJoined);

	//	cout << "Hourly Rate: RM";
	//	cin >> hourlyRate;
	//	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	//	cout << "Phone Number: ";
	//	cin >> phoneNumber;
	//	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	//	cout << "House Address: ";
	//	getline(cin, address);

	//	cout << "Credentials: ";
	//	cin >> credential;
	//	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	//	cout << "Branch Name: ";
	//	getline(cin, branch);

	//	cout << "Subject Code: ";
	//	cin >> subjectCode;
	//	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	//	cout << "Subject Name: ";
	//	getline(cin, subjectName);

	//	newnode = CreateNewNode(tutorID, firstName, lastName, dateJoined, "-", hourlyRate, phoneNumber, address, credential, branch, subjectCode, subjectName, 0);
	//	addTutor(newnode);

	//	cout << endl << "Do you still want to add a new tutor?"
	//		<< " 1- yes, others -No : ";
	//	cin >> choice;
	//	cout << endl;
	//}



	////Delete function
	//cout << "Do you want to delete tutor? 1 = Yes, 0 = No: ";
	//cin >> choice;
	//while (choice == 1)
	//{
	//	string keyword;

	//	cout << "Which tutor do you want to delete? Please provide his/ her Tutor ID: ";
	//	cin >> keyword;
	//	cout << endl;

	//	deleteTutor(keyword);

	//	//after delete, display list again
	//	displayList();
	//	cout << endl << "The current amount of the size is " << ::sizeofLinkedList << endl;

	//	cout << "Do you want to delete any item based on keyword? 1 = YES, 0 = NO: ";
	//	cin >> choice;
	//}



	//Modify function
	//cout << "Which tutor details to edit?";
	//cin >> tutorID;
	//searchByTutorID(tutorID);
	//cout << endl;
	//do
	//{
	//	displayModifyTutorMenu();
	//	cin >> choice;
	//	modifyTutor(tutorID, choice);
	//	cout << "Do you want to edit again? 1 = YES, 0 = NO: ";
	//	cin >> choice;
	//}
	//while (choice == 1);


	//SearchRating
	//cout << "Which tutor like to search by rating?";
	//cin >> rating;
	//searchByRating(to_string(rating));
	//cout << endl;
	//cout << "Search tutor again by rating? 1 = YES, 0 = NO:";
	//cin >> choice;
	//do
	//{
	//	cout << "Which tutor like to search by rating?";
	//	cin >> rating;
	//	searchByRating(to_string(rating));
	//	cout << endl;
	//	cout << "Search tutor again by rating? 1 = YES, 0 = NO:";
	//	cin >> choice;
	//}
	//while (choice == 1);

	//Sort by TutorID, HourlyRate function
	//sortByTutorID(&head);
	//sortByHourlyRate(&head);
	//sortByOverallPerformance(&head);

	//displayStartMenu();
	//displayAdminMenu();

	//displayList();

	//displayHRMenu();

	//displayList();

	//displayTutorMenu();
	//displayLocationMenu();
	//displayUserType();

	//generateReport();

	return 0;


}