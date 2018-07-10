#include "Source/BTECH.h"

int main(int argc, char *argv[]) {
	std::string f;
	BTECH::program p;

	if(argc > 1){
		f = argv[1];  // TODO compiler flags later
	}else{
		std::cout << "Please enter the name of the program file";
		std::cin >> f;
	}
	p.build_program(f);

	return 0;
}
