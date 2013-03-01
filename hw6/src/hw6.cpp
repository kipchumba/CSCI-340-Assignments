
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <time.h>
#include <iomanip>
#include <algorithm>

#include "heapsort.h"
#include "scramble.h"

std::string toLower (const std::string&);
using namespace std;

struct greaterThan {

	 bool operator() (const string& right, const string& left){
		
		string rightComp = toLower (right);
		string leftComp = toLower (left);
		rightComp.erase ( remove_if (rightComp.begin(),rightComp.end(), ::ispunct),rightComp.end() );
		leftComp.erase ( remove_if (leftComp.begin(),leftComp.end(), ::ispunct),leftComp.end() );
		
		return (rightComp>leftComp);
	 }
 
};

struct lesserThan {
	
	bool operator() (const string& right, const string& left){
		
		string rightComp = toLower (right);
		string leftComp = toLower (left);
		rightComp.erase ( remove_if (rightComp.begin(),rightComp.end(), ::ispunct),rightComp.end() );
		leftComp.erase ( remove_if (leftComp.begin(),leftComp.end(), ::ispunct),leftComp.end() );

		return (rightComp<leftComp);
	 }
};

int main (int argc, char* argv []) {
	
	if (argc!=2){
		cout<<"Usage: <programfilename> <inputFile>\n"; 
	}
	
	else {
	
		fstream input;
		string fileName=argv[1];
		vector<string> inputFile1;
		vector<string> inputFile2;
		vector<string> heapVectorGreater;
		vector<string> heapVectorLesser;
		vector<string> outputGreater;
		vector<string> outputLesser;
		greaterThan predGreater;
		lesserThan predLesser;
		clock_t heapsortLesser_start;
		clock_t heapsortGreater_start;
		clock_t heapsortGreater_end;
		clock_t heapsortLesser_end;
		
				
		input.open (fileName.c_str());
		if (input.fail()) {
			cout<<"Couldn't open the first file: "<<fileName<<endl;
		}	
		
		else {
			
			while (!input.eof()) {
				
				string temp;
				input>>temp;
				inputFile1.push_back(temp);
			
			}
			input.close();
			
			inputFile2=inputFile1;
			heapVectorGreater.push_back("dummy sentinel");
			heapVectorLesser.push_back("dummy sentinel");
			
			/*cout<<"Before Scrambling"<<endl<<endl;
			for (std::vector<string>::const_iterator iter= inputFile1.begin(); iter!=inputFile1.end();++iter) {
				
				cout<<*iter<<endl;
			}
			
			cout<<endl<<"After Scrambling"<<endl<<endl;
			scramble (inputFile1);
			for (std::vector<string>::const_iterator iter= inputFile1.begin(); iter!=inputFile1.end();++iter) {
				
				cout<<*iter<<endl;
			}
			*/
			scramble (inputFile1);
			scramble (inputFile2);
			cout<<endl;
			heapsortGreater_start = clock();
			build_heap (inputFile1,heapVectorGreater,predGreater);
			cout<<" Descending order : "<<endl<<endl;
			heapsort (heapVectorGreater,outputGreater,predGreater);
			heapsortGreater_end = clock();
			
			heapsortLesser_start = clock();
			build_heap (inputFile2,heapVectorLesser,predLesser);
			cout<<endl<<endl<<" Ascending order : "<<endl<<endl;
			heapsort (heapVectorLesser,outputLesser,predLesser);
			heapsortLesser_end = clock();
						
			double heapsortGreater_time= ((double) (heapsortGreater_end - heapsortGreater_start)) / (double) CLOCKS_PER_SEC;
			double heapsortLesser_time= ((double) (heapsortLesser_end - heapsortLesser_start)) / (double) CLOCKS_PER_SEC;
			
			cout<<endl<<endl<<"Heapsort Analysis "<<endl;
			cout<<"Number of unsorted elements in input vector = "<<setw(8)<<std::right<<(inputFile1.size())<<endl;
			cout<<"Ascending Sort Time in seconds              = "<<setw(8)<<std::right<<setprecision(4)<<heapsortGreater_time<<endl;
			cout<<"Descending Sort Time in seconds             = "<<setw(8)<<std::right<<setprecision(4)<<heapsortLesser_time<<endl;
		}
	
	
	
	}

}

std::string toLower (const std::string &s) {
	char* buf= new char [s.length()];
	int c= s.length();
	for (int x=0;x<c;x++) {
		
		buf [x]=tolower(s.at(x));
	}
	std::string r (buf,c);
	delete [] buf;
	return r;
}