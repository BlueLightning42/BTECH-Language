// file used to turn all the generic tokens into nested objects
#include "BTECH.h"
using namespace BTECH;

inline void ptr_pop_convert(std::vector<std::unique_ptr<token> > &ptr_vec1,
					std::vector<std::shared_ptr<token> > &ptr_vec2, 
					int i){
	ptr_vec2.push_back(std::move(ptr_vec1[i]));
	ptr_vec1.erase(ptr_vec1.begin()+i,ptr_vec1.begin()+i+1);
}
inline std::shared_ptr<token> ptr_pop(std::vector<std::unique_ptr<token> > &ptr_vec1, int i){
	std::shared_ptr<token> c = std::move(ptr_vec1[i]); //move a single token out of unique
	ptr_vec1.erase(ptr_vec1.begin()+i,ptr_vec1.begin()+i+1); //errase spot where ptr used to be
	return c;
}

bool scope::build_scope(std::vector<std::unique_ptr<token> >& tok){
	std::move(tok.begin(), tok.end(), std::back_inserter(this->tokens));
	while(_itter < tokens.size()-1){//keep adding stuff to main unstil we reach EOF
		this->body.push_back( build_command() );
	}
	return 0;
}
bool scope::add_to_scope(std::vector<std::unique_ptr<token> >& tok){

	//transfer ownership of unique pointers to the scope
	std::move(tok.begin(), tok.end(), std::back_inserter(this->tokens));   

	while(_itter < tokens.size()-1){//parse the newest line
		this->body.push_back( build_command() );
	}
	return 1;
}
//NOTE if I want to be safe and nice I should probably delete all the items in the vector later
std::shared_ptr<command> scope::build_function(){
	std::shared_ptr<function> func = std::make_shared<function>(get_token().name);

	get_token();//move past :

	func->body = build_command(); //bind the next command whatever it is to the function
	return func;
}
std::shared_ptr<command> scope::build_scope(){
	std::shared_ptr<scope> scp = std::make_shared<scope>(get_token().name);

	get_token();//move past {

	while(!tokens[_itter]->name_is("EOF") && !op_is('}') ){
		scp->body.push_back(build_command());
	}
	get_token();//move past }

	if(tokens.back()->name != "EOL")
		get_token();//move past }
	return scp;
}

std::shared_ptr<command> scope::build_expression(){
	std::shared_ptr<expression> express = std::make_shared<expression>();

	while(!(tokens[_itter]->name_is("EOL") || tokens[_itter]->name_is("EOF") || op_is(')') )){
		if (op_is('(')){
			_itter++;
			express->body.push_back(build_expression()); //add all tokens into the array
		}else{
			ptr_pop_convert(tokens, express->body, _itter); //add all tokens into the array
		}
		_itter++;
	}_itter++;
	
	return express;
}
bool scope::op_is(char b){
	if (tokens[_itter]->name_is("op")){
		if(tokens[_itter]->type_is(b))
			return true;
	}
	return false;
}
std::shared_ptr<command> scope::build_command(){
	if (tokens[_itter]->name_is("EOF"))
		return std::make_shared<command>("EOF");
	if (tokens[_itter]->name_is("op")){
		if(tokens[_itter]->type_is('(')){
			_itter++;
			return build_multiline_command();	// multiline commands
		}else{
			return build_expression();
		}
	}else if (tokens[_itter+1]->name_is("op")){
		if (tokens[_itter+1]->type_is('=')){
			std::cout << "=";
			_itter++;
			//cmd =	assignment(get_token());
		}else if (tokens[_itter+1]->type_is('{')){ //TODO
			return build_scope();
		//cmd =	function_declariation(get_token());
		}else if(tokens[_itter+1]->type_is(':')){
			return build_function();	// nested function calls
		}else{
			return build_expression();	// nested function calls
		}
	}//else
	return build_expression();
}
std::shared_ptr<command> scope::build_multiline_command(){
	std::shared_ptr<expression> cmds = std::make_shared<expression>("multcmd");
	while(	!op_is(')') && !tokens[_itter]->name_is("EOF") ){	// peek
		(cmds)->body.push_back(build_command());
	}
	//remove weird EOL's that apear after multilines? TEST DOES THIS BREAK ANYTHING
	while ((tokens[_itter+1]->name_is("EOL") || tokens[_itter]->name_is("EOL")) && !op_is(')')) _itter++; 
	return cmds;
}
//split vector of tokens created in parser into a tree of statements...
//stuff like	 func_init: name
//			 expression: number, operator, number



/*

function_declariation(token n){
	 // make your own function and append to the global function list in the form
	 /**
	 custom_func{ (passed arguments-default *arg)
							 (logic to be preformed on arg)
							 (any returned variables)
	 }
	 **/
	 // note this is a joke language and creating functions is obtuse/hidden away like this because
	 // its designed for you to use all the "custom" functions defined in the standard library (like yotka:)
	 /**psudocode for yotka function would be
	 yotka{ (expression e)
				 (a = cast_to_string((eval(e)))
				 (a)
	}
	**/


// NUM SUB NUM MULT NUM ADD NUM DIV EXPRESSION		//math
