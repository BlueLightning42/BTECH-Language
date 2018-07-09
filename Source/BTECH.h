#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <complex>
#include <memory>

class token{
 public:
  std::string name;
	token(std::string n="Unknown"): name(n) {}//default Unknown
};

class _operator: token{
  char _type; //type
  token left, right;
 public:
	_operator(char t): token("op"), _type(t) {}
};

class command{
  public:
	command() {}
	/**std::ostream& operator<<(std::vector<token>& tok){
	std::ostream os;
		os << this->name  << " (";
		for (auto &t: tok){//print everything in the stream
			os << t;
		}
		os << ")\n"
		return os;
	}**/
};







// "types"
class _string: token{
  public:
	std::string contents;
	_string(std::string);
};
/**
class _number: token{
  public:
	virtual void get_value() const {}
	//pass defenition will be done in parser
};
class _complex: number{
  public:
	std::complex value;
	_complex(std::complex v): value(v) {};
	void get_value(std::ostream& o) const { o << this->value;}
};
class _integer: number{
  public:
	int value;
	_integer(int v): value(v) {};
	void get_value(std::ostream& o) const { o << this->value;}
};
class _floating_point: number{
  public:
	double value;
	_floating_point(double v): value(v) {};
	void get_value(std::ostream& o) const { o << this->value;}
};
**/

class program{
  private:
	std::vector<std::unique_ptr<token>> tokens;
	std::vector <command> ast;
  public:
	int _itter = 0; //used to be a std::vector<token>::itterator
	token get_token(){ //basically pop front...
		_itter++;
		return *tokens.at(_itter -1);
	}
	void build_program(std::string);
	void build_ast();
	void optomise_ast();
	void write_asm();
};
