/* Probably not the best name for this file but...
   as I'm putting all of the "reserved" funcitons in here along with the logic of calling them Idk
*/
#include "BTECH.h"

using namespace BTECH;

void call_function(std::string, command *, command *);


void program::run_program(){
	if(debug) std::cout << "\nRun Program:";
	else std::cout<<'.';
	std::cout<< std::endl << std::string(30-program_name.size()/2, '=')
			 << ' ' << this->program_name << ' '  
			 << std::string(30-program_name.size()/2 - program_name.size()%2, '=') << std::endl;
	command * result = new function("test");
    ast->run(result);
	
	std::cout << std::endl << std::string(62, '=');

    if (result->name_is("ERROR"))
        std::cout << "Error Running Program";
    delete result;
}




void yotka(command * params){
	if(params->name_is("op")){
		std::cout << "calc";
		//if fail break
		return;
	}
	std::cout << "Yotka doesn't know what to do with that";
}
void nasim(command * result){
	if(result->name_is("op")){
		*result = /*calc*/*result;
		//if fail break
		return;
	}
	result = new function("nasim");
}


//================= jen =====================//
std::string token::jen_print() const{return "";}
std::string command::jen_print() const{return "";}
std::string _generic_token::jen_print() const{
	return this->name;
}
std::string _operator::jen_print() const{
	return std::string(1, this->_type);
}
std::string _string::jen_print() const{
	return this->contents;
}
std::string function::jen_print() const{
	if(this->name_is("nasim") || this->name_is("yotka")){
		return "*jen* A wonderfull colegue\n";
	}else if (this->name_is("jen")){
		return "*jen* That is my name yes\n";
	}else{
		return this->name + ' ';
	}	
}
std::string generic_command::jen_print() const{
	std::string temp;
	 if (!this->body.empty()){
		for(auto i: body){ //::const_iterator
			temp += i->jen_print();
		}
	}
	return temp;
}
std::string scope::jen_print() const{
	std::string temp;
	 if (!this->body.empty()){
		for(auto i: body){ //::const_iterator
			temp += i->jen_print();
		}
	}
	return temp;
}
std::string expression::jen_print() const{
	std::string temp = "A math Expression: ";
	for(auto i: this->expr){
		temp += i->jen_print();
	}
	return temp;
}
//jen should never fail no matter what is passed to her
void jen(command * params){
	std::cout << " hi";
	try{
		std::cout << params->jen_print() << std::endl;
	}catch(std::exception e){
		std::cout << "jen is confused\n";
	}
}

void function::run(command * result){
	call_function(this->name, (command *)(&body), result);
}
void scope::run(command * result){
    for(auto i: body){
        (*i).run(result);
    }
}
//if defined, invoke it
void call_function(std::string name, command *params, command * result){ 
	//result = return
	params->run(result); //nesting

    //wanted to use a map of function pointers and call 
    // map[name](result) but std::map wasnt working and idk...
	if(name == "yotka"){
		yotka(result);
	}else if(!(name.compare("jen") + name.compare("jennifer")) ){
		jen(result);
	}else if(name == "nasim"){
		nasim(result);
	}
}
