// file used to turn all the generic tokens into nested objects

#include "BTECH.h"

using namespace BTECH;

bool scope::build_scope(std::vector<token *> tok){
	this->tokens = tok;
	while(_itter < tokens.size()-1){//keep adding stuff to main unstil we reach EOF
		this->body.push_back( build_command() );
	}
	return 0;
}
bool scope::add_to_scope(std::vector<token *> tok){
	tokens.reserve(tokens.size() + tok.size());
	std::move(tok.begin(), tok.end(), std::inserter(tokens, tokens.end()));

	while(_itter < tokens.size()-1){//parse the newest line
		this->body.push_back( build_command() );
	}
	return 1;
}
//NOTE if I want to be safe and nice I should probably delete all the items in the vector later
command* scope::build_function(){
	command* func = (command*)(new function(get_token().name));

	get_token();//move past :

	(*func).body.push_back(build_command());
	return func;
}
command* scope::build_scope(){
	command* scp = (command*)(new scope(get_token().name));

	get_token();//move past {

	while(!tokens[_itter]->name_is("EOF") && !op_is('}') ){
		(*scp).body.push_back(build_command());
	}
	get_token();//move past }

	if(tokens.back()->name != "EOL")
		get_token();//move past }
	return scp;
}

command* scope::build_expression(){
	expression* express = new expression();

	while(!(tokens[_itter]->name_is("EOL") || tokens[_itter]->name_is("EOF") || op_is(')') )){
		if (op_is('(')){
			_itter++;
			express->body.push_back(build_expression());//add all tokens into the array
		}else{
			express->body.push_back(tokens[_itter]);//add all tokens into the array
		}
		_itter++;
	}_itter++;
	
	return (command *)(express);
}
bool scope::op_is(char b){
	if (tokens[_itter]->name_is("op")){
		if(tokens[_itter]->type_is(b))
			return true;
	}
	return false;
}
command* scope::build_command(){
	command* cmd;
	if (tokens[_itter]->name_is("EOF")) 
		return (command *)(&tokens[_itter]);
	if (tokens[_itter]->name_is("op")){
		if(tokens[_itter]->type_is('(')){
			_itter++;
			cmd = build_multiline_command();	// multiline commands
		}else{
			cmd = build_expression();
		}
	}else if (tokens[_itter+1]->name_is("op")){
		if (tokens[_itter+1]->type_is('=')){
			std::cout << "=";
			_itter++;
			//cmd =	assignment(get_token());
		}else if (tokens[_itter+1]->type_is('{')){ //TODO
			cmd = build_scope();
		//cmd =	function_declariation(get_token());
		}else if(tokens[_itter+1]->type_is(':')){
			cmd = build_function();	// nested function calls
		}else{
			cmd = build_expression();	// nested function calls
		}
	}else{
		cmd = build_expression();
	}
	return cmd;
}
command* scope::build_multiline_command(){
	expression * cmds = new expression("multcmd");
	while(	!op_is(')') && !tokens[_itter]->name_is("EOF") ){	// peek
		(*cmds).body.push_back((token *)build_command());
	}
	//remove weurd EOL's that apear after multilines? TEST DOES THIS BREAK ANYTHING
	while ((tokens[_itter+1]->name_is("EOL") || tokens[_itter]->name_is("EOL")) && !op_is(')')) _itter++; 
	return (command *)(cmds);
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
