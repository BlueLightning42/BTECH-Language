#include "BTECH.h"
using namespace BTECH;

// c++14 feature added to c++11 in a hack :3


std::set <char> ops = {'+','-','/','*','%','&','(',')','>','<','^','|','=','!',':','{','}'};
//token initializers

//first step is the parser will tokenize the file
bool program::build_program(std::string f){
	//short circuit if for adding a filename if its not there
	if((f.size() > 4) && (f.at(f.size()-4) != '.')){
		f.append(".btl");
	}
	// parse input into token array
	std::ifstream file;
	try{
		std::cout << "attempting to open file"<<std::endl;
		file.open(f.c_str());
		std::cout << "file opend sucessfully"<<std::endl;
	}catch(std::exception e){
		std::cout << "Error opening file"<<std::endl;
		return 1;
	}
	if(!file){
		std::cout << "File not found";
		return 1;
	}
	if(file.peek() == std::ifstream::traits_type::eof()){
		std::cout << "File is empty!";
		return 1;
	}
	std::string line;
	char next_character;
	while (!file.eof()){
		next_character = file.get();
		if(next_character == EOF) break;
		if (next_character == '#') {  // Stealing comment syntax from python
			// comment out whole line
			file.ignore(10000,'\n');

		}else if (next_character == '"') {  // build strings "
			getline(file, line,'"');
			tokens.push_back(BTECH::make_unique<_string>(line));

		}else if (next_character == '\'') {  // build strings '
			getline(file, line,'\'');
			tokens.push_back(BTECH::make_unique<_string>(line));

		}else if (next_character == '\n' ) {  // end of commands
			if(!tokens.empty()){
				if(tokens.back()->name != "EOL")//ignore multiple std::vector<std::unique_ptr<token> > (newlines
					tokens.push_back(BTECH::make_unique<_generic_token>("EOL"));
			}

		}else if (next_character == '\\' ) {  // end of commands
			file.ignore(1);//ignore backslash lines

		}else if (next_character == ' ' || next_character == '\t' || next_character == EOF) {  // end of commands
			continue;

		}else if (ops.find(next_character) != ops.end()) {  // build operators (single char)
			tokens.push_back(BTECH::make_unique<_operator>(next_character));

		}else  if (next_character == '.' || 
				   isdigit(next_character) || 
				  ((next_character == 'i'|| next_character == 'j') && isdigit(file.peek()))
		){
		// build numbers
			line = "";
			bool is_imaginary = false;
			if (next_character == 'i'|| next_character == 'j'){
				is_imaginary = true;
				next_character = file.get();
			}

			while(next_character == '.' || isdigit(next_character)){
				line += next_character; //file.get() not working?
				next_character = file.get();
			}
			if (next_character == 'i'|| next_character == 'j'){
				is_imaginary = true;
				next_character = file.get();
			}
			if(next_character != EOF) file.unget();

			tokens.push_back(BTECH::make_unique<_number>(line, is_imaginary));

		}else{  // build everything else
			line = "";
			while(next_character != ' ' && next_character != '\n' && next_character != '\t' && next_character != EOF && ops.find(next_character) == ops.end()){
				line += next_character; //file.get() not working?
				next_character = file.get();
			}
			if(next_character != EOF) file.unget();
			
			tokens.push_back(BTECH::make_unique<_generic_token>(line));
		}
	}file.close();
	if (tokens.size() < 1){
		std::cout << "File is Empty!";
		return 1;
	}
	if (tokens.back()->name_is("EOL"))
		tokens.pop_back();
	tokens.push_back(BTECH::make_unique<_generic_token>("EOF"));

	return 0;
};


// Alot of overlap but it would complicate reading it even more if I tried to combine them (from file and from console) into one function that uses either cin or ifstream...or seperate parts of it into even more functions.
std::vector<std::unique_ptr<token> > program::parse_line(){
	std::cout << "->";
	char next_character;
	bool not_escaped = true;
	tokens.clear();
	std::string line = "";
	while (std::cin.get(next_character)) {
		if (next_character == '"' || next_character == '\''){
			std::cin.get(next_character);
			while (!(next_character == '"' || next_character == '\'')){
				if (next_character == '\n'){
					std::cout << "  ";
				}
				line += next_character;
				
				std::cin.get(next_character);
			}
			tokens.push_back(BTECH::make_unique<_string>(line));
			continue;
		}
		if (next_character == '\\') not_escaped = false;
		if (next_character == '\n' && not_escaped) break;
		if (next_character == '\n') not_escaped = true;
		if(next_character == '#'){
			std::cin >> line;
			std::cout << '|' << line << '|';
			if (line == "help"){
				std::cout << "\n\tType a line you wish to execute\n\t" <<
							"shell specific commands:\n\t" << 
							"#end or #quit or #q to leave\n\t" << 
							"#d1 to turn on debugging or #d0 to turn it off\n\t" << 
							"#tree to show the current scoped tree\n\t|help|";
			}else if (line == "d1") {
				debug = 1;
				std::cout << " debugging ON";
			}else if (line == "d0") {
				debug = 0;
				std::cout << " debugging OFF";
			}else if (line == "end" || line == "quit" || line == "q") {
				tokens.push_back(BTECH::make_unique<_generic_token>("EOF"));
			}else if (line == "tree"){
				std::cout << _main;
			}else{
				std::cout <<" <- Unkown Command";
			}
			std::cout << std::endl;
		}
		if (ops.find(next_character) != ops.end()) {  // build operators (single char)
			tokens.push_back(BTECH::make_unique<_operator>(next_character));
			continue;			
		}

		if (next_character == '.' || 
				   isdigit(next_character) || 
				  (next_character == 'i' && isdigit(std::cin.peek()))
		){
		// build numbers again
			line = "";
			bool is_imaginary = false;
			if (next_character == 'i'){
				is_imaginary = true;
				next_character = std::cin.get();
			}

			while(next_character == '.' || isdigit(next_character)){
				line += next_character; //file.get() not working?
				next_character = std::cin.get();
			}
			if (next_character == 'i'){
				is_imaginary = true;
				next_character = std::cin.get();
			}
			if (next_character == '\n') std::cin.unget();
			tokens.push_back(BTECH::make_unique<_number>(line, is_imaginary));

		}
	}
	tokens.push_back(BTECH::make_unique<_generic_token>("EOL"));
	if(debug){
		for (const auto &tok: tokens){
			std::cout << *tok;
		}std::cout << std::endl;
	}
	return tokens;
}
