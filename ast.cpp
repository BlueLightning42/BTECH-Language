//split vector of tokens created in parser into a tree of statements...
//stuff like   func_init: name
//             expression: number, operator, number

class token{
public:
	//pass defenition will be done in parser
}
class number: token(){
public:
	//pass defenition will be done in parser
}
class complex: number(){
	std::complex value;
  public:
	number(std::complex v):value(v) {};
}
class integer: number(){
	int value;
  public:
	number(int v):value(v) {};
}
class floating_point: number(){
	double value;
  public:
	number(double v):value(v) {};
}
class command(){
 public:
 	std::string name;
	std::vector <token> tokens;
	std::ostream& operator<<(std::ostream& os, std::vector<tokens>& tok){
		os << this->name  << " (";
		for (auto &t: tok){//print everything in the stream
			os << t;
		}
		os << ")\n"
		return os;
	}
}
// NUM SUB NUM MULT NUM ADD NUM DIV EXPRESSION      //math
class expression: command{
	public:
	expression(name, std::vector <token> tokens){
	this->name = name;
		this->tokens = tokens;
		//sort to BEDMAS
		std::vector<token>::iterator itr = tokens.begin();
		while (itr != tokens.end()){
			if (tokens[*itr] = div || tokens[*itr] = mult){
				test(tokens[*itr-1],tokens[*itr],tokens[*itr+1])
			}
		}
		itr = tokens.begin();//reset iter
		while (itr != tokens.end()){
			if (tokens[*itr] = add || tokens[*itr] = sub){
				test(tokens[*itr-1],tokens[*itr],tokens[*itr+1])
			}
		}
	}
	test(token left, token _operator, token  right){
		if ((type(left) == number) && (type(right) == number) ){ 
			return (number_cast)_operator.operation(left,right);
		}
		 if (left == number) _operator.add(left, right);//build an operation object by shoving the left and right sides into the operator object
		 else _operator.add(right,left);
		return  _operator;
	}
}
class function: command{
public:
	function(name, tokens){
		this->name = name;
		//build function recursivly
	}
}


