#include "BTECH.h"
#include <set>
#include <fstream>
using namespace BTECH;

std::set <char> ops = {'+','-','/','*','%','&','(',')','>','<','^','|','=','!',':'};
//token initializers
token::token(std::string s): name(s) {}
void token::print(std::ostream& os) const{std::cout <<"ERROR: IMPOSIBLE TO REACH THIS";} // should never reach
//default Unknown
_generic_token::_generic_token(std::string n="Unknown Token"): token(n) {} 
_string::_string(std::__cxx11::string c): token("string"), contents(c) {}
_operator::_operator(char t): token("op"), _type(t) {}
//_number::_number(N n): token("number"), value(n) {}
//_number::get_value() const {return value} //getter for numbers

//boilerplate for printing tokens?
std::ostream& operator<< (std::ostream& os, const token& tok) {

    tok.print(os); //call print method of derived class
    return os;
}
void _generic_token::print(std::ostream& os) const{
	os <<'[' << this->name << "] ";
	if (this->name == "EOL"){
		os << std::endl;
	}
}
void _operator::print(std::ostream& os) const{
	os <<'['<<this->name << "(" << this->_type << ")] ";
}
void _string::print(std::ostream& os) const{
	os <<'['<< this->name << " \"" << this->contents << "\"]";
}
/*
void _number::print(std::ostream& os) const{
	os << this->get_value() << " ";
}*/
// etc...






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
			/*int start = file.tellg();
			std::string temp = std::string(std::istreambuf_iterator<char>(file),std::istreambuf_iterator<char>());
			int end = temp.find_first_not_of("1234567890.",start);
			int length = (start-end);
			std::cout << length;
			char * buff = new char[length];
			file.read(buff,length);
			line = std::string(buff);
			delete[] buff;*/

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

	tokens.push_back(new _generic_token("EOF"));

	

	if(debug){
		std::cout << "Tokenizing sucessfull.\nTokens generated:\n  ";
		for(std::vector<token *>::iterator i = tokens.begin(); i != tokens.end(); i++){
			std::cout << **i << "  "; 
			// took me ages to figure out I had to double * it to get the value not the pointer
			// int* b = new int(210);
			// std::cout << *b << std::endl;
		}
	}
	build_ast();
};
