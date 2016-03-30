// Phase2.cpp : main project file.

//Imports
#include "FileWriter.h"
#include <iostream> 
#include <string>
#include <fstream>

using namespace std;

// create File

void FileWriter::createFile() {
    ofstream file; //open ifstream
    file.open(file_path, ios::app); // append the file
}

//WriteFile function
void FileWriter::WriteFile(string line) { 
	ofstream file; //open ifstream
	file.open(file_path, ios::app); // append the file
	if (file.is_open()) {  //if file opened successfully
		file << line << '\n';
		file.close(); //close file
	} else { //if the file is not found
		cout << "Unable to open" << '\n';
	}
}

void FileWriter::WriteTransation(string trans_code, string account_holder_name, string account_number, string amount, string miscellaneous) {
	const int length = 40;
	int index = 0;
	char trans_line[length];
	// fill out the line to all empty
	for (int i = 0; i < length; i++) {
		trans_line[i] = ' ';
	}
	// fill in the transaction code
	// the first digit of the transaction line is the transaction code.
	for (int i = 0; i < trans_code.length(); i++) {
		trans_line[index++] = trans_code.at(i); 	
	}

	// fill in the account holder's name
	// the index of account holder's name start at 3
	index = 3;
	for (int i = 0; i < account_holder_name.length(); i++) {
		trans_line[index++] = account_holder_name.at(i);
	} 

	// fill in the bank account number
	// the index of account number start at 23
	index = 23;
	// fill with all 0 first
	for (int i = 0; i < 5; i++ ) {
		trans_line[index++] = '0';
	}
	// add the account number reversely since it is right justified
		index = 27;
		for (int i = account_number.length(); i > 0; i--) {
			trans_line[index--] = account_number.at(i-1); // at(i-1) because the length is 5 but the index is 4 (start with 0)
		}

	// fill in he amount of funds involved
	// the index of amount of funds start at 29
	index = 29;
	// fill with all 0 first
	for (int i = 0; i < 8; i++ ) {
		trans_line[index++] = '0';
	}
	// fill in the actual amount
	// add the amount reversely since it is right justified
	index = 36;
	for (int i = amount.length(); i > 0; i--) {
		trans_line[index--] = amount.at(i-1); // at(i-1) because the length is 5 but the index is 4 (start with 0)
	}
	// fill int the any additional miscellaneous
	// the index of additional miscellaneous start at 38
	index = 38;
	for (int i = 0 ; i < miscellaneous.length(); i++) {
		trans_line[index++] = miscellaneous.at(i);
	}
	// write the file
	WriteFile(trans_line);
}
