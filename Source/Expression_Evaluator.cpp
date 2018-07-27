#ifndef INCLUDED_EXPRESSION
#define INCLUDED_EXPRESSION


#include "BTECH.h"
using namespace BTECH;




/* As I write this I can feel myself give up... I couldn't write what I wanted ie
//template <typename N>
N _number::get_value() const{
	return floating_point ? f_val : i_val;
}
and short of making a seperate object for all 3 numbers this is all I can think to do...
this macro feels gross but I legit don't know how to use templates and the docs wont help and neither will stackoverflow
I'm not trying to obsfucate this I swear
*/
#define GET_VAL(param, i) (dynamic_cast<_number *>(param->expr.at(i))->get_value(dynamic_cast<_number *>(param->expr[i])->floating_point ? f : l))
#define GET_INT_VAL(i) (dynamic_cast<_number *>(param->expr.at(i))->get_value(l))
#define EVAL_TO_LAST(param, i, val) (param->expr[i] = new _number(val))
#define REMOVE_EXCESS_TOKENS(param, i) (param->expr.erase( (param->expr).begin()+i + 1, (param->expr).begin()+i +3))
//say it with me macooOOooroos are evvvvil :3<<<

void evaluate_numeric_expression(expression *param){

	// TODO  evaluate nested expression objects
	// TODO  replace any variables with thire scoped values or zero.
	// TODO call any functions in the expression - map trigometric functions etc

	//hacky variables used to call seperate overloaded functions
	double f = 0.0; long long l =0; 
	
	int i=0;

	while( i< (param->expr).size()-1){	
		if (param->expr[i]->type_is('!')){
			auto a = GET_INT_VAL(i+1);
			for(int i=a; i>0; i--){
				a *= i;
			}
			param->expr[i] = new _number( a );
			param->expr.erase(param->expr.begin()+i+1);
			continue;
		}
		i++;
	}
	i = 0;	//BEDMAS
	while( i+2 < (param->expr).size() ){
		if (param->expr[i+1]->type_is('/')){
			EVAL_TO_LAST(param, i, GET_VAL(param, i) / GET_VAL(param, i+2));
			REMOVE_EXCESS_TOKENS(param, i);
			continue;
		}
		if (param->expr[i+1]->type_is('*')){
			EVAL_TO_LAST(param, i, GET_VAL(param, i) * GET_VAL(param, i+2));
			REMOVE_EXCESS_TOKENS(param, i);
			continue;
		}
		i++;
	}
	i = 0;
	while( i+2< (param->expr).size() ){
		if (param->expr[i+1]->type_is('+')){
			EVAL_TO_LAST(param, i, (GET_VAL(param, i) + GET_VAL(param, i+2)));
			REMOVE_EXCESS_TOKENS(param, i);
			continue;
		}
		if (param->expr[i+1]->type_is('-')){
			EVAL_TO_LAST(param, i, GET_VAL(param, i) - GET_VAL(param, i+2));
			REMOVE_EXCESS_TOKENS(param, i);
			continue;
		}
		i++;
	}
}
_number evaluate_binary_expression(expression *param){
	// evaluate nested expression objects
	// replace any variables with thire scoped values or zero.
	//call any functions in the expression
	long long l = 0;;
	int i = 0;
	while( i< (param->expr).size()-2 ){
		if (param->expr[i]->type_is('&')){
			EVAL_TO_LAST(param, i, GET_INT_VAL(i-1) & GET_INT_VAL(i+1));
			REMOVE_EXCESS_TOKENS(param, i);

		}
		if (param->expr[i]->type_is('|')){
			EVAL_TO_LAST(param, i, GET_INT_VAL(i-1) | GET_INT_VAL(i+1));
			REMOVE_EXCESS_TOKENS(param, i);

		}
		if (param->expr[i]->type_is('+')){
			EVAL_TO_LAST(param, i, GET_INT_VAL(i-1) ^ GET_INT_VAL(i+1));
			REMOVE_EXCESS_TOKENS(param, i);
		}
		if (param->expr[i]->type_is('!')){
			param->expr[i-1] = new _number(~GET_INT_VAL(i+1));
			param->expr.erase(param->expr.begin()+i,param->expr.begin()+i + 1);
		}
		i++;
	}
	return *(dynamic_cast<_number *>(param->expr[0]));
}


#endif
