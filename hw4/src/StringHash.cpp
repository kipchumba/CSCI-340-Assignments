#ifndef STRINGHASH_H
#define STRINGHASH_H
#include <iostream>
#include <cmath>

const long pow2to27=pow(2,27);

struct StringHash { // a hash function for strings

		int operator() (const std::string& s){
			int sum=0;
			int length=s.length();
				for (int i=0;i<length;i++){
					int x=(int)s.at(i);
					sum=(sum*8)+x;
					if (sum>(pow2to27)) 
						sum=sum%pow2to27;
				}
			return std::abs(sum);
		}
};


struct StringEqual{

	bool operator()(const std::string& right, const std::string& left){
		return (right==left);
	}

};


#endif