
#include "Variable.h"

Variable::Variable(char a, double b) : name(a), value(b){
}

std::ostream& operator<<(std::ostream& out, Variable variable){
	out<<variable.name<<" "<<variable.value;
	
}