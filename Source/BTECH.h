#include <stdio.h>
#include <vector>
#include <string>
#include <set>
#include <iostream>
#include <fstream>
#include <complex>
#include <memory>

namespace BTECH{
	//token list will be a vector of pointers to an abstract token class
	class token{  // abstract base class cause why not
	  public:
		std::string name;
		token(std::string s): name(s) {}
		token(): name("_") {}
		virtual void print(std::ostream&) const;
		virtual std::string jen_print() const;
		bool name_is(std::string) const;
		virtual bool type_is(char) const;
		void run(token * result) {result = this;}
	};

	class _generic_token: public token{
	  public:
		_generic_token(std::string);
		void print(std::ostream&) const;
		std::string jen_print() const;
	};

	class _operator: public token{
		char _type; //type of operator
	  public:
		_operator(char);
		void print(std::ostream&) const;
		std::string jen_print() const;
		bool type_is(char) const;
	};


	// "types"
	class _string: public token{
	  public:
		std::string contents;
		_string(std::string);
		void print(std::ostream&) const;
		std::string jen_print() const;
	};
	/*
	template <typename N> 
	// I haven't ever touched templates why is this so confusing aaa what do I do
	class _number: public token{ //generic number token that can store any type of number
		N value;
	  public:
	  	_number(N);
		N get_value();
		void print(std::ostream&) const;
	};*/


	// and the token class is basicaly just object
	// functions are the most important part of this language even though its not functional
	class command: public token{
	  public:
		std::vector <token *> body;
		command(std::string);
		virtual void print(std::ostream&) const;
		virtual std::string jen_print() const;
	};
	class generic_command: public command{
	  public:
		generic_command(std::string);
		void print(std::ostream&) const;
		std::string jen_print() const;
	};
	class function: public command{
	  public:
		function(std::string);
		function(std::string, command*);
		void print(std::ostream&) const;
		std::string jen_print() const;
		void run(command * result);
	};
	class expression: public command{
	  public:
		std::vector<token *> expr;
		expression();
		void print(std::ostream&) const;
		std::string jen_print() const;
	};
	class scope: public command{
	  public:
		scope(std::string);
		void print(std::ostream&) const;
		std::string jen_print() const;
		void run(command * result);
	};



//main program
	class program{
	  private:
		int debug; //debug flag
		std::string program_name;
		std::vector<token *> tokens; //array of tokens
		command * ast; //main function and everything attached
	  public:
		int _itter; //used to be a std::vector<token>::itterator...
		token get_token(){ //basically pop front...
			_itter++;
			return *tokens.at(_itter -1);
		}
		program(std::string s, int d=1): debug(d), _itter(0), program_name(s) {build_program(s);}
		~program();
		void build_program(std::string);
		command* build_function();
		command* build_command();
		command* build_scope();
		command* build_expression();
		command* build_multiline_command();
		bool find_bracket(char);
		void build_ast();
		void run_program();
	};


}
std::ostream& operator<<(std::ostream&, const BTECH::token&);
