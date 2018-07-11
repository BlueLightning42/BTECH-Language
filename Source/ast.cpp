#include "BTECH.h"
using namespace BTECH;

command::command(std::string s): name(s) {}
function::function(std::string s): command(s) {}


void program::build_ast(){
	_itter = -1; // reause itterator
	ast.push_back(new function("main"));
	tokens.clear();//delete token tree;
	optomise_ast();
}





//split vector of tokens created in parser into a tree of statements...
//stuff like   func_init: name
//			 expression: number, operator, number

function::function(std::string n) name(n){
	_itter++;  // move global itterator past the ":"
	if (tokens[_itter+1].name_is(":"){
		cmd = function(get_token());  // nested functions
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
	  cmd =  assignment(get_token());
  }else if (tokens[*_itter+1].name_is("op")){  // type is instead
	  cmd =  expression();
  }else if (tokens[*_itter+1].name_is("{")){
	  cmd =  function_declariation(get_token());
  }else if(tokens[*_itter+1].name_is(":")){
	  cmd = function(get_token());  // nested function calls
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
	while(  !(tokens[*_itter].name_is(")")){  // peek
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
  }

// NUM SUB NUM MULT NUM ADD NUM DIV EXPRESSION	  //math
