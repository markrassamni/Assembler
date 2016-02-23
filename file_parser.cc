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
	///cout << "Parsing file: " << s << endl;
}
file_parser::~file_parser() {}

int current_line = 0;

void file_parser::read_file() {

	/* ***** TEST CASE ***** */
	// Check if file exists
	string line;
	ifstream file_reader (filename.c_str());
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
		//cout << "line_data[" << i << "]: " << line_data << endl;
		parse_line(line_data);
		current_line++;

		//cout << "Label: " << line_vector[i].label << endl;
		//cout << "Opcode: " << line_vector[i].opcode << endl;
		//cout << "Operand: " << line_vector[i].operand << endl;
		//cout << "Comment: " << line_vector[i].comment << endl;
		//cout << line_vector[i].comment << endl;
	}//end-for
  	
	
	
}

int is_label = 0;
int is_opcode = 0;
int is_operand = 0;

void file_parser::parse_line(string s){
	string line = s;


	//int line_size = line.length();
	bool is_comment = 0;
	bool is_quoted = 0;
	
	is_label = 0;
	is_opcode = 0;
	is_operand = 0;


	/* ***** TEST CASE ***** */
	// Label must begin in column 0
	if(isspace(line[0])){
	 is_label++;
	 is_opcode = 1;
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
		  		// cout << "Label: " << word << endl;
		  		 line_vector[current_line].label = word;
		  		 is_opcode = 1;
		  		 break;
		  	case 2: // Opcode
		  		//cout << "Opcode: " << word << endl;
		  		line_vector[current_line].opcode = word;
		  		is_opcode = 0; is_operand = 1;
		  		break;
		  	case 3: // Operand
		  		//cout << "Operand: " << word << endl;
		  		line_vector[current_line].operand = word;
		  		break;
		  	default:
		  		throw file_parse_exception("Invalid Token: " + word
		  			+ ", Could not identify token type.");
		  		break;

		   }//end-switch
		 is_label++;
		}//end-while
		//cout<< "Comment: " << line_vector[current_line].comment << endl;
	
}

int file_parser::token_type(string s){
	string token = s;

	if(s[0] == '.') return 0;
	else if(valid_label(s)) return 1;
	else if(valid_opcode(s)) return 2;
	else if(valid_operand(s)) return 3;
	else return 4;
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

int file_parser::valid_opcode(string s){
		string token = s;
		if(is_opcode == 1){
			return 1;
		}
 return 0;
}

int file_parser::valid_operand(string s){
		string token = s;
		if(is_operand == 1){
			is_operand++;
			return 1;
		}
 return 0;
}

string file_parser::get_token(unsigned int row, unsigned int col)
	{
		//cout << line_vector[row].operand << endl;

		string line = file_vector[row];
		int column = col;

		int i = 0;
		string word;
		istringstream iss(line, istringstream::in);
		while( (i <= col) && (iss >> word)){
			i++;
		}

		if(word.at(0) == '.') column = 3; 

		switch(column){
			case 0 : return line_vector[row].label; break;
			case 1 : return line_vector[row].opcode; break;
			case 2 : return line_vector[row].operand; break;
			case 3 : return line_vector[row].comment; break;
			default: return " "; 
		}
	}  

void file_parser::print_file() {
	// Iterate through Line_vector
	for (unsigned i=0; i< size(); i++){
		string line_data = file_vector[i]; //
		cout << line_data << endl;
		current_line++;

	
	}//end-for
}


//private methods


void file_parser::get_line_tokens (int line_number, string the_line) {}
