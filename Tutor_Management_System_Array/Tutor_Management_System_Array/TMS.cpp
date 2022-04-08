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
	initialize_records();
	int choice; int i = 0; int arraySize = 0;
	while (allTutors[i].tutorID != NULL) {
		arraySize++;
		i++;
	}
	display_ascending(arraySize - 1);
	cout << "Done" << endl;

	//displayExitMenu();

	return 0;
}
