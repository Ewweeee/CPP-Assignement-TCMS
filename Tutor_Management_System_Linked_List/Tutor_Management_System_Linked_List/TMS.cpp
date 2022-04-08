#include <iostream>
#include "Menu.h"
#include "Struct.h"
using namespace std;

//Function Prototype

//Validate Whether User Is A Tutor
void CheckTutor();

//Validate User Login
void CheckLogin();

//Add New Tutor Record
void AddTutor();

//Modify Tutor Record
void ModifyTutor();

//Delete Tutor Record
void DeleteTutor();

//Generate Report
void GenerateReport();
void sort_display_record();
void search_record();
void exit_sys();

void CheckTutor() {
	int choice = 0;
	displayUserType();
	cin >> choice;
	
	switch (choice)
	{
	case 1:
		cout << "HI Admin" << endl;
		break;
	case 2:
		cout << "HI HR" << endl;
		break;
	case 3:
		cout << "HI TUTOR" << endl;
		break;
	default:
		cout << "Invalid Selection" << endl;
		break;
	}
}

int main() {
	displayLoginMenu();
	displayAdminMenu();
	displayHRMenu();
	displayTutorMenu();
	displayLocationMenu();
	displayUserType();
	CheckTutor();
	return 0;

	//hi this is Evonne uwu
}