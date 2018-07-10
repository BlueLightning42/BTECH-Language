#include "BTECH.h"
#include <set>
#include <fstream>
#include <iostream>

using namespace BTECH;

std::set <char> ops = {'+','-','/','*','%','&','(',')','>','<','^','|','=','!'};
//token initializers
token::token(std::string s): name(s) {}
//default Unknown
_generic_token::_generic_token(std::string n="Unknown Token"): token(n) {} 
_string::_string(std::__cxx11::string c): token("string"), contents(c) {}
_operator::_operator(char t): token("op"), _type(t) {}
_number::_number(N n): token("number"), value(n) {}
_number::get_value() const {return value} //getter for numbers

//boilerplate for printing tokens?
std::ostream& operator<< (std::ostream& os, const token& tok) {
    tok.print(os); //call print method of derived class
    return os;
}
void _generic_token::print(std::ostream& os) const{
	os << this->name << " ";
	if (this->name == "EOL"){
		os << std::endl;
	}
}
void _operator::print(std::ostream& os) const{
	os <<this->name << "(" << this->_type << ") ";
}
void _string::print(std::ostream& os) const{
	os << this->name << " \"" << this->contents << "\"";
}
void _number::print(std::ostream& os) const{
	os << this->get_value() << " ";
}
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
	while (!file.eof()){
		if (file.peek() == '#') {  // Stealing comment syntax from python
			// comment out whole line
			file.ignore(10000,'\n');

		}else if (file.peek() == '"') {  // build strings "
			file.ignore(1);//ignore first quote
			getline(file, line,'"');
			tokens.push_back(new _string(line));

		}else if (file.peek() == '\'') {  // build strings '
			getline(file, line,'\'');
			tokens.push_back(new _string(line));

		}else if (file.peek() == '\\' && file.peek()-1 != '\\') {  // end of commands
			tokens.push_back(new token("EOL"));

		}else if (ops.find(file.peek()) != ops.end()) {  // build operators
			tokens.push_back(new _operator(file.get()));

		}else if (file.peek() == 'i' && isdigit(file.peek()+1)) {  // build operators
			getline(file, line,' ');
			tokens.push_back(new _number(line)); //TODO figure out complex later

		}else  if (file.peek() == '.' || isdigit(file.peek())){
		// build numbers
			getline(file, line,' ');
			if ( line.find('.') != std::string::npos){//contains a decimal
				tokens.push_back(new _number(std::stod(line)));	
			}else{
				tokens.push_back(new _number(std::stoi(line)));
			}

		}else{  // build everything else
			getline(file, line,' ');
			tokens.push_back(new _generic_token(line));

		}
		tokens.push_back(new _generic_token("EOL"));
	}file.close();

	tokens.push_back(new _generic_token("EOF"));

	if(debug){
		std::cout << "Tokenizing sucessfull\nTokens generated:\n";
		for(std::vector<token *>::iterator i = tokens.begin(); i != tokens.end(); i++){
			if (/**/"" == "EOL"){ 
				std::cout << "EOL\n";
				continue;
			}
			//std::cout << i << "  ";
		}
	}
	build_ast();
};
