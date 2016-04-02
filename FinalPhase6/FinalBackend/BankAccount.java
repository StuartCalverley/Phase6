
public class BankAccount implements Comparable<BankAccount> {
  
  private int number;
  private String name;
  private float balance;
  private boolean active;
  private char type;
  private int transactions;
  
  public BankAccount(int number, String name, boolean active, float balance, char type, int transactions) {
    this.number = number;
    this.name = name;
    this.active = active;
    this.balance = balance;
    this.type = type;
    this.transactions = transactions;

  }
  
  // Prints basic information about the account to help with debugging
  public String toString() {
    return "Name: " + this.name + "\nNumber:" + this.number + "\nBalance: " + this.balance + "\n\n\n";
  }
  
  // Simply adds the amount to the current balance
  public void setBalance(float amount) {
    this.balance += amount;
  }
  
  // Enables account. Returns true if account enabled else returns false.
  public boolean enable() {
    if(!this.active) {
      this.active = true;
      return true;
    } else {
      return false;
    }
  }
  
  // Disables account. Returns true if account disabled else return false.
  public boolean disable() {
    if(this.active) {
      this.active = false;
      return true;
    } else {
      return false;
    }
  }
  
  // Toggles the account type. Returns the new type of account.
  public char changeType() {
    if(this.type == 'S') {
      this.type = 'N';
    } else {
      this.type = 'S';
    }
    return this.type;
  }
  
  public int getNumber() {
    return this.number;
  }
  
  public String getName() {
    return this.name;
  }
  
  public float getBalance() {
    return this.balance;
  }
  
  public char getType() {
    return this.type;
  }
  
  public boolean getStatus() {
    return this.active;
  }
  
  public float getTransactionFee() {
    if(this.type == 'S') {
      return 0.05f;
    } else {
      return 0.10f;
    }
  }

  public int getTransactions(){
    return transactions;
  }

  public void addTransactions(){
    transactions++; 
  }

  @Override
  public int compareTo(BankAccount otherAccount) {
    if(this.number > otherAccount.number){
      return 1;
    } else {
      return -1;
    }
  }
  
}
