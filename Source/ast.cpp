#include "BTECH.h"
//split vector of tokens created in parser into a tree of statements...
//stuff like   func_init: name
//             expression: number, operator, number


_operator::operation(){
		if (_type == '+')
			return left.value + right.value;
		
		if (_type == '-')
			return left.value - right.value;
		
		if (_type == '*')
			return left.value * right.value;
		
		if (_type == '/')
			return left.value / right.value;
		
		std::cout << "ERROR: unknown operator";
		return 0;
	}
	std::ostream& operator<<(std::ostream& os){
		os << this->_type;
		return os;
	}
	//pass defenition will be done in parser
}


// NUM SUB NUM MULT NUM ADD NUM DIV EXPRESSION      //math
class expression: command{
  public:
	expression(std::string n, std::vector <token> tokens): name(n){
		this->tokens = tokens;
		//sort to BEDMAS at some point with all constants near the start
		std::vector<token>::iterator itr = tokens.begin();
		while (itr != tokens.end()){
			if (tokens[*itr] = div || tokens[*itr] = mult){
				test(tokens[*itr-1],tokens[*itr],tokens[*itr+1])
			}
		}
		itr = tokens.begin();//reset iter
		while (itr != tokens.end()){
			if (tokens[*itr] = add || tokens[*itr] = sub){
				build(tokens[*itr-1],tokens[*itr],tokens[*itr+1])
			}
		}
	}
	build(token left, _operator op, token  right){
		if ((type(left) == number) && (type(right) == number) ){ 
			return (number_cast)_operator.operation(left,right);
		}
		 if (left == number) op.add(left, right);//build an operation object by shoving the left and right sides into the operator object
		 else op.add(right,left);
		return  op;
	}
}
class function: command{
	std::vector<token> param;
	std::vector<token> commands;
	token _return;
  public:
	function(std::string n,std::vector<token> tokens): name(n){
		std::vector<token>::iterator itr = tokens.begin();
		while (itr != tokens.end()){
			if (*itr == def) {
				//I know this syntax is wrong will fix later
				function f_( tokens[*itr-1].name, /** find params somehow **/, commands));
				commands.push_back(f_);
			}
			if(*itr == assignment){
				expression e_( tokens[*itr-1].name, commands));
				commands.push_back(e_);
			}
		}
	}
	std::ostream& operator<<(std::ostream& os){
		os << this->_return << " " << this->name  << " (";
		for (auto &t: param){//print everything in the stream
			os <<t.get_type() <<  t.name << ",";
		}
		os << "){\n"
		os<<func << "\n}\n";
		return os;
	}
}


