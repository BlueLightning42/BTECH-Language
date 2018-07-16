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
		std::cout << ".\n->Objects created:\n  ";
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

	while(!(tokens[_itter]->name_is("EOL") || tokens[_itter]->name_is("EOF"))){
		express->expr.push_back(tokens[_itter]);//add all tokens into the array
		_itter++;
	}_itter++;
	
	return (command *)(express);
}
command* program::build_command(){
	command* cmd;
	if (tokens[_itter+1]->name_is("op")){
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
		_itter++;
		std::cout << "Not a valid command!\n";
	}
	return cmd;
}
std::vector <command*> program::build_multiline_command(){
	std::vector <command*> cmds;
	while(	!(tokens[_itter]->name_is(")"))){	// peek
		cmds.push_back(build_command());
	}
	return cmds;
}

function_declariation(token n){}
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
