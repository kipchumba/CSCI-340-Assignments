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
   
   ifstream oldFile("players.txt");
   if (!oldFile)
      {
      cerr << "Unable to open player data file\n";
      exit(1);
      }

   cout << "Loading player data...\n\n";
      
   db.load_team(oldFile);

   oldFile.close();
   
   cout << "Printing player data...\n\n";
      
   db.print_team();

   cout << "Done\n";
         
   return 0;
   }
