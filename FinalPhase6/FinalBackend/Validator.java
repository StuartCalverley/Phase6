import java.util.Map;

public class Validator {
	// Static variable for pass case
	private final String pass = "Pass";
	// Static variable for pass case
	private final String fail = "Fail";
	// Static variable for pass case
	private final String fatal = "Fatal";

	/**
	 * The purpose is to check is the final balance fits the constraints
	 * 
	 * @param balance
	 *            The total amount of money in available
	 * @param command
	 *            The command that the check came from
	 * @param accNum
	 *            The account number for the accounts
	 * @return
	 */
	public boolean balanceCheck(float balance, String commands, int accNum) {
		if (balance < 0) {
			System.out.println("ERROR: " + commands
					+ " caused negative balance on account " + accNum);
		} else if (balance > (float) 99999.99f) {
			System.out.println("ERROR: " + commands
					+ " caused balance over 99999.99 on account " + accNum);
		} else {
			return true;
		}
		return false;
	}

	/**
	 * Validates any form of withdrawal
	 * 
	 * @param balance
	 *            the amount of money of the account
	 * @param type
	 *            The type of account student or non student
	 * @param transactionAmount
	 *            The amount of money being processed in a transaction
	 * @param accNum
	 *            The account number number of the user
	 * @param command
	 *            The command it came from
	 * @param admin 
	 *			  Checks if the user if logged in as admin
	 * @return a string either pass, fail, or fatal to show results of
	 *         validation
	 */
	public String withdrawal(float balance, char type, float transactionAmount,
			int accNum, String command, boolean admin) {
		float fee = 0;
		// Determine the transfer fee
		if (admin) {
			fee = (float) 0;
		} else {

			if (type == 'S') {
				fee = (float) 0.05;
			} else if (type == 'N') {
				fee = (float) 0.10;
			} else {
				System.out
						.println("ERROR: Invalid account type (Master Accounts File)");
				return fatal;
			}

		}
		// Determine what amount to transfer
		balance = balance + -(transactionAmount + fee);
		// Performs the final balance check
		if (!(balanceCheck(balance, command, accNum))) {
			return fail;
		}
		return pass;
	}

	/**
	 * Validates any form of deposit
	 * 
	 * @param balance
	 *            the amount of money of the account
	 * @param type
	 *            The type of account student or non student
	 * @param transactionAmount
	 *            The amount of money being processed in a transaction
	 * @param accNum
	 *            The account number number of the user
	 * @param command
	 *            The command it came from
	 * @param admin 
	 *			  Checks if the user if logged in as admin
	 * @return a string either pass, fail, or fatal to show results of
	 *         validation
	 */
	public String deposit(float balance, char type, float transactionAmount,
			int accNum, String command, boolean admin) {
		float fee = 0;
		// Determine the transfer fee
		if (admin) {
			fee = (float) 0;
		} else {

			if (type == 'S') {
				fee = (float) 0.05;
			} else if (type == 'N') {
				fee = (float) 0.10;
			} else {
				System.out
						.println("ERROR: Invalid account type (Master Accounts File)");
				return fatal;
			}

		}		// Determine what amount to transfer
		balance = balance + (transactionAmount + fee);
		// Perform the final balance check
		if (!(balanceCheck(balance, command, accNum))) {
			return fail;
		}
		return pass;
	}

	/**
	 * Validates any form of paybill
	 * 
	 * @param balance
	 *            the amount of money of the account
	 * @param type
	 *            The type of account student or non student
	 * @param transactionAmount
	 *            The amount of money being processed in a transaction
	 * @param accNum
	 *            The account number number of the user
	 * @param mm
	 *            The company the bill is being payed to.
	 * @param admin 
	 *			  Checks if the user if logged in as admin
	 * @return a string either pass, fail, or fatal to show results of
	 *         validation
	 */
	public String paybill(float balance, char type, float transactionAmount,
			int accNum, String mm, boolean admin) {
		if (!(mm.equals("EC") || mm.equals("TV") || mm.equals("CQ"))) {
			System.out.println("ERROR: Paybill company " + mm
					+ " does not exist (Merged Transaction File)");
			return fatal;
		}
		if (!(withdrawal(balance, type, transactionAmount, accNum, "Paybill",
				admin).equals("Pass"))) {
			return fail;
		}
		return pass;
	}

	/**
	 * Validate the create function
	 * 
	 * @param accounts
	 *            list of all accounts
	 * @param accNum
	 *            the new account number
	 * @param amount
	 *            the amount
	 * @return a string either pass, fail, or fatal to show results of
	 *         validation
	 */
	public String create(Map<Integer, BankAccount> accounts, int accNum,
			float amount) {
		if (accNumExist(accounts, accNum)) {
			System.out.println("ERROR: Create the account number " + accNum
					+ " is already in use");
			return fail;
		}
		if (!(balanceCheck(amount, "Create", accNum))) {
			return fail;
		}
		return pass;
	}

	/**
	 * Checks if the account exists already.
	 * 
	 * @param accounts
	 *            list of all accounts
	 * @param accName
	 *            The name of the account
	 * @return true if name is found false if name is not found
	 */
	public boolean nameExist(Map<Integer, BankAccount> accounts, String accName) {
		String name;
		//System.out.println("IN THE NAMEEXIST method and name is:"+ accName + ".");
		System.out.println(accounts.get(4));
		for (int key : accounts.keySet()) {
			name = accounts.get(key).getName();
			//System.out.println("name asdasda: " +  name + ".");
			if (name.equals(accName)) {
				return true;
			}
		}
		return false;
	}

	/**
	 * Check if the account number exists
	 * 
	 * @param accounts
	 *            list of all accounts
	 * @param accNum
	 *            The account number
	 * @return true if name is found false if name is not found
	 */
	public boolean accNumExist(Map<Integer, BankAccount> accounts, int accNum) {
		for (int key : accounts.keySet()) {
			if (key == (accNum)) {
				return true;
			}
		}
		return false;
	}

	/**
	 * Check if the account number and account name are matching
	 * 
	 * @param accounts
	 *            list of all accounts
	 * @param accNum
	 *            The account number
	 * @param accName
	 *            The account name
	 * @return true if name is owned by account is found false if name is not
	 *         found
	 */
	public boolean matchNumName(Map<Integer, BankAccount> accounts, int accNum,
			String accName) {
		for (int key : accounts.keySet()) {
			if (key == (accNum)) {
				if (accounts.get(accNum).getName().equals(accName)) {
					return true;
				}
			}
		}
		return false;
	}

	/**
	 * Check if the account number and account name are matching
	 * 
	 * @param accounts
	 *            list of all accounts
	 * @param accNum
	 *            The account number
	 * @param accName
	 *            The account name
	 * @param command
	 *            the command the method was called from
	 * @return true if name is owned by account is found false if name is not
	 *         found
	 */
	public String verifyUser(Map<Integer, BankAccount> accounts, int accNum,
			String accName, String command) {
		//System.out.println("THE NAME IS: "+ accName);
		if (!(nameExist(accounts, accName))) {
			System.out.println("ERROR: The account name " + accName
					+ " is not found from command " + command);
			return fail;
		}
		if (!(accNumExist(accounts, accNum))) {
			System.out.println("ERROR: The account num " + accNum
					+ " is not found from command " + command);
			return fail;
		}
		if (!(matchNumName(accounts, accNum, accName))) {
			System.out.println("ERROR: The account num " + accNum
					+ " and name " + accName
					+ " does not match (Merged Transaction File)");
			return fatal;
		}
		return pass;
	}
}
