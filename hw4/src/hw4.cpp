#include <fstream>
#include <algorithm>
#include "Table.h"
#include "NumericTable.h"


using namespace std;

// constants used in the program
const string vowels ("aeiou");
const string CONSONANT ("consonants");
const string VOWEL ("vowels");
const string DIGIT ("digits");
const char DOUBLEQUOTE ='\"';
const char SINGLEQUOTE ='\'';
const char COMMA=',';
const char PERIOD ='.';

// appropriate methods used in the program
bool checkParameters (int,char* []);
bool isVowel(char);
bool hasDoubleSingleQuotes(string &);
bool isDoubleQuote(char);
bool endsInPunctuation(string &);
bool isAllDigitsWithComma(string &);
string toLower (string &);


int main (int argc, char* argv[]){
		
	if (checkParameters(argc,argv)){
		
		ifstream input;
		string inputFile= argv[1];
		cout<<"\nreceived 2 argument(s)"<<endl;
		cout<<"input file will be: "<<inputFile<<endl<<endl;
		
		Table distinctWords_case;
		Table distinctWords_caseNot;
		Table initialLetter_case;
		Table initialLetterDistinctWords_case;
		Table eachLetter_case;
		Table categories_caseNot;
		NumericTable nLetterWords;
		map<string,int> distinctWordsCase;
		
		string that="a";
		if ((*(that.end()-1)==SINGLEQUOTE)&&(*(that.end()-1)==SINGLEQUOTE))
			cout<<*(that.begin())<<" "<<*(that.end()-1)<<endl;	
		
		// start reading words from the input
		input.open(inputFile.c_str());
		while (!input.eof()){
			string word;
			input>>word;
			
			// check the last empty string
			if (!word.empty()) {
			
				// 1. remove all the double quotes (")
				if (word.find(DOUBLEQUOTE)!=std::string::npos){
					string temp=word;
					word.erase(remove_if(word.begin(),word.end(),isDoubleQuote),word.end());
					cout<<temp<<"->"<<word<<endl;
				}
				// 2. If the word ends in a comma or period, delete the final punctuation mark.
				
				if (endsInPunctuation(word)){
					string temp=word;
					word.erase(word.end()-1);
					cout<<temp<<"->"<<word<<endl;
				}
				
				// 3. If the word starts and ends with a single quote ('), remove both quotes. 
				// Do not remove any other single quotes.
				if (hasDoubleSingleQuotes(word)){
					string temp=word;
					word.erase(word.begin());
					word.erase(word.end()-1); // end() returns a null pointer after the last element
					cout<<temp<<"->"<<word<<endl;
				}
				
				// 4. If the word consists of all numeric digits with the possible exception of a comma, 
				// replace the comma by a period.
				if (isAllDigitsWithComma(word)){
					string temp=word;
					replace_if(word.begin(),word.end(),::ispunct,PERIOD);
					cout<<temp<<"->"<<word<<endl;
				}
				
				// adding the strings to their respective tables
				distinctWords_case.add(word);
				distinctWordsCase[word]++;
				distinctWords_caseNot.add(toLower(word));
				if (!isdigit(*(word.begin())))
					initialLetter_case.add(word.substr(0,1));
				if (distinctWordsCase[word]==1&&!isdigit(*word.begin()))
					initialLetterDistinctWords_case.add(word.substr(0,1));
					
				nLetterWords.add(word.length());
				
				int elementAt=0;
				for (std::string::iterator iter=word.begin(); iter!=word.end(); iter++) {
				
					if ( !isdigit(*iter) && !ispunct(*iter) )
						eachLetter_case.add(word.substr(elementAt,1));
					if ( isVowel(tolower(*iter)) ){
						categories_caseNot.add(VOWEL);
					}
					else if ( isdigit(*iter) ){
						categories_caseNot.add(DIGIT);
					}
					else if ( !ispunct(*iter)){
						categories_caseNot.add(CONSONANT);
					}
					elementAt++;
				}
				
			}
		
		}
		
		distinctWords_case.print("Table 1: Words (case-sensitive)");
		cout<<endl<<endl;
		distinctWords_caseNot.print("Table 2: Words (case-insensitive)");
		cout<<endl<<endl;
		initialLetter_case.print("Table 3: Initial letters (case-sensitive)");
		cout<<endl<<endl;
		initialLetterDistinctWords_case.print("Table 4: Initial letters of distinct words (case-sensitive)");
		cout<<endl<<endl;
		eachLetter_case.print("Table 5: Letters (case-sensitive)");
		cout<<endl<<endl;
		categories_caseNot.print("Table 6: Some categories of characters");
		cout<<endl<<endl;
		nLetterWords.print("Table 7: Words by length");
	}	
}


/*
 * Name         : checkParameters
 * Synopsis     : checkParameters (int num, char* args[]) *
 * Arguments    : int  num, char * args[] : 
 * Description  : check whether all the command line arguments are ok
 * Returns      : bool
 */
bool checkParameters (int num, char* args[]){
	if (num!=2){
		cout<<"Usage: programFile inputFile.txt\n";
		return false;
	}
	else {
		ifstream tryInput;
		tryInput.open (args[1]);
		if (tryInput.fail()) {
			cout<<"Couldn't open the input file: "<<args[1]<<endl;
			return false;
		}
		tryInput.close();
		return true;
		
	}
}


/*
 * Name         : isVowel
 * Synopsis     : isVowel (char var) *
 * Arguments    : char  var : 
 * Description  : check whether the character is a vowel
 * Returns      : bool
 */
bool isVowel (char var){
	string::const_iterator first= vowels.begin();
	string::const_iterator last= vowels.end();
	while(first!=last){
		if (var==*first)
			return true;
		first++;
	}
	return false;
}


bool isDoubleQuote(char var){
	return (var==DOUBLEQUOTE);
}


/*
 * Name         : isSingleQouteDouble
 * Synopsis     : isSingleQouteDouble(string& str) *
 * Description  : checks whether the word begins and ends with a single quote
 * Returns      : bool
 */
bool hasDoubleSingleQuotes(string& str){
	return ((*(str.begin())==SINGLEQUOTE)&&(*(str.end()-1)==SINGLEQUOTE));
}


/*
 * Name         : endsInPunctuation
 * Synopsis     : endsInPunctuation(char var) *
 * Arguments    : char  var : 
 * Description  : checks whether the last character is a comma, period etc...
 * Returns      : bool
 */
bool endsInPunctuation(string& str){
	std::string::iterator last=str.end()-1;
	return ((*last) == COMMA || (*last) == PERIOD);
}


bool isAllDigitsWithComma(string& str){
	
	std::string::size_type digit_counter=0;
	for (std::string::iterator iter=str.begin();iter!=str.end();iter++){
		if (isdigit(*iter) || (*iter)==COMMA)
			digit_counter++;
	}
	if ((str.length()>1)&&(digit_counter==str.length()))
		return (str.find(COMMA)!=std::string::npos);
	else 
		return false;
	
}


/*
 * Name         : toLower
 * Synopsis     : toLower (std::string& s)  *
 * Description  : convert string to lowercase
 * Returns      : a lowercase string
 */
string toLower (string &s) {
	char* buf= new char [s.length()];
	int c= s.length();
	for (int x=0;x<c;x++) {
		
		buf [x]=tolower(s.at(x));
	}
	std::string r (buf,c);
	delete [] buf;
	return r;
}