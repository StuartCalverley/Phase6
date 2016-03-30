//	CSCI 3060/ SOFE 3980 Course Project Front endl
//	Group: Untitled
//	Member: Calvin Lo, Albert Fung, Karan Chandwaney
#include "TransactionProcessing.h"

TransactionProcessing::TransactionProcessing(string trans_file) {
	// set the default login mode to 'N' (Not logged in)
	login_mode = 'N';
	// set the default input type to 'T' (Termainal input)
	input_type = 'T';

	//referring to the filepath of created object
	transaction_writer.file_path =  trans_file;
	// Set account holder's name, bank account number, amount, account type, miscellaneous to default
	account_holder_name = "";
	account_number = "";
	amount = "";
	miscellaneous = "";
	trans_code = "";
	acc_status = 'E';
	account_type = 'N';

	// parse the current bank account file
	parse();
        
        
        // create empty transaction file
        transaction_writer.createFile();
        

	while (true) {
		getline(cin, input);
		startTransaction(input);
	}
}

TransactionProcessing::TransactionProcessing(string input_file, string trans_file) {
	// set the default login mode to 'N' (Not logged in)
	login_mode = 'N';
	// set the default input type to 'F' (File input)
	input_type = 'F';
	// Set the command index for the input file to 0
	command_index = 0;
	//referring to the filepath of created object
	transaction_writer.file_path = trans_file;
	// Set account holder's name, bank account number, amount, account type, miscellaneous to default
	account_holder_name = "";
	account_number = "";
	amount = "";
	miscellaneous = "";
	trans_code = "";
	acc_status = 'E';
	account_type = 'S';

	// parse the current bank account file
	parse();
        
        // create empty transaction file
        transaction_writer.createFile();
        
	//referring to the filepath of created object
	input_reader.file_path = input_file;
	//call the readfile function on filepath given above
	input_reader.ReadFile();
	input_reader.commands = input_reader.buffer;
	// Read int the commands from the file
	while (command_index < input_reader.commands.size() ) {
		input = input_reader.commands.at(command_index);
                
        // increase the command index
		command_index++;
                
            // change the input type to terminal when reach the last row                
            if (command_index == input_reader.commands.size()) {
                input_type = 'T';
            }
                
		// start transactions with given input
		startTransaction(input);
                
	}
	// Start command line input when all the transaction in the input file is done
	TransactionProcessing("trans_file");
}

TransactionProcessing::TransactionProcessing() {
	// set the default login mode to 'N' (Not logged in)
	login_mode = 'N';
	// set the default input type to 'T' (Termainal input)
	input_type = 'T';
	//referring to the filepath of created object
	transaction_writer.file_path = "transactions.trans";
	// Set account holder's name, bank account number, amount, account type, miscellaneous to default
	account_holder_name = "";
	account_number = "";
	amount = "";
	miscellaneous = "";
	trans_code = "";
	acc_status = 'E';
	account_type = 'N';

	// parse the current bank account file
	parse();
        
        // create empty transaction file
        transaction_writer.createFile();
        
	while (true) {
		getline(cin, input);
		startTransaction(input);
	}
}

TransactionProcessing::~TransactionProcessing() {

}

bool TransactionProcessing::startTransaction(string input) {

	// set the default transaction status to false;
	status = false;
	// Set the miscellaneous information to empty;
	miscellaneous = "";

	if (input == "login") {
		trans_code = "10";
		return login();
	} else if (input == "withdrawal") {
		trans_code = "01";
		return withdrawal();
	} else if (input == "transfer") {
		trans_code = "02";
		return transfer();
	} else if (input == "paybill") {
		trans_code = "03";
		return paybill();
	} else if (input == "deposit") {
		trans_code = "04";
		return deposit();
	} else if (input == "create") {
		trans_code = "05";
		return create();
	} else if (input == "delete") {
		trans_code = "06";
		return delete1();
	} else if (input == "enable") {
		trans_code = "09";
		return enable();
	} else if (input == "disable") {
		trans_code = "07";
		return disable();
	} else if (input == "changeplan") {
		trans_code = "08";
		return changeplan();
	} else if (input == "logout") {
		trans_code = "00";
		return logout();
	} else {
		cout << "Invalid command." << endl;
		return false;
	}

}

string TransactionProcessing::readCommand() {
	string command;


	// if the input type is terminal input
	if (input_type == 'T') {
		getline(cin, command);
	}
	// if the input type is file input
	else if (input_type == 'F') {
		command = input_reader.commands.at(command_index);
		// increase the command index
		command_index++;
        // change the input type to terminal when reach the last row                
        if (command_index == input_reader.commands.size()) {
            input_type = 'T';
        }
	}
        
	return command;
}

bool TransactionProcessing::login() {

	// Keep track of valid account holder's name
	bool valid_acc_holder = false;


	// if there are no one logged in.
	if (login_mode == 'N') {
		msg = "Do you wish to login as a standard user or admin?";
		cout << msg << endl;
                input = readCommand(); 
                if (isTransaction(input) == true) {
                    startTransaction(input); 
                    return false;
                }
		// logged in as standard mode
		if (input == "standard session") {
			msg = "Logged in as a standard user.";
			login_mode = 'S';
			account_type = 'S';
		}
		// logged in as admin mode
		else if (input == "admin session") {
			msg = "Logged in as an admin user.";
			login_mode = 'A';
		}
		// Not valid mode
		else {
			msg = "Invalid Mode";
			cout << msg << endl;
			return status;
		}
        // set the miscel information
        miscellaneous =+ login_mode;
        cout << msg << endl;
        msg = "What is the account holder's name?";
        cout << msg << endl;
        input = readCommand(); 
        if (isTransaction(input) == true) {
            startTransaction(input); 
            return false;
        }
        account_holder_name = input;
        
        // checks if name exists inside bank accounts file
        int pos = searchName(account_holder_name);
        if (pos != -1) { 
            valid_acc_holder = true;
        } 
        // Set valid_acc_holder equal to true for admin mode since the name is optional.
        else if (login_mode == 'A' && account_holder_name == "") {
            valid_acc_holder = true;
        }

        // if account holder name is valid
        if (valid_acc_holder == true) {
            // Sucessfully log in
            status = true;
            if (account_holder_name != "") {
                msg = "logged in as " + account_holder_name + ".";
                cout << msg << endl;
            } 
            else {
                msg = "logged in as general admin mode.";
                cout << msg << endl;
            }
            // write the transation file
            transaction_writer.WriteTransation(trans_code, account_holder_name, account_number, amount, miscellaneous);
            return status;
        }
        // if account holder name is NOT valid
        else {
            msg = "Invalid account holder name.";
            cout << msg << endl;
                        login_mode = 'N';
            return status;
        }

	}
	// if there are already someone logged in
	else {                
        msg = "login: Invalid command. User " + account_holder_name + " must be logged out before attempting to login again.";
		cout << msg << endl;
		return status;
	}

	return status;
}

bool TransactionProcessing::withdrawal() {
	// Keep track of the account holder name for withdrawal
	string withdrawal_acc_holder;
	// Keep track of the account holder name for withdrawal
	string withdrawal_acc_num;
	// Keep track of the amount for withdrawal;
	string withdrawal_amount;
	// True if the amount to withdraw is valid, False if not
	bool valid_amount = false;
	// True if the account holder name to withdraw is valid, False if not
	bool valid_acc_holder = false;
	// True if the account number to withdraw is valid, False if not
	bool valid_acc_num = false;
	// true if the transfer amount is under the limit, false if not
	bool valid_under_limit = false;

	// Check whether the user logged in.  If logged in, check if they have the privilege to withdrawal money
	// Return false if the user is not logged in
	if (login_mode == 'N') {
		msg = "withdrawal: Invalid command. You are required to be logged into the system.";
		cout << msg << endl;
		return status;
	}
	else if (login_mode == 'S' || login_mode == 'A') {
		msg = "withdrawal: Valid command.";
		cout << msg << endl;

		// Ask for the account holder's name if logged in as admin
		if (login_mode == 'A') {
			msg = "What is the account holder's name for withdrawal?";
			cout << msg << endl;
			input = readCommand(); if (isTransaction(input) == true) { startTransaction(input); return false ;}
			withdrawal_acc_holder = input;
		}
		// Set the account holder's name to the current user if logged in as standard
		else {
			withdrawal_acc_holder = account_holder_name;
		}

		// checks if the name exists inside bank accounts file
		int pos = searchName(withdrawal_acc_holder);
		if (pos != -1) {
			valid_acc_holder = true;
		}

		// if the account holder name is valid.
		if (valid_acc_holder == true) {
			msg =  withdrawal_acc_holder + " set as withdrawal account holder.";
			cout << msg << endl;
			msg = "What is the account number you wish to withdraw from?";
			cout << msg << endl;
			input = readCommand(); if (isTransaction(input) == true) { startTransaction(input); return false ;}
			withdrawal_acc_num = input;

			// search bank accounts file for bank account number
			int pos2 = searchAcc(withdrawal_acc_num);
			// account name must match account number
			if (pos != -1 && pos2 == pos) {
				valid_acc_num = true;
			}

			// if the account number is valid.
			if (valid_acc_num == true) {
				msg = "Valid account number " + withdrawal_acc_num + ".";
				cout << msg << endl;
				msg = "What is the amount to withdraw?";
				cout << msg << endl;
				input = readCommand(); if (isTransaction(input) == true) { startTransaction(input); return false ;}
				withdrawal_amount = input;

				// if the amount is in the format ####.##
				// return false if not
				if (isCorrectFormat(withdrawal_amount) == false) {
					msg = "Amount format incorrect. Withdrawal failed.";
					cout << msg << endl;
					return status;
				}

				// check for multiple of five
				else if (isDivisibleBy5(withdrawal_amount) == false) {
					msg = "Unable to complete withdrawal. Must be a multiple of 5.";
					cout << msg << endl;
					return status;
				}

				// check if correct format
				else {
					valid_amount = true;
				}

				// check if valid amount
				if (valid_amount == true) {
					msg = "Valid amount $" +withdrawal_amount + ".";
					cout << msg << endl;
				}

				// check for the account type and subtract corresponding transaction fee
				withdrawal_amount = minusTransactionFee(withdrawal_amount, pos);
				// check if the amount to withdraw minus transaction fee is below 500
				if (withdrawal_amount != "ABOVE 500") {
					status = true;
					msg = "$" + withdrawal_amount + " successfully withdrawn.";
					cout << msg << endl;
				}

				// write the transaction file
					transaction_writer.WriteTransation(trans_code, withdrawal_acc_holder, withdrawal_acc_num, withdrawal_amount, miscellaneous);
					return status;
				}
				// if the amount is NOT valid
				else {
					msg = "Invalid amount. Withdrawal failed.";
					cout << msg << endl;
					return status;
				}
			}
			// if the account number is NOT valid
			else {
				msg = "Invalid account number. Withdrawal failed.";
				cout << msg << endl;
				return status;
			}
		}
		// if the acount holder name is NOT valid
		else {
			msg = "Invalid account holder name. Withdrawal failed.";
			cout << msg << endl;
			return status;
		}
	return status;
}

bool TransactionProcessing::transfer() {
	// Keep track of the account holder name for transfer from
	string transfer_acc_name_from;

	// Keep track of the account holder name for transfer to
	string transfer_acc_name_to;

	// Keep track of the account holder name for transfer from
	string transfer_acc_num_from;

	// Keep track of the account holder name for transfer to
	string transfer_acc_num_to;

	// Keep track of the amount for transfer
	string transfer_amount;

	// True if the amount to transfer is valid, False if not
	bool valid_amount = false;

	// True if the account holder names to transfer is valid, False if not
	bool valid_acc_holder_from = false;
	bool valid_acc_holder_to = false;

	// True if the account numbers to transfer is valid, False if not
	bool valid_acc_num_from = false;
	bool valid_acc_num_to = false;

	// true if the transfer amount is under the limit, false if not
	bool valid_under_limit = false;

	// true if the account to transfer to is not disabled, false if not
	bool valid_not_disabled = false;

	// true if the account has enough money to cover the transaction fee, false if not
	bool valid_non_student_fee = false;

	// true if the account has enough money to cover the student transaction fee, false if not
	bool valid_student_fee = false;

	// true if the account has sufficient funds to cover transfer, false if not

	bool sufficient_funds = false;

	// Check whether the user logged in.  If logged in, check if they have the privilege to transfer money
	// Return false if the user is not logged
	if (login_mode == 'N') {
		msg = "trasfer: Invalid command. You are required to be logged into the system.";
		cout << msg << endl;
		
                return status;
	} else if (login_mode == 'S' || login_mode == 'A') {
		msg = "transfer: Valid command.";
		cout << msg << endl;

		// Admin mode transfer request
		if (login_mode == 'A') {
			msg = "What is the account holder's name for origin transfer?";
			cout << msg << endl;
                        input = readCommand(); 
                        if (isTransaction(input) == true) {
                            startTransaction(input); 
                            return false;
                        }
			transfer_acc_name_from = input;

			// standard mode transfer, from is the account currently logged in
		} else {
			transfer_acc_name_from = account_holder_name;
		}
		
                int pos = searchName(transfer_acc_name_from);
                if (pos != -1) { 
                    valid_acc_holder_from = true;
                } 

		// if name given for origin transfer is valid
		if (valid_acc_holder_from == true) {
			msg =  transfer_acc_name_from + " selected as account holder name for origin transfer.";
			cout << msg << endl;
			msg = "What is the account number for origin transfer?";
			cout << msg << endl;
                        input = readCommand(); 
                        if (isTransaction(input) == true) {
                            startTransaction(input); 
                            return false;
                        }
			transfer_acc_num_from = input;
                        
                        // search bank accounts file for bank account number
			int pos2 = searchAcc(transfer_acc_num_from);
			// account name must match account number
			if (pos2 != -1 && pos2 == pos) { 
                            valid_acc_num_from= true;
			}
                        

			// if the origin account number is valid.
			if (valid_acc_num_from == true) {
				msg = "Account number " + transfer_acc_num_from + " selected for origin transfer.";
				cout << msg << endl;
				msg = "What is the destination account number";
				cout << msg << endl;
                                input = readCommand(); 
                                if (isTransaction(input) == true) {
                                    startTransaction(input); 
                                    return false;
                                }
				transfer_acc_num_to = input;
                                
                                int pos3 = searchAcc(transfer_acc_num_to);
                                if (pos3 != -1) {
                                    valid_acc_num_to = true;
                                    // find the account name
                                    transfer_acc_name_to = all_accounts[pos3].acc_holder_name;
                                    
                                }
                                
				// if destination account number is valid
				if (valid_acc_num_to == true) {
					msg = "Account number " + transfer_acc_num_to + " set as destination account number.";
					cout << msg << endl;
					msg = "What is the amount to transfer from accounts " + transfer_acc_num_from + " to " + transfer_acc_num_to + "?";
					cout << msg << endl;
                                        input = readCommand(); 
                                        if (isTransaction(input) == true) {
                                            startTransaction(input); 
                                            return false;
                                        }
					transfer_amount = input;

					//sufficient funds
                                        sufficient_funds = stof(all_accounts[pos].acc_balance) - stof(transfer_amount) >= 0 
                                                            && stof(all_accounts[pos3].acc_balance) + stof(transfer_amount) >= 0;;
					if (sufficient_funds == true) {
                                                                                                                                                                 
                                                // destination account number not disabled
                                                if (all_accounts[pos3].acc_status == 'A') {
                                                    valid_not_disabled = true; 
                                                } 
						if (valid_not_disabled == true) {

							// if valid amount to transfer
                                                        
                                                        if (isCorrectFormat(transfer_amount) == true) {
                                                            valid_amount = true;
                                                            
                                                        }
                                                        
							if (valid_amount == true) {

								// if account type is student, check if bal is enough to cover fee
								if (account_type == 'S') {
                                                                        valid_student_fee = enoughTransactionFee(transfer_amount, pos);
									if (valid_student_fee == true) {
										// if amount to transfer is below limit
                                                                            
                                                                                
                                                                                valid_under_limit = stof(transfer_amount) <= 1000.00;
										if (valid_under_limit == true) {
											// success

											status = true;
											msg = "$" + transfer_amount + " transferred from accounts " + transfer_acc_num_from + " to " + transfer_acc_num_to + ".";
											cout << msg << endl;
											transaction_writer.WriteTransation(trans_code, transfer_acc_name_from, transfer_acc_num_from, transfer_amount, miscellaneous);
											transaction_writer.WriteTransation(trans_code, transfer_acc_name_to, transfer_acc_num_to, transfer_amount, miscellaneous);
											return status;
											// amount to transfer above limit
										} else {
											msg = "Transfer limit exceeded. You must transfer less than $" + transfer_amount + ".";
											cout << msg << endl;
											return status;
										}
										// student not enough to cover fee
									} else {
										msg = "Insufficient funds of 5 cents to transfer $" + transfer_amount + " due to transaction fee.";
										cout << msg << endl;
										return status;
									}
								}
								// if account type is non-student, check if bal is enough to cover fee
								
								if (account_type == 'N') {
                                                                        valid_non_student_fee = enoughTransactionFee(transfer_amount, pos);
									if (valid_non_student_fee == true) {
										// if amount to transfer is below limit
										if (valid_under_limit == true) {
											// success

											status = true;
											msg = "$" + transfer_amount + " transferred from accounts " + transfer_acc_num_from + " to " + transfer_acc_num_to + ".";
											cout << msg << endl;
											transaction_writer.WriteTransation(trans_code, transfer_acc_name_from, transfer_acc_num_from, transfer_amount, miscellaneous);
											transaction_writer.WriteTransation(trans_code, transfer_acc_name_to, transfer_acc_num_to, transfer_amount, miscellaneous);
											return status;
											// amount to transfer above limit
										} else {
											msg = "Transfer limit exceeded. You must transfer less than $" + transfer_amount + ".";
											cout << msg << endl;
											return status;
										}
										// non - student not enough to cover fee
									} else {
										msg = "Insufficient funds of 10 cents to transfer $" + transfer_amount + " due to transaction fee.";
										cout << msg << endl;
										return status;
									}
								}
								// amount to transfer not valid
							} else {
								msg = "Invalid format. Must be ####.## where # is a digit 0 - 9.";
								cout << msg << endl;
								return status;
							}
							// destination account number disabled
						} else {
							msg = "Invalid destination account number, the account has been disabled.";
							cout << msg << endl;
							return status;
						}
						// insufficient funds
					} else {
						msg = "Insufficient funds to transfer $" + transfer_amount + ".";
						cout << msg << endl;
						return status;
					}
					// if destination account number is invalid
				} else {
					msg = "Invalid account number for destination of transfer.";
					cout << msg << endl;
					return status;
				}
				// origin account number is not valid
			} else {
				msg = "Invalid account number for origin of transfer.";
				cout << msg << endl;
				return status;
			}
			// origin account name is not valid
		} else {
			msg = "Invalid account name";
			cout << msg << endl;
			return status;
		}
	}
	return status;
}


bool TransactionProcessing::paybill() {
    // Keep track of the account holder name for withdrawal
	string paybill_acc_holder;
	// Keep track of the account holder number for withdrawal
	string paybill_acc_num;
	// Keep track of the amount to be paid
	string paybill_amount;
	// Keep track of the company to whom the bill is being paid
	string paybill_company_name;
	// True if the amount to pay is valid, False if not
	bool valid_amount = false;
	// True if the account holder name to pay bill is valid, False if not
	bool valid_acc_holder = false;
	// True if the account holder number to pay bill is valid, False if not
	bool valid_acc_num = false;
	// True if the company name to whom bill is being paid is valid, False if not
	bool valid_company_name = false;

        

	// Check whether the user logged in.  If logged in, check if they have the privilege to pay bill
	// Return false if the user is not logged
	if (login_mode == 'N') {
		msg = "paybill: Invalid command. You are required to be logged into the system.";
		cout << msg << endl;
		return status;
	} else if (login_mode == 'S' || login_mode == 'A') {
		msg = "paybill: Valid command.";
		cout << msg << endl;
		// Ask for the account holder's name if logged in as admin
		if (login_mode == 'A') {
			msg = "What is the account holder's name for bill payment?";
			cout << msg << endl;
                        input = readCommand(); 
                        if (isTransaction(input) == true) {
                            startTransaction(input); 
                            return false;
                        }
			paybill_acc_holder = input;
		}
		// Set the account holder's name to the curretn user if logged in as standard
		else {
			paybill_acc_holder = account_holder_name;
		}
		
        // checks if name exists inside bank accounts file
        int pos = searchName(paybill_acc_holder);
        if (pos != -1) { 
            valid_acc_holder = true;
        }

		// if the account holder name is valid
		if (valid_acc_holder == true) {
			msg = paybill_acc_holder + " set as the account holder of the bill payment.";
			cout << msg << endl;
			msg = "What is the account number from which you wish to pay a bill from?";
			cout << msg << endl;
                        input = readCommand(); 
                        if (isTransaction(input) == true) {
                            startTransaction(input); 
                            return false;
                        }
			paybill_acc_num = input;
            
                        // search bank accounts file for bank account number
			int pos2 = searchAcc(paybill_acc_num);
			// account name must match account number
			if (pos2 != -1 && pos2 == pos) { 
				valid_acc_num = true;
			}
		
			// if the account number is valid
			if (valid_acc_num == true) {
				msg = "Valid account number " + paybill_acc_num + ".";
				cout << msg << endl;
				msg = "What company would you like to pay the bill to?";
				cout << msg << endl;
                                input = readCommand(); 
                                if (isTransaction(input) == true) {
                                    startTransaction(input); 
                                    return false;
                                }
				paybill_company_name = input;
            
                // check if company is valid
                if (paybill_company_name == "EC" || paybill_company_name == "CQ" || paybill_company_name == "TV") {
                    valid_company_name = true;
                }
                
                
                // if the company name is valid
                if (valid_company_name == true) {
                    string company_full_name;
                    if (paybill_company_name == "EC") {
                        company_full_name = "Bright Light Electric Comapny (EC)";
                    } else if (paybill_company_name == "CQ") {
                        company_full_name = "Credit Card Company (CQ)";
                    } else if (paybill_company_name == "TV") {
                        company_full_name = "Low Definition TV (TV)";
                    }
            
                    msg = company_full_name + "selected. What is the amount of the bill payment?";
                    cout << msg << endl;
            
                    msg = "What is the amount to pay?";
                    cout << msg << endl;
                    input = readCommand(); 
                    if (isTransaction(input) == true) {
                        startTransaction(input); 
                        return false;
                    }
                    paybill_amount = input;
            
                    // if the amount is valid (<2000)
                    // return false if not
                    if (stof(paybill_amount) > 2000.00) {
                        msg = "Payment cannot exceed $2000.00 in standard mode. Bill payment failed.";
                        cout << msg << endl;
                        return status;
                    }
                    // if the account balance is at least $0.00 after bill is paid
                    // return false if not
                    else if (stof(all_accounts[pos].acc_balance) - stof(paybill_amount) < 0) {
                        msg = "Account balance after bill payment is less than $00.00. Bill payment failed.";
                        cout << msg << endl;
                        return status;
                    }
                    // if the amount is in the format ####.##
                    // return false if not
                    else if (isCorrectFormat(paybill_amount) == false)  {
                        msg = "Amount format incorrect. Bill payment failed.";
                        cout << msg << endl;
                        return status;                      
                    }
                    // if the account has enough money to cover the transaction fee, 
                    //if the account has enough money to cover the student transaction fee
                    // return false if not
                    else if (enoughTransactionFee(paybill_amount, pos) == false)  {
                        msg = "Bill payment failed.";
                        cout << msg << endl;
                        return status;
                    }
                    // amount is valid
                    else {
                        valid_amount = true;
                    }
                    
                    /*if (stof(paybill_amount) < 2000.00 && stof(all_accounts[pos].acc_balance) - stof(paybill_amount) >= 0 && isCorrectFormat(paybill_amount) && enoughTransactionFee(paybill_amount, pos)) {
                        valid_amount = true;
                    }*/
                    
                    if (valid_amount == true) {
                        msg = "Valid amount $" + paybill_amount + ".";
                        cout << msg << endl;
                        
                        // Successfully paid bill
                        status = true;
                        msg = "$" + paybill_amount + " Successfully paid to " + paybill_company_name + " from account number " + paybill_acc_num + ".";
                        cout << msg << endl;
                        // Write the transaction file
                        transaction_writer.WriteTransation(trans_code, paybill_acc_holder, paybill_acc_num, paybill_amount, paybill_company_name);
                        return status;
                    }
                    // if the amount is NOT valid
                    else {
                        return status;
                    }
                }
                // if the company name is NOT valid
                else {
                    msg = "Invalid company. Bill payment failed.";
                    cout << msg << endl;
                    return status;
                }
            }
            // if the account number is NOT valid
            else {
                msg = "Invalid account number or Name and account number do not match. Bill payment rejected.";
                cout << msg << endl;
                return status;
            }
        }
        // if the account name is NOT valid
        else {
            msg = "Invalid account holder name";
            cout << msg << endl;
            return status;
        }
    }
    return status;
}

bool TransactionProcessing::deposit() {
	// stores the name of the account holder
	string deposit_acc_holder;

	// stores the account number of the account holder
	string deposit_acc_num;

	// stores the amount to be deposited
	string deposit_amount;

	// true if the account holder is valid, otherwise false
	bool valid_acc_holder = false;

	// true if the account number is valid, otherwise false
	bool valid_acc_num = false;

	// true if the deposit is valid, otherwise false
	bool valid_amount = false;


	// Check whether the user logged in.  If logged in, check if they have the privilege to deposit money
	// Return false if the user is not logged
	if (login_mode == 'N') {
            msg = "deposit: Invalid command. You are required to be logged into the system.";
            cout << msg << endl;
            return status;        
	} 
	else if (login_mode == 'S' || login_mode == 'A') {
            msg = "deposit: Valid command.";
            cout << msg << endl;
            
            // Ask for the account holder's name if logged in as admin
            if (login_mode == 'A') {
                    msg = "What is the account holder's name which you wish to deposit to?";
                    cout << msg << endl;
                    input = readCommand(); 
                    if (isTransaction(input) == true) {
                        startTransaction(input); 
                        return false;
                    }
                    deposit_acc_holder = input;
            }
            // Set the account holder's name to the curretn user if logged in as standard
            else {
                    deposit_acc_holder = account_holder_name;
            }
            
            // checks if name exists inside bank accounts file
            int pos = searchName(deposit_acc_holder);
            if (pos != -1) { 
                valid_acc_holder = true;
            }
            
            // if account name is valid
            if (valid_acc_holder == true) {
                msg = deposit_acc_holder + " set as the account holder of the deposit.";
                cout << msg << endl;
                msg = "What is the account number which you wish to deposit to?";
                cout << msg << endl;
                input = readCommand(); 
                if (isTransaction(input) == true) {
                    startTransaction(input); 
                    return false;
                }
                deposit_acc_num = input;
                
                
                // search bank accounts file for bank account number
                int pos2 = searchAcc(deposit_acc_num);
                // account name must match account number
                if (pos2 != -1 && pos2 == pos) { 
                    valid_acc_num = true;
                }
                
                // if account number is valid
                if (valid_acc_num == true) {
                    msg = deposit_acc_num + " set as the account number of the deposit.";
                    cout << msg << endl;
                    msg = "What is the amount to be deposited?";
                    cout << msg << endl;
                    input = readCommand(); 
                    if (isTransaction(input) == true) {
                        startTransaction(input); 
                        return false;
                    }
                    deposit_amount = input;
                    
                    // if the amount is in the format ####.## 
                    // return false if not
                    if (isCorrectFormat(deposit_amount) == false)  {
                        msg = "Amount format incorrect. Deposit failed.";
                        cout << msg << endl;
                        return status;           
                    } 
                    // check for multiple of five                    
                    else if (isDivisibleBy5(deposit_amount) == false) {
                        msg = "Unable to complete deposit. Amount must be a multiple of 5.";
                        cout << msg << endl;
                        return status;
                    }
                    // if is correct format
                    else {
                        valid_amount = true;
                    }
                    
                    
                    // if valid amount 
                    if (valid_amount == true) {
                        msg = "Valid amount $" + deposit_amount + ".";
                        cout << msg << endl;
                        
                        // check for account type and minus corresponding transaction fee 
                        deposit_amount = minusTransactionFee(deposit_amount, pos);
                        // check if the amount minus transaction fee is greater than 0
                        if (deposit_amount != "BELOW 0") {
                            status = true; 
                            msg = "$" + deposit_amount + " successfully deposited.";
                            cout << msg << endl;
                            msg = "Deposited amount usable next day only.";
                            cout << msg << endl;
                        }
                        else {
                            return false;
                        }
                        
                    
                    }
                    // if amount is not valud
                    else {
                        return status;
                    }
                }
                // if account number is not valid
                else {
                    msg = "Invalid account number or Name and account number do not match. Deposit failed.";
                    cout << msg << endl;
                    return status;
                }
                
            } 
            //if account name is not valid 
            else {
                msg = "Invalid account holder name. Deposit failed.";
                cout << msg << endl;
                return status;
            }
        }
    return status;
}

bool TransactionProcessing::create() {
	// Stores the name of the account holder you want to create
	string create_acc_name;
	// Stores the account number that you want to create
	string create_acc_num;
        // Stores the balance that you want to create
        string create_acc_balance;
	// True if the account name is valid, otherwise false
	bool valid_acc_name = false;
	// True if the account number is valid, otherwise false
	bool valid_acc_num = false;
        // True if the balance is valid, otherwise false
        bool valid_acc_balance = false;

	// Check whether the user logged in.  If logged in, check if they have the privilege to create account
	// Return false if the user is not logged
	if (login_mode == 'N') {
		msg = "create: Invalid command. You are required to be logged into the system.";
		cout << msg << endl;
		return status;
	} else if (login_mode == 'S') {
		msg = "create: Invalid command. Admin access required.";
		cout << msg << endl;
		return status;
        } else if (login_mode == 'A') {
            msg = "create: Valid command. Admin access granted.";
            cout << msg << endl;
            msg = "Enter the new bank account holder's name to be created.";
            cout << msg << endl;
            input = readCommand(); 
            if (isTransaction(input) == true) {
                startTransaction(input); 
                return false;
            }
            create_acc_name = input;
            
            // fix create_acc_name
            create_acc_name = fixName(create_acc_name);
            if (create_acc_name.length() == 20) {
                valid_acc_name = true;
            }
            
            // If the account holder's name is valid
            if (valid_acc_name == true) {
                msg = "Accepted new bank account name: " + trim(create_acc_name) + ".";
                cout << msg << endl;
                
                msg = "What is the initial balance of the account?";
                cout << msg << endl;
                input = readCommand(); 
                if (isTransaction(input) == true) {
                    startTransaction(input); 
                    return false;
                }
                create_acc_balance = input;
                
                
                // check if balance is less than $99999.99
                // return false if not
                if (stof(create_acc_balance) > 99999.99) {
                    msg = "Balance is over $99999.99. Account creation unsuccessful.";
                    cout << msg << endl;
                    return status;
                }
                // check if it is the good format
                // return false if not
                else if (isCorrectFormat(create_acc_balance) == false)  {
                    msg = "Amount format incorrect. Account creation unsuccessful.";
                    cout << msg << endl;
                    return status;  
                }
                // balance is valid
                else {
                    valid_acc_balance = true;
                }
                
                if (valid_acc_balance == true) {
                    msg = "Accepted inital balance $" + create_acc_balance + ".";
                    cout << msg << endl;
                    
                    // create and check account number
                    // start from 00001 and find the next available number
                    int create_acc_num_int = 1;
                    create_acc_num = numToString(create_acc_num_int);
                    while (searchAcc(create_acc_num) != -1)  {
                        ++create_acc_num_int;
                        create_acc_num = numToString(create_acc_num_int);
                    }
                    
                    // double check if the cerated account number is unique
                    int pos2 = searchAcc(create_acc_num);
                    if (pos2 == -1) { 
                            valid_acc_num = true;
                    }
                    // If account number is valid
                    if (valid_acc_num == true) {
                        // Successfully created account
                        // set default account type in save as miscellaneous information
                        miscellaneous += 'N';
                        status = true;
                        msg = "Accepted bank account number to be created: " + create_acc_num + " for " + trim(create_acc_name) +".";
                        cout << msg << endl;
                        msg = "Account type: Non-Student Plan.";
                        cout << msg << endl;
                        transaction_writer.WriteTransation(trans_code, create_acc_name, create_acc_num, amount, miscellaneous);
                    } 
                    // if account number is not valid
                    else {
                        msg = "Account number already exists. Account creation unsuccessful";
                        cout << msg << endl;
                    }
                }
                // if balance is not valid
                else {
                    msg = "Invalid Balance. Account creation unsuccessful";
                    cout << msg << endl;
                    
                }
            // If the account holder's name is not valid
            } else {
                msg = "Rejected bank account holder's name. (Entered an invalid account holder name).";
                cout << msg << endl;
                return status;
            }
        }
    return status;
}

bool TransactionProcessing::delete1() {
	// stores the name of the account holder that you want to delete
	string delete_acc_holder;

	// stores the account number that you want to delete
	string delete_acc_num;
	// true if the account holder is valid, otherwise false
	bool valid_acc_holder = false;

	// true if the bank acconut number is valid, otherwise false
	bool valid_acc_num = false;

	// Check whether the user logged in.  If logged in, check if they have the privilege to delete account
	// Return false if the user is not logged
	if (login_mode == 'N') {
		msg = "delete: Invalid command. You are required to be logged into the system.";
		cout << msg << endl;
		return status;
	} else if (login_mode == 'S') {
		msg = "delete: Invalid command. Admin access required.";
		cout << msg << endl;
		return status;
	} else if (login_mode == 'A') {
		msg = "delete: Valid command. Admin access granted.";
		cout << msg << endl;
		msg = "Enter the bank account holder's name to be deleted.";
		cout << msg << endl;
		input = readCommand(); 
                if (isTransaction(input) == true) { 
                    startTransaction(input); 
                    return false;
                } 
		delete_acc_holder = input;

		int pos = searchName(delete_acc_holder);
		if (pos != -1) {
			valid_acc_holder = true;
		}

		// if the account holder's name is valid
		if (valid_acc_holder == true) {
			msg = "Accepted bank account holder's name: " + delete_acc_holder + ".";
			cout << msg << endl;
			msg = "Enter bank account number to be deleted.";
			cout << msg << endl;
                        input = readCommand(); 
                        if (isTransaction(input) == true) { 
                            startTransaction(input);
                            return false;
                        } 
			delete_acc_num = input;

			// search bank accounts file for bank account number, if exists, set account type
			int pos2 = searchNameAcc(delete_acc_holder, delete_acc_num);
			// account name must match account number
			if (pos2 != -1) { 
				valid_acc_num = true;
				account_type = all_accounts[pos2].acc_type;
				acc_status = all_accounts[pos2].acc_status;
			}

			// if account number is valid
			if (valid_acc_num == true) {
				// success
				status = true;
				msg = "Accepted bank account number to be deleted: " + delete_acc_num + ".";
				cout << msg << endl;
				msg = "Account " + delete_acc_num + " from " + delete_acc_holder + " has been deleted. Information saved to bank account transaction file.";
				cout << msg << endl;
				transaction_writer.WriteTransation(trans_code, delete_acc_holder, delete_acc_num, amount, miscellaneous);
				return status;
				// if the account number is not valid
			} else {
				msg = "Rejected bank account number to be deleted: " + delete_acc_num + ". (Entered an invalid bank account number)";
				cout << msg << endl;
				return status;
			}
			// if the account holder's name is not valid
		} else {
			msg = "Rejected bank account holder's name: Invalid name. (Entered an invalid account holder's name)";
			cout << msg << endl;
			return status;
		}
	}
	msg = "Delete Unsucessfully.";
	cout << msg << endl;
	return status;
}

bool TransactionProcessing::enable() {
	// stores the name of the account holder that you want to enable
	string enable_account_holder;

	// stores the account number that you want to enable
	string enable_account_num;
	// true if the account holder is valid, otherwise false
	bool valid_acc_holder = false;

	// true if the bank acconut number is valid, otherwise false
	bool valid_acc_num = false;

	// Check whether the user logged in.  If logged in, check if they have the privilege to enable account
	// Return false if the user is not logged
	if (login_mode == 'N') {
		msg = "enable: Invalid command. You are required to be logged into the system.";
		cout << msg << endl;
		return status;
	} else if (login_mode == 'S') {
		msg = "enable: Invalid command. Admin access required.";
		cout << msg << endl;
		return status;
	} else if (login_mode == 'A') {
		msg = "enable: Valid command. Admin access granted.";
		cout << msg << endl;
		msg = "Enter the bank account holder's name to be enabled.";
		cout << msg << endl;
                input = readCommand(); 
                if (isTransaction(input) == true) { 
                    startTransaction(input);
                    return false;
                } 
		enable_account_holder = input;


		int pos = searchName(enable_account_holder);
		if (pos != -1) { 
			valid_acc_holder = true;
		}
		// valid account holder
		if (valid_acc_holder == true) {
			msg = "Accepted bank account holder's name: " + enable_account_holder + ".";
			cout << msg << endl;
			msg = "Enter bank account number to be enabled.";
			cout << msg << endl;
                        input = readCommand(); 
                        if (isTransaction(input) == true) { 
                            startTransaction(input);
                            return false;
                        } 
			enable_account_num = input;

			// search bank accounts file for bank account number, if exists, set account type
			int pos2 = searchNameAcc(enable_account_holder, enable_account_num);
			// account name must match account number
			if (pos2 != -1) { 
				valid_acc_num = true;
				account_type = all_accounts[pos2].acc_type;
				acc_status = all_accounts[pos2].acc_status;
			}

			// valid bank account number, disabled account
			if (valid_acc_num == true && acc_status == 'D') {
				//success
				status = true;
				msg = "Accepted bank account number: " + enable_account_num + ".";
				cout << msg << endl;
				msg = "Account " + enable_account_num + " from "  + enable_account_holder + " has been enabled. Information saved to bank account transaction file.";
				cout << msg << endl;
				transaction_writer.WriteTransation(trans_code, enable_account_holder, enable_account_num, amount, miscellaneous);
				return status;
				// valid bank account number, enabled account
			} else if (valid_acc_num == true && acc_status == 'E') {
				msg = "Rejected bank account number to be enabled: " + enable_account_holder + " (Account " + enable_account_num + " is a enabled account.)";
				cout << msg << endl;
				return status;
			} else { // not valid bank account number
				msg = "Rejected bank account number to be enabled: " + enable_account_holder + " (Account " + enable_account_num + ". Entered an invalid bank account number)";
				cout << msg << endl;
				return status;
			}
			// not valid account holder
		} else {
			msg = "Rejected the bank account holder's name: Invalid name. (Entered an invalid account holder's name)";
			cout << msg << endl;
			return status;
		}
	}
	msg = "enable Unsucessfully.";
	cout << msg << endl;
	return status;
}

bool TransactionProcessing::disable() {

	// Keep track of the account holder name to disable
	string disable_account_holder;
	// Keep track of the account number to disable
	string disable_account_num;
	// True if the account holder name is valid, False if not
	bool valid_acc_holder = false;
	// True if the account holder number is valid, False if not
	bool valid_acc_num = false;

	// Check whether the user logged in.  If logged in, check if they have the privilege to disable account
	// Return false if the user is not logged
	if (login_mode == 'N') {
		msg = "disable: Invalid command. You are required to be logged into the system.";
		cout << msg << endl;
		return status;
	} else if (login_mode == 'S') {
		msg = "disable: Invalid command. Admin access required.";
		cout << msg << endl;
		return status;
	} else if (login_mode == 'A') {
		msg = "disable: Valid command. Admin access granted.";
		cout << msg << endl;
		msg = "Enter the bank account holder's name to be disabled.";
		cout << msg << endl;
                input = readCommand(); 
                if (isTransaction(input) == true) {
                    startTransaction(input); 
                    return false;
                }
		disable_account_holder = input;


		int pos = searchName(disable_account_holder);
		if (pos != -1) {
			valid_acc_holder = true;
		}
		// if valid account holder name
		if (valid_acc_holder == true) {
			msg = "Accepted bank account holder's name: " + disable_account_holder + ".";
			cout << msg << endl;
			msg = "Enter bank account number to be disabled.";
			cout << msg << endl;
			input = readCommand(); 
                        if (isTransaction(input) == true) {
                            startTransaction(input);
                            return false;
                        }
			disable_account_num = input;

			// search bank accounts file for bank account number, if exists, set account type
			int pos2 = searchNameAcc(disable_account_holder, disable_account_num);
			// account name must match account number
			if (pos2 != -1) {
				valid_acc_num = true;
				account_type = all_accounts[pos2].acc_type;
				acc_status = all_accounts[pos2].acc_status;
			}

			// Valid bank account number, enabled account
			if (valid_acc_num == true && acc_status == 'A') {
				// Successfully disabled
				status = true;
				msg = "Accepted bank account number: " + disable_account_num + ".";
				cout << msg << endl;
				msg = "Account " + disable_account_num + " from " + disable_account_holder + " has been disabled. Information saved to bank account transaction file.";
				cout << msg << endl;
				transaction_writer.WriteTransation(trans_code, disable_account_holder, disable_account_num, amount, miscellaneous);
				return status;
				// Valid bank account number, enabled account
			} else if (valid_acc_num == true && acc_status == 'D') {
				msg = "Bank account number disabled: " + disable_account_holder + " (Account " + disable_account_num + " is a disabled account).";
				cout << msg << endl;
				return status;
			} else { // Not valid bank account number
				msg = "Rejected bank account number to be disabled: " + disable_account_holder + ", Account number: " + disable_account_num + ". (entered an invalid bank account number).";
				cout << msg << endl;
				return status;
			}
			// Invalid account holder
		} else {
			msg = "Rejected bank account holder's name (Invalid name)";
			cout << msg << endl;
			return status;
		}
	}
	msg = "Account disable unsuccessful.";
	cout << msg << endl;
	return status;
}

bool TransactionProcessing::changeplan() {
	// stores the name of the account holder that you want to change the plan for
	string changeplan_account_holder;

	// stores the account number that you want to change the plan for
	string changeplan_account_num;
	// true if the account holder is valid, otherwise false
	bool valid_acc_holder = false;

	// true if the bank acconut number is valid, otherwise false
	bool valid_acc_num = false;

	// Check whether the user logged in.  If logged in, check if they have the privilege to change plan
	// Return false if the user is not logged

	if (login_mode == 'N') {
		msg = "changeplan: Invalid command. You are required to be logged into the system.";
		cout << msg << endl;
		return status;
	} else if (login_mode == 'S') {
		msg = "changeplan: Invalid command. Admin access required.";
		cout << msg << endl;
		return status;
	} else if (login_mode == 'A') {
		msg = "changeplan: Valid command. Admin access granted.";
		cout << msg << endl;
		msg = "Enter the bank account holder's name to change the transaction payment plan.";
		cout << msg << endl;
                input = readCommand(); 
                if (isTransaction(input) == true) {
                    startTransaction(input); 
                    return false;
                }
		changeplan_account_holder = input;

		
		int pos = searchName(changeplan_account_holder);
		if (pos != -1) { 
			valid_acc_holder = true;
		}
		

		// if valid bank account holder name student to non student
		if (valid_acc_holder == true) {
			msg = "Accepted bank account holder's name: " + changeplan_account_holder + ".";
			cout << msg << endl;
			msg = "Enter bank account number to change the transaction payment plan.";
			cout << msg << endl;
                        input = readCommand(); 
                        if (isTransaction(input) == true) {
                            startTransaction(input); 
                            return false;
                        }
			changeplan_account_num = input;
			
			
			// search bank accounts file for bank account number, if exists, set account type
			int pos2 = searchAcc(changeplan_account_num);
			// account name must match account number
			if (pos2 != -1 && pos2 == pos) { 
				valid_acc_num = true;
				account_type = all_accounts[pos].acc_type;
			}
		
			// valid bank account number
			if (valid_acc_num == true && account_type == 'S') {
				//success

				status = true;
				msg = "Accepted bank account number: " + changeplan_account_num + ".";
				cout << msg << endl;
				msg = "Account " + changeplan_account_num + " from " + changeplan_account_holder + " has changed from student (SP) to non - student (NP). Information saved to bank account transaction file.";
				cout << msg << endl;
				transaction_writer.WriteTransation(trans_code, changeplan_account_holder, changeplan_account_num, amount, miscellaneous);
				return status;
				// valid bank account number non student to student
			} else if (valid_acc_num == true && account_type == 'N') {
				// success

				status = true;
				msg = "Account " + changeplan_account_num + " from " + changeplan_account_holder + " has changed from non - student (NP) to student (SP). Information saved to bank account transaction file.";
				cout << msg << endl;
				transaction_writer.WriteTransation(trans_code, changeplan_account_holder, changeplan_account_num, amount, miscellaneous);
				return status;
				// not valid bank account number
			} else {
				msg = "Rejected bank account number to change the transaction payment plan: " + changeplan_account_num + " (Entered an invalid bank account number)";
				cout << msg << endl;
				return status;
			}
			// not valid bank account holder name
		} else {
			msg = "Rejected Bank account holder's name: Invalid name. (Entered an invalid account holder's name)";
			cout << msg << endl;
			return status;
		}
	}
	//fail
	msg = "changeplan Unsucessfully.";
	cout << msg << endl;
	return status;
}

bool TransactionProcessing::logout() {
	// Check whether the user logged in.  If logged in, check if they have the privilege to logout
	// Return false if the user is not logged
	if (login_mode == 'N') {
		msg = "logout: Invalid command. You are required to be logged into the system.";
		cout << msg << endl;
		return status;
	} else if (login_mode == 'S' || login_mode == 'A') {
		msg = "logout: Valid command.";
		cout << msg << endl;
		msg = "Logout Sucessfully.";
		cout << msg << endl;
		transaction_writer.WriteTransation(trans_code, account_holder_name, account_number, amount, miscellaneous);
		login_mode = 'N';
		account_holder_name = "";
	}

	status = true;
	return status;
}

void TransactionProcessing::parse() {

	FileReader bank_account_reader;
	//referring to the filepath of created object
	bank_account_reader.file_path = "BankAccounts.txt";
	//call the readfile function on filepath given above
	bank_account_reader.ReadFile();
	bank_account_reader.commands = bank_account_reader.buffer;

	for (int i = 0; i < bank_account_reader.commands.size(); i++) {

		bank_account temp_account;
		// Bank account number start at 0 and have a length of 5
		temp_account.acc_number = bank_account_reader.buffer.at(i).substr(0, 5);
		// Bank account holder name start at 6 and have a length of 20
		temp_account.acc_holder_name = bank_account_reader.buffer.at(i).substr(6, 20);
		// Account status (Active or Disabled) at 27
		temp_account.acc_status = bank_account_reader.buffer.at(i).at(27);
		// Account balance start at 29 and have a length of 8
		temp_account.acc_balance = bank_account_reader.buffer.at(i).substr(29, 8);
		// Account type (Student or Non Student) at 38
		temp_account.acc_type = bank_account_reader.buffer.at(i).at(38);

		// Remove all the white space after the last character
		temp_account.acc_holder_name = trim(temp_account.acc_holder_name);

		//cout << temp_account.acc_holder_name.length() << endl;

		// push back the temp account to the all account vector
		all_accounts.push_back(temp_account);
	}

}

int TransactionProcessing::searchName(string name) {
	for (int i = 0; i < all_accounts.size(); i++) {
		//cout << all_accounts[i].acc_holder_name << endl;
		if (all_accounts[i].acc_holder_name.compare(name) == 0) { 
			return i;
		}
	}	
	return -1;
}

int TransactionProcessing::searchAcc(string accnum) {
	for (int i = 0; i < all_accounts.size(); i++) {
		if (all_accounts[i].acc_number.compare(accnum) == 0)  {
			return i;
		}
	}	
	return -1;
}

int TransactionProcessing::searchNameAcc(string name, string accnum) { 
	for (int i = 0; i < all_accounts.size(); i++) { 
		if (all_accounts[i].acc_holder_name.compare(name) == 0 && all_accounts[i].acc_number.compare(accnum) == 0) { 
			return i;
		}
	}
	return -1;
}

bool TransactionProcessing::isTransaction(string input) {
    if (input == "login" || input == "withdrawal" || input == "transfer"  || input == "paybill"  
        || input == "deposit" || input == "create" || input == "delete" || input == "enable"
        || input == "disable" || input == "changeplan" || input == "logout")  {
    
        return true;
        
    }
    return false;
    
}

bool TransactionProcessing::isCorrectFormat(string input) {
    regex float_m("[[:digit:]]?[[:digit:]]?[[:digit:]]?[[:digit:]?][[:digit:]].[[:digit:]][[:digit:]]");
    
    return (regex_match (input, float_m));
}

bool TransactionProcessing::enoughTransactionFee(string amount, int pos) {
    bool result;
    if (all_accounts[pos].acc_type == 'S') { 
        result = stof(all_accounts[pos].acc_balance) - stof(amount) - 0.05f >= 0;  
        if (result == false) {
            msg = "Account balance is exactly $" + amount + ". Unable to process $0.05 Student account transaction fees.";
            cout << msg << endl;
        }
    }
    if (all_accounts[pos].acc_type == 'N') {
        result =  stof(all_accounts[pos].acc_balance) - stof(amount) - 0.10f >= 0;   
        if (result == false) {
            msg = "Account balance is exactly $" + amount + ". Unable to process $0.10 Non Student account transaction fees.";
            cout << msg << endl; 
        }
    }
    
    return result;
}

string TransactionProcessing::minusTransactionFee(string amount, int pos) {
    float temp_amount = stof(amount);
    ostringstream s;
    if (all_accounts[pos].acc_type == 'S') {
        temp_amount -= 0.05;
        if (temp_amount <= 0) {
            msg = "Deposit amount is exactly $0.05. Unable to process $0.10 Non Student account transaction fees.";
            return ("BELOW 0");
        }
        s << fixed <<setprecision(2) << temp_amount;
        msg = "$0.05 deducted for Student Account transaction fees.";
        cout << msg << endl;
    }
    if (all_accounts[pos].acc_type == 'N') {
        temp_amount -= 0.10;
        if (temp_amount <= 0) {
            msg = "Deposit amount is exactly $0.10. Unable to process $0.10 Non Student account transaction fees.";
            return ("BELOW 0");
        }
        s << fixed <<setprecision(2) << temp_amount;
        msg = "$0.10 deducted for Non - Student Account transaction fees.";
        cout << msg << endl;
    }
    amount = s.str();
    return amount;
    
}

bool TransactionProcessing::isDivisibleBy5(string amount)  {
    float temp_amount_f = stof(amount);
    int temp_amount_i = temp_amount_f;
    if (ceilf(temp_amount_f) == temp_amount_f) {
        return (temp_amount_i%5 == 0);  
    }
    else {
        return false;
    }
}

string TransactionProcessing::fixName(string name)  {
    if (input.length() > 20) {
            input = input.substr(0,20);
    } else if (input.length() < 20) {
            for (int i = input.length(); i < 20; i++) {
                    input += " ";
            }
    }
    return input;
    
}

string TransactionProcessing::numToString(int acc_num_int) {
    string acc_num = "00000";

    string acc_num_temp = to_string(acc_num_int);

    int index = 0;
    for (int i = 0; i < 5; i++ ) {
        acc_num[index++] = '0';
    }
    index = 4;
    for (int i = acc_num_temp.length(); i > 0; i--) {
        acc_num[index--] = acc_num_temp.at(i-1); // at(i-1) because the length is 5 but the index is 4 (start with 0)
    }
    return acc_num;
    
}

string TransactionProcessing::trim(string s) {
	// substing from 0 to the first not white space char from the end
	return s.substr(0, (s.find_last_not_of(' ') + 1));
}
