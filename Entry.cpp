/****************************File Description*********************************
*	Author: Samuel Huxtable		Last Revision: 30/04/20						 *
*	Description: Contains all functions used by the class Entry.			 *
*																			 *
*							Funtions Included:								 *
*																			 *
*	AddEntrys - Adds a new user created object of class Entry to a vector	 *
*	DisplayEntrys - Displays all the entrys in a vector					     *
*	SearchAndDisplay - Used to search for and display a entry from a vector	 *
*	SearchAndBorrowed - Set a entry from a vector to borrowed				 *
*	SearchAndReturned - Set a entry from a vector to not borrowed			 *
*	SaveListToFile - Saves the contents of a vector to a file				 *
*	ReadListFromFile - Reads from a file into a vecor of Entrys				 *
*	RemoveEntrys - Searchs a vector and removes choosen entrys				 *
*	Finished - Asks the user if they have finished							 *
******************************************************************************/

#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <sstream>
#include "Entry.h"
using namespace std;

int finished();

//AddEntrys(Pointer to a vector of Entrys) - Allows the user to create more entrys and add them to the vector
vector<Entry*> Entry::AddEntrys(vector<Entry*> List) {
	
	int check = 1;
	int choice = 0;
	while (check) {
		k = List.size();
		cout << "What is your new entry?" << endl << "1: Album" << endl << "2: Book" << endl << "3: Film" << endl;
		cin >> choice;
		if (choice == 1) {
			List.push_back(new Album());		//Push Back list with a new album
		}
		else if (choice == 2) {
			List.push_back(new Book());			//Push Back List with a new book
		}
		else if (choice = 3) {
			List.push_back(new Film());			//Push Back List with a new film
		}
		else {
			cout << "Please select a correct answer" << endl;
		}
		check = finished();		//Confirm the user has finished
	}
	return List;			//Return the updated list
};

//DisplayEntry(Pointer to a vector of Entrys) - Displays onscreen all entrys contained with List
const void Entry::DisplayEntrys(vector<Entry*> List) {
	k = List.size();		//Find the size of List

	for (int i = 0; i < k; i++) {			//Loop upto the List size
		cout << "Entry " << i << endl;
		List[i] -> PrintName();			//Print the Name
		List[i] -> PrintYear();			//Print the year published
		List[i]->PrintBorrowed();		//Print if the item has been borrowed
	}
};

//SearchAndDisplay(Pointer to a vector of Entrys) - Searchs the vector List and displays the result in greater detail
void Entry::SearchAndDisplay(vector<Entry*> List) {
	k = List.size();		//Find the size of List
	string hold, hold2;

	cout << "Input the information about your search" << endl;
	cout << "Name: ";
	cin >> hold;
	cout << "Year Published: ";
	cin >> hold2;
	
	for (int i = 0; i < k; i++) {
		if (hold.compare(List[i] -> ReturnName()) == 0) {		//Find if the names match
			if (hold2.compare(List[i]-> ReturnYear()) == 0) {		//Find if the years match
				List[i] -> PrintName();			//Print Name
				List[i] -> PrintYear();			//Print Year
				List[i] -> PrintBorrowed();		//Print if the item is borrow
				List[i] -> PrintDetails();		//Print all other details
			}
		}
	}
};

//SearchAndBorrowed(Pointer to a vector of Entrys) - Searchs List and sets the Entry to borrowd
vector<Entry*> Entry::SearchAndBorrowed(vector<Entry*> List) {
	k = List.size();			//Find the size of List
	string hold, hold2, hold3;

	cout << "Input the information about your search" << endl;
	cout << "Name: ";
	cin >> hold;
	cout << "Year Published: ";
	cin >> hold2;
	cout << "Who is borrowing the item?" << endl;
	cin >> hold3;

	for (int i = 0; i < k; i++) {
		if (hold.compare(List[i]->ReturnName()) == 0) {
			if (hold2.compare(List[i]->ReturnYear()) == 0) {
				List[i]->entryBorrowed(hold3);		//Make the entry borrowed by hold3
			}
		}
	}
	return List;		//Return the modified list
};

//SearchAndReturned(Pointer to a vector of Entrys) - Searchs List and sets the Entry to returned
vector<Entry*> Entry::SearchAndReturned(vector<Entry*> List) {
	k = List.size();
	string hold, hold2, hold3;

	cout << "Input the information about your search" << endl;
	cout << "Name: ";
	cin >> hold;
	cout << "Year Published: ";
	cin >> hold2;

	for (int i = 0; i < k; i++) {
		if (hold.compare(List[i]->ReturnName()) == 0) {			//Find if the names match
			if (hold2.compare(List[i]->ReturnYear()) == 0) {		//Find if the years match
				List[i]->entryReturned();			//Return the item
			}
		}
	}
	return List;
};

//SaveEntryListToFile(Pointer to a vector of Entrys) - Saves List to a file
void Entry::SaveEntryListToFile(vector<Entry*> List) {
	ofstream writefile;		//Create a output file 

	remove("./test.txt");			//Empty the file test.txt
 	writefile.open("./test.txt");	//Open a new test.txt for writing
	if (!writefile) { 
		cout << "Error opening the file!" << endl;
	}

	for (k = 0; k < List.size(); k++) {				//Loop through List, in increments of 3, upto the list size
		List[k]->FileWrite(writefile);						//Write to the file
	}
	writefile.close();				//close the file
}

//ReadListFromFile() - Reads from a file and returns its contains as a pointer to a vector
vector<Entry*> Entry::ReadListFromFile() {
	Entry* a = (Entry*)malloc(1);		//Create a pointer and point it to a location
	vector<Entry*> List;		//Create a vector of Entry pointers
	ifstream readfile;			//Create a input file handler
	string linestr, line;
	int i = 0;
	int k = 0;
		
	readfile.open("./test.txt");		//Open test.txt for reading
	if (!readfile) {
		cout << "Error opening the file!" << endl;
		return List;
	}
	while (std::getline(readfile, linestr)) {		//While a line is being read from the file save it into linestr
		k = 0;
		std::stringstream ss(linestr);			//Make ss into a string stream of linestr
		ss >> line;			//Save the first element of ss into line
		if (ss.good()) {				//Check ss worked
			if (line == "Album") {
				a = new Album(" ", " ", " ", " ");		//Create a blank album
				List.push_back(a->FileRead(linestr));		//Push back List with the return from Fileread. Fileread is passed linstr
			}
			else if (line == "Film") {
				a = new Book(" ", " ", " ", " ", " ");		//Create a blank book
				List.push_back(a->FileRead(linestr));			//Push back List with the return from Fileread. Fileread is passed linstr
			}
			else if (line == "Film") {
				a = new Film(" ", " ", " ", " ");		//Create a blank film
				List.push_back(a->FileRead(linestr));		//Push back List with the return from Fileread. Fileread is passed linstr
			}
		}
	}
	readfile.close();		//close the file
	return List;
}

//RemoveEntry(Pointer to vector of entrys) - Removes selected entry from List
vector<Entry*> Entry::RemoveEntry(vector<Entry*>List) {

	string hold, hold2;
	cout << "What entry do you wish to remove?" << endl;
	cout << "Name: ";
	cin >> hold;
	cout << "Year Published: ";
	cin >> hold2;
	
	for (int i = 0; i < List.size(); i++) {
		if (hold.compare(List[i]->ReturnName()) == 0) {
			if (hold2.compare(List[i]->ReturnYear()) == 0) {
				List[i]->PrintName();				//Print the name
				List[i]->PrintYear();				//Print the year
				List[i]->PrintDetails();				//Print all other details
				cout << "  Is this the entry you wish to remove? (y/n)" << endl;
				cin >> hold;
				if (hold == "y") {	
					List.erase(List.begin() + i);			//Remove the entry from the vector List
					cout << "The Entry has been removed" << endl;
				}
			}
		}
	}
	return List;		//Return List
}

int finished() {		//Function to check if the user is finshed what they are doing

	string fin = "n";
	string yn = "";
	while (fin == "n") {
		cout << "Have you finished? (y/n)";
		cin >> yn;
		if (yn == "y") { return 0; }
		if (yn == "n") { return 1; }
		else { fin = "n"; }
	}
	return 0;
}