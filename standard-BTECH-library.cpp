#include <iostream>
//include header

ostream build_func(function func){
  ostream os;

  
  //########## Teachers ########//
  //will calculate your result and show it for you but not give you the answer nor will he calculate simple problems
  if (func.name == nasim){
    if (func.trivial) os << "puts(\"The answer to \"" << func << "is trivial and left as an exersise;\n";
    else os << "printf(\"%d," << func << ");\n";
  }

  //will always give you the answer in a well meaning way but in a useless format/skipping steps
  if (func.name == yotka){
    os << "char* " << func._return << " = (*char)" << func;
  }


  //god is there for you and will help with anything you need invalidating the need for both yotka and nasim
  if (func.name == sesha){
    os << func._return << " = " << func;
  }

//wrapper for printf basically
  if (func.name == jen || func.name == comm){
    os << "printf(";
    for (auto &t: func){
      os << "," << t.format;
    }
    for (auto &t: func){
      os << "," << t.name;
    }
    os <<");";
    return os;
  }

//########### classes ##########//



//############ memes ############//
/** 
    figure out how to 
    catch SEGMENTATION_FAULT
    then -> puts("A wild tiger corrupted your memory")
    exit(0)    // -> remove informative exception for now
    catch GENERAL_EXCEPTION
    then -> puts("BAM tiger")
    exit(0)    // -> remove informative exception for now
**/
