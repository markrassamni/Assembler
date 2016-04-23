/*
 * symtab.cpp
 *
 *  Created on: Apr 22, 2016
 *      Author: markrassamni
 */

#include "symtab.h"

void symtab::new_sym(string sym, string val){
	if(!exists(sym)){
		m[sym] = val;
	}
	else{
		throw symtab_exception("This symbol is already defined.");
	}
}
//void symtab::equ() EQU LATER



string symtab::string_to_hex(string s){
	istringstream instr(s);
	int x;
	instr >> x;
	stringstream out;
	out<<setw(5)<<setfill('0')<<hex<<x;
	return out.str();
}
