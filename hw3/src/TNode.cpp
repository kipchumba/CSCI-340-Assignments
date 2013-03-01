
#include "TNode.h"

TNode::TNode(char a, double b=0.0) : type(a), operandValue(b){left=NULL;right=NULL;}


std::ostream& operator<<(std::ostream& out, TNode& node){
	if (node.type=='#')
		out<<node.operandValue;
	else 
		out<<node.type;
}