/* Probably not the best name for this file but...
   as I'm putting all of the "reserved" funcitons in here along with the logic of calling them Idk
*/
#include "BTECH.h"
using namespace BTECH;


#ifndef INCLUDED_EXPRESSION
#define INCLUDED_EXPRESSION
#include "Expression_Evaluator.cpp"
void evaluate_numeric_expression(expression *); // wont compile without these and idk why
void evaluate_binary_expression(expression *);
#endif


void call_function(std::string, std::vector<token*>, command *);


bool program::run_program(){
	command * result = new function("test");
    this->_main.run(result);

    if (result->name_is("ERROR"))
        return 1;
    delete result;
	return 0;
}



void _if(std::vector<token*> params){
	expression e = *(dynamic_cast<expression *>(params.at(0))); //copy expression object
	evaluate_binary_expression(&e);
	if (e.body.at(0) == 0){
		dynamic_cast<command *>(params.at(1))->run(new command("NOP"));
	}else{
		dynamic_cast<command *>(params.at(2))->run(new command("NOP"));
	}
}




// teacher functions
void yotka(std::vector<token*> params){
	for(auto p: params){
		if(p->name_is("expression")){
			expression e = *(dynamic_cast<expression *>(p)); //copy expression object
			evaluate_numeric_expression(&e);//evaluate and collapse expresison object
			std::cout << "Result: " << e.jen_print() << std::endl;
		}
	}
}
void nasim(std::vector<token*> params){
	for(auto p: params){
		if(p->name_is("expression")){
			expression e = *(dynamic_cast<expression *>(p)); //copy expression object
			evaluate_numeric_expression(&e);//evaluate and collapse expresison object
			if (e.body.size() > 1) break;
			if (e.body.at(0)->name_is("num")){
				params.clear();
				params.push_back(e.body.at(0));
				return;
			}
		}
	}
	std::cout << "Nasim: \"The Question was worded incorectly\"";
	params.clear();
	params.push_back(new function("nasim"));
}
void zen(std::vector<token*> params){
	for(auto p: params){
		if(p->name_is("expression")){
			expression e = *(dynamic_cast<expression *>(p)); //copy expression object
			evaluate_binary_expression(&e);//evaluate and collapse expresison object
			if (e.body.at(0)->name_is("num")){
				params.clear();
				params.push_back(e.body.at(0));
				return;
			}
		}
	}
}

//jen should never fail no matter what is passed to her
void jen(std::vector<token*> params){
	for(auto p: params){
		try{
			std::cout << p->jen_print() << std::endl;
		}catch(std::exception e){
			std::cout << "jen is confused\n";
		}
	}
}

void command::run(command * result) {result = this;}
void function::run(command * result){
	call_function(this->name, body, result);
}
void scope::run(command * result){
    for(auto i: body){
       command *cmd = dynamic_cast<command *>(i);
	   if (cmd != nullptr){
		   cmd->run(result);
	   }
    }
}
//if defined, invoke it
void call_function(std::string name, std::vector<token*> params, command * result){ 
	//result = return

    //wanted to use a map of function pointers and call 
    // map[name](result) but std::map wasnt working and idk...
	if(name == "yotka"){
		yotka(params);
	}else if((name.compare("jen") || name.compare("jennifer")) ){
		jen(params);
	}else if(name == "nasim"){
		nasim(params);
	}else if(name == "if"){
		_if(params);
	}
}
