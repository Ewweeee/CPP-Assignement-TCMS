//preprocessor directive used to prevent header files from being included multiple times
#pragma once

#include <iostream>
#include <iomanip>
#include <windows.h>

using namespace std;
int tutorID;

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

//Tutor Structure - to store tutor's information (Array)
struct Tutor {
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
	string subjectCode;
	string subjectName;
	int rating;
};
struct Tutor allTutors[100];

void initialize_records() {
	allTutors[0].tutorID = 1;
	allTutors[0].firstName = "Chan";
	allTutors[0].lastName = "Hong Xian";
	allTutors[0].dateJoined = "23 / 06 / 2013";
	allTutors[0].hourlyRate = 40;
	allTutors[0].center.centerCode = 1002;
	allTutors[0].center.centerName = "eXcel Tuition Centre Bukit Jalil";
	allTutors[0].center.branch = "Bukit Jalil";
	allTutors[0].subjectCode = "CHN";
	allTutors[0].subjectName = "Chinese";
	allTutors[0].phoneNumber = "601975623245";
	allTutors[0].address = "Jln 24, Taman Putra, Bukit Jalil";
	allTutors[0].rating = 4;

	allTutors[1].tutorID = 2;
	allTutors[1].firstName = "Tan";
	allTutors[1].lastName = "Xin Qian";
	allTutors[1].dateJoined = "20 / 05 / 2012";
	allTutors[1].hourlyRate = 40;
	allTutors[1].center.centerCode = 1001;
	allTutors[1].center.centerName = "eXcel Tuition Centre Cheras";
	allTutors[1].center.branch = "Cheras";
	allTutors[1].subjectCode = "ENG";
	allTutors[1].subjectName = "English";
	allTutors[1].phoneNumber = "601782635467";
	allTutors[1].address = "Connaught Avenue, Taman Connaught, Cheras";
	allTutors[1].rating = 5;

	allTutors[2].tutorID = 3;
	allTutors[2].firstName = "Yew";
	allTutors[2].lastName = "Ming Yao";
	allTutors[2].dateJoined = "20 / 11 / 2015";
	allTutors[2].hourlyRate = 45;
	allTutors[2].center.centerCode = 1003;
	allTutors[2].center.centerName = "eXcel Tuition Centre Puchong";
	allTutors[2].center.branch = "Puchong";
	allTutors[2].subjectCode = "MLY";
	allTutors[2].subjectName = "Malay";
	allTutors[2].phoneNumber = "601822654371";
	allTutors[2].address = "BK5 Desiran Bandar Kinrara, Puchong";
	allTutors[2].rating = 3;
}

void display_ascending(int lastIndex) {
	/*system("CLS");*/
	/*formating for the title for details of tutor*/
	cout << "\t| TUTOR DETAILS |" << endl << endl;
	cout << "|TUTOR ID|" << setw(3) << "FIRST NAME|" << setw(3) << "LAST NAME|" << setw(3) << "DATE JOINED|";
	cout << setw(3) << "DATE TERMINATED|" << setw(3) << "PAY|" << setw(3) << "CENTRE CODE|" << setw(3) << "CENTRE LOCATION|";
	cout << setw(3) << "CENTRE NAME|" << setw(3) << "SUB CODE|" << setw(3) << "SUB NAME|" << setw(3) << "PHONE NUM|";
	cout << setw(3) << "ADDRESS|" << setw(3) << "RATINGS | " << endl;
	int i = 0;
	/*while index is lesser or equals to last index display tutor details*/
	while (i <= lastIndex) {
		/*check if tutor ID in the index is not null*/
		if (allTutors[i].tutorID != NULL) {
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
	/*press enter to leave the current function*/
	cout << "	PRESS ENTER TO LEAVE ......" << endl;
	cout << "	"; cin.get();
	if (cin.get() == '\n') {
		cout << "	EXITING BACK TO MAIN MENU	" << endl;
		Sleep(2000);
		system("CLS");
	}
}

