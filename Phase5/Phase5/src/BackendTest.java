import static org.junit.Assert.*;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

import org.junit.Test;

public class BackendTest {
	@Test
	public void withdrawalTest(){
		Backend B = new Backend();
		B.setAccounts(10000, "Janahan", true, (float) 100.00, 'S', 0);
		float test = B.withdrawal(10000, B.getAccounts().get(10000), 50);
		assertEquals("Valid Withdrawal",test,49.95,0.01);
		test = B.withdrawal(10000, B.getAccounts().get(10000), 120);
		assertEquals("Invalid Withdrawal",test,49.95,0.01);
	}
	
	@Test
	public void DepositTest(){
		Backend B = new Backend();
		B.setAccounts(10000, "Janahan", true, (float) 100.00, 'S', 0);
		float test = B.deposit(10000, B.getAccounts().get(10000), 50);
		assertEquals("Valid Deposit",test,149.95,0.01);
		test = B.deposit(10000, B.getAccounts().get(10000), 100000);
		assertEquals("Invalid Deposit",test,149.95,0.01);
	}
	
	@Test
	public void CreateTest(){
		Backend B = new Backend();
		int accountNum = B.create(10000, "Janahan", 20000);
		assertEquals("Valid Create",10000, accountNum);
	}
	
	@Test
	public void TransferTest(){
		Backend B = new Backend();
		B.setAccounts(10000, "Janahan", true, (float) 100.00, 'S', 0);
		B.setAccounts(10001, "Janahan", true, (float) 200.00, 'S', 0);
		float test[] = B.transfer(10000,10001, B.getAccounts().get(10000), B.getAccounts().get(10001), 50);
		float results[] = {49.95f,249.95f};
		assertTrue("Valid Transfer",Arrays.equals(test, results));
		test = B.transfer(10000,10001, B.getAccounts().get(10000), B.getAccounts().get(10001), 50);
		assertTrue("Invalid Transfer",Arrays.equals(test, results));
	}
	
	@Test
	public void PayBillTest(){
		Backend B = new Backend();
		B.setAccounts(10000, "Janahan", true, (float) 100.00, 'S', 0);
		float result = B.paybill(10000, B.getAccounts().get(10000), 20,"TV");
		assertEquals("Valid Paybill",79.95,result,0.001);
		result = B.paybill(10000, B.getAccounts().get(10000), 100,"TV");
		assertEquals("InValid Transfer",79.95,result,0.001);
	}

	@Test
	public void accChangeTest(){
		Backend B = new Backend();
		B.setAccounts(10000, "Janahan", true, (float) 100.00, 'S', 0);
		B.setAccounts(10001, "Janahan", true, (float) 100.00, 'N', 0);
		String results = B.accChange(10001, "Janahan", "delete");
		assertEquals("Valid delete",results,"delete");
		results = B.accChange(10000, "Janahan", "disable");
		assertEquals("Valid disable",results,"disable");
		results = B.accChange(10000, "Janahan", "enable");
		assertEquals("Valid enable",results,"enable");
		results = B.accChange(10000, "Janahan", "change plan");
		assertEquals("Valid change plan",results,"change plan");
		results = B.accChange(10001, "Janahan", "delete");
		assertEquals("Invalid account",results,"fail");
		
		
	}
	
	@Test
	public void mergeTransactions() throws FileNotFoundException{
		Backend b = new Backend();
		b.mergeTransactions();
		ArrayList<String> expect = fileCompare("MergedTransactionFile.txt");
		ArrayList<String> result = fileCompare("TestMergedTransactionFile.txt");
		assertEquals(expect.size(),result.size());
		if(expect.size() == result.size()){
			for(int i = 0; i < expect.size(); i++){
				assertEquals("Valid Merge Transactions",expect.get(i),result.get(i));
			}
		}
	
	}
	
	@Test
	public void getTransactionsTest()  {
		Backend b = new Backend();
		File match[] = b.getTransactions();
		assertEquals("Valid find test file 0001",match[match.length - 1].getName(), "0001Transaction.txt");
		assertEquals("Valid find test file 0002",match[match.length - 2].getName(), "0002Transaction.txt");
	}

	@Test
	public void padSpaceTest() {
		Backend b = new Backend();
		assertEquals(b.padSpace(20, "Hello "), "Hello               ");
	}

	@Test
	public void padZeroTest() {
		Backend b = new Backend();
		assertEquals(b.padZero(8, "100.10"), "00100.10");
	}
	
	@Test
	public void importAccountsFileTest(){
		Backend b = new Backend();
		Map<Integer, BankAccount> test =b.importAccountsFile("MasterAccountFileTest.txt" );
		BankAccount bank = new BankAccount(10000, "Troy Bartan         ", true, (float)1.80,'S', 60);
		assertEquals(test.get(10000).getName(),bank.getName() );
		assertEquals(test.get(10000).getNumber(),bank.getNumber() );
		assertEquals(test.get(10000).getBalance(),bank.getBalance(),0.009 );
		assertEquals(test.get(10000).getTransactions(),bank.getTransactions() );
		
	}	
	
	@Test
	public void TestTransactionFile(){ 
		Backend B = new Backend();
		B.setAccounts(10000, "Janahan", true, (float) 1000.00, 'S', 0);
		B.setAccounts(10001, "Janahan", true, (float) 1000.00, 'N', 0);
		B.setAccounts(10002, "Janahan", true, (float) 1000.00, 'N', 0);
		
		B.importTransactionFile("transactionstest1.txt");
		assertEquals("Valid test case 1 in import Transaction file ",1,B.gettestTransactionFile());
		B.importTransactionFile("transactionstest2.txt");
		assertEquals("Valid test case 2 in import Transaction file ",2,B.gettestTransactionFile());
		B.importTransactionFile("transactionstest3.txt");
		assertEquals("Valid test case 3 in import Transaction file ",3,B.gettestTransactionFile());
		B.importTransactionFile("transactionstest4.txt");
		assertEquals("Valid test case 4 in import Transaction file ",4,B.gettestTransactionFile());
		B.importTransactionFile("transactionstest5.txt");
		assertEquals("Valid test case 5 in import Transaction file ",5,B.gettestTransactionFile());
		B.importTransactionFile("transactionstest6.txt");
		assertEquals("Valid test case 6 in import Transaction file ",6,B.gettestTransactionFile());
		B.importTransactionFile("transactionstest7.txt");
		assertEquals("Valid test case 7 in import Transaction file ",7,B.gettestTransactionFile());
		B.importTransactionFile("transactionstest8.txt");
		assertEquals("Valid test case 8 in import Transaction file ",8,B.gettestTransactionFile());
		B.importTransactionFile("transactionstest9.txt");
		assertEquals("Valid test case 9 in import Transaction file ",9,B.gettestTransactionFile());
		B.importTransactionFile("transactionstest10.txt");
		assertEquals("Valid test case 10 in import Transaction file ",10,B.gettestTransactionFile());
		B.importTransactionFile("transactionstest11.txt");
		assertEquals("Valid test case for any other cases in import Transaction file ",11,B.gettestTransactionFile());
		
	}
	public ArrayList<String> fileCompare(String fileName) throws FileNotFoundException {
		Scanner file = new Scanner(new File(fileName));
		ArrayList<String> fileArray = new ArrayList<String>();
		while (file.hasNextLine()) {
			fileArray.add(file.nextLine());
		}
		return fileArray;
	}
}
