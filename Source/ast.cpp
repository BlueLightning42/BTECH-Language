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
	}if(debug > 1){
		std::cout << ".\n->Objects created:\n";
		for(auto i: ast){
			std::cout << *i << "  ";
		}
	}std::cout << '.' << std::endl;
	run_program();
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
			std::cout <<"{ NOT IMPLEMENTED YET";
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
	//remove weurd EOL's that apear after multilines? TEST DOES THIS BREAK ANYTHING
	while ((tokens[_itter+1]->name_is("EOL") || tokens[_itter]->name_is("EOL")) && !find_bracket()) _itter++; 
	return (command *)(cmds);
}
