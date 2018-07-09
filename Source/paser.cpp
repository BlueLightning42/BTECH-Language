#include "BTECH.h"
#include <set>
#include <fstream>
#include <iostream>


std::set <char> ops = {'+','-','/','*','%','&','(',')','>','<','^','|','=','!'};
_string::_string(std::string c): token("string"), contents(c) {}

void program::build_program(std::string f){
	// parse input into token array

	std::ifstream file(f.c_str());
	if(!file){
		std::cout << "file not found";
		return;
	}
	std::string line;
	while (!file.eof()){
		if (file.peek() == '#') {  // Stealing comment syntax from python
			// comment out whole line
			file.ignore(10000,'\n');

		}else if (file.peek() == '"') {  // build strings
			getline(file, line,'"');
			tokens.push_back(new _string(line));

		}else if (file.peek() == '\'') {  // build strings
			getline(file, line,'\'');
			tokens.push_back(new _string(line));

		}else if (file.peek() == '\\' && file.peek()-1 != '\\') {  // end of commands
			tokens.push_back(new token("EOL"));

		}else if (ops.find(file.peek()) != ops.end()) {  // build operators
			tokens.push_back(new _operator(file.get()));

		}else if (file.peek() == 'i' && isdigit(file.peek()+1)) {  // build operators
			tokens.push_back(new _operator(file.get()));

		}else  if (file.peek() == '.' || isdigit(file.peek())){
		// build numbers
			getline(file, line,' ');
			if ( line.find('.') != line.end() ){//contains a decimal
				tokens.push_back(new _double(std::stod(line));	
			}else{
				tokens.push_back(new std::stoi(line));
			}

		}else{  // build everything else
			getline(file, line,' ');
			tokens.push_back(new token(line));

		}

	}file.close()
	tokens.push_back(new token("EOF"));
	std::cout << "Tokenizing sucessfull";
	build_ast();
};
