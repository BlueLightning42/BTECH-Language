#include "BTECH.h"
using namespace BTECH;

program::~program(){
	std::for_each(tokens.begin(), tokens.end(), delete_pointed_to<token>);
	tokens.clear();
}
command::~command(){
	std::for_each(body.begin(), body.end(), delete_pointed_to<token>);
	body.clear();
}
scope::~scope(){
	std::for_each(tokens.begin(), tokens.end(), delete_pointed_to<token>);
	tokens.clear();
}
expression::~expression(){
	std::for_each(body.begin(), body.end(), delete_pointed_to<token>);
	body.clear();
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

double _number::get_value(double _) const{
	//return floating_point ? f_val : i_val;
	return f_val;
}
long long _number::get_value(long long _) const{
	return i_val;
}
std::complex<double> _number::get_value_i() const{
	return c_val;
}

void  _number::remake(std::complex<double> n) {
	this->imaginary = true;
	this->c_val = n;
	this->i_val = static_cast<long long>(c_val.real()+0.5);
	this->f_val = static_cast<double>(c_val.real());
	if ( c_val.imag() > -0.000002 && c_val.imag() < 0.000002){
		this->imaginary = false;
		this->floating_point = !( (f_val - i_val) > -0.0000002 && (f_val - i_val) < 0.0000002);
	} 
}
void  _number::remake(double n) {
	this->imaginary = false;
	this->c_val.imag(0);
	this->i_val = static_cast<long long>(n+0.5);
	this->f_val = n;
	this->c_val.real(f_val);
	this->floating_point = !( (f_val - i_val) > -0.0000002 && (f_val - i_val) < 0.0000002);
}
void  _number::remake(long long n) {
	this->imaginary = false;
	this->c_val.imag(0);
	this->i_val = n;
	this->f_val = static_cast<double>(n);
	this->c_val.real(f_val);
	this->floating_point = !( (f_val - i_val) > -0.0000002 && (f_val - i_val) < 0.0000002);
}


_number::_number(std::string n, bool i): token("num"), imaginary(i) {
	c_val = (0.0,0.0);
	if (i) {
		c_val.imag(stod(n));
		i_val = 0;
		f_val = 0;
	}else{
		i_val = stoll(n);
		f_val = stod(n);
		c_val.real(f_val);
		floating_point = !((f_val - i_val) > -0.0000002 && (f_val - i_val) < 0.0000002);
	}
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

//                    SHELL                       //
program::program():
											debug(0), 
											_itter(0), 
											program_name("shell"), 
											_main("shell")
											{
	std::cout << "===============================================================\n" << 
	"Welcome to the shell    \ntype #help for information or enter a line you wish to run" << "\n->========================== SHELL ============================\n";
	// READ EVAL PRINT LOOP
	while(_main.add_to_scope(this->parse_line())){}
	std::cout << ".\n->======================== END SHELL ==========================\n";
}
