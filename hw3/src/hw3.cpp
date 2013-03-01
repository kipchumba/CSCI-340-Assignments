#include <iostream>
#include <iomanip>
#include <string>

#include "ExprTree.cpp"

using std::cout;
using std::endl;
using std::string;

int main()
   {
   
   cout << "Test 1: Constructor and build function\n\n";
   
   string s1 = "3.5 2.7 + -4.7 2.64 * -";
   const ExprTree t1(s1);
   
   cout << "Test 2: Postorder traversal\n\n";
   cout << "Original expression string: " << s1 << endl;
   cout << "Postorder traversal of t1:  ";
   t1.printPostOrder();
   
   cout << "\nTest 3: Evaluate tree\n\n";
   
   cout << "Value of expression represented by t1 = " << t1.evaluate() << endl;

   cout << "\nTest 4: Inorder traversal\n\n";

   cout << "Inorder traversal of t1: ";

   t1.printInOrder();

   cout << "\nTest 5: Level-by-level traversal\n\n";

   cout << "Level-by-level traversal of t1: ";
   
   t1.printLevel();

   cout << "\nTest 6: Copy constructor\n\n";

   ExprTree t2 = t1;
   
   cout << "Postorder traversal of t2: ";
   
   t2.printPostOrder();
   
   cout << "\nTest 7: Clear t2\n\n";
   
   t2.clear();
   
   cout << "Level-by-level traversal of t2: ";
   t2.printLevel();
   
   cout << "\nTest 8: Build new tree with variables\n\n";
   
   t2.build("A 47.2 + B - 36 C / *");
   t2.setVariable('A', 10);
   t2.setVariable('B', 25);
   t2.setVariable('C', 2);

   cout << "Original expression string: " << "A 47.2 + B - 36 C / *" << endl;
   cout << "Postorder traversal of t2:  ";
   t2.printPostOrder();

   cout << "\nTest 9: Printing variables of t2\n\n";
     
   t2.printVariables();
   
   cout << "\nValue of expression represented by t2 = " << t2.evaluate() << endl;
   
   cout << "\nTest 10: Assignment operator\n\n";
   
   ExprTree t3;
   t3 = t2;

   cout << "Postorder traversal of t3:  ";
   t3.printPostOrder();

   cout << "\nTest 11: Evaluate tree containing variables\n";

   cout << "\nValue of expression represented by t3 = " << t3.evaluate() << endl;

   cout << "\nTest 12: Set existing variables to new values\n\n";
   
   t3.setVariable('C', 3);
   t3.setVariable('A', 8);

   cout << "Printing variables of t3\n\n";

   t3.printVariables();

   cout << "\nValue of expression represented by t3 = " << t3.evaluate() << endl;
      
   return 0;
   }
