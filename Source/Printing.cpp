#include "BTECH.h"
using namespace BTECH;


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
void _number::print(std::ostream& os) const{
	double d;
	long long l;
	if (this->floating_point) {os <<"[num(" << this->get_value(d) << ")] ";}
	else {os <<"[num(" << this->get_value(l) << ")] ";}
}
void function::print(std::ostream& os) const{
	os <<"  func\'" << this->name << ": \t{";
	if (!this->body.empty()){
		for(auto i: body){ //::const_iterator
			os << *i << " \n";
		}
	}
	os << "\t}";
}
void scope::print(std::ostream& os) const{
	os <<"  scope'" << this->name << "{ \n";
	if (!this->body.empty()){
		for(auto i: body){ //::const_iterator
			os << *i << " \n";
		}
	}
	os << "\t}";
}
void generic_command::print(std::ostream& os) const{
	os << this->name << "(\n";
	 if (!this->body.empty()){
		for(auto i: body){ //::const_iterator
			os <<"\n\t" << *i;
		}
	}os << ')';
}
void expression::print(std::ostream& os) const{
	os <<"  [ ";
	for(auto i: this->expr){
		os << *i;
	}
	os << "] ";
}


//================= jen =====================//
/*    jen printing/converting to strings     */


std::string token::jen_print() const{return "";}
std::string command::jen_print() const{return "";}
std::string _generic_token::jen_print() const{
	return this->name;
}
std::string _operator::jen_print() const{
	return std::string(1, this->_type);
}
std::string _string::jen_print() const{
	return this->contents;
}
std::string _number::jen_print() const{
	if (this->floating_point){
		return  std::to_string(this->f_val);
	}else{
		return  std::to_string(this->i_val);
	}
}
std::string function::jen_print() const{
	if(this->name_is("nasim") || this->name_is("yotka")){
		return "jen: "+this->name +" A wonderfull collegue\n";
	}else if (this->name_is("jen")){
		return "jen: That is my name yes\n";
	}else{
		return this->name + ' ';
	}	
}
std::string generic_command::jen_print() const{
	std::string temp;
	 if (!this->body.empty()){
		for(auto i: body){ //::const_iterator
			temp += i->jen_print();
		}
	}
	return temp;
}
std::string scope::jen_print() const{
	std::string temp;
	 if (!this->body.empty()){
		for(auto i: body){ //::const_iterator
			temp += i->jen_print();
		}
	}
	return temp;
}
std::string expression::jen_print() const{
	std::string temp = "";
	for(auto i: this->expr){
		temp += i->jen_print();
	}
	return temp;
}
