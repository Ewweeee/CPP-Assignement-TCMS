#pragma once
#include <iostream>
using namespace std;

//Display This Menu When User Starts The System
void displayStartMenu() {
	cout << string(82, '=') << endl;
	cout << "|" << string(20, ' ') << "WELCOME TO EXCEL TUTOR MANAGEMENT SYSTEM" << string(20, ' ') << "|" << endl;
	cout << "|" << string(80, ' ') << "|" << endl;
	cout << "|" << string(47, ' ') << "BY: TP055546_TP055495_TP055801" << string(3, ' ') << "|" << endl;
	cout << string(82, '=') << endl;
	/*Login menu selection*/
	cout << string(20, ' ') << "Please Select ONE Choice From The Menu" << string(22, ' ') << endl << endl;
	cout << "1. Log In" << endl;
	cout << "2. Exit Program " << endl;
	cout << endl;
	cout << "Please Enter Your Option : ";
	cout << endl;
}

//Display This Menu When Users Want To Log In The System
void displayUserType() {
	cout << string(82, '=') << endl;
	cout << "|" << string(20, ' ') << "Please Select ONE User Type From The Menu" << string(19, ' ') << "|" << endl;
	cout << string(82, '=') << endl;
	/*User Type selection*/
	cout << "1. Admin" << endl;
	cout << "2. HR" << endl;
	cout << "3. Tutor" << endl;
	cout << endl;
	cout << "Please Enter Your Option : ";
}

//Display This Menu When Users Type = Admin
void displayAdminMenu() {
	cout << string(82, '=') << endl;
	cout << "|" << string(35, ' ') << "ADMIN MENU" << string(35, ' ') << "|" << endl;
	cout << string(82, '=') << endl;
	/*Admin menu selection*/
	cout << string(20, ' ') << "Please Select ONE Choice From The Menu" << string(22, ' ') << endl << endl;
	cout << "1. Add New Tutor Record" << endl;
	cout << "2. View Tutor Record " << endl;
	cout << "3. Exit Program " << endl;
	cout << endl;
	cout << "Please Enter Your Option : ";
	cout << endl;
}

//Display This Menu When Users Type = HR
void displayHRMenu() {
	cout << string(82, '=') << endl;
	cout << "|" << string(31, ' ') << "HUMAN RESOURCE MENU" << string(30, ' ') << "|" << endl;
	cout << string(82, '=') << endl;
	/*HR menu selection*/
	cout << string(20, ' ') << "Please Select ONE Choice From The Menu" << string(22, ' ') << endl << endl;
	cout << "1. Add New Tutor Record" << endl;
	cout << "2. View Tutor Record " << endl;
	cout << "3. Modify Tutor Record " << endl;
	cout << "4. Delete Tutor Record " << endl;
	cout << "5. View Report " << endl;
	cout << "6. Exit Program " << endl;
	cout << endl;
	cout << "Please Enter Your Option : ";
	cout << endl;
}

//Display This Menu When Users Type = Tutor
void displayTutorMenu() {
	cout << string(82, '=') << endl;
	cout << "|" << string(35, ' ') << "TUTOR MENU" << string(35, ' ') << "|" << endl;
	cout << string(82, '=') << endl;
	/*Tutor menu selection*/
	cout << string(20, ' ') << "Please Select ONE Choice From The Menu" << string(22, ' ') << endl << endl;
	cout << "1. View Personal Profile" << endl;
	cout << "2. Modify Personal Profile" << endl;
	cout << "3. View Other Tutor Profile" << endl;
	cout << "4. Exit Program " << endl;
	cout << endl;
	cout << "Please Enter Your Option : ";
	cout << endl;
}

//Display This Menu When Users Enter Tutor Details For The Tution Centre's Location
void displayLocationMenu() {
	/*Tuition Center Location selection*/
	cout << "Please Select ONE Choice From The Available Selection : " << string(20, ' ') << endl << endl;
	cout << "1. Bukit Jalil" << endl;
	cout << "3. Cheras" << endl;
	cout << "4. Petaling Jaya" << endl;
	cout << endl;
	cout << "Please Enter Your Option : ";
	cout << endl;
}

//Display This Menu When Users Enter Tutor Details For The Subject Taught
void displaySubjectMenu() {
	/*Tuition Center Location selection*/
	cout << "Please Select ONE Choice From The Available Selection : " << string(20, ' ') << endl << endl;
	cout << "1. English" << endl;
	cout << "2. Malay" << endl;
	cout << "3. Chinese" << endl;
	cout << "4. Science" << endl;
	cout << "5. Mathematics" << endl;
	cout << endl;
	cout << "Please Enter Your Option : ";
	cout << endl;
}

//Display This Menu To Enable User To Select Sorting Criteria
void displaySortMenu() {
	cout << string(82, '=') << endl;
	cout << "|" << string(20, ' ') << "Please Select ONE Option From The Menu" << string(22, ' ') << "|" << endl;
	cout << string(82, '=') << endl;
	/*User Type selection*/
	cout << "1. Sort By Hourly Pay Rate" << endl;
	cout << "2. Sort By Overall Performance" << endl;
	cout << "3. Sort By Tutor ID" << endl;
	cout << endl;
	cout << "Please Enter Your Option : ";
	cout << endl;
}

//Display This Menu When Users Want To Generate Report (Summary / Location)
void displayReportTypeMenu() {
	cout << string(82, '=') << endl;
	cout << "|" << string(20, ' ') << "Please Select ONE Option From The Menu" << string(22, ' ') << "|" << endl;
	cout << string(82, '=') << endl;
	/*User Type selection*/
	cout << "1. Summary Report" << endl;
	cout << "2. Report By Location" << endl;
	cout << endl;
	cout << "Please Enter Your Option : ";
	cout << endl;
}

//Display This Menu To Enable User To Select Searching Criteria
void displaySearchMenu() {
	cout << string(82, '=') << endl;
	cout << "|" << string(20, ' ') << "Please Select ONE Option From The Menu" << string(22, ' ') << "|" << endl;
	cout << string(82, '=') << endl;
	/*User Type selection*/
	cout << "1. Search By Tutor ID" << endl;
	cout << "2. Search By Overall Performance" << endl;
	cout << endl;
	cout << "Please Enter Your Option : ";
	cout << endl;
}

//Display This Menu To Enable User (HR / Admin) To Select Sections That They Want To Modify
void displayModifyTutorMenu() {
	cout << string(82, '=') << endl;
	cout << "|" << string(20, ' ') << "Please Select ONE Option From The Menu" << string(22, ' ') << "|" << endl;
	cout << string(82, '=') << endl;
	/*User Type selection*/
	cout << "1. Tutor Name" << endl;
	cout << "2. Date Joined" << endl;
	cout << "3. Date Terminated" << endl;
	cout << "4. Hourly Rate" << endl;
	cout << "5. Phone Number" << endl;
	cout << "6. Address" << endl;
	cout << "7. Credentials" << endl;
	cout << "8. Branch Name" << endl;
	cout << "9. Subject" << endl;
	cout << "10. Rating" << endl;
	cout << endl;
	cout << "Please Enter Your Option : ";
	cout << endl;
}

//Display This Menu To Enable User (Tutor) To Select Sections That They Want To Modify
void displayModifyPersonalInfoMenu() {
	cout << string(82, '=') << endl;
	cout << "|" << string(20, ' ') << "Please Select ONE Option From The Menu" << string(22, ' ') << "|" << endl;
	cout << string(82, '=') << endl;
	/*User Type selection*/
	cout << "1. Name" << endl;
	cout << "2. Phone Number" << endl;
	cout << "3. Address" << endl;
	cout << "4. Account Credentials" << endl;
	cout << endl;
	cout << "Please Enter Your Option : ";
	cout << endl;
}

//Display This Menu When Users Wanted To Exit The System
void displayExitMenu() {
	string choice;
	cout << "Are You Sure To Exit The Program ? (Y/N)" << endl;
	cin >> choice;
	if (choice == "Y" || choice == "Yes")
	{
		cout << "Thank You !!";
	}
	else if (choice == "N" || choice == "No")
	{
		cout << "Remain";
		cout << endl;
		displayExitMenu();
	}
	else
	{
		cout << "Invalid Selection !!! Please Try Again !!";
		cout << endl;
		displayExitMenu();
	}
	cout << endl;
}
