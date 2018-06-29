#include "BTECH.h"
token EndOfFile;
program::program(){
        //parse input into token array
        std::string file;
        for (std::string::iterator c = file.begin(); c++) {
            if (*c == ' ' || *c == '	') { continue; }

            if (*c == '"' || *c == '\'') {//build strings
                c++;
                unsigned dlim_start = *c;
                while ((*c == '"' || *c == '\'') && (*c-1 != '\\')) {c++;} //escaped quotes
                
                _string s(file.substr(dlim_start, c));
                tokens.push_back(s);
            }

            if (*c == '\n' && *c-1 != '\\') {
                tokens.push_back(EndOfFile);
                return;
            }

            if (*c == '+' || *c == '-' || *c == '*' || *c == '/') {
                _operator op(*c);
            }

        }
    }

};