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

//Check Whether There Is Slots Available
int checkVacantSlot(string branchname)
{
	int countBJ = 0, countCH = 0, countPJ = 0, totalslot = 10;

	// to count how many branches are there in the system
	while (!allTutors[0].tutorID.empty())
	{
		if (allTutors[0].branch == "Bukit Jalil")
		{
			countBJ++;
		}
		else if (allTutors[0].branch == "Cheras")
		{
			countCH++;
		}
		else
		{
			countPJ++;
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
	regex r("[a-zA-Z]+");
	int choice = 0;
	bool input = true;
	cout << endl;
	cout << string(82, '=') << endl;
	cout << "|" << string(30, ' ') << "Tutor Details Form" << string(32, ' ') << "|" << endl;
	cout << string(82, '=') << endl;
	cout << "	Generated Tutor ID                  : " << ID << endl; // print generated tutor ID

	cout << "	Please enter The First Name of Tutor: ";
	getline(cin, allTutors[i].firstName);
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "	Please enter The Last Name of Tutor : ";
	cin >> allTutors[i].lastName;

	cout << "	Please enter Tutor Date Joined  Format (DD/MM/YYYY) : ";
	cin >> allTutors[i].dateJoined;

	while (cin.fail() || allTutors[i].hourlyRate < 40 || allTutors[i].hourlyRate > 80) {
		cout << "	Please enter Hourly Pay Rate (40-80): ";
		cin >> allTutors[i].hourlyRate;
	}
	do {
		cout << "	Please select Tuition Center        : " << endl;
		cout << "	1. Cheras " << endl;
		cout << "	2. Bukit Jalil" << endl;
		cout << "	3. Petaling Jaya" << endl;

		cout << "	Please insert choice (1-3) : ";
		cin >> choice;
		if (choice < 1 || choice > 3)
		{
			input = false;
		}

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
			input = false;
			break;
		}
	} while (!input);
	do {
		cout << "	Please select Subject Taught : " << endl;
		cout << "	1. Chinese " << endl;
		cout << "	2. Malay" << endl;
		cout << "	3. English" << endl;
		cout << "	4. Mathematics" << endl;
		cout << "	5. Science" << endl;
		cout << "	Please insert choice(1 - 5) : ";

		cin >> choice;
		if (choice < 1 || choice > 5)
		{
			input = false;
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
	} while (!input);
	while (cin.fail() || allTutors[i].phoneNumber.size()) {
		cout << "	Please enter Phone Number           : ";
		cin >> allTutors[i].phoneNumber;
	}
	cout << "	Please enter Tutor Address          : ";
	getline(cin, allTutors[i].address);
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	/*check whether given choice input is valid 1 to 5*/
	while (cin.fail() || allTutors[i].rating < 1 || allTutors[i].rating >5) {
		cout << "	Please enter Tutor Rating     (1-5) : ";
		cin >> allTutors[i].rating;
	}
	arraySize++;

	Sleep(2000);
	cout << endl << "\t*****     Entered Details Successful     *****";
	system("CLS");
}

//Add New Tutor Record (HR)
void addTutor(string branch) {
	string ID = "";

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
			cout << allTutors[i].tutorID << setw(3);
			cout << allTutors[i].hourlyRate << setw(3);
			cout << allTutors[i].tutorID << setw(3) << allTutors[i].firstName << setw(3) << allTutors[i].lastName;
			cout << allTutors[i].dateJoined << setw(3) << allTutors[i].dateTerminated << setw(3);
			cout << allTutors[i].hourlyRate << setw(3) << allTutors[i].center.centerCode << setw(3) << allTutors[i].center.branch;
			cout << setw(3) << allTutors[i].center.centerName;
			cout << setw(3) << allTutors[i].subjectCode << setw(3) << allTutors[i].subjectName;
			cout << setw(3) << allTutors[i].phoneNumber << setw(3) << allTutors[i].address;
			cout << setw(3) << allTutors[i].rating;
			cout << endl;
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
			cout << allTutors[i].hourlyRate << setw(3);
			cout << allTutors[i].tutorID << setw(3) << allTutors[i].firstName << setw(3) << allTutors[i].lastName;
			cout << allTutors[i].dateJoined << setw(3) << allTutors[i].dateTerminated << setw(3);
			cout << allTutors[i].hourlyRate << setw(3) << allTutors[i].center.centerCode << setw(3) << allTutors[i].center.branch;
			cout << setw(3) << allTutors[i].center.centerName;
			cout << setw(3) << allTutors[i].subjectCode << setw(3) << allTutors[i].subjectName;
			cout << setw(3) << allTutors[i].phoneNumber << setw(3) << allTutors[i].address;
			cout << setw(3) << allTutors[i].rating;
			cout << endl;
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
			cout << setw(3) << allTutors[i].rating;
			cout << allTutors[i].hourlyRate << setw(3);
			cout << allTutors[i].tutorID << setw(3) << allTutors[i].firstName << setw(3) << allTutors[i].lastName;
			cout << allTutors[i].dateJoined << setw(3) << allTutors[i].dateTerminated << setw(3);
			cout << allTutors[i].hourlyRate << setw(3) << allTutors[i].center.centerCode << setw(3) << allTutors[i].center.branch;
			cout << setw(3) << allTutors[i].center.centerName;
			cout << setw(3) << allTutors[i].subjectCode << setw(3) << allTutors[i].subjectName;
			cout << setw(3) << allTutors[i].phoneNumber << setw(3) << allTutors[i].address;
			cout << endl;
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
	bool input = true;
	int rating;
	char decision;
	cout << "Please Enter Tutor ID To Be Modified : ";
	cin >> TID;

	int result = searchByTutorIDBinary(0, totalSize, TID);
	if (result == -1)
	{
		cout << "Invalid Tutor ID. Record cannot be not found!";
	}
	else
	{
		do
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
				cout << "Please select Tuition Center        : " << endl;
				cout << "1. Cheras " << endl;
				cout << "2. Bukit Jalil" << endl;
				cout << "3. Petaling Jaya" << endl;

				cout << "Please insert choice (1-3) : ";
				cin >> choice;

				/*check whether given choice input is valid 1 to 3*/

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
				allTutors[result].rating = rating;
				cout << "Rating Had Successfully Changed" << endl;

				break;
			default:
				cout << "Invalid Choice !!! Please Try Again" << endl;
				break;
			}
		} while (!input);

		cout << "Do you want to edit again? 1 = YES, 0 = NO: ";
		cin >> choice;
	} while (choice == 1);
}

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
void viewTutor()
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
		do
		{
			cout << "Which tutor like to search by ID?" << endl;
			cout << "Tutor ID: ";
			cin >> searchTutor;
			result = searchByTutorIDBinary(0, arraySize, searchTutor);
			if (result != -1)
			{
				cout << result << " - " << allTutors[result].tutorID << " - " << allTutors[result].firstName << " - " << allTutors[result].lastName << " - " << allTutors[result].dateJoined << " - " << allTutors[result].dateTerminated << " - " << allTutors[result].hourlyRate << " - " << allTutors[result].phoneNumber << " - " << allTutors[result].address << " - "
					<< allTutors[result].credential << " - " << allTutors[result].branch << " - " << allTutors[result].subjectCode << " - " << allTutors[result].subjectName << " - "
					<< allTutors[result].rating << endl;
			}

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
				cout << "Which tutor would you like to search by rating?";
				cout << "Rating: ";
				cin >> rating;
				result = searchByRatingBinary(0, arraySize, rating);
				if (result != -1)
				{
					cout << result << allTutors[result].tutorID << " - " << allTutors[result].firstName << " - " << allTutors[result].lastName << " - " << allTutors[result].dateJoined << " - " << allTutors[result].dateTerminated << " - " << allTutors[result].hourlyRate << " - " << allTutors[result].phoneNumber << " - " << allTutors[result].address << " - "
						<< allTutors[result].credential << " - " << allTutors[result].branch << " - " << allTutors[result].subjectCode << " - " << allTutors[result].subjectName << " - "
						<< allTutors[result].rating << endl;
				}
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
			cout << "Which tutor would you like to search by rating?";
			cout << "Rating: ";
			cin >> rating;
			result = searchByRatingBinary(0, arraySize, rating);
			if (result != -1)
			{
				cout << result << "" << allTutors[result].tutorID << " - " << allTutors[result].firstName << " - " << allTutors[result].lastName << " - " << allTutors[result].dateJoined << " - " << allTutors[result].dateTerminated << " - " << allTutors[result].hourlyRate << " - " << allTutors[result].phoneNumber << " - " << allTutors[result].address << " - "
					<< allTutors[result].credential << " - " << allTutors[result].branch << " - " << allTutors[result].subjectCode << " - " << allTutors[result].subjectName << " - "
					<< allTutors[result].rating << endl;
			}
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
				cin >> rating;
				cin >> searchTutor;
				result = searchByTutorIDBinary(0, arraySize, searchTutor);
				if (result != -1)
				{
					cout << result << allTutors[result].tutorID << " - " << allTutors[result].firstName << " - " << allTutors[result].lastName << " - " << allTutors[result].dateJoined << " - " << allTutors[result].dateTerminated << " - " << allTutors[result].hourlyRate << " - " << allTutors[result].phoneNumber << " - " << allTutors[result].address << " - "
						<< allTutors[result].credential << " - " << allTutors[result].branch << " - " << allTutors[result].subjectCode << " - " << allTutors[result].subjectName << " - "
						<< allTutors[result].rating << endl;
				}

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
	bool userCredentials = true;
	int i = 0, opt = 0;
	string userType;
	string branch;

	//Convert The First and Second Letter Of The User Code To UpperCase
	//To ensure that the letters are in uppercase
	userCode[0] = toupper(userCode[0]);
	userCode[1] = toupper(userCode[1]);

	//Compare HR and Admin User Code & Credentials With The System's Access Records
	while (!allAccess[i].userCode.empty()) {
		if (userCode == allAccess[i].getUserCode() && credentials == allAccess[i].getCredentials())
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
				viewTutor();
				break;
			case 3:
				modifyTutor();
				break;
			case 4:
				deleteTutor();
				break;
			case 5:
				generateReport();
				break;
			case 6:
				displayExitMenu();
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
		int choice;
		cout << "Login Successful !! ";

		system("CLS");
		do {
			displayAdminMenu();
			cin >> choice;
			switch (choice)
			{
			case 1:
				addTutor(branch);
				bubbleSortTutorID(allTutors);
				cout << endl;
				cout << "Directing back to menu ........";
				system("CLS");
				input = false;
				break;
			case 2:
				viewTutor();
				cout << endl;
				cout << "Directing back to menu ........";
				system("CLS");
				input = false;
				break;
			case 3:
				generateReport();
				cout << endl;
				cout << "Directing back to menu ........";
				system("CLS");
				input = false;
				break;
			case 4:
				displayExitMenu();
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
	int rating = 0, opt = 0, i = 0, rpt = 0, exit = 0;
	do {
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
			break;
		case 4:

			if (displayExitMenu() == 0)
			{
				return;
			}
			else
			{
				cout << "Directing User Back To Menu..........";
				cout << endl;
				checkBranch(branch1, userCode);
			}
			break;

		default:
			cout << "Invalid Choice! Please Re-Enter Your Choice";
			cout << endl;
			break;
		}
		cout << "Anything else to work on this section? 1- YES, Others- NO";
		cout << endl;
		cout << "Choice : ";
		cin >> opt;
	} while (opt == 1);
	cout << "Directing User Back To Menu..........";
	cout << endl;
	checkBranch(branch1, userCode);
}

//Validate User Login Based On User Type
void checkLogin()
{
	int choice;
	bool input = true;
	string userCode, userType, credentials, branch;
	do {
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
			cout << "Invalid selection, Please Try Again";
			input = false;
			system("CLS");
			cout << endl;
		}
	} while (!input);
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
			if (exit = 0)
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

			exit1 = displayExitMenu();
			if (exit1 == 2)
			{
				runprg();
			}
			else
			{
				exit(0);
			}
			break;

		default:

			cout << "Invalid Choice !!! Please Try Again";
			cout << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			input = false;
			break;
		}
	} while (!input);
	//string s = "a";
	//bool match = regex_match(s, r);
	//if (match)
	//	cin >> allTutors[i].lastName;
	//else
	//	std::cout << "Error!" << std::endl;
	//checkLogin();
	//int choice;
	//cout << "Welcome to sorting" << endl;
	//cout << "How would you like to sort your records ?" << endl;
	//cout << "Press 1 for acsending and 2 for descending" << endl;
	//cin >> choice;
	//bubbleSortHourlyRate(allTutors, choice);
	//bubbleSortTutorID(allTutors);
	//cout << "ID: " << tutorIDGenerator(allTutors, arraySize, "Cheras");
	////displayAdminMenu();
	////displayHRMenu();
	////displayTutorMenu();
	////displayLocationMenu();
	////initialize_records();
	////int choice; int i = 0; int arraySize = 0;
	////while (!allTutors[i].tutorID.empty()) {
	////	arraySize++;
	////	i++;
	//
	//
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
	//checkLogin();
	//checkAccess("HR001", "12345");
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