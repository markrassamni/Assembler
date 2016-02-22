#include <iostream>
#include <fstream>

#include "file_parser.h"
#include "file_parse_exception.h"

using namespace std;

//public methods
file_parser::file_parser(string s) {
	filename = s;
	cout << "Parsing file: " << s << endl;
}
file_parser::~file_parser() {}


void file_parser::read_file() {

	/* ***** TEST CASE ***** */
	// Check if file exists
	string line;
	  ifstream myfile (filename);
	  if (myfile.is_open())
	  {
	    while ( getline (myfile,line) )
	    {
	      cout << line << '\n';
	    }
	    myfile.close();
	  }

  else //cout << "Unable to open file" << '\n'; 
  {
  	throw file_parse_exception("Unable to open file: " + filename);
  }
}
string file_parser::get_token(unsigned int row, unsigned int col)
	{return "Testing";}  
void file_parser::print_file() {}
int file_parser::size() { return 1;}

//private methods
void file_parser::read_in_source_file() {}
void file_parser::process_lines() {}
void file_parser::get_line_tokens (int line_number, string the_line) {}