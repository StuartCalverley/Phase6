//	CSCI 3060/ SOFE 3980 Course Project Front End
//	Group: Untitled
//	Member: Calvin Lo, Albert Fung, Karan Chandwaney
#ifndef FileReader_h_ 
#define FileReader_h_

#include <string>
#include <vector> 
#include <iostream> 
#include <fstream>

using namespace std;


class FileReader { 


 public:
	string file_path; //stores file path
	vector<string> commands;	
	vector<string> buffer;
	void ReadFile(); //ReadFile function
};

#endif // FileReader_h_
