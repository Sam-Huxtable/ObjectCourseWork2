/****************************File Description*********************************
*			Author: Samuel Huxtable		Last Revision: 25/3/20				 *
*							File Name: Entry.h								 *
*	Description: Defines the Class Entry and creates all varibles and		 *
*				 Functions used by the class.								 *
*																			 *
******************************************************************************/
#ifndef Entry_H
#define Entry_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "Entry.h"

using namespace std;

//Create the class Entry
class Entry {
	//Initilize varibles
	bool borrowed = 0;
	string borrowedBy = "Not_on_Loan";
	string name;
	string year;
	int k = 0;

public:
	string hold;
	string hold2;

	//Functions for a Setting single Entry
	inline void SetName(string hold) { name = hold; };
	inline void SetYear(string hold) { year = hold; };
	inline void SetBorrowedBy(string hold) { borrowedBy = hold; };
	inline void SetBorrowed() { borrowed = 1; }
	void entryBorrowed(string name) { SetBorrowedBy(name); SetBorrowed(); };
	void entryReturned() { borrowed = 0; borrowedBy = "Not_on_Loan"; }

	//Functions to print info
	inline const void PrintName() { cout << "  Name: " << name << endl; };
	inline const void PrintYear() { cout << "  Year: " << year << endl; };
	inline const void PrintBorrowed() { cout << "  Currently on loan to: " << borrowedBy << endl; };

	//Virtual Functions used in all subclasses
	virtual void UserInput() = 0;
	virtual const void FileWrite(ofstream&) = 0;
	virtual const void PrintDetails() = 0;
	virtual Entry* FileRead(string) = 0;

	//Functions to return info
	inline const string ReturnName() { return name; }
	inline const string ReturnYear() { return year; }
	inline const string ReturnBorrowedBy() { return borrowedBy; }
	inline string ReturnBorrowed() { hold = std::to_string(borrowed); return hold; }
	
	//Funtions to work with vectors
	vector<Entry*> AddEntrys(vector<Entry*>);
	const void DisplayEntrys(vector<Entry*>);
	void SearchAndDisplay(vector<Entry*>);
	vector<Entry*> SearchAndBorrowed(vector<Entry*>);
	vector<Entry*> SearchAndReturned(vector<Entry*>);
	void SaveEntryListToFile(vector<Entry*>);
	vector<Entry*> ReadListFromFile();
	vector<Entry*> RemoveEntry(vector<Entry*>);
};

//Create the subclass album
class Album : public Entry {
	//Initilize varibles
	string artist;
	string recordLabel;
public:
	//Create a object of type Entry-Album (No arguments)
	Album() { UserInput(); };
	//Create a object of type Entry-Ablum (4 arguments)
	Album(string name, string year, string artist, string recordLabel) { SetName(name); SetYear(year); SetArtist(artist); SetRecordLabel(recordLabel); };

	//Sets the varible artist to the value of input string hold 
	inline void SetArtist(string hold) {
		artist = hold;
	};

	//Sets the varible recordLabel to the value of input string hold 
	inline void SetRecordLabel(string hold) {
		recordLabel = hold;
	};

	//Print the artist and recordlabel
	const void PrintDetails() {
		cout << "  Artist: " << artist << endl;
		cout << "  Recordlabel: " << recordLabel << endl;
	};

	//Write Album objects to a line of a text file
	const void FileWrite(ofstream& writefile) {
		writefile << "Album " << ReturnName() << " " << ReturnYear() << " " << ReturnBorrowed() << " " << ReturnBorrowedBy() << " ";
		writefile << artist << " " << recordLabel << endl;
	};

	//Read Album objects from a text file and create these objects
	Entry* FileRead(string line) {
		string lin;
		std::stringstream ss(line);		//Create ss as a string stream of line
		Album* a = new Album(" ", " ", " ", "");		//Create a blank pointer to a new album
		int i = 0;

		while (ss.good()) {		//While the stream is good
			ss >> lin;
			if (i == 1) {
				a->SetName(lin);		//Set the name
			}
			else if (i == 2) {
				a->SetYear(lin);		//Set the year
			}
			else if (i == 3) {
				if (lin == "1") {
					a->entryBorrowed(lin);		//Set the entry borrowed by lin
				}
			}
			else if (i == 5) {
				a->SetArtist(lin);		//Set the Artist
			}
			else if (i == 6) {
				a->SetRecordLabel(lin);		//Set the record label
			}
			i++;
		}
		Entry* b = a;		//convert the pointer to the Album to a point of type Entry
		return b;
	};

	//Allows the user to create Album Objects
	void UserInput() {
		cout << "Please input the information required" << endl;
		cout << "Name: ";
		cin >> hold;
		SetName(hold);
		cout << "Year of publishing: ";
		cin >> hold2;
		SetYear(hold2);
		cout << "Artist: ";
		cin >> artist;
		cout << "Recordlabel: ";
		cin >> recordLabel;
	};

};

//Create the subclass Book
class Book : public Entry {
	//Initilize varibles
	string author;
	string publisher;
	string edition;
public:
	//Create a object of type Entry-Book (No arguments)
	Book() { UserInput(); };
	//Create a object of type Entry-Book (5 arguments)
	Book(string name, string year, string author, string publisher, string edition) { SetName(name); SetYear(year); SetAuthor(author); SetPublisher(publisher); SetEdition(edition); };
	
	//Sets the varible author to the value of input string hold 
	inline void SetAuthor(string hold) {
		author = hold;
	};

	//Sets the varible publisher to the value of input string hold 
	inline void SetPublisher(string hold) {
		publisher = hold;
	};

	//Sets the varible edition to the value of input string hold 
	inline void SetEdition(string hold) {
		edition = hold;
	};

	//Print the Author, Publisher and Edition
	const void PrintDetails() {
		cout << "  Author: " << author << endl;
		cout << "  Publisher: " << publisher << endl;
		cout << "  Edition: " << edition << endl;
	};

	//Write Book objects to a line of a text file
	const void FileWrite(ofstream& writefile) {
		writefile << "Book " << ReturnName() << " " << ReturnYear() << " " << ReturnBorrowed() << " " << ReturnBorrowedBy() << " ";
		writefile << author << " " << publisher << " " << edition << endl;
	};

	//Read Book objects from a text file and create these objects
	Entry* FileRead(string line) {
		string lin;
		std::stringstream ss(line);		//Create ss as a string stream of line
		Book* a = new Book(" ", " ", " ", " ", "");			//Create a blank pointer to a new album
		int i = 0;
		while (ss.good()) {			//While the stream is good
			ss >> lin;
			if (i == 1) {
				a->SetName(lin);
			}
			else if (i == 2) {
				a->SetYear(lin);
			}
			else if (i == 3) {
				if (lin == "1") {
					a->entryBorrowed(lin);
				}
			}
			else if (i == 5) {
				a->SetAuthor(lin);
			}
			else if (i == 6) {
				a->SetPublisher(lin);
			}
			else if (i == 7) {
				a->SetEdition(lin);
			}
			i++;
		}
		Entry* b = a;		//convert the pointer to the Album to a point of type Entry
		return b;
	};

	//Allows the user to create Book Objects
	void UserInput() {
		cout << "Please input the information required" << endl;
		cout << "Name: ";
		cin >> hold;
		SetName(hold);
		cout << "Year of publishing: ";
		cin >> hold2;
		SetYear(hold2);
		cout << "Author: ";
		cin >> author;
		cout << "Publisher: ";
		cin >> publisher;
		cout << "Edition: ";
		cin >> edition;
	};

};

//Create a object of subclass Film
class Film : public Entry {
	string director;
	string language;
public:
	//Create a object of type Entry-Book (No arguments)
	Film() { UserInput(); };
	//Create a object of type Entry-Book (4 arguments)
	Film(string name, string year, string director, string Language) { SetName(name); SetYear(year); SetDirector(director); SetLanguage(language); };

	//Sets the varible director to the value of input string hold 
	inline void SetDirector(string hold) {
		director = hold;
	};

	//Sets the varible language to the value of input string hold 
	inline void SetLanguage(string hold) {
		language = hold;
	};

	//Print the Director and Language
	const void PrintDetails() {
		cout << "  Director: " << director << endl;
		cout << "  Language: " << language << endl;
	};

	//Write Film objects to a line of a text file
	const void FileWrite(ofstream& writefile) {
		writefile << "Film " << ReturnName() << " " << ReturnYear() << " " << ReturnBorrowed() << " " << ReturnBorrowedBy() << " ";
		writefile << director << " " << language << endl;
	};

	//Read Film objects from a text file and create these objects
	Entry* FileRead(string line) {
		string lin;
		std::stringstream ss(line);			//Create ss as a string stream of line
		Film* a = new Film(" ", " ", " ", "");			//Create a blank pointer to a new album
		int i = 0;
		while (ss.good()) {				//While the stream is good
			ss >> lin;
			if (i == 1) {
				a->SetName(lin);
			}
			else if (i == 2) {
				a->SetYear(lin);
			}
			else if (i == 3) {
				if (lin == "1") {
					a->entryBorrowed(lin);
				}
			}
			else if (i == 5) {
				a->SetDirector(lin);
			}
			else if (i == 6) {
				a->SetLanguage(lin);
			}
			i++;
		}
		Entry* b = a;		//convert the pointer to the Album to a point of type Entry
		return a;
	};

	//Allows the user to create Film Objects
	void UserInput() {
		cout << "Please input the information required" << endl;
		cout << "Name: ";
		cin >> hold;
		SetName(hold);
		cout << "Year of publishing: ";
		cin >> hold2;
		SetYear(hold2);
		cout << "Director: ";
		cin >> director;
		cout << "Language: ";
		cin >> language;
	};

};
#endif