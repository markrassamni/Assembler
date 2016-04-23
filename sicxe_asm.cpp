/*
 * sicxeasm.cpp
 *
 *  Created on: Apr 22, 2016
 *      Author: markrassamni
 */

#include "sicxe_asm.h"

void sicxe_asm::asm_directives(string op, string operand, int index) {
	int val;
	string tmp_op = uppercase(op);
	//int size = dir_size.find(tmp_op)->pass2; // Size given in pass 2
	if(tmp_op == "START") {
				start = 1;
				val = strip_to_hex(operand);
				asm_address = val;
	}
	else if(tmp_op == "END"){
		vec.push_back(data);
		//break;
	}
	else if(tmp_op == "BYTE") { //***** 2nd PASS
		start = 1;
		int l = operand.length() - 3; // length of operand, removes 3 vals (c/x, and the 's)

		if(operand[0] == 'X' || operand[0] == 'x') { //reserve half of hex digits as bytes
			if(l % 2 == 0)
				asm_address += l/2;
			else
				asm_address += (l/2) + 1;
		}
		else if(operand[0] == 'C' || operand[0] == 'c') //reserve # characters as bytes
			asm_address += l;
		else
			asm_address++; //if no c/x, add 1 byte
	}
	else if(tmp_op == "WORD"){
		start = 1;
		asm_address += 3;
	}
	else if(tmp_op == "RESB"){
		start = 1;
		val = hex(operand);
		asm_address += val;
	}
	else if(tmp_op == "RESW"){
		start = 1;
		val = hex(operand);
		asm_address += (3 * val);
	}
	else if(tmp_op == "BASE") {
				base_operand = operand;
				base = 1;
	}
	else if(tmp_op == "NOBASE")
				base = -1;
//EQU ????
}
void sicxe_asm::addresses(file_parser parse) {
	for(int i = 1; i < parse.size(); i++) {
		assign(parse, i);
		string check_dir = upper(data.opcode);

			if(m_asm_directives.find(check_dir) != m_asm_directives.end()) //if opcode is assembly directive
				asm_directives(data.opcode, data.operand, i);
			else{
				if(data.operand[1] == '#'){  //???????
					ss << "Error on line: " << i << ". Invalid operand.";
					throw symtab_exception(ss.str());
				}
				if(start == -1 && !(data.opcode[0] == '.' || data.opcode.size == 0)) {
					ss << "Error on line: " << i << ". Invalid operation! Opcode operation before Start.";
					throw opcode_error_exception(ss.str());
				}
				else if(start != -1 && !(data.opcode[0] == '.' || data.opcode.size == 0)) {
					try {  // ERROR SETTING ADDRESS
						//string op = data.opcode;
						//asm_address += opcodetab::get_instruction_size(op);
						//asm_address += opcodetab::get_instruction_size(data.opcode);
						//opcodetab size(data.opcode);
						//asm_address += size.get_instruction_size(data.opcode);
						asm_address += opcode.get_instruction_size(data.opcode);
					}
					catch(opcode_error_exception ox) {
						cerr << "An Opcode error has occurred at line " << i  << ": " << ox.getMessage() << endl;
					}
				}
			}
		symtab::new_sym(data.address, data.label, data.operand);
		vec.push_back(data);
	}
}

void sicxe_asm::pass1(string filename){
	file_parser parse(filename);
	parse.read_file();
	addresses(parse);
}

void sicxe_asm::pass2() {

}

void sicxe_asm::output(string filename) {

}


void sicxe_asm::assign(file_parser parse, int row) {
		data.label = parse.get_token(row,0);
		data.opcode = parse.get_token(row,1);
		data.operand = parse.get_token(row,2);
		data.address = format_string(asm_address);
}


void sicxe_asm::dir_size() { //Not used******
	m_asm_directives["START"] = 0;
	m_asm_directives["END"] = 0;
	m_asm_directives["BYTE"] = 1;
	m_asm_directives["WORD"] = 3;
	m_asm_directives["RESB"] = 1;
	m_asm_directives["RESW"] = 3;
	m_asm_directives["BASE"] = 0;
	m_asm_directives["NOBASE"] = 0;
	m_asm_directives["EQU"] = 0;

/*	reg["A"] = "0";
	reg["X"] = "1";
	reg["L"] = "2";
	reg["B"] = "3";
	reg["S"] = "4";
	reg["T"] = "5";
	reg["PC"] = "8";
	reg["SW"] = "9";	*/
}

int sicxe_asm::strip_to_hex(string s) {
	int val;
	if(s[0] == '$' || s[0] == '#' || s[0] == '@')
		s.erase(0,1);
	sscanf(s.c_str(),"%X",&val);
	return val;

}
int sicxe_asm::hex(string s) {
	int val;
		if(s[0] == '$' || s[0] == '#' || s[0] == '@') {
			s.erase(0,1);
		}
	 	stringstream str_val;
	 	str_val << s;
	 	str_val >> val;
	 	return val;
}


string sicxe_asm::uppercase(string s){
	transform(s.begin(),s.end(),s.begin(),::toupper);
	return s;
}

int main(int argc, char *argv[]) {
	string file = argv[1];

	try {
	 	sicxe_asm assembler(file);
	 	}
	catch(symtab_exception sx) {
 		cerr << "An error has occurred: " << sx.getMessage() << endl;
 	}
	return 0;
}
