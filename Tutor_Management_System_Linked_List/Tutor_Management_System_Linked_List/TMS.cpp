#include <iostream>
#include <string>
#include <iomanip>
#include "Menu.h"
#include "Struct.h"
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

//Function Prototype

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

//Validate Whether Tutor's Login Credentials
void checkTutor();

//Validate User Login Based On User Type
void checkLogin();

//Check Whether There Is Slots Available
void checkVacantSlot();

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
	::sizeofLinkedList++;
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

				break;

			case 2:
				cout << "Enter New Last Name: ";
				cin >> current->lastName;

				break;

			case 3:
				cout << "Enter New Join Date: ";
				cin >> current->dateJoined;

				break;

			case 4:
				cout << "Enter New Terminate Date: ";
				cin >> current->dateTerminated;

				break;

			case 5:
				cout << "Enter New Hourly Rate: ";
				cin >> current->hourlyRate;

				break;

			case 6:
				cout << "Enter New Phone Number: ";
				cin >> current->phoneNumber;

				break;

			case 7:
				cout << "Enter New Address: ";
				cin >> current->address;

				break;

			case 8:
				cout << "Enter New Credential: ";
				cin >> current->credential;

				break;

			case 9:
				cout << "Enter New Branch: ";
				cin >> current->branch;

				break;

			case 10:
				cout << "Enter New SubjectCode: ";
				cin >> current->subjectCode;

				break;

			case 11:
				cout << "Enter New SubjectName: ";
				cin >> current->subjectName;

				break;

			case 12:
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
		::sizeofLinkedList--;
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
				::sizeofLinkedList--;
				return;
			}
			previous = current;
			current = current->nextAddress;
		}
		cout << "Tutor ID " << TutorID << " is not found in the list!" << endl;
	}
}

//Sort Records By Tutor ID / Hourly Rate / Overall Performance
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

void sortByHourlyRate();

void sortByOverallPerformance();

//Search Records By Tutor ID / Rating
void searchByTutorID();

void searchByRating();

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
	Tutor* current = new Tutor();

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

		break;
	}
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

int main() {

	head = NULL;

	int choice = 1;

	Tutor* newnode = CreateNewNode("C0001", "Ali", "Bakar", "30/5/2022", "-", 10.00, "019-2344567", "A202 Strawberry Apartment",
		"iluvtoburn", "Cheras", "CH01", "Malay", 4);
	addTutor(newnode);

	newnode = CreateNewNode("C0002", "Ali", "Muhammad", "30/5/2022", "-", 10.00, "012-3477690", "A203 Strawberry Apartment",
		"iluvtoeat", "Cheras", "CH04", "Science", 4);
	addTutor(newnode);

	newnode = CreateNewNode("K0001", "Wendy", "Foo", "30/5/2022", "-", 10.00, "012-0723445", "G122 Banana Condominium",
		"iluvtodrink", "Kuala Lumpur", "KL03", "Chinese", 4);
	addTutor(newnode);

	newnode = CreateNewNode("P0001", "Kenny", "Tan", "30/5/2022", "-", 10.00, "016-1288965", "J901 Watermelon Apartment",
		"iluvtoplay", "Puchong", "PU03", "Chinese", 4);
	addTutor(newnode);

	//----------------------------------------------------
	//Add function
	while (choice == 1)
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

		newnode = CreateNewNode(tutorID, firstName, lastName, dateJoined, "-", hourlyRate, phoneNumber, address, credential, branch, subjectCode, subjectName, 0);
		addTutor(newnode);

		cout << endl << "Do you still want to add a new tutor?"
			<< " 1- yes, others -No : ";
		cin >> choice;
		cout << endl;
	}
	//-----------------------------------------------------


	//-----------------------------------------------------
	//Delete function
	cout << "Do you want to delete tutor? 1 = Yes, 0 = No: ";
	cin >> choice;

	while (choice == 1)
	{
		string keyword;

		cout << "Which tutor do you want to delete? Please provide his/ her Tutor ID: ";
		cin >> keyword;
		cout << endl;

		deleteTutor(keyword);

		//after delete, display list again
		displayList();
		cout << endl << "The current amount of the size is " << ::sizeofLinkedList << endl;

		cout << "Do you want to delete any item based on keyword? 1 = YES, 0 = NO: ";
		cin >> choice;
	}
	//-----------------------------------------------------


	//-----------------------------------------------------
	//Modify function
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
	//-----------------------------------------------------



	displayStartMenu();
	displayAdminMenu();

	displayList();

	displayHRMenu();

	displayList();

	displayTutorMenu();
	displayLocationMenu();
	displayUserType();
	//generateReport();

	return 0;


}