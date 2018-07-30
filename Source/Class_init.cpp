#include "BTECH.h"
using namespace BTECH;


template <typename T>
void delete_pointed_to(T* const ptr){
	if (!(ptr->name_is("EOL") || ptr->name_is("EOF"))){
		delete ptr;
	}
}
program::~program(){
	std::for_each(tokens.begin(), tokens.end(), delete_pointed_to<token>);
	tokens.clear();
}
command::~command(){
	std::for_each(body.begin(), body.end(), delete_pointed_to<token>);
	body.clear();
}
expression::~expression(){

}



void token::print(std::ostream& os) const{std::cout <<"ERROR: IMPOSIBLE TO REACH THIS";} // should never reach
void command::print(std::ostream& os) const{std::cout <<"ERROR: IMPOSIBLE TO REACH THIS";} // should never reach

//default Unknown
_generic_token::_generic_token(std::string n): token(n) {}
_string::_string(std::__cxx11::string c): token("string"), contents(c) {}
_operator::_operator(char t): token("op"), _type(t) {}
//doesn't liking having these in ast file
command::command(std::string s): token(s) {}


scope::scope(std::string s): command(s), _itter(0) {}
function::function(std::string s): command(s) {}
expression::expression(): command("expression") {}
expression::expression(std::string s): command(s) {}

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





program::program(std::string s, int d=1): 
											debug(d), 
											_itter(0), 
											program_name(s), 
											_main("main")
											{
	if(build_program(s)){
		std::cout << "\nTokenizing unsucessfull";
		return;
	}
	if(debug > 1) std::cout << std::endl << std::string(62, '=');
	if(debug){
		std::cout << "\nTokenizing sucessfull";
	}
	if(debug > 1){
std::cout << ".\n->===================== Tokens generated: ====================\n  ";
		for(auto i: tokens){
			std::cout << *i << "  "; 
		}
	}std::cout << '.';
	/*  ~  ~  ~  ~  ~  ~  ~  */
	if(_main.build_scope(tokens)){
		std::cout << "\nObject creator unsucessfull";
		return;
	}
	if(debug > 1) std::cout << "\n\n" << std::string(62, '=');
	if(debug){
		std::cout << "\nAst complete";
	}if(debug > 1){
std::cout << ".\n->====================== Objects created: ====================\n";
		std::cout << _main;
	}std::cout << '.';
	/*  ~  ~  ~  ~  ~  ~  ~  */
	if(debug > 1) std::cout << "\n\n" << std::string(62, '=');
	if(debug) std::cout << "\nRun Program:";
	else std::cout<<'.';
	std::cout<< std::endl << "->" << std::string(30-program_name.size()/2-2, '=')
			 << ' ' << this->program_name << ' '  
			 << std::string(30-program_name.size()/2 - program_name.size()%2, '=') << std::endl;
	if(run_program()){
		std::cout << "\nError While Running";
		return;
	}
	std::cout << std::endl << std::string(62, '=');
	if(debug > 1) std::cout << "\n\n\n";
}
