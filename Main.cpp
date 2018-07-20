#include "BTECH.h"

int main(int argc, char *argv[]) {
	std::string f, line, tmp;
	int d=1; //debug
	BTECH::program* p;
	if(argc > 1){
		f = argv[1];  // TODO compiler flags later
		if (argv[1][0] == '-'){
			if (argv[1][1] = 'd'){
				try {
					d = std::stoi(std::string(std::string(argv[1], 2)));
				}catch(std::exception e){
					d = 1;
				}
			}
		}
		p = new BTECH::program(f,d);
		delete p;
	}else{
		std::cout << "Please enter the name of the script file\n"
				<<"followed by any flags (type flags to list all optional flags)\n"
				<<" OR type btech to enter the (semi) shell type q to quit.\n~>";
		while(getline(std::cin, line)){
			if(!line.compare("btech")){
				//p.shell;
			}else if(!line.compare("flags")){
				std::cout << "debugging flags:\n  -d0 nothing\n  -d1 (default) informative\n  -d2 verbose.\n~>";
			}else if(!line.compare("q")){
				break;
			}else{
				std::istringstream buff(line);
				buff >> f;
				while(buff >> tmp){
					if (tmp[0] == '-'){
						if (tmp[1] = 'd'){
							try {
								d = std::stoi(tmp.substr(2));
							}catch(std::exception e){
								d = 1;
							}
						}
					}
				}
				p = new BTECH::program(f,d);
				delete p;
				std::cout << "\n\nFeel free to run another script or type q to quit...\n~>";
				d=0;

			}
		}
	}
	return 0;
}
