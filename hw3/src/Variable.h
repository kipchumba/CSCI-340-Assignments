
#include <iostream>
#include <string>
//#include "ExprTree.h"

class ExprTree;

class Variable {
	
	public:
		Variable(char, double);
		friend std::ostream& operator<<(std::ostream&, Variable);
		friend class ExprTree;
		
	private:
		char name;
		double value;
		

};