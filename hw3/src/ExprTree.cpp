
#include <stack>
#include <stdlib.h>
#include <sstream>
#include <queue>
#include "ExprTree.h"
/** some constants used **/
const char A_NUMBER='#';
const char PLUS='+';
const char MINUS='-';
const char DIVIDE='/';
const char MULTIPLY='*';
const std::string ALPHABET ("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

/** declarations of helper functions **/
std::string doubleToString(double);
bool isOperation (char);
bool isAlphabet (char);

/*===================ExprTree Methods==========================*/

/*
 * Method Name  : ExprTree
 * Synopsis     : Tree::ExprTree(const ExprTree& right) *
 * Arguments    : const  ExprTree : 
 * Description  : copy constructor
 */
ExprTree::ExprTree(const ExprTree& right){
	root=copyHelper(right.root);
	variables=right.variables;
}


/*
 * Method Name  : clear
 * Synopsis     : void ExprTree::clear () *
 * Description  : deletes all the dynamic memory of the Tree
 */
void ExprTree::clear (){
	destroy(root);
	root=NULL;
}


/*
 * Synopsis     : Tree::operator= (const ExprTree& right) *
 * Arguments    : const  ExprTree& : 
 * Description  : assignment operator
 */
ExprTree& ExprTree::operator= (const ExprTree& right){
	root=copyHelper(right.root);
	variables=right.variables;
}


/*
 * Method Name  : build
 * Synopsis     : void ExprTree::build (const std::string& s) *
 * Arguments    : const  std::String&
 * Description  : builds an expression tree from the given string
 */
void ExprTree::build (const std::string& s){
	std::stack<TNode*> holder;
	int i=0;
	
	while (i<s.length()){
		char varChar=s.at(i);
		
		if (isspace(varChar)){
			i++;
		}
		
		else if (isAlphabet(varChar)){
			TNode* newNode= new TNode(varChar,0.0);
			holder.push(newNode);
			i++;
		}
		
		else if (isOperation(varChar)){
			
			if ((i==s.length()-1)||(i<(s.length()-1)&&isspace(s.at(i+1)))){
				TNode* newNode= new TNode(varChar,0.0);
				newNode->right=holder.top();
				holder.pop();
				newNode->left=holder.top();
				holder.pop();
				holder.push(newNode);
				i++;
			}
			else {
				std::string temp= s.substr(i); 
				char* pEnd;
				double number=strtod(temp.c_str(), &pEnd);
				TNode* newNode= new TNode(A_NUMBER, number);
				holder.push(newNode);
				
				int size= (doubleToString(number)).length();
				i+=size;
			} 
			
		}
		
		else {
			std::string temp= s.substr(i); 
			char* pEnd;
			double number=strtod(temp.c_str(), &pEnd);
			//std::cout<<i<<" "<<number<<std::endl;
			TNode* newNode= new TNode(A_NUMBER, number);
			holder.push(newNode);
			int size= (doubleToString(number)).length();
			i+=size;
		}
	}
	root=holder.top();
}

/*
 * Method Name  : printInOrder
 * Synopsis     : void ExprTree::printInOrder()  *
 * Description  : prints the expression tree usind in order traversal, 
 *				  using () to deparate operations
 */
void ExprTree::printInOrder() const{
	printInOrder(root);
	std::cout<<std::endl;
}

/*
 * Method Name  : printPostOrder
 * Synopsis     : void ExprTree::printPostOrder()  *
 * Description  : prints the expression tree using post order traversal, 
 */
void ExprTree::printPostOrder() const{
	printPostOrder(root);
	std::cout<<std::endl;
}

/*
 * Method Name  : printLevel
 * Synopsis     : void ExprTree::printLevel()  *
 * Description  : prints the tree level by level till it reaches the leaves
 */
void ExprTree::printLevel() const{
	if (root==NULL)
		return;
	std::queue<TNode* > que;
	TNode *tempNode, *tempLeft, *tempRight;
	que.push(root);
	que.push(NULL);
	
	while (!que.empty()){
		tempNode=que.front();
		que.pop();
		if (tempNode!=NULL){
			std::cout<<*tempNode<<" ";
			tempLeft=tempNode->left;
			tempRight=tempNode->right;
			if (tempLeft)
				que.push(tempLeft);
			if (tempRight)
				que.push(tempRight);
		}
		
		else {
			if (!que.empty())
				que.push(NULL);
		}
	}
	std::cout<<std::endl;
}

/*
 * Method Name  : setVariable
 * Synopsis     : void ExprTree::setVariable(char varName, double val) *
 * Arguments    : char  varName: 
 *                double   val:
 * Description  : changes the value of the varName variable, and if not found, 
				  then a new variable with varName as its name and val as its value is added
 */
void ExprTree::setVariable(char varName, double val){
	std::vector<Variable>::iterator start= variables.begin();
	std::vector<Variable>::iterator end= variables.end();
	
	while (start!=end){
		if (varName==(start->name)){
			start->value=val;
			return;
		}
		start++;
	}
	
	Variable var(varName, val);
	variables.push_back(var);
	return;
}


/*
 * Method Name  : getVariable
 * Synopsis     : double ExprTree::getVariable (char varName)  *
 * Arguments    : char  varName : 
 * Description  :  checks for the existence of the varName variable and returns its
				   value, and if it is not there, then it returns 0.0
 */
double ExprTree::getVariable (char varName) const{
	
	int i=0;
	while (i<variables.size()){
		if (varName==(variables[i].name))
			return variables[i].value;
		i++;
	}
	return 0.0;
}

/*
 * Method Name  : printVariables
 * Synopsis     : void ExprTree::printVariables() *
 * Description  : prints the variables contained in the vector in a single line
 */
void ExprTree::printVariables(){
	std::vector<Variable>::iterator start= variables.begin();
	std::vector<Variable>::iterator end= variables.end();
	
	while (start!=end){
		std::cout<<*start<<" ";
		start++;
	}
	std::cout<<std::endl;
	return;
}

/*
 * Method Name  : destroy
 * Synopsis     : void ExprTree::destroy (TNode* node) *
 * Arguments    : TNode * node : 
 * Description  : uses post order recursion to delete a node and its subtree
 */
void ExprTree::destroy (TNode* node){
	if (node==NULL)
		return;
	TNode* toDestroy;
	destroy (node->left);
	destroy (node->right);
	toDestroy=node;
	node=NULL;
	delete toDestroy;
	return;
}

/*
 * Method Name  : evaluate
 * Synopsis     : double ExprTree::evaluate (TNode* node)  *
 * Arguments    : TNode * node : 
 * Description  : uses also post order recursion to calculate the value of the node
 * Returns      : double 
 */
double ExprTree::evaluate (TNode* node) const{
	if (node==NULL)
		return 0.0;
	else if (node->type==A_NUMBER)
		return node->operandValue;
		
	else if (isAlphabet(node->type))
		return getVariable(node->type);
		
	else if (isOperation(node->type)){
		double leftValue=evaluate(node->left);
		double rightValue=evaluate(node->right);
		if (node->type==PLUS)
			return (leftValue+rightValue);
		else if (node->type==MINUS)
			return (leftValue-rightValue);
		else if (node->type==MULTIPLY)
			return (leftValue*rightValue);
		else 
			return (leftValue/rightValue);
	}
		
}

void ExprTree::printInOrder(TNode* node) const{
	if (node==NULL) return;
	std::cout<<"( ";
	printInOrder(node->left);
	std::cout <<*node<<" ";
	printInOrder(node->right);
	std::cout<<" )";
}

void ExprTree::printPostOrder(TNode* node) const{
	if (node==NULL) return;
	printPostOrder(node->left);
	printPostOrder(node->right);
	std::cout<<*node<<" ";
}

/*
 * Method Name  : copyHelper
 * Synopsis     : TNode* ExprTree::copyHelper (const TNode* toCopy) *
 * Arguments    : const TNode * toCopy : 
 * Description  : recursively builds a tree 
 * Returns      : the root of the tree built
 */
TNode* ExprTree::copyHelper (const TNode* toCopy){
	if (toCopy==NULL)
		return NULL;
	TNode* copyNode= new TNode(toCopy->type,toCopy->operandValue);
	copyNode->left=copyHelper(toCopy->left);
	copyNode->right=copyHelper(toCopy->right);
	return copyNode;
}

/*
 * Name         : doubleToString
 * Synopsis     : string doubleToString(double val) *
 * Arguments    : double  val : 
 * Description  : converts a double to a string
 * Returns      : string 
 */
std::string doubleToString(double val){
   std::ostringstream out;
   out<<val;
   return out.str();
}


/*
 * Name         : isOperation
 * Synopsis     : bool isOperation (char a) *
 * Arguments    : char  a : 
 * Description  : checks whether the char value represents an operation
 * Returns      : bool 
 */
bool isOperation (char a){
	if (a==PLUS)
		return true;
	else if (a==MINUS)
		return true;
	else if (a==DIVIDE)
		return true;
	else if (a==MULTIPLY)
		return true;
	else 
		return false;
}

/*
 * Name         : isAlphabet
 * Synopsis     : bool isAlphabet(char a) *
 * Arguments    : char  a : 
 * Description  : checks whether the char value is an alphabet value
 * Returns      : bool 
 */
bool isAlphabet(char a){
	for (int i=0;i<ALPHABET.size();i++){
		char temp=ALPHABET.at(i);
		if (a==temp)
			return true;
	}
	return false;
}