#include <iostream>
#include <string>
#include "Menu.h"
#include "Struct.h"
using namespace std;

//Function Prototype

//Validate Whether Tutor's Login Credentials
void checkTutor(string userCode, string credentials)
{
	int i = 0;
	boolean found = 0;

	//Convert The First Letter Of The User Code To UpperCase
	userCode[0] = toupper(userCode[0]);

	//Compare Tutor's Tutor ID & Credentials With The System's Tutor Records
	while (!allTutors[i].tutorID.empty()) {
		if (userCode == allTutors[i].getTutorID() && credentials == allTutors[i].getCredential())
		{
			found = 1;
		}
		i++;
	}

	//Check Whether Tutor Credentials Are Valid
	if (found == 0)
	{
		cout << "Invalid Tutor ID & Credentials !!! Please Double Check Your Credentials !!!";
		cout << endl;
	}
	else
	{
		cout << "Login Successful !!";
		cout << endl;
		return;
	}
};

//Validate User Login Based On User Type
void checkLogin()
{
	int choice;
	string userCode, userType, credentials, branch;
	displayUserType();
	int arraySize = 0; int i = 0;
	while (!allTutors[i].tutorID.empty()) {
		arraySize++;
		i++;
	}

	cin >> choice;
	switch (choice)
	{
	case 1:
		userType = "Admin";
		cout << endl;
		cout << "Please Enter Your User Code : ";
		cin >> userCode;
		cout << endl;

		if (userCode == "A001")
		{
			cout << "Please Enter Tuition Center Branch : ";
			cin >> branch;

			cout << "Please Enter Your Credentials : ";
			cin >> credentials;

			if (branch == "Bukit Jalil")
			{
				displayAllRecords(arraySize - 1, branch);
			}
			else if (branch == "Cheras")
			{
				displayAllRecords(arraySize - 1, branch);
			}
			else if (branch == "Petaling Jaya")
			{
				displayAllRecords(arraySize - 1, branch);
			}
		}
		break;
	case 2:
		userType = "HR";
		cout << endl;
		cout << "Please Enter Your User Code : ";
		cin >> userCode;
		cout << endl;
		cout << "Please Enter Your Credentials : ";
		cin >> credentials;
		cout << endl;
		displayAllRecords(arraySize - 1);
		break;

	case 3:
		userType = "Tutor";
		cout << endl;
		cout << "Please Enter Your Tutor ID : ";
		cin >> userCode;
		cout << endl;
		cout << "Please Enter Your Credentials : ";
		cin >> credentials;
		cout << endl;
		checkTutor(userCode, credentials);
		break;

	default:
		cout << "User Account Invalid ! Please Double Check Your Credentials !!!";
		cout << endl;
	}
};

//Check Whether There Is Slots Available
void checkVacantSlot();

//Add New Tutor Record
void addTutor();

//Modify Tutor Record
void modifyTutor();

//Delete Tutor Record
void deleteTutor();

//Sort Records By Tutor ID / Hourly Rate / Overall Performance
void sortByTutorID();

void sortByHourlyRate();

void sortByOverallPerformance();

//Search Records By Tutor ID / Rating
void searchByTutorID();

void searchByRating();

//Generate Summary Report / By Location Function
void generateReport() {
	int i = 0;
	int choice = 0;
	int totalTutorsInEachLoc = 10;
	//Summary Report Variables
	int emptySlot = 0;
	int occupiedSlot = 0;
	//Location Report Variables
	int BJOcc = 0;
	int CHOcc = 0;
	int PJOcc = 0;

	cin >> choice;
	cout << endl;
	switch (choice)
	{
	case 1:
		//Loop 30 Times (ALL Records)
		while (i < 30) {
			if (!allTutors[i].tutorID.empty()) {
				occupiedSlot++;
			}
			else {
				emptySlot++;
			}
			i++;
		}
		cout << endl;
		cout << "	TOTAL NUMBER OF TUTORS" << setw(11) << " = " << occupiedSlot << endl;
		cout << "	TOTAL NUMBER OF AVAILABLE SLOT = " << emptySlot << endl;
		break;
	case 2:
		while (i < 30 && !allTutors[i].tutorID.empty()) {
			/*check if tutor id in selected index is NULL*/
			if (allTutors[i].center.branch == "Bukit Jalil") {
				BJOcc++;
			}
			if (allTutors[i].center.branch == "Cheras") {
				CHOcc++;
			}
			if (allTutors[i].center.branch == "Petaling Jaya") {
				PJOcc++;
			}
			i++;
		}
		cout << "Report By Location : " << endl << endl;
		// Location : Bukit Jalil
		cout << string(82, '=') << endl;
		cout << "|" << string(34, ' ') << "Bukit Jalil" << string(35, ' ') << "|" << endl;
		cout << string(82, '=') << endl << endl;
		cout << "	TOTAL NUMBER OF TUTORS" << setw(11) << " = " << BJOcc << endl;
		cout << "	TOTAL NUMBER OF AVAILABLE SLOT = " << totalTutorsInEachLoc - BJOcc << endl << endl;

		// Location : Cheras
		cout << string(82, '=') << endl;
		cout << "|" << string(37, ' ') << "Cheras" << string(37, ' ') << "|" << endl;
		cout << string(82, '=') << endl << endl;
		cout << "	TOTAL NUMBER OF TUTORS" << setw(11) << " = " << CHOcc << endl;
		cout << "	TOTAL NUMBER OF AVAILABLE SLOT = " << totalTutorsInEachLoc - CHOcc << endl << endl;

		// Location : Petaling Jaya
		cout << string(82, '=') << endl;
		cout << "|" << string(33, ' ') << "Petaling Jaya" << string(34, ' ') << "|" << endl;
		cout << string(82, '=') << endl << endl;
		cout << "	TOTAL NUMBER OF TUTORS" << setw(11) << " = " << PJOcc << endl;
		cout << "	TOTAL NUMBER OF AVAILABLE SLOT = " << totalTutorsInEachLoc - PJOcc << endl << endl;
		break;
	}
}

int main() {
	initializeRecords();
	displayStartMenu();
	//generateReport();
	//checkLogin();
	//displayAdminMenu();
	//displayHRMenu();
	//displayTutorMenu();
	//displayLocationMenu();
	//initialize_records();
	//int choice; int i = 0; int arraySize = 0;
	//while (!allTutors[i].tutorID.empty()) {
	//	arraySize++;
	//	i++;
	//}
	//displayAllRecords(arraySize - 1);
	//cout << "Done" << endl;

	//displayExitMenu();

	return 0;
}