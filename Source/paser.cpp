#include "BTECH.h"
token EndOfLine("EOL"), EndOfFile("EOF");
std::set <char> ops = {'+','-','/','*','%','&','(',')','>','<','^','|','=','!'};
program::program(){
    // parse input into token array
    std::string file;
    for (std::string::iterator c = file.begin(); c++) {
        if (*c == '"' || *c == '\'') {  // build strings
            c++;
            unsigned dlim_start = *c;
            while (!(*c == '"' || *c == '\'') && (*c-1 == '\\')) {c++;}  // escaped quotes

            _string s(file.substr(dlim_start, c));
                tokens.push_back(s);
        }
        else if (*c == '\n' && *c-1 != '\\') {  // end of commands
            tokens.push_back(EndOfLine);
            return;
        }
        else if (ops.find(*c) != ops.end()) {  // build operators
            _operator op(*c);
        }
        else  if (*c == '.' || *c == 'i' || isdigit(c*)){  // build numbers
            unsigned dlim_start = *c;
            while (!(*c == ' ' || *c == '	' || c* == '\n' || ops.find(*c)) {c++;}  // escaped quotes not space newline or operator

           std::string temp = (file.substr(dlim_start, c);
                if (temp[0] == 'i'){
                    tokens.push_back(imaginary(std::stod(temp));
                }else if (temp.find('.')){
                    tokens.push_back(_double(std::stod(temp));		   	
                }else{
                    tokens.push_back(std::stoi(temp));
                }
        }
        else{  // build everything else
            unsigned dlim_start = *c;
            while (!(*c == ' ' || *c == '	' || c* == '\n' || ops.find(*c)) {c++;}

            token t(file.substr(dlim_start, c));
            tokens.push_back(t);
        }
    tokens.push_back(EndOfFile);
    }
};
