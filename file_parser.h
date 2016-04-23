/*  file_parser.h
    CS530, Spring 2016
*/

#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include <string>
#include <vector>

using namespace std;

class file_parser {
    public:
        // ctor, filename is the parameter.  A driver program will read
        // the filename from the command line, and pass the filename to
        // the file_parser constructor.  Filenames must not be hard-coded.
        file_parser(string);

        // dtor
        ~file_parser();

        // reads the source file, storing the information is some
        // auxiliary data structure you define in the private section.
        // Throws a file_parse_exception if an error occurs.
        // if the source code file fails to conform to the above
        // specification, this is an error condition.
        void read_file();

        // returns the token found at (row, column).  Rows and columns
        // are zero based.  Returns the empty string "" if there is no
        // token at that location. column refers to the four fields
        // identified above.
        string get_token(unsigned int, unsigned int);

        // prints the source code file to stdout.  Should not repeat
        // the exact formatting of the original, but uses tabs to align
        // similar tokens in a column. The fields should match the
        // order of token fields given above (label/opcode/operands/comments)
        void print_file();

        // returns the number of lines in the source code file
        int size();



    private:

        // returns the file specified at runtime
        string filename;



        // structure to hold data of each line
        struct data{
            string label;
            string opcode;
            string operand;
            string comment;
        };



        // reads the vector structure and iterates through each item and
        // stores information of each item into a vector structure to store
        // in a struct data
        void process_lines();


        // reads a line and returns the type of tokens it contains.
        void parse_line(string s);

        // reads a token and determines type
        int token_type(string s);


        // data structure to hold all the lines of the file provided
        vector<string> file_vector;

        // data structure to hold stuct with data on each line
        vector<data> line_vector;

        //Checks against the rules specified if they can be tokens
        int valid_label(string s);
        int valid_opcode(string s);
        int valid_operand(string s);



};

#endif
