// Database.h
   
#include <iostream>        
#include <string>
#include <cassert>
#include <fstream>

using namespace std;

class Database 
{
	int capacity; // length of underlying array
	string* arr; // pointer to the underlying array, i.e our database
	int size; // number of elements in int_vec 

public:

	// default constructor
	Database() 
	: capacity(1000), arr(new string[capacity]), size(0) 
	{ }

	// destructor 
	~Database() 
	{
		delete[] arr;
	}

	// getter that returns size 
	int get_size() const 
	{
		return size;
	}

	// getter that returns capacity
	int get_capacity() const 
	{
		return capacity;
	}

	// getter that returns arr 
	string* get_arr() const 
	{
		return arr;
	}

	// getter that returns the song at index location i
	string get(int i) const 
	{
		assert(i >= 0 && i < size);

		return arr[i];			
	}

	// method append adds string s to the end of Database and size + 1
	void append(const string& s) 
	{
		if(size >= capacity) 
		{
			capacity *= 2;
			string* new_arr = new string[capacity]; // new array with 2x capacity

			for (int i = 0; i < size; i++) 
			{
				new_arr[i] = arr[i]; // copy data into new_arr
			}

			delete[] arr; 
			arr = new_arr; // set the old array to be the new_arr
		}

		arr[size] = s; // assign next element on the right in array to be s
		size++; 
	}
	
	void remove_all(const string& s)
	{
		string* temp = new string[capacity];

		int j = 0;

		for (int i = 0; i < size; i++)
		{
			if (arr[i] != s)
			{
				temp[j] = arr[i];
				j++;
			}
		}
		delete[] arr;
		arr = temp;
		size = j;
	}

	// method for splitting a string up, i.e for getting fields of our records
	void tokenize(const string& s, string* &words)
	{
		int i = 0; // for indexing through words array

	    int start = 0;
    	int end = s.find(',');

		while (end != -1)
		{
			words[i] = s.substr(start, end - start);

			start = end + 1;

			end = s.find(',', start);

			i++;
		}
	}

	// constructor to read our file and store the records in our array, i.e our Database
	Database(const string& fname) 
	: capacity(1000), arr(new string[capacity]), size(0)
	{
		ifstream fin;
		string current_line;
	
		fin.open(fname); // opening file
		getline(fin, current_line); // skip first line

		string* words = new string[20];

		while(fin.good())
		{			
			getline(fin, current_line); // storing each line in our file into current_line

			if (current_line.empty())
			{
				getline(fin,current_line); // skip empty lines
			}
			else
			{
				tokenize(current_line, words); // array of words/values 

				// adding record into the database with the specified fields
				// words[1]: song name, words[2]: artist, words[3]:genre, words[4]: year and words[5]: bpm
				append(words[1] + "," + words[2] + ',' + words[3] + ',' + words[4] + ',' + words[5] + ',');
			}
		}

		delete[] words;

		fin.close();
	}

// ADDING A RECORD --------------------------------------------------------------
	void add_song()
	{
		string title;
		string artist;
		string genre;
		int year;
		int bpm;

		cout << "Title: ";
		getline(cin, title);
		cout << "\n";

		cout << "Artist: ";
		getline(cin, artist);
		cout << "\n";

		cout << "Genre: ";
		getline(cin, genre);
		cout << "\n";

		while (true) 
		{
	        cout << "Year: ";
	        if (cin >> year && year < 2022 && year > 0) 
	        {
	            break;
	        } 
	        else 
	        {
	            cout << "Invalid input for year, try again\n";
	            cin.clear();
	            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
	        }
    	}

		cout << "\n";

		while (true) 
		{
	        cout << "Beats per minute (Bpm): ";
	        if (cin >> bpm && bpm > 0 && bpm < 1000) 
	        {
	            break;
	        } 
	        else 
	        {
	            cout << "Invalid input for bpm, try again\n";
	            cin.clear();
	            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
	        }
    	}

    	cout << "\n";

		// convert first letter of the title/artist of each song as upper case and rest lower case
		// this is to help keep our database consistent 
		for (int i = 0; i < title.size(); i++) 
		{
			if (i == 0)
			{
				title[i] = toupper(title[i]);
			}

			else if (title[i-1] == ' ')
			{
				title[i] = toupper(title[i]);
			}

			else
			{
				title[i] = tolower(title[i]);
			}
		}

		for (int i = 0; i < artist.size(); i++) 
		{
			if (i == 0)
			{
				artist[i] = toupper(artist[i]);
			}

			else if (artist[i-1] == ' ')
			{
				artist[i] = toupper(artist[i]);
			}

			else
			{
				artist[i] = tolower(artist[i]);
			}
		}

		// convert genre to lower case to make it case insensitive since genre in our data is all lower case
		for (int i = 0; i < genre.size(); i++) 
		{
			genre[i] = tolower(genre[i]);
		}

		string record;

		int count = 0;

		record = title + ',' + artist + ',' + genre + ',' + to_string(year) + ',' + to_string(bpm) + ',' ;

		cout << record << endl;

		for (int x = 0; x < size; x++)
		{
			if (arr[x].compare(record) == 0)
			{
				cout << "This song already exists in the database so it will not be added\n\n";
				count++;
				break;
			} 
		}

		string placeholder = "999";
		// reason why I have 999 is because when I downloaded my data it had columns
		// I didn't want to add so I include these as placeholders so it doesn't mess up 
		// my constructor which uses the tokenize function and requires the extra information
		string full_record = placeholder + ',' + title + ',' + artist + ',' + genre + ',' + to_string(year) + ',' + to_string(bpm) + ',' + placeholder;

		// count == 0 means if no records were found with the one I am adding 
		if(count == 0)
		{
			append(full_record); // updating our arr

			ofstream fname;

			fname.open("database.csv", std::ios::app); // open database.csv in append mode

			fname << '\n';

			fname << full_record;

			fname.close(); // close the file

			cout << "Song has been added\n\n";
		}
	} // add_song

// DELETING A RECORD ----------------------------------------------------------
	void delete_record_song_name(const string &s)
	{
		string field = s;
		int count = 0; // keeping track if any record was found

		// convert first letter of each word as upper case and rest lower case to make it case insensitive
		for (int i = 0; i < field.size(); i++) 
		{
			if (i == 0)
			{
				field[i] = toupper(field[i]);
			}

			else if (field[i-1] == ' ')
			{
				field[i] = toupper(field[i]);
			}

			else
			{
				field[i] = tolower(field[i]);
			}
		}

		string* to_delete = new string[500];
		int z = 0;

		// search for field that our user inputted from our database
		for (int j = 0; j < size; j++)
		{
			// get song name field from our database recall fields are song name, artist, genre, year, and bpm
			string* words = new string[20];
			tokenize(arr[j], words);

			if (words[0].find(field) != string::npos && !words[0].empty()) 
			{			
				count++;
				to_delete[z] = arr[j];
				z++;
			}
			delete[] words;
		}

		if (count == 0)
		{
			cout << "No matching song found with the song name: " << field << '\n';
		}
		else if ( count != 0)
		{ 
			// outputting songs to delete
			for ( int k = 0; k < count; k++)
			{
				cout << to_delete[k] << '\n';
			}

			cout << "Enter 'yes' if you want to delete these songs\n";
			cout << "Enter 'no' if you DON'T want to delete these songs\n";

			string response;

			getline(cin,response);

			if (response.compare("yes") == 0)
			{
				string line;
				ifstream fin;
				fin.open("database.csv");

				ofstream temp; // opening temp output file
				temp.open("temp.txt");

				int counter = 0;

				    while (getline(fin, line)) 
				    {
				        // write all lines to temp other than the songs in to_delete
				        for (int x = 0; x < count; x++)
				        {
				        	if (line.find(to_delete[x]) != string::npos)
					        {
					        	counter++;
					        }
					        remove_all(to_delete[x]); // delete all occurances in our arr and resize
				    	}

				    	if (counter == 0)
				    	{
				    		temp << line << endl;
				    	}
				    	counter = 0; // reset counter
				    } // while

				    temp.close();
				    fin.close();

				    // required conversion for remove and rename functions
				    remove("database.csv"); // delete original file
				    rename("temp.txt", "database.csv");

			} // if 'yes'

			else if(response.compare("no") == 0)
			{
				cout << "Okay returning back to the main menu ...\n";
			}
			else
			{
				cout << "Invalid input, returning back to the main menu ...\n";
			}
		}
		delete[] to_delete;
	} // delete_record_song_name


	void delete_record_song_name_full(const string &s)
	{
		string field = s;
		int count = 0; // keeping track if any record was found

		// convert first letter of each word as upper case and rest lower case to make it case insensitive
		for (int i = 0; i < field.size(); i++) 
		{
			if (i == 0)
			{
				field[i] = toupper(field[i]);
			}

			else if (field[i-1] == ' ')
			{
				field[i] = toupper(field[i]);
			}

			else
			{
				field[i] = tolower(field[i]);
			}
		}

		string* to_delete = new string[500];
		int z = 0;

		// search for field that our user inputted from our database
		for (int j = 0; j < size; j++)
		{
			// get song name field from our database recall fields are song name, artist, genre, year, and bpm
			string* words = new string[20];
			tokenize(arr[j], words);

			if (words[0].compare(field) == 0 && !words[0].empty()) 
			{
				count++;
				to_delete[z] = arr[j];
				z++;
			}
			delete[] words;
		}


		if (count == 0)
		{
			cout << "No matching song found with the song name: " << field << '\n';
		}
		else if ( count != 0)
		{ 
			// outputting songs to delete
			for ( int k = 0; k < count; k++)
			{
				cout << to_delete[k] << '\n';
			}

			cout << "Enter 'yes' if you want to delete these songs\n";
			cout << "Enter 'no' if you DON'T want to delete these songs\n";

			string response;

			getline(cin,response);

			if (response.compare("yes") == 0)
			{
				string line;
				ifstream fin;
				fin.open("database.csv");

				ofstream temp; // opening temp output file
				temp.open("temp.txt");

				int counter = 0;

				    while (getline(fin, line)) 
				    {
				        // write all lines to temp other than the songs in to_delete
				        for (int x = 0; x < count; x++)
				        {
				        	if (line.find(to_delete[x]) != string::npos)
					        {
					        	counter++;
					        }
					        remove_all(to_delete[x]); // delete all occurances in our arr and resize
				    	}

				    	if (counter == 0)
				    	{
				    		temp << line << endl;
				    	}
				    	counter = 0; // reset counter
				    } // while

				    temp.close();
				    fin.close();

				    // required conversion for remove and rename functions
				    remove("database.csv"); // delete original file
				    rename("temp.txt", "database.csv");

			} // if 'yes'

			else if(response.compare("no") == 0)
			{
				cout << "Okay returning back to the main menu ...\n";
			}
			else
			{
				cout << "Invalid input, returning back to the main menu ...\n";
			}
		}
		delete[] to_delete;
	} // delete_record_song_name_full


	void delete_record_artist(const string &s)
	{
		string field = s;
		int count = 0; // keeping track if any record was found

		// convert first letter of each word as upper case and rest lower case to make it case insensitive
		for (int i = 0; i < field.size(); i++) 
		{
			if (i == 0)
			{
				field[i] = toupper(field[i]);
			}

			else if (field[i-1] == ' ')
			{
				field[i] = toupper(field[i]);
			}

			else
			{
				field[i] = tolower(field[i]);
			}
		}

		string* to_delete = new string[500];
		int z = 0;

		// search for field that our user inputted from our database
		for (int j = 0; j < size; j++)
		{
			// get song name field from our database recall fields are song name, artist, genre, year, and bpm
			string* words = new string[20];
			tokenize(arr[j], words);

			if (words[1].find(field) != string::npos && !words[1].empty()) 
			{
				count++;
				to_delete[z] = arr[j];
				z++;
			}
			delete[] words;
		}

		if (count == 0)
		{
			cout << "No matching song found with the artist: " << field << '\n';
		}
		else if ( count != 0)
		{ 
			// outputting songs to delete
			for ( int k = 0; k < count; k++)
			{
				cout << to_delete[k] << '\n';
			}

			cout << "Enter 'yes' if you want to delete these songs\n";
			cout << "Enter 'no' if you DON'T want to delete these songs\n";

			string response;

			getline(cin,response);

			if (response.compare("yes") == 0)
			{
				string line;
				ifstream fin;
				fin.open("database.csv");

				ofstream temp; // opening temp output file
				temp.open("temp.txt");

				int counter = 0;

				    while (getline(fin, line)) 
				    {
				        // write all lines to temp other than the songs in to_delete
				        for (int x = 0; x < count; x++)
				        {
				        	if (line.find(to_delete[x]) != string::npos)
					        {
					        	counter++;
					        }
					        remove_all(to_delete[x]); // delete all occurances in our arr and resize
				    	}

				    	if (counter == 0)
				    	{
				    		temp << line << endl;
				    	}
				    	counter = 0; // reset counter
				    } // while

				    temp.close();
				    fin.close();

				    // required conversion for remove and rename functions
				    remove("database.csv"); // delete original file
				    rename("temp.txt", "database.csv");

			} // if 'yes'

			else if(response.compare("no") == 0)
			{
				cout << "Okay returning back to the main menu ...\n";
			}
			else
			{
				cout << "Invalid input, returning back to the main menu ...\n";
			}
		}
		delete[] to_delete;
	} // delete_record_artist


	void delete_record_artist_full(const string &s)
	{
		string field = s;
		int count = 0; // keeping track if any record was found

		// convert first letter of each word as upper case and rest lower case to make it case insensitive
		for (int i = 0; i < field.size(); i++) 
		{
			if (i == 0)
			{
				field[i] = toupper(field[i]);
			}

			else if (field[i-1] == ' ')
			{
				field[i] = toupper(field[i]);
			}

			else
			{
				field[i] = tolower(field[i]);
			}
		}

		string* to_delete = new string[500];
		int z = 0;

		// search for field that our user inputted from our database
		for (int j = 0; j < size; j++)
		{
			// get song name field from our database recall fields are song name, artist, genre, year, and bpm
			string* words = new string[20];
			tokenize(arr[j], words);

			if (words[1].compare(field) == 0 && !words[1].empty()) 
			{
				count++;
				to_delete[z] = arr[j];
				z++;
			}
			delete[] words;
		}

		if (count == 0)
		{
			cout << "No matching song found with the artist: " << field << '\n';
		}
		else if ( count != 0)
		{ 
			// outputting songs to delete
			for ( int k = 0; k < count; k++)
			{
				cout << to_delete[k] << '\n';
			}

			cout << "Enter 'yes' if you want to delete these songs\n";
			cout << "Enter 'no' if you DON'T want to delete these songs\n";

			string response;

			getline(cin,response);

			if (response.compare("yes") == 0)
			{
				string line;
				ifstream fin;
				fin.open("database.csv");

				ofstream temp; // opening temp output file
				temp.open("temp.txt");

				int counter = 0;

				    while (getline(fin, line)) 
				    {
				        // write all lines to temp other than the songs in to_delete
				        for (int x = 0; x < count; x++)
				        {
				        	if (line.find(to_delete[x]) != string::npos)
					        {
					        	counter++;
					        }
					        remove_all(to_delete[x]); // delete all occurances in our arr and resize
				    	}

				    	if (counter == 0)
				    	{
				    		temp << line << endl;
				    	}
				    	counter = 0; // reset counter
				    } // while

				    temp.close();
				    fin.close();

				    // required conversion for remove and rename functions
				    remove("database.csv"); // delete original file
				    rename("temp.txt", "database.csv");

			} // if 'yes'

			else if(response.compare("no") == 0)
			{
				cout << "Okay returning back to the main menu ...\n";
			}
			else
			{
				cout << "Invalid input, returning back to the main menu ...\n";
			}
		}
		delete[] to_delete;
	} // delete_record_artist_full


	void delete_record_genre(const string &s)
	{
		string field = s;
		int count = 0; // keeping track if any record was found

		// convert to lower case to make it case insensitive since genre in our data is all lower case
		for (int i = 0; i < field.size(); i++) 
		{
			field[i] = tolower(field[i]);
		}

		string* to_delete = new string[500];
		int z = 0;

		// search for field that our user inputted from our database
		for (int j = 0; j < size; j++)
		{
			// get song name field from our database recall fields are song name, artist, genre, year, and bpm
			string* words = new string[20];
			tokenize(arr[j], words);

			if (words[2].find(field) != string::npos && !words[2].empty()) 
			{
				count++;
				to_delete[z] = arr[j];
				z++;
			}
			delete[] words;
		}


		if (count == 0)
		{
			cout << "No matching song found with the genre: " << field << '\n';
		}
		else if ( count != 0)
		{ 
			// outputting songs to delete
			for ( int k = 0; k < count; k++)
			{
				cout << to_delete[k] << '\n';
			}

			cout << "Enter 'yes' if you want to delete these songs\n";
			cout << "Enter 'no' if you DON'T want to delete these songs\n";

			string response;

			getline(cin,response);

			if (response.compare("yes") == 0)
			{
				string line;
				ifstream fin;
				fin.open("database.csv");

				ofstream temp; // opening temp output file
				temp.open("temp.txt");

				int counter = 0;

				    while (getline(fin, line)) 
				    {
				        // write all lines to temp other than the songs in to_delete
				        for (int x = 0; x < count; x++)
				        {
				        	if (line.find(to_delete[x]) != string::npos)
					        {
					        	counter++;
					        }
					        remove_all(to_delete[x]); // delete all occurances in our arr and resize
				    	}

				    	if (counter == 0)
				    	{
				    		temp << line << endl;
				    	}
				    	counter = 0; // reset counter
				    } // while

				    temp.close();
				    fin.close();

				    // required conversion for remove and rename functions
				    remove("database.csv"); // delete original file
				    rename("temp.txt", "database.csv");

			} // if 'yes'

			else if(response.compare("no") == 0)
			{
				cout << "Okay returning back to the main menu ...\n";
			}
			else
			{
				cout << "Invalid input, returning back to the main menu ...\n";
			}
		}
		delete[] to_delete;
	} // delete_record_genre


	void delete_record_genre_full(const string &s)
	{
		string field = s;
		int count = 0; // keeping track if any record was found

		// convert to lower case to make it case insensitive since genre in our data is all lower case
		for (int i = 0; i < field.size(); i++) 
		{
			field[i] = tolower(field[i]);
		}

		string* to_delete = new string[500];
		int z = 0;

		// search for field that our user inputted from our database
		for (int j = 0; j < size; j++)
		{
			// get song name field from our database recall fields are song name, artist, genre, year, and bpm
			string* words = new string[20];
			tokenize(arr[j], words);

			if (words[2].compare(field) == 0 && !words[2].empty()) 
			{
				count++;
				to_delete[z] = arr[j];
				z++;
			}
			delete[] words;
		}


		if (count == 0)
		{
			cout << "No matching song found with the genre: " << field << '\n';
		}
		else if ( count != 0)
		{ 
			// outputting songs to delete
			for ( int k = 0; k < count; k++)
			{
				cout << to_delete[k] << '\n';
			}

			cout << "Enter 'yes' if you want to delete these songs\n";
			cout << "Enter 'no' if you DON'T want to delete these songs\n";

			string response;

			getline(cin,response);

			if (response.compare("yes") == 0)
			{
				string line;
				ifstream fin;
				fin.open("database.csv");

				ofstream temp; // opening temp output file
				temp.open("temp.txt");

				int counter = 0;

				    while (getline(fin, line)) 
				    {
				        // write all lines to temp other than the songs in to_delete
				        for (int x = 0; x < count; x++)
				        {
				        	if (line.find(to_delete[x]) != string::npos)
					        {
					        	counter++;
					        }
					        remove_all(to_delete[x]); // delete all occurances in our arr and resize
				    	}

				    	if (counter == 0)
				    	{
				    		temp << line << endl;
				    	} 
				    	counter = 0; // reset counter
				    } // while

				    temp.close();
				    fin.close();

				    // required conversion for remove and rename functions
				    remove("database.csv"); // delete original file
				    rename("temp.txt", "database.csv");

			} // if 'yes'

			else if(response.compare("no") == 0)
			{
				cout << "Okay returning back to the main menu ...\n";
			}
			else
			{
				cout << "Invalid input, returning back to the main menu ...\n";
			}
		}
		delete[] to_delete;
	} // delete_record_genre_full


	void delete_record_year(int s)
	{

		int count = 0; // keeping track if any record was found

		string* to_delete = new string[500];
		int z = 0;

		// search for field that our user inputted from our database
		for (int j = 0; j < size; j++)
		{
			// get song name field from our database recall fields are song name, artist, genre, year, and bpm
			string* words = new string[20];
			tokenize(arr[j], words);

			if (stoi(words[3]) == s && !words[3].empty()) 
			{
				count++;
				to_delete[z] = arr[j];
				z++;
			}
			delete[] words;
		}

		if (count == 0)
		{
			cout << "No matching song found with the year: " << s << '\n';
		}
		else if ( count != 0)
		{ 
			// outputting songs to delete
			for ( int k = 0; k < count; k++)
			{
				cout << to_delete[k] << '\n';
			}

			cout << "Enter 'yes' if you want to delete these songs\n";
			cout << "Enter 'no' if you DON'T want to delete these songs\n";

			string response;

			getline(cin,response);

			if (response.compare("yes") == 0)
			{
				string line;
				ifstream fin;
				fin.open("database.csv");

				ofstream temp; // opening temp output file
				temp.open("temp.txt");

				int counter = 0;

				    while (getline(fin, line)) 
				    {
				        // write all lines to temp other than the songs in to_delete
				        for (int x = 0; x < count; x++)
				        {
				        	if (line.find(to_delete[x]) != string::npos)
					        {
					        	counter++;
					        }
					        remove_all(to_delete[x]); // delete all occurances in our arr and resize
				    	}

				    	if (counter == 0)
				    	{
				    		temp << line << endl;
				    	}
				    	counter = 0; // reset counter
				    } // while

				    temp.close();
				    fin.close();

				    // required conversion for remove and rename functions
				    remove("database.csv"); // delete original file
				    rename("temp.txt", "database.csv");

			} // if 'yes'

			else if(response.compare("no") == 0)
			{
				cout << "Okay returning back to the main menu ...\n";
			}
			else
			{
				cout << "Invalid input, returning back to the main menu ...\n";
			}
		}

		delete[] to_delete;
	} // delete_record_year


	void delete_record_bpm(int s)
	{

		int count = 0; // keeping track if any record was found

		string* to_delete = new string[500];
		int z = 0;

		// search for field that our user inputted from our database
		for (int j = 0; j < size; j++)
		{
			// get song name field from our database recall fields are song name, artist, genre, year, and bpm
			string* words = new string[20];
			tokenize(arr[j], words);

			if (stoi(words[4]) == s && !words[4].empty()) 
			{
				count++;
				to_delete[z] = arr[j];
				z++;
			}
			delete[] words;
		}

		if (count == 0)
		{
			cout << "No matching song found with the year: " << s << '\n';
		}
		else if ( count != 0)
		{ 
			// outputting songs to delete
			for ( int k = 0; k < count; k++)
			{
				cout << to_delete[k] << '\n';
			}

			cout << "Enter 'yes' if you want to delete these songs\n";
			cout << "Enter 'no' if you DON'T want to delete these songs\n";

			string response;

			getline(cin,response);

			if (response.compare("yes") == 0)
			{
				string line;
				ifstream fin;
				fin.open("database.csv");

				ofstream temp; // opening temp output file
				temp.open("temp.txt");

				int counter = 0;

				    while (getline(fin, line)) 
				    {
				        // write all lines to temp other than the songs in to_delete
				        for (int x = 0; x < count; x++)
				        {
				        	if (line.find(to_delete[x]) != string::npos)
					        {
					        	counter++;
					        }
					        remove_all(to_delete[x]); // delete all occurances in our arr and resize
				    	}

				    	if (counter == 0)
				    	{
				    		temp << line << endl;
				    	}
				    	counter = 0; // reset counter
				    } // while

				    temp.close();
				    fin.close();

				    // required conversion for remove and rename functions
				    remove("database.csv"); // delete original file
				    rename("temp.txt", "database.csv");

			} // if 'yes'

			else if(response.compare("no") == 0)
			{
				cout << "Okay returning back to the main menu ...\n";
			}
			else
			{
				cout << "Invalid input, returning back to the main menu ...\n";
			}
		}

		delete[] to_delete;
	} // delete_record_bpm


	void delete_record_year_range(int s, int n)
	{
		assert(s <= n); // check if range is properly inputted

		int count = 0; // keeping track if any record was found

		string* to_delete = new string[500];
		int z = 0;

		// search for field that our user inputted from our database
		for (int j = 0; j < size; j++)
		{
			// get song name field from our database recall fields are song name, artist, genre, year, and bpm
			string* words = new string[20];
			tokenize(arr[j], words);

			if (stoi(words[3]) >= s && stoi(words[3]) <= n && !words[3].empty()) 
			{
				count++;
				to_delete[z] = arr[j];
				z++;
			}
			delete[] words;
		}

		if (count == 0)
		{
			cout << "No matching song found within the years: " << s << " to " << n << '\n';
		}
		else if ( count != 0)
		{ 
			// outputting songs to delete
			for ( int k = 0; k < count; k++)
			{
				cout << to_delete[k] << '\n';
			}

			cout << "Enter 'yes' if you want to delete these songs\n";
			cout << "Enter 'no' if you DON'T want to delete these songs\n";

			string response;

			getline(cin,response);

			if (response.compare("yes") == 0)
			{
				string line;
				ifstream fin;
				fin.open("database.csv");

				ofstream temp; // opening temp output file
				temp.open("temp.txt");

				int counter = 0;

				    while (getline(fin, line)) 
				    {
				        // write all lines to temp other than the songs in to_delete
				        for (int x = 0; x < count; x++)
				        {
				        	if (line.find(to_delete[x]) != string::npos)
					        {
					        	counter++;
					        }
					        remove_all(to_delete[x]); // delete all occurances in our arr and resize
				    	}

				    	if (counter == 0)
				    	{
				    		temp << line << endl;
				    	}
				    	counter = 0; // reset counter
				    } // while

				    temp.close();
				    fin.close();

				    // required conversion for remove and rename functions
				    remove("database.csv"); // delete original file
				    rename("temp.txt", "database.csv");

			} // if 'yes'

			else if(response.compare("no") == 0)
			{
				cout << "Okay returning back to the main menu ...\n";
			}
			else
			{
				cout << "Invalid input, returning back to the main menu ...\n";
			}
		}

		delete[] to_delete;
	} // delete_record_year_range


	void delete_record_bpm_range(int s, int n)
	{
		assert(s <= n); // check if range is properly inputted

		int count = 0; // keeping track if any record was found

		string* to_delete = new string[500];
		int z = 0;

		// search for field that our user inputted from our database
		for (int j = 0; j < size; j++)
		{
			// get song name field from our database recall fields are song name, artist, genre, year, and bpm
			string* words = new string[20];
			tokenize(arr[j], words);

			if (stoi(words[4]) >= s && stoi(words[4]) <= n && !words[4].empty()) 
			{
				count++;
				to_delete[z] = arr[j];
				z++;
			}
			delete[] words;
		}

		if (count == 0)
		{
			cout << "No matching song found within the bpm: " << s << " to " << n << '\n';
		}
		else if ( count != 0)
		{ 
			// outputting songs to delete
			for ( int k = 0; k < count; k++)
			{
				cout << to_delete[k] << '\n';
			}

			cout << "Enter 'yes' if you want to delete these songs\n";
			cout << "Enter 'no' if you DON'T want to delete these songs\n";

			string response;

			getline(cin,response);

			if (response.compare("yes") == 0)
			{
				string line;
				ifstream fin;
				fin.open("database.csv");

				ofstream temp; // opening temp output file
				temp.open("temp.txt");

				int counter = 0;

				    while (getline(fin, line)) 
				    {
				        // write all lines to temp other than the songs in to_delete
				        for (int x = 0; x < count; x++)
				        {
				        	if (line.find(to_delete[x]) != string::npos)
					        {
					        	counter++;
					        }
					        remove_all(to_delete[x]); // delete all occurances in our arr and resize
				    	}

				    	if (counter == 0)
				    	{
				    		temp << line << endl;
				    	}
				    	counter = 0; // reset counter
				    } // while

				    temp.close();
				    fin.close();

				    // required conversion for remove and rename functions
				    remove("database.csv"); // delete original file
				    rename("temp.txt", "database.csv");

			} // if 'yes'

			else if(response.compare("no") == 0)
			{
				cout << "Okay returning back to the main menu ...\n";
			}
			else
			{
				cout << "Invalid input, returning back to the main menu ...\n";
			}
		}

		delete[] to_delete;
	} // delete_record_bpm_range



// FINDING A RECORD METHODS ---------------------------------------------------
	// searches database for songs using its partial name 
	void get_song_name(const string& s)
	{
		string song_name = s;
		int count = 0; // keeping track if any record was found

		// convert first letter of each word as upper case and rest lower case to make it case insensitive
		for (int i = 0; i < song_name.size(); i++) 
		{
			if (i == 0)
			{
				song_name[i] = toupper(song_name[i]);
			}

			else if (song_name[i-1] == ' ')
			{
				song_name[i] = toupper(song_name[i]);
			}

			else
			{
				song_name[i] = tolower(song_name[i]);
			}
		}

		// search for song_name that our user inputted from our database
		for (int j = 0; j < size; j++)
		{
			// get song name field from our database recall fields are song name, artist, genre, year, and bpm
			string* words = new string[20];
			tokenize(arr[j], words);

			if (words[0].find(song_name) != string::npos) 
			{
				count++;
				cout << arr[j] << '\n'; // print record if found
			}
			delete[] words;
		}

		if (count == 0)
		{
			cout << "No matching song found with the name: " << song_name << '\n';
		}
	} // get_song_name

	// searches database for songs using exact name
	void get_full_song_name(const string& s)
	{
		string song_name = s;
		int count = 0; // keeping track if any record was found

		// convert first letter of each word as upper case and rest lower case to make it case insensitive
		for (int i = 0; i < song_name.size(); i++) 
		{
			if (i == 0)
			{
				song_name[i] = toupper(song_name[i]);
			}

			else if (song_name[i-1] == ' ')
			{
				song_name[i] = toupper(song_name[i]);
			}

			else
			{
				song_name[i] = tolower(song_name[i]);
			}
		}

		// search for song_name that our user inputted from our database
		for (int j = 0; j < size; j++)
		{
			// get song name field from our database recall fields are song name, artist, genre, year, and bpm
			string* words = new string[20];
			tokenize(arr[j], words);

			if (words[0].compare(song_name) == 0) 
			{
				count++;
				cout << arr[j] << '\n'; // print record if found
			}
			delete[] words;
		}

		if (count == 0)
		{
			cout << "No matching song found with the name: " << song_name << '\n';
		}
	} // get_full_song_name

	// searches database for songs using partial artist name
	void get_artist(const string& s)
	{
		string artist = s;
		int count = 0; // keeping track if any record was found

		// convert first letter of each word as upper case and rest lower case to make it case insensitive
		for (int i = 0; i < artist.size(); i++) 
		{
			if (i == 0)
			{
				artist[i] = toupper(artist[i]);
			}

			else if (artist[i-1] == ' ')
			{
				artist[i] = toupper(artist[i]);
			}

			else
			{
				artist[i] = tolower(artist[i]);
			}
		}

		// search for artist that our user inputted from our database
		for (int j = 0; j < size; j++)
		{
			// get artist field from our database recall fields are song name, artist, genre, year, and bpm
			string* words = new string[20];
			tokenize(arr[j], words);

			if (words[1].find(artist) != string::npos) 
			{
				count++;
				cout << arr[j] << '\n'; // print record if found
			}
			delete[] words;
		}

		if (count == 0)
		{
			cout << "No matching song found with the artist: " << artist << '\n';
		}
	} // get_artist

	// searches database for songs using exact artist name
	void get_full_artist(const string& s)
	{
		string artist = s;
		int count = 0; // keeping track if any record was found

		// convert first letter of each word as upper case and rest lower case to make it case insensitive
		for (int i = 0; i < artist.size(); i++) 
		{
			if (i == 0)
			{
				artist[i] = toupper(artist[i]);
			}

			else if (artist[i-1] == ' ')
			{
				artist[i] = toupper(artist[i]);
			}

			else
			{
				artist[i] = tolower(artist[i]);
			}
		}

		// search for song_name that our user inputted from our database
		for (int j = 0; j < size; j++)
		{
			// get song name field from our database recall fields are song name, artist, genre, year, and bpm
			string* words = new string[20];
			tokenize(arr[j], words);

			if (words[1].compare(artist) == 0) 
			{
				count++;
				cout << arr[j] << '\n'; // print record if found
			}
			delete[] words;
		}

		if (count == 0)
		{
			cout << "No matching song found with the artist: " << artist << '\n';
		}
	} // get_full_artist

	// searches database for songs with partial genre
	void get_genre(const string& s)
	{
		string genre = s;
		int count = 0; // keeping track if any record was found

		// convert to lower case to make it case insensitive since genre in our data is all lower case
		for (int i = 0; i < genre.size(); i++) 
		{
			genre[i] = tolower(genre[i]);
		}

		// search for genre that our user inputted from our database
		for (int j = 0; j < size; j++)
		{
			// get genre field from our database recall fields are song name, artist, genre, year, and bpm
			string* words = new string[20];
			tokenize(arr[j], words);

			if (words[2].find(genre) != string::npos) 
			{
				count++;
				cout << arr[j] << '\n'; // print record if found
			}
			delete[] words;
		}

		if (count == 0)
		{
			cout << "No matching song found with the genre: " << genre << '\n';
		}
	} // get_genre


	// searches database for songs using its FULL name
	void get_full_genre(const string& s)
	{
		string genre = s;
		int count = 0; // keeping track if any record was found

		// conver to lower case to make it case insensitive since genre in our data is all lower case
		for (int i = 0; i < genre.size(); i++) 
		{
			genre[i] = tolower(genre[i]);
		}


		// search for genre that our user inputted from our database
		for (int j = 0; j < size; j++)
		{
			// get song name field from our database recall fields are song name, artist, genre, year, and bpm
			string* words = new string[20];
			tokenize(arr[j], words);

			if (words[2].compare(genre) == 0) 
			{
				count++;
				cout << arr[j] << '\n'; // print record if found
			}
			delete[] words;
		}

		if (count == 0)
		{
			cout << "No matching song found with the genre: " << genre << '\n';
		}
	} // get_full_genre


	void get_year(int s)
	{
		int count = 0; // keeping track if any record was found

		// search for year that our user inputted from our database
		for (int j = 0; j < size; j++)
		{
			// get year field from our database recall fields are song name, artist, genre, year, and bpm
			string* words = new string[20];
			tokenize(arr[j], words);

			if (stoi(words[3]) == s) 
			{
				count++;
				cout << arr[j] << '\n'; // print record if found
			}
			delete[] words;
		}

		if (count == 0)
		{
			cout << "No matching song found with the year: " << s << '\n';
		}
	} // get_year

	// searches all songs within the year range specified
	void get_year_range(int s, int n)
	{
		assert(s <= n); // check if range is properly inputted

		int count = 0; // keeping track if any record was found

		// search for year that our user inputted from our database
		for (int j = 0; j < size; j++)
		{
			// get year field from our database recall fields are song name, artist, genre, year, and bpm
			string* words = new string[20];
			tokenize(arr[j], words);

			if (stoi(words[3]) >= s && stoi(words[3]) <= n) 
			{
				count++;
				cout << arr[j] << '\n'; // print record if found
			}
			delete[] words;
		}

		if (count == 0)
		{
			cout << "No matching song found within the years: " << s << " to " << n << '\n';
		}
	} // get_year_range


	void get_bpm(int s)
	{
		int count = 0; // keeping track if any record was found

		// search for bpm that our user inputted from our database
		for (int j = 0; j < size; j++)
		{
			// get bpm field from our database recall fields are song name, artist, genre, year, and bpm
			string* words = new string[20];
			tokenize(arr[j], words);

			// cout<<words[4]<<'\n';

			if (stoi(words[4]) == s) 
			{
				count++;
				cout << arr[j] << '\n'; // print record if found
			}
			delete[] words;
		}

		if (count == 0)
		{
			cout << "No matching song found with the bpm: " << s << '\n';
		}
	} // get_bpm

	// searches all songs within the bpm range specified
	void get_bpm_range(int s, int n)
	{
		assert(s <= n);

		int count = 0; // keeping track if any record was found

		// search for year that our user inputted from our database
		for (int j = 0; j < size; j++)
		{
			// get year field from our database recall fields are song name, artist, genre, year, and bpm
			string* words = new string[20];
			tokenize(arr[j], words);

			if (stoi(words[4]) >= s && stoi(words[4]) <= n) 
			{
				count++;
				cout << arr[j] << '\n'; // print record if found
			}
			delete[] words;
		}

		if (count == 0)
		{
			cout << "No matching song found within the bpm range: " << s << " to " << n << '\n';
		}
	} // get_bpm_range


// LISTING RECORDS METHODS -----------------------------------------------------------
	// listing in alphabetical order
	void song_names_alpha()
	{
		string* new_arr = new string[capacity]; 

		for (int i = 0; i < size; i++) 
		{
			new_arr[i] = arr[i]; // copy data into new_arr
		}

		string* words = new string[20];

		string* words2 = new string[20];

		string temp;

		for (int j = 0; j < size; j++)
		{
			for (int k = j+1; k < size; k++)
			{
				tokenize(new_arr[j], words);
				tokenize(new_arr[k], words2);

				if (words[0][0] > words2[0][0]) // first letter of each song name 
				{				
					temp = new_arr[j];
					new_arr[j] = new_arr[k];
					new_arr[k] = temp;
				}
			}
		}

		for ( int l = 0; l<size; l++)
		{
			cout << new_arr[l]<<'\n';
		}

		delete[] new_arr;
		delete[] words;
		delete[] words2;
	} // song_names_alpha


	void song_names_alpha_reversed()
	{
		string* new_arr = new string[capacity]; 

		for (int i = 0; i < size; i++) 
		{
			new_arr[i] = arr[i]; // copy data into new_arr
		}

		string* words = new string[20];

		string* words2 = new string[20];

		string temp;

		for (int j = 0; j < size; j++)
		{
			for (int k = j+1; k < size; k++)
			{
				tokenize(new_arr[j], words);
				tokenize(new_arr[k], words2);

				if (words[0][0] < words2[0][0]) // first letter of each song name 
				{				
					temp = new_arr[j];
					new_arr[j] = new_arr[k];
					new_arr[k] = temp;
				}
			}
		}

		for ( int l = 0; l<size; l++)
		{
			cout << new_arr[l]<<'\n';
		}

		delete[] new_arr;
		delete[] words;
		delete[] words2;
	} // song_names_alpha_reversed


	void artist_names_alpha()
	{
		string* new_arr = new string[capacity]; 

		for (int i = 0; i < size; i++) 
		{
			new_arr[i] = arr[i]; // copy data into new_arr
		}

		string* words = new string[20];

		string* words2 = new string[20];

		string temp;

		for (int j = 0; j < size; j++)
		{
			for (int k = j+1; k < size; k++)
			{
				tokenize(new_arr[j], words);
				tokenize(new_arr[k], words2);

				if (words[1][0] > words2[1][0]) // first letter of each artist  
				{				
					temp = new_arr[j];
					new_arr[j] = new_arr[k];
					new_arr[k] = temp;
				}
			}
		}

		for ( int l = 0; l<size; l++)
		{
			cout << new_arr[l]<<'\n';
		}

		delete[] new_arr;
		delete[] words;
		delete[] words2;
	} // artist_names_alpha


	void artist_names_alpha_reversed()
	{
		string* new_arr = new string[capacity]; 

		for (int i = 0; i < size; i++) 
		{
			new_arr[i] = arr[i]; // copy data into new_arr
		}

		string* words = new string[20];

		string* words2 = new string[20];

		string temp;

		for (int j = 0; j < size; j++)
		{
			for (int k = j+1; k < size; k++)
			{
				tokenize(new_arr[j], words);
				tokenize(new_arr[k], words2);

				if (words[1][0] < words2[1][0]) // first letter of each artist  
				{				
					temp = new_arr[j];
					new_arr[j] = new_arr[k];
					new_arr[k] = temp;
				}
			}
		}

		for ( int l = 0; l<size; l++)
		{
			cout << new_arr[l]<<'\n';
		}

		delete[] new_arr;
		delete[] words;
		delete[] words2;
	} // artist_names_alpha_reversed


	void genre_names_alpha()
	{
		string* new_arr = new string[capacity]; 

		for (int i = 0; i < size; i++) 
		{
			new_arr[i] = arr[i]; // copy data into new_arr
		}

		string* words = new string[20];

		string* words2 = new string[20];

		string temp;

		for (int j = 0; j < size; j++)
		{
			for (int k = j+1; k < size; k++)
			{
				tokenize(new_arr[j], words);
				tokenize(new_arr[k], words2);

				if (words[2][0] > words2[2][0]) // first letter of each genre  
				{				
					temp = new_arr[j];
					new_arr[j] = new_arr[k];
					new_arr[k] = temp;
				}
			}
		}

		for ( int l = 0; l<size; l++)
		{
			cout << new_arr[l]<<'\n';
		}

		delete[] new_arr;
		delete[] words;
		delete[] words2;
	} // genre_names_alpha


	void genre_names_alpha_reversed()
	{
		string* new_arr = new string[capacity]; 

		for (int i = 0; i < size; i++) 
		{
			new_arr[i] = arr[i]; // copy data into new_arr
		}

		string* words = new string[20];

		string* words2 = new string[20];

		string temp;

		for (int j = 0; j < size; j++)
		{
			for (int k = j+1; k < size; k++)
			{
				tokenize(new_arr[j], words);
				tokenize(new_arr[k], words2);

				if (words[2][0] < words2[2][0]) // first letter of each genre  
				{				
					temp = new_arr[j];
					new_arr[j] = new_arr[k];
					new_arr[k] = temp;
				}
			}
		}

		for ( int l = 0; l<size; l++)
		{
			cout << new_arr[l]<<'\n';
		}

		delete[] new_arr;
		delete[] words;
		delete[] words2;
	} // genre_names_alpha_reversed


	void year_ascending()
	{
		string* new_arr = new string[capacity]; 

		for (int i = 0; i < size; i++) 
		{
			new_arr[i] = arr[i]; // copy data into new_arr
		}

		string* words = new string[20];

		string* words2 = new string[20];

		string temp;

		for (int j = 0; j < size; j++)
		{
			for (int k = j+1; k < size; k++)
			{
				tokenize(new_arr[j], words);
				tokenize(new_arr[k], words2);

				if (words[3] > words2[3]) // comparing the years  
				{				
					temp = new_arr[j];
					new_arr[j] = new_arr[k];
					new_arr[k] = temp;
				}
			}
		}

		for ( int l = 0; l<size; l++)
		{
			cout << new_arr[l]<<'\n';
		}

		delete[] new_arr;
		delete[] words;
		delete[] words2;
	} // year_ascending


	void year_descending()
	{
		string* new_arr = new string[capacity]; 

		for (int i = 0; i < size; i++) 
		{
			new_arr[i] = arr[i]; // copy data into new_arr
		}

		string* words = new string[20];

		string* words2 = new string[20];

		string temp;

		for (int j = 0; j < size; j++)
		{
			for (int k = j+1; k < size; k++)
			{
				tokenize(new_arr[j], words);
				tokenize(new_arr[k], words2);

				if (words[3] < words2[3]) // comparing the years  
				{				
					temp = new_arr[j];
					new_arr[j] = new_arr[k];
					new_arr[k] = temp;
				}
			}
		}

		for ( int l = 0; l<size; l++)
		{
			cout << new_arr[l]<<'\n';
		}

		delete[] new_arr;
		delete[] words;
		delete[] words2;
	} // year_descending


	void bpm_ascending()
	{
		string* new_arr = new string[capacity]; 

		for (int i = 0; i < size; i++) 
		{
			new_arr[i] = arr[i]; // copy data into new_arr
		}

		string* words = new string[20];

		string* words2 = new string[20];

		string temp;

		for (int j = 0; j < size; j++)
		{
			for (int k = j+1; k < size; k++)
			{
				tokenize(new_arr[j], words);
				tokenize(new_arr[k], words2);

				//cout << words[4] << '\n';

				if (stoi(words[4]) > stoi(words2[4])) // comparing the bpm 
				{				
					temp = new_arr[j];
					new_arr[j] = new_arr[k];
					new_arr[k] = temp;
				}
			}
		}

		for ( int l = 0; l<size; l++)
		{
			cout << new_arr[l]<<'\n';
		}

		delete[] new_arr;
		delete[] words;
		delete[] words2;
	} // bpm_ascending


	void bpm_descending()
	{
		string* new_arr = new string[capacity]; 

		for (int i = 0; i < size; i++) 
		{
			new_arr[i] = arr[i]; // copy data into new_arr
		}

		string* words = new string[20];

		string* words2 = new string[20];

		string temp;

		for (int j = 0; j < size; j++)
		{
			for (int k = j+1; k < size; k++)
			{
				tokenize(new_arr[j], words);
				tokenize(new_arr[k], words2);

				if (stoi(words[4]) < stoi(words2[4])) // comparing the bpm  
				{				
					temp = new_arr[j];
					new_arr[j] = new_arr[k];
					new_arr[k] = temp;
				}
			}
		}

		for ( int l = 0; l<size; l++)
		{
			cout << new_arr[l]<<'\n';
		}

		delete[] new_arr;
		delete[] words;
		delete[] words2;
	} // bpm_descending

}; // Class Database
