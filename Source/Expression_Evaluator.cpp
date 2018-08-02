#ifndef INCLUDED_EXPRESSION
#define INCLUDED_EXPRESSION

#include "BTECH.h"
using namespace BTECH;



/* As I write this I can feel myself give up... I couldn't write what I wanted ie
template <typename N>
N _number::get_value() const{
	if (imaginary) return c_val;
	return floating_point ? f_val : i_val;
}
and nesting functions doesn't work for what I want cause I have to define a seperate function for every expression which grows in complexity for each token I add.
same with putting the logic for adding inside each number class and overloading the operators
and short of making a seperate object for all 3 numbers/a seperate templated function for every possible input this is all I can think to do...
these macros feels gross but I legit don't know how to use templates to do what I want and the docs wont help and neither will stackoverflow
I'm not trying to obsfucate this I swear
*/
#define CASTBODY(i) dynamic_cast<_number *>(param->body.at(i))
#define GET_INT_VAL(i) (CASTBODY(i)->get_value(l))
/*
#define GET_VAL(i) ((CASTBODY(i)->imaginary) ? (CASTBODY(i)->c_val) : \
			((CASTBODY(i)->floating_point) ? (CASTBODY(i)->f_val) : (CASTBODY(i)->i_val)))
*/ 
#define GET_VAL(i) (CASTBODY(i)->get_value((CASTBODY(i)->floating_point) ? f : l))


inline void delete_next_two(std::vector<token*> *expr, int i){
	std::for_each(expr->begin()+i+1, expr->begin()+i+3, delete_pointed_to<token>);
	expr->erase( expr->begin()+i+1, expr->begin()+i+3);
}
// function like macro's I can pass operator tokens :3
// evaluate a bidirectional token  (ex a + b   or   a / b )
#define EVAL_BI_TOKEN(alias, tok) do{ i=0;										\
	while( i+2 < (param->body).size() ){ 										\
		if (param->body.at(i+1)->type_is( alias )){								\
			if (CASTBODY(i)->imaginary || CASTBODY((i+2))->imaginary){			\
dynamic_cast<_number *>(param->body[i])->remake( (CASTBODY(i)->get_value_i()) tok (CASTBODY((i+2))->get_value_i()));\
			}else{ 																\
dynamic_cast<_number *>(param->body[i])->remake( (GET_VAL(i) tok GET_VAL((i+2))) );			\
			}																	\
			delete_next_two(&param->body, i);									\
			continue;															\
		}i++;																	\
	}} while(0)
//for operations that only work on integers
#define EVAL_BI_INT_TOKEN(alias, tok) do{ i=0;										\
	while( i+2 < (param->body).size() ){ 										\
		if (param->body.at(i+1)->type_is( alias )){								\
dynamic_cast<_number *>(param->body[i])->remake( (CASTBODY(i)->get_value(l)) tok (CASTBODY((i+2))->get_value(l)));\
			delete_next_two(&param->body, i);									\
			continue;															\
		}i++;																	\
	}} while(0)
//for functions that only work on floating point stuff
#define EVAL_BI_REAL_FUNCTION(alias, func) do{ i=0;										\
	while( i+2 < (param->body).size() ){ 										\
		if (param->body.at(i+1)->type_is( alias )){								\
			CASTBODY(i)->remake( ( func(GET_VAL(i) , GET_VAL((i+2)) ) ) );		\
			delete_next_two(&param->body, i);									\
			continue;															\
		}i++;																	\
	}} while(0)
// evaluate a bidirectional funciton  (ex a^b -> pow(a,b))
#define EVAL_BI_FUNCTION(alias, func) do{ i=0;									\
	while( i+2 < (param->body).size() ){ 										\
		if (param->body.at(i+1)->type_is( alias )){								\
			if (CASTBODY(i)->imaginary || CASTBODY((i+2))->imaginary){			\
CASTBODY(i)->remake( func((CASTBODY(i)->get_value_i()) , (CASTBODY((i+2))->get_value_i())) ); \
			}else{ 																\
				CASTBODY(i)->remake( ( func(GET_VAL(i) , GET_VAL((i+2)) ) ) );	\
			}																	\
			delete_next_two(&param->body, i);									\
			continue;															\
		}i++;																	\
	}} while(0)



//say it with me macooOOooroos are evvvvil :3<<<

void evaluate_numeric_expression(expression *param){
	// TODO  evaluate nested expression objects
	// TODO  replace any variables with thire scoped values or zero.
	// TODO call any functions in the expression - map trigometric functions etc

	//hacky variables used to call seperate overloaded functions
	double f = 0.0; long long l =0; char c = 'p';
	int i=0;

	while( i< (param->body).size()-1){	
		if (param->body[i]->type_is('!')){
			auto a = GET_INT_VAL((i+1));
			for(int i=a; i>0; i--){
				a *= i;
			}
			CASTBODY(i)->remake( a );
			param->body.erase(param->body.begin()+i+1);
			continue;
		}
		i++;
	}
	
	//originally had stringnation but now it works for different types of expressions that use the same token
	//BEDMAS
	for (auto e: param->body){
		if (e->name_is("expression")){
			evaluate_numeric_expression(dynamic_cast<expression *>(e));
		}
	}
	i = 0;
	// new format   alias, function
	EVAL_BI_FUNCTION( '^' , std::pow );
	EVAL_BI_REAL_FUNCTION( '<' , std::polar );  // 5<0.5 polar form
	
	// new format   alias, operator
	EVAL_BI_TOKEN('/', / );
	EVAL_BI_TOKEN('*', * );
	EVAL_BI_TOKEN('+', + ); 
	EVAL_BI_TOKEN('-', - ); 
	
}
_number evaluate_binary_expression(expression *param){
	// evaluate nested expression objects
	// replace any variables with thire scoped values or zero.
	//call any functions in the expression
	long long l = 0;double f=0.0;
	int i = 0;
	EVAL_BI_INT_TOKEN('&', & );
	EVAL_BI_INT_TOKEN('|', | );
	EVAL_BI_INT_TOKEN('+', ^ ); 

	
	
	/*
	while( i< (param->body).size()-2 ){
		if (param->body[i]->type_is('&')){
			EVAL_TO_LAST(param, i, GET_INT_VAL(i-1) & GET_INT_VAL(i+1));
			REMOVE_EXCESS_TOKENS(param, i);

		}
		if (param->body[i]->type_is('|')){
			EVAL_TO_LAST(param, i, GET_INT_VAL(i-1) | GET_INT_VAL(i+1));
			REMOVE_EXCESS_TOKENS(param, i);

		}
		if (param->body[i]->type_is('+')){
			EVAL_TO_LAST(param, i, GET_INT_VAL(i-1) ^ GET_INT_VAL(i+1));
			REMOVE_EXCESS_TOKENS(param, i);
		}
		if (param->body[i]->type_is('!')){
			param->body[i-1] = new _number(~GET_INT_VAL(i+1));
			param->body.erase(param->body.begin()+i,param->body.begin()+i + 1);
		}
		i++;
	}*/
	return * CASTBODY(0);
}
// I'm sorry for using macro's in c++11 >_<
#endif
