
#include <iostream>
#include <vector>
#include "Variable.h"
#include "TNode.h"

class ExprTree {
	public:
		ExprTree() : root(NULL){}
		ExprTree(const std::string& s) {build(s);}
		ExprTree(const ExprTree&);
		~ExprTree(){destroy(root);}
		void clear ();
		ExprTree& operator=(const ExprTree&);
		void build (const std::string&);
		double evaluate () const{return evaluate(root);}
		void printInOrder() const;
		void printPostOrder() const;
		void printLevel() const;
		void setVariable(char, double);
		double getVariable(char) const ;
		void printVariables();
		
		
	private:
		TNode* root;
		std::vector<Variable> variables;
		void destroy(TNode*);
		double evaluate (TNode*) const;
		void printInOrder(TNode*) const;
		void printPostOrder(TNode*) const;
		TNode* copyHelper (const TNode*);
		
};
