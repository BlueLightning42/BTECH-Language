#include "BTECH.h"
using namespace BTECH;

std::set <char> ops = {'+','-','/','*','%','&','(',')','>','<','^','|','=','!',':'};
//token initializers




//first step is the parser will tokenize the file
void program::build_program(std::string f){
	// parse input into token array

	std::ifstream file(f.c_str());
	if(!file){
		std::cout << "file not found";
		return;
	}
	std::string line;
	char next_character;
	while (!file.eof()){
		next_character = file.get();
		if (next_character == '#') {  // Stealing comment syntax from python
			// comment out whole line
			file.ignore(10000,'\n');

		}else if (next_character == '"') {  // build strings "
			getline(file, line,'"');
			tokens.push_back(new _string(line));

		}else if (next_character == '\'') {  // build strings '
			getline(file, line,'\'');
			tokens.push_back(new _string(line));

		}else if (next_character == '\n' ) {  // end of commands
			if(tokens.back()->name != "EOL")//ignore multiple newlines
				tokens.push_back(new _generic_token("EOL"));

		}else if (next_character == '\\' ) {  // end of commands
			file.ignore(1);//ignore backslash lines

		}else if (next_character == ' ' || next_character == '\t' || next_character == EOF) {  // end of commands
			continue;

		}else if (ops.find(next_character) != ops.end()) {  // build operators (single char)
			tokens.push_back(new _operator(next_character));

		}else if (next_character == 'i' && isdigit(file.peek())) {  // build operators
			getline(file, line,' ');
			//tokens.push_back(new _number(line)); //TODO figure out complex later

		}else  if (next_character == '.' || isdigit(next_character)){
		// build numbers
			line = "";
			while(next_character == '.' || isdigit(next_character)){
				line += next_character; //file.get() not working?
				next_character = file.get();
			}
			if(next_character != EOF) file.unget();
			
			tokens.push_back(new _generic_token(line));

			if (1 == 1){//contains a decimal
				//tokens.push_back(new _number(std::stod(line)));	
			}else{
				//tokens.push_back(new _number(std::stoi(line)));
			}

		}else{  // build everything else
			line = "";
			while(next_character != ' ' && next_character != '\n' && next_character != '\t' && next_character != EOF && ops.find(next_character) == ops.end()){
				line += next_character; //file.get() not working?
				next_character = file.get();
			}
			if(next_character != EOF) file.unget();
			
			tokens.push_back(new _generic_token(line));
		}
	}file.close();
	if (tokens.back()->name_is("EOL"))
		tokens.pop_back();
	tokens.push_back(new _generic_token("EOF"));

	
	if(debug){
		std::cout << "Tokenizing sucessfull";
	}
	if(debug > 1){
		std::cout << ".\n->Tokens generated:\n  ";
		for(auto i: tokens){
			std::cout << *i << "  "; 
		}
	}std::cout << '.' << std::endl;//flush
	build_ast();
};
