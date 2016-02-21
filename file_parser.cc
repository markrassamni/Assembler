#include "file_parser.h"
#include "file_parse_exception.h"

using namespace std;

//public methods
file_parser::file_parser(string s) {}
file_parser::~file_parser() {}
void file_parser::read_file() {}
string file_parser::get_token(unsigned int row, unsigned int col)
	{return "Hello";}
void file_parser::print_file() {}
int file_parser::size() { return 1;}

//private methods
void file_parser::read_in_source_file() {}
void file_parser::process_lines() {}
void file_parser::get_line_tokens (int line_number, string the_line) {}