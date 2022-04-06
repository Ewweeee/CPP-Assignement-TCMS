#pragma once
#include <iostream>
using namespace std;

void displayLoginMenu() {
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
}

void displayAdminMenu() {
	cout << string(82, '=') << endl;
	cout << "|" << string(35, ' ') << "ADMIN MENU" << string(35, ' ') << "|" << endl;
	cout << string(82, '=') << endl;
	/*Admin menu selection*/
	cout << string(20, ' ') << "Please Select ONE Choice From The Menu" << string(22, ' ') << endl << endl;
	cout << "1. Add New Tutor Record" << endl;
	cout << "2. View Tutor Record " << endl;
	cout << "3. View Report " << endl;
	cout << "4. Exit Program " << endl;
	cout << endl;
}

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
}

void displayTutorMenu() {
	cout << string(82, '=') << endl;
	cout << "|" << string(35, ' ') << "TUTOR MENU" << string(35, ' ') << "|" << endl;
	cout << string(82, '=') << endl;
	/*Tutor menu selection*/
	cout << string(20, ' ') << "Please Select ONE Choice From The Menu" << string(22, ' ') << endl << endl;
	cout << "1. View Personal Profile" << endl;
	cout << "2. View Other Tutor Profile" << endl;
	cout << "3. Exit Program " << endl;
	cout << endl;
}

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