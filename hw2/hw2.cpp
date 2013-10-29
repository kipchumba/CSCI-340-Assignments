#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include "create_names.h"
#include "PlayerDatabase.h"

using namespace std;

int main(int argc, char *argv[])
   {

     ifstream inFile;
     ofstream outFileAll;
     ofstream outFileGood;
     ofstream outFileSmall;
     ofstream outFileRepeat;

     string inFileName;
     string outFileNameAll;
     string outFileNameGood;
     string outFileNameSmall;
     string outFileNameRepeat;

     PlayerDatabase db;
   
     create_names(argc, argv, inFileName, outFileNameAll, outFileNameGood,
		  outFileNameSmall, outFileNameRepeat);

     inFile.open(inFileName.c_str());
     if (!inFile)
       {
	 cerr << "Unable to open player data file" << endl;;
         exit(1);
       }
     cout << "Loading player data..." << endl << endl;
     db.load_team(inFile);
     inFile.close();

     cout << endl << "Printing player data for full team..." << endl << endl;
     outFileAll.open(outFileNameAll.c_str());
     db.print_team(outFileAll);
     outFileAll.close();   
     cout << "Done full team: "<< db.get_team_count() << " members" << endl;
         
     // there are three ways to invoke the copy constructor
     // 1. using an initializer, as below
     // 2. another form of initialization: PlayerDatabase db2 = db1;
     // 3. call or return by value - see 241 sample programs

     cout << endl << "Printing player data for good team..." << endl << endl;
     PlayerDatabase db2(db);
     outFileGood.open(outFileNameGood.c_str());
     db2.create_good_team();
     db2.print_team(outFileGood);
     outFileGood.close();
     cout << "Done good team: "<< db2.get_team_count() << " members" << endl;
     
     // ... and this will invoke the overloaded assignment operator
    
     cout << endl << "Printing player data for small team..." << endl << endl;
     PlayerDatabase db3;
     db3 = db;

     outFileSmall.open(outFileNameSmall.c_str());
     db3.create_small_team();
     db3.print_team(outFileSmall);
     outFileSmall.close();
     cout << "Done small team: "<< db3.get_team_count() << " members" << endl;

     cout << endl << "Printing player data for original team again..." << endl << endl;
     outFileRepeat.open(outFileNameRepeat.c_str());
     db.print_team(outFileRepeat);
     outFileRepeat.close();
     cout << "Done original team: "<< db.get_team_count() << " members" << endl;


         
     return 0;
     }
