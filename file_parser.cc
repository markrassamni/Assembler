#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "file_parser.h"
#include "file_parse_exception.h"

using namespace std;

//public methods
file_parser::file_parser(string s) {
	filename = s;
	cout << "Parsing file: " << s << endl;
}
file_parser::~file_parser() {}

int current_line = 0;

void file_parser::read_file() {

	/* ***** TEST CASE ***** */
	// Check if file exists
	string line;
	ifstream file_reader (filename);
	if (file_reader.is_open())
	  {
	  	int i = 0; 												/* remove */
	    while ( getline (file_reader,line) )
	    {
	     //Pass in lines into vector < ln1, ln2, ln2,...,lnk >
	     //cout << line << '\n';
	    	file_vector.push_back(line);
	    	//cout << "Vector[" << i << "]: " << line << endl; 	/* remove */
	    	i++;												/* remove */
	    }
	    file_reader.close();
	    process_lines();
	  }

  else //cout << "Unable to open file" << '\n'; 
  {
  	throw file_parse_exception("Unable to open file: " + filename);
  }
}

int file_parser::size() { return file_vector.size();}


void file_parser::process_lines() {
	// Iterate through File_vector
	for (unsigned i=0; i< size(); i++){
		string line_data = file_vector[i];
		
		line_vector.push_back(data());



	}//end-for
    
    // Iterate through Line_vector
	for (unsigned i=0; i< size(); i++){
		string line_data = file_vector[i]; //
		cout << "line_data[" << i << "]: " << line_data << endl;
		parse_line(line_data);
		
		//cout << line_vector[i].comment << endl;
	}//end-for
  	
	
	
}

void file_parser::parse_line(string s){
	string line = s;
	//int line_size = line.length();

		string word; 
		string temp;
		bool is_comment = 0;
		istringstream iss(line, istringstream::in);
		//True when there is not a blank space
		while( iss >> word )     
		{
		  /* ***** TEST CASE ***** */
		  // When period is encountered rest of line is a comment
		  
		  int token_key = token_type(word);

		  if(is_comment){
		  	 word = temp + ' ' + word;
		  	 token_key = 0;
		  }

		  switch(token_key){
		  	case 0:	// Comment
		  		line_vector[current_line].comment = word;
		  		is_comment = 1;
		  		temp = word;
		  		cout << line_vector[current_line].comment << endl;
		  		break;
		  	default:
		  		cout << "Token default" << endl;
		  		is_comment = 0;
		  		break;

		   }//end-switch

		}//end-while

	
}

int file_parser::token_type(string s){
	string token = s;

	if(s[0] == '.') return 0;
	else return 1;
}


string file_parser::get_token(unsigned int row, unsigned int col)
	{return "Testing";}  
void file_parser::print_file() {}


//private methods


void file_parser::get_line_tokens (int line_number, string the_line) {}