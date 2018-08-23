#include "Source/BTECH.h"
/*
If anyone ever reads this I advise not looking in Source Folder
any code located in there runs on black magic and hot glue (a mess of design choices and abuse of pointers)
this was written as a way for me to learn the stl and after reaching a certain point bad practices started to creep in as I tried to implement stuff.
*/
int main(int argc, char *argv[]) {
	std::string f, line, tmp;
	int d=1; //debug level is 1 by default
	BTECH::program* p;

	if(argc > 1){
		f = std::string(argv[1]);  // TODO more compiler flags later
		for(int i=1; i<argc; i++){
			if (argv[i][0] == '-'){
				if (argv[i][1] == 'd'){
					try {
						d = std::stoi(std::string(std::string(argv[i], 2)));
					}catch(std::exception e){
						d = 1;
					}
				}
			}
		}
		p = new BTECH::program(f,d);
		delete p;
	}else{
		std::cout << "Please enter the name of the script file\n"
				<<"followed by any flags (type flags to list all optional flags)\n"
				<<" OR type btech (or shell) to enter the (semi) shell OR type q to quit.\n~>";
		while(getline(std::cin, line)){
			if(!line.compare("btech") || !line.compare("shell")){
				p = new BTECH::program();
				delete p;
			}else if(!line.compare("flags")){
				std::cout << "debugging flags:\n  -d0 nothing\n  -d1 (default) informative\n  -d2 verbose.\n~>";
			}else if(!line.compare("q")){
				break;
			}else{
				std::istringstream buff(line);
				buff >> f;
				while(buff >> tmp){
					if (tmp[0] == '-'){
						if (tmp[1] == 'd'){
							try {
								d = std::stoi(tmp.substr(2));
							}catch(std::exception e){
								d = 2;
							}
						}
					}
				}
				p = new BTECH::program(f,d);
				delete p;
				std::cout << "\n\nFeel free to run another script or type q to quit...\n~>";
				d=1;
			}
		}
	}
	return 0;
}
