#include <iostream>
#include <string>
#include <iomanip>
#include "Menu.h"
#include "Struct.h"
#include "conio.h"
#include <regex>

#undef max
using namespace std;
int arraySize = 0;
void checkLogin();
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
//To change user input to "*" character
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

//Tutor ID generator
string tutorIDGenerator(Tutor allTutor[], int arraySize, string branch)
{
	string tutorID = "";
	string newTID;
	string prefix;

	int number = 0;
	Tutor maxTID = allTutor[0];
	int i = 0;
	for (int i = 0; i < arraySize; i++)
	{
		if (allTutors[i].center.branch == branch) {
			if (allTutor[i].getTutorID() > maxTID.getTutorID()) {
				maxTID = allTutor[i];
			}
		}
	}
	tutorID = maxTID.getTutorID();

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
		do {
			cout << "Invalid Tutor ID & Credentials !!! Please Double Check Your Credentials !!!";
			cout << endl;
			cout << "Please Enter Your User Code : ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> userCode;
			cout << endl;
			cout << "Please Enter Your Credentials : ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			credentials = takePasswdFromUser();
			checkTutor(userCode, credentials);
			return branch;
		} while (found == 0);
	}
	else
	{
		cout << "Login Successful !!";
		cout << endl;
		return branch;
	}
};

//Check Whether There Is slots Available
int checkVacantSlot(string branchname)
{
	int countBJ = 0, countCH = 0, countPJ = 0, totalslot = 10;

	// to count how many branches are there in the system
	for (int i = 0; i < arraySize; i++)
	{
		if (!allTutors[i].tutorID.empty())
		{
			if (allTutors[i].center.branch == "Bukit Jalil")
			{
				countBJ++;
			}
			else if (allTutors[i].center.branch == "Cheras")
			{
				countCH++;
			}
			else
			{
				countPJ++;
			}
		}
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
};

//enter new details
void enterDetails(int i, string ID) {
	int choice = 0;
	bool input = true;
	cout << endl;
	cout << string(82, '=') << endl;
	cout << "|" << string(30, ' ') << "Tutor Details Form" << string(32, ' ') << "|" << endl;
	cout << string(82, '=') << endl;
	cout << "	Generated Tutor ID                  : " << ID << endl; // print generated tutor ID

	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	// First Name
	cout << "	Please enter The First Name of Tutor: ";
	getline(cin, allTutors[i].firstName);
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	// Last Name
	cout << "	Please enter The Last Name of Tutor : ";
	getline(cin, allTutors[i].lastName);
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	// Date Joined
	cout << "	Please enter Tutor Date Joined [Format (DD/MM/YYYY)] : ";
	cin >> allTutors[i].dateJoined;
	while (cin.fail() || allTutors[i].dateJoined.size() != 10)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << endl << "Please provide a valid date! " << endl;
		cout << "	Please enter Tutor Date Joined [Format (DD/MM/YYYY)] : ";
		cin >> allTutors[i].dateJoined;
	}
	cout << endl;

	// Hourly Pay Rate
	cout << "	Please enter Hourly Pay Rate (40-80): ";
	cin >> allTutors[i].hourlyRate;
	while (cin.fail() || allTutors[i].hourlyRate < 40 || allTutors[i].hourlyRate > 80) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << endl << "	Please give a valid hourly rate! " << endl;
		cout << "	Please enter Hourly Pay Rate (40-80): ";
		cin >> allTutors[i].hourlyRate;
	}
	cout << endl;

	// Tuition Center
	cout << "	Please select Tuition Center        : " << endl;
	cout << "	1. Cheras " << endl;
	cout << "	2. Bukit Jalil" << endl;
	cout << "	3. Petaling Jaya" << endl;
	cout << "	Please select Tuition Center        : ";
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
		cout << "	Invalid Input, Please Insert Valid Choice (1-3)!" << endl << "\t";
		break;
	}

	while (cin.fail() || choice < 1 || choice > 3)
	{
		cout << endl << "	Please enter a valid selection! " << endl << endl;
		cout << "	Please select Tuition Center        : " << endl;
		cout << "	1. Cheras " << endl;
		cout << "	2. Bukit Jalil" << endl;
		cout << "	3. Petaling Jaya" << endl;
		cout << "	Please select Tuition Center        : ";
		cin >> choice;

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
			cout << "	Invalid Input, Please Insert Valid Choice (1-3)!" << endl << "\t";
			input = false;
			break;
		}
	};

	cout << endl;

	// Subject Taught

	cout << "	Please select Subject Taught        : " << endl;
	cout << "	1. Chinese " << endl;
	cout << "	2. Malay" << endl;
	cout << "	3. English" << endl;
	cout << "	4. Mathematics" << endl;
	cout << "	5. Science" << endl;
	cout << "	Please insert choice(1 - 5)         : ";
	cin >> choice;

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
		cout << "	Invalid Input, Please Insert Valid Choice (1-5)!" << endl << "\t";
		input = false;
		break;
	}

	while (cin.fail() || choice < 1 || choice > 5) {
		cout << endl << "	Please enter a valid selection! " << endl << endl;
		cout << "	Please select Subject Taught        : " << endl;
		cout << "	1. Chinese " << endl;
		cout << "	2. Malay" << endl;
		cout << "	3. English" << endl;
		cout << "	4. Mathematics" << endl;
		cout << "	5. Science" << endl;
		cout << "	Please insert choice(1 - 5)         : ";

		cin >> choice;

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
			cout << "	Invalid Input, Please Insert Valid Choice (1-5)!" << endl << "\t";
			input = false;
			break;
		}
	}

	cout << endl;

	// Phone Number
	cout << "	Please Enter Phone Number           : ";
	cin >> allTutors[i].phoneNumber;
	while (cin.fail() || allTutors[i].phoneNumber.size() >= 13) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << endl << "Please give a valid phone number! " << endl;
		cout << "	Please Enter Phone Number           : ";
		cin >> allTutors[i].phoneNumber;
	}

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << endl;

	// Tutor Address
	cout << "	Please enter Tutor Address          : ";
	getline(cin, allTutors[i].address);
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "	Working on it!!" << endl;
	Sleep(2000);

	arraySize++;
	system("CLS");
}

//Add New Tutor Record (HR)
void addTutor(string branch) {
	string ID = "";
	int slots = 0;
	slots = checkVacantSlot(branch);
	cout << endl << endl;
	if (slots <= 0)
		cout << "Cannot add new tutor anymore! The slots for " << branch << "  are full now!";
	cout << "Current slots in " << branch << ": " << slots << endl;
	ID = tutorIDGenerator(allTutors, arraySize, branch);

	/*check whether the first element in array is empty*/
	if (allTutors[0].tutorID.empty()) {
		allTutors[0].tutorID = ID;
		enterDetails(0, ID); //call enter details with the first index passed to the enter details function
	}
	else {
		ID = tutorIDGenerator(allTutors, arraySize, branch);
		/*find the index of the empty element*/
		for (int index = 0; index < 30; index++) {
			/*check whether the element in index is empty*/
			if (!allTutors[index].tutorID.empty()) {
				continue;
			}
			else {
				allTutors[index].tutorID = ID;
				enterDetails(index, ID);
				break;
			}
		}
	}
};

//Add New Tutor Record (Admin)
void addTutor() {
	string ID = "";
	int choice = 0;
	string branch = "";
	int slots = 0;
	cout << endl;
	cout << "Please Choose The Branch That You Would Like To Add" << endl;
	cout << "1. Bukit Jalil \t 2. Petaling Jaya \t 3. Cheras" << endl;
	cout << "Branch: ";
	cin >> choice;
	switch (choice)
	{
	case 1:
		branch = "Bukit Jalil";
		break;
	case 2:
		branch = "Petaling Jaya";
		break;
	case 3:
		branch = "Cheras";
		break;
	default:
		cout << "Invalid Choice !!! Please Try Again!";
		break;
	}
	slots = checkVacantSlot(branch);
	cout << endl << endl;
	if (slots <= 0)
		cout << "Cannot add new tutor anymore! The slots for " << branch << "  are full now!";
	cout << "Current slots in " << branch << ": " << slots << endl;

	ID = tutorIDGenerator(allTutors, arraySize, branch);

	/*check whether the first element in array is empty*/
	if (allTutors[0].tutorID.empty()) {
		allTutors[0].tutorID = ID;
		enterDetails(0, ID); //call enter details with the first index passed to the enter details function
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
				enterDetails(index, ID);
				break;
			}
		}
	}
};

//Sort Records By Tutor ID / Hourly Rate / Overall Performance with Bubble Sort
//By ascending order
void bubbleSortTutorID(Tutor allTutor[])
{
	//Bubble sort
	int loop_j;
	Tutor key;
	//Ascending
	for (int index = 1; index < arraySize; index++)
	{
		key = allTutor[index];
		loop_j = index;

		while (loop_j > 0 && stoi(allTutor[loop_j - 1].getTutorID().substr(1)) < stoi(key.getTutorID().substr(1))) {
			allTutor[loop_j] = allTutor[loop_j - 1];
			loop_j--;
		}
		allTutor[loop_j] = key;
	}

	cout << "After bubble sort, the array result as here: " << endl;
	int i = 0;
	while (i <= arraySize) {
		//Validatation 1 : Check whether array is empty or not
		if (!allTutors[i].tutorID.empty()) {
			cout << i + 1 << " : " << allTutors[i].tutorID << " - " << allTutors[i].firstName << " " << allTutors[i].lastName << " - " <<
				allTutors[i].dateJoined << " - " << allTutors[i].dateTerminated << " - " << allTutors[i].hourlyRate << " - " <<
				allTutors[i].phoneNumber << " - " << allTutors[i].address << " - " << allTutors[i].center.centerName << " - " <<
				allTutors[i].subjectCode << " - " << allTutors[i].subjectName << " - " << allTutors[i].rating;
			cout << endl << endl;
		}
		i++;
	}
}

void bubbleSortTutorID(Tutor allTutor[], string branch)
{
	//Bubble sort
	int loop_j;
	Tutor key;
	//Ascending
	for (int index = 1; index < arraySize; index++)
	{
		key = allTutor[index];
		loop_j = index;

		while (loop_j > 0 && stoi(allTutor[loop_j - 1].getTutorID().substr(1)) < stoi(key.getTutorID().substr(1))) {
			allTutor[loop_j] = allTutor[loop_j - 1];
			loop_j--;
		}
		allTutor[loop_j] = key;
	}

	cout << "After bubble sort, the array result as here: " << endl;
	int i = 0;
	while (i <= arraySize) {
		//Validatation 1 : Check whether array is empty or not
		if (!allTutors[i].tutorID.empty() && allTutors[i].center.branch == branch) {
			cout << i + 1 << " : " << allTutors[i].tutorID << " - " << allTutors[i].firstName << " " << allTutors[i].lastName << " - " <<
				allTutors[i].dateJoined << " - " << allTutors[i].dateTerminated << " - " << allTutors[i].hourlyRate << " - " <<
				allTutors[i].phoneNumber << " - " << allTutors[i].address << " - " << allTutors[i].center.centerName << " - " <<
				allTutors[i].subjectCode << " - " << allTutors[i].subjectName << " - " << allTutors[i].rating;
			cout << endl << endl;
		}
		i++;
	}
}

void bubbleSortHourlyRate(Tutor allTutor[], int style)
{
	//Bubble sort
	int loop_j;
	Tutor key;
	//Style defines the way of sorting: 1 for ascending; 2 for descending
	if (style == 1)
	{
		//Ascending
		for (int index = 1; index < arraySize; index++)
		{
			key = allTutor[index];
			loop_j = index;

			while (loop_j > 0 && allTutor[loop_j - 1].getHourlyRate() > key.getHourlyRate()) {
				allTutor[loop_j] = allTutor[loop_j - 1];
				loop_j--;
			}
			allTutor[loop_j] = key;
		}
	}
	else
	{
		//Descending
		for (int index = 1; index < arraySize; index++)
		{
			key = allTutor[index];
			loop_j = index;

			while (loop_j > 0 && allTutor[loop_j - 1].getHourlyRate() < key.getHourlyRate()) {
				allTutor[loop_j] = allTutor[loop_j - 1];
				loop_j--;
			}
			allTutor[loop_j] = key;
		}
	}

	cout << "After bubble sort, the array result as here: " << endl;
	int i = 0;
	while (i <= arraySize) {
		//Validatation 1 : Check whether array is empty or not
		if (!allTutors[i].tutorID.empty()) {
			cout << i + 1 << " : " << allTutors[i].tutorID << " - " << allTutors[i].firstName << " " << allTutors[i].lastName << " - " <<
				allTutors[i].dateJoined << " - " << allTutors[i].dateTerminated << " - " << allTutors[i].hourlyRate << " - " <<
				allTutors[i].phoneNumber << " - " << allTutors[i].address << " - " << allTutors[i].center.centerName << " - " <<
				allTutors[i].subjectCode << " - " << allTutors[i].subjectName << " - " << allTutors[i].rating;
			cout << endl << endl;
		}
		i++;
	}
}

void bubbleSortOverallPerformance(Tutor allTutor[], int style)
{
	int loop_j;
	Tutor key;

	//Style defines the way of sorting: 1 for ascending; 2 for descending
	if (style == 1)
	{
		//Ascending
		for (int index = 1; index < arraySize; index++)
		{
			key = allTutor[index];
			loop_j = index;

			while (loop_j > 0 && allTutor[loop_j - 1].getRating() > key.getRating()) {
				allTutor[loop_j] = allTutor[loop_j - 1];
				loop_j--;
			}
			allTutor[loop_j] = key;
		}
	}
	else
	{
		//Descending
		for (int index = 1; index < arraySize; index++)
		{
			key = allTutor[index];
			loop_j = index;

			while (loop_j > 0 && allTutor[loop_j - 1].getRating() < key.getRating()) {
				allTutor[loop_j] = allTutor[loop_j - 1];
				loop_j--;
			}
			allTutor[loop_j] = key;
		}
	}

	cout << "After bubble sort, the array result as here: " << endl;
	int i = 0;
	while (i <= arraySize) {
		//Validatation 1 : Check whether array is empty or not
		if (!allTutors[i].tutorID.empty()) {
			cout << i + 1 << " : " << allTutors[i].tutorID << " - " << allTutors[i].firstName << " " << allTutors[i].lastName << " - " <<
				allTutors[i].dateJoined << " - " << allTutors[i].dateTerminated << " - " << allTutors[i].hourlyRate << " - " <<
				allTutors[i].phoneNumber << " - " << allTutors[i].address << " - " << allTutors[i].center.centerName << " - " <<
				allTutors[i].subjectCode << " - " << allTutors[i].subjectName << " - " << allTutors[i].rating;
			cout << endl << endl;
		}
		i++;
	}
}

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
int searchByTutorIDBinary(int initial, int totalArraySize, string tutID) {
	//Binary Search
	if (totalArraySize >= initial) {
		int mid = initial + (totalArraySize - initial) / 2;
		//if the tutor id in the middle index then return
		if (allTutors[mid].tutorID == tutID)
			return mid;
		//if the tutor id in the middle index is greater than the given tutor
		else if (allTutors[mid].tutorID > tutID)
			return searchByTutorIDBinary(initial, mid - 1, tutID); //put middle - 1 as the int r in the binary search
		else
			return searchByTutorIDBinary(mid + 1, totalArraySize, tutID); //put middle + 1 as the int l in the binary search
	}
	return -1;
};

//Search Rating
int searchByRatingBinary(int initial, int totalArraySize, string rating) {
	//Binary Search
	if (totalArraySize >= initial) {
		int mid = initial + (totalArraySize - initial) / 2;
		//if the tutor id in the middle index then return
		if ((to_string(allTutors[mid].rating)).find(rating) != string::npos)
			return mid;
		//if the tutor id in the middle index is greater than the given tutor
		else if (to_string(allTutors[mid].rating) > rating)
			//put middle - 1 as the int r in the binary search
			return searchByRatingBinary(initial, mid - 1, rating);
		else
			//put middle + 1 as the int l in the binary search
			return searchByRatingBinary(mid + 1, totalArraySize, rating);
	}
	return -1;
};

//Search Rating - Linear Search (Return multiple records)
void searchByRatingLinear(string rating)
{
	int i = 0;
	boolean flag = false;

	if (arraySize > 0 && (to_string(allTutors[i].rating)).find(rating) != string::npos)
	{
		while ((to_string(allTutors[i].rating)).find(rating) != string::npos)
		{
			cout << "Record No." << i + 1 << " : " << allTutors[i].tutorID << " - " << allTutors[i].firstName << " " <<
				allTutors[i].lastName << " - " << allTutors[i].dateJoined << " - " << allTutors[i].dateTerminated << " - " <<
				allTutors[i].hourlyRate << " - " << allTutors[i].phoneNumber << " - " << allTutors[i].address << " - " <<
				allTutors[i].center.centerName << " - " << allTutors[i].subjectCode << " - " << allTutors[i].subjectName << " - " <<
				allTutors[i].rating;
			cout << endl;
			i++;
		}

		flag = true;
		cout << "Searching is done here!" << endl;
	}
	else {
		cout << "Search is not found!!" << endl;
	}
}

//Search Rating - Linear Search (Return multiple records)
void searchByRatingLinear(string rating, string branch)
{
	for (int i = 0; i <= arraySize; i++) {
		if ((to_string(allTutors[i].rating)).find(rating) != string::npos && allTutors[i].center.branch == branch)
		{
			cout << "Record No." << i + 1 << " : " << allTutors[i].tutorID << " - " << allTutors[i].firstName << " " <<
				allTutors[i].lastName << " - " << allTutors[i].dateJoined << " - " << allTutors[i].dateTerminated << " - " <<
				allTutors[i].hourlyRate << " - " << allTutors[i].phoneNumber << " - " << allTutors[i].address << " - " <<
				allTutors[i].center.centerName << " - " << allTutors[i].subjectCode << " - " << allTutors[i].subjectName << " - " <<
				allTutors[i].rating;
			cout << endl;
		}
	}
	cout << "Searching is done here! NOTE: There are no relevant tutor records shown if they could not be found." << endl;
}

//Search TutorID - Linear Search (Return multiple records)
void searchByTutorIDLinear(string ID)
{
	for (int i = 0; i <= arraySize; i++) {
		if (allTutors[i].tutorID.find(ID) != string::npos)
		{
			cout << "Record No." << i + 1 << " : " << allTutors[i].tutorID << " - " << allTutors[i].firstName << " " <<
				allTutors[i].lastName << " - " << allTutors[i].dateJoined << " - " << allTutors[i].dateTerminated << " - " <<
				allTutors[i].hourlyRate << " - " << allTutors[i].phoneNumber << " - " << allTutors[i].address << " - " <<
				allTutors[i].center.centerName << " - " << allTutors[i].subjectCode << " - " << allTutors[i].subjectName << " - " <<
				allTutors[i].rating;
			cout << endl;
		}
	}
	cout << "Searching is done here! NOTE: There are no relevant tutor records shown if they could not be found." << endl;
};

void searchByTutorIDLinear(string ID, string branch)
{
	for (int i = 0; i <= arraySize; i++) {
		if (allTutors[i].tutorID.find(ID) != string::npos && allTutors[i].center.branch == branch)
		{
			cout << "Record No." << i + 1 << " : " << allTutors[i].tutorID << " - " << allTutors[i].firstName << " " <<
				allTutors[i].lastName << " - " << allTutors[i].dateJoined << " - " << allTutors[i].dateTerminated << " - " <<
				allTutors[i].hourlyRate << " - " << allTutors[i].phoneNumber << " - " << allTutors[i].address << " - " <<
				allTutors[i].center.centerName << " - " << allTutors[i].subjectCode << " - " << allTutors[i].subjectName << " - " <<
				allTutors[i].rating;
			cout << endl;
		}
	}
	cout << "Searching is done here! NOTE: There are no relevant tutor records shown if they could not be found." << endl;
};

//Modify Tutor Record
void modifyTutor(int i, string ID, int choice)
{
	int totalSize = arraySize;
	string address;
	string phoneNumber;
	string lastName;
	string firstName;
	string tutorID;
	string dateJoined;
	string dateTerminated;
	double hourlyRate;
	string credential;
	bool input = true;
	int rating;
	char decision;

	if (allTutors[i].tutorID == ID)
	{
		switch (choice)
		{
		case 1:
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please Enter New Name: " << endl;
			cout << "First Name: ";
			getline(cin, firstName);
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Last Name: ";
			getline(cin, lastName);
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			allTutors[i].setFirstName(firstName);

			allTutors[i].setLastName(lastName);
			//allTutors[result].lastName = lastName;
			bubbleSortTutorID(allTutors);
			break;

		case 2:
			cout << "Please enter Hourly Pay Rate (40-80): ";
			cin >> hourlyRate;
			/*check whether given hourly pay rate input is valid 40 to 80*/
			while (hourlyRate < 40 || hourlyRate > 80) {
				cout << "Please Try Again With Valid Input: ";
			}

			//Check how to change string to double
			allTutors[i].setHourlyRate(hourlyRate);
			cout << "Hourly Pay Rate Had Successfully Changed" << endl;

			break;

		case 3:
			cout << "Please Insert New Phone Number: ";
			cin >> phoneNumber;
			allTutors[i].phoneNumber = phoneNumber;
			cout << "Phone Number Had Successfully Changed" << endl;
			break;

		case 4:
			cout << "Please Enter New Address: ";
			getline(cin, address);
			allTutors[i].address = address;
			cout << "Address Had Successfully Changed" << endl;
			break;

		case 5:
			cout << "Please Enter New Credentials: ";
			cin >> credential;
			allTutors[i].credential = credential;
			cout << "Credential Had Successfully Changed" << endl;

			break;

		case 6:
			cout << "Please select Tuition Center        : " << endl;
			cout << "1. Cheras " << endl;
			cout << "2. Bukit Jalil" << endl;
			cout << "3. Petaling Jaya" << endl;

			cout << "Please insert choice (1-3) : ";
			cin >> choice;

			/*check whether given choice input is valid 1 to 3*/

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
				break;
			}

		case 7:
			cout << "Please select Subject Taught : " << endl;
			cout << "1. Chinese " << endl;
			cout << "2. Malay" << endl;
			cout << "3. English" << endl;
			cout << "4. Mathematics" << endl;
			cout << "5. Science" << endl;
			cout << "Please insert choice(1 - 5) : ";
			do {
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
					allTutors[i].subjectCode = "ENG";
					allTutors[i].subjectName = "English";
					break;
				case 4:
					allTutors[i].subjectCode = "MTH";
					allTutors[i].subjectName = "Mathematics";
					break;
				case 5:
					allTutors[i].subjectCode = "SCI";
					allTutors[i].subjectName = "Science";
					break;
				default:
					cout << "Invalid Input, Please Insert Valid Choice (1-5)!" << endl << "\t";
					input = false;
					break;
				}
			} while (!input);
			break;
		case 8:
			cout << "	Please enter Tutor Rating     (1-5) : ";
			cin >> rating;
			/*check whether given choice input is valid 1 to 5*/
			while (rating < 1 || rating >5) {
				cout << "Invalid Input, Please Insert Valid Choice (1-5)!: ";
			}
			allTutors[i].rating = rating;
			cout << "Rating Had Successfully Changed" << endl;

			break;
		default:
			cout << "Invalid Choice !!! Please Try Again" << endl;
			break;
		}
	}
}

//Function to finsh today date
string todayDate()
{
	time_t t = time(NULL);
	struct tm now;
	localtime_s(&now, &t);
	string today = (to_string(0)).append(to_string(now.tm_mday)).append("/").append(to_string(0)).append((to_string(now.tm_mon + 1))).append("/").append(to_string((now.tm_year) + 1900));
	return today;
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

//Delete Tutor Record (6 months from current date)
void deleteTutor(string TutorID)
{
	int i = 0;
	while (!allTutors[i].tutorID.empty())

	{
		if (allTutors[i].getTutorID() == TutorID) {
			int diff = getDateDifference(allTutors[i].getDateTerminated(), todayDate());
			if (diff < 180)
			{
				cout << "Cannot delete this tutor as the termination duration from today has not reach at least 6 months!";
				cout << endl;
			}
			else
			{
				int choice = 0;
				cout << "Are you sure to delete this tutor? 1- YES, Others- NO" << endl;
				cin >> choice;
				if (choice == 1)
				{
					//list is empty
					if (allTutors[i].tutorID.empty())
					{
						cout << "Empty list!" << endl;
						return;
					}
					else if (allTutors[i].getTutorID() == TutorID)
					{
						cout << "Records to be deleted:-";
						cout << allTutors[i].getTutorID() << " - " << allTutors[i].getFirstName() << " - " << allTutors[i].getLastName() << " - " << allTutors[i].getDateJoined() << " - "
							<< allTutors[i].getDateTerminated() << " - " << allTutors[i].getHourlyRate() << " - " << allTutors[i].getphoneNumber() << " - " << allTutors[i].getAddress() << " - "
							<< allTutors[i].getCredential() << " - " << allTutors[i].getBranch() << " - " << allTutors[i].getSubjectCode() << " - " << allTutors[i].getSubjectName() << " - "
							<< allTutors[i].getRating() << endl << endl;
						cout << TutorID << " is deleted from the list!" << endl;

						if (allTutors[i].tutorID == TutorID) {
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

							arraySize--;
							return;
						}
					}
					else
					{
						cout << "Tutor ID " << TutorID << " is not found in the list!" << endl;
					}
				}
			}
		}
		i++;
	}
}

//View Tutor Record
void viewTutor()
{
	int choice;
	int result;
	string rating;
	string searchTutor = "";

	cout << endl;
	cout << " Search by?" << endl;
	cout << "1 - TutorID, 2 - Ratings" << endl;
	cout << "Choice: ";
	cin >> choice;
	if (choice == 1)
	{
		do
		{
			cout << "Which tutor like to search by ID?" << endl;
			cout << "Tutor ID: ";
			cin >> searchTutor;
			searchByTutorIDLinear(searchTutor);

			cout << endl;
			cout << "Search tutor again by ID? 1 = YES, Others = NO:" << endl;
			cout << "Choice: ";
			cin >> choice;
		} while (choice == 1);

		cout << "Want to search by ratings instead? 1 = YES, Others = NO:" << endl;
		cout << "Choice: ";
		cin >> choice;
		if (choice == 1)
		{
			do
			{
				cout << "Which tutor would you like to search by rating?" << endl;
				cout << "Rating: ";
				cin >> rating;

				searchByRatingLinear(rating);

				cout << endl;
				cout << "Search tutor again by rating? 1 = YES, Others = NO:" << endl;
				cout << "Choice: ";
				cin >> choice;
			} while (choice == 1);
		}
	}
	else if (choice == 2)
	{
		do
		{
			cout << "Which tutor would you like to search by rating?" << endl;
			cout << "Rating: ";
			cin >> rating;

			searchByRatingLinear(rating);

			cout << endl;
			cout << "Search tutor again by rating? 1 = YES, Others = NO:" << endl;
			cout << "Choice: ";
			cin >> choice;
		} while (choice == 1);

		cout << "Want to search by TutorID instead? 1 = YES, Others = NO:" << endl;
		cout << "Choice: ";
		if (choice == 1)
		{
			do
			{
				cout << "Which tutor like to search by ID?" << endl;
				cout << "Tutor ID: ";
				cin >> searchTutor;
				searchByTutorIDLinear(searchTutor);

				cout << endl;
				cout << "Search tutor again by ID? 1 = YES, Others = NO:" << endl;
				cout << "Choice: ";
				cin >> choice;
			} while (choice == 1);
		}
	}
};

void viewTutor(string branch)
{
	int choice;
	int result;
	string rating;
	string searchTutor = "";

	cout << " Search by?" << endl;
	cout << "1 - TutorID, 2 - Ratings" << endl;
	cout << "Choice: ";
	cin >> choice;
	if (choice == 1)
	{
		for (int i = 0; i <= arraySize; i++) {
			if (allTutors[i].center.branch == branch) {
				do
				{
					cout << "Which tutor like to search by ID?" << endl;
					cout << "Tutor ID: ";
					cin >> searchTutor;
					searchByTutorIDLinear(searchTutor, branch);

					cout << endl;
					cout << "Search tutor again by ID? 1 = YES, Others = NO:" << endl;
					cout << "Choice: ";
					cin >> choice;
				} while (choice == 1);

				cout << "Want to search by ratings instead? 1 = YES, Others = NO:" << endl;
				cout << "Choice: ";
				cin >> choice;
				if (choice == 1)
				{
					do
					{
						cout << "Which tutor would you like to search by rating?" << endl;
						cout << "Rating: ";
						cin >> rating;

						searchByRatingLinear(rating, branch);

						cout << endl;
						cout << "Search tutor again by rating? 1 = YES, Others = NO:" << endl;
						cout << "Choice: ";
						cin >> choice;
					} while (choice == 1);
				}
			}
		}
	}
	else if (choice == 2)
	{
		do
		{
			cout << "Which tutor would you like to search by rating?" << endl;
			cout << "Rating: ";
			cin >> rating;

			searchByRatingLinear(rating, branch);

			cout << endl;
			cout << "Search tutor again by rating? 1 = YES, Others = NO:" << endl;
			cout << "Choice: ";
			cin >> choice;
		} while (choice == 1);

		cout << "Want to search by TutorID instead? 1 = YES, Others = NO:" << endl;
		cout << "Choice: ";
		if (choice == 1)
		{
			do
			{
				cout << "Which tutor like to search by ID?" << endl;
				cout << "Tutor ID: ";
				cin >> searchTutor;
				searchByTutorIDLinear(searchTutor, branch);

				cout << endl;
				cout << "Search tutor again by ID? 1 = YES, Others = NO:" << endl;
				cout << "Choice: ";
				cin >> choice;
			} while (choice == 1);
		}
	}
};

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
	displayReportTypeMenu();
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

//Validate HR and Admin's Login Credentials
void checkAccess(string userCode, string credentials)
{
	bool found = 0;
	bool input = true;
	bool sort = true;
	bool userCredentials = true;
	int i = 0, opt = 0;
	int exit = 0;
	int style;
	int rlyExit = 0;
	string userType;
	string branch;
	string TID;

	//Convert The First and Second Letter Of The User Code To UpperCase
	//To ensure that the letters are in uppercase
	userCode[0] = toupper(userCode[0]);
	userCode[1] = toupper(userCode[1]);

	//Compare HR and Admin User Code & Credentials With The System's Access Records
	while (!allAccess[i].userCode.empty()) {
		if (userCode == allAccess[i].userCode && credentials == allAccess[i].credentials)
		{
			found = 1;
			userType = allAccess[i].getUserType();
			branch = allAccess[i].getBranch();
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

		//Clear Screen
		system("CLS");
		do {
			displayHRMenu();
			cin >> choice;
			switch (choice)
			{
			case 1:
				addTutor();
				bubbleSortTutorID(allTutors);
				break;
			case 2:
				do {
					displaySortMenu();
					cin >> choice;
					switch (choice)
					{
					case 1:
						cout << "Tutor Details sorted by Hourly Rate: " << endl;
						cout << "Press 1 for Ascending 2 for Descending" << endl;
						cin >> style;
						bubbleSortHourlyRate(allTutors, style);
						cout << endl;
						break;
					case 2:
						cout << "Tutor Details sorted by Overall Performance: " << endl;
						cout << "Press 1 for Ascending 2 for Descending" << endl;
						cin >> style;
						bubbleSortOverallPerformance(allTutors, style);
						cout << endl;
						break;
					case 3:
						cout << "Tutor Details sorted by Tutor ID: " << endl;
						bubbleSortTutorID(allTutors);
						cout << endl;
						break;
					default:
						cout << "Invalid selection" << endl;
						sort = false;
						break;
					}
				} while (!sort);
				viewTutor();
				break;
			case 3:
				do
				{
					bubbleSortTutorID(allTutors);
					cout << "Please Enter Tutor ID To Be Modified : ";
					cin >> TID;

					int index = searchByTutorID(arraySize, TID);
					cout << endl;
					do
					{
						displayModifyTutorMenu();
						cin >> choice;
						modifyTutor(index, TID, choice);
						cout << "Do you want to edit again? 1 = YES, 0 = NO: ";
						cin >> choice;
					} while (choice == 1);
					cout << " Do you want to edit another tutor? 1 = YES, 0 = NO: ";
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
					int result = searchByTutorID(arraySize, keyword);
					cin.clear();	//remove input operation
					cin.ignore(numeric_limits<streamsize>::max(), '\n');	//remove content
					while (result == -1)
					{
						cout << "Tutor ID " << keyword << " is not found in the list!" << endl;

						cout << "Which tutor do you want to delete? Please provide his/ her Tutor ID: ";
						cin >> keyword;
						cout << endl;
						result = searchByTutorID(arraySize, keyword);
					}

					deleteTutor(keyword);

					//after delete, display list again
					displayAllRecords(arraySize);
					cout << endl << "The current amount of the size is " << arraySize << endl;

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
					//exit(0);
				}
				break;
			default:
				cout << "Invalid selection, Please Try Again" << endl;
				input = false;
				break;
			}
		} while (!input);
	}
	else if (found == 1 && userType == "Admin")
	{
		int choice = 0;

		system("CLS");
		cout << endl << "Login Successful !!" << endl;
		cout << "Welcome " + userCode << endl << endl;

		do {
			displayAdminMenu();
			cin >> choice;
			switch (choice)
			{
			case 1:
				addTutor(branch);
				bubbleSortTutorID(allTutors);
				cout << endl;
				input = false;
				break;
			case 2:
				bubbleSortTutorID(allTutors, branch);
				viewTutor(branch);
				cout << endl;
				input = false;
				break;
			case 3:
				rlyExit = displayExitMenu();
				if (rlyExit == 1)
				{
					checkLogin();

				}
				else
				{
					//exit(0);
				}
				break;
			default:
				cout << "Invalid selection, Please Try Again" << endl;
				input = false;
				break;
			}
		} while (!input);
	}
	else
	{
		cout << "Invalid User Code & Credentials !!! Please Double Check Your Credentials !!!" << endl << endl;
		cout << "Please Enter Your User Code : ";
		cin >> userCode;
		cout << endl;
		cout << "Please Enter Your Credentials : ";
		credentials = takePasswdFromUser();
		checkAccess(userCode, credentials);
	}
};

void checkBranch(string branch, string userCode)
{
	int choice;
	string tutorID = "";
	string name = "";
	string dateJoined = "";
	string phoneNumber = "";
	string address = "";
	string subject = "";
	string credential = "";
	string branch1 = "";
	string searchTutor = "";
	int rating = 0, opt = 0, i = 0, rpt = 0, rlyExit = 0;
	//do {
	displayTutorMenu();
	cin >> choice;
	switch (choice)
	{
	case 1:
		//View Tutor's Personal Profile
		for (int i = 0; i < arraySize; i++)
		{
			if (allTutors[i].tutorID == userCode)
			{
				tutorID = userCode;
				name = allTutors[i].firstName + " " + allTutors[i].lastName;
				dateJoined = allTutors[i].dateJoined;
				phoneNumber = allTutors[i].phoneNumber;
				address = allTutors[i].address;
				credential = allTutors[i].credential;
				subject = allTutors[i].subjectCode + allTutors[i].subjectName;
				branch = allTutors[i].center.branch;
			}
		}
		cout << string(82, '=') << endl;
		cout << "|" << string(30, ' ') << "Personal Profile" << string(30, ' ') << "|" << endl;
		cout << string(82, '=') << endl;
		cout << string(1, ' ') << "Tutor ID: " << tutorID << endl;
		cout << string(1, ' ') << "Name: " << name << endl;
		cout << string(1, ' ') << "Date Joined: " << dateJoined << endl;
		cout << string(1, ' ') << "Phone Number: " << phoneNumber << endl;
		cout << string(1, ' ') << "Address: " << address << endl;
		cout << string(1, ' ') << "Credential: " << credential << endl;
		cout << string(1, ' ') << "Subject: " << subject << endl;

		cout << string(82, '=') << endl;
		cout << "Directing User Back To Menu..........";
		cout << endl;
		system("CLS");
		checkBranch(branch1, userCode);
		break;
	case 2:
		//Modify Personal Info
		while (!allTutors[i].tutorID.empty()) {
			if (userCode == allTutors[i].tutorID)
			{
				do {
					displayModifyPersonalInfoMenu();
					int option;
					cin >> option;
					switch (option)
					{
					case 1:
						cout << "Enter New First Name: ";
						cin >> allTutors[i].firstName;
						cout << endl;
						cout << "Enter New Last Name: ";
						cin >> allTutors[i].lastName;
						cout << endl;
						while (cin.fail())
						{
							cin.clear();	//remove input operation
							cin.ignore(numeric_limits<streamsize>::max(), '\n');	//remove content
							cout << endl << "Please give a valid name! " << endl;
							cout << "Enter New First Name: ";
							cin >> allTutors[i].firstName;
							cout << endl;
							cout << "Enter New Last Name: ";
							cin >> allTutors[i].lastName;
							cout << endl;
						}
						cout << "Do You Want To Edit Other Fields ?";
						cout << "Choice : ";
						cin >> rpt;

						break;

					case 2:
						cout << "Enter New Phone Number: ";
						cin >> allTutors[i].phoneNumber;

						while (cin.fail() || allTutors[i].phoneNumber.size() <= 10)
						{
							cin.clear();	//remove input operation
							cin.ignore(numeric_limits<streamsize>::max(), '\n');	//remove content
							cout << endl << "Please give a valid phone number! " << endl;
							cout << "Enter New Phone Number: ";
							cin >> allTutors[i].phoneNumber;
						}
						cout << "Do You Want To Edit Other Fields ?";
						cout << "Choice : ";
						cin >> rpt;

						break;
					case 3:
						cout << "Enter New Address: ";
						cin >> allTutors[i].address;
						while (cin.fail())
						{
							cin.clear();	//remove input operation
							cin.ignore(numeric_limits<streamsize>::max(), '\n');	//remove content
							cout << endl << "Please give a valid house address! " << endl;
							cout << "Enter New Address: ";
							cin >> allTutors[i].address;
						}
						cout << "Do You Want To Edit Other Fields ?";
						cout << "Choice : ";
						cin >> rpt;

						break;
					case 4:
						cout << "Enter New Credential: ";
						cin >> allTutors[i].credential;
						while (cin.fail())
						{
							cin.clear();	//remove input operation
							cin.ignore(numeric_limits<streamsize>::max(), '\n');	//remove content
							cout << endl << "Please give a valid credential! " << endl;
							cout << "Enter New Credential: ";
							cin >> allTutors[i].credential;
						}
						cout << "Do You Want To Edit Other Fields ?" << endl;
						cout << "Press 1 to edit other feilds, Others to navigate back to Main Menu" << endl;
						cout << "Choice : ";
						cin >> rpt;
						break;
					}
				} while (rpt == 1);
			}
			i++;
		}
		cout << endl;
		cout << "Directing User Back To Menu..........";
		cout << endl;
		system("CLS");
		checkBranch(branch1, userCode);
		break;
	case 3:

		// View Other Tutor Profile

		while (!allTutors[i].tutorID.empty())
		{
			do
			{
				cout << "Who you would like to search? ";
				cout << endl;
				cout << "Choice :";
				cin >> searchTutor;
				if ((allTutors[i].tutorID).find(searchTutor) != string::npos && allTutors[i].center.branch == branch)
				{
					tutorID = allTutors[i].tutorID;
					name = allTutors[i].firstName + allTutors[i].lastName;
					dateJoined = allTutors[i].dateJoined;
					phoneNumber = allTutors[i].phoneNumber;
					address = allTutors[i].address;
					subject = allTutors[i].subjectCode + allTutors[i].subjectName;

					cout << "Results found!" << endl;
					cout << tutorID << "-" << name << "-" << dateJoined << "-" << phoneNumber << "-" << address << "-"
						<< subject << endl;
					cout << "Search another tutor? 1 = YES, Others = NO";
					cout << endl;
					cout << "Choice :";
					cin >> choice;
				}
			} while (choice == 1);
			i++;
		}
		cout << "Directing User Back To Menu..........";
		cout << endl;
		system("CLS");
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
			//exit(0);
		}
		break;

	default:
		cout << "Invalid Choice! Please Re-Enter Your Choice";
		cout << endl;
		break;
	}
	//	cout << "Anything else to work on this section? 1- YES, Others- NO";
	//	cout << endl;
	//	cout << "Choice : ";
	//	cin >> opt;
	//} while (opt == 1);
	//cout << "Directing User Back To Menu..........";
	//cout << endl;
	//checkBranch(branch1, userCode);
}

//Validate User Login Based On User Type
void checkLogin()
{
	int choice;
	bool input = true;
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
		cout << endl;
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
		system("CLS");
		cout << endl;
	}
};

//Rerun Program
void runprg() {
	int choice;
	int exit = 0;
	bool input = false;
	do {
		displayStartMenu();
		cin >> choice;
		switch (choice)
		{
		case 1:
			system("CLS");
			checkLogin();
			break;
		case 2:
			exit = displayExitMenu();
			if (exit == 0)
			{
				runprg();
			}
			else {
				return;
			};
			break;

		default:
			cout << "Invalid Choice !!! Please Try Again";
			input = false;
			system("CLS");
			break;
		}
	} while (!input);
}

int main() {
	int choice;
	bool input = true;
	int exit1 = 0;
	//Initialize Predefined Records
	initializeRecords();
	//Calculate Array Size
	calculateArraySize();

	switch (loginInput())
	{
	case 1:
		system("CLS");
		checkLogin();
		break;
	case 2:
		exit1 = displayExitMenu();
		if (exit1 == 1)
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