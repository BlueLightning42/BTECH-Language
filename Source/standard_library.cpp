#include "BTECH.h"

using namespace BTECH;

void call_function(std::string, command *, command *);


void program::run_program(){
	std::cout << "\nRun Program:\n";
	for (auto i: ast){
		i->run();
	}
}
void generic_command::run(){
	for (auto i: body){
		i->run();
	}
}
void function::run(){
	command* temp = new command("tmp");

	call_function(this->name, (command *)(&body), temp);
	delete temp;
}



void yotka(command * params){
	if(params->name_is("op")){
		std::cout << "calc";
		//if fail break
		return;
	}
	std::cout << "Yotka doesn't know what to do with that";
}
void nasim(command * params, command * result){
	if(params->name_is("op")){
		*result = /*calc*/*params;
		//if fail break
		return;
	}
	result = new function("nasim");
}
//jen should never fail no matter what is passed to her
void jen(command * params){
	if(params->name_is("op")){
		std::cout << "calc";
		//if fail break
		return;
	}else{
		std::cout << "Jen tells you that you are important";
	}
}



//if defined, invoke it
void call_function(std::string name, command * params, command * result){ //result = return
	if(name == "yotka"){
		yotka(params);
		result = new function("yotka");
	}else if(name == "jen" || name == "jennifer"){
		jen(params);
		result = new function("jen");
	}else if(name == "nasim"){
		nasim(params, result);
	}
}
