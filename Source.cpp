/****************************File Description*********************************
*			Author: Samuel Huxtable		Last Revision: 25/3/20				 *
*							File Name: Source.cpp							 *
*	Description: Main function as described in course work,					 *
*																			 *
******************************************************************************/
#include "Entry.h"
#include <vector>

using namespace std;

int main() {
	//Initilize varibles
	int choice = 0;
	Entry* a = (Entry*) malloc (1);		//Create a pointer and point it to a location
	vector<Entry*> entryList;
	cout << "Library Entry Manager" << endl;
	//If a file Exists, then read the values and save them into entryList
	entryList = a->ReadListFromFile();

	while (1) {
		cout << "What action would you like to undertake?" << endl << endl;
		cout << "1: Add New Entrys" << endl;
		cout << "2: Display All Entrys" << endl;
		cout << "3: Search and Display information about a entry" << endl;
		cout << "4: Lend a item" << endl;
		cout << "5: Return a item" << endl;
		cout << "6: Remove a Entry" << endl;
		cin >> choice;
		if (choice == 1) {
			//Allows the user to add entrys to entryList 
			entryList = a -> AddEntrys(entryList);
		}
		else if (choice == 2) {
			//Displays the contents of entryList
			a -> DisplayEntrys(entryList);
		}
		else if (choice == 3) {
			//Search entryList and display the values of the element
			a -> SearchAndDisplay(entryList);
		}
		else if (choice == 4) {
			//Search entryList and change the element to borrowed
			entryList = a->SearchAndBorrowed(entryList);
		}
		else if (choice == 5) {
			//Search entryList and set the element to returned 
			entryList = a->SearchAndReturned(entryList);
		}
		else if (choice == 6) {
			//Search entryList and remove the selected element
			entryList = a->RemoveEntry(entryList);
		}
		else {
			cout << "Please try again" << endl << endl;
		}
		//Save any changes to entryList
		a->SaveEntryListToFile(entryList);
	}
};


