#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "PlayerDatabase.h"

using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;
using std::ofstream;


int main()
   {
   PlayerDatabase db;
   PlayerDatabase db1;
   PlayerDatabase db3;
   PlayerDatabase db4;
     
   ifstream origFile ("players-orig.txt");
   ifstream miniFile ("players-mini.txt");
   ifstream doubleFile("players-orig-double.txt");
   
   // for db, 40 players
   if (!origFile)
      {
      cerr << "Unable to open player data file\n";
      exit(1);
      }

   cout << "Loading player data for db...\n\n";
      
   db.load_team(origFile);

   origFile.close();
   
   cout << "Printing player data for db...\n\n";
      
   db.print_team();
   
   cout << "Done\n";
   
   // for db3, 4 players
   if (!miniFile)
      {
      cerr << "Unable to open player data file\n";
      exit(1);
      }

   cout << "Loading player data for db3...\n\n";
      
   db3.load_team(miniFile);

   miniFile.close();
   
   cout << "Printing player data for db3...\n\n";
      
   db3.print_team();
   
   cout << "Done\n";
   
   // for db4, 80 players, a check for the resize function
   if (!doubleFile)
      {
      cerr << "Unable to open player data file\n";
      exit(1);
      }

   cout << "Loading player data for db3...\n\n";
      
   db4.load_team(doubleFile);

   doubleFile.close();
   
   cout << "Printing player data for db3...\n\n";
      
   db4.print_team();
   
   cout << "Done\n";
   
   // check for the asssignment operator
   db1=db;
   cout << "Printing player data for db1...\n\n";
   db1.print_team();
   
   // check for the copy constructor
   PlayerDatabase db2(db3);
   cout << "Printing player data for db2...\n\n";
   db2.print_team();
   
   cout<<"\n\nALL is done!\n\n";
   return 0;
   
   }
