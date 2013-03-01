#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <list>
#include <vector>
#include "HashTable.h"
#include "StringHash.cpp"

using namespace std;


typedef HashTable<string,StringHash> Wordlist; // the hashtable structure

const string alpha ("abcdefghijklmnopqrstuvwxyz"); // the alphabet in lowercase

/*
 * Name: Pair
 * Description : holds pairs of words when a given word is split in two
 */
struct Pair {
	string first;
	string second;
};	

/*** functions used by the programs ***/				 
bool checkparameters(int,char*[]);
vector<string> singleLetterOmissions(string);
vector<string> singleLetterAdditions(string);
vector<string> neighbouringLettersSwap (string);
vector<string> substituteLetters(string);
vector<Pair> pairsWhenSplitIntoTwo(string);
std::string toLower (std::string&);
 
int main (int argc, char* argv[]){
	
	if (checkparameters(argc,argv)){ // make sure all the CLI parameters are ok
	
	clock_t prog_start, prog_end; 	// global time
	prog_start= clock(); 			// start timing the program
	
	int buckets= atoi (argv[1]);	// parameter 1, buckets number
	string dict= argv[2];			// parameter 2, dictionary word file
	string words=argv[3];			// parameter 3, file with words to spell check
	
	cout<<"SpellChecker"<<endl<<endl;
	
	clock_t load_start, load_end, wordcheck_start, wordcheck_end; // for timing dictionary load time, and wordcheck time
	double progtime=0, loadtime=0, wordchecktime=0;
    
	ifstream fin;
	string word;
	Wordlist myDict(buckets); // create the hashtable of the dictionary
	fin.open(dict.c_str());
	
	load_start= clock();
	while (!fin.eof()){
		getline(fin,word);
		myDict.insert(toLower(word)); // upload the dictionary, changing all thw words to lowercase
	}
	
	load_end= clock();
	loadtime=((double)(load_end-load_start))/(double)CLOCKS_PER_SEC; // loading time for the dictionary
	fin.close();
	
	vector<string> WordsToCheck;
	fin.open(words.c_str());
	
	while (!fin.eof()) {
		getline(fin,word);
		WordsToCheck.push_back(toLower(word));	// load the words to be checked, also change them to lowercase
	}
	fin.close();
	
	vector<string>::iterator begin;
	vector<string>::iterator end;
	begin=WordsToCheck.begin();
	end=WordsToCheck.end();
	
	/** to store alternate words found **/
	std::list<string> alternateWords;
	
	/***** the main loop of spell checking ****/
	wordcheck_start=clock(); // 
	while (begin!=end){
		// store state of results
		bool alternatesNotFound=true;
		bool notFound=true;
		
		cout<<*begin<<endl;
		if(myDict.find(*begin)) {
			cout<<"OK"<<endl<<endl;
			notFound=false;
		}
			
		else {
			vector<string> omissions, additions, neighbourSwaps, substitutes;
			vector<Pair> pairs;
			
			omissions=singleLetterOmissions(*begin);
			for (int i=0;i<omissions.size();i++){
				if(myDict.find(omissions[i])) {
					alternateWords.push_front(omissions[i]);
					alternatesNotFound=false;
				}
			}
			
			additions=singleLetterAdditions(*begin);
			for (int i=0;i<additions.size();i++){
				if (myDict.find(additions[i])){
					alternateWords.push_front(additions[i]);
					if(alternatesNotFound)
						alternatesNotFound=false;
				}
			}
			
			neighbourSwaps= neighbouringLettersSwap(*begin);
			for (int i=0;i<neighbourSwaps.size();i++){
				if (myDict.find(neighbourSwaps[i])){
					alternateWords.push_front(neighbourSwaps[i]);
					if(alternatesNotFound)
						alternatesNotFound=false;
				}
			} 
			
			substitutes= substituteLetters(*begin);
			for (int i=0;i<substitutes.size();i++){
				if (myDict.find(substitutes[i])){
					alternateWords.push_front(substitutes[i]);
					if(alternatesNotFound)
						alternatesNotFound=false;
				}
			}
			
			pairs= pairsWhenSplitIntoTwo(*begin);
			for (int i=0;i<pairs.size();i++){
				if (myDict.find(pairs[i].first)&&myDict.find(pairs[i].second)){
					string temp=pairs[i].first+" "+pairs[i].second;
					alternateWords.push_front(temp);
					if(alternatesNotFound)
						alternatesNotFound=false;
				}
			}
			
			// sort and print the alternatives found
			alternateWords.sort();
			std::list<string>::iterator iter;
			for (iter=alternateWords.begin();iter!=alternateWords.end();iter++){
				cout<<*iter<<endl;
			}
			alternateWords.clear();
			
		}
		
		/** if nothing was found**/
		if (notFound&&alternatesNotFound)
			cout<<"Not Found"<<endl;
				
		cout<<endl;
		begin++;
	}
	
	wordcheck_end=clock();
	wordchecktime=((double) (wordcheck_end - wordcheck_start)) / (double) CLOCKS_PER_SEC;
	
	prog_end= clock();
	progtime= ((double) (prog_end - prog_start)) / (double) CLOCKS_PER_SEC;
	
	cout<<"Number of entries: \t"<<myDict.getsize()<<endl;
	cout<<"Number of buckets:\t"<<buckets<<endl;
	cout<<"Buckets in use:\t\t"<<myDict.bucketsUsed()<<endl;
	cout<<"Average List Length\t"<<myDict.getsize()/(double)myDict.bucketsUsed()<<endl;
	cout<<"Maximum list length:\t"<<myDict.maxLength()<<endl<<endl;
	cout<<"Time to load the dictionary:\t"<<loadtime<<"s"<<endl;
	cout<<"Time to check the words:\t"<<wordchecktime<<"s"<<endl;
	cout<<"Total program time: \t\t"<<progtime<<"s"<<endl;
	}
}

/*
 * Name         : checkparameters
 * Synopsis     : bool checkparameters(int,int,string,string) *
 * Description  : checks the arguments provided in the commandline, if all are ok i.e 
				  the two files provided can be opened, and the first parameter is an integer greater than 0		  
 * Returns      : bool, if true it gives the main program a go ahead 
 */
bool checkparameters(int c, char* argv[]){

	if (c!=4){
	
		cout<<"Usage: <programfilename> <numberofbuckets> <dictionaryFile.txt> <wordsTocheckfile.txt>"<<endl;
		return false;
	}
	
	else {
		int n= atoi(argv[1]);
		string a= argv[2];
		string b= argv[3];
		if (n<=0) {
			cout<<"First parameter is an integer greater than 0"<<endl;
			return false;
		}
	
		else {
		
			ifstream in;
			
			in.open (a.c_str());
			if (in.fail()) {
				cout<<"Couldn't open the first file: "<<a<<endl;
				return false;
			}	
			in.close();
			in.open(b.c_str());
			if (in.fail()){
				cout<<"Couldn't open the second file: "<<b<<endl;
				return false;
			}
			else {
				in.close();
				return true;
			}

}

}

}

/*
 * Name         : singleLetterOmissions
 *
 * Synopsis     :  singleLetterOmissions (string s) *
 * Arguments    :  string  s 
 * Description  : generates words with single letter omissions from input string s (at each point) 
 * Returns      : a list of words with a single letter less than string s (the number of words=size of input string)
 */
vector<string> singleLetterOmissions (string s){
	
	vector<string> words;
	string temp;
	string::iterator iter;
		
	for (int i=0;i<s.length();i++){
		temp=s;
		iter=temp.begin()+i;
		temp.erase(iter);
		words.push_back(temp);
		
	}
	
	return words;
}

/*
 * Name         : singleLetterAdditions
 * Synopsis     : singleLetterAdditions(string) *
 * Arguments    : string  s 
 * Description  : generates words with single letter additions to the input string s (insertion of letter at any point in s)
 * Returns      : a list of words with a single letter more than the string s (number of words=26 times size of s-1)
 */
vector<string> singleLetterAdditions(string s){
	string temp,temp2;
	vector<string> words;
	
	for (int i=0;i<s.size();i++){
	
		for (int x=0;x<alpha.size();x++){
			temp=s;
			temp2=alpha;
			temp.insert(i,temp2.substr(x,1));
			words.push_back(temp);
		}
	}
			
	for (int x=0;x<alpha.size();x++){
		temp=s;
		temp2=alpha;
		temp.append(temp2,x,1);
		words.push_back(temp);
	}
	
	return words;
}

/*
 * Name         : neighbouringLettersSwap
 * Synopsis     : neighbouringLettersSwap (string) *
 * Arguments    : string  s 
 * Description  : generates words by swapping adjacent letters in s
 * Returns      : a list of words creating by the swaps (number of words=size of s-1)
 */
vector<string> neighbouringLettersSwap (string s){

	vector<string> words;
	char a;
	char b;
	string temp;
	for (int i=0;i<s.size()-1;i++){
		temp=s;
		a=temp.at(i);
		b=temp.at(i+1);
		temp[i]=b;
		temp[i+1]=a;
		words.push_back(temp);
	}
	return words;

}

/*
 * Name         : replaceLetters
 * Synopsis     :  replaceLetters(string s) *
 * Arguments    : string  s : 
 * Description  : generates words by replacing each letter in s, with letters of the alphabet
				  there is no checking whether the letter is being replaced by itself
 * Returns      : a list of words (number of words=26 times size of s) 
 */
vector<string> substituteLetters(string s){
	vector<string> words;
	string temp;
	char a;
	
	for (int i=0;i<s.size();i++){
		
		for (int j=0;j<alpha.size();j++){
			temp=s;
			a=alpha.at(j);
			temp[i]=a;
			words.push_back(temp);
		}
	}
	return words;
}

/*
 * Name         : pairsWhenSplitIntoTwo
 * Synopsis     : pairsWhenSplitIntoTwo(string s) *
 * Arguments    : string  s : 
 * Description  : generates pairs of words when space is added at any point in s
 * Returns      : a list of the pairs (number of words=size of s-1)
 */
vector<Pair> pairsWhenSplitIntoTwo(string s){
	vector<Pair> pairs;
	string temp,temp2,temp3,temp4;
	Pair holder;
	
	for (int i=0;i<s.size()-1;i++){
		temp=s;
		temp2=s;
		temp3=temp.substr(0,i+1);
		temp4=temp2.substr(i+1);
		holder.first=temp3;
		holder.second=temp4;
		pairs.push_back(holder);
	}
	return pairs;
}

/*
 * Name         : toLower
 * Synopsis     : toLower (std::string& s)  *
 * Description  : convert string to lowercase
 * Returns      : a lowercase string
 */
std::string toLower (std::string &s) {
	char* buf= new char [s.length()];
	int c= s.length();
	for (int x=0;x<c;x++) {
		
		buf [x]=tolower(s.at(x));
	}
	std::string r (buf,c);
	delete [] buf;
	return r;
}