/*
 *Backend.java, BankAccount.java, and Validation.java created by Matthew McCormick, Nick Gregorio, and Janahan Mathanamohan starting on March 11th, 2016
 *The following code is the backend for a bank terminal
 *It will take inputs MasterAccountFile.txt and MergedTransactionFile.txt, and create outputs CurrentAccountsFile.txt and also update files MasterAccountFile.txt and MergedTransactionFile.txt 
 *(assumed that Transactions merged on backend, not front end)
 *Backend.java and related files are currently run on their own.
 *Program should be compiled via javac Backend.java BankAccount.java Validation.java, and run via the command java Backend MasterAccountFile.txt MergedTransactionFile.txt
 */

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.io.PrintWriter;
import java.io.File;
import java.io.FilenameFilter;

public class Backend {

	private static Map<Integer, BankAccount> accounts = new HashMap<Integer, BankAccount>();
	private static ArrayList<BankAccount> accountsList;
	private static Validator valid = new Validator();
	private static int testTransactionFile;
	private static boolean admin = false;
	static String resultsGlobal = " ";

	/**
	 * This soley a testing method to check for condition coverage
	 * 
	 * @return an integer
	 */
	public int gettestTransactionFile() {
		;
		return testTransactionFile;
	}

	/**
	 * Sets accounts mainly used for white box testing
	 * 
	 * @param number
	 *            account number
	 * @param name
	 *            account name
	 * @param active
	 *            status of account
	 * @param balance
	 *            balance of account
	 * @param type
	 *            account type
	 * @param transactions
	 *            account transactions
	 */
	public static void setAccounts(int number, String name, boolean active,
			float balance, char type, int transactions) {
		accounts.put(number, new BankAccount(number, name, active, balance,
				type, transactions));
	}

	/**
	 * Returns a map of the accounts
	 * 
	 * @return returns the map
	 */
	public static Map<Integer, BankAccount> getAccounts() {
		return accounts;
	}

	/**
	 * Returns an array list of all the accounts
	 * 
	 * @return returns an ArrayList
	 */
	public static ArrayList<BankAccount> getAccountsList() {
		accountsList = new ArrayList<BankAccount>(accounts.values());
		return accountsList;
	}

	/**
	 * The withdrawal function
	 * 
	 * @param accountNum
	 *            Account Number
	 * @param account
	 *            Account
	 * @param balance
	 *            money being transfered
	 */
	public static float withdrawal(int accountNum, BankAccount account,
			float balance) {
		System.out.println("withdrawal");
		System.out.println(accountNum);

		String results = valid.withdrawal(account.getBalance(),
				account.getType(), balance, accountNum, "Withdrawal", admin);
		float fee1;
		if (admin) {
			fee1 = (float)0;
		} else {
			fee1 = account.getTransactionFee();
		}
		resultsGlobal = results;
		if (results.equals("Pass")) {
			System.out.println("Withdrawal " + " successful.");
			accounts.get(accountNum).setBalance(
					-(balance + fee1));
			System.out.println("Withdrawal " + account.getBalance());
		}
		return accounts.get(accountNum).getBalance();
	}

	/**
	 * Transfer function
	 * 
	 * @param accountNum
	 *            Account number from
	 * @param accountNum2
	 *            Account number to
	 * @param account
	 *            Account from
	 * @param account2
	 *            Account to
	 * @param balance
	 *            money being transfered
	 */
	public static float[] transfer(int accountNum, int accountNum2,
			BankAccount account, BankAccount account2, float balance) {
		String results = valid.withdrawal(account.getBalance(),
				account.getType(), balance, accountNum, "Transfer1",admin);
		resultsGlobal = results;
		float fee1;
		if (admin) {
			fee1 = (float)0;
		} else {
			fee1 = account.getTransactionFee();
		}
		if (results.equals("Pass")) {
			String results2 = valid.deposit(account2.getBalance(),
					account.getType(), balance, accountNum2, "Transfer2",true);
			resultsGlobal = results2;
			if (results2.equals("Pass")) {
				System.out.println("Transfer1" + " successful.");
				accounts.get(accountNum).setBalance(
						-(balance  + fee1));
				System.out.println("Transfer1" + account.getBalance());
				System.out.println("Transfer2" + " successful.");
				accounts.get(accountNum2).setBalance(
						(balance));
				System.out.println("Transfer2" + account2.getBalance());
			}
		}
		float[] test = new float[2];
		test[0] = accounts.get(accountNum).getBalance();
		test[1] = accounts.get(accountNum2).getBalance();
		return test;
	}

	/**
	 * Paybill function
	 * 
	 * @param accountNum
	 *            Account Number
	 * @param account
	 *            Account
	 * @param balance
	 *            money being transfered
	 * @param misc
	 *            string for mm field
	 * @return
	 */
	public static float paybill(int accountNum, BankAccount account,
			float balance, String misc) {
		System.out.println("Paybill");
		System.out.println(accountNum);
		account = accounts.get(accountNum);
		String results = valid.paybill(account.getBalance(), account.getType(),
				balance, accountNum, misc, admin);
		resultsGlobal = results;
		float fee1;
		if (admin) {
			fee1 = (float)0;
		} else {
			fee1 = account.getTransactionFee();
		}
		if (results.equals("Pass")) {
			System.out.println("Paybill" + " successful.");
			accounts.get(accountNum).setBalance(
					-(balance + fee1));
			System.out.println("Paybill" + account.getBalance());
		}
		return accounts.get(accountNum).getBalance();

	}

	/**
	 * Deposit function
	 * 
	 * @param accountNum
	 *            Account Number
	 * @param account
	 *            Account
	 * @param balance
	 *            money being transfered
	 * @return
	 */
	public static float deposit(int accountNum, BankAccount account,
			float balance) {

		System.out.println("deposit");
		System.out.println(accountNum);
		account = accounts.get(accountNum);
		String results = valid.deposit(account.getBalance(), account.getType(),
				balance, accountNum, "Deposit", admin);
		resultsGlobal = results;
		float fee1;
		if (admin) {
			fee1 = (float)0;
		} else {
			fee1 = account.getTransactionFee();
		}
		if (results.equals("Pass")) {
			System.out.println("Deposit" + " successful.");
			accounts.get(accountNum).setBalance(
					(balance - fee1));
			System.out.println("Deposit " + account.getBalance());
		}
		return accounts.get(accountNum).getBalance();
	}

	/**
	 * Create function
	 * 
	 * @param accountNum
	 *            Account Number
	 * @param accountName
	 *            Account Name
	 * @param balance
	 *            money being transfereds
	 * @return
	 */
	public static int create(int accountNum, String accountName, float balance) {
		System.out.println("Create");
		System.out.println(accountNum);
		String results = valid.create(accounts, accountNum, balance);
		resultsGlobal = results;
		if (results.equals("Pass")) {
			BankAccount account = new BankAccount(accountNum, accountName,
					true, balance, 'N', 0);
			accounts.put(accountNum, account);
		} else if(results.equals("Fail")) {
			boolean checkExist = true;
			int accountNew = accountsList.get(accountsList.size() - 1).getNumber();
			while(checkExist){
				accountNew++;
				checkExist = false;
				for(BankAccount i: accountsList){
					if(i.getNumber() == accountNew){
						checkExist = true;
					}
				}
			}
			BankAccount account = new BankAccount(accountNew, accountName,
					true, balance, 'N', 0);
			accounts.put(accountNew, account);
		}
		// Makes a List from the Hashmap of accounts
		accountsList = new ArrayList<BankAccount>(accounts.values());
		// Sorts the List
		Collections.sort(accountsList);

		return accounts.get(accountNum).getNumber();
	}

	/**
	 * methods that change account value
	 * 
	 * @param accountNum
	 *            Account Number
	 * @param accountName
	 *            Account Name
	 * @param Type
	 *            Type of method to use
	 */
	public static String accChange(int accountNum, String accountName,
			String Type) {
		System.out.println("delete");
					System.out.println(accounts.get(4));
		String result = valid.verifyUser(accounts, accountNum, accountName,
				Type);
		resultsGlobal = result;

		if (result.equals("Pass")) {
			if (Type.compareTo("delete") == 0) {
				accounts.remove(accountNum);
				for(int i = 0; i < accountsList.size(); i++) {
					if(accountsList.get(i).getNumber() == accountNum){
						accountsList.remove(i);
					}
				}
				return "delete";
			} else if (Type.compareTo("disable") == 0) {
				accounts.get(accountNum).disable();
				return "disable";
			} else if (Type.compareTo("enable") == 0) {
				accounts.get(accountNum).enable();
				return "enable";
			} else if (Type.compareTo("change plan") == 0) {
				accounts.get(accountNum).changeType();
				return "change plan";
			}
		}
		return "fail";
	}

	/**
	 * 
	 * @return a list of files in a direction ending with transaction
	 */
	public static File[] getTransactions() {
		File dir = new File("./");
		File[] match = dir.listFiles(new FilenameFilter() {
			public boolean accept(File dir, String name) {
				return name.endsWith("Transaction.txt");
			}
		});
		return match;
	}

	/**
	 * Merges transaction files in the form xxxxTransaction.txt, where xxxx is a
	 * number from 0001 to 9999
	 */
	public static void mergeTransactions() {
		try {

			FileInputStream fis;
			BufferedReader br;
			PrintWriter writer = new PrintWriter("../Application/Accounts/MergedTransactionFile.txt",
					"UTF-8");

			// Grabbing the current directory via ./ allows dynamic usage.
			File[] match = getTransactions();

			//
			for (File file : match) {
				System.out.println(file.getName());
				fis = new FileInputStream(file.getName());
				br = new BufferedReader(new InputStreamReader(fis));
				String line;
				while ((line = br.readLine()) != null) {
					writer.println(line);
				}
			}

			// Appending an extra, empty 00 line allows subsequent methods to
			// know which line should not compute transactions.
			writer.print(padSpace(41, "00"));
			writer.close();

		} catch (IOException e) {
			System.out
					.println("ERROR: Issue reading transaction files. \n" + e);
			return;
		}
	}

	/**
	 * Takes the inputed MasterAccountsFile, and stores this data in a map.
	 * 
	 * @param file
	 *            : The inputted file equivalent to MasterAccountFile.txt
	 */
	public static Map<Integer, BankAccount> importAccountsFile(String file) {
		try {
			Map<Integer, BankAccount> accounts = new HashMap<Integer, BankAccount>();

			FileInputStream fis = new FileInputStream(file);

			// Construct BufferedReader from InputStreamReader
			BufferedReader br = new BufferedReader(new InputStreamReader(fis));

			String line;
			while ((line = br.readLine()) != null) {
				// Relevant info must be grabbed from each line in the file, to
				// store it relative to a account.

				String accountNumberString = line.substring(0, 5);
				int accountNumber = Integer.parseInt(accountNumberString);

				String accountName = line.substring(6, 26);
				accountName = accountName.trim();

				char statusChar = line.charAt(27);
				boolean status = statusChar == 'A';

				String balanceString = line.substring(29, 37);
				float balance = Float.parseFloat(balanceString);

				String transactionString = line.substring(38, 42);
				int transactions = Integer.parseInt(transactionString);
				char accountType = line.charAt(43);
				BankAccount account = new BankAccount(accountNumber,
						accountName, status, balance, accountType, transactions);

				accounts.put(accountNumber, account);
			}

			br.close();

			return accounts;

		} catch (IOException e) {
			System.out
					.println("Error: Issue when reading accounts file \n" + e);
			return null;
		}
	}

	/*
	 * Parameter(s): Filename of transaction file. Reads the transaction file
	 * and runs the transactions.
	 */
	public static void importTransactionFile(String file) {
		try {
			FileInputStream fis = new FileInputStream(file);

			// Construct BufferedReader from InputStreamReader
			BufferedReader br = new BufferedReader(new InputStreamReader(fis));
			// Hold the results of check
			// Hold the second user of results
			String line;
			while (!(line = br.readLine())
					.equals("00                                       ")
					&& !(resultsGlobal.equals("Fatal"))) {
				// TODO: Debugging info, remove
				//System.out.println(line);

				// Gets the transaction id number and converts it to an integer
				String transactionString = line.substring(0, 2);
				int transaction = Integer.parseInt(transactionString);

				// Gets the account name and removes the trailing spaces
				String accountName = line.substring(3, 23);
				accountName = accountName.replaceAll("\\s+$", "");

				// Gets the account number and converts it to an integer
				String accountNumString = line.substring(24, 29);
				int accountNum = Integer.parseInt(accountNumString);

				// Gets the account balance and converts it to a float
				String balanceString = line.substring(30, 38);

				float balance = Float.parseFloat(balanceString);
				
				// Gets the misc field
				// TODO: Find out what this is used for?
				String misc = line.substring(39, 41);
				System.out.println("MISC " + misc + " " + misc.length());
				// Here, distribute tasks depending on what the transaction code
				// is. (FOR BALANCE CHANGES, WE SHOULD MAKE USE OF A NEW OBJECT
				// IF POSSIBLE)
				switch (transaction) {
				case 0:
					admin = false;
					break;
				case 10: // End of session, unsure if anything needed
					testTransactionFile = 10;
					System.out.println("Logged in/out");
					if(misc.compareTo("A ")==0){
						admin = true;
						System.out.println("True");
					}
					break;
				case 1: // withdrawal
					testTransactionFile = 1;
					withdrawal(accountNum, accounts.get(accountNum), balance);
					accounts.get(accountNum).addTransactions();
					break;
				case 2: // transfer
					testTransactionFile = 2;
					// gets the line for second user
					line = br.readLine();
					// gets the account number for the second user
					String accountNumString2 = line.substring(24, 29);
					// changes the account number to an int
					int accountNum2 = Integer.parseInt(accountNumString2);
					// Creates a tmp second account for transfter
					transfer(accountNum, accountNum2, accounts.get(accountNum),
							accounts.get(accountNum2), balance);
					accounts.get(accountNum).addTransactions();
					break;
				case 3: // paybill
					testTransactionFile = 3;
					paybill(accountNum, accounts.get(accountNum), balance, misc);
					accounts.get(accountNum).addTransactions();
					break;
				case 4: // deposit
					testTransactionFile = 4;
					deposit(accountNum, accounts.get(accountNum), balance);
					accounts.get(accountNum).addTransactions();
					break;
				case 5: // create
					testTransactionFile = 5;
					create(accountNum, accountName, balance);
					break;
				case 6: // delete
					testTransactionFile = 6;
					accChange(accountNum, accountName, "delete");
					break;
				case 7: // disable
					testTransactionFile = 7;
					accChange(accountNum, accountName, "disable");
					accounts.get(accountNum).addTransactions();
					break;
				case 8: // changeplan
					testTransactionFile = 8;
					accChange(accountNum, accountName, "change plan");
					accounts.get(accountNum).addTransactions();
					break;
				case 9: // enable
					testTransactionFile = 9;
					accChange(accountNum, accountName, "enable");
					accounts.get(accountNum).addTransactions();
					break;
				default:
					testTransactionFile = 11;
					System.out.println("Error: Command not found!");
					break;
				}
			}

			br.close();

		} catch (IOException e) {
			System.out.println("Error: Issue when reading transaction file \n"
					+ e);
			return;
		}
	}

	/**
	 * Writes the Master and current account files in a sorted fashion
	 * 
	 * @param accounts
	 *            : A list of all accounts, in sorted order.
	 * @param isMaster
	 *            : distinction between writing to master file or current file.
	 */
	public static void writeFile(List<BankAccount> accounts, boolean isMaster) {
		String active;
		Float preBalance;
		String balance;
		PrintWriter writer;

		try {
			// To remove unneeded repetition, writer must be implemented in
			// different ways.
			if (isMaster) {
				writer = new PrintWriter("../Application/Accounts/MasterAccountFile.txt", "UTF-8");
			} else {
				writer = new PrintWriter("../Application/Accounts/CurrentAccountFile.txt", "UTF-8");
			}

			for (int i = 0; i < accounts.size(); i++) {
				if (accounts.get(i).getStatus()) {
					active = "A";
				} else {
					active = "D";
				}

				preBalance = accounts.get(i).getBalance();
				balance = String.format("%.2f", preBalance);

				writer.print(padZero(5,
						String.valueOf(accounts.get(i).getNumber()))
						+ " "
						+ padSpace(20, accounts.get(i).getName())
						+ " "
						+ active + " " + padZero(8, balance) + " ");
				// This statement is only printed if printing to the master
				// account file.
				if (isMaster) {
					writer.print(padZero(4,
							String.valueOf(accounts.get(i).getTransactions()))
							+ " ");
				}
				writer.print(accounts.get(i).getType());

				if (accounts.size() - i != 1) {
					writer.print("\n");
				}
			}

			writer.close();
		} catch (IOException e) {
			System.out.println("ERROR: Issue writing master account file. \n"
					+ e);
			return;
		}

	}

	/**
	 * For transaction info containing strings, this method will pad spaces to
	 * fit the character requirements
	 * 
	 * @param totalLength
	 *            : The character requirement of the string
	 * @param text
	 *            : The actual contents of the string before padding.
	 */
	public static String padSpace(int totalLength, String text) {
		int padNum = totalLength - text.length();
		for (int i = 0; i < padNum; i++) {
			text = text + " ";
		}
		return text;
	}

	/**
	 * For transaction info containing numerical data, this method will pad
	 * zeroes to fit the character requirements
	 * 
	 * @param totalLength
	 *            : the character requirement of the numerical data
	 * @param value
	 *            : the actual value of the integer, in String form.
	 */
	public static String padZero(int totalLength, String value) {
		int padNum = totalLength - value.length();
		for (int i = 0; i < padNum; i++) {
			value = "0" + value;
		}
		return value;
	}

	/*
	 * Takes the merged transaction file and master bank accounts file as
	 * parameters Creates a current bank accounts file and new master bank
	 * accounts file
	 */
	public static void main(String[] args) {

		if (args.length != 1) {
			System.out
					.println("Error: Provide arguments Merged Transaction File.");
			return;
		}
		// CHANGE THIS FOR MASTER ACCOUNT FILE
		accounts = importAccountsFile("../Application/Accounts/MasterAccountFile.txt");

		if (accounts == null) {
			System.out.println("Error: No accounts found!");
			return;
		}

		// Makes a List from the Hashmap of accounts
		accountsList = new ArrayList<BankAccount>(accounts.values());
		// Sorts the List
		Collections.sort(accountsList);
		// Prints the list out
		System.out.println(accountsList);

		// TODO: Just handle the transactions as standard input with the same
		// code as in this function
		importTransactionFile(args[0]);

		// Write to the master account file
		writeFile(accountsList, true);
		// Write to the current account file.
		writeFile(accountsList, false);

	}
}

