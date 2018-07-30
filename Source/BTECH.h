#ifndef INCLUDED_BTECH_H
#define INCLUDED_BTECH_H

#include <stdio.h>
#include <vector>
#include <string>
#include <set>
#include <iostream>
#include <fstream>
#include <complex>
#include <memory>
#include <algorithm>
/*

This Whole project has led me to the understanding that Polymorphism is evil.
It started off relativly simple but then everything had to become base class pointers to derived objects and to acess alot of the derived methods I had to dynamic cast the base pointers to derived ones...and it quickly decended into a mess
While the first note I get when I search it up says to use composition instead of inheritance I'm stuck trying to figure out how that would even be implemented.
at then end of the day I'm shifting stuff from derived classes into an array of attributes in the token class and its more expensive to preform a check to see if an array of attributes contains a certain attribute than it is to declare some methodes virtual and then define them in every derived class?
all in all the esc model seems to have specific benefits in a game but for this case/a interpeter it doesn't work (well).

only thing I'm sacarficing is readability

*/
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
		~token() {}
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
		~_operator() {}
	};


	// "types"
	class _string: public token{
	  public:
		std::string contents;
		_string(std::string);
		void print(std::ostream&) const;
		std::string jen_print() const;
	};
	


	class _number: public token{ //generic number token that can store any type of number
		double f_val;
		long long i_val;
		// std::complex<double> c_val; WILL IMPLEMENT ONCE FLOATS AND DOUBLES WORK
		// dont be too ambitious for joke language unstil it works
	  public:
		bool floating_point;
		_number (double d){
			f_val = d;
			i_val = static_cast<long long>(d);
			floating_point = ((f_val - i_val) > 0.0000001);
			
		}
		_number (long long i){
			i_val = i;
			f_val = static_cast<double>(i);
			floating_point = false;
		}
		_number (int i){
			i_val = i;
			f_val = static_cast<double>(i);
			floating_point = false;
		}
	  	_number(std::string n, bool imaginary): token("num") {
			if (imaginary) {
				//make complex
			}else{
				i_val = stoll(n);
				f_val = stod(n);
				floating_point = ((f_val - i_val) > 0.0000001);
			}
		}
		//template <typename N>
		double get_value(double) const;
		long long get_value(long long) const;
		
		virtual std::string jen_print() const;
		void print(std::ostream&) const;
		~_number() {}
	};


	// and the token class is basicaly just object
	// functions are the most important part of this language even though its not functional
	class command: public token{
	  public:
		std::vector <token *> body;
		command(std::string);
		~command();
		virtual void print(std::ostream&) const;
		virtual std::string jen_print() const;
		virtual void run(command *);
	};
	/* merged with expression object
	class generic_command: public command{
	  public:
		generic_command(std::string);
		void print(std::ostream&) const;
		std::string jen_print() const;
	};
	*/
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
		expression();
		expression(std::string);
		void print(std::ostream&) const;
		std::string jen_print() const;
		~expression();
	};
	class scope: public command{
	  public:
		scope(std::string);
		std::vector<token *> tokens;
		void print(std::ostream&) const;
		std::string jen_print() const;
		void run(command * result);
		/*  ~  ~  ~  ~  ~  ~  ~  */
		int _itter; //used to be a std::vector<token>::itterator...
		token get_token(){ //basically pop front...
			_itter++;
			return *tokens.at(_itter -1);
		}
		command* build_function();
		command* build_command();
		command* build_scope();
		command* build_expression();
		command* build_multiline_command();
		bool op_is(char);
		bool build_scope(std::vector<token *>);
	};



//main program
	class program{
	  private:
		int debug; //debug flag
		std::string program_name;
		std::vector<token*> tokens;
		scope _main; //main function and everything attached
	  public:
		int _itter; //used to be a std::vector<token>::itterator...
		program(std::string, int);
		~program();
		bool build_program(std::string);

		bool run_program();
	};


}
std::ostream& operator<<(std::ostream&, const BTECH::token&);

#endif
