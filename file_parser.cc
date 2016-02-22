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

int is_label = 0;

void file_parser::parse_line(string s){
	string line = s;


	//int line_size = line.length();
	bool is_comment = 0;
	bool is_quoted = 0;
	is_label = 0;

	/* ***** TEST CASE ***** */
	// Label must begin in column 0
	if(isspace(line[0])){
	 is_label++;
	}

		string word; 
		string temp;
		
		istringstream iss(line, istringstream::in);
		/* ***** TEST CASE ***** */
		// Must be a whitespace between each of the four fields
		while( iss >> word )     
		{

		  int token_key = token_type(word);

		  /* ***** TEST CASE ***** */
		  // When period is encountered rest of line is a comment
		  if(is_comment){
		  	// Can be problematic because it assumes comments are single spaced between words
		  	 word = temp + ' ' + word;
		  	 token_key = 0;
		  }
		  else if(is_quoted){

		  }

		  switch(token_key){
		  	case 0:	// Comment
		  		line_vector[current_line].comment = word;
		  		is_comment = 1;
		  		temp = word;
		  		//cout << line_vector[current_line].comment << endl;
		  		break;
		  	case 1: // Label
				  /* ***** TEST CASE ***** */
				  // Only first eight characters of a label are used
		  	     word = word.substr(0,8);	
		  		 cout << "Label: " << word << endl;
		  		 line_vector[current_line].label = word;
		  		 break;
		  	default:
		  		//cout << "Token: " << word << endl;
		  		is_comment = 0;
		  		break;

		   }//end-switch
		 is_label++;
		}//end-while

	
}

int file_parser::token_type(string s){
	string token = s;

	if(s[0] == '.') return 0;
	else if(valid_label(s)){  
		return 1;
	}
	else return 2;
}

int file_parser::valid_label(string s){
	
	string token = s;
	if(is_label == 0){			// Begins in Column 0
		if(isalpha(token[0])){	// First Character is a letter /*TESTCASE*/
			int i =0;
			while(i < token.length()) {
				if(!(isdigit(token[i]) || isalpha(token[i]))) // Must be Digits and Letters /*TESTCASE*/
					throw file_parse_exception("Invalid Label: " + token + 
						", Label must consist of digits and letters(a-z A-Z 0-9)");
			i++;
			}
		return 1;
		}
		else throw file_parse_exception("Invalid Label: " + token + " , First "
			+ "character must be a letter");
	}
 return 0;
}


string file_parser::get_token(unsigned int row, unsigned int col)
	{return "Testing";}  
void file_parser::print_file() {}


//private methods


void file_parser::get_line_tokens (int line_number, string the_line) {}