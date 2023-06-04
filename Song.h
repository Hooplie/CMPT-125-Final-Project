// Song.h

#include <iostream>        
#include <string>
#include <cassert>

using namespace std;

class Song {

	// fields of a record, i.e a song
	string record;
	string name;
	string artist;
	string genre;
	int year;
	int bpm;

public:

	// constructor for storing a single record consisting of the fields name, artist, genre, year and bpm
	Song(const string& name, const string& artist, const string& genre, int year, int bpm)
	: name(name), artist(artist), genre(genre), year(year), bpm(bpm)
	{ }

	string get_full_record()
	{
		cout << "test";
		record = name + ',' + artist + ',' + genre + ',' + to_string(year) + ',' + to_string(bpm) + ',';
		return record;
	}
}; // class Song

