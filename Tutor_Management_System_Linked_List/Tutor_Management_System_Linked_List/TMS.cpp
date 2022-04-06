#include <iostream>
#include "Menu.h"
using namespace std;

//Function Prototype
void CheckLogin();
void AddTutor();
void ModifyTutor();
void DeleteTutor();
void GenerateReport();
void sort_display_record();
void search_record();
void exit_sys();


int main() {
	displayLoginMenu();
	displayAdminMenu();
	displayHRMenu();
	displayTutorMenu();
	displayExitMenu();
	return 0;

	//hi this is Evonne uwu
}
