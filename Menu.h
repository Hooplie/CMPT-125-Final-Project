// Menu.h

#include <iostream>        
#include <string>
#include <cassert>


using namespace std;

class Menu
{

string user_input;

public:
	// default constructor 
	Menu()
	{ 
		cout << "\n-----------------------------\n" <<
		"Welcome to the Song Database!\n" << "-----------------------------\n\n" << 
		"Please select from the following options:\n" << 
		"1. Add a song\n" <<
		"2. Find a song\n" << 
		"3. Delete a song\n" <<
		"4. List songs\n" << 
		"5. Quit\n\n";
	}

	void main_menu()
	{
		cout << "\n-----------------------------\n" <<
		"Welcome to the Song Database!\n" << "-----------------------------\n\n" << 
		"Please select from the following options:\n" << 
		"1. Add a song\n" <<
		"2. Find a song\n" << 
		"3. Delete a song\n" <<
		"4. List songs\n" << 
		"5. Quit\n\n";
	}

	void add_song() // INPUT 1
	{
		cout << "\n----------" <<
		"\nAdd a Song\n" << "----------\n\n" <<
		"Enter the following information:\n";
	}

	void find_song() // INPUT 2
	{
		cout << "\n-----------" <<
		"\nFind a Song\n" << "-----------\n\n" <<
		"Enter the Exact:\n" <<
		"1. Name of the song\n" <<
		"2. Artist\n" <<
		"3. Genre\n" <<
		"4. Year\n" <<
		"5. Beats per minute\n\n" <<
		"Partially Enter:\n" <<
		"6. Name of the song\n" <<
		"7. Artist\n" <<
		"8. Genre\n\n" <<
		"Enter a Range:\n" <<
		"9. Year\n" <<
		"10. Beats per minute\n\n" <<
		"(R)eturn to the main menu\n";
	}

	void delete_song() // INPUT 3
	{
		cout << "\n-------------" <<
		"\nDelete a Song\n" << "-------------\n\n" <<
		"Enter the Exact:\n" <<
		"1. Name of the song\n" <<
		"2. Artist\n" <<
		"3. Genre\n" <<
		"4. Year\n" <<
		"5. Beats per minute\n\n" <<
		"Partially Enter:\n" <<
		"6. Name of the song\n" <<
		"7. Artist\n" <<
		"8. Genre\n\n" <<
		"Enter a Range:\n" <<
		"9. Year\n" <<
		"10. Beats per minute\n\n" <<
		"(R)eturn to the main menu\n";
	}

	void list_song() // INPUT 4
	{
		cout << "\n---------------" <<
		"\nList your songs\n" << "---------------\n\n" <<
		"Alphebetically:\n" <<
		"1. Name\n" <<
		"2. Artist\n" <<
		"3. Genre\n\n" <<
		"Reverse Alphabetically:\n" <<
		"4. Name\n" <<
		"5. Artist\n" <<
		"6. Genre\n\n" <<
		"Ascending Order:\n" <<
		"7. Year\n" <<
		"8. Beats per minute\n\n" <<
		"Descending Order:\n" <<
		"9. Year\n" <<
		"10. Beats per minute\n\n" <<
		"(R)eturn to the main menu\n";
	}

	void quit_menu() // INPUT 5
	{
		cout << "\n----------------" <<
		"\nExiting database\n" << "----------------\n\n" <<
		"Your database has been updated and stored in 'database.csv'\n\n" <<
		"Goodbye\n";
	}

	void invalid_input(const string& user_input)
	{
		cout << "\nOption " << "'" << user_input << "'" << " not recognized\n" <<
		"Please select from the following options:\n"  <<
		"1. Add a song\n" <<
		"2. Find a song\n" << 
		"3. Delete a song\n" <<
		"4. List songs\n" << 
		"5. Quit\n";
	}

}; //class Menu

