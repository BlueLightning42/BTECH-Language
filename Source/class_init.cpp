#include "BTECH.h"
using namespace BTECH;

program::~program(){
 //doesn't like iterating over every pointer and deleting? //TODO FIX
	tokens.clear();
    //delete ast;
}


void token::print(std::ostream& os) const{std::cout <<"ERROR: IMPOSIBLE TO REACH THIS";} // should never reach
void command::print(std::ostream& os) const{std::cout <<"ERROR: IMPOSIBLE TO REACH THIS";} // should never reach

//default Unknown
_generic_token::_generic_token(std::string n): token(n) {}
_string::_string(std::__cxx11::string c): token("string"), contents(c) {}
_operator::_operator(char t): token("op"), _type(t) {}
//doesn't liking having these in ast file
command::command(std::string s): token(s) {}
generic_command::generic_command(std::string s): command(s) {}


scope::scope(std::string s): command(s) {}
function::function(std::string s): command(s) {}
expression::expression(): command("expression") {}

bool token::name_is(std::string s) const{return !s.compare(this->name);}
bool token::type_is(char c) const{return 0;}
bool _operator::type_is(char c) const{return (c == this->_type);}


//template <typename N>
double _number::get_value(double _) const{
	//return floating_point ? f_val : i_val;
	return f_val;
}
long long _number::get_value(long long _) const{
	return i_val;
}

