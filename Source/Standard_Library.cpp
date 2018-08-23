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

typedef void (*BTECHFUNC)(std::shared_ptr<token>&, scope&);
void yotka(	std::shared_ptr<token>&,	scope&);
void jen(	std::shared_ptr<token>&,	scope&);
void nasim(	std::shared_ptr<token>&,	scope&);
void zen(	std::shared_ptr<token>&,	scope&);
void _if(	std::shared_ptr<token>&,	scope&);
void loop(	std::shared_ptr<token>&,	scope&);
void redef(	std::shared_ptr<token>&,	scope&);
const std::map<std::string, BTECHFUNC> standard_functions ={
	{"yotka", 			&yotka},
	{"jen", 			&jen},
	{"jennifer", 		&jen},
	{"zen", 			&zen},
	{"nasim", 			&nasim},
	{"if", 				&_if},
	{"reassignment", 	&redef},
	{"redef", 			&redef},
	{"loop", 			&loop}
};
std::map<std::string, BTECHFUNC> custom_functions;

//if defined, invoke it
void call_function(std::string name, std::shared_ptr<token>& params, scope& current_scope, int debug){ 
	//result = return
	
	auto std_func = standard_functions.find(name);
	auto cust_func = custom_functions.find(name);

	if (cust_func != custom_functions.end()){//custom functions have higher priority then standard
		if (debug > 2) std::cout << "Called Custom Function: " <<name<<" With -> " << *params << std::endl;
		cust_func->second(params, current_scope);
	}else if (std_func != standard_functions.end()){
		if (debug > 2) std::cout << "Called Standard Function: " <<name<<" With -> " << *params << std::endl;
		std_func->second(params, current_scope);
	}else{
		if (debug > 2) std::cout << "Called UNFOUND FUNCTION EXITING" << std::endl;
		auto tmp = std::make_shared<expression>("ERROR");
		tmp->body.push_back(std::make_shared<_string>(std::string("Function \"" + name + "\" not found!")));
		params = tmp;
	}
}


bool program::run_program(){
	std::shared_ptr<token> result = std::make_shared<expression>();
	scope scp("to trash");
	this->_main.run(result,scp, this->debug);

	if (result->name_is("ERROR")){
		if (this->debug > 2) std::cout << ".\n->========================== ERROR ===========================\n";
		std::dynamic_pointer_cast<expression>(result)->out_print();
		std::cout << "\n==============================================================";
		return 1;
	}/*else*/
	if (this->debug > 2) std::cout << ".\n->========================= Output ===========================\n";
	std::dynamic_pointer_cast<expression>(result)->out_print();
	return 0;
}



void _if(std::shared_ptr<token>& params, scope& current_scope){
	//evaluate_binary_expression(&e);
	/*if (e.body.at(0) == 0){
		dynamic_cast<command *>(params.at(1))->run(new command("NOP"));
	}else{
		dynamic_cast<command *>(params.at(2))->run(new command("NOP"));
	}*/
}
void loop(std::shared_ptr<token>& params, scope& current_scope){
}
void redef(std::shared_ptr<token>& params, scope& current_scope){
	auto tmp = std::dynamic_pointer_cast<expression>(params);
	for(auto it: current_scope.pointers){
		if(it->name_is(tmp->body.at(0)->name)){
			tmp->body.erase(tmp->body.begin(), tmp->body.begin() + 2);
			it->contents = tmp;
			return;
		}
	}

	auto err = std::make_shared<expression>("ERROR");
	err->body.push_back(std::make_shared<_string>(std::string( tmp->body.at(0)->name + "not found!")));
	params = err;
	
}


// teacher functions
void yotka(std::shared_ptr<token>& params, scope& current_scope){
	/*for(const auto &p: params){
		if(p->name_is("expression")){
			expression e = *(dynamic_cast<expression *>(p)); //copy expression object
			//evaluate_numeric_expression(&e);//evaluate and collapse expresison object
			std::cout << "Result: " << e.jen_print() << std::endl;
		}
	}*/
}
void nasim(std::shared_ptr<token>& params, scope& current_scope){
	if(params->name_is("expression")){
		//expression e = *(dynamic_cast<expression *>(p)); //copy expression object
		//evaluate_numeric_expression(&e);//evaluate and collapse expresison object
		//if (e.body.size() > 1) break;
		//if (e.body.at(0)->name_is("num")){
			//params.clear();
			//params.push_back(e.body.at(0));
			return;
		//}
	}
	std::cout << "Nasim: \"The Question was worded incorectly\"";
	params = (std::make_shared<function>("nasim"));
}
void zen(std::shared_ptr<token>& params, scope& current_scope){
	if(params->name_is("expression")){
		//expression e = *(dynamic_cast<expression *>(p)); //copy expression object
		//evaluate_binary_expression(&e);//evaluate and collapse expresison object
		//if (e.body.at(0)->name_is("num")){
			//params.clear();
			//params.push_back(e.body.at(0));
			return;
	}
}

//jen should never fail no matter what is passed to her
void jen(std::shared_ptr<token>& params, scope& current_scope){
	std::stringstream tmp;
	try{
		params->jen_print(tmp, current_scope);
	}catch(std::exception e){//doesn't do shit...
		tmp << "jen is confused\n";
	}
	for(auto it: current_scope.pointers){
		if(it->name_is("nl")){ //done this way so you can overwrite the standard new line object
			it->jen_print(tmp, current_scope);
		}
	}
	params = std::make_shared<_string>(tmp.str());

}
void pointer::run(std::shared_ptr<token>& result, scope& current_scope, int debug) {
	contents->run(result, current_scope, debug);
} //forward
void command::run(std::shared_ptr<token>& result, 	 scope& c, int d) {} //forward
void expression::run(std::shared_ptr<token>& result, scope& c, int d) {} //forward
void function::run(std::shared_ptr<token>& result,	 scope& c, int d) {
	result = body;
	call_function(this->name, result, c, d);
}
void scope::run(std::shared_ptr<token> &top_result, scope& current_scope, int debug){
	if (debug>2) std::cout << "Entered Scope: "<< this->name <<std::endl;
	auto result = std::make_shared<token>("NOP");
	for(auto i: this->body){
		if (i != nullptr){
			i->run(result,*this, debug);
			if (result->name_is("string")){
				std::dynamic_pointer_cast<expression>(top_result)->body.push_back(result);
			}else if (result->name_is("ERROR")){
				top_result = result;
				return; //break out in the case of a error
			}
		}
	}
	if (debug>2) std::cout << "Scope: "<< this->name << " Exited" <<std::endl;
}
