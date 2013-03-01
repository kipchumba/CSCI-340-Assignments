#include <iostream>
#include <string>
//#include "ExprTree.h"

class ExprTree;

class TNode {
	
	public:
		TNode(char a, double b);
		friend std::ostream& operator<<(std::ostream&, TNode&);
		friend class ExprTree;
	
	private:
		char type;
		double operandValue;
		TNode* left;
		TNode* right;
};
