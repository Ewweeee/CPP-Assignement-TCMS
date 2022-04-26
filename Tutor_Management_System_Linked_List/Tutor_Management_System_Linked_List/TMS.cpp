#include <iostream>
#include <string>
#include <iomanip>
#include "Menu.h"
#include "Struct.h"
using namespace std;

//Function Prototype

//Validate Whether Tutor's Login Credentials
void checkTutor();

//Validate User Login Based On User Type
void checkLogin();

//Check Whether There Is Slots Available
void checkVacantSlot();

//Add New Tutor Record
void addTutor();

//Modify Tutor Record
void modifyTutor();

//Delete Tutor Record
void deleteTutor();

//Sort Records By Tutor ID / Hourly Rate / Overall Performance
void sortByTutorID();

void sortByHourlyRate();

void sortByOverallPerformance();

//Search Records By Tutor ID / Rating
void searchByTutorID();

void searchByRating();

//Generate Summary Report / By Location Function
void generateReport() {
	int i = 0;
	int choice = 0;
	int totalTutors = 30;
	int totalTutorsInEachLoc = 10;
	//Summary Report Variables
	int emptySlot = 0;
	int occupiedSlot = 0;
	//Location Report Variables
	int BJOcc = 0;
	int CHOcc = 0;
	int PJOcc = 0;
	Tutor* current = new Tutor();

	cin >> choice;
	cout << endl;
	switch (choice)
	{
	case 1:
		if (head != NULL) {
			/*While Current Node != NULL */
			while (current != NULL) {
				occupiedSlot++;
				current = current->nextAddress;
			}
			emptySlot = totalTutors - occupiedSlot; //calculate empty slot
			cout << endl;
			cout << "	TOTAL NUMBER OF TUTORS" << setw(11) << " = " << occupiedSlot << endl;
			cout << "	TOTAL NUMBER OF AVAILABLE SLOT = " << emptySlot << endl;
		}
		else {
			//If LinkedList is Empty, reset the emptySlot = 30
			emptySlot = 30;
			cout << endl;
			cout << "	TOTAL NUMBER OF TUTORS" << setw(11) << " = " << occupiedSlot << endl;
			cout << "	TOTAL NUMBER OF AVAILABLE SLOT = " << emptySlot << endl;
		}
		break;

	case 2:

		break;
	}
}

int main() {
	displayStartMenu();
	displayAdminMenu();
	displayHRMenu();
	displayTutorMenu();
	displayLocationMenu();
	displayUserType();
	generateReport();
	return 0;

	//hi this is Evonne uwu
}