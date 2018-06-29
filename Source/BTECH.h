#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <string>
#include <iostream>

class token{
   	std::string name = "_";
  public:
	token(string n) name(n) {}
	token() {}
}

class _operator: token{
  char _type; //type
  token left, right;
 public:
    _operator(char t): _type(t) {}
    operation();
}

class command(){
  public:
	std::vector <token> tokens;
	command();
	std::ostream& operator<<(std::ostream& os, std::vector<tokens>& tok){
		os << this->name  << " (";
		for (auto &t: tok){//print everything in the stream
			os << t;
		}
		os << ")\n"
		return os;
	}
}







// "types"
class _string: token {
public:
    std::string contents;
    _string(std::string n, std::string c) name(n), contents(c) {}
};

class number: token(){
  public:
  virtual number get_value() const {}
	//pass defenition will be done in parser
}
class complex: number(){
	std::complex value;
  public:
	number(std::complex v):value(v) {};
	number get_value(ostream& o) const { o << this->value;}
}
class integer: number(){
	int value;
  public:
	number(int v): value(v) {};
	number get_value(ostream& o) const { o << this->value;}
}
class floating_point: number(){
	double value;
  public:
	number(double v): value(v) {};
	number get_value(ostream& o) const { o << this->value;}
}


class program{
  private:
    std::vector <token> tokens;
    std::vector <command> ast;
    build_program();
    build_ast();
    optomise_ast();
    write_asm();
}
