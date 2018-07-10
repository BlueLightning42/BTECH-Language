#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <complex>
#include <memory>

namespace BTECH{
	class token{  // abstract base class cause why not
	  public:
		std::string name;
		token(std::string s);
		virtual void print(std::ostream&) const;
	};

	class _generic_token: public token{
	  public:
		_generic_token(std::string);
		void print(std::ostream&) const;
	};

	class _operator: public token{
		char _type; //type of operator
	  public:
		_operator(char);
		void print(std::ostream&) const;
	};


	// "types"
	class _string: public token{
	  public:
		std::string contents;
		_string(std::string);
		void print(std::ostream&) const;
	};
	
	template <typename N> 
	//I haven't ever touched templates why is this so confusing aaa what do I do
	class _number: public token{ //generic number token that can store any type of number
		N value;
	  public:
	  	_number(N);
		N get_value();
		void print(std::ostream&) const;
	};

	//commands for the ast
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



//main program
	class program{
	  private:
		int debug = 1; //debug flag
		std::vector<token *> tokens;
		std::vector <command *> ast;
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

std::ostream& operator<<(std::ostream&, const BTECH::token&);
}
