#include "BTECH.h"
using namespace BTECH;

void token::print(std::ostream& os) const{std::cout <<"ERROR: IMPOSIBLE TO REACH THIS";} // should never reach
void command::print(std::ostream& os) const{std::cout <<"ERROR: IMPOSIBLE TO REACH THIS";} // should never reach

//default Unknown
_generic_token::_generic_token(std::string n): token(n) {}
_string::_string(std::__cxx11::string c): token("string"), contents(c) {}
_operator::_operator(char t): token("op"), _type(t) {}
//doesn't liking having these in ast file
command::command(std::string s): token(s) {}
generic_command::generic_command(std::string s): command(s) {}
function::function(std::string s): command(s) {}
expression::expression(): command("expression") {}

//_number::_number(N n): token("number"), value(n) {}
//_number::get_value() const {return value} //getter for numbers

bool token::name_is(std::string s) const{return !s.compare(this->name);}
bool token::type_is(char c) const{return 0;}
bool _operator::type_is(char c) const{return (c == this->_type);}

//boilerplate for printing tokens?
std::ostream& operator<< (std::ostream& os, const token& tok) {
    tok.print(os); //call print method of derived class
    return os;
}
void _generic_token::print(std::ostream& os) const{
	os <<'[' << this->name << "] ";
	if (this->name_is("EOL")){
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
void function::print(std::ostream& os) const{
	os <<"func\'" << this->name << ": {";
	if (!this->body.empty()){
		for(std::vector<token *>::const_iterator i = this->body.begin(); i != this->body.end(); i++){
			os << **i << " ";
		}
	}
	os << "}\n";
}
void generic_command::print(std::ostream& os) const{
	os <<"[" << this->name << /*" (" << this->body <<*/ "]";
}
void expression::print(std::ostream& os) const{
	os <<"  [ ";
	for(auto i: this->expr){
		os << *i;
	}
	os << "] ";
}
