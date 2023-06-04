## Final Project: A Database

In this project, your task is to create a **database**, containing data of
your choice, that can search, sort, and add/delete data. All the data in the
database consists of **records**, and each record consists of **fields** of
different types. For example, if your database is storing songs, then its
records might have fields for the song name (a string), the artist (a string),
and the year of publication (a whole number).

Your record must have **at least three fields**, and at least one field must
be a string, and at least one field must be a number. Please note this is the
minimal size of a record, and more fields are encouraged.

You should make your database about something you're interested in. For
example, your records could be songs, movies, books, games, celebrities,
sports teams, etc.

## General Implementation Constraints

Please use standard C++ techniques as discussed in the course. 

**Important!** You *cannot* use `vector`, or any other C++ "container" class
from the STL or elsewhere. Instead, we want you to re-use and modify your
dynamic array class from assignment 3 to work with this assignment.

**Do not** use raw C++ arrays directly. We are using C++, not C, and we want
to see you take advantage of C++ features. Again, re-use the class you wrote
for assignment 3.

Not being allowed to use `vector` or similar classes might seem like a strange
constraint. In "real life" you would definitely use `vector`, or any other
class that makes sense. But the purpose of this course is to understand the
low-level details that go into coding classes such as `vector`. We want to see
that you can do this, not just call pre-made code.
