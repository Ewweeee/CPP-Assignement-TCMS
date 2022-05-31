#include <iostream>
#include <string>
#include "Menu.h"
#include "Struct.h"
#include "conio.h"

using namespace std;
int arraySize = 0;
//Function Prototype

//Calculate The Array Size
int calculateArraySize() {
	//Calculate size of tutor array
	int i = 0;
	while (!allTutors[i].tutorID.empty()) {
		arraySize++;
		i++;
	}
	return arraySize;
};

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

//Validate Tutor's Login Credentials
string checkTutor(string userCode, string credentials)
{
	boolean found = 0;
	int i = 0;
	string branch = "";

	//Convert The First Letter Of The User Code To UpperCase
	userCode[0] = toupper(userCode[0]);

	//Compare Tutor's Tutor ID & Credentials With The System's Tutor Records
	while (!allTutors[i].tutorID.empty()) {
		if (userCode == allTutors[i].getTutorID() && credentials == allTutors[i].getCredential())
		{
			branch = allTutors[i].center.getBranch();
			found = 1;
			break;
		}
		i++;
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

/*enter new details of the tutor into newnode*/
void enterDetails(int i) {
	int choice; string tutorID;
	cout << endl;
	cout << string(82, '=') << endl;
	cout << "|" << string(20, ' ') << "Tutor Details Form" << string(20, ' ') << "|" << endl;
	cout << string(82, '=') << endl;
	//cout << "	Generated Tutor ID                  : " << tutorID << endl; // print generated tutor ID
	cout << "	Please enter Tutor Name             : ";
	cin >> allTutors[i].firstName;
	cout << "	Please enter The Last Name of Tutor : ";
	cin >> allTutors[i].lastName;
	cout << "	Please enter Tutor Date Joined  Format (DD/MM/YYYY) : ";
	cin >> allTutors[i].dateJoined;
	cout << "	Please enter Hourly Pay Rate (40-80): ";
	cin >> allTutors[i].hourlyRate;

	/*check whether given hourly pay rate input is valid 40 to 80*/
	if (allTutors[i].hourlyRate < 40 || allTutors[i].hourlyRate > 80) {
		cout << "PLEASE TRY AGAIN WITH VALID INPUT   : ";
	}

	cout << "	Please select Tuition Center        : " << endl;
	cout << "	1. Cheras " << endl;
	cout << "	2. Bukit Jalil" << endl;
	cout << "	3. Petaling Jaya" << endl;

	cout << "Please insert choice (1-3) : ";
	cin >> choice;

	/*check whether given choice input is valid 1 to 5*/
	switch (choice) {
	case 1:
		allTutors[i].center.centerCode = 1001;
		allTutors[i].center.centerName = "eXcel Tuition Centre Cheras";
		allTutors[i].center.branch = "Cheras";
		break;
	case 2:
		allTutors[i].center.centerCode = 1002;
		allTutors[i].center.centerName = "eXcel Tuition Centre Bukit Jalil";
		allTutors[i].center.branch = "Bukit Jalil";
		break;
	case 3:
		allTutors[i].center.centerCode = 1003;
		allTutors[i].center.centerName = "eXcel Tuition Centre Petaling Jaya";
		allTutors[i].center.branch = "Petaling Jaya";
		break;
	default:
		cout << "Invalid Input, Please Insert Valid Choice (1-3)!" << endl << "\t";
	}
	cout << "	Please select Subject Taught : " << endl;
	cout << "	1. Chinese " << endl;
	cout << "	2. Malay" << endl;
	cout << "	3. English" << endl;
	cout << "	4. Mathematics" << endl;
	cout << "	5. Science" << endl;
	cout << "Please insert choice(1 - 5) : ";

	cin >> choice;
	/*check whether given choice input is valid 1 to 5*/
	switch (choice) {
	case 1:

		allTutors[i].subjectCode = "MLY";
		allTutors[i].subjectName = "Malay";
		break;
	case 2:
		allTutors[i].subjectCode = "CHN";
		allTutors[i].subjectName = "Chinese";
		break;
	case 3:
		allTutors[i].subjectCode = "ENF";
		allTutors[i].subjectName = "English";
		break;
	case 4:
		allTutors[i].subjectCode = "MTH";
		allTutors[i].subjectName = "Mathematics";
		break;
	case 5:
		allTutors[i].subjectCode = "SCN";
		allTutors[i].subjectName = "Science";
		break;
	default:
		cout << "Invalid Input, Please Insert Valid Choice (1-5)!" << endl << "\t";
		break;
	}
	cout << "	Please enter Phone Number           : ";
	cin >> allTutors[i].phoneNumber;
	cout << "	Please enter Tutor Address          : ";
	cin.ignore();
	getline(cin, allTutors[i].address);

	cout << "	Please enter Tutor Rating     (1-5) : ";
	cin >> allTutors[i].rating;
	/*check whether given choice input is valid 1 to 5*/
	if (allTutors[i].rating < 1 || allTutors[i].rating >5) {
		cout << "Invalid Input, Please Insert Valid Choice (1-5)!: ";
	}

	Sleep(2000); //wait 2 seconds
	cout << endl << "\t*****     Entered Details Successful     *****";
	Sleep(2000); system("CLS"); //wait 2 seconds and clear the screen
}

//Add New Tutor Record
void addTutor() {
	int ID = 1;
	/*check whether the first element in array is empty*/
	if (allTutors[0].tutorID.empty()) {
		allTutors[0].tutorID = ID;
		enterDetails(0); //call enter details with the first index passed to the enter details function
		ID = ID++;
	}
	else {
		/*find the index of the empty element*/
		for (int index = 0; index < 30; index++) {
			/*check whether the element in index is empty*/
			if (!allTutors[index].tutorID.empty()) {
				continue;
			}
			else {
				allTutors[index].tutorID = ID;
				enterDetails(index);
				ID = ID++;
				break;
			}
		}
	}
};

//Validate HR and Admin's Login Credentials
void checkAccess(string userCode, string credentials)
{
	boolean found = 0;
	int i = 0;
	string userType;

	//Convert The First Letter Of The User Code To UpperCase
	userCode[0] = toupper(userCode[0]);

	//Compare HR and Admin User Code & Credentials With The System's Access Records
	while (!allAccess[i].userCode.empty()) {
		if (userCode == allAccess[i].getUserCode() && credentials == allAccess[i].getCredentials())
		{
			found = 1;
			userType = allAccess[i].getUserType();
			break;
		}
		i++;
	}

	//Check Whether HR and Admin Credentials Are Valid
	if (found == 1 && userType == "HR")
	{
		int choice = 0;
		cout << "Login Successful !!";
		cout << "Welcome " + userCode;
		Sleep(1000);
		system("CLS");
		//displayHRMenu();
		switch (choice)
		{
		case 1:
			addTutor();
			/*case 2:
				viewTutor();
			case 3:
				modifyTutor();
			case 4:
				deleteTutor();
			case 5:
				generateReport();
			case 6:
				displayExitMenu();*/
		default:
			cout << "Invalid selection, Please Try Again" << endl;
		}
		return;
	}
	else if (found == 1 && userType == "Admin")
	{
		cout << "Login Successful !! ";
		Sleep(1000);
		system("CLS");
		displayAdminMenu();
		return;
	}
	else
	{
		cout << "Invalid User Code & Credentials !!! Please Double Check Your Credentials !!!";
		cout << endl;
	}
};

void checkBranch(string branch, string userCode)
{
	int choice;
	displayAllRecords(arraySize, branch);
	displayTutorMenu();
	cin >> choice;
	string tutorID = "";
	string name = "";
	string dateJoined = "";
	string phoneNumber = "";
	string address = "";
	string subject = "";
	int rating = 0;

	switch (choice)
	{
	case 1:
		cout << "1. View Personal Profile" << endl;

		for (int i = 0; i < arraySize; i++)
		{
			if (allTutors[i].tutorID == userCode)
			{
				tutorID = userCode;
				name = allTutors[i].firstName + allTutors[i].lastName;
				dateJoined = allTutors[i].dateJoined;
				phoneNumber = allTutors[i].phoneNumber;
				address = allTutors[i].address;
				subject = allTutors[i].subjectCode + allTutors[i].subjectName;
			}
		}
		cout << string(82, '=') << endl;
		cout << "|" << string(20, ' ') << "Personal Profile" << string(19, ' ') << "|" << endl;
		cout << string(82, '=') << endl;
		cout << string(52, ' ') << "Tutor ID: " << tutorID << endl;
		cout << string(52, ' ') << "Name: " << name;
		cout << string(82, '=') << endl;
		break;
	case 2:
		cout << "2. Modify Personal Profile" << endl;

		break;
	case 3:
		cout << "3. View Other Tutor Profile" << endl;
		break;
	case 4:
		displayExitMenu();
		break;

	default:
		cout << "Invalid Choice! Please Re-Enter Your Choice";
		cout << endl;
	}

}
//Validate User Login Based On User Type
void checkLogin()
{
	int choice;
	string userCode, userType, credentials, branch;

	displayUserType();
	/*int arraySize = 0; int i = 0;
	while (!allTutors[i].tutorID.empty()) {
		arraySize++;
		i++;
	}*/

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
		cin >> credentials;
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

//Sort Records By Tutor ID / Hourly Rate / Overall Performance
void sortByTutorID();

void sortByHourlyRate();

void sortByOverallPerformance();

//Search Records By Tutor ID / Rating
//Used for Modify & Delete Record
int searchByTutorID(int arraySize, string ID)
{	//Linear Search
	// Going through array sequencially
	for (int i = 0; i < arraySize; i++)
		if (allTutors[i].tutorID == ID)
			return i;
	return -1;
};

//Search TutorID
int searchByTutorIDBinary(Tutor allTutor[], int initial, int totalArraySize, string tutID) {
	//Binary Search
	if (totalArraySize >= initial) {
		int mid = initial + (totalArraySize - initial) / 2;
		//if the tutor id in the middle index then return
		if (allTutors[mid].tutorID == tutID)
			return mid;
		//if the tutor id in the middle index is greater than the given tutor
		else if (allTutors[mid].tutorID > tutID)
			return searchByTutorIDBinary(allTutor, initial, mid - 1, tutID); //put middle - 1 as the int r in the binary search
		else
			return searchByTutorIDBinary(allTutor, mid + 1, totalArraySize, tutID); //put middle + 1 as the int l in the binary search
	}
	return -1;
};

//Search Rating
int searchByRatingBinary(Tutor allTutor[], int initial, int totalArraySize, int rating) {
	//Binary Search
	if (totalArraySize >= initial) {
		int mid = initial + (totalArraySize - initial) / 2;
		//if the tutor id in the middle index then return
		if (allTutors[mid].rating == rating)
			return mid;
		//if the tutor id in the middle index is greater than the given tutor
		else if (allTutors[mid].rating > rating)
			//put middle - 1 as the int r in the binary search
			return searchByRatingBinary(allTutor, initial, mid - 1, rating);
		else
			//put middle + 1 as the int l in the binary search
			return searchByRatingBinary(allTutor, mid + 1, totalArraySize, rating);
	}
	return -1;
};

//Search HourlyRate
int searchByHourlyRateBinary(Tutor allTutor[], int initial, int totalArraySize, int rate) {
	//Binary Search
	if (totalArraySize >= initial) {
		int mid = initial + (totalArraySize - initial) / 2;
		//if the tutor id in the middle index then return
		if (allTutors[mid].hourlyRate == rate)
			return mid;
		//if the tutor id in the middle index is greater than the given tutor
		else if (allTutors[mid].hourlyRate > rate)
			//put middle - 1 as the int r in the binary search
			return searchByRatingBinary(allTutor, initial, mid - 1, rate);
		else
			//put middle + 1 as the int l in the binary search
			return searchByRatingBinary(allTutor, mid + 1, totalArraySize, rate);
	}
	return -1;
};
//Modify Tutor Record
void modifyTutor()
{
	int i = 0; int choice = 0;
	int totalSize = arraySize;
	string TID;
	string address;
	string phoneNumber;
	string lastName;
	string firstName;
	string tutorID;
	//string firstName;
	//string lastName;
	string dateJoined;
	string dateTerminated;
	double hourlyRate;
	string credential;

	int rating;
	char decision;
	cout << "Please Enter Tutor ID To Be Modified : ";
	cin >> TID;

	int result = searchByTutorID(totalSize, TID);
	if (result == -1)
	{
		cout << "Invalid Tutor ID. Record cannot be not found!";
	}
	else
	{
		displayModifyTutorMenu();
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Please Enter New Name: " << endl;
			cout << "First Name: ";
			getline(cin, firstName);
			cout << "Last Name: ";
			cin >> lastName;
			allTutors[result].firstName = firstName;
			allTutors[result].lastName = lastName;
			cout << "Tutor Name Had Successfully Changed" << endl;
			return;

		case 2:
			cout << "Please enter Hourly Pay Rate (40-80): ";
			cin >> hourlyRate;
			/*check whether given hourly pay rate input is valid 40 to 80*/
			while (hourlyRate < 40 || hourlyRate > 80) {
				cout << "Please Try Again With Valid Input: ";
			}
			allTutors[result].hourlyRate = hourlyRate;
			cout << "Hourly Pay Rate Had Successfully Changed" << endl;
			return;

			break;
		case 3:
			cout << "Please Insert New Phone Number: ";
			cin >> phoneNumber;
			allTutors[result].phoneNumber = phoneNumber;
			cout << "Phone Number Had Successfully Changed" << endl;
			return;
			break;
		case 4:
			cout << "Please Enter New Address: ";
			getline(cin, address);
			allTutors[result].address = address;
			cout << "Address Had Successfully Changed" << endl;
			return;
			break;

		case 5:
			cout << "Please Enter New Credentials: ";
			cin >> credential;
			allTutors[result].credential = credential;
			cout << "Credential Had Successfully Changed" << endl;
			return;

			break;

		case 6:
			cout << "	Please select Tuition Center        : " << endl;
			cout << "	1. Cheras " << endl;
			cout << "	2. Bukit Jalil" << endl;
			cout << "	3. Petaling Jaya" << endl;

			cout << "Please insert choice (1-3) : ";
			cin >> choice;

			/*check whether given choice input is valid 1 to 5*/
			switch (choice) {
			case 1:
				allTutors[result].center.centerCode = 1001;
				allTutors[result].center.centerName = "eXcel Turesulttresulton Centre Cheras";
				allTutors[result].center.branch = "Cheras";
				break;
			case 2:
				allTutors[result].center.centerCode = 1002;
				allTutors[result].center.centerName = "eXcel Turesulttresulton Centre Bukresultt Jalresultl";
				allTutors[result].center.branch = "Bukresultt Jalresultl";
				break;
			case 3:
				allTutors[result].center.centerCode = 1003;
				allTutors[result].center.centerName = "eXcel Turesulttresulton Centre Petalresultng Jaya";
				allTutors[result].center.branch = "Petalresultng Jaya";
				break;
			default:
				cout << "Invalid Input, Please Insert Valid Choice (1-3)!" << endl << "\t";
			}
			break;

		case 7:
			cout << "	Please select Subject Taught : " << endl;
			cout << "	1. Chinese " << endl;
			cout << "	2. Malay" << endl;
			cout << "	3. English" << endl;
			cout << "	4. Mathematics" << endl;
			cout << "	5. Science" << endl;
			cout << "Please insert choice(1 - 5) : ";

			cin >> choice;
			/*check whether given choice input is valid 1 to 5*/
			switch (choice) {
			case 1:
				allTutors[result].subjectCode = "MLY";
				allTutors[result].subjectName = "Malay";
				break;
			case 2:
				allTutors[result].subjectCode = "CHN";
				allTutors[result].subjectName = "Chresultnese";
				break;
			case 3:
				allTutors[result].subjectCode = "ENF";
				allTutors[result].subjectName = "Englresultsh";
				break;
			case 4:
				allTutors[result].subjectCode = "MTH";
				allTutors[result].subjectName = "Mathematresultcs";
				break;
			case 5:
				allTutors[result].subjectCode = "SCN";
				allTutors[result].subjectName = "Scresultence";
				break;
			default:
				cout << "Invalid Input, Please Insert Valid Choice (1-5)!" << endl << "\t";
				break;
			}
			break;
		case 8:
			cout << "	Please enter Tutor Rating     (1-5) : ";
			cin >> rating;
			/*check whether given choice input is valid 1 to 5*/
			while (rating < 1 || rating >5) {
				cout << "Invalid Input, Please Insert Valid Choice (1-5)!: ";
			}
			allTutors[result].rating = rating;
			cout << "Rating Had Successfully Changed" << endl;
			return;
			break;
			//addTutor();
		}
	}
};

//Delete Tutor Record
void deleteTutor()
{
	int i = 0;
	int totalSize = arraySize;
	string TID;
	string decision;
	cout << "Please Enter Tutor ID That Wanted To Be Deleted : ";
	cin >> TID;

	int result = searchByTutorID(totalSize, TID);

	if (result == -1)
	{
		cout << "Invalid Tutor ID. Record cannot be not found!";
	}
	else
	{
		cout << "Are You Sure You Want To Delete This Record ?";
		cin >> decision;

		if (decision == "Y" || decision == "Yes") {
			cout << string(15, '-') << "Performing Deletion" << string(15, '-') << endl;
			for (int i = 0; i < totalSize; i++)
				if (allTutors[i].tutorID == TID) {
					//deleting the last element
					allTutors[i].tutorID = "";
					allTutors[i].firstName = "";
					allTutors[i].lastName = "";
					allTutors[i].dateJoined = "";
					allTutors[i].dateTerminated = "";
					allTutors[i].hourlyRate = NULL;
					allTutors[i].center.centerCode = NULL;
					allTutors[i].center.centerName = "";
					allTutors[i].center.branch = "";
					allTutors[i].subjectCode = "";
					allTutors[i].subjectName = "";
					allTutors[i].phoneNumber = "";
					allTutors[i].address = "";
					allTutors[i].rating = NULL;
				}
		}
	}
};

//View Tutor Record
void viewTutor();

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
	calculateArraySize();

	//int choice = 0;
	////displayStartMenu();

	//displayHRMenu();
	////addTutor();
	////generateReport();
	checkLogin();
	////displayAdminMenu();
	////displayHRMenu();
	////displayTutorMenu();
	////displayLocationMenu();
	////initialize_records();
	////int choice; int i = 0; int arraySize = 0;
	////while (!allTutors[i].tutorID.empty()) {
	////	arraySize++;
	////	i++;
	////}
	////displayAllRecords(arraySize - 1);
	////cout << "Done" << endl;
	//cin >> choice;
	//if (choice == 1)
	//{
	//	modifyTutor();
	//}
	//int i = 0; int arraySize = 0;
	//while (!allTutors[i].tutorID.empty()) {
	//	arraySize++;
	//	i++;
	//}

	//cout << "Done" << endl;
	//displayExitMenu();
	//modifyTutor();
	//modifyTutor();
	//displayAllRecords(arraySize - 1);
	//int index;
	//if ((index = searchByRatingBinary(allTutors, 0, arraySize, 1)) >= 0)
	//	cout << "Item found at location: " << index << endl;
	//else
	//	cout << "Item is not found in the list." << endl;
	return 0;
}