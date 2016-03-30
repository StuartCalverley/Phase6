import static org.junit.Assert.*;

import org.junit.Test;


public class BankAccountTest {

  @Test
  public void testBankAccount() {
    BankAccount testAccount = new BankAccount(1000, "Johnny Test", true, 100.0f, 'S', 3);
    
    assertEquals("Account number incorrect.", 1000, testAccount.getNumber());
    assertEquals("Account name incorrect.", "Johnny Test", testAccount.getName());
    assertEquals("Account state incorrect.", true, testAccount.getStatus());
    assertEquals("Account balance incorrect.", 100.0f, testAccount.getBalance(), 0.001f);
    assertEquals("Account type incorrect.", 'S', testAccount.getType());
    assertEquals("Account transactions incorrect.", 3, testAccount.getTransactions());
  }

  @Test
  public void testSetBalance() {
    BankAccount testAccount = new BankAccount(1000, "Johnny Test", true, 100.0f, 'S', 3);
    
    testAccount.setBalance(3.14f);
    assertEquals("Account balance incorrect.", 103.14f, testAccount.getBalance(), 0.001f);
  }

  @Test
  public void testEnable() {
    BankAccount testAccount = new BankAccount(1000, "Johnny Test", false, 100.0f, 'S', 3);
    
    // Tests the true case for the if statement
    boolean ret = testAccount.enable();
    assertEquals("Account status incorrect.", true, testAccount.getStatus());
    assertEquals("Account status return incorrect.", true, ret);
    
    // Tests the else case of the if statement
    ret = testAccount.enable();
    assertEquals("Account status incorrect (Account already enabled test).", true, testAccount.getStatus());
    assertEquals("Account status return incorrect (Account already enabled test).", false, ret);
  }

  @Test
  public void testDisable() {
    BankAccount testAccount = new BankAccount(1000, "Johnny Test", true, 100.0f, 'S', 3);
    
    // Tests the true case for the if statement
    boolean ret = testAccount.disable();
    assertEquals("Account status incorrect.", false, testAccount.getStatus());
    assertEquals("Account status return incorrect.", true, ret);
    
    // Tests the else case of the if statement
    ret = testAccount.disable();
    assertEquals("Account status incorrect (Account already disabled test).", false, testAccount.getStatus());
    assertEquals("Account status return incorrect (Account already disabled test).", false, ret);
  }

  @Test
  public void testChangeType() {
    BankAccount testAccount = new BankAccount(1000, "Johnny Test", true, 100.0f, 'S', 3);
    
    char ret = testAccount.changeType();
    assertEquals("Account type incorrect.", 'N', ret);
    
    ret = testAccount.changeType();
    assertEquals("Account type incorrect.", 'S', ret);
  }

  @Test
  public void testGetTransactionFee() {
    BankAccount testStudentAccount = new BankAccount(1000, "Johnny Test", true, 100.0f, 'S', 3);
    BankAccount testNormalAccount = new BankAccount(2000, "Billy Bob", true, 100.0f, 'N', 12);
    
    float fee = testStudentAccount.getTransactionFee();
    assertEquals("Student transaction fee incorrect.", 0.05f, fee, 0.001f);
    
    fee = testNormalAccount.getTransactionFee();
    assertEquals("Normal transaction fee incorrect.", 0.10f, fee, 0.001f);
  }

  @Test
  public void testAddTransactions() {
    BankAccount testAccount = new BankAccount(1000, "Johnny Test", true, 100.0f, 'S', 3);
    
    testAccount.addTransactions();
    int trans = testAccount.getTransactions();
    assertEquals("Add transaction incorrect.", 4, trans);
  }

  @Test
  public void testCompareTo() {
    BankAccount testStudentAccount = new BankAccount(1000, "Johnny Test", true, 100.0f, 'S', 3);
    BankAccount testNormalAccount = new BankAccount(2000, "Billy Bob", true, 100.0f, 'N', 12);
    
    int result = testStudentAccount.compareTo(testNormalAccount);
    assertEquals("Compare to incorrect.", -1, result);
    
    result = testNormalAccount.compareTo(testStudentAccount);
    assertEquals("Compare to incorrect.", 1, result);
  }

}
