/*	Alex Buitimea, Nick Phimmasone, Tyler Nguyen, Mark Rassamni
	masc0892
	team Connecticut
	prog2
	opcodetab.cc
	CS530, Spring 2016
*/
#include <string>
#include <map>

#include "opcodetab.h"
#include "opcode_error_exception.h"

using namespace std;

// ctor
        // creates a new dictionary structure and loads all of the opcodes for 
        // the SIC/XE architecture into the table.  Use the STL
        // map for this.
opcodetab::opcodetab(){
	//Create Table/Map and Load all Value of Opcodes
	for (unsigned int i =0; i < NUM_OF_OPS; i++ ){
		opcodes[mnemonics[i]] = Data(ops[i], formats[i]);
	}
}; 
        
        // takes a SIC/XE opcode and returns the machine code 
        // equivalent as a two byte string in hexadecimal.
        // Example:  get_machine_code("ADD") returns the value 18
        // Note that opcodes may be prepended with a '+'.
        // throws an opcode_error_exception if the opcode is not 
        // found in the table.
string opcodetab::get_machine_code(string s){
	 /* ***** TEST CASE ***** */
	// Assembler is not case sensitive
	string op = s;

	// Remove '+' if found 
	  if(op[0] == '+'){
	  	op = op.substr(1);
	  }
	//Change op to all upper case
	  int i = 0;
	  while (op[i])
	  {
	    op[i] = toupper(op[i]);
	    i++;
	  }
	  

	  // If the opcode is found, set an iterator to the position of the opcode
	  // in otherwords return the position of the opcode
	  opcode_it = opcodes.find(op);

	  //If no opcode matches then throw and error
	  if(opcode_it == opcodes.end()){
	  	throw opcode_error_exception("Could not find opcode: " + op);
	  }
 	
	return(opcode_it->second.machine_code);


}; 
        
        // takes a SIC/XE opcode and returns the number of bytes 
        // needed to encode the instruction, which is an int in
        // the range 1..4.
        // NOTE: the opcode must be prepended with a '+' for format 4.
        // throws an opcode_error_exception if the opcode is not 
        // found in the table.        
int opcodetab::get_instruction_size(string s){
	string op = s;
	bool plus = false;

	// Test Case: the opcode must be prepended with a '+' for format 4.
      if(op[0] == '+'){
      	op = op.substr(1);
      	plus = true;
      }

    //Change op to all upper case
	int i = 0;
	  while (op[i])
	  {
	    op[i] = toupper(op[i]);
	    i++;
	  }

	  

       // If the opcode is found, set an iterator to the position of the opcode
	  // in otherwords return the position of the opcode
	  opcode_it = opcodes.find(op);
	  if(opcode_it == opcodes.end())
	  	throw opcode_error_exception("Could not find opcode: " + op);
	  else if(plus){
	  	if(opcode_it->second.format != 3)
	  		throw opcode_error_exception("+" + op + " is not a valid format to be extended with '+'.");
	  	else
	  		return 4;
	  }else
	  	return (opcode_it->second.format);

}

