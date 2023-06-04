// final_project.cpp

#include "Song.h"
#include "Database.h"
#include "Menu.h"
#include <cassert>
#include <string>

using namespace std;

// testing functions
void Database_test() 
{
  cout << "Database_test() ... \n";

  Database empty_db; // { }
  
  assert(empty_db.get_size() ==  0);
  assert(empty_db.get_capacity() == 1000);
  assert(empty_db.get_arr() != nullptr);


  Database db("database.csv"); 

  // prints the name, artist, genre, year, bpm, and nrgy
  // for ( int i = 0; i < db.get_size(); i++ ) 
  // {
  // 	cout << db.get(i) << "\n";
  // }

  // testing whether the arr got updated
  // string* print_arr = db.get_arr();

  // for (int i = 0; i < db.get_size(); i++)
  // {
  //   cout << print_arr[i] << "\n";
  // }

  // db.get_song_name("hey soul");

  // db.get_full_song_name("hey soul sister");

  // db.get_artist("beyon");

  // db.get_full_artist("beyonce");

  // db.get_genre("rap");

  // db.get_full_genre("electronic trap");

  // db.get_year(2019);

  // db.get_year_range(2018, 2019);

  // db.get_bpm(136);

  // db.get_bpm_range(120,1360);

  // db.song_names_alpha();

  // db.song_names_alpha_reversed();

  // db.artist_names_alpha();

  // db.artist_names_alpha_reversed();

  // db.genre_names_alpha();

  // db.genre_names_alpha_reversed();

  // db.year_ascending();

  // db.year_descending();

  // db.bpm_ascending();

  // db.bpm_descending();

  // db.add_song();

  // db.delete_record_song_name("no brainer");

  // db.delete_record_song_name_full("kiLlS you slOwly");

  // db.delete_record_artist("Linkin");

  // db.delete_record_artist_full("linkin park");

  // db.delete_record_genre("pop");

  // db.delete_record_genre_full("elect");

  // db.delete_record_year(2019);

  // db.delete_record_bpm(518);

  // db.delete_record_year_range(2020,2020);

  // db.delete_record_bpm_range(100,110);

  cout << "\nDatabase_test() passed\n\n";
}


void Song_test()
{
  cout << "Song_test() ... \n";

  // Song entry{"Beautiful Mistakes (feat. Megan Thee Stallion)", "Maroon 5", "Pop", 2021, 99};

  // string record = entry.get_full_record();

  // cout<< record << endl;

  cout << "\nSong_test() passed\n\n";
}


int main()
{
  // calling test functions here
	// Database_test();
  // Song_test(); 

  // main program
  Database db("database.csv"); // reading records/songs from csv file

  string user_input; 
  string find;
  string range;
  
  Menu menu{}; // opening the menu

  while(true)
  {
    getline(cin, user_input);

    if (user_input == "1") // INPUT 1: ADDING A SONG 
    {
      menu.add_song(); 
      db.add_song();
    } // INPUT "1" ADDING A SONG

    else if(user_input == "2") // INPUT 2: FINDING A SONG
    {
      menu.find_song(); // outputting find song submenu 

      getline(cin, user_input); // for submenu user inputs below

      if(user_input == "1") // find song using exact song name
      {
        cout << "Enter the name of the song:\n";
        getline(cin,user_input); 
        db.get_full_song_name(user_input);
        menu.main_menu(); 
      }
      else if(user_input == "2") // find the song using exact artist name
      {
        cout << "Enter the name of the artist:\n";
        getline(cin,user_input);
        db.get_full_artist(user_input);
        menu.main_menu(); 
      }
      else if(user_input == "3") // find the song using exact genre
      {
        cout << "Enter the genre:\n";
        getline(cin,user_input);
        db.get_full_genre(user_input);
        menu.main_menu(); 
      }
      else if(user_input == "4") // find the song using exact year
      {
        cout << "Enter the year:\n";
        getline(cin,user_input);
        db.get_year(stoi(user_input));
        menu.main_menu(); 
      }
      else if(user_input == "5") // find the song using exact bpm
      {
        cout << "Enter the beats per minute:\n";
        getline(cin,user_input);
        db.get_bpm(stoi(user_input));
        menu.main_menu(); 
      }
      else if(user_input == "6") // find the song using partial song name
      {
        cout << "Enter the name of the song:\n";
        getline(cin,user_input);
        db.get_song_name(user_input);
        menu.main_menu(); 
      }
      else if(user_input == "7") // find the song using partial artist name
      {
        cout << "Enter the name of the artist:\n";
        getline(cin,user_input);
        db.get_artist(user_input);
        menu.main_menu(); 
      }
      else if(user_input == "8") // find the song using partial genre
      {
        cout << "Enter the genre:\n";
        getline(cin,user_input);
        db.get_genre(user_input);
        menu.main_menu(); 
      }
      else if(user_input == "9") // find the songs using a range of years
      {
        cout << "Enter the year you wish to start at\n";
        getline(cin,user_input);
        cout << "Enter the year your wish to end at\n";
        getline(cin,range);
        db.get_year_range(stoi(user_input),stoi(range));
        menu.main_menu(); 
      }
      else if(user_input == "10") // find the songs using a range of bpm
      {
        cout << "Enter the beats per minute you wish to start at:\n";
        getline(cin,user_input);
        cout << "Enter the beats per minute you wish to start at:\n";
        getline(cin,range);
        db.get_bpm_range(stoi(user_input),stoi(range));
        menu.main_menu(); 
      }
      else if(user_input == "R") // to return to main menu
      {
        menu.main_menu();
      }
      // if user inputs none of the options from the main menu 
      else if(user_input != "1" || user_input != "2" || user_input != "3" || user_input != "4" || user_input != "5" ||
              user_input != "6" || user_input != "7" || user_input != "8" || user_input != "9" || user_input != "10" || user_input != "R")
      {
        menu.invalid_input(user_input);
      }
    } // INPUT "2" FINDING SONG 

    else if(user_input == "3") // INTPUT 3: DELETING A SONG 
    {
      menu.delete_song(); 
      getline(cin,user_input);

      if(user_input == "1") // delete song using exact song name
      {
        cout << "Enter the name of the song:\n";
        getline(cin,user_input); 
        db.delete_record_song_name_full(user_input);
        menu.main_menu(); 
      }
      else if(user_input == "2") // delete song using exact artist name
      {
        cout << "Enter the name of the artist:\n";
        getline(cin,user_input);
        db.delete_record_artist_full(user_input);
        menu.main_menu(); 
      }
      else if(user_input == "3") // delete song using exact genre
      {
        cout << "Enter the genre:\n";
        getline(cin,user_input);
        db.delete_record_genre_full(user_input);
        menu.main_menu(); 
      }
      else if(user_input == "4") // delete song using exact year
      {
        cout << "Enter the year:\n";
        getline(cin,user_input);
        db.delete_record_year(stoi(user_input));
        menu.main_menu(); 
      }
      else if(user_input == "5") // find the song using exact bpm
      {
        cout << "Enter the beats per minute:\n";
        getline(cin,user_input);
        db.delete_record_bpm(stoi(user_input));
        menu.main_menu(); 
      }
      else if(user_input == "6") // delete song using partial song name
      {
        cout << "Enter the name of the song:\n";
        getline(cin,user_input);
        db.delete_record_song_name(user_input);
        menu.main_menu(); 
      }
      else if(user_input == "7") // delete song using partial artist name
      {
        cout << "Enter the name of the artist:\n";
        getline(cin,user_input);
        db.delete_record_artist(user_input);
        menu.main_menu(); 
      }
      else if(user_input == "8") // delete song using partial genre
      {
        cout << "Enter the genre:\n";
        getline(cin,user_input);
        db.delete_record_genre(user_input);
        menu.main_menu(); 
      }
      else if(user_input == "9") // delete songs using a range of years
      {
        cout << "Enter the year you wish to start at\n";
        getline(cin,user_input);
        cout << "Enter the year your wish to end at\n";
        getline(cin,range);
        db.delete_record_year_range(stoi(user_input),stoi(range));
        menu.main_menu(); 
      }
      else if(user_input == "10") // delete songs using a range of bpm
      {
        cout << "Enter the beats per minute you wish to start at:\n";
        getline(cin,user_input);
        cout << "Enter the beats per minute you wish to start at:\n";
        getline(cin,range);
        db.delete_record_bpm_range(stoi(user_input),stoi(range));
        menu.main_menu(); 
      }
      else if(user_input == "R") // to return to main menu
      {
        menu.main_menu();
      }
      // if user inputs none of the options from the main menu 
      else if(user_input != "1" || user_input != "2" || user_input != "3" || user_input != "4" || user_input != "5" ||
              user_input != "6" || user_input != "7" || user_input != "8" || user_input != "9" || user_input != "10" || user_input != "R")
      {
        menu.invalid_input(user_input);
      }
    } // INPUT "3" DELETING A SONG

    else if(user_input == "4") // INPUT 4: LISTING SONGS
    {
      menu.list_song();
      getline(cin,user_input);
      if (user_input == "1") // list alphabetically by song name
      {
        db.song_names_alpha();
        menu.main_menu();
      }
      else if (user_input == "2") // list alphabetically by artist
      {
        db.artist_names_alpha();
        menu.main_menu();
      }
      else if (user_input == "3") // list alphabetically by genre
      {
        db.genre_names_alpha();
        menu.main_menu();
      }
      else if (user_input == "4") // list reverse alphabetically by song name
      {
        db.song_names_alpha_reversed();
        menu.main_menu();
      }
      else if (user_input == "5") // list reverse alphabetically by artist
      {
        db.artist_names_alpha_reversed();
        menu.main_menu();
      }
      else if (user_input == "6") // list reverse alphabetically by genre
      {
        db.genre_names_alpha_reversed();
        menu.main_menu();
      }
      else if (user_input == "7") // list ascending order by year
      {
        db.year_ascending();
        menu.main_menu();
      }
      else if (user_input == "8") // list ascending order by beats per minute
      {
        db.bpm_ascending();
        menu.main_menu();
      }
      else if (user_input == "9") // list descending order by year
      {
        db.year_descending();
        menu.main_menu();
      }
      else if (user_input == "10") // list descending order by beats per minute
      {
        db.bpm_descending();
        menu.main_menu();
      }
      else if(user_input == "R") // to return to main menu
      {
        menu.main_menu();
      }
      // if user inputs none of the options from the main menu 
      else if(user_input != "1" || user_input != "2" || user_input != "3" || user_input != "4" || user_input != "5" ||
              user_input != "6" || user_input != "7" || user_input != "8" || user_input != "9" || user_input != "10" || user_input != "R")
      {
        menu.invalid_input(user_input);
      }
    } // INPUT "4" LISTING SONGS

    else if(user_input == "5") // INTPUT 4: QUIT PROGRAM 
    {
      menu.quit_menu(); // exiting program
      return 0;
    } // INPUT "5" QUIT PROGRAM

    // if user inputs none of the options from the main menu 
    else if(user_input != "1" || user_input != "2" || user_input != "3" || user_input != "4" || user_input != "5")
    {
      menu.invalid_input(user_input);
    }
    else // always want to return back to the main menu 
    {
      menu.main_menu();
    }
 
 } // while

  return 0;
}