#include <iostream>
#include "Menu.h"
#include "Struct.h"
using namespace std;

//Function Prototype
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

int main() {
	displayLoginMenu();
	displayAdminMenu();
	displayHRMenu();
	displayTutorMenu();
	displayLocationMenu();
	return 0;

	//hi this is Evonne uwu
}
