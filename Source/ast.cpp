#include "BTECH.h"

using namespace BTECH;

void program::build_ast(){
	_itter = 0; // reause itterator
	function _main("main");
	while(_itter < tokens.size()-1){//keep adding stuff to main unstil we reach EOF
		_main.body.push_back( build_command() );
	}
	ast.push_back((command*)(&_main));

	//tokens.clear();//delete token tree;
	if(debug){
		std::cout << "\nAst complete";
	if(debug > 1)
		std::cout << ".\n->Objects created:\n";
		for(std::vector<token *>::iterator i = ast.begin(); i != ast.end(); i++){
			std::cout << **i << "  ";
		}
	}std::cout << '.' << std::endl;
	optomise_ast();
}
//NOTE if I want to be safe and nice I should probably delete all the items in the vector later
command* program::build_function(){
	command* func = (command*)(new function(get_token().name));

	get_token();//move past :

	(*func).body.push_back(build_command());
	return func;
}
command* program::build_expression(){
	expression* express = new expression();

	while(!(tokens[_itter]->name_is("EOL") || tokens[_itter]->name_is("EOF") || find_bracket() )){
		express->expr.push_back(tokens[_itter]);//add all tokens into the array
		_itter++;
	}_itter++;
	
	return (command *)(express);
}
bool program::find_bracket(){
	if (tokens[_itter]->name_is("op")){
		if(tokens[_itter]->type_is(')'))
			return true;
	}
	return false;
}
command* program::build_command(){
	command* cmd;
	if (tokens[_itter]->name_is("EOF")) 
		return (command *)(tokens[_itter]);
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
			std::cout <<"{";
			_itter++;
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
command* program::build_multiline_command(){
	generic_command * cmds = new generic_command("multcmd");
	while(	!find_bracket() && !tokens[_itter]->name_is("EOF") ){	// peek
		(*cmds).body.push_back((token *)build_command());
	}
	return (command *)(cmds);
}
//split vector of tokens created in parser into a tree of statements...
//stuff like	 func_init: name
//			 expression: number, operator, number



/*
function::function(std::string n) name(n){
	_itter++;	// move global itterator past the ":"
	if (tokens[_itter+1].name_is(":"){
		cmd = function(get_token());	// nested functions
	}else if (tokens[_itter+1].name_is("("){
		_itter++;
		cmd = build_multiline_command();
	}else{
		cmd = build_command;
	}
	// return self; 
}

// is this...the factory pattern?
command build_command(){
	command cmd;
	if (tokens[*_itter+1].name_is("=")){
		cmd =	assignment(get_token());
	}else if (tokens[*_itter+1].name_is("op")){	// type is instead
		cmd =	expression();
	}else if (tokens[*_itter+1].name_is("{")){
		cmd =	function_declariation(get_token());
	}else if(tokens[*_itter+1].name_is(":")){
		cmd = function(get_token());	// nested function calls
	}else if(tokens[*_itter+1].name_is("#") || tokens[*_itter+1].name_is("EOF") ){
	//skip empty lines and comments
	__itter++
	cmd = build_command();
	}else{
		 std::cout << "Not a valid command";
	}
	return cmd;
}
command build_multiline_command(){
	std::vector <command> cmds;
	while(	!(tokens[*_itter].name_is(")")){	// peek
		cmds.push_back(build_command());
	}
	return cmds;
}
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
