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
	/*template <typename T>
	void delete_pointed_to(T* const ptr){
		if (!(ptr->name_is("EOL") || ptr->name_is("EOF"))){
			delete ptr;
		}
	}*/
	template<typename T, typename... Args>
	inline std::unique_ptr<T> make_unique(Args&&... args) {
		return (std::unique_ptr<T>(new T(std::forward<Args>(args)...)));
	}
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
		~token(); //removes a load of errors for not having a default deconstructor and for some reason they can't be in the header file
	};

	class _generic_token: public token{
	  public:
		_generic_token(std::string);
		void print(std::ostream&) const;
		std::string jen_print() const;
		~_generic_token(); 
	};

	class _operator: public token{
		char _type; //type of operator
	  public:
		_operator(char);
		void print(std::ostream&) const;
		std::string jen_print() const;
		bool type_is(char) const;
		~_operator();
		
	};


	// "types"
	class _string: public token{
	  public:
		std::string contents;
		_string(std::string);
		void print(std::ostream&) const;
		std::string jen_print() const;
		~_string(); 
	};
	


	class _number: public token{ //generic number token that can store any type of number
	  private:
		double f_val;
		long long i_val;
		std::complex<double> c_val;
	  public: 
	  //used to be private

		bool floating_point;
		bool imaginary;
	  	_number(std::__cxx11::string, bool);

		_number(std::complex<double>);
		_number(double);
		_number(long long);

		double get_value(double) const;
		long long get_value(long long) const;
		std::complex<double> get_value_i() const;


		virtual std::string jen_print() const;
		void print(std::ostream&) const;

		~_number(); 
	};


	// and the token class is basicaly just object
	// functions are the most important part of this language even though its not functional
	class command: public token{
	  public:
		command(std::string);
		virtual void print(std::ostream&) const;
		virtual std::string jen_print() const;
		virtual void run(std::shared_ptr<token>);
		~command();
	};
	class function: public command{
	  public:
		function(std::string);
		function(std::string, std::vector<std::shared_ptr<command> >);
		std::shared_ptr<command> body;
		void print(std::ostream&) const;
		std::string jen_print() const;
		void run(std::shared_ptr<token>);
		~function(); 
	};
	class expression: public command{
	  public:
		expression();
		expression(std::string);
		std::vector<std::shared_ptr<token> > body;
		void print(std::ostream&) const;
		std::string jen_print() const;
		~expression(); 
	};
	class scope: public command{
	  public:
		scope(std::string);
		std::vector<std::unique_ptr<token> > tokens;
		std::vector<std::shared_ptr<command> > body;
		void print(std::ostream&) const;
		std::string jen_print() const;
		void run(std::shared_ptr<token>);
		/*  ~  ~  ~  ~  ~  ~  ~  */
		int _itter; //used to be a std::vector<token>::itterator...
		token get_token(){ //basically pop front...
			_itter++;
			return *tokens.at(_itter -1);
		}
		std::shared_ptr<command> build_function();
		std::shared_ptr<command> build_command();
		std::shared_ptr<command> build_scope();
		std::shared_ptr<command> build_expression();
		std::shared_ptr<command> build_multiline_command();
		bool add_to_scope(std::vector<std::unique_ptr<token> >&);
		bool build_scope( std::vector<std::unique_ptr<token> >&);
		bool op_is(char);
		~scope(); 
	};



//main program
	class program{
	  private:
		int debug; //debug flag
		std::string program_name;
		std::vector<std::unique_ptr<token> > tokens;
		scope _main; //main function and everything attached
	  public:
		int _itter; //used to be a std::vector<token>::itterator...
		program(std::string, int);
		program();//shell
		~program();
		bool build_program(std::string);
		void parse_line();
		bool run_program();
	};


}
std::ostream& operator<<(std::ostream&, const BTECH::token&);

#endif
