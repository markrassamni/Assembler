/*	Alex Buitimea, Nick Phimmasone, Tyler Nguyen, Mark Rassamni
	masc0892
	team Connecticut
	prog2
	opcodetab.h
	CS530, Spring 2016
*/


//Your opcode_error_exception class should a a single constructor that take a string argument, and a string getMessage() method that returns the message passed to the constructor when thrown.

#ifndef OPCODE_ERROR_EXCEPTION_H
#define OPCODE_ERROR_EXCEPTION_H

#include <string>

using namespace std;

class opcode_error_exception {

public:
	opcode_error_exception(string message) {
		this->message = message;
	}

	opcode_error_exception() {
		message = "An error has occurred.";
	}

	string getMessage(){
		return message;
	}

private:
	string message;
};

#endif
