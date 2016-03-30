//	CSCI 3060/ SOFE 3980 Course Project Front End
//	Group: Untitled
//	Member: Calvin Lo, Albert Fung, Karan Chandwaney
#ifndef TransactionProcessing_h_
#define TransactionProcessing_h_

#include "FileReader.h"
#include "FileWriter.h"
#include <time.h>
#include <regex>
#include <iomanip>

using namespace std;

class TransactionProcessing {

private:

	//Keep track of the input type (T for terminal; F for file input)
	char input_type;
	// Keep track of the user input
	string input;	
	// Keep track of the transaction status
	bool status;
	// The output msg to terminal or file
	string msg;
	// Keep track of the current session mode (A for admin; S for standard; N for not logged in)
	char login_mode;
	// the transaction code for the current transation
	// 01-withdrawal, 02-transfer, 03-paybill, 04-deposit, 05-create
	// 06-delete, 07-disable, 08-changeplan, 09-enable, 00-end of session, 10-login
	string trans_code;
	// Keep track of the current account holder name
	string account_holder_name;
	// keep track of the account number;
	string account_number;
	// keep track of the amount of money;
	string amount;
	// keep track of the miscel information;
	string miscellaneous;
	// keep track of the account type, student or non student
	char account_type; 
	// keep track of disabled or enabled accounts
	char acc_status;


	// Keep track of the command index of file input	
	int command_index;

	// File Reader for reading input file
	FileReader input_reader;
	// File Writer for writing the transaction file
	FileWriter transaction_writer;

	// store the bank account
	struct bank_account{
		// account holder's name
		string acc_holder_name;
		// account number
		string acc_number;
		// balance
		string acc_balance;
		// student or non student
		char acc_type;
		// active or enabled accounts
		char acc_status;
	};

	// store all the bank account in a vector
	vector<bank_account> all_accounts;

protected:

public:

	// Constructor for terminal input
	// Set the login_mode to N
	// Set the status to false
	TransactionProcessing(string trans_file);
	// Constructor for file input
	// Set the login_mode to N
	// Set the status to false
	TransactionProcessing(string input_file, string trans_file);

	TransactionProcessing();
	// Deconstructor
	~TransactionProcessing();
	// check which transaction is required and start
	bool startTransaction(string input);
	// read the command from terminal if the type is T
	// read the command from file if the type is F
	// return the command 
	string readCommand();
	// Start a Front End session
	// Set the login_mode to S if logged in standard mode
	// Set the login_mode to A if logged in admin mode
	// Set the account_holder_name based on user input
	// Returns true if the transaction success
	bool login();
	// Withdraw money from a bank account
	// Returns true if the transaction success
	bool withdrawal();
	// Transfer money from one bank account to another
	// Returns true if the transaction success
	bool transfer();
	// Pay a bill from a bank account
	// Returns true if the transaction success
	bool paybill();
	// Deposit money into a bank account
	// Returns true if the transaction success
	bool deposit();
	// Create a new bank account (privileged transaction) 
	// Returns true if the transaction success
	bool create();
	// Delete a bank account (privileged transaction)
	// Returns true if the transaction success
	bool delete1();
	// Enable all transactions in a bank account (privileged transaction)
	// * Used delete1 instead of delete since delete is the build in function in c++.
	// Returns true if the transaction success
	bool enable();
	// Disable all transactions in a bank account (privileged transaction)
	// Returns true if the transaction success	
	bool disable();
	// Change the transaction plan of a bank account (privileged transaction)
	// Returns true if the transaction su	
	bool changeplan();
	// End a Front End session
	// Returns true if the transaction su	
	bool logout();
	// parse the Current Bank Account File and store the information in all accounts
	void parse();
	// search the parsed bank account name with the input, if exists, then fill correct fields with information
	// returns the index in the vector which the bank account exists in, if not found, returns -1
	int searchName(string name);
	// search the parsed bank account number with the input, if exists, then fill correct fields with information
	// returns the index in the vector which the bank account exists in, if not found, returns -1
	int searchAcc(string accnum);
	// search the parsed bank account number and name with the input, if exists, then fill correct fields with information
	// returns the index in the vector in which the account number and name exists, if not found, returns -1
	int searchNameAcc(string name, string accnum);
        // check input is transaction code or not
        bool isTransaction(string input);
        // check if the amount is in the format ####.##
        bool isCorrectFormat(string input);
        // check if the account has enough money to cover the transaction fee, 
        // check if the account has enough money to cover the student transaction fee
        bool enoughTransactionFee(string amount, int pos);
        // minus the transaction fee 
        string minusTransactionFee(string amount, int pos);
        // return true if deposit amount is divisible by 5, return false or not
        bool isDivisibleBy5(string amount);
        // truncate name if character over 20 or fill in spaces if character under 20
        string fixName(string input);
        // cast account number from int to string
        string numToString (int acc_num_int);
        
        
	// remove the trailing white spaces
	string trim(string str);
};

#endif // TransactionProcessing_h_