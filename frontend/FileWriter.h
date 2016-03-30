//	CSCI 3060/ SOFE 3980 Course Project Front End
//	Group: Untitled
//	Member: Calvin Lo, Albert Fung, Karan Chandwaney
#ifndef FileWriter_h_
#define FileWriter_h_

#include <string>

using namespace std;

class FileWriter { 
 public:
	//stores file path
	string file_path;
        //Create File
        void createFile();
	//WriteFile function
	void WriteFile(string line);
	// save the transation file
	void WriteTransation(string trans_code, string account_holder_name, string account_number, string amount, string miscellaneous);
};

#endif // FileWriter_h_
