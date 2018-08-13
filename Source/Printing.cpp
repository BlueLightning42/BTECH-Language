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
	if (this->imaginary){
		os << "[inum( "<<this->c_val.real() << ", " << c_val.imag() << "i )] ";
	}else{
		if (this->floating_point) {os <<"[num(" << this->f_val << ")] ";}
		else 					  {os <<"[num(" << this->i_val << ")] ";}
	}
}
void function::print(std::ostream& os) const{
	os <<"  func\'" << this->name << ": \t{";
	os << this->body << " \n";
	os << "\t}";
}
void scope::print(std::ostream& os) const{
	os <<"  scope'" << this->name << "{ \n";
	if (!this->body.empty()){
		for(const auto &i: body){ //::const_iterator
			os << *i << " \n";
		}
	}
	os << "\t}";
}
void expression::print(std::ostream& os) const{
	if (this->name_is("multcmd")){
		os << this->name << "(\n";
		if (!this->body.empty()){
			for(const auto &i: body){ //::const_iterator
				os <<"\n\t" << *i;
			}
		}os << ')';
	}else{
		os <<"  [ ";
		for(const auto &i: this->body){
			os << *i;
		}
		os << "] ";
	}
}


//================= jen =====================//
/*	jen printing/converting to strings	 */


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

inline std::string clip_zero(std::string str){
	str.erase ( str.find_last_not_of('0') + 1, std::string::npos );
	str.erase ( str.find_last_not_of('.') + 1, std::string::npos );
	return str;
}
inline bool close_to_int(double f){
	return !( f > -0.0000002 && f < 0.0000002);
}
std::string _number::jen_print() const{
	if(this->imaginary){
		return (close_to_int(c_val.real()) ? 
					clip_zero(std::to_string(this->c_val.real())) + " " 
					: "") +
				(c_val.imag() > 0 ? 
					close_to_int(c_val.real()) ? "+ " : "" 
					: "- ") + 
				clip_zero(std::to_string(std::abs(this->c_val.imag()))) + "j";
	}else{
		if (this->floating_point){
			return clip_zero(std::to_string(this->f_val));
		}else{
			return std::to_string(this->i_val);
		}
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
std::string scope::jen_print() const{
	std::string temp;
	 if (!this->body.empty()){
		for(const auto &i: body){ //::const_iterator
			temp += i->jen_print();
		}
	}
	return temp;
}
std::string expression::jen_print() const{
	std::string temp = "";
	for(const auto &i: this->body){
		temp += i->jen_print() + " ";
	}
	return temp;
}





//================= Zen =====================//
/*	Zen printing uses 7 segment displays   */

/*	top	
	top left	
	top right	
	center		
	bottom left	
	bottom right
	bottom
	point
*/
const int EMPTY = 10;
const int POINT = 11;
const unsigned char screen[12] ={
	0b11101110, // 0
	0b00100100, // 1
	0b10111010, // 2
	0b10110110, // 3
	0b01110100, // 4
	0b11010110, // 5
	0b11011110, // 6
	0b11100100, // 7
	0b11111110, // 8
	0b11110110, // 9
	0b00000000, // null/empty
	0b00000001  // point
};
inline void append_number_to_7SD(std::vector<std::string> &s, unsigned char c){
	s[0].insert(8,"  " +std::string((c >> 7 & 1)? ".____." : ".	.")										+ "  ");
	s[1].insert(8,"  " +std::string((c >> 6 & 1)? "|" : " ") + "	" + std::string((c >> 5 & 1)? "|" : " ")	+ "  ");
	s[2].insert(8,"  " +std::string((c >> 6 & 1)? "|" : " ") + "	" + std::string((c >> 5 & 1)? "|" : " ")	+ "  ");
	s[3].insert(8,"  " +std::string((c >> 4 & 1)? ".____." : ".	.")										+ "  ");
	s[4].insert(8,"  " +std::string((c >> 3 & 1)? "|" : " ") + "	" + std::string((c >> 2 & 1)? "|" : " ")	+ "  ");
	s[5].insert(8,"  " +std::string((c >> 3 & 1)? "|" : " ") + "	" + std::string((c >> 2 & 1)? "|" : " ")	+ "  ");
	s[6].insert(8,"  " +std::string((c >> 1 & 1)? ".____." : ".	.") + std::string((c >> 0 & 1)? "o" : " ") + " " );
}
inline int i_pow(int a, int b){
	if (b==0) return 1;
	while(b > 1){
		a *= a;
		b--;
	}
	return a;
}
void print_7SD(int num){
	std::vector<std::string> s = {"	\n|| ","  ||\n|| ","  ||\n|| ","  ||\n|| ","  ||\n|| ","  ||\n|| ","  ||\n||   ||_"};
	int tn=num;
	do{
		append_number_to_7SD(s, screen[tn % 10]);
		tn /= 10;
	}while(tn);
	std::cout << "\n================";
	if(num / 100) std::cout << "==========";
	if(num/10) std::cout << "===========";
	for(auto a: s){
		std::cout << a;
	}
	if(num / 100 > 0){ std::cout << "\n===================================||3|\n";
	}else if(num/10 > 0) {std::cout << "\n=========================||2|\n";
	}else{std::cout << "\n===============||1|\n";}
}
void print_7SD(float num){
	std::vector<std::string> s = {"	\n|| ","  ||\n|| ","  ||\n|| ","  ||\n|| ","  ||\n|| ","  ||\n|| ","  ||\n||   ||_"};
	int tn=num;
	int places = 0;
	while(tn){
		places++;
		tn /=10;
	}
	int rest = (num-tn) * (10 * (3-places));
	do{
		append_number_to_7SD(s, screen[tn % 10] & (tn/=10 ? EMPTY : POINT ));
		tn /= 10;
	}while(tn);

	std::cout << "\n=====================================";
	for(auto a: s){
		std::cout << a;
	}
	std::cout << "\n===================================||3|\n";

}
